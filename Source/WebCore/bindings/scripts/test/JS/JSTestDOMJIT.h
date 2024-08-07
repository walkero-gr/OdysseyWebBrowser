/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#pragma once

#include "JSNode.h"
#include "TestDOMJIT.h"
#include <JavaScriptCore/DOMJITGetterSetter.h>

namespace WebCore {

class JSTestDOMJIT : public JSNode {
public:
    using Base = JSNode;
    using DOMWrapped = TestDOMJIT;
    static JSTestDOMJIT* create(JSC::Structure* structure, JSDOMGlobalObject* globalObject, Ref<TestDOMJIT>&& impl)
    {
        JSTestDOMJIT* ptr = new (NotNull, JSC::allocateCell<JSTestDOMJIT>(globalObject->vm().heap)) JSTestDOMJIT(structure, *globalObject, WTFMove(impl));
        ptr->finishCreation(globalObject->vm());
        return ptr;
    }

    static JSC::JSObject* createPrototype(JSC::VM&, JSDOMGlobalObject&);
    static JSC::JSObject* prototype(JSC::VM&, JSDOMGlobalObject&);

    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::JSType(JSNodeType), StructureFlags), info());
    }

    static JSC::JSValue getConstructor(JSC::VM&, const JSC::JSGlobalObject*);
    TestDOMJIT& wrapped() const
    {
        return static_cast<TestDOMJIT&>(Base::wrapped());
    }
protected:
    JSTestDOMJIT(JSC::Structure*, JSDOMGlobalObject&, Ref<TestDOMJIT>&&);

    void finishCreation(JSC::VM&);
};


// DOM JIT Attributes

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITAnyAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITBooleanAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITByteAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITOctetAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITShortAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnsignedShortAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITLongAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnsignedLongAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITLongLongAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnsignedLongLongAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITFloatAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnrestrictedFloatAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITDoubleAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnrestrictedDoubleAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITDomStringAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITByteStringAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUsvStringAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITNodeAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITBooleanNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITByteNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITOctetNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITShortNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnsignedShortNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITLongNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnsignedLongNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITLongLongNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnsignedLongLongNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITFloatNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnrestrictedFloatNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITDoubleNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUnrestrictedDoubleNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITDomStringNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITByteStringNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITUsvStringNullableAttrAttribute();
#endif

#if ENABLE(JIT)
Ref<JSC::DOMJIT::CallDOMGetterSnippet> compileTestDOMJITNodeNullableAttrAttribute();
#endif

template<> struct JSDOMWrapperConverterTraits<TestDOMJIT> {
    using WrapperClass = JSTestDOMJIT;
    using ToWrappedReturnType = TestDOMJIT*;
};

} // namespace WebCore
