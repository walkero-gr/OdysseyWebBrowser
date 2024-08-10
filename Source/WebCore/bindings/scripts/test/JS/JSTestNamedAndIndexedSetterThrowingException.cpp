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
#include "JSTestNamedAndIndexedSetterThrowingException.h"

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
#include <JavaScriptCore/PropertyNameArray.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Attributes

JSC::EncodedJSValue jsTestNamedAndIndexedSetterThrowingExceptionConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestNamedAndIndexedSetterThrowingExceptionConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);

class JSTestNamedAndIndexedSetterThrowingExceptionPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestNamedAndIndexedSetterThrowingExceptionPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestNamedAndIndexedSetterThrowingExceptionPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestNamedAndIndexedSetterThrowingExceptionPrototype>(vm.heap)) JSTestNamedAndIndexedSetterThrowingExceptionPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestNamedAndIndexedSetterThrowingExceptionPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

using JSTestNamedAndIndexedSetterThrowingExceptionConstructor = JSDOMConstructorNotConstructable<JSTestNamedAndIndexedSetterThrowingException>;

template<> JSValue JSTestNamedAndIndexedSetterThrowingExceptionConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestNamedAndIndexedSetterThrowingExceptionConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestNamedAndIndexedSetterThrowingException::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(&vm, String("TestNamedAndIndexedSetterThrowingException"_s)), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestNamedAndIndexedSetterThrowingExceptionConstructor::s_info = { "TestNamedAndIndexedSetterThrowingException", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedAndIndexedSetterThrowingExceptionConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestNamedAndIndexedSetterThrowingExceptionPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestNamedAndIndexedSetterThrowingExceptionConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestNamedAndIndexedSetterThrowingExceptionConstructor) } },
};

const ClassInfo JSTestNamedAndIndexedSetterThrowingExceptionPrototype::s_info = { "TestNamedAndIndexedSetterThrowingExceptionPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedAndIndexedSetterThrowingExceptionPrototype) };

void JSTestNamedAndIndexedSetterThrowingExceptionPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestNamedAndIndexedSetterThrowingException::info(), JSTestNamedAndIndexedSetterThrowingExceptionPrototypeTableValues, *this);
}

const ClassInfo JSTestNamedAndIndexedSetterThrowingException::s_info = { "TestNamedAndIndexedSetterThrowingException", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestNamedAndIndexedSetterThrowingException) };

JSTestNamedAndIndexedSetterThrowingException::JSTestNamedAndIndexedSetterThrowingException(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestNamedAndIndexedSetterThrowingException>&& impl)
    : JSDOMWrapper<TestNamedAndIndexedSetterThrowingException>(structure, globalObject, WTFMove(impl))
{
}

void JSTestNamedAndIndexedSetterThrowingException::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

}

JSObject* JSTestNamedAndIndexedSetterThrowingException::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestNamedAndIndexedSetterThrowingExceptionPrototype::create(vm, &globalObject, JSTestNamedAndIndexedSetterThrowingExceptionPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestNamedAndIndexedSetterThrowingException::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestNamedAndIndexedSetterThrowingException>(vm, globalObject);
}

JSValue JSTestNamedAndIndexedSetterThrowingException::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestNamedAndIndexedSetterThrowingExceptionConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestNamedAndIndexedSetterThrowingException::destroy(JSC::JSCell* cell)
{
    JSTestNamedAndIndexedSetterThrowingException* thisObject = static_cast<JSTestNamedAndIndexedSetterThrowingException*>(cell);
    thisObject->JSTestNamedAndIndexedSetterThrowingException::~JSTestNamedAndIndexedSetterThrowingException();
}

bool JSTestNamedAndIndexedSetterThrowingException::getOwnPropertySlot(JSObject* object, ExecState* state, PropertyName propertyName, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedAndIndexedSetterThrowingException*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    if (auto index = parseIndex(propertyName)) {
        if (index.value() < thisObject->wrapped().length()) {
            auto value = toJS<IDLDOMString>(*state, thisObject->wrapped().item(index.value()));
            slot.setValue(thisObject, static_cast<unsigned>(0), value);
            return true;
        }
        return JSObject::getOwnPropertySlot(object, state, propertyName, slot);
    }
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> Optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return WTF::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::No>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(0), value);
        return true;
    }
    return JSObject::getOwnPropertySlot(object, state, propertyName, slot);
}

