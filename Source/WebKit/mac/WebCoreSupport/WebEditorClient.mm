/*
 * Copyright (C) 2006-2016 Apple Inc. All rights reserved.
 * Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "WebEditorClient.h"

#import "DOMCSSStyleDeclarationInternal.h"
#import "DOMDocumentFragmentInternal.h"
#import "DOMDocumentInternal.h"
#import "DOMHTMLElementInternal.h"
#import "DOMHTMLInputElementInternal.h"
#import "DOMHTMLTextAreaElementInternal.h"
#import "DOMNodeInternal.h"
#import "DOMRangeInternal.h"
#import "WebArchive.h"
#import "WebDataSourceInternal.h"
#import "WebDelegateImplementationCaching.h"
#import "WebDocument.h"
#import "WebEditingDelegatePrivate.h"
#import "WebFormDelegate.h"
#import "WebFrameInternal.h"
#import "WebHTMLView.h"
#import "WebHTMLViewInternal.h"
#import "WebKitLogging.h"
#import "WebKitVersionChecks.h"
#import "WebLocalizableStringsInternal.h"
#import "WebNSURLExtras.h"
#import "WebResourceInternal.h"
#import "WebViewInternal.h"
#import <WebCore/ArchiveResource.h>
#import <WebCore/Document.h>
#import <WebCore/DocumentFragment.h>
#import <WebCore/Editor.h>
#import <WebCore/FloatQuad.h>
#import <WebCore/Frame.h>
#import <WebCore/FrameView.h>
#import <WebCore/HTMLInputElement.h>
#import <WebCore/HTMLNames.h>
#import <WebCore/HTMLTextAreaElement.h>
#import <WebCore/KeyboardEvent.h>
#import <WebCore/LegacyWebArchive.h>
#import <WebCore/NSSpellCheckerSPI.h>
#import <WebCore/Page.h>
#import <WebCore/PlatformKeyboardEvent.h>
#import <WebCore/Settings.h>
#import <WebCore/SpellChecker.h>
#import <WebCore/StyleProperties.h>
#import <WebCore/TextIterator.h>
#import <WebCore/UndoStep.h>
#import <WebCore/UserTypingGestureIndicator.h>
#import <WebCore/VisibleUnits.h>
#import <WebCore/WebCoreObjCExtras.h>
#import <runtime/InitializeThreading.h>
#import <wtf/MainThread.h>
#import <wtf/PassRefPtr.h>
#import <wtf/RunLoop.h>
#import <wtf/text/WTFString.h>

#if PLATFORM(IOS)
#import <WebCore/WebCoreThreadMessage.h>
#import "DOMElementInternal.h"
#import "WebFrameView.h"
#import "WebUIKitDelegate.h"
#endif

using namespace WebCore;

using namespace HTMLNames;

#if !PLATFORM(IOS)
@interface NSSpellChecker (WebNSSpellCheckerDetails)
- (NSString *)languageForWordRange:(NSRange)range inString:(NSString *)string orthography:(NSOrthography *)orthography;
@end
#endif

@interface NSAttributedString (WebNSAttributedStringDetails)
- (DOMDocumentFragment *)_documentFromRange:(NSRange)range document:(DOMDocument *)document documentAttributes:(NSDictionary *)attributes subresources:(NSArray **)subresources;
@end

static WebViewInsertAction kit(EditorInsertAction action)
{
    switch (action) {
    case EditorInsertAction::Typed:
        return WebViewInsertActionTyped;
    case EditorInsertAction::Pasted:
        return WebViewInsertActionPasted;
    case EditorInsertAction::Dropped:
        return WebViewInsertActionDropped;
    }
}

@interface WebUndoStep : NSObject
{
    RefPtr<UndoStep> m_step;   
}

+ (WebUndoStep *)stepWithUndoStep:(UndoStep&)step;
- (UndoStep&)step;

@end

@implementation WebUndoStep

+ (void)initialize
{
#if !PLATFORM(IOS)
    JSC::initializeThreading();
    WTF::initializeMainThreadToProcessMainThread();
    RunLoop::initializeMainRunLoop();
#endif
}

- (id)initWithUndoStep:(UndoStep&)step
{
    self = [super init];
    if (!self)
        return nil;
    m_step = &step;
    return self;
}

- (void)dealloc
{
    if (WebCoreObjCScheduleDeallocateOnMainThread([WebUndoStep class], self))
        return;

    [super dealloc];
}

+ (WebUndoStep *)stepWithUndoStep:(UndoStep&)step
{
    return [[[WebUndoStep alloc] initWithUndoStep:step] autorelease];
}

- (UndoStep&)step
{
    return *m_step;
}

@end

@interface WebEditorUndoTarget : NSObject

- (void)undoEditing:(id)arg;
- (void)redoEditing:(id)arg;

@end

@implementation WebEditorUndoTarget

- (void)undoEditing:(id)arg
{
    ASSERT([arg isKindOfClass:[WebUndoStep class]]);
    [arg step].unapply();
}

- (void)redoEditing:(id)arg
{
    ASSERT([arg isKindOfClass:[WebUndoStep class]]);
    [arg step].reapply();
}

@end

WebEditorClient::WebEditorClient(WebView *webView)
    : m_webView(webView)
    , m_undoTarget(adoptNS([[WebEditorUndoTarget alloc] init]))
    , m_weakPtrFactory(this)
{
}

WebEditorClient::~WebEditorClient()
{
}

bool WebEditorClient::isContinuousSpellCheckingEnabled()
{
    return [m_webView isContinuousSpellCheckingEnabled];
}

#if !PLATFORM(IOS)

void WebEditorClient::toggleContinuousSpellChecking()
{
    [m_webView toggleContinuousSpellChecking:nil];
}

bool WebEditorClient::isGrammarCheckingEnabled()
{
    return [m_webView isGrammarCheckingEnabled];
}

void WebEditorClient::toggleGrammarChecking()
{
    [m_webView toggleGrammarChecking:nil];
}

int WebEditorClient::spellCheckerDocumentTag()
{
    return [m_webView spellCheckerDocumentTag];
}

#endif

bool WebEditorClient::shouldDeleteRange(Range* range)
{
    return [[m_webView _editingDelegateForwarder] webView:m_webView
        shouldDeleteDOMRange:kit(range)];
}

bool WebEditorClient::smartInsertDeleteEnabled()
{
    Page* page = [m_webView page];
    if (!page)
        return false;
    return page->settings().smartInsertDeleteEnabled();
}

bool WebEditorClient::isSelectTrailingWhitespaceEnabled()
{
    Page* page = [m_webView page];
    if (!page)
        return false;
    return page->settings().selectTrailingWhitespaceEnabled();
}

bool WebEditorClient::shouldApplyStyle(StyleProperties* style, Range* range)
{
    Ref<MutableStyleProperties> mutableStyle(style->isMutable() ? Ref<MutableStyleProperties>(static_cast<MutableStyleProperties&>(*style)) : style->mutableCopy());
    return [[m_webView _editingDelegateForwarder] webView:m_webView
        shouldApplyStyle:kit(mutableStyle->ensureCSSStyleDeclaration()) toElementsInDOMRange:kit(range)];
}

static void updateFontPanel(WebView *webView)
{
#if !PLATFORM(IOS)
    NSView <WebDocumentView> *view = [[[webView selectedFrame] frameView] documentView];
    if ([view isKindOfClass:[WebHTMLView class]])
        [(WebHTMLView *)view _updateFontPanel];
#else
    UNUSED_PARAM(webView);
#endif
}

void WebEditorClient::didApplyStyle()
{
    updateFontPanel(m_webView);
}

bool WebEditorClient::shouldMoveRangeAfterDelete(Range* range, Range* rangeToBeReplaced)
{
    return [[m_webView _editingDelegateForwarder] webView:m_webView
        shouldMoveRangeAfterDelete:kit(range) replacingRange:kit(rangeToBeReplaced)];
}

bool WebEditorClient::shouldBeginEditing(Range* range)
{
    return [[m_webView _editingDelegateForwarder] webView:m_webView
        shouldBeginEditingInDOMRange:kit(range)];

    return false;
}

bool WebEditorClient::shouldEndEditing(Range* range)
{
    return [[m_webView _editingDelegateForwarder] webView:m_webView
                             shouldEndEditingInDOMRange:kit(range)];
}

bool WebEditorClient::shouldInsertText(const String& text, Range* range, EditorInsertAction action)
{
    WebView* webView = m_webView;
    return [[webView _editingDelegateForwarder] webView:webView shouldInsertText:text replacingDOMRange:kit(range) givenAction:kit(action)];
}

bool WebEditorClient::shouldChangeSelectedRange(Range* fromRange, Range* toRange, EAffinity selectionAffinity, bool stillSelecting)
{
    return [m_webView _shouldChangeSelectedDOMRange:kit(fromRange) toDOMRange:kit(toRange) affinity:kit(selectionAffinity) stillSelecting:stillSelecting];
}

void WebEditorClient::didBeginEditing()
{
#if !PLATFORM(IOS)
    [[NSNotificationCenter defaultCenter] postNotificationName:WebViewDidBeginEditingNotification object:m_webView];
#else
    WebThreadPostNotification(WebViewDidBeginEditingNotification, m_webView, nil);
#endif
}

#if PLATFORM(IOS)

void WebEditorClient::startDelayingAndCoalescingContentChangeNotifications()
{
    m_delayingContentChangeNotifications = true;
}

void WebEditorClient::stopDelayingAndCoalescingContentChangeNotifications()
{
    m_delayingContentChangeNotifications = false;
    
    if (m_hasDelayedContentChangeNotification)
        this->respondToChangedContents();
    
    m_hasDelayedContentChangeNotification = false;
}

#endif

void WebEditorClient::respondToChangedContents()
{
    updateFontPanel(m_webView);
#if !PLATFORM(IOS)
    [[NSNotificationCenter defaultCenter] postNotificationName:WebViewDidChangeNotification object:m_webView];    
#else
    if (m_delayingContentChangeNotifications) {
        m_hasDelayedContentChangeNotification = true;
    } else {
        WebThreadPostNotification(WebViewDidChangeNotification, m_webView, nil);
    }
#endif
}

void WebEditorClient::respondToChangedSelection(Frame* frame)
{
    if (frame->editor().isGettingDictionaryPopupInfo())
        return;

    NSView<WebDocumentView> *documentView = [[kit(frame) frameView] documentView];
    if ([documentView isKindOfClass:[WebHTMLView class]]) {
        [(WebHTMLView *)documentView _selectionChanged];
        [m_webView updateTouchBar];
        m_lastEditorStateWasContentEditable = [(WebHTMLView *)documentView _isEditable] ? EditorStateIsContentEditable::Yes : EditorStateIsContentEditable::No;
    }

#if !PLATFORM(IOS)
    // FIXME: This quirk is needed due to <rdar://problem/5009625> - We can phase it out once Aperture can adopt the new behavior on their end
    if (!WebKitLinkedOnOrAfter(WEBKIT_FIRST_VERSION_WITHOUT_APERTURE_QUIRK) && [[[NSBundle mainBundle] bundleIdentifier] isEqualToString:@"com.apple.Aperture"])
        return;

    [[NSNotificationCenter defaultCenter] postNotificationName:WebViewDidChangeSelectionNotification object:m_webView];
#else
    // Selection can be changed while deallocating down the WebView / Frame / Editor.  Do not post in that case because it's already too late
    // for the NSInvocation to retain the WebView.
    if (![m_webView _isClosing])
        WebThreadPostNotification(WebViewDidChangeSelectionNotification, m_webView, nil);
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200
    if (frame->editor().canEdit())
        requestCandidatesForSelection(frame->selection().selection());
#endif
}

void WebEditorClient::discardedComposition(Frame*)
{
    // The effects of this function are currently achieved via -[WebHTMLView _updateSelectionForInputManager].
}

void WebEditorClient::canceledComposition()
{
#if !PLATFORM(IOS)
    [[NSTextInputContext currentInputContext] discardMarkedText];
#endif
}

void WebEditorClient::didEndEditing()
{
#if !PLATFORM(IOS)
    [[NSNotificationCenter defaultCenter] postNotificationName:WebViewDidEndEditingNotification object:m_webView];
#else
    WebThreadPostNotification(WebViewDidEndEditingNotification, m_webView, nil);
#endif
}

void WebEditorClient::didWriteSelectionToPasteboard()
{
#if !PLATFORM(IOS)
    [[m_webView _editingDelegateForwarder] webView:m_webView didWriteSelectionToPasteboard:[NSPasteboard generalPasteboard]];
#endif
}

void WebEditorClient::willWriteSelectionToPasteboard(WebCore::Range*)
{
    // Not implemented WebKit, only WebKit2.
}

void WebEditorClient::getClientPasteboardDataForRange(WebCore::Range*, Vector<String>& pasteboardTypes, Vector<RefPtr<WebCore::SharedBuffer>>& pasteboardData)
{
    // Not implemented WebKit, only WebKit2.
}

NSString *WebEditorClient::userVisibleString(NSURL *URL)
{
    return [URL _web_userVisibleString];
}

NSURL *WebEditorClient::canonicalizeURL(NSURL *URL)
{
    return [URL _webkit_canonicalize];
}

NSURL *WebEditorClient::canonicalizeURLString(NSString *URLString)
{
    NSURL *URL = nil;
    if ([URLString _webkit_looksLikeAbsoluteURL])
        URL = [[NSURL _webkit_URLWithUserTypedString:URLString] _webkit_canonicalize];
    return URL;
}

static NSDictionary *attributesForAttributedStringConversion()
{
    NSArray *excludedElements = [[NSArray alloc] initWithObjects:
        // Omit style since we want style to be inline so the fragment can be easily inserted.
        @"style",
        // Omit xml so the result is not XHTML.
        @"xml",
        // Omit tags that will get stripped when converted to a fragment anyway.
        @"doctype", @"html", @"head", @"body", 
        // Omit deprecated tags.
        @"applet", @"basefont", @"center", @"dir", @"font", @"menu", @"s", @"strike", @"u",
        // Omit object so no file attachments are part of the fragment.
        @"object", nil];

#if PLATFORM(IOS)
    static NSString * const NSExcludedElementsDocumentAttribute = @"ExcludedElements";
#endif

    NSDictionary *dictionary = [NSDictionary dictionaryWithObject:excludedElements forKey:NSExcludedElementsDocumentAttribute];

    [excludedElements release];

    return dictionary;
}

void _WebCreateFragment(Document& document, NSAttributedString *string, FragmentAndResources& result)
{
    static NSDictionary *documentAttributes = [attributesForAttributedStringConversion() retain];
    NSArray *subresources;
    DOMDocumentFragment* fragment = [string _documentFromRange:NSMakeRange(0, [string length])
        document:kit(&document) documentAttributes:documentAttributes subresources:&subresources];
    result.fragment = core(fragment);
    for (WebResource* resource in subresources)
        result.resources.append([resource _coreResource]);
}

void WebEditorClient::setInsertionPasteboard(const String& pasteboardName)
{
#if !PLATFORM(IOS)
    NSPasteboard *pasteboard = pasteboardName.isEmpty() ? nil : [NSPasteboard pasteboardWithName:pasteboardName];
    [m_webView _setInsertionPasteboard:pasteboard];
#endif
}

#if USE(APPKIT)

void WebEditorClient::uppercaseWord()
{
    [m_webView uppercaseWord:nil];
}

void WebEditorClient::lowercaseWord()
{
    [m_webView lowercaseWord:nil];
}

void WebEditorClient::capitalizeWord()
{
    [m_webView capitalizeWord:nil];
}

#endif

#if USE(AUTOMATIC_TEXT_REPLACEMENT)

void WebEditorClient::showSubstitutionsPanel(bool show)
{
    NSPanel *spellingPanel = [[NSSpellChecker sharedSpellChecker] substitutionsPanel];
    if (show)
        [spellingPanel orderFront:nil];
    else
        [spellingPanel orderOut:nil];
}

bool WebEditorClient::substitutionsPanelIsShowing()
{
    return [[[NSSpellChecker sharedSpellChecker] substitutionsPanel] isVisible];
}

void WebEditorClient::toggleSmartInsertDelete()
{
    [m_webView toggleSmartInsertDelete:nil];
}

bool WebEditorClient::isAutomaticQuoteSubstitutionEnabled()
{
    return [m_webView isAutomaticQuoteSubstitutionEnabled];
}

void WebEditorClient::toggleAutomaticQuoteSubstitution()
{
    [m_webView toggleAutomaticQuoteSubstitution:nil];
}

bool WebEditorClient::isAutomaticLinkDetectionEnabled()
{
    return [m_webView isAutomaticLinkDetectionEnabled];
}

void WebEditorClient::toggleAutomaticLinkDetection()
{
    [m_webView toggleAutomaticLinkDetection:nil];
}

bool WebEditorClient::isAutomaticDashSubstitutionEnabled()
{
    return [m_webView isAutomaticDashSubstitutionEnabled];
}

void WebEditorClient::toggleAutomaticDashSubstitution()
{
    [m_webView toggleAutomaticDashSubstitution:nil];
}

bool WebEditorClient::isAutomaticTextReplacementEnabled()
{
    return [m_webView isAutomaticTextReplacementEnabled];
}

void WebEditorClient::toggleAutomaticTextReplacement()
{
    [m_webView toggleAutomaticTextReplacement:nil];
}

bool WebEditorClient::isAutomaticSpellingCorrectionEnabled()
{
    return [m_webView isAutomaticSpellingCorrectionEnabled];
}

void WebEditorClient::toggleAutomaticSpellingCorrection()
{
    [m_webView toggleAutomaticSpellingCorrection:nil];
}

#endif // USE(AUTOMATIC_TEXT_REPLACEMENT)

bool WebEditorClient::shouldInsertNode(Node *node, Range* replacingRange, EditorInsertAction givenAction)
{ 
    return [[m_webView _editingDelegateForwarder] webView:m_webView shouldInsertNode:kit(node) replacingDOMRange:kit(replacingRange) givenAction:(WebViewInsertAction)givenAction];
}

static NSString* undoNameForEditAction(EditAction editAction)
{
    // FIXME: This is identical to code in WebKit2's WebEditCommandProxy class; would be nice to share the strings instead of having two copies.
    switch (editAction) {
        case EditActionUnspecified: return nil;
        case EditActionInsert: return nil;
        case EditActionInsertReplacement: return nil;
        case EditActionInsertFromDrop: return nil;
        case EditActionSetColor: return UI_STRING_KEY_INTERNAL("Set Color", "Set Color (Undo action name)", "Undo action name");
        case EditActionSetBackgroundColor: return UI_STRING_KEY_INTERNAL("Set Background Color", "Set Background Color (Undo action name)", "Undo action name");
        case EditActionTurnOffKerning: return UI_STRING_KEY_INTERNAL("Turn Off Kerning", "Turn Off Kerning (Undo action name)", "Undo action name");
        case EditActionTightenKerning: return UI_STRING_KEY_INTERNAL("Tighten Kerning", "Tighten Kerning (Undo action name)", "Undo action name");
        case EditActionLoosenKerning: return UI_STRING_KEY_INTERNAL("Loosen Kerning", "Loosen Kerning (Undo action name)", "Undo action name");
        case EditActionUseStandardKerning: return UI_STRING_KEY_INTERNAL("Use Standard Kerning", "Use Standard Kerning (Undo action name)", "Undo action name");
        case EditActionTurnOffLigatures: return UI_STRING_KEY_INTERNAL("Turn Off Ligatures", "Turn Off Ligatures (Undo action name)", "Undo action name");
        case EditActionUseStandardLigatures: return UI_STRING_KEY_INTERNAL("Use Standard Ligatures", "Use Standard Ligatures (Undo action name)", "Undo action name");
        case EditActionUseAllLigatures: return UI_STRING_KEY_INTERNAL("Use All Ligatures", "Use All Ligatures (Undo action name)", "Undo action name");
        case EditActionRaiseBaseline: return UI_STRING_KEY_INTERNAL("Raise Baseline", "Raise Baseline (Undo action name)", "Undo action name");
        case EditActionLowerBaseline: return UI_STRING_KEY_INTERNAL("Lower Baseline", "Lower Baseline (Undo action name)", "Undo action name");
        case EditActionSetTraditionalCharacterShape: return UI_STRING_KEY_INTERNAL("Set Traditional Character Shape", "Set Traditional Character Shape (Undo action name)", "Undo action name");
        case EditActionSetFont: return UI_STRING_KEY_INTERNAL("Set Font", "Set Font (Undo action name)", "Undo action name");
        case EditActionChangeAttributes: return UI_STRING_KEY_INTERNAL("Change Attributes", "Change Attributes (Undo action name)", "Undo action name");
        case EditActionAlignLeft: return UI_STRING_KEY_INTERNAL("Align Left", "Align Left (Undo action name)", "Undo action name");
        case EditActionAlignRight: return UI_STRING_KEY_INTERNAL("Align Right", "Align Right (Undo action name)", "Undo action name");
        case EditActionCenter: return UI_STRING_KEY_INTERNAL("Center", "Center (Undo action name)", "Undo action name");
        case EditActionJustify: return UI_STRING_KEY_INTERNAL("Justify", "Justify (Undo action name)", "Undo action name");
        case EditActionSetWritingDirection: return UI_STRING_KEY_INTERNAL("Set Writing Direction", "Set Writing Direction (Undo action name)", "Undo action name");
        case EditActionSubscript: return UI_STRING_KEY_INTERNAL("Subscript", "Subscript (Undo action name)", "Undo action name");
        case EditActionSuperscript: return UI_STRING_KEY_INTERNAL("Superscript", "Superscript (Undo action name)", "Undo action name");
        case EditActionUnderline: return UI_STRING_KEY_INTERNAL("Underline", "Underline (Undo action name)", "Undo action name");
        case EditActionOutline: return UI_STRING_KEY_INTERNAL("Outline", "Outline (Undo action name)", "Undo action name");
        case EditActionUnscript: return UI_STRING_KEY_INTERNAL("Unscript", "Unscript (Undo action name)", "Undo action name");
        case EditActionDeleteByDrag: return UI_STRING_KEY_INTERNAL("Drag", "Drag (Undo action name)", "Undo action name");
        case EditActionCut: return UI_STRING_KEY_INTERNAL("Cut", "Cut (Undo action name)", "Undo action name");
        case EditActionPaste: return UI_STRING_KEY_INTERNAL("Paste", "Paste (Undo action name)", "Undo action name");
        case EditActionPasteFont: return UI_STRING_KEY_INTERNAL("Paste Font", "Paste Font (Undo action name)", "Undo action name");
        case EditActionPasteRuler: return UI_STRING_KEY_INTERNAL("Paste Ruler", "Paste Ruler (Undo action name)", "Undo action name");
        case EditActionTypingDeleteSelection:
        case EditActionTypingDeleteBackward:
        case EditActionTypingDeleteForward:
        case EditActionTypingDeleteWordBackward:
        case EditActionTypingDeleteWordForward:
        case EditActionTypingDeleteLineBackward:
        case EditActionTypingDeleteLineForward:
        case EditActionTypingDeletePendingComposition:
        case EditActionTypingDeleteFinalComposition:
        case EditActionTypingInsertText:
        case EditActionTypingInsertLineBreak:
        case EditActionTypingInsertParagraph:
        case EditActionTypingInsertPendingComposition:
        case EditActionTypingInsertFinalComposition:
            return UI_STRING_KEY_INTERNAL("Typing", "Typing (Undo action name)", "Undo action name");
        case EditActionCreateLink: return UI_STRING_KEY_INTERNAL("Create Link", "Create Link (Undo action name)", "Undo action name");
        case EditActionUnlink: return UI_STRING_KEY_INTERNAL("Unlink", "Unlink (Undo action name)", "Undo action name");
        case EditActionInsertOrderedList:
        case EditActionInsertUnorderedList:
            return UI_STRING_KEY_INTERNAL("Insert List", "Insert List (Undo action name)", "Undo action name");
        case EditActionFormatBlock: return UI_STRING_KEY_INTERNAL("Formatting", "Format Block (Undo action name)", "Undo action name");
        case EditActionIndent: return UI_STRING_KEY_INTERNAL("Indent", "Indent (Undo action name)", "Undo action name");
        case EditActionOutdent: return UI_STRING_KEY_INTERNAL("Outdent", "Outdent (Undo action name)", "Undo action name");
        case EditActionBold: return UI_STRING_KEY_INTERNAL("Bold", "Bold (Undo action name)", "Undo action name");
        case EditActionItalics: return UI_STRING_KEY_INTERNAL("Italics", "Italics (Undo action name)", "Undo action name");
        case EditActionDelete: return UI_STRING_KEY_INTERNAL("Delete", "Delete (Undo action name)", "Undo action name");
        case EditActionDictation: return UI_STRING_KEY_INTERNAL("Dictation", "Dictation (Undo action name)", "Undo action name");
    }
    return nil;
}

void WebEditorClient::registerUndoOrRedoStep(UndoStep& step, bool isRedo)
{
    NSUndoManager *undoManager = [m_webView undoManager];

#if PLATFORM(IOS)
    // While we are undoing, we shouldn't be asked to register another Undo operation, we shouldn't even be touching the DOM.
    // But just in case this happens, return to avoid putting the undo manager into an inconsistent state.
    // Same for being asked to register a Redo operation in the midst of another Redo.
    if (([undoManager isUndoing] && !isRedo) || ([undoManager isRedoing] && isRedo))
        return;
#endif

    NSString *actionName = undoNameForEditAction(step.editingAction());
    WebUndoStep *webEntry = [WebUndoStep stepWithUndoStep:step];
    [undoManager registerUndoWithTarget:m_undoTarget.get() selector:(isRedo ? @selector(redoEditing:) : @selector(undoEditing:)) object:webEntry];
    if (actionName)
        [undoManager setActionName:actionName];
    m_haveUndoRedoOperations = YES;
}

void WebEditorClient::updateEditorStateAfterLayoutIfEditabilityChanged()
{
    // FIXME: We should update EditorStateIsContentEditable to track whether the state is richly
    // editable or plainttext-only.
    if (m_lastEditorStateWasContentEditable == EditorStateIsContentEditable::Unset)
        return;

    Frame* frame = core([m_webView _selectedOrMainFrame]);
    if (!frame)
        return;

    NSView<WebDocumentView> *documentView = [[kit(frame) frameView] documentView];
    if (![documentView isKindOfClass:[WebHTMLView class]])
        return;

    EditorStateIsContentEditable editorStateIsContentEditable = [(WebHTMLView *)documentView _isEditable] ? EditorStateIsContentEditable::Yes : EditorStateIsContentEditable::No;
    if (m_lastEditorStateWasContentEditable != editorStateIsContentEditable)
        [m_webView updateTouchBar];
}

void WebEditorClient::registerUndoStep(UndoStep& cmd)
{
    registerUndoOrRedoStep(cmd, false);
}

void WebEditorClient::registerRedoStep(UndoStep& cmd)
{
    registerUndoOrRedoStep(cmd, true);
}

void WebEditorClient::clearUndoRedoOperations()
{
    if (m_haveUndoRedoOperations) {
        // workaround for <rdar://problem/4645507> NSUndoManager dies
        // with uncaught exception when undo items cleared while
        // groups are open
        NSUndoManager *undoManager = [m_webView undoManager];
        int groupingLevel = [undoManager groupingLevel];
        for (int i = 0; i < groupingLevel; ++i)
            [undoManager endUndoGrouping];
        
        [undoManager removeAllActionsWithTarget:m_undoTarget.get()];
        
        for (int i = 0; i < groupingLevel; ++i)
            [undoManager beginUndoGrouping];
        
        m_haveUndoRedoOperations = NO;
    }    
}

bool WebEditorClient::canCopyCut(Frame*, bool defaultValue) const
{
    return defaultValue;
}

bool WebEditorClient::canPaste(Frame*, bool defaultValue) const
{
    return defaultValue;
}

bool WebEditorClient::canUndo() const
{
    return [[m_webView undoManager] canUndo];
}

bool WebEditorClient::canRedo() const
{
    return [[m_webView undoManager] canRedo];
}

void WebEditorClient::undo()
{
    if (canUndo())
        [[m_webView undoManager] undo];
}

void WebEditorClient::redo()
{
    if (canRedo())
        [[m_webView undoManager] redo];    
}

void WebEditorClient::handleKeyboardEvent(KeyboardEvent* event)
{
    Frame* frame = event->target()->toNode()->document().frame();
#if !PLATFORM(IOS)
    WebHTMLView *webHTMLView = [[kit(frame) frameView] documentView];
    if ([webHTMLView _interpretKeyEvent:event savingCommands:NO])
        event->setDefaultHandled();
#else
    WebHTMLView *webHTMLView = (WebHTMLView *)[[kit(frame) frameView] documentView];
    if ([webHTMLView _handleEditingKeyEvent:event])
        event->setDefaultHandled();
#endif
}

void WebEditorClient::handleInputMethodKeydown(KeyboardEvent* event)
{
#if !PLATFORM(IOS)
    // FIXME: Switch to WebKit2 model, interpreting the event before it's sent down to WebCore.
    Frame* frame = event->target()->toNode()->document().frame();
    WebHTMLView *webHTMLView = [[kit(frame) frameView] documentView];
    if ([webHTMLView _interpretKeyEvent:event savingCommands:YES])
        event->setDefaultHandled();
#else
    // iOS does not use input manager this way
#endif
}

#define FormDelegateLog(ctrl)  LOG(FormDelegate, "control=%@", ctrl)

void WebEditorClient::textFieldDidBeginEditing(Element* element)
{
    if (!is<HTMLInputElement>(*element))
        return;

    DOMHTMLInputElement* inputElement = kit(downcast<HTMLInputElement>(element));
    FormDelegateLog(inputElement);
    CallFormDelegate(m_webView, @selector(textFieldDidBeginEditing:inFrame:), inputElement, kit(element->document().frame()));
}

void WebEditorClient::textFieldDidEndEditing(Element* element)
{
    if (!is<HTMLInputElement>(*element))
        return;

    DOMHTMLInputElement* inputElement = kit(downcast<HTMLInputElement>(element));
    FormDelegateLog(inputElement);
    CallFormDelegate(m_webView, @selector(textFieldDidEndEditing:inFrame:), inputElement, kit(element->document().frame()));
}

void WebEditorClient::textDidChangeInTextField(Element* element)
{
    if (!is<HTMLInputElement>(*element))
        return;

#if !PLATFORM(IOS)
    if (!UserTypingGestureIndicator::processingUserTypingGesture() || UserTypingGestureIndicator::focusedElementAtGestureStart() != element)
        return;
#endif

    DOMHTMLInputElement* inputElement = kit(downcast<HTMLInputElement>(element));
    FormDelegateLog(inputElement);
    CallFormDelegate(m_webView, @selector(textDidChangeInTextField:inFrame:), inputElement, kit(element->document().frame()));
}

static SEL selectorForKeyEvent(KeyboardEvent* event)
{
    // FIXME: This helper function is for the auto-fill code so we can pass a selector to the form delegate.  
    // Eventually, we should move all of the auto-fill code down to WebKit and remove the need for this function by
    // not relying on the selector in the new implementation.
    // The key identifiers are from <http://www.w3.org/TR/DOM-Level-3-Events/keyset.html#KeySet-Set>
    const String& key = event->keyIdentifier();
    if (key == "Up")
        return @selector(moveUp:);
    if (key == "Down")
        return @selector(moveDown:);
    if (key == "U+001B")
        return @selector(cancel:);
    if (key == "U+0009") {
        if (event->shiftKey())
            return @selector(insertBacktab:);
        return @selector(insertTab:);
    }
    if (key == "Enter")
        return @selector(insertNewline:);
    return 0;
}

bool WebEditorClient::doTextFieldCommandFromEvent(Element* element, KeyboardEvent* event)
{
    if (!is<HTMLInputElement>(*element))
        return NO;

    DOMHTMLInputElement* inputElement = kit(downcast<HTMLInputElement>(element));
    FormDelegateLog(inputElement);
    if (SEL commandSelector = selectorForKeyEvent(event))
        return CallFormDelegateReturningBoolean(NO, m_webView, @selector(textField:doCommandBySelector:inFrame:), inputElement, commandSelector, kit(element->document().frame()));
    return NO;
}

void WebEditorClient::textWillBeDeletedInTextField(Element* element)
{
    if (!is<HTMLInputElement>(*element))
        return;

    DOMHTMLInputElement* inputElement = kit(downcast<HTMLInputElement>(element));
    FormDelegateLog(inputElement);
    // We're using the deleteBackward selector for all deletion operations since the autofill code treats all deletions the same way.
    CallFormDelegateReturningBoolean(NO, m_webView, @selector(textField:doCommandBySelector:inFrame:), inputElement, @selector(deleteBackward:), kit(element->document().frame()));
}

void WebEditorClient::textDidChangeInTextArea(Element* element)
{
    if (!is<HTMLTextAreaElement>(*element))
        return;

    DOMHTMLTextAreaElement* textAreaElement = kit(downcast<HTMLTextAreaElement>(element));
    FormDelegateLog(textAreaElement);
    CallFormDelegate(m_webView, @selector(textDidChangeInTextArea:inFrame:), textAreaElement, kit(element->document().frame()));
}

#if PLATFORM(IOS)

void WebEditorClient::writeDataToPasteboard(NSDictionary* representation)
{
    if ([[m_webView _UIKitDelegateForwarder] respondsToSelector:@selector(writeDataToPasteboard:)])
        [[m_webView _UIKitDelegateForwarder] writeDataToPasteboard:representation];
}

NSArray *WebEditorClient::supportedPasteboardTypesForCurrentSelection()
{
    if ([[m_webView _UIKitDelegateForwarder] respondsToSelector:@selector(supportedPasteboardTypesForCurrentSelection)]) 
        return [[m_webView _UIKitDelegateForwarder] supportedPasteboardTypesForCurrentSelection]; 

    return nil; 
}

NSArray *WebEditorClient::readDataFromPasteboard(NSString* type, int index)
{
    if ([[m_webView _UIKitDelegateForwarder] respondsToSelector:@selector(readDataFromPasteboard:withIndex:)])
        return [[m_webView _UIKitDelegateForwarder] readDataFromPasteboard:type withIndex:index];
    
    return nil;
}

bool WebEditorClient::hasRichlyEditableSelection()
{
    if ([[m_webView _UIKitDelegateForwarder] respondsToSelector:@selector(hasRichlyEditableSelection)])
        return [[m_webView _UIKitDelegateForwarder] hasRichlyEditableSelection];
    
    return false;
}

int WebEditorClient::getPasteboardItemsCount()
{
    if ([[m_webView _UIKitDelegateForwarder] respondsToSelector:@selector(getPasteboardItemsCount)])
        return [[m_webView _UIKitDelegateForwarder] getPasteboardItemsCount];
    
    return 0;
}

RefPtr<WebCore::DocumentFragment> WebEditorClient::documentFragmentFromDelegate(int index)
{
    if ([[m_webView _editingDelegateForwarder] respondsToSelector:@selector(documentFragmentForPasteboardItemAtIndex:)]) {
        DOMDocumentFragment *fragmentFromDelegate = [[m_webView _editingDelegateForwarder] documentFragmentForPasteboardItemAtIndex:index];
        if (fragmentFromDelegate)
            return core(fragmentFromDelegate);
    }
    
    return nullptr;
}

bool WebEditorClient::performsTwoStepPaste(WebCore::DocumentFragment* fragment)
{
    if ([[m_webView _UIKitDelegateForwarder] respondsToSelector:@selector(performsTwoStepPaste:)])
        return [[m_webView _UIKitDelegateForwarder] performsTwoStepPaste:kit(fragment)];

    return false;
}

int WebEditorClient::pasteboardChangeCount()
{
    if ([[m_webView _UIKitDelegateForwarder] respondsToSelector:@selector(getPasteboardChangeCount)])
        return [[m_webView _UIKitDelegateForwarder] getPasteboardChangeCount];
    
    return 0;
}

Vector<TextCheckingResult> WebEditorClient::checkTextOfParagraph(StringView string, TextCheckingTypeMask checkingTypes, const VisibleSelection&)
{
    ASSERT(checkingTypes & NSTextCheckingTypeSpelling);

    Vector<TextCheckingResult> results;

    NSArray *incomingResults = [[m_webView _UIKitDelegateForwarder] checkSpellingOfString:string.createNSStringWithoutCopying().get()];
    for (NSValue *incomingResult in incomingResults) {
        NSRange resultRange = [incomingResult rangeValue];
        ASSERT(resultRange.location != NSNotFound && resultRange.length > 0);
        TextCheckingResult result;
        result.type = TextCheckingTypeSpelling;
        result.location = resultRange.location;
        result.length = resultRange.length;
        results.append(result);
    }

    return results;
}

#endif // PLATFORM(IOS)

#if !PLATFORM(IOS)

bool WebEditorClient::shouldEraseMarkersAfterChangeSelection(TextCheckingType type) const
{
    // This prevents erasing spelling markers on OS X Lion or later to match AppKit on these Mac OS X versions.
    return type != TextCheckingTypeSpelling;
}

void WebEditorClient::ignoreWordInSpellDocument(const String& text)
{
    [[NSSpellChecker sharedSpellChecker] ignoreWord:text inSpellDocumentWithTag:spellCheckerDocumentTag()];
}

void WebEditorClient::learnWord(const String& text)
{
    [[NSSpellChecker sharedSpellChecker] learnWord:text];
}

void WebEditorClient::checkSpellingOfString(StringView text, int* misspellingLocation, int* misspellingLength)
{
    NSRange range = [[NSSpellChecker sharedSpellChecker] checkSpellingOfString:text.createNSStringWithoutCopying().get() startingAt:0 language:nil wrap:NO inSpellDocumentWithTag:spellCheckerDocumentTag() wordCount:NULL];

    if (misspellingLocation) {
        // WebCore expects -1 to represent "not found"
        if (range.location == NSNotFound)
            *misspellingLocation = -1;
        else
            *misspellingLocation = range.location;
    }
    
    if (misspellingLength)
        *misspellingLength = range.length;
}

String WebEditorClient::getAutoCorrectSuggestionForMisspelledWord(const String& inputWord)
{
    // This method can be implemented using customized algorithms for the particular browser.
    // Currently, it computes an empty string.
    return String();
}

void WebEditorClient::checkGrammarOfString(StringView text, Vector<GrammarDetail>& details, int* badGrammarLocation, int* badGrammarLength)
{
    NSArray *grammarDetails;
    NSRange range = [[NSSpellChecker sharedSpellChecker] checkGrammarOfString:text.createNSStringWithoutCopying().get() startingAt:0 language:nil wrap:NO inSpellDocumentWithTag:spellCheckerDocumentTag() details:&grammarDetails];
    if (badGrammarLocation)
        // WebCore expects -1 to represent "not found"
        *badGrammarLocation = (range.location == NSNotFound) ? -1 : static_cast<int>(range.location);
    if (badGrammarLength)
        *badGrammarLength = range.length;
    for (NSDictionary *detail in grammarDetails) {
        ASSERT(detail);
        GrammarDetail grammarDetail;
        NSValue *detailRangeAsNSValue = [detail objectForKey:NSGrammarRange];
        ASSERT(detailRangeAsNSValue);
        NSRange detailNSRange = [detailRangeAsNSValue rangeValue];
        ASSERT(detailNSRange.location != NSNotFound);
        ASSERT(detailNSRange.length > 0);
        grammarDetail.location = detailNSRange.location;
        grammarDetail.length = detailNSRange.length;
        grammarDetail.userDescription = [detail objectForKey:NSGrammarUserDescription];
        NSArray *guesses = [detail objectForKey:NSGrammarCorrections];
        for (NSString *guess in guesses)
            grammarDetail.guesses.append(String(guess));
        details.append(grammarDetail);
    }
}

static Vector<TextCheckingResult> core(NSArray *incomingResults, TextCheckingTypeMask checkingTypes)
{
    Vector<TextCheckingResult> results;

    for (NSTextCheckingResult *incomingResult in incomingResults) {
        NSRange resultRange = [incomingResult range];
        NSTextCheckingType resultType = [incomingResult resultType];
        ASSERT(resultRange.location != NSNotFound);
        ASSERT(resultRange.length > 0);
        if (NSTextCheckingTypeSpelling == resultType && 0 != (checkingTypes & NSTextCheckingTypeSpelling)) {
            TextCheckingResult result;
            result.type = TextCheckingTypeSpelling;
            result.location = resultRange.location;
            result.length = resultRange.length;
            results.append(result);
        } else if (NSTextCheckingTypeGrammar == resultType && 0 != (checkingTypes & NSTextCheckingTypeGrammar)) {
            TextCheckingResult result;
            NSArray *details = [incomingResult grammarDetails];
            result.type = TextCheckingTypeGrammar;
            result.location = resultRange.location;
            result.length = resultRange.length;
            for (NSDictionary *incomingDetail in details) {
                ASSERT(incomingDetail);
                GrammarDetail detail;
                NSValue *detailRangeAsNSValue = [incomingDetail objectForKey:NSGrammarRange];
                ASSERT(detailRangeAsNSValue);
                NSRange detailNSRange = [detailRangeAsNSValue rangeValue];
                ASSERT(detailNSRange.location != NSNotFound);
                ASSERT(detailNSRange.length > 0);
                detail.location = detailNSRange.location;
                detail.length = detailNSRange.length;
                detail.userDescription = [incomingDetail objectForKey:NSGrammarUserDescription];
                NSArray *guesses = [incomingDetail objectForKey:NSGrammarCorrections];
                for (NSString *guess in guesses)
                    detail.guesses.append(String(guess));
                result.details.append(detail);
            }
            results.append(result);
        } else if (NSTextCheckingTypeLink == resultType && 0 != (checkingTypes & NSTextCheckingTypeLink)) {
            TextCheckingResult result;
            result.type = TextCheckingTypeLink;
            result.location = resultRange.location;
            result.length = resultRange.length;
            result.replacement = [[incomingResult URL] absoluteString];
            results.append(result);
        } else if (NSTextCheckingTypeQuote == resultType && 0 != (checkingTypes & NSTextCheckingTypeQuote)) {
            TextCheckingResult result;
            result.type = TextCheckingTypeQuote;
            result.location = resultRange.location;
            result.length = resultRange.length;
            result.replacement = [incomingResult replacementString];
            results.append(result);
        } else if (NSTextCheckingTypeDash == resultType && 0 != (checkingTypes & NSTextCheckingTypeDash)) {
            TextCheckingResult result;
            result.type = TextCheckingTypeDash;
            result.location = resultRange.location;
            result.length = resultRange.length;
            result.replacement = [incomingResult replacementString];
            results.append(result);
        } else if (NSTextCheckingTypeReplacement == resultType && 0 != (checkingTypes & NSTextCheckingTypeReplacement)) {
            TextCheckingResult result;
            result.type = TextCheckingTypeReplacement;
            result.location = resultRange.location;
            result.length = resultRange.length;
            result.replacement = [incomingResult replacementString];
            results.append(result);
        } else if (NSTextCheckingTypeCorrection == resultType && 0 != (checkingTypes & NSTextCheckingTypeCorrection)) {
            TextCheckingResult result;
            result.type = TextCheckingTypeCorrection;
            result.location = resultRange.location;
            result.length = resultRange.length;
            result.replacement = [incomingResult replacementString];
            results.append(result);
        }
    }

    return results;
}

#if HAVE(ADVANCED_SPELL_CHECKING)
static int insertionPointFromCurrentSelection(const VisibleSelection& currentSelection)
{
    VisiblePosition selectionStart = currentSelection.visibleStart();
    VisiblePosition paragraphStart = startOfParagraph(selectionStart);
    return TextIterator::rangeLength(makeRange(paragraphStart, selectionStart).get());
}
#endif

Vector<TextCheckingResult> WebEditorClient::checkTextOfParagraph(StringView string, TextCheckingTypeMask checkingTypes, const VisibleSelection& currentSelection)
{
    NSDictionary *options = nil;
#if HAVE(ADVANCED_SPELL_CHECKING)
    options = @{ NSTextCheckingInsertionPointKey :  [NSNumber numberWithUnsignedInteger:insertionPointFromCurrentSelection(currentSelection)] };
#endif
    return core([[NSSpellChecker sharedSpellChecker] checkString:string.createNSStringWithoutCopying().get() range:NSMakeRange(0, string.length()) types:(checkingTypes | NSTextCheckingTypeOrthography) options:options inSpellDocumentWithTag:spellCheckerDocumentTag() orthography:NULL wordCount:NULL], checkingTypes);
}

void WebEditorClient::updateSpellingUIWithGrammarString(const String& badGrammarPhrase, const GrammarDetail& grammarDetail)
{
    NSMutableArray* corrections = [NSMutableArray array];
    for (unsigned i = 0; i < grammarDetail.guesses.size(); i++) {
        NSString* guess = grammarDetail.guesses[i];
        [corrections addObject:guess];
    }
    NSRange grammarRange = NSMakeRange(grammarDetail.location, grammarDetail.length);
    NSString* grammarUserDescription = grammarDetail.userDescription;
    NSDictionary* grammarDetailDict = [NSDictionary dictionaryWithObjectsAndKeys:[NSValue valueWithRange:grammarRange], NSGrammarRange, grammarUserDescription, NSGrammarUserDescription, corrections, NSGrammarCorrections, nil];
    
    [[NSSpellChecker sharedSpellChecker] updateSpellingPanelWithGrammarString:badGrammarPhrase detail:grammarDetailDict];
}

void WebEditorClient::updateSpellingUIWithMisspelledWord(const String& misspelledWord)
{
    [[NSSpellChecker sharedSpellChecker] updateSpellingPanelWithMisspelledWord:misspelledWord];
}

void WebEditorClient::showSpellingUI(bool show)
{
    NSPanel *spellingPanel = [[NSSpellChecker sharedSpellChecker] spellingPanel];
    if (show)
        [spellingPanel orderFront:nil];
    else
        [spellingPanel orderOut:nil];
}

bool WebEditorClient::spellingUIIsShowing()
{
    return [[[NSSpellChecker sharedSpellChecker] spellingPanel] isVisible];
}

void WebEditorClient::getGuessesForWord(const String& word, const String& context, const WebCore::VisibleSelection& currentSelection, Vector<String>& guesses)
{
    guesses.clear();
    NSString* language = nil;
    NSOrthography* orthography = nil;
    NSSpellChecker *checker = [NSSpellChecker sharedSpellChecker];
    NSDictionary *options = nil;
#if HAVE(ADVANCED_SPELL_CHECKING)
    options = @{ NSTextCheckingInsertionPointKey :  [NSNumber numberWithUnsignedInteger:insertionPointFromCurrentSelection(currentSelection)] };
#endif
    if (context.length()) {
        [checker checkString:context range:NSMakeRange(0, context.length()) types:NSTextCheckingTypeOrthography options:options inSpellDocumentWithTag:spellCheckerDocumentTag() orthography:&orthography wordCount:0];
        language = [checker languageForWordRange:NSMakeRange(0, context.length()) inString:context orthography:orthography];
    }
    NSArray* stringsArray = [checker guessesForWordRange:NSMakeRange(0, word.length()) inString:word language:language inSpellDocumentWithTag:spellCheckerDocumentTag()];
    unsigned count = [stringsArray count];

    if (count > 0) {
        NSEnumerator* enumerator = [stringsArray objectEnumerator];
        NSString* string;
        while ((string = [enumerator nextObject]) != nil)
            guesses.append(string);
    }
}

#endif // !PLATFORM(IOS)

void WebEditorClient::willSetInputMethodState()
{
}

void WebEditorClient::setInputMethodState(bool)
{
}

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200

void WebEditorClient::requestCandidatesForSelection(const VisibleSelection& selection)
{
    if (![m_webView shouldRequestCandidates])
        return;

    RefPtr<Range> selectedRange = selection.toNormalizedRange();
    if (!selectedRange)
        return;
    
    Frame* frame = core([m_webView _selectedOrMainFrame]);
    if (!frame)
        return;

    m_lastSelectionForRequestedCandidates = selection;

#if HAVE(ADVANCED_SPELL_CHECKING)
    VisiblePosition selectionStart = selection.visibleStart();
    VisiblePosition selectionEnd = selection.visibleEnd();
    VisiblePosition paragraphStart = startOfParagraph(selectionStart);
    VisiblePosition paragraphEnd = endOfParagraph(selectionEnd);

    int lengthToSelectionStart = TextIterator::rangeLength(makeRange(paragraphStart, selectionStart).get());
    int lengthToSelectionEnd = TextIterator::rangeLength(makeRange(paragraphStart, selectionEnd).get());
    m_rangeForCandidates = NSMakeRange(lengthToSelectionStart, lengthToSelectionEnd - lengthToSelectionStart);
    m_paragraphContextForCandidateRequest = plainText(frame->editor().contextRangeForCandidateRequest().get());

    NSTextCheckingTypes checkingTypes = NSTextCheckingTypeSpelling | NSTextCheckingTypeReplacement | NSTextCheckingTypeCorrection;
    auto weakEditor = m_weakPtrFactory.createWeakPtr();
    m_lastCandidateRequestSequenceNumber = [[NSSpellChecker sharedSpellChecker] requestCandidatesForSelectedRange:m_rangeForCandidates inString:m_paragraphContextForCandidateRequest.get() types:checkingTypes options:nil inSpellDocumentWithTag:spellCheckerDocumentTag() completionHandler:[weakEditor](NSInteger sequenceNumber, NSArray<NSTextCheckingResult *> *candidates) {
        dispatch_async(dispatch_get_main_queue(), ^{
            if (!weakEditor)
                return;
            weakEditor->handleRequestedCandidates(sequenceNumber, candidates);
        });
    }];
#endif // HAVE(ADVANCED_SPELL_CHECKING)
}

void WebEditorClient::handleRequestedCandidates(NSInteger sequenceNumber, NSArray<NSTextCheckingResult *> *candidates)
{
    if (![m_webView shouldRequestCandidates])
        return;

    if (m_lastCandidateRequestSequenceNumber != sequenceNumber)
        return;

    Frame* frame = core([m_webView _selectedOrMainFrame]);
    if (!frame)
        return;

    const VisibleSelection& selection = frame->selection().selection();
    if (selection != m_lastSelectionForRequestedCandidates)
        return;

    RefPtr<Range> selectedRange = selection.toNormalizedRange();
    if (!selectedRange)
        return;

    IntRect rectForSelectionCandidates;
    Vector<FloatQuad> quads;
    selectedRange->absoluteTextQuads(quads);
    if (!quads.isEmpty())
        rectForSelectionCandidates = frame->view()->contentsToWindow(quads[0].enclosingBoundingBox());

    [m_webView showCandidates:candidates forString:m_paragraphContextForCandidateRequest.get() inRect:rectForSelectionCandidates forSelectedRange:m_rangeForCandidates view:m_webView completionHandler:nil];
}

void WebEditorClient::handleAcceptedCandidateWithSoftSpaces(TextCheckingResult acceptedCandidate)
{
    Frame* frame = core([m_webView _selectedOrMainFrame]);
    if (!frame)
        return;

    const VisibleSelection& selection = frame->selection().selection();
    if (selection != m_lastSelectionForRequestedCandidates)
        return;

    NSView <WebDocumentView> *view = [[[m_webView selectedFrame] frameView] documentView];
    if ([view isKindOfClass:[WebHTMLView class]]) {
        unsigned replacementLength = acceptedCandidate.replacement.length();
        if (replacementLength > 0) {
            NSRange replacedRange = NSMakeRange(acceptedCandidate.location, replacementLength);
            NSRange softSpaceRange = NSMakeRange(NSMaxRange(replacedRange) - 1, 1);
            if (acceptedCandidate.replacement.endsWith(" "))
                [(WebHTMLView *)view _setSoftSpaceRange:softSpaceRange];
        }
    }

    frame->editor().handleAcceptedCandidate(acceptedCandidate);
}

#endif // PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200

#if !PLATFORM(IOS)

@interface WebEditorSpellCheckResponder : NSObject
{
    WebEditorClient* _client;
    int _sequence;
    RetainPtr<NSArray> _results;
}
- (id)initWithClient:(WebEditorClient*)client sequence:(int)sequence results:(NSArray*)results;
- (void)perform;
@end

@implementation WebEditorSpellCheckResponder
- (id)initWithClient:(WebEditorClient*)client sequence:(int)sequence results:(NSArray*)results
{
    self = [super init];
    if (!self)
        return nil;
    _client = client;
    _sequence = sequence;
    _results = results;
    return self;
}

- (void)perform
{
    _client->didCheckSucceed(_sequence, _results.get());
}

@end

void WebEditorClient::didCheckSucceed(int sequence, NSArray* results)
{
    ASSERT_UNUSED(sequence, sequence == m_textCheckingRequest->data().sequence());
    m_textCheckingRequest->didSucceed(core(results, m_textCheckingRequest->data().mask()));
    m_textCheckingRequest = nullptr;
}

#endif

void WebEditorClient::requestCheckingOfString(WebCore::TextCheckingRequest& request, const VisibleSelection& currentSelection)
{
#if !PLATFORM(IOS)
    ASSERT(!m_textCheckingRequest);
    m_textCheckingRequest = &request;

    int sequence = m_textCheckingRequest->data().sequence();
    NSRange range = NSMakeRange(0, m_textCheckingRequest->data().text().length());
    NSRunLoop* currentLoop = [NSRunLoop currentRunLoop];
    NSDictionary *options = nil;
#if HAVE(ADVANCED_SPELL_CHECKING)
    options = @{ NSTextCheckingInsertionPointKey :  [NSNumber numberWithUnsignedInteger:insertionPointFromCurrentSelection(currentSelection)] };
#endif
    [[NSSpellChecker sharedSpellChecker] requestCheckingOfString:m_textCheckingRequest->data().text() range:range types:NSTextCheckingAllSystemTypes options:options inSpellDocumentWithTag:0 completionHandler:^(NSInteger, NSArray* results, NSOrthography*, NSInteger) {
            [currentLoop performSelector:@selector(perform) 
                                  target:[[[WebEditorSpellCheckResponder alloc] initWithClient:this sequence:sequence results:results] autorelease]
                                argument:nil order:0 modes:[NSArray arrayWithObject:NSDefaultRunLoopMode]];
        }];
#endif
}
