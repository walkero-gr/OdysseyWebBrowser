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
#include "JSTestNamedSetterWithUnforgableProperties.h"

#include "JSDOMAbstractOperations.h"
#include "JSDOMAttribute.h"
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

JSC::EncodedJSValue JSC_HOST_CALL jsTestNamedSetterWithUnforgablePropertiesInstanceFunctionUnforgeableOperation(JSC::ExecState*);

// Attributes

JSC::EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestNamedSetterWithUnforgablePropertiesConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesUnforgeableAttribute(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);

class JSTestNamedSetterWithUnforgablePropertiesPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestNamedSetterWithUnforgablePropertiesPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestNamedSetterWithUnforgablePropertiesPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestNamedSetterWithUnforgablePropertiesPrototype>(vm.heap)) JSTestNamedSetterWithUnforgablePropertiesPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestNamedSetterWithUnforgablePropertiesPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

using JSTestNamedSetterWithUnforgablePropertiesConstructor = JSDOMConstructorNotConstructable<JSTestNamedSetterWithUnforgableProperties>;

/* Hash table */

static const struct CompactHashIndex JSTestNamedSetterWithUnforgablePropertiesTableIndex[4] = {
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { 0, -1 },
};


static const HashTableValue JSTestNamedSetterWithUnforgablePropertiesTableValues[] =
{
    { "unforgeableAttribute", static_cast<unsigned>(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestNamedSetterWithUnforgablePropertiesUnforgeableAttribute), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "unforgeableOperation", static_cast<unsigned>(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestNamedSetterWithUnforgablePropertiesInstanceFunctionUnforgeableOperation), (intptr_t) (0) } },
};

static const HashTable JSTestNamedSetterWithUnforgablePropertiesTable = { 2, 3, true, JSTestNamedSetterWithUnforgableProperties::info(), JSTestNamedSetterWithUnforgablePropertiesTableValues, JSTestNamedSetterWithUnforgablePropertiesTableIndex };
template<> JSValue JSTestNamedSetterWithUnforgablePropertiesConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestNamedSetterWithUnforgablePropertiesConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestNamedSetterWithUnforgableProperties::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(&vm, String("TestNamedSetterWithUnforgableProperties"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestNamedSetterWithUnforgablePropertiesConstructor::s_info = { "TestNamedSetterWithUnforgableProperties", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedSetterWithUnforgablePropertiesConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestNamedSetterWithUnforgablePropertiesPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestNamedSetterWithUnforgablePropertiesConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestNamedSetterWithUnforgablePropertiesConstructor) } },
};

const ClassInfo JSTestNamedSetterWithUnforgablePropertiesPrototype::s_info = { "TestNamedSetterWithUnforgablePropertiesPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedSetterWithUnforgablePropertiesPrototype) };

void JSTestNamedSetterWithUnforgablePropertiesPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestNamedSetterWithUnforgableProperties::info(), JSTestNamedSetterWithUnforgablePropertiesPrototypeTableValues, *this);
}

const ClassInfo JSTestNamedSetterWithUnforgableProperties::s_info = { "TestNamedSetterWithUnforgableProperties", &Base::s_info, &JSTestNamedSetterWithUnforgablePropertiesTable, nullptr, CREATE_METHOD_TABLE(JSTestNamedSetterWithUnforgableProperties) };

JSTestNamedSetterWithUnforgableProperties::JSTestNamedSetterWithUnforgableProperties(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestNamedSetterWithUnforgableProperties>&& impl)
    : JSDOMWrapper<TestNamedSetterWithUnforgableProperties>(structure, globalObject, WTFMove(impl))
{
}

void JSTestNamedSetterWithUnforgableProperties::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

}

JSObject* JSTestNamedSetterWithUnforgableProperties::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestNamedSetterWithUnforgablePropertiesPrototype::create(vm, &globalObject, JSTestNamedSetterWithUnforgablePropertiesPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestNamedSetterWithUnforgableProperties::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestNamedSetterWithUnforgableProperties>(vm, globalObject);
}

