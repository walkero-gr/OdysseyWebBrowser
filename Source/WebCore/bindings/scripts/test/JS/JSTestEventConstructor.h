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

#include "JSDOMConvertDictionary.h"
#include "JSDOMWrapper.h"
#include "JSEvent.h"
#include "TestEventConstructor.h"

namespace WebCore {

class JSTestEventConstructor : public JSEvent {
public:
    using Base = JSEvent;
    using DOMWrapped = TestEventConstructor;
    static JSTestEventConstructor* create(JSC::Structure* structure, JSDOMGlobalObject* globalObject, Ref<TestEventConstructor>&& impl)
    {
        JSTestEventConstructor* ptr = new (NotNull, JSC::allocateCell<JSTestEventConstructor>(globalObject->vm().heap)) JSTestEventConstructor(structure, *globalObject, WTFMove(impl));
        ptr->finishCreation(globalObject->vm());
        return ptr;
    }

    static JSC::JSObject* createPrototype(JSC::VM&, JSDOMGlobalObject&);
    static JSC::JSObject* prototype(JSC::VM&, JSDOMGlobalObject&);

    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::JSType(JSEventType), StructureFlags), info());
    }

    static JSC::JSValue getConstructor(JSC::VM&, const JSC::JSGlobalObject*);
    TestEventConstructor& wrapped() const
    {
        return static_cast<TestEventConstructor&>(Base::wrapped());
    }
protected:
    JSTestEventConstructor(JSC::Structure*, JSDOMGlobalObject&, Ref<TestEventConstructor>&&);

    void finishCreation(JSC::VM&);
};

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, TestEventConstructor&);
inline JSC::JSValue toJS(JSC::ExecState* state, JSDOMGlobalObject* globalObject, TestEventConstructor* impl) { return impl ? toJS(state, globalObject, *impl) : JSC::jsNull(); }
JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject*, Ref<TestEventConstructor>&&);
inline JSC::JSValue toJSNewlyCreated(JSC::ExecState* state, JSDOMGlobalObject* globalObject, RefPtr<TestEventConstructor>&& impl) { return impl ? toJSNewlyCreated(state, globalObject, impl.releaseNonNull()) : JSC::jsNull(); }

template<> struct JSDOMWrapperConverterTraits<TestEventConstructor> {
    using WrapperClass = JSTestEventConstructor;
    using ToWrappedReturnType = TestEventConstructor*;
};
template<> TestEventConstructor::Init convertDictionary<TestEventConstructor::Init>(JSC::ExecState&, JSC::JSValue);


} // namespace WebCore
