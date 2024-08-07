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
#include "JSTestNamedDeleterWithIdentifier.h"

#include "JSDOMAbstractOperations.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/JSCInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>


namespace WebCore {
using namespace JSC;

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsTestNamedDeleterWithIdentifierPrototypeFunctionNamedDeleter(JSC::ExecState*);

// Attributes

JSC::EncodedJSValue jsTestNamedDeleterWithIdentifierConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestNamedDeleterWithIdentifierConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);

class JSTestNamedDeleterWithIdentifierPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestNamedDeleterWithIdentifierPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestNamedDeleterWithIdentifierPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestNamedDeleterWithIdentifierPrototype>(vm.heap)) JSTestNamedDeleterWithIdentifierPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestNamedDeleterWithIdentifierPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

using JSTestNamedDeleterWithIdentifierConstructor = JSDOMConstructorNotConstructable<JSTestNamedDeleterWithIdentifier>;

template<> JSValue JSTestNamedDeleterWithIdentifierConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestNamedDeleterWithIdentifierConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestNamedDeleterWithIdentifier::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(&vm, String(ASCIILiteral("TestNamedDeleterWithIdentifier"))), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestNamedDeleterWithIdentifierConstructor::s_info = { "TestNamedDeleterWithIdentifier", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedDeleterWithIdentifierConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestNamedDeleterWithIdentifierPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestNamedDeleterWithIdentifierConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestNamedDeleterWithIdentifierConstructor) } },
    { "namedDeleter", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<NativeFunction>(jsTestNamedDeleterWithIdentifierPrototypeFunctionNamedDeleter), (intptr_t) (1) } },
};

const ClassInfo JSTestNamedDeleterWithIdentifierPrototype::s_info = { "TestNamedDeleterWithIdentifierPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedDeleterWithIdentifierPrototype) };

void JSTestNamedDeleterWithIdentifierPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestNamedDeleterWithIdentifier::info(), JSTestNamedDeleterWithIdentifierPrototypeTableValues, *this);
}

const ClassInfo JSTestNamedDeleterWithIdentifier::s_info = { "TestNamedDeleterWithIdentifier", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedDeleterWithIdentifier) };

JSTestNamedDeleterWithIdentifier::JSTestNamedDeleterWithIdentifier(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestNamedDeleterWithIdentifier>&& impl)
    : JSDOMWrapper<TestNamedDeleterWithIdentifier>(structure, globalObject, WTFMove(impl))
{
}

void JSTestNamedDeleterWithIdentifier::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

}

JSObject* JSTestNamedDeleterWithIdentifier::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestNamedDeleterWithIdentifierPrototype::create(vm, &globalObject, JSTestNamedDeleterWithIdentifierPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestNamedDeleterWithIdentifier::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestNamedDeleterWithIdentifier>(vm, globalObject);
}

JSValue JSTestNamedDeleterWithIdentifier::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestNamedDeleterWithIdentifierConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestNamedDeleterWithIdentifier::destroy(JSC::JSCell* cell)
{
    JSTestNamedDeleterWithIdentifier* thisObject = static_cast<JSTestNamedDeleterWithIdentifier*>(cell);
    thisObject->JSTestNamedDeleterWithIdentifier::~JSTestNamedDeleterWithIdentifier();
}

bool JSTestNamedDeleterWithIdentifier::getOwnPropertySlot(JSObject* object, ExecState* state, PropertyName propertyName, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedDeleterWithIdentifier*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> std::optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return std::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::No>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly), value);
        return true;
    }
    return JSObject::getOwnPropertySlot(object, state, propertyName, slot);
}

bool JSTestNamedDeleterWithIdentifier::getOwnPropertySlotByIndex(JSObject* object, ExecState* state, unsigned index, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedDeleterWithIdentifier*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    auto propertyName = Identifier::from(state, index);
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> std::optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return std::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::No>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly), value);
        return true;
    }
    return JSObject::getOwnPropertySlotByIndex(object, state, index, slot);
}

void JSTestNamedDeleterWithIdentifier::getOwnPropertyNames(JSObject* object, ExecState* state, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    auto* thisObject = jsCast<JSTestNamedDeleterWithIdentifier*>(object);
    ASSERT_GC_OBJECT_INHERITS(object, info());
    for (auto& propertyName : thisObject->wrapped().supportedPropertyNames())
        propertyNames.add(Identifier::fromString(state, propertyName));
    JSObject::getOwnPropertyNames(object, state, propertyNames, mode);
}