JSValue JSTestNamedSetterWithUnforgableProperties::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestNamedSetterWithUnforgablePropertiesConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestNamedSetterWithUnforgableProperties::destroy(JSC::JSCell* cell)
{
    JSTestNamedSetterWithUnforgableProperties* thisObject = static_cast<JSTestNamedSetterWithUnforgableProperties*>(cell);
    thisObject->JSTestNamedSetterWithUnforgableProperties::~JSTestNamedSetterWithUnforgableProperties();
}

bool JSTestNamedSetterWithUnforgableProperties::getOwnPropertySlot(JSObject* object, ExecState* state, PropertyName propertyName, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgableProperties*>(object);
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
        slot.setValue(thisObject, static_cast<unsigned>(0), value);
        return true;
    }
    return JSObject::getOwnPropertySlot(object, state, propertyName, slot);
}

bool JSTestNamedSetterWithUnforgableProperties::getOwnPropertySlotByIndex(JSObject* object, ExecState* state, unsigned index, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgableProperties*>(object);
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
        slot.setValue(thisObject, static_cast<unsigned>(0), value);
        return true;
    }
    return JSObject::getOwnPropertySlotByIndex(object, state, index, slot);
}

void JSTestNamedSetterWithUnforgableProperties::getOwnPropertyNames(JSObject* object, ExecState* state, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgableProperties*>(object);
    ASSERT_GC_OBJECT_INHERITS(object, info());
    for (auto& propertyName : thisObject->wrapped().supportedPropertyNames())
        propertyNames.add(Identifier::fromString(state, propertyName));
    JSObject::getOwnPropertyNames(object, state, propertyNames, mode);
}

bool JSTestNamedSetterWithUnforgableProperties::put(JSCell* cell, ExecState* state, PropertyName propertyName, JSValue value, PutPropertySlot& putPropertySlot)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgableProperties*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (!propertyName.isSymbol()) {
        PropertySlot slot { thisObject, PropertySlot::InternalMethodType::VMInquiry };
        JSValue prototype = thisObject->getPrototypeDirect(state->vm());
        if (!(prototype.isObject() && asObject(prototype)->getPropertySlot(state, propertyName, slot))) {
            auto throwScope = DECLARE_THROW_SCOPE(state->vm());
            auto nativeValue = convert<IDLDOMString>(*state, value);
            RETURN_IF_EXCEPTION(throwScope, true);
            thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue));
            return true;
        }
    }

    return JSObject::put(thisObject, state, propertyName, value, putPropertySlot);
}

bool JSTestNamedSetterWithUnforgableProperties::putByIndex(JSCell* cell, ExecState* state, unsigned index, JSValue value, bool shouldThrow)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgableProperties*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    auto propertyName = Identifier::from(state, index);
    PropertySlot slot { thisObject, PropertySlot::InternalMethodType::VMInquiry };
    JSValue prototype = thisObject->getPrototypeDirect(state->vm());
    if (!(prototype.isObject() && asObject(prototype)->getPropertySlot(state, propertyName, slot))) {
        auto throwScope = DECLARE_THROW_SCOPE(state->vm());
        auto nativeValue = convert<IDLDOMString>(*state, value);
        RETURN_IF_EXCEPTION(throwScope, true);
        thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue));
        return true;
    }

    return JSObject::putByIndex(cell, state, index, value, shouldThrow);
}

bool JSTestNamedSetterWithUnforgableProperties::defineOwnProperty(JSObject* object, ExecState* state, PropertyName propertyName, const PropertyDescriptor& propertyDescriptor, bool shouldThrow)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgableProperties*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (!propertyName.isSymbol()) {
static bool isUnforgeablePropertyName(PropertyName propertyName)
{
    return propertyName == "unforgeableAttribute" || propertyName == "unforgeableOperation";
}

        if (!isUnforgeablePropertyName(propertyName)) {
            PropertySlot slot { thisObject, PropertySlot::InternalMethodType::VMInquiry };
            if (!JSObject::getOwnPropertySlot(thisObject, state, propertyName, slot)) {
                if (!propertyDescriptor.isDataDescriptor())
                    return false;
                auto throwScope = DECLARE_THROW_SCOPE(state->vm());
                auto nativeValue = convert<IDLDOMString>(*state, propertyDescriptor.value());
                RETURN_IF_EXCEPTION(throwScope, true);
                thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue));
                return true;
            }
        }
    }

    PropertyDescriptor newPropertyDescriptor = propertyDescriptor;
    newPropertyDescriptor.setConfigurable(true);
    return JSObject::defineOwnProperty(object, state, propertyName, newPropertyDescriptor, shouldThrow);
}

