/*
 * Copyright (C) 2015 Krzysztof Smiechowicz. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "execallocator.h"
#include "arosbailout.h"

#include <proto/alib.h>
#include <exec/lists.h>
#include <aros/debug.h>

#undef PAGESIZE
#define PAGESIZE                (4096)
#define ALIGN(val, align)       (((IPTR)val + (IPTR)align - 1) & (~((IPTR)align - 1)))

static const ULONG BLOCKSIZES[] = {1024, 512, 256, 128, 64}; /* In pages */
static const ULONG BLOCKSIZESCOUNT = sizeof(BLOCKSIZES)/sizeof(BLOCKSIZES[0]);

class PageAllocator
{
public:
    PageAllocator();
    ~PageAllocator();
    void * getPages(size_t count, bool executable);
    void * getPages(size_t count, size_t alignment, bool executable);
    void freePages(void * address, size_t count);
    void freePages(void * address);
    int getAllocatedPagesCount();

private:
    struct List blocks;
    struct SignalSemaphore lock;

    struct PageBlock
    {
        struct Node pb_Node;
        IPTR        pb_AllocAddress;
        IPTR        pb_StartAddress;
        IPTR        pb_EndAddress;
        ULONG       pb_Alignment;
        ULONG       pb_Flags;
        WORD        *pb_PagesBitMap; /* 0 - free, -1 allocated, > 0 allocation size (only first page) */
        ULONG       pb_FreePages;
        ULONG       pb_TotalPages;
    };

    void * allocatePagesFromBlock(PageAllocator::PageBlock * block, size_t count, size_t alignment);
    PageAllocator::PageBlock * allocateNewBlock(size_t count, ULONG flags);
    void freeBlock(PageAllocator::PageBlock * block);
    void reportBlockUsage();
};

PageAllocator::PageAllocator()
{
    NEWLIST(&blocks);
    InitSemaphore(&lock);
}

PageAllocator::~PageAllocator()
{
    void * n, *n1;

    ForeachNodeSafe(&blocks, n, n1)
    {
        PageAllocator::PageBlock * block = (PageAllocator::PageBlock *)n;
        freeBlock(block);
    }
}

void PageAllocator::reportBlockUsage()
{
    void * n, *n1;
    ULONG totalpages = 0;

    bug("PageAllocator block usage\n");
    bug("-------------------------\n");
    ForeachNodeSafe(&blocks, n, n1)
    {
        PageAllocator::PageBlock * block = (PageAllocator::PageBlock *)n;
        bug("Block: Size %d KB, Alignment %d KB, %%%d Available\n",
                block->pb_TotalPages * PAGESIZE / 1024,
                block->pb_Alignment / 1024,
                block->pb_FreePages * 100 / block->pb_TotalPages);
        totalpages += block->pb_TotalPages;
    }
    bug("Total allocated size: %d KB\n", totalpages * PAGESIZE / 1024);
    bug("-------------------------\n");
}

PageAllocator::PageBlock * PageAllocator::allocateNewBlock(size_t count, ULONG flags)
{
    PageAllocator::PageBlock * block = (PageAllocator::PageBlock *)AllocMem(sizeof(PageAllocator::PageBlock), MEMF_ANY);

    block->pb_Alignment = PAGESIZE;
    block->pb_Flags = flags;

    void * memoryblock = NULL;
    IPTR allocationsize = 0;

retry:
    ULONG i = 0;
    /* Try to allocation a range of decreasing block sizes */
    while (memoryblock == NULL && i < BLOCKSIZESCOUNT)
    {
        allocationsize = (BLOCKSIZES[i] > count ? BLOCKSIZES[i] : count) * PAGESIZE;
        memoryblock = AllocMem(allocationsize + block->pb_Alignment, block->pb_Flags);
        i++;
    }

    if (!memoryblock)
    {
        if (aros_memory_allocation_error(allocationsize, block->pb_Alignment) == 2)
            return NULL; /* quit */

        goto retry; /* retry */
    }

    block->pb_TotalPages = allocationsize / PAGESIZE;
    block->pb_FreePages = allocationsize / PAGESIZE;

    block->pb_AllocAddress = (IPTR)memoryblock;
    block->pb_StartAddress = (IPTR)ALIGN(block->pb_AllocAddress, block->pb_Alignment);
    block->pb_EndAddress = block->pb_StartAddress + allocationsize;
    block->pb_PagesBitMap = (WORD *)AllocMem(block->pb_TotalPages * sizeof(WORD), MEMF_ANY | MEMF_CLEAR);

    AddTail(&blocks, (struct Node *)block);

    D(bug("Adding page block 0x%lx, %d\n", block->pb_StartAddress, block->pb_TotalPages));
    D(reportBlockUsage());
    return block;
}

