/*
 * Copyright (C) 2016-2018 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "APIObject.h"
#include "AutomationBackendDispatchers.h"
#include "AutomationFrontendDispatchers.h"
#include "Connection.h"
#include "ShareableBitmap.h"
#include "SimulatedInputDispatcher.h"
#include "WebEvent.h"
#include <wtf/CompletionHandler.h>
#include <wtf/Forward.h>
#include <wtf/RunLoop.h>

#if ENABLE(REMOTE_INSPECTOR)
#include <JavaScriptCore/RemoteAutomationTarget.h>
#endif

namespace API {
class AutomationSessionClient;
}

namespace Inspector {
class BackendDispatcher;
class FrontendRouter;
}

namespace WebCore {
class IntPoint;
class IntRect;

struct Cookie;
}

#if PLATFORM(COCOA)
OBJC_CLASS NSArray;
typedef unsigned short unichar;
#endif

#if USE(APPKIT)
OBJC_CLASS NSEvent;
#endif

namespace API {
class OpenPanelParameters;
}

namespace WebKit {

class WebAutomationSessionClient;
class WebFrameProxy;
class WebOpenPanelResultListenerProxy;
class WebPageProxy;
class WebProcessPool;

class AutomationCommandError {
public:
    Inspector::Protocol::Automation::ErrorMessage type;
    std::optional<String> message { std::nullopt };
    
    AutomationCommandError(Inspector::Protocol::Automation::ErrorMessage type)
        : type(type) { }

    AutomationCommandError(Inspector::Protocol::Automation::ErrorMessage type, const String& message)
        : type(type)
        , message(message) { }
    
    String toProtocolString();
};

using AutomationCompletionHandler = WTF::CompletionHandler<void(std::optional<AutomationCommandError>)>;

class WebAutomationSession final : public API::ObjectImpl<API::Object::Type::AutomationSession>, public IPC::MessageReceiver
#if ENABLE(REMOTE_INSPECTOR)
    , public Inspector::RemoteAutomationTarget
#endif
    , public Inspector::AutomationBackendDispatcherHandler
    , public SimulatedInputDispatcher::Client
{
public:
    WebAutomationSession();
    ~WebAutomationSession();

    void setClient(std::unique_ptr<API::AutomationSessionClient>&&);

    void setSessionIdentifier(const String& sessionIdentifier) { m_sessionIdentifier = sessionIdentifier; }
    String sessionIdentifier() const { return m_sessionIdentifier; }

    WebProcessPool* processPool() const { return m_processPool; }
    void setProcessPool(WebProcessPool*);

    void navigationOccurredForFrame(const WebFrameProxy&);
    void documentLoadedForFrame(const WebFrameProxy&);
    void inspectorFrontendLoaded(const WebPageProxy&);
    void keyboardEventsFlushedForPage(const WebPageProxy&);
    void mouseEventsFlushedForPage(const WebPageProxy&);
    void willClosePage(const WebPageProxy&);
    void handleRunOpenPanel(const WebPageProxy&, const WebFrameProxy&, const API::OpenPanelParameters&, WebOpenPanelResultListenerProxy&);
    void willShowJavaScriptDialog(WebPageProxy&);
    void didEnterFullScreenForPage(const WebPageProxy&);
    void didExitFullScreenForPage(const WebPageProxy&);

    bool shouldAllowGetUserMediaForPage(const WebPageProxy&) const;

#if ENABLE(REMOTE_INSPECTOR)
    // Inspector::RemoteAutomationTarget API
    String name() const override { return m_sessionIdentifier; }
    void dispatchMessageFromRemote(const String& message) override;
    void connect(Inspector::FrontendChannel*, bool isAutomaticConnection = false, bool immediatelyPause = false) override;
    void disconnect(Inspector::FrontendChannel*) override;
#endif
    void terminate();

    // SimulatedInputDispatcher::Client API
    void simulateMouseInteraction(WebPageProxy&, MouseInteraction, WebMouseEvent::Button, const WebCore::IntPoint& locationInView, AutomationCompletionHandler&&) final;
    void simulateKeyboardInteraction(WebPageProxy&, KeyboardInteraction, WTF::Variant<VirtualKey, CharKey>&&, AutomationCompletionHandler&&) final;
    void viewportInViewCenterPointOfElement(WebPageProxy&, uint64_t frameID, const String& nodeHandle, Function<void (std::optional<WebCore::IntPoint>, std::optional<AutomationCommandError>)>&&) final;

    // Inspector::AutomationBackendDispatcherHandler API
    // NOTE: the set of declarations included in this interface depend on the "platform" property in Automation.json
    // and the --platform argument passed to the protocol bindings generator.

    // Platform: Generic
    void getBrowsingContexts(Ref<GetBrowsingContextsCallback>&&) final;
    void getBrowsingContext(const String&, Ref<GetBrowsingContextCallback>&&) final;
    void createBrowsingContext(const bool* preferNewTab, Ref<CreateBrowsingContextCallback>&&) final;
    void closeBrowsingContext(Inspector::ErrorString&, const String&) final;
    void switchToBrowsingContext(const String& browsingContextHandle, const String* optionalFrameHandle, Ref<SwitchToBrowsingContextCallback>&&) final;
    void setWindowFrameOfBrowsingContext(const String& handle, const JSON::Object* origin, const JSON::Object* size, Ref<SetWindowFrameOfBrowsingContextCallback>&&) final;
    void maximizeWindowOfBrowsingContext(const String& handle, Ref<MaximizeWindowOfBrowsingContextCallback>&&) final;
    void hideWindowOfBrowsingContext(const String& handle, Ref<HideWindowOfBrowsingContextCallback>&&) final;
    void navigateBrowsingContext(const String& handle, const String& url, const String* optionalPageLoadStrategyString, const int* optionalPageLoadTimeout, Ref<NavigateBrowsingContextCallback>&&) override;
    void goBackInBrowsingContext(const String&, const String* optionalPageLoadStrategyString, const int* optionalPageLoadTimeout, Ref<GoBackInBrowsingContextCallback>&&) override;
    void goForwardInBrowsingContext(const String&, const String* optionalPageLoadStrategyString, const int* optionalPageLoadTimeout, Ref<GoForwardInBrowsingContextCallback>&&) override;
    void reloadBrowsingContext(const String&, const String* optionalPageLoadStrategyString, const int* optionalPageLoadTimeout, Ref<ReloadBrowsingContextCallback>&&) override;
    void waitForNavigationToComplete(const String& browsingContextHandle, const String* optionalFrameHandle, const String* optionalPageLoadStrategyString, const int* optionalPageLoadTimeout, Ref<WaitForNavigationToCompleteCallback>&&) override;
    void evaluateJavaScriptFunction(const String& browsingContextHandle, const String* optionalFrameHandle, const String& function, const JSON::Array& arguments, const bool* optionalExpectsImplicitCallbackArgument, const int* optionalCallbackTimeout, Ref<Inspector::AutomationBackendDispatcherHandler::EvaluateJavaScriptFunctionCallback>&&) override;
    void performMouseInteraction(const String& handle, const JSON::Object& requestedPosition, const String& mouseButton, const String& mouseInteraction, const JSON::Array& keyModifiers, Ref<PerformMouseInteractionCallback>&&) final;
    void performKeyboardInteractions(const String& handle, const JSON::Array& interactions, Ref<PerformKeyboardInteractionsCallback>&&) override;
    void performInteractionSequence(const String& handle, const String* optionalFrameHandle, const JSON::Array& sources, const JSON::Array& steps, Ref<PerformInteractionSequenceCallback>&&) override;
    void cancelInteractionSequence(const String& handle, const String* optionalFrameHandle, Ref<CancelInteractionSequenceCallback>&&) override;
    void takeScreenshot(const String& handle, const String* optionalFrameHandle, const String* optionalNodeHandle, const bool* optionalScrollIntoViewIfNeeded, const bool* optionalClipToViewport, Ref<TakeScreenshotCallback>&&) override;
    void resolveChildFrameHandle(const String& browsingContextHandle, const String* optionalFrameHandle, const int* optionalOrdinal, const String* optionalName, const String* optionalNodeHandle, Ref<ResolveChildFrameHandleCallback>&&) override;
    void resolveParentFrameHandle(const String& browsingContextHandle, const String& frameHandle, Ref<ResolveParentFrameHandleCallback>&&) override;
    void computeElementLayout(const String& browsingContextHandle, const String& frameHandle, const String& nodeHandle, const bool* optionalScrollIntoViewIfNeeded, const String& coordinateSystem, Ref<Inspector::AutomationBackendDispatcherHandler::ComputeElementLayoutCallback>&&) override;
    void selectOptionElement(const String& browsingContextHandle, const String& frameHandle, const String& nodeHandle, Ref<Inspector::AutomationBackendDispatcherHandler::SelectOptionElementCallback>&&) override;
    void isShowingJavaScriptDialog(Inspector::ErrorString&, const String& browsingContextHandle, bool* result) override;
    void dismissCurrentJavaScriptDialog(Inspector::ErrorString&, const String& browsingContextHandle) override;
    void acceptCurrentJavaScriptDialog(Inspector::ErrorString&, const String& browsingContextHandle) override;
    void messageOfCurrentJavaScriptDialog(Inspector::ErrorString&, const String& browsingContextHandle, String* text) override;
    void setUserInputForCurrentJavaScriptPrompt(Inspector::ErrorString&, const String& browsingContextHandle, const String& text) override;
    void setFilesToSelectForFileUpload(Inspector::ErrorString&, const String& browsingContextHandle, const JSON::Array& filenames) override;
    void getAllCookies(const String& browsingContextHandle, Ref<GetAllCookiesCallback>&&) override;
    void deleteSingleCookie(const String& browsingContextHandle, const String& cookieName, Ref<DeleteSingleCookieCallback>&&) override;
    void addSingleCookie(const String& browsingContextHandle, const JSON::Object& cookie, Ref<AddSingleCookieCallback>&&) override;
    void deleteAllCookies(Inspector::ErrorString&, const String& browsingContextHandle) override;
    void getSessionPermissions(Inspector::ErrorString&, RefPtr<JSON::ArrayOf<Inspector::Protocol::Automation::SessionPermissionData>>& out_permissions) override;
    void setSessionPermissions(Inspector::ErrorString&, const JSON::Array& in_permissions) override;

    // Platform: macOS
#if PLATFORM(MAC)
    void inspectBrowsingContext(const String&, const bool* optionalEnableAutoCapturing, Ref<InspectBrowsingContextCallback>&&) override;
#endif

    // Event Simulation Support.
    bool isSimulatingUserInteraction() const;
    SimulatedInputDispatcher& inputDispatcherForPage(WebPageProxy&);
    SimulatedInputSource* inputSourceForType(SimulatedInputSourceType) const;

#if PLATFORM(MAC)
    bool wasEventSynthesizedForAutomation(NSEvent *);
    void markEventAsSynthesizedForAutomation(NSEvent *);
#endif

private:
    WebPageProxy* webPageProxyForHandle(const String&);
    String handleForWebPageProxy(const WebPageProxy&);
    Ref<Inspector::Protocol::Automation::BrowsingContext> buildBrowsingContextForPage(WebPageProxy&, WebCore::FloatRect windowFrame);
    void getNextContext(Ref<WebAutomationSession>&&, Vector<Ref<WebPageProxy>>&&, Ref<JSON::ArrayOf<Inspector::Protocol::Automation::BrowsingContext>>, Ref<WebAutomationSession::GetBrowsingContextsCallback>&&);

    std::optional<uint64_t> webFrameIDForHandle(const String&);
    String handleForWebFrameID(uint64_t frameID);
    String handleForWebFrameProxy(const WebFrameProxy&);

    void waitForNavigationToCompleteOnPage(WebPageProxy&, Inspector::Protocol::Automation::PageLoadStrategy, Seconds, Ref<Inspector::BackendDispatcher::CallbackBase>&&);
    void waitForNavigationToCompleteOnFrame(WebFrameProxy&, Inspector::Protocol::Automation::PageLoadStrategy, Seconds, Ref<Inspector::BackendDispatcher::CallbackBase>&&);
    void respondToPendingPageNavigationCallbacksWithTimeout(HashMap<uint64_t, RefPtr<Inspector::BackendDispatcher::CallbackBase>>&);
    void respondToPendingFrameNavigationCallbacksWithTimeout(HashMap<uint64_t, RefPtr<Inspector::BackendDispatcher::CallbackBase>>&);
    void loadTimerFired();

    void exitFullscreenWindowForPage(WebPageProxy&, WTF::CompletionHandler<void()>&&);
    void restoreWindowForPage(WebPageProxy&, WTF::CompletionHandler<void()>&&);
    void maximizeWindowForPage(WebPageProxy&, WTF::CompletionHandler<void()>&&);
    void hideWindowForPage(WebPageProxy&, WTF::CompletionHandler<void()>&&);

    // Implemented in generated WebAutomationSessionMessageReceiver.cpp.
    void didReceiveMessage(IPC::Connection&, IPC::Decoder&) override;

    // Called by WebAutomationSession messages.
    void didEvaluateJavaScriptFunction(uint64_t callbackID, const String& result, const String& errorType);
    void didResolveChildFrame(uint64_t callbackID, uint64_t frameID, const String& errorType);
    void didResolveParentFrame(uint64_t callbackID, uint64_t frameID, const String& errorType);
    void didComputeElementLayout(uint64_t callbackID, WebCore::IntRect, std::optional<WebCore::IntPoint>, bool isObscured, const String& errorType);
    void didSelectOptionElement(uint64_t callbackID, const String& errorType);
    void didTakeScreenshot(uint64_t callbackID, const ShareableBitmap::Handle&, const String& errorType);
    void didGetCookiesForFrame(uint64_t callbackID, Vector<WebCore::Cookie>, const String& errorType);
    void didDeleteCookie(uint64_t callbackID, const String& errorType);

    // Platform-dependent implementations.
    void platformSimulateMouseInteraction(WebPageProxy&, MouseInteraction, WebMouseEvent::Button, const WebCore::IntPoint& locationInView, WebEvent::Modifiers keyModifiers);
    // Simulates a single virtual or char key being pressed/released, such as 'a', Control, F-keys, Numpad keys, etc. as allowed by the protocol.
    void platformSimulateKeyboardInteraction(WebPageProxy&, KeyboardInteraction, WTF::Variant<VirtualKey, CharKey>&&);
    // Simulates key presses to produce the codepoints in a string. One or more code points are delivered atomically at grapheme cluster boundaries.
    void platformSimulateKeySequence(WebPageProxy&, const String&);
    // Get base64 encoded PNG data from a bitmap.
    std::optional<String> platformGetBase64EncodedPNGData(const ShareableBitmap::Handle&);

#if PLATFORM(COCOA)
    // The type parameter of the NSArray argument is platform-dependent.
    void sendSynthesizedEventsToPage(WebPageProxy&, NSArray *eventsToSend);

    std::optional<unichar> charCodeForVirtualKey(Inspector::Protocol::Automation::VirtualKey) const;
    std::optional<unichar> charCodeIgnoringModifiersForVirtualKey(Inspector::Protocol::Automation::VirtualKey) const;
#endif

    WebProcessPool* m_processPool { nullptr };

    std::unique_ptr<API::AutomationSessionClient> m_client;
    String m_sessionIdentifier { "Untitled Session"_s };
    Ref<Inspector::FrontendRouter> m_frontendRouter;
    Ref<Inspector::BackendDispatcher> m_backendDispatcher;
    Ref<Inspector::AutomationBackendDispatcher> m_domainDispatcher;
    std::unique_ptr<Inspector::AutomationFrontendDispatcher> m_domainNotifier;

    HashMap<uint64_t, String> m_webPageHandleMap;
    HashMap<String, uint64_t> m_handleWebPageMap;

    HashMap<uint64_t, String> m_webFrameHandleMap;
    HashMap<String, uint64_t> m_handleWebFrameMap;

    HashMap<uint64_t, RefPtr<Inspector::BackendDispatcher::CallbackBase>> m_pendingNormalNavigationInBrowsingContextCallbacksPerPage;
    HashMap<uint64_t, RefPtr<Inspector::BackendDispatcher::CallbackBase>> m_pendingEagerNavigationInBrowsingContextCallbacksPerPage;
    HashMap<uint64_t, RefPtr<Inspector::BackendDispatcher::CallbackBase>> m_pendingNormalNavigationInBrowsingContextCallbacksPerFrame;
    HashMap<uint64_t, RefPtr<Inspector::BackendDispatcher::CallbackBase>> m_pendingEagerNavigationInBrowsingContextCallbacksPerFrame;
    HashMap<uint64_t, RefPtr<Inspector::BackendDispatcher::CallbackBase>> m_pendingInspectorCallbacksPerPage;
    HashMap<uint64_t, Function<void(std::optional<AutomationCommandError>)>> m_pendingKeyboardEventsFlushedCallbacksPerPage;
    HashMap<uint64_t, Function<void(std::optional<AutomationCommandError>)>> m_pendingMouseEventsFlushedCallbacksPerPage;

    uint64_t m_nextEvaluateJavaScriptCallbackID { 1 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::EvaluateJavaScriptFunctionCallback>> m_evaluateJavaScriptFunctionCallbacks;

    uint64_t m_nextResolveFrameCallbackID { 1 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::ResolveChildFrameHandleCallback>> m_resolveChildFrameHandleCallbacks;

    uint64_t m_nextResolveParentFrameCallbackID { 1 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::ResolveParentFrameHandleCallback>> m_resolveParentFrameHandleCallbacks;

    // Start at 2 and use only even numbers to not conflict with m_nextViewportInViewCenterPointOfElementCallbackID.
    uint64_t m_nextComputeElementLayoutCallbackID { 2 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::ComputeElementLayoutCallback>> m_computeElementLayoutCallbacks;

    // Start at 3 and use only odd numbers to not conflict with m_nextComputeElementLayoutCallbackID.
    uint64_t m_nextViewportInViewCenterPointOfElementCallbackID { 3 };
    HashMap<uint64_t, Function<void(std::optional<WebCore::IntPoint>, std::optional<AutomationCommandError>)>> m_viewportInViewCenterPointOfElementCallbacks;

    uint64_t m_nextScreenshotCallbackID { 1 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::TakeScreenshotCallback>> m_screenshotCallbacks;

    uint64_t m_nextGetCookiesCallbackID { 1 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::GetAllCookiesCallback>> m_getCookieCallbacks;

    uint64_t m_nextDeleteCookieCallbackID { 1 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::DeleteSingleCookieCallback>> m_deleteCookieCallbacks;

    uint64_t m_nextSelectOptionElementCallbackID { 1 };
    HashMap<uint64_t, RefPtr<Inspector::AutomationBackendDispatcherHandler::SelectOptionElementCallback>> m_selectOptionElementCallbacks;

    enum class WindowTransitionedToState {
        Fullscreen,
        Unfullscreen,
    };
    Function<void(WindowTransitionedToState)> m_windowStateTransitionCallback { };

    RunLoop::Timer<WebAutomationSession> m_loadTimer;
    Vector<String> m_filesToSelectForFileUpload;

    bool m_permissionForGetUserMedia { true };

    // Keep track of currently active modifiers across multiple keystrokes.
    // Most platforms do not track current modifiers from synthesized events.
    unsigned m_currentModifiers { 0 };

    // SimulatedInputDispatcher APIs take a set of input sources. We also intern these
    // so that previous input source state is used as initial state for later commands.
    HashSet<Ref<SimulatedInputSource>> m_inputSources;
    HashMap<uint64_t, Ref<SimulatedInputDispatcher>> m_inputDispatchersByPage;

#if ENABLE(REMOTE_INSPECTOR)
    Inspector::FrontendChannel* m_remoteChannel { nullptr };
#endif

};

} // namespace WebKit