bool JSTestNamedDeleterWithIdentifier::deleteProperty(JSCell* cell, ExecState* state, PropertyName propertyName)
{
    auto& thisObject = *jsCast<JSTestNamedDeleterWithIdentifier*>(cell);
    auto& impl = thisObject.wrapped();
    if (isVisibleNamedProperty<OverrideBuiltins::No>(*state, thisObject, propertyName)) {
        impl.namedDeleter(propertyNameToString(propertyName));
        return true;
    }
    return JSObject::deleteProperty(cell, state, propertyName);
}

bool JSTestNamedDeleterWithIdentifier::deletePropertyByIndex(JSCell* cell, ExecState* state, unsigned index)
{
    auto& thisObject = *jsCast<JSTestNamedDeleterWithIdentifier*>(cell);
    auto& impl = thisObject.wrapped();
    auto propertyName = Identifier::from(state, index);
    if (isVisibleNamedProperty<OverrideBuiltins::No>(*state, thisObject, propertyName)) {
        impl.namedDeleter(propertyNameToString(propertyName));
        return true;
    }
    return JSObject::deletePropertyByIndex(cell, state, index);
}

template<> inline JSTestNamedDeleterWithIdentifier* IDLOperation<JSTestNamedDeleterWithIdentifier>::cast(ExecState& state)
{
    return jsDynamicDowncast<JSTestNamedDeleterWithIdentifier*>(state.vm(), state.thisValue());
}

EncodedJSValue jsTestNamedDeleterWithIdentifierConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicDowncast<JSTestNamedDeleterWithIdentifierPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(state, throwScope);
    return JSValue::encode(JSTestNamedDeleterWithIdentifier::getConstructor(state->vm(), prototype->globalObject()));
}

bool setJSTestNamedDeleterWithIdentifierConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicDowncast<JSTestNamedDeleterWithIdentifierPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(state, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

static inline JSC::EncodedJSValue jsTestNamedDeleterWithIdentifierPrototypeFunctionNamedDeleterBody(JSC::ExecState* state, typename IDLOperation<JSTestNamedDeleterWithIdentifier>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(state);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(state->argumentCount() < 1))
        return throwVMError(state, throwScope, createNotEnoughArgumentsError(state));
    auto name = convert<IDLDOMString>(*state, state->uncheckedArgument(0));
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    impl.namedDeleter(WTFMove(name));
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestNamedDeleterWithIdentifierPrototypeFunctionNamedDeleter(ExecState* state)
{
    return IDLOperation<JSTestNamedDeleterWithIdentifier>::call<jsTestNamedDeleterWithIdentifierPrototypeFunctionNamedDeleterBody>(*state, "namedDeleter");
}

bool JSTestNamedDeleterWithIdentifierOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestNamedDeleterWithIdentifierOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestNamedDeleterWithIdentifier = static_cast<JSTestNamedDeleterWithIdentifier*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestNamedDeleterWithIdentifier->wrapped(), jsTestNamedDeleterWithIdentifier);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestNamedDeleterWithIdentifier@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore30TestNamedDeleterWithIdentifierE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject* globalObject, Ref<TestNamedDeleterWithIdentifier>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl.ptr()));
#if PLATFORM(WIN)
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(__identifier("??_7TestNamedDeleterWithIdentifier@WebCore@@6B@"));
#else
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(&_ZTVN7WebCore30TestNamedDeleterWithIdentifierE[2]);
#endif

    // If this fails TestNamedDeleterWithIdentifier does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestNamedDeleterWithIdentifier>::value, "TestNamedDeleterWithIdentifier is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestNamedDeleterWithIdentifier has subclasses. If TestNamedDeleterWithIdentifier has subclasses that get passed
    // to toJS() we currently require TestNamedDeleterWithIdentifier you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestNamedDeleterWithIdentifier>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::ExecState* state, JSDOMGlobalObject* globalObject, TestNamedDeleterWithIdentifier& impl)
{
    return wrap(state, globalObject, impl);
}

TestNamedDeleterWithIdentifier* JSTestNamedDeleterWithIdentifier::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicDowncast<JSTestNamedDeleterWithIdentifier*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