void PageAllocator::freeBlock(PageAllocator::PageBlock * block)
{

    IPTR allocationsize = block->pb_TotalPages * PAGESIZE;

    D(bug("Removing page block 0x%x, %d\n", block->pb_StartAddress, block->pb_TotalPages));

    Remove((struct Node *)block);

    FreeMem((APTR)block->pb_AllocAddress, allocationsize + block->pb_Alignment);
    FreeMem(block->pb_PagesBitMap, block->pb_TotalPages * sizeof(WORD));
    FreeMem(block, sizeof(PageAllocator::PageBlock));
    D(reportBlockUsage());
}

void * PageAllocator::allocatePagesFromBlock(PageAllocator::PageBlock * block,
        size_t count, size_t alignment)
{
    const ULONG increment = alignment / PAGESIZE; /* Jump over that many pages */
    IPTR alignedblockaddress;
    ULONG i;

    if (!block)
        return NULL;

    if (block->pb_FreePages < count)
        return NULL;

    /* Calculate initial index:
     * The resulting address at i must be aligned to alignment */

    alignedblockaddress = ALIGN(block->pb_StartAddress, alignment);
    i = (alignedblockaddress - (block->pb_StartAddress)) / PAGESIZE;

    /* i increments to point to next aligned address */
    for (; i < block->pb_TotalPages; i += increment)
    {
        if (block->pb_PagesBitMap[i] == 0)
        {
            bool spacefound = true;
            size_t j = 0;
            /* Check for continous space */
            for (; (j < count && (i + j) < block->pb_TotalPages); j++)
            {
                if (block->pb_PagesBitMap[i + j] != 0)
                {
                    spacefound = false;
                    break;
                }
            }

            if (j != count) /* We exited before count of pages could be checked */
            {
                spacefound = false;
            }

            if (spacefound)
            {
                /* Marks as used */
                block->pb_PagesBitMap[i] = count; /* Store allocation size */
                for (size_t k = 1; k < count; k++)
                {
                    block->pb_PagesBitMap[i + k] = -1;
                }

                block->pb_FreePages -= count;

                D
                (
                IPTR pagesstart = ALIGN((block->pb_StartAddress + (i * PAGESIZE)), PAGESIZE);
                IPTR pagesend = ALIGN((block->pb_StartAddress + ((i + count) * PAGESIZE)), PAGESIZE);

                bug("ALLOC block (0x%x, 0x%x) pages(0x%x, 0x%x)\n", block->pb_StartAddress, block->pb_EndAddress, pagesstart, pagesend);
                );

                return (void *)ALIGN((block->pb_StartAddress + (i * PAGESIZE)), PAGESIZE);
            }
        }
    }

    return NULL;
}

void * PageAllocator::getPages(size_t count, bool executable)
{
    return getPages(count, PAGESIZE, executable);
}

void * PageAllocator::getPages(size_t count, size_t alignment, bool executable)
{
    void * n; void * _return = NULL;
    ULONG flags = MEMF_ANY;

    if (executable) flags = MEMF_EXECUTABLE;

    ObtainSemaphore(&lock);

    ForeachNode(&blocks, n)
    {
        PageAllocator::PageBlock * block = (PageAllocator::PageBlock *)n;

        if (block->pb_Flags != flags)
            continue;

        if (block->pb_FreePages < count)
            continue;

        /* Found block with enough free pages, let's check if they are continous */
        _return = allocatePagesFromBlock(block, count, alignment);
        if (_return != NULL)
        {
            ReleaseSemaphore(&lock);
            return _return;
        }
    }

    /* If we are here, it means none of the blocks was big enough */
    PageAllocator::PageBlock * block = allocateNewBlock(count, flags);
    if (block)
        _return = allocatePagesFromBlock(block, count, alignment);
    ReleaseSemaphore(&lock);
    return _return;
}

