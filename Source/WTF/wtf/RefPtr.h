/*
 *  Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2013 Apple Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

// RefPtr and PassRefPtr are documented at http://webkit.org/coding/RefPtr.html

#ifndef WTF_RefPtr_h
#define WTF_RefPtr_h

#include <algorithm>
#include <utility>
#include <wtf/FastMalloc.h>
#include <wtf/GetPtr.h>
#include <wtf/PassRefPtr.h>

namespace WTF {

enum HashTableDeletedValueType { HashTableDeletedValue };

template<typename T> class RefPtr {
    WTF_MAKE_FAST_ALLOCATED;
public:
    typedef T ValueType;
    typedef ValueType* PtrType;

    ALWAYS_INLINE RefPtr() : m_ptr(nullptr) { }
    ALWAYS_INLINE RefPtr(T* ptr) : m_ptr(ptr) { refIfNotNull(ptr); }
    ALWAYS_INLINE RefPtr(const RefPtr& o) : m_ptr(o.m_ptr) { refIfNotNull(m_ptr); }
    template<typename U> RefPtr(const RefPtr<U>& o) : m_ptr(o.get()) { refIfNotNull(m_ptr); }

    ALWAYS_INLINE RefPtr(RefPtr&& o) : m_ptr(o.release().leakRef()) { }
    template<typename U> RefPtr(RefPtr<U>&& o) : m_ptr(o.release().leakRef()) { }

    // See comments in PassRefPtr.h for an explanation of why this takes a const reference.
    template<typename U> RefPtr(const PassRefPtr<U>&);

    template<typename U> RefPtr(Ref<U>&&);

    // Hash table deleted values, which are only constructed and never copied or destroyed.
    RefPtr(HashTableDeletedValueType) : m_ptr(hashTableDeletedValue()) { }
    bool isHashTableDeletedValue() const { return m_ptr == hashTableDeletedValue(); }

    ALWAYS_INLINE ~RefPtr() { derefIfNotNull(std::exchange(m_ptr, nullptr)); }

    T* get() const { return m_ptr; }
    
    void clear();
    PassRefPtr<T> release() { PassRefPtr<T> tmp = adoptRef(m_ptr); m_ptr = nullptr; return tmp; }
    Ref<T> releaseNonNull() { ASSERT(m_ptr); Ref<T> tmp(adoptRef(*m_ptr)); m_ptr = nullptr; return tmp; }

    T* leakRef() WARN_UNUSED_RETURN;

    T& operator*() const { ASSERT(m_ptr); return *m_ptr; }
    ALWAYS_INLINE T* operator->() const { return m_ptr; }
    
    bool operator!() const { return !m_ptr; }

    // This conversion operator allows implicit conversion to bool but not to other integer types.
    typedef T* (RefPtr::*UnspecifiedBoolType);
    operator UnspecifiedBoolType() const { return m_ptr ? &RefPtr::m_ptr : nullptr; }
    
    RefPtr& operator=(const RefPtr&);
    RefPtr& operator=(T*);
    RefPtr& operator=(const PassRefPtr<T>&);
    template<typename U> RefPtr& operator=(const RefPtr<U>&);
    template<typename U> RefPtr& operator=(const PassRefPtr<U>&);
    RefPtr& operator=(RefPtr&&);
    template<typename U> RefPtr& operator=(RefPtr<U>&&);
    template<typename U> RefPtr& operator=(Ref<U>&&);

    void swap(RefPtr&);

    static T* hashTableDeletedValue() { return reinterpret_cast<T*>(-1); }

#if COMPILER_SUPPORTS(CXX_REFERENCE_QUALIFIED_FUNCTIONS)
    RefPtr copyRef() && = delete;
    RefPtr copyRef() const & WARN_UNUSED_RETURN { return RefPtr(m_ptr); }
#else
    RefPtr copyRef() const WARN_UNUSED_RETURN { return RefPtr(m_ptr); }
#endif

private:
    T* m_ptr;
};

template<typename T> template<typename U> inline RefPtr<T>::RefPtr(const PassRefPtr<U>& o)
    : m_ptr(o.leakRef())
{
}

template<typename T> template<typename U> inline RefPtr<T>::RefPtr(Ref<U>&& reference)
    : m_ptr(&reference.leakRef())
{
}

template<typename T> inline void RefPtr<T>::clear()
{
    derefIfNotNull(std::exchange(m_ptr, nullptr));
}

template<typename T>
inline T* RefPtr<T>::leakRef()
{
    return std::exchange(m_ptr, nullptr);
}

template<typename T> inline RefPtr<T>& RefPtr<T>::operator=(const RefPtr& o)
{
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<typename T> template<typename U> inline RefPtr<T>& RefPtr<T>::operator=(const RefPtr<U>& o)
{
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<typename T> inline RefPtr<T>& RefPtr<T>::operator=(T* optr)
{
    RefPtr ptr = optr;
    swap(ptr);
    return *this;
}

template<typename T> inline RefPtr<T>& RefPtr<T>::operator=(const PassRefPtr<T>& o)
{
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<typename T> template<typename U> inline RefPtr<T>& RefPtr<T>::operator=(const PassRefPtr<U>& o)
{
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<typename T> inline RefPtr<T>& RefPtr<T>::operator=(RefPtr&& o)
{
    RefPtr ptr = WTF::move(o);
    swap(ptr);
    return *this;
}

template<typename T> template<typename U> inline RefPtr<T>& RefPtr<T>::operator=(RefPtr<U>&& o)
{
    RefPtr ptr = WTF::move(o);
    swap(ptr);
    return *this;
}

template<typename T> template<typename U> inline RefPtr<T>& RefPtr<T>::operator=(Ref<U>&& reference)
{
    RefPtr ptr = WTF::move(reference);
    swap(ptr);
    return *this;
}

template<class T> inline void RefPtr<T>::swap(RefPtr& o)
{
    std::swap(m_ptr, o.m_ptr);
}

template<class T> inline void swap(RefPtr<T>& a, RefPtr<T>& b)
{
    a.swap(b);
}

template<typename T, typename U> inline bool operator==(const RefPtr<T>& a, const RefPtr<U>& b)
{ 
    return a.get() == b.get(); 
}

template<typename T, typename U> inline bool operator==(const RefPtr<T>& a, U* b)
{ 
    return a.get() == b; 
}

template<typename T, typename U> inline bool operator==(T* a, const RefPtr<U>& b) 
{
    return a == b.get(); 
}

template<typename T, typename U> inline bool operator!=(const RefPtr<T>& a, const RefPtr<U>& b)
{ 
    return a.get() != b.get(); 
}

template<typename T, typename U> inline bool operator!=(const RefPtr<T>& a, U* b)
{
    return a.get() != b; 
}

template<typename T, typename U> inline bool operator!=(T* a, const RefPtr<U>& b)
{ 
    return a != b.get(); 
}

template<typename T, typename U> inline RefPtr<T> static_pointer_cast(const RefPtr<U>& p)
{ 
    return RefPtr<T>(static_cast<T*>(p.get())); 
}

template <typename T> struct IsSmartPtr<RefPtr<T>> {
    static const bool value = true;
};

} // namespace WTF

using WTF::RefPtr;
using WTF::static_pointer_cast;

#endif // WTF_RefPtr_h
