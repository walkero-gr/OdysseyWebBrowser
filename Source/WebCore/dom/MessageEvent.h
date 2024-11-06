/*
 * Copyright (C) 2007 Henry Mason (hmason@mac.com)
 * Copyright (C) 2003-2018 Apple Inc. All rights reserved.
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
 *
 */

#pragma once

#include "Event.h"
#include "JSValueInWrappedObject.h"
#include "MessagePort.h"
#include "SerializedScriptValue.h"
#include "ServiceWorker.h"
#include "WindowProxy.h"
#if OS(AROS)
#include <wtf/Variant.h>
#else
#warning "Source/WebCore/dom/MessageEvent.h Variant"
#include <variant>
#endif // OS(AROS)

namespace WebCore {

class Blob;

#if OS(AROS)
#if ENABLE(SERVICE_WORKER)
using MessageEventSource = Variant<RefPtr<WindowProxy>, RefPtr<MessagePort>, RefPtr<ServiceWorker>>;
#else
using MessageEventSource = Variant<RefPtr<WindowProxy>, RefPtr<MessagePort>>;
#endif // ENABLE(SERVICE_WORKER)
#else
#if ENABLE(SERVICE_WORKER)
using MessageEventSource = std::variant<RefPtr<WindowProxy>, RefPtr<MessagePort>, RefPtr<ServiceWorker>>;
#else
using MessageEventSource = std::variant<RefPtr<WindowProxy>, RefPtr<MessagePort>>;
#endif // ENABLE(SERVICE_WORKER)
#endif // OS(AROS)
class MessageEvent final : public Event {
public:
    static Ref<MessageEvent> create(Vector<RefPtr<MessagePort>>&&, Ref<SerializedScriptValue>&&, const String& origin = { }, const String& lastEventId = { }, Optional<MessageEventSource>&& source = WTF::nullopt);
    static Ref<MessageEvent> create(const AtomicString& type, Ref<SerializedScriptValue>&&, const String& origin, const String& lastEventId);
    static Ref<MessageEvent> create(const String& data, const String& origin = { });
    static Ref<MessageEvent> create(Ref<Blob>&& data, const String& origin);
    static Ref<MessageEvent> create(Ref<ArrayBuffer>&& data, const String& origin = { });
    static Ref<MessageEvent> createForBindings();

    struct Init : EventInit {
        JSC::JSValue data;
        String origin;
        String lastEventId;
        Optional<MessageEventSource> source;
        Vector<RefPtr<MessagePort>> ports;
    };
    static Ref<MessageEvent> create(const AtomicString& type, Init&&, IsTrusted = IsTrusted::No);

    virtual ~MessageEvent();

    void initMessageEvent(const AtomicString& type, bool canBubble, bool cancelable, JSC::JSValue data, const String& origin, const String& lastEventId, Optional<MessageEventSource>&&, Vector<RefPtr<MessagePort>>&&);

    const String& origin() const { return m_origin; }
    const String& lastEventId() const { return m_lastEventId; }
    const Optional<MessageEventSource>& source() const { return m_source; }
    const Vector<RefPtr<MessagePort>>& ports() const { return m_ports; }

    using DataType = Variant<JSValueInWrappedObject, Ref<SerializedScriptValue>, String, Ref<Blob>, Ref<ArrayBuffer>>;
    const DataType& data() const { return m_data; }

    JSValueInWrappedObject& cachedData() { return m_cachedData; }
    JSValueInWrappedObject& cachedPorts() { return m_cachedPorts; }

private:
    MessageEvent();
    MessageEvent(const AtomicString& type, Init&&, IsTrusted);
    MessageEvent(const AtomicString& type, Ref<SerializedScriptValue>&& data, const String& origin, const String& lastEventId);
    MessageEvent(DataType&&, const String& origin, const String& lastEventId = { }, Optional<MessageEventSource>&& = WTF::nullopt, Vector<RefPtr<MessagePort>>&& = { });

    EventInterface eventInterface() const final;

    DataType m_data;
    String m_origin;
    String m_lastEventId;
    Optional<MessageEventSource> m_source;
    Vector<RefPtr<MessagePort>> m_ports;

    JSValueInWrappedObject m_cachedData;
    JSValueInWrappedObject m_cachedPorts;
};

} // namespace WebCore