/* This version relies on size passed as parameter.
 * Note that in such case, the following must be possible:
 * X = getPages(A)
 * freePages(X + Z, A - Z)
 * freePages(X, Z)
 */
void PageAllocator::freePages(void * address, size_t count)
{
   void * n; IPTR addr = (IPTR)address;

   ObtainSemaphore(&lock);

   ForeachNode(&blocks, n)
   {
       PageAllocator::PageBlock * block = (PageAllocator::PageBlock *)n;
       if (addr >= block->pb_StartAddress && addr <= block->pb_EndAddress)
       {
           IPTR relative = addr - block->pb_StartAddress;
           int pos = relative / PAGESIZE;
           for (size_t i = 0; i < count; i++)
               block->pb_PagesBitMap[i + pos] = 0;
           block->pb_FreePages += count;

           /* Check if block can be freed */
           if (block->pb_FreePages == block->pb_TotalPages)
               freeBlock(block);

           ReleaseSemaphore(&lock);
           return;
       }
   }

   bug("[ExecAllocator]: Address 0x%p not part of any block!\n", (APTR)addr);
   ReleaseSemaphore(&lock);
}

/* This version relies on allocation size stored internally */
void PageAllocator::freePages(void * address)
{
   void * n; IPTR addr = (IPTR)address;

   ObtainSemaphore(&lock);

   ForeachNode(&blocks, n)
   {
       PageAllocator::PageBlock * block = (PageAllocator::PageBlock *)n;
       if (addr >= block->pb_StartAddress && addr <= block->pb_EndAddress)
       {
           IPTR relative = addr - block->pb_StartAddress;
           int pos = relative / PAGESIZE;
           size_t count = 0;

           if (block->pb_PagesBitMap[pos] > 0)
               count = (size_t)block->pb_PagesBitMap[pos];
           /* TODO: implement else ? */

           for (size_t i = 0; i < count; i++)
               block->pb_PagesBitMap[i + pos] = 0;
           block->pb_FreePages += count;

           /* Check if block can be freed */
           if (block->pb_FreePages == block->pb_TotalPages)
               freeBlock(block);

           ReleaseSemaphore(&lock);
           return;
       }
   }

   bug("[ExecAllocator]: Address 0x%p not part of any block!\n", (APTR)addr);
   ReleaseSemaphore(&lock);
}

int PageAllocator::getAllocatedPagesCount()
{
    void * n; int count = 0;

    ObtainSemaphore(&lock);

    ForeachNode(&blocks, n)
    {
        PageAllocator::PageBlock * block = (PageAllocator::PageBlock *)n;
        count += block->pb_TotalPages;
    }

    ReleaseSemaphore(&lock);

    return count;
}

static PageAllocator allocator;

/*************************************************************************************************/

static inline int getPageCount(size_t bytes)
{
    /* Round up size to next page size */
    return (int)((bytes + PAGESIZE - 1) / PAGESIZE);
}

void * allocator_getmem_page_aligned(size_t bytes, bool executable)
{
    int pagecount = getPageCount(bytes);
    void * ptr = allocator.getPages(pagecount, executable);

    D(bug("A:getmem_page_aligned 0x%x -> pagecount %d \n", ptr, pagecount));

    if(ptr)
        memset(ptr, 0, bytes);

    D(reservedAdd(bytes, u););


    return ptr;
}

void * allocator_getmem_aligned(size_t bytes, size_t alignment)
{
    D(bug("A:getmem_aligned bytes %d, alignment %d \n", bytes, alignment));

    /* Can only allocate full pages */
    if (alignment < PAGESIZE) alignment = PAGESIZE;

    int pagecount = getPageCount(bytes);
    void * ptr = allocator.getPages(pagecount, alignment, false);

    if(ptr)
        memset(ptr, 0, bytes);

    return ptr;
}

void allocator_freemem(void * address, size_t bytes)
{
    D(bug("A:freemem 0x%x bytes %d \n", address, bytes));

    int pagecount = getPageCount(bytes);
    allocator.freePages(address, pagecount);
}

void allocator_freemem(void * address)
{
    D(bug("A:freemem 0x%x \n", address));

    allocator.freePages(address);

}
