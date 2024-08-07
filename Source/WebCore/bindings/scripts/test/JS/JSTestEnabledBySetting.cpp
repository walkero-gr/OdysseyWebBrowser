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
#include "JSTestEnabledBySetting.h"

#include "Document.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "JSTestSubObj.h"
#include "Settings.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/JSCInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>

#if ENABLE(TEST_FEATURE)
#include "JSDOMConvertStrings.h"
#endif


namespace WebCore {
using namespace JSC;

// Functions

#if ENABLE(TEST_FEATURE)
JSC::EncodedJSValue JSC_HOST_CALL jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperation(JSC::ExecState*);
#endif

// Attributes

JSC::EncodedJSValue jsTestEnabledBySettingConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestEnabledBySettingConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);
JSC::EncodedJSValue jsTestEnabledBySettingTestSubObjEnabledBySettingConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#if ENABLE(TEST_FEATURE)
JSC::EncodedJSValue jsTestEnabledBySettingEnabledBySettingAttribute(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
bool setJSTestEnabledBySettingEnabledBySettingAttribute(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);
#endif

class JSTestEnabledBySettingPrototype : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestEnabledBySettingPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestEnabledBySettingPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestEnabledBySettingPrototype>(vm.heap)) JSTestEnabledBySettingPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestEnabledBySettingPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

using JSTestEnabledBySettingConstructor = JSDOMConstructorNotConstructable<JSTestEnabledBySetting>;

template<> JSValue JSTestEnabledBySettingConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestEnabledBySettingConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestEnabledBySetting::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(&vm, String(ASCIILiteral("TestEnabledBySetting"))), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

template<> const ClassInfo JSTestEnabledBySettingConstructor::s_info = { "TestEnabledBySetting", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEnabledBySettingConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestEnabledBySettingPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestEnabledBySettingConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestEnabledBySettingConstructor) } },
#if ENABLE(TEST_FEATURE)
    { "enabledBySettingAttribute", static_cast<unsigned>(JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestEnabledBySettingEnabledBySettingAttribute), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestEnabledBySettingEnabledBySettingAttribute) } },
#else
    { 0, 0, NoIntrinsic, { 0, 0 } },
#endif
#if ENABLE(TEST_FEATURE)
    { "enabledBySettingOperation", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<NativeFunction>(jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperation), (intptr_t) (1) } },
#else
    { 0, 0, NoIntrinsic, { 0, 0 } },
#endif
};

const ClassInfo JSTestEnabledBySettingPrototype::s_info = { "TestEnabledBySettingPrototype", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEnabledBySettingPrototype) };

void JSTestEnabledBySettingPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestEnabledBySetting::info(), JSTestEnabledBySettingPrototypeTableValues, *this);
#if ENABLE(TEST_FEATURE)
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settings().testSettingEnabled()) {
        auto propertyName = Identifier::fromString(&vm, reinterpret_cast<const LChar*>("enabledBySettingOperation"), strlen("enabledBySettingOperation"));
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        JSObject::deleteProperty(this, globalObject()->globalExec(), propertyName);
    }
#endif
#if ENABLE(TEST_FEATURE)
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settings().testSettingEnabled()) {
        auto propertyName = Identifier::fromString(&vm, reinterpret_cast<const LChar*>("enabledBySettingAttribute"), strlen("enabledBySettingAttribute"));
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        JSObject::deleteProperty(this, globalObject()->globalExec(), propertyName);
    }
#endif
}

const ClassInfo JSTestEnabledBySetting::s_info = { "TestEnabledBySetting", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEnabledBySetting) };

JSTestEnabledBySetting::JSTestEnabledBySetting(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestEnabledBySetting>&& impl)
    : JSDOMWrapper<TestEnabledBySetting>(structure, globalObject, WTFMove(impl))
{
}

void JSTestEnabledBySetting::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    if (downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settings().testSettingEnabled())
        putDirectCustomAccessor(vm, static_cast<JSVMClientData*>(vm.clientData)->builtinNames().TestSubObjEnabledBySettingPublicName(), CustomGetterSetter::create(vm, jsTestEnabledBySettingTestSubObjEnabledBySettingConstructor, setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructor), attributesForStructure(static_cast<unsigned>(JSC::PropertyAttribute::DontEnum)));
}

JSObject* JSTestEnabledBySetting::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestEnabledBySettingPrototype::create(vm, &globalObject, JSTestEnabledBySettingPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestEnabledBySetting::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestEnabledBySetting>(vm, globalObject);
}

JSValue JSTestEnabledBySetting::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestEnabledBySettingConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestEnabledBySetting::destroy(JSC::JSCell* cell)
{
    JSTestEnabledBySetting* thisObject = static_cast<JSTestEnabledBySetting*>(cell);
    thisObject->JSTestEnabledBySetting::~JSTestEnabledBySetting();
}

template<> inline JSTestEnabledBySetting* IDLAttribute<JSTestEnabledBySetting>::cast(ExecState& state, EncodedJSValue thisValue)
{
    return jsDynamicDowncast<JSTestEnabledBySetting*>(state.vm(), JSValue::decode(thisValue));
}

template<> inline JSTestEnabledBySetting* IDLOperation<JSTestEnabledBySetting>::cast(ExecState& state)
{
    return jsDynamicDowncast<JSTestEnabledBySetting*>(state.vm(), state.thisValue());
}

EncodedJSValue jsTestEnabledBySettingConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicDowncast<JSTestEnabledBySettingPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(state, throwScope);
    return JSValue::encode(JSTestEnabledBySetting::getConstructor(state->vm(), prototype->globalObject()));
}

bool setJSTestEnabledBySettingConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    VM& vm = state->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicDowncast<JSTestEnabledBySettingPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype)) {
        throwVMTypeError(state, throwScope);
        return false;
    }
    // Shadowing a built-in constructor
    return prototype->putDirect(vm, vm.propertyNames->constructor, JSValue::decode(encodedValue));
}

static inline JSValue jsTestEnabledBySettingTestSubObjEnabledBySettingConstructorGetter(ExecState& state, JSTestEnabledBySetting& thisObject, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(state);
    return JSTestSubObj::getConstructor(state.vm(), thisObject.globalObject());
}

EncodedJSValue jsTestEnabledBySettingTestSubObjEnabledBySettingConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    return IDLAttribute<JSTestEnabledBySetting>::get<jsTestEnabledBySettingTestSubObjEnabledBySettingConstructorGetter>(*state, thisValue, "TestSubObjEnabledBySetting");
}

static inline bool setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructorSetter(ExecState& state, JSTestEnabledBySetting& thisObject, JSValue value, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    // Shadowing a built-in constructor.
    return thisObject.putDirect(state.vm(), Identifier::fromString(&state.vm(), reinterpret_cast<const LChar*>("TestSubObjEnabledBySetting"), strlen("TestSubObjEnabledBySetting")), value);
}

bool setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    return IDLAttribute<JSTestEnabledBySetting>::set<setJSTestEnabledBySettingTestSubObjEnabledBySettingConstructorSetter>(*state, thisValue, encodedValue, "TestSubObjEnabledBySetting");
}

#if ENABLE(TEST_FEATURE)
static inline JSValue jsTestEnabledBySettingEnabledBySettingAttributeGetter(ExecState& state, JSTestEnabledBySetting& thisObject, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(state);
    auto& impl = thisObject.wrapped();
    JSValue result = toJS<IDLDOMString>(state, throwScope, impl.enabledBySettingAttribute());
    return result;
}

EncodedJSValue jsTestEnabledBySettingEnabledBySettingAttribute(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    return IDLAttribute<JSTestEnabledBySetting>::get<jsTestEnabledBySettingEnabledBySettingAttributeGetter, CastedThisErrorBehavior::Assert>(*state, thisValue, "enabledBySettingAttribute");
}

#endif

#if ENABLE(TEST_FEATURE)
static inline bool setJSTestEnabledBySettingEnabledBySettingAttributeSetter(ExecState& state, JSTestEnabledBySetting& thisObject, JSValue value, ThrowScope& throwScope)
{
    UNUSED_PARAM(throwScope);
    auto& impl = thisObject.wrapped();
    auto nativeValue = convert<IDLDOMString>(state, value);
    RETURN_IF_EXCEPTION(throwScope, false);
    AttributeSetter::call(state, throwScope, [&] {
        return impl.setEnabledBySettingAttribute(WTFMove(nativeValue));
    });
    return true;
}

bool setJSTestEnabledBySettingEnabledBySettingAttribute(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    return IDLAttribute<JSTestEnabledBySetting>::set<setJSTestEnabledBySettingEnabledBySettingAttributeSetter>(*state, thisValue, encodedValue, "enabledBySettingAttribute");
}

#endif

#if ENABLE(TEST_FEATURE)
static inline JSC::EncodedJSValue jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperationBody(JSC::ExecState* state, typename IDLOperation<JSTestEnabledBySetting>::ClassParameter castedThis, JSC::ThrowScope& throwScope)
{
    UNUSED_PARAM(state);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(state->argumentCount() < 1))
        return throwVMError(state, throwScope, createNotEnoughArgumentsError(state));
    auto testParam = convert<IDLDOMString>(*state, state->uncheckedArgument(0));
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    impl.enabledBySettingOperation(WTFMove(testParam));
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperation(ExecState* state)
{
    return IDLOperation<JSTestEnabledBySetting>::call<jsTestEnabledBySettingPrototypeFunctionEnabledBySettingOperationBody>(*state, "enabledBySettingOperation");
}

#endif

bool JSTestEnabledBySettingOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestEnabledBySettingOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestEnabledBySetting = static_cast<JSTestEnabledBySetting*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestEnabledBySetting->wrapped(), jsTestEnabledBySetting);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestEnabledBySetting@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore20TestEnabledBySettingE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject* globalObject, Ref<TestEnabledBySetting>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl.ptr()));
#if PLATFORM(WIN)
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(__identifier("??_7TestEnabledBySetting@WebCore@@6B@"));
#else
    void* expectedVTablePointer = WTF_PREPARE_VTBL_POINTER_FOR_INSPECTION(&_ZTVN7WebCore20TestEnabledBySettingE[2]);
#endif

    // If this fails TestEnabledBySetting does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestEnabledBySetting>::value, "TestEnabledBySetting is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestEnabledBySetting has subclasses. If TestEnabledBySetting has subclasses that get passed
    // to toJS() we currently require TestEnabledBySetting you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestEnabledBySetting>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::ExecState* state, JSDOMGlobalObject* globalObject, TestEnabledBySetting& impl)
{
    return wrap(state, globalObject, impl);
}

TestEnabledBySetting* JSTestEnabledBySetting::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicDowncast<JSTestEnabledBySetting*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