bool JSTestNamedAndIndexedSetterThrowingException::getOwnPropertySlotByIndex(JSObject* object, ExecState* state, unsigned index, PropertySlot& slot)
{
    auto* thisObject = jsCast<JSTestNamedAndIndexedSetterThrowingException*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    if (LIKELY(index <= MAX_ARRAY_INDEX)) {
        if (index < thisObject->wrapped().length()) {
            auto value = toJS<IDLDOMString>(*state, thisObject->wrapped().item(index));
            slot.setValue(thisObject, static_cast<unsigned>(0), value);
            return true;
        }
        return JSObject::getOwnPropertySlotByIndex(object, state, index, slot);
    }
    auto propertyName = Identifier::from(state, index);
    using GetterIDLType = IDLDOMString;
    auto getterFunctor = [] (auto& thisObject, auto propertyName) -> Optional<typename GetterIDLType::ImplementationType> {
        auto result = thisObject.wrapped().namedItem(propertyNameToAtomicString(propertyName));
        if (!GetterIDLType::isNullValue(result))
            return typename GetterIDLType::ImplementationType { GetterIDLType::extractValueFromNullable(result) };
        return WTF::nullopt;
    };
    if (auto namedProperty = accessVisibleNamedProperty<OverrideBuiltins::No>(*state, *thisObject, propertyName, getterFunctor)) {
        auto value = toJS<IDLDOMString>(*state, WTFMove(namedProperty.value()));
        slot.setValue(thisObject, static_cast<unsigned>(0), value);
        return true;
    }
    return JSObject::getOwnPropertySlotByIndex(object, state, index, slot);
}

void JSTestNamedAndIndexedSetterThrowingException::getOwnPropertyNames(JSObject* object, ExecState* state, PropertyNameArray& propertyNames, EnumerationMode mode)
{
    auto* thisObject = jsCast<JSTestNamedAndIndexedSetterThrowingException*>(object);
    ASSERT_GC_OBJECT_INHERITS(object, info());
    for (unsigned i = 0, count = thisObject->wrapped().length(); i < count; ++i)
        propertyNames.add(Identifier::from(state, i));
    for (auto& propertyName : thisObject->wrapped().supportedPropertyNames())
        propertyNames.add(Identifier::fromString(state, propertyName));
    JSObject::getOwnPropertyNames(object, state, propertyNames, mode);
}

bool JSTestNamedAndIndexedSetterThrowingException::put(JSCell* cell, ExecState* state, PropertyName propertyName, JSValue value, PutPropertySlot& putPropertySlot)
{
    auto* thisObject = jsCast<JSTestNamedAndIndexedSetterThrowingException*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (auto index = parseIndex(propertyName)) {
        auto throwScope = DECLARE_THROW_SCOPE(state->vm());
        auto nativeValue = convert<IDLDOMString>(*state, value);
        RETURN_IF_EXCEPTION(throwScope, true);
        propagateException(*state, throwScope, thisObject->wrapped().setItem(index.value(), WTFMove(nativeValue)));
        return true;
    }

    if (!propertyName.isSymbol()) {
        PropertySlot slot { thisObject, PropertySlot::InternalMethodType::VMInquiry };
        JSValue prototype = thisObject->getPrototypeDirect(state->vm());
        if (!(prototype.isObject() && asObject(prototype)->getPropertySlot(state, propertyName, slot))) {
            auto throwScope = DECLARE_THROW_SCOPE(state->vm());
            auto nativeValue = convert<IDLDOMString>(*state, value);
            RETURN_IF_EXCEPTION(throwScope, true);
            propagateException(*state, throwScope, thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue)));
            return true;
        }
    }

    return JSObject::put(thisObject, state, propertyName, value, putPropertySlot);
}

bool JSTestNamedAndIndexedSetterThrowingException::putByIndex(JSCell* cell, ExecState* state, unsigned index, JSValue value, bool shouldThrow)
{
    auto* thisObject = jsCast<JSTestNamedAndIndexedSetterThrowingException*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (LIKELY(index <= MAX_ARRAY_INDEX)) {
        auto throwScope = DECLARE_THROW_SCOPE(state->vm());
        auto nativeValue = convert<IDLDOMString>(*state, value);
        RETURN_IF_EXCEPTION(throwScope, true);
        propagateException(*state, throwScope, thisObject->wrapped().setItem(index, WTFMove(nativeValue)));
        return true;
    }

    auto propertyName = Identifier::from(state, index);
    PropertySlot slot { thisObject, PropertySlot::InternalMethodType::VMInquiry };
    JSValue prototype = thisObject->getPrototypeDirect(state->vm());
    if (!(prototype.isObject() && asObject(prototype)->getPropertySlot(state, propertyName, slot))) {
        auto throwScope = DECLARE_THROW_SCOPE(state->vm());
        auto nativeValue = convert<IDLDOMString>(*state, value);
        RETURN_IF_EXCEPTION(throwScope, true);
        propagateException(*state, throwScope, thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue)));
        return true;
    }

    return JSObject::putByIndex(cell, state, index, value, shouldThrow);
}

