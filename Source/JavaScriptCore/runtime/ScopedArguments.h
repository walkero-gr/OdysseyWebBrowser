/*
 * Copyright (C) 2015-2018 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#pragma once

#include "GenericArguments.h"
#include "JSLexicalEnvironment.h"

namespace JSC {

// This is an Arguments-class object that we create when you say "arguments" inside a function,
// and one or more of the arguments may be captured in the function's activation. The function
// will copy its formally declared arguments into the activation and then create this object. This
// object will store the overflow arguments, if there are any. This object will use the symbol
// table's ScopedArgumentsTable and the activation, or its overflow storage, to handle all indexed
// lookups.
class ScopedArguments final : public GenericArguments<ScopedArguments> {
private:
    ScopedArguments(VM&, Structure*, WriteBarrier<Unknown>* storage);
    void finishCreation(VM&, JSFunction* callee, ScopedArgumentsTable*, JSLexicalEnvironment*);
    using Base = GenericArguments<ScopedArguments>;

public:
    template<typename CellType>
    static CompleteSubspace* subspaceFor(VM& vm)
    {
        RELEASE_ASSERT(!CellType::needsDestruction);
        return &vm.jsValueGigacageCellSpace;
    }

    // Creates an arguments object but leaves it uninitialized. This is dangerous if we GC right
    // after allocation.
    static ScopedArguments* createUninitialized(VM&, Structure*, JSFunction* callee, ScopedArgumentsTable*, JSLexicalEnvironment*, unsigned totalLength);
    
    // Creates an arguments object and initializes everything to the empty value. Use this if you
    // cannot guarantee that you'll immediately initialize all of the elements.
    static ScopedArguments* create(VM&, Structure*, JSFunction* callee, ScopedArgumentsTable*, JSLexicalEnvironment*, unsigned totalLength);
    
    // Creates an arguments object by copying the arguments from the stack.
    static ScopedArguments* createByCopying(ExecState*, ScopedArgumentsTable*, JSLexicalEnvironment*);
    
    // Creates an arguments object by copying the arguments from a well-defined stack location.
    static ScopedArguments* createByCopyingFrom(VM&, Structure*, Register* argumentsStart, unsigned totalLength, JSFunction* callee, ScopedArgumentsTable*, JSLexicalEnvironment*);
    
    static void visitChildren(JSCell*, SlotVisitor&);
    
    uint32_t internalLength() const
    {
        return storageHeader().totalLength;
    }
    
    uint32_t length(ExecState* exec) const
    {
        VM& vm = exec->vm();
        auto scope = DECLARE_THROW_SCOPE(vm);
        if (UNLIKELY(storageHeader().overrodeThings)) {
            auto value = get(exec, vm.propertyNames->length);
            RETURN_IF_EXCEPTION(scope, 0);
            scope.release();
            return value.toUInt32(exec);
        }
        return internalLength();
    }
    
    bool isMappedArgument(uint32_t i) const
    {
        WriteBarrier<Unknown>* storage = overflowStorage();
        if (i >= storageHeader(storage).totalLength)
            return false;
        unsigned namedLength = m_table->length();
        if (i < namedLength)
            return !!m_table->get(i);
        return !!storage[i - namedLength].get();
    }

    bool isMappedArgumentInDFG(uint32_t i) const
    {
        return isMappedArgument(i);
    }
    
    JSValue getIndexQuickly(uint32_t i) const
    {
        ASSERT_WITH_SECURITY_IMPLICATION(isMappedArgument(i));
        WriteBarrier<Unknown>* storage = overflowStorage();
        unsigned totalLength = storageHeader(storage).totalLength;
        unsigned namedLength = m_table->length();
        if (i < namedLength)
            return preciseIndexMaskPtr(i, totalLength, &m_scope->variableAt(m_table->get(i)))->get();
        return preciseIndexMaskPtr(i, totalLength, storage + (i - namedLength))->get();
    }

    void setIndexQuickly(VM& vm, uint32_t i, JSValue value)
    {
        ASSERT_WITH_SECURITY_IMPLICATION(isMappedArgument(i));
        WriteBarrier<Unknown>* storage = overflowStorage();
        unsigned totalLength = storageHeader(storage).totalLength;
        unsigned namedLength = m_table->length();
        if (i < namedLength)
            preciseIndexMaskPtr(i, totalLength, &m_scope->variableAt(m_table->get(i)))->set(vm, m_scope.get(), value);
        else
            preciseIndexMaskPtr(i, totalLength, storage + (i - namedLength))->set(vm, this, value);
    }

    JSFunction* callee()
    {
        return m_callee.get();
    }

    bool overrodeThings() const { return storageHeader().overrodeThings; }
    void overrideThings(VM&);
    void overrideThingsIfNecessary(VM&);
    void unmapArgument(VM&, uint32_t index);
    
    void initModifiedArgumentsDescriptorIfNecessary(VM& vm)
    {
        GenericArguments<ScopedArguments>::initModifiedArgumentsDescriptorIfNecessary(vm, m_table->length());
    }

    void setModifiedArgumentDescriptor(VM& vm, unsigned index)
    {
        GenericArguments<ScopedArguments>::setModifiedArgumentDescriptor(vm, index, m_table->length());
    }

    bool isModifiedArgumentDescriptor(unsigned index)
    {
        return GenericArguments<ScopedArguments>::isModifiedArgumentDescriptor(index, m_table->length());
    }

    void copyToArguments(ExecState*, VirtualRegister firstElementDest, unsigned offset, unsigned length);

    DECLARE_INFO;
    
    static Structure* createStructure(VM&, JSGlobalObject*, JSValue prototype);
    
    static ptrdiff_t offsetOfStorage() { return OBJECT_OFFSETOF(ScopedArguments, m_storage); }
    static ptrdiff_t offsetOfOverrodeThingsInStorage() { return OBJECT_OFFSETOF(StorageHeader, overrodeThings) - sizeof(WriteBarrier<Unknown>); }
    static ptrdiff_t offsetOfTotalLengthInStorage() { return OBJECT_OFFSETOF(StorageHeader, totalLength) - sizeof(WriteBarrier<Unknown>); }
    static ptrdiff_t offsetOfTable() { return OBJECT_OFFSETOF(ScopedArguments, m_table); }
    static ptrdiff_t offsetOfScope() { return OBJECT_OFFSETOF(ScopedArguments, m_scope); }
    
    static size_t allocationSize(size_t inlineSize)
    {
        RELEASE_ASSERT(!inlineSize);
        return sizeof(ScopedArguments);
    }
    
    static size_t storageSize(Checked<size_t> capacity)
    {
        return (sizeof(WriteBarrier<Unknown>) * (capacity + static_cast<size_t>(1))).unsafeGet();
    }
    
    static size_t storageHeaderSize() { return sizeof(WriteBarrier<Unknown>); }
    
private:
    struct StorageHeader {
        unsigned totalLength;
        bool overrodeThings; // True if length, callee, and caller are fully materialized in the object.
    };
    
    WriteBarrier<Unknown>* overflowStorage() const
    {
        return m_storage.get().unpoisoned();
    }
    
    static StorageHeader& storageHeader(WriteBarrier<Unknown>* storage)
    {
        static_assert(sizeof(StorageHeader) <= sizeof(WriteBarrier<Unknown>), "StorageHeader needs to be no bigger than a JSValue");
        return *bitwise_cast<StorageHeader*>(storage - 1);
    }
    
    StorageHeader& storageHeader() const
    {
        return storageHeader(overflowStorage());
    }
    
    template<typename T>
    using PoisonedBarrier = PoisonedWriteBarrier<ScopedArgumentsPoison, T>;
    
    PoisonedBarrier<JSFunction> m_callee;
    PoisonedBarrier<ScopedArgumentsTable> m_table;
    PoisonedBarrier<JSLexicalEnvironment> m_scope;
    
    AuxiliaryBarrier<Poisoned<ScopedArgumentsPoison, WriteBarrier<Unknown>*>> m_storage;
};

} // namespace JSC
