/*
 * Copyright (C) 2009, 2010 Apple Inc. All Rights Reserved.
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
 */

// This all-in-one cpp file cuts down on template bloat to allow us to build our Windows release build.

#include "ArrayValue.cpp"
#include "CallbackFunction.cpp"
#include "DOMWrapperWorld.cpp"
#include "Dictionary.cpp"
#include "GCController.cpp"
#include "JSAttrCustom.cpp"
#include "JSAudioTrackCustom.cpp"
#include "JSAudioTrackListCustom.cpp"
#include "JSBlobCustom.cpp"
#include "JSCDATASectionCustom.cpp"
#if ENABLE(STREAMS_API)
#include "JSCountQueuingStrategyCustom.cpp"
#endif
#include "JSCSSRuleCustom.cpp"
#include "JSCSSRuleListCustom.cpp"
#include "JSCSSStyleDeclarationCustom.cpp"
#include "JSCSSValueCustom.cpp"
#include "JSCallbackData.cpp"
#include "JSCanvasRenderingContext2DCustom.cpp"
#include "JSCanvasRenderingContextCustom.cpp"
#include "JSCharacterDataCustom.cpp"
#include "JSCommandLineAPIHostCustom.cpp"
#include "JSCryptoCustom.cpp"
#include "JSCustomEventCustom.cpp"
#include "JSCustomSQLStatementErrorCallback.cpp"
#include "JSCustomXPathNSResolver.cpp"
#include "JSDOMBinding.cpp"
#include "JSDOMFormDataCustom.cpp"
#include "JSDOMGlobalObject.cpp"
#include "JSDOMGlobalObjectTask.cpp"
#include "JSDOMMimeTypeArrayCustom.cpp"
#include "JSDOMPluginArrayCustom.cpp"
#include "JSDOMPluginCustom.cpp"
#include "JSDOMPromise.cpp"
#include "JSDOMStringListCustom.cpp"
#include "JSDOMStringMapCustom.cpp"
#include "JSDOMWindowBase.cpp"
#include "JSDOMWindowCustom.cpp"
#include "JSDOMWindowShell.cpp"
#include "JSDOMWrapper.cpp"
#include "JSDataCueCustom.cpp"
#include "JSDataTransferCustom.cpp"
#include "JSDedicatedWorkerGlobalScopeCustom.cpp"
#include "JSDeviceOrientationEventCustom.cpp"
#include "JSDictionary.cpp"
#include "JSDocumentCustom.cpp"
#include "JSDocumentFragmentCustom.cpp"
#include "JSDocumentTypeCustom.cpp"
#include "JSElementCustom.cpp"
#include "JSErrorHandler.cpp"
#include "JSEventCustom.cpp"
#include "JSEventListener.cpp"
#include "JSEventTargetCustom.cpp"
#include "JSExceptionBase.cpp"
#include "JSFileReaderCustom.cpp"
#include "JSGeolocationCustom.cpp"
#include "JSHTMLAllCollectionCustom.cpp"
#include "JSHTMLAppletElementCustom.cpp"
#include "JSHTMLCanvasElementCustom.cpp"
#include "JSHTMLCollectionCustom.cpp"
#include "JSHTMLDocumentCustom.cpp"
#include "JSHTMLElementCustom.cpp"
#include "JSHTMLEmbedElementCustom.cpp"
#include "JSHTMLFormControlsCollectionCustom.cpp"
#include "JSHTMLFormElementCustom.cpp"
#include "JSHTMLFrameElementCustom.cpp"
#include "JSHTMLFrameSetElementCustom.cpp"
#include "JSHTMLInputElementCustom.cpp"
#include "JSHTMLLinkElementCustom.cpp"
#include "JSHTMLMediaElementCustom.cpp"
#include "JSHTMLObjectElementCustom.cpp"
#include "JSHTMLOptionsCollectionCustom.cpp"
#include "JSHTMLSelectElementCustom.cpp"
#include "JSHTMLTemplateElementCustom.cpp"
#include "JSHistoryCustom.cpp"
#include "JSImageConstructor.cpp"
#include "JSImageDataCustom.cpp"
#include "JSInspectorFrontendHostCustom.cpp"
#include "JSLazyEventListener.cpp"
#include "JSLocationCustom.cpp"
#include "JSMainThreadExecState.cpp"
#include "JSMessageChannelCustom.cpp"
#include "JSMessageEventCustom.cpp"
#include "JSMessagePortCustom.cpp"
#include "JSMutationCallback.cpp"
#include "JSMutationObserverCustom.cpp"
#include "JSNamedNodeMapCustom.cpp"
#include "JSNodeCustom.cpp"
#include "JSNodeFilterCondition.cpp"
#include "JSNodeFilterCustom.cpp"
#include "JSNodeIteratorCustom.cpp"
#include "JSNodeListCustom.cpp"
#include "JSNodeOrString.cpp"
#include "JSPluginElementFunctions.cpp"
#include "JSPopStateEventCustom.cpp"
#if ENABLE(STREAMS_API)
#include "JSReadableStreamControllerCustom.cpp"
#include "JSReadableStreamCustom.cpp"
#include "JSReadableStreamReaderCustom.cpp"
#include "ReadableJSStream.cpp"
#endif
#include "JSRequestAnimationFrameCallbackCustom.cpp"
#include "JSSQLResultSetRowListCustom.cpp"
#include "JSSQLTransactionCustom.cpp"
#include "JSSVGLengthCustom.cpp"
#include "JSSVGPathSegCustom.cpp"
#include "JSStorageCustom.cpp"
#include "JSStyleSheetCustom.cpp"
#include "JSStyleSheetListCustom.cpp"
#include "JSTextCustom.cpp"
#include "JSTextTrackCueCustom.cpp"
#include "JSTextTrackCustom.cpp"
#include "JSTextTrackListCustom.cpp"
#include "JSTouchCustom.cpp"
#include "JSTouchListCustom.cpp"
#include "JSTrackCustom.cpp"
#include "JSTrackEventCustom.cpp"
#include "JSTreeWalkerCustom.cpp"
#include "JSVideoTrackCustom.cpp"
#include "JSVideoTrackListCustom.cpp"
#include "JSWebKitPointCustom.cpp"
#include "JSWorkerCustom.cpp"
#include "JSWorkerGlobalScopeBase.cpp"
#include "JSWorkerGlobalScopeCustom.cpp"
#include "JSXMLHttpRequestCustom.cpp"
#include "JSXPathResultCustom.cpp"
#include "JSXSLTProcessorCustom.cpp"
#include "ScheduledAction.cpp"
#include "ScriptCachedFrameData.cpp"
#include "ScriptController.cpp"
#include "ScriptGlobalObject.cpp"
#include "ScriptState.cpp"
#include "SerializedScriptValue.cpp"
#include "WebCoreTypedArrayController.cpp"
#include "WorkerScriptController.cpp"
#include "WorkerScriptDebugServer.cpp"
