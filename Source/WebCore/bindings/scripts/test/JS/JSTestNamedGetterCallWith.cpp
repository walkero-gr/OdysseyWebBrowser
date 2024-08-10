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

#include "config.h"
#include "JSTestNamedGetterCallWith.h"

#include "JSDOMAbstractOperations.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMWrapperCache.h"
#include "ScriptExecutionContext.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapSnapshotBuilder.h>
#include <JavaScriptCore/JSCInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Attributes

JSC::EncodedJSValue jsTestNamedGetterCallWithConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestNamedGetterCallWithConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);

class JSTestNamedGetterCallWithPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestNamedGetterCallWithPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestNamedGetterCallWithPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestNamedGetterCallWithPrototype>(vm.heap)) JSTestNamedGetterCallWithPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestNamedGetterCallWithPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

using JSTestNamedGetterCallWithConstructor = JSDOMConstructorNotConstructable<JSTestNamedGetterCallWith>;

template<> JSValue JSTestNamedGetterCallWithConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestNamedGetterCallWithConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestNamedGetterCallWith::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(&vm, String("TestNamedGetterCallWith"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestNamedGetterCallWithConstructor::s_info = { "TestNamedGetterCallWith", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedGetterCallWithConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestNamedGetterCallWithPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestNamedGetterCallWithConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestNamedGetterCallWithConstructor) } },
};

const ClassInfo JSTestNamedGetterCallWithPrototype::s_info = { "TestNamedGetterCallWithPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedGetterCallWithPrototype) };

void JSTestNamedGetterCallWithPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestNamedGetterCallWith::info(), JSTestNamedGetterCallWithPrototypeTableValues, *this);
}

const ClassInfo JSTestNamedGetterCallWith::s_info = { "TestNamedGetterCallWith", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedGetterCallWith) };

JSTestNamedGetterCallWith::JSTestNamedGetterCallWith(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestNamedGetterCallWith>&& impl)
    : JSDOMWrapper<TestNamedGetterCallWith>(structure, globalObject, WTFMove(impl))
{
}

void JSTestNamedGetterCallWith::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

}

JSObject* JSTestNamedGetterCallWith::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestNamedGetterCallWithPrototype::create(vm, &globalObject, JSTestNamedGetterCallWithPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestNamedGetterCallWith::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestNamedGetterCallWith>(vm, globalObject);
}

JSValue JSTestNamedGetterCallWith::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestNamedGetterCallWithConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestNamedGetterCallWith::destroy(JSC::JSCell* cell)
{
    JSTestNamedGetterCallWith* thisObject = static_cast<JSTestNamedGetterCallWith*>(cell);
    thisObject->JSTestNamedGetterCallWith::~JSTestNamedGetterCallWith();
}

bool JSTestNamedGetterCallWith::getOwnPropertySlot(JSObject* object, ExecState* state, PropertyName propertyName, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedGetterCallWith*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> Optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(worldForDOMObject(thisObject), propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return WTF::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::No>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly), value);
        return true;
    }
    return JSObject::getOwnPropertySlot(object, state, propertyName, slot);
}

bool JSTestNamedGetterCallWith::getOwnPropertySlotByIndex(JSObject* object, ExecState* state, unsigned index, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedGetterCallWith*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    auto propertyName = Identifier::from(state, index);
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> Optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(worldForDOMObject(thisObject), propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return WTF::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::No>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly), value);
        return true;
    }
    return JSObject::getOwnPropertySlotByIndex(object, state, index, slot);
}

void JSTestNamedGetterCallWith::getOwnPropertyNames(JSObject* object, ExecState* state, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    auto* thisObject = jsCast<JSTestNamedGetterCallWith*>(object);
    ASSERT_GC_OBJECT_INHERITS(object, info());
    for (auto& propertyName : thisObject->wrapped().supportedPropertyNames())
        propertyNames.add(Identifier::fromString(state, propertyName));
    JSObject::getOwnPropertyNames(object, state, propertyNames, mode);
}

EncodedJSValue jsTestNamedGetterCallWithConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedGetterCallWithPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(state, throwScope);
    return JSValue::encode(JSTestNamedGetterCallWith::getConstructor(state->vm(), prototype->globalObject()));
}

bool setJSTestNamedGetterCallWithConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedGetterCallWithPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(state, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

void JSTestNamedGetterCallWith::heapSnapshot(JSCell* cell, HeapSnapshotBuilder& builder)
{
    auto* thisObject = jsCast<JSTestNamedGetterCallWith*>(cell);
    builder.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        builder.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::heapSnapshot(cell, builder);
}

bool JSTestNamedGetterCallWithOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestNamedGetterCallWithOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestNamedGetterCallWith = static_cast<JSTestNamedGetterCallWith*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestNamedGetterCallWith->wrapped(), jsTestNamedGetterCallWith);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestNamedGetterCallWith@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore23TestNamedGetterCallWithE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject* globalObject, Ref<TestNamedGetterCallWith>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl.ptr()));
#if PLATFORM(WIN)
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(__identifier("??_7TestNamedGetterCallWith@WebCore@@6B@"));
#else
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(&_ZTVN7WebCore23TestNamedGetterCallWithE[2]);
#endif

    // If this fails TestNamedGetterCallWith does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestNamedGetterCallWith>::value, "TestNamedGetterCallWith is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestNamedGetterCallWith has subclasses. If TestNamedGetterCallWith has subclasses that get passed
    // to toJS() we currently require TestNamedGetterCallWith you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestNamedGetterCallWith>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::ExecState* state, JSDOMGlobalObject* globalObject, TestNamedGetterCallWith& impl)
{
    return wrap(state, globalObject, impl);
}

TestNamedGetterCallWith* JSTestNamedGetterCallWith::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestNamedGetterCallWith*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