template<> inline JSTestNamedSetterWithUnforgableProperties* IDLAttribute<JSTestNamedSetterWithUnforgableProperties>::cast(ExecState& state, EncodedJSValue thisValue)
{
    return jsDynamicCast<JSTestNamedSetterWithUnforgableProperties*>(state.vm(), JSValue::decode(thisValue));
}

template<> inline JSTestNamedSetterWithUnforgableProperties* IDLOperation<JSTestNamedSetterWithUnforgableProperties>::cast(ExecState& state)
{
    return jsDynamicCast<JSTestNamedSetterWithUnforgableProperties*>(state.vm(), state.thisValue());
}

EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedSetterWithUnforgablePropertiesPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(state, throwScope);
    return JSValue::encode(JSTestNamedSetterWithUnforgableProperties::getConstructor(state->vm(), prototype->globalObject()));
}

bool setJSTestNamedSetterWithUnforgablePropertiesConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedSetterWithUnforgablePropertiesPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(state, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

static inline JSValue jsTestNamedSetterWithUnforgablePropertiesUnforgeableAttributeGetter(ExecState& state, JSTestNamedSetterWithUnforgableProperties& thisObject, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(state);
    auto& impl = thisObject.wrapped();
    JSValue result = toJS<IDLDOMString>(state, throwScope, impl.unforgeableAttribute());
    return result;
}

EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesUnforgeableAttribute(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    return IDLAttribute<JSTestNamedSetterWithUnforgableProperties>::get<jsTestNamedSetterWithUnforgablePropertiesUnforgeableAttributeGetter, CastedThisErrorBehavior::Assert>(*state, thisValue, "unforgeableAttribute");
}

static inline JSC::EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesInstanceFunctionUnforgeableOperationBody(JSC::ExecState* state, typename IDLOperation<JSTestNamedSetterWithUnforgableProperties>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(state);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    impl.unforgeableOperation();
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestNamedSetterWithUnforgablePropertiesInstanceFunctionUnforgeableOperation(ExecState* state)
{
    return IDLOperation<JSTestNamedSetterWithUnforgableProperties>::call<jsTestNamedSetterWithUnforgablePropertiesInstanceFunctionUnforgeableOperationBody>(*state, "unforgeableOperation");
}

bool JSTestNamedSetterWithUnforgablePropertiesOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestNamedSetterWithUnforgablePropertiesOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestNamedSetterWithUnforgableProperties = static_cast<JSTestNamedSetterWithUnforgableProperties*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestNamedSetterWithUnforgableProperties->wrapped(), jsTestNamedSetterWithUnforgableProperties);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestNamedSetterWithUnforgableProperties@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore39TestNamedSetterWithUnforgablePropertiesE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject* globalObject, Ref<TestNamedSetterWithUnforgableProperties>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl.ptr()));
#if PLATFORM(WIN)
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(__identifier("??_7TestNamedSetterWithUnforgableProperties@WebCore@@6B@"));
#else
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(&_ZTVN7WebCore39TestNamedSetterWithUnforgablePropertiesE[2]);
#endif

    // If this fails TestNamedSetterWithUnforgableProperties does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestNamedSetterWithUnforgableProperties>::value, "TestNamedSetterWithUnforgableProperties is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestNamedSetterWithUnforgableProperties has subclasses. If TestNamedSetterWithUnforgableProperties has subclasses that get passed
    // to toJS() we currently require TestNamedSetterWithUnforgableProperties you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestNamedSetterWithUnforgableProperties>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::ExecState* state, JSDOMGlobalObject* globalObject, TestNamedSetterWithUnforgableProperties& impl)
{
    return wrap(state, globalObject, impl);
}

TestNamedSetterWithUnforgableProperties* JSTestNamedSetterWithUnforgableProperties::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestNamedSetterWithUnforgableProperties*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
