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
#include "JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins.h"

#include "JSDOMAbstractOperations.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMOperation.h"
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

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsInstanceFunctionUnforgeableOperation(JSC::ExecState*);

// Attributes

JSC::EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsUnforgeableAttribute(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);

class JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype>(vm.heap)) JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

using JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor = JSDOMConstructorNotConstructable<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>;

/* Hash table */

static const struct CompactHashIndex JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsTableIndex[4] = {
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { 0, -1 },
};


static const HashTableValue JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsTableValues[] =
{
    { "unforgeableAttribute", static_cast<unsigned>(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsUnforgeableAttribute), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "unforgeableOperation", static_cast<unsigned>(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsInstanceFunctionUnforgeableOperation), (intptr_t) (0) } },
};

static const HashTable JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsTable = { 2, 3, true, JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::info(), JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsTableValues, JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsTableIndex };
template<> JSValue JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(&vm, String("TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor::s_info = { "TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor) } },
};

const ClassInfo JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype::s_info = { "TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype) };

void JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::info(), JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototypeTableValues, *this);
}

const ClassInfo JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::s_info = { "TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins", &Base::s_info, &JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsTable, nullptr, CREATE_METHOD_TABLE(JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins) };

JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>&& impl)
    : JSDOMWrapper<TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>(structure, globalObject, WTFMove(impl))
{
}

void JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

}

JSObject* JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype::create(vm, &globalObject, JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>(vm, globalObject);
}

JSValue JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::destroy(JSC::JSCell* cell)
{
    JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins* thisObject = static_cast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(cell);
    thisObject->JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::~JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins();
}

bool JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::getOwnPropertySlot(JSObject* object, ExecState* state, PropertyName propertyName, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> Optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return WTF::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::Yes>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(0), value);
        return true;
    }
    return JSObject::getOwnPropertySlot(object, state, propertyName, slot);
}

bool JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::getOwnPropertySlotByIndex(JSObject* object, ExecState* state, unsigned index, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    auto propertyName = Identifier::from(state, index);
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> Optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return WTF::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::Yes>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(0), value);
        return true;
    }
    return JSObject::getOwnPropertySlotByIndex(object, state, index, slot);
}

void JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::getOwnPropertyNames(JSObject* object, ExecState* state, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(object);
    ASSERT_GC_OBJECT_INHERITS(object, info());
    for (auto& propertyName : thisObject->wrapped().supportedPropertyNames())
        propertyNames.add(Identifier::fromString(state, propertyName));
    JSObject::getOwnPropertyNames(object, state, propertyNames, mode);
}

bool JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::put(JSCell* cell, ExecState* state, PropertyName propertyName, JSValue value, PutPropertySlot& putPropertySlot)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (!propertyName.isSymbol()) {
        auto throwScope = DECLARE_THROW_SCOPE(state->vm());
        auto nativeValue = convert<IDLDOMString>(*state, value);
        RETURN_IF_EXCEPTION(throwScope, true);
        thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue));
        return true;
    }

    return JSObject::put(thisObject, state, propertyName, value, putPropertySlot);
}

bool JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::putByIndex(JSCell* cell, ExecState* state, unsigned index, JSValue value, bool)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    auto propertyName = Identifier::from(state, index);
    auto throwScope = DECLARE_THROW_SCOPE(state->vm());
    auto nativeValue = convert<IDLDOMString>(*state, value);
    RETURN_IF_EXCEPTION(throwScope, true);
    thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue));
    return true;
}

bool JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::defineOwnProperty(JSObject* object, ExecState* state, PropertyName propertyName, const PropertyDescriptor& propertyDescriptor, bool shouldThrow)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (!propertyName.isSymbol()) {
static bool isUnforgeablePropertyName(PropertyName propertyName)
{
    return propertyName == "unforgeableAttribute" || propertyName == "unforgeableOperation";
}

        if (!isUnforgeablePropertyName(propertyName)) {
            if (!propertyDescriptor.isDataDescriptor())
                return false;
            auto throwScope = DECLARE_THROW_SCOPE(state->vm());
            auto nativeValue = convert<IDLDOMString>(*state, propertyDescriptor.value());
            RETURN_IF_EXCEPTION(throwScope, true);
            thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue));
            return true;
        }
    }

    PropertyDescriptor newPropertyDescriptor = propertyDescriptor;
    newPropertyDescriptor.setConfigurable(true);
    return JSObject::defineOwnProperty(object, state, propertyName, newPropertyDescriptor, shouldThrow);
}

template<> inline JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins* IDLAttribute<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>::cast(ExecState& state, EncodedJSValue thisValue)
{
    return jsDynamicCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(state.vm(), JSValue::decode(thisValue));
}

template<> inline JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins* IDLOperation<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>::cast(ExecState& state)
{
    return jsDynamicCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(state.vm(), state.thisValue());
}

EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(state, throwScope);
    return JSValue::encode(JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::getConstructor(state->vm(), prototype->globalObject()));
}

bool setJSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(state, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

static inline JSValue jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsUnforgeableAttributeGetter(ExecState& state, JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins& thisObject, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(state);
    auto& impl = thisObject.wrapped();
    JSValue result = toJS<IDLDOMString>(state, throwScope, impl.unforgeableAttribute());
    return result;
}

EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsUnforgeableAttribute(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    return IDLAttribute<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>::get<jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsUnforgeableAttributeGetter, CastedThisErrorBehavior::Assert>(*state, thisValue, "unforgeableAttribute");
}

static inline JSC::EncodedJSValue jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsInstanceFunctionUnforgeableOperationBody(JSC::ExecState* state, typename IDLOperation<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(state);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    impl.unforgeableOperation();
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsInstanceFunctionUnforgeableOperation(ExecState* state)
{
    return IDLOperation<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>::call<jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsInstanceFunctionUnforgeableOperationBody>(*state, "unforgeableOperation");
}

void JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::heapSnapshot(JSCell* cell, HeapSnapshotBuilder& builder)
{
    auto* thisObject = jsCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(cell);
    builder.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        builder.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::heapSnapshot(cell, builder);
}

bool JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins = static_cast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins->wrapped(), jsTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore58TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject* globalObject, Ref<TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl.ptr()));
#if PLATFORM(WIN)
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(__identifier("??_7TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins@WebCore@@6B@"));
#else
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(&_ZTVN7WebCore58TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltinsE[2]);
#endif

    // If this fails TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>::value, "TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins has subclasses. If TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins has subclasses that get passed
    // to toJS() we currently require TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::ExecState* state, JSDOMGlobalObject* globalObject, TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins& impl)
{
    return wrap(state, globalObject, impl);
}

TestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins* JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestNamedSetterWithUnforgablePropertiesAndOverrideBuiltins*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