bool JSTestNamedAndIndexedSetterThrowingException::defineOwnProperty(JSObject* object, ExecState* state, PropertyName propertyName, const PropertyDescriptor& propertyDescriptor, bool shouldThrow)
{
    auto* thisObject = jsCast<JSTestNamedAndIndexedSetterThrowingException*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (auto index = parseIndex(propertyName)) {
        if (!propertyDescriptor.isDataDescriptor())
            return false;
        auto throwScope = DECLARE_THROW_SCOPE(state->vm());
        auto nativeValue = convert<IDLDOMString>(*state, propertyDescriptor.value());
        RETURN_IF_EXCEPTION(throwScope, true);
        propagateException(*state, throwScope, thisObject->wrapped().setItem(index.value(), WTFMove(nativeValue)));
        return true;
    }

    if (!propertyName.isSymbol()) {
        PropertySlot slot { thisObject, PropertySlot::InternalMethodType::VMInquiry };
        if (!JSObject::getOwnPropertySlot(thisObject, state, propertyName, slot)) {
            if (!propertyDescriptor.isDataDescriptor())
                return false;
            auto throwScope = DECLARE_THROW_SCOPE(state->vm());
            auto nativeValue = convert<IDLDOMString>(*state, propertyDescriptor.value());
            RETURN_IF_EXCEPTION(throwScope, true);
            propagateException(*state, throwScope, thisObject->wrapped().setNamedItem(propertyNameToString(propertyName), WTFMove(nativeValue)));
            return true;
        }
    }

    PropertyDescriptor newPropertyDescriptor = propertyDescriptor;
    newPropertyDescriptor.setConfigurable(true);
    return JSObject::defineOwnProperty(object, state, propertyName, newPropertyDescriptor, shouldThrow);
}

EncodedJSValue jsTestNamedAndIndexedSetterThrowingExceptionConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedAndIndexedSetterThrowingExceptionPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(state, throwScope);
    return JSValue::encode(JSTestNamedAndIndexedSetterThrowingException::getConstructor(state->vm(), prototype->globalObject()));
}

bool setJSTestNamedAndIndexedSetterThrowingExceptionConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestNamedAndIndexedSetterThrowingExceptionPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(state, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

void JSTestNamedAndIndexedSetterThrowingException::heapSnapshot(JSCell* cell, HeapSnapshotBuilder& builder)
{
    auto* thisObject = jsCast<JSTestNamedAndIndexedSetterThrowingException*>(cell);
    builder.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        builder.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::heapSnapshot(cell, builder);
}

bool JSTestNamedAndIndexedSetterThrowingExceptionOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestNamedAndIndexedSetterThrowingExceptionOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestNamedAndIndexedSetterThrowingException = static_cast<JSTestNamedAndIndexedSetterThrowingException*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestNamedAndIndexedSetterThrowingException->wrapped(), jsTestNamedAndIndexedSetterThrowingException);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestNamedAndIndexedSetterThrowingException@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore42TestNamedAndIndexedSetterThrowingExceptionE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject* globalObject, Ref<TestNamedAndIndexedSetterThrowingException>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl.ptr()));
#if PLATFORM(WIN)
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(__identifier("??_7TestNamedAndIndexedSetterThrowingException@WebCore@@6B@"));
#else
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(&_ZTVN7WebCore42TestNamedAndIndexedSetterThrowingExceptionE[2]);
#endif

    // If this fails TestNamedAndIndexedSetterThrowingException does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestNamedAndIndexedSetterThrowingException>::value, "TestNamedAndIndexedSetterThrowingException is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestNamedAndIndexedSetterThrowingException has subclasses. If TestNamedAndIndexedSetterThrowingException has subclasses that get passed
    // to toJS() we currently require TestNamedAndIndexedSetterThrowingException you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestNamedAndIndexedSetterThrowingException>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::ExecState* state, JSDOMGlobalObject* globalObject, TestNamedAndIndexedSetterThrowingException& impl)
{
    return wrap(state, globalObject, impl);
}

TestNamedAndIndexedSetterThrowingException* JSTestNamedAndIndexedSetterThrowingException::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestNamedAndIndexedSetterThrowingException*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
