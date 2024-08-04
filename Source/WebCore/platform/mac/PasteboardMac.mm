/*
 * Copyright (C) 2006, 2013 Apple Inc. All rights reserved.
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

#import "config.h"
#import "Pasteboard.h"

#import "CachedImage.h"
#import "Document.h"
#import "DocumentFragment.h"
#import "DocumentLoader.h"
#import "DragData.h"
#import "Editor.h"
#import "EditorClient.h"
#import "Frame.h"
#import "FrameView.h"
#import "FrameLoaderClient.h"
#import "HitTestResult.h"
#import "htmlediting.h"
#import "Image.h"
#import "URL.h"
#import "LegacyWebArchive.h"
#import "LoaderNSURLExtras.h"
#import "MIMETypeRegistry.h"
#import "PasteboardStrategy.h"
#import "PlatformStrategies.h"
#import "RenderImage.h"
#import "Text.h"
#import "WebCoreNSStringExtras.h"
#import "WebNSAttributedStringExtras.h"
#import "markup.h"
#import <wtf/StdLibExtras.h>
#import <wtf/RetainPtr.h>
#import <wtf/text/StringBuilder.h>
#import <wtf/unicode/CharacterNames.h>

namespace WebCore {

const char* const WebArchivePboardType = "Apple Web Archive pasteboard type";
const char* const WebURLNamePboardType = "public.url-name";

const char WebSmartPastePboardType[] = "NeXT smart paste pasteboard type";
const char WebURLPboardType[] = "public.url";
const char WebURLsWithTitlesPboardType[] = "WebURLsWithTitlesPboardType";

// Making this non-inline so that WebKit 2's decoding doesn't have to include SharedBuffer.h.
PasteboardWebContent::PasteboardWebContent()
{
}

PasteboardWebContent::~PasteboardWebContent()
{
}

// Making this non-inline so that WebKit 2's decoding doesn't have to include Image.h.
PasteboardImage::PasteboardImage()
{
}

PasteboardImage::~PasteboardImage()
{
}

static const Vector<String> writableTypesForURL()
{
    Vector<String> types;
    
    types.append(WebURLsWithTitlesPboardType);
    types.append(String(NSURLPboardType));
    types.append(WebURLPboardType);
    types.append(WebURLNamePboardType);
    types.append(String(NSStringPboardType));        
    return types;
}

static Vector<String> writableTypesForImage()
{
    Vector<String> types;
    types.append(String(NSTIFFPboardType));
    types.appendVector(writableTypesForURL());
    types.append(String(NSRTFDPboardType));
    return types;
}

Pasteboard::Pasteboard()
    : m_pasteboardName(emptyString())
    , m_changeCount(0)
{
}

Pasteboard::Pasteboard(const String& pasteboardName)
    : m_pasteboardName(pasteboardName)
    , m_changeCount(platformStrategies()->pasteboardStrategy()->changeCount(m_pasteboardName))
{
    ASSERT(pasteboardName);
}

std::unique_ptr<Pasteboard> Pasteboard::createForCopyAndPaste()
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return std::make_unique<Pasteboard>(NSGeneralPboard);
#pragma clang diagnostic pop
}

std::unique_ptr<Pasteboard> Pasteboard::createPrivate()
{
    return std::make_unique<Pasteboard>(platformStrategies()->pasteboardStrategy()->uniqueName());
}

#if ENABLE(DRAG_SUPPORT)
std::unique_ptr<Pasteboard> Pasteboard::createForDragAndDrop()
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    return std::make_unique<Pasteboard>(NSDragPboard);
#pragma clang diagnostic pop
}

std::unique_ptr<Pasteboard> Pasteboard::createForDragAndDrop(const DragData& dragData)
{
    return std::make_unique<Pasteboard>(dragData.pasteboardName());
}
#endif

void Pasteboard::clear()
{
    m_changeCount = platformStrategies()->pasteboardStrategy()->setTypes(Vector<String>(), m_pasteboardName);
}

void Pasteboard::write(const PasteboardWebContent& content)
{
    Vector<String> types;

    if (content.canSmartCopyOrDelete)
        types.append(WebSmartPastePboardType);
    if (content.dataInWebArchiveFormat)
        types.append(WebArchivePboardType);
    if (content.dataInRTFDFormat)
        types.append(String(NSRTFDPboardType));
    if (content.dataInRTFFormat)
        types.append(String(NSRTFPboardType));
    if (!content.dataInHTMLFormat.isNull())
        types.append(String(NSHTMLPboardType));
    if (!content.dataInStringFormat.isNull())
        types.append(String(NSStringPboardType));
    types.appendVector(content.clientTypes);

    m_changeCount = platformStrategies()->pasteboardStrategy()->setTypes(types, m_pasteboardName);

    ASSERT(content.clientTypes.size() == content.clientData.size());
    for (size_t i = 0, size = content.clientTypes.size(); i < size; ++i)
        m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(content.clientData[i].get(), content.clientTypes[i], m_pasteboardName);
    if (content.canSmartCopyOrDelete)
        m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(nullptr, WebSmartPastePboardType, m_pasteboardName);
    if (content.dataInWebArchiveFormat)
        m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(content.dataInWebArchiveFormat.get(), WebArchivePboardType, m_pasteboardName);
    if (content.dataInRTFDFormat)
        m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(content.dataInRTFDFormat.get(), NSRTFDPboardType, m_pasteboardName);
    if (content.dataInRTFFormat)
        m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(content.dataInRTFFormat.get(), NSRTFPboardType, m_pasteboardName);
    if (!content.dataInHTMLFormat.isNull())
        m_changeCount = platformStrategies()->pasteboardStrategy()->setStringForType(content.dataInHTMLFormat, NSHTMLPboardType, m_pasteboardName);
    if (!content.dataInStringFormat.isNull())
        m_changeCount = platformStrategies()->pasteboardStrategy()->setStringForType(content.dataInStringFormat, NSStringPboardType, m_pasteboardName);
}

void Pasteboard::writePlainText(const String& text, SmartReplaceOption smartReplaceOption)
{
    Vector<String> types;
    types.append(NSStringPboardType);
    if (smartReplaceOption == CanSmartReplace)
        types.append(WebSmartPastePboardType);

    platformStrategies()->pasteboardStrategy()->setTypes(types, m_pasteboardName);
    m_changeCount = platformStrategies()->pasteboardStrategy()->setStringForType(text, NSStringPboardType, m_pasteboardName);
    if (smartReplaceOption == CanSmartReplace)
        m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(0, WebSmartPastePboardType, m_pasteboardName);
}

static long writeURLForTypes(const Vector<String>& types, const String& pasteboardName, const PasteboardURL& pasteboardURL)
{
    long newChangeCount = platformStrategies()->pasteboardStrategy()->setTypes(types, pasteboardName);
    
    ASSERT(!pasteboardURL.url.isEmpty());
    
    NSURL *cocoaURL = pasteboardURL.url;
    NSString *userVisibleString = pasteboardURL.userVisibleForm;
    NSString *title = (NSString *)pasteboardURL.title;
    if (![title length]) {
        title = [[cocoaURL path] lastPathComponent];
        if (![title length])
            title = userVisibleString;
    }

    if (types.contains(WebURLsWithTitlesPboardType)) {
        Vector<String> paths;
        paths.append([cocoaURL absoluteString]);
        paths.append(pasteboardURL.title.stripWhiteSpace());
        newChangeCount = platformStrategies()->pasteboardStrategy()->setPathnamesForType(paths, WebURLsWithTitlesPboardType, pasteboardName);
    }
    if (types.contains(String(NSURLPboardType)))
        newChangeCount = platformStrategies()->pasteboardStrategy()->setStringForType([cocoaURL absoluteString], NSURLPboardType, pasteboardName);
    if (types.contains(WebURLPboardType))
        newChangeCount = platformStrategies()->pasteboardStrategy()->setStringForType(userVisibleString, WebURLPboardType, pasteboardName);
    if (types.contains(WebURLNamePboardType))
        newChangeCount = platformStrategies()->pasteboardStrategy()->setStringForType(title, WebURLNamePboardType, pasteboardName);
    if (types.contains(String(NSStringPboardType)))
        newChangeCount = platformStrategies()->pasteboardStrategy()->setStringForType(userVisibleString, NSStringPboardType, pasteboardName);

    return newChangeCount;
}
    
void Pasteboard::write(const PasteboardURL& pasteboardURL)
{
    m_changeCount = writeURLForTypes(writableTypesForURL(), m_pasteboardName, pasteboardURL);
}

void Pasteboard::writeTrustworthyWebURLsPboardType(const PasteboardURL& pasteboardURL)
{
    NSURL *cocoaURL = pasteboardURL.url;
    Vector<String> paths = { [cocoaURL absoluteString], pasteboardURL.title.stripWhiteSpace() };
    m_changeCount = platformStrategies()->pasteboardStrategy()->setPathnamesForType(paths, WebURLsWithTitlesPboardType, m_pasteboardName);
}

static NSFileWrapper* fileWrapper(const PasteboardImage& pasteboardImage)
{
    NSFileWrapper *wrapper = [[[NSFileWrapper alloc] initRegularFileWithContents:pasteboardImage.resourceData->createNSData().get()] autorelease];
    [wrapper setPreferredFilename:suggestedFilenameWithMIMEType(pasteboardImage.url.url, pasteboardImage.resourceMIMEType)];
    return wrapper;
}

static void writeFileWrapperAsRTFDAttachment(NSFileWrapper *wrapper, const String& pasteboardName, long& newChangeCount)
{
    NSTextAttachment *attachment = [[NSTextAttachment alloc] initWithFileWrapper:wrapper];
    NSAttributedString *string = [NSAttributedString attributedStringWithAttachment:attachment];
    [attachment release];

    NSData *RTFDData = [string RTFDFromRange:NSMakeRange(0, [string length]) documentAttributes:@{ }];
    if (!RTFDData)
        return;

    newChangeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(SharedBuffer::wrapNSData(RTFDData).ptr(), NSRTFDPboardType, pasteboardName);
}

void Pasteboard::write(const PasteboardImage& pasteboardImage)
{
    CFDataRef imageData = pasteboardImage.image->tiffRepresentation();
    if (!imageData)
        return;

    // FIXME: Why can we assert this? It doesn't seem like it's guaranteed.
    ASSERT(MIMETypeRegistry::isSupportedImageResourceMIMEType(pasteboardImage.resourceMIMEType));

    auto types = writableTypesForImage();
    if (pasteboardImage.dataInWebArchiveFormat)
        types.append(WebArchivePboardType);

    m_changeCount = writeURLForTypes(types, m_pasteboardName, pasteboardImage.url);
    m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(SharedBuffer::wrapCFData(imageData).ptr(), NSTIFFPboardType, m_pasteboardName);
    if (pasteboardImage.dataInWebArchiveFormat)
        m_changeCount = platformStrategies()->pasteboardStrategy()->setBufferForType(pasteboardImage.dataInWebArchiveFormat.get(), WebArchivePboardType, m_pasteboardName);
    writeFileWrapperAsRTFDAttachment(fileWrapper(pasteboardImage), m_pasteboardName, m_changeCount);
}

void Pasteboard::writePasteboard(const Pasteboard& pasteboard)
{
    m_changeCount = platformStrategies()->pasteboardStrategy()->copy(pasteboard.m_pasteboardName, m_pasteboardName);
}

bool Pasteboard::canSmartReplace()
{
    Vector<String> types;
    platformStrategies()->pasteboardStrategy()->getTypes(types, m_pasteboardName);
    return types.contains(WebSmartPastePboardType);
}

void Pasteboard::writeMarkup(const String&)
{
}

void Pasteboard::read(PasteboardPlainText& text)
{
    PasteboardStrategy& strategy = *platformStrategies()->pasteboardStrategy();

    Vector<String> types;
    strategy.getTypes(types, m_pasteboardName);
    
    if (types.contains(String(NSStringPboardType))) {
        text.text = strategy.stringForType(NSStringPboardType, m_pasteboardName);
        text.isURL = false;
        return;
    }
    
    if (types.contains(String(NSRTFDPboardType))) {
        if (RefPtr<SharedBuffer> data = strategy.bufferForType(NSRTFDPboardType, m_pasteboardName)) {
            if (auto attributedString = adoptNS([[NSAttributedString alloc] initWithRTFD:data->createNSData().get() documentAttributes:NULL])) {
                text.text = [attributedString string];
                text.isURL = false;
                return;
            }
        }
    }

    if (types.contains(String(NSRTFPboardType))) {
        if (RefPtr<SharedBuffer> data = strategy.bufferForType(NSRTFPboardType, m_pasteboardName)) {
            if (auto attributedString = adoptNS([[NSAttributedString alloc] initWithRTF:data->createNSData().get() documentAttributes:NULL])) {
                text.text = [attributedString string];
                text.isURL = false;
                return;
            }
        }
    }

    if (types.contains(String(NSFilenamesPboardType))) {
        Vector<String> pathnames;
        strategy.getPathnamesForType(pathnames, NSFilenamesPboardType, m_pasteboardName);
        StringBuilder builder;
        for (size_t i = 0, size = pathnames.size(); i < size; i++) {
            if (i)
                builder.append('\n');
            builder.append(pathnames[i]);
        }
        text.text = builder.toString();
        text.isURL = false;
        return;
    }

    // FIXME: The code above looks at the types vector first, but this just gets the string without checking. Why the difference?
    text.text = strategy.stringForType(NSURLPboardType, m_pasteboardName);
    text.isURL = !text.text.isNull();
}

void Pasteboard::read(PasteboardWebContentReader& reader)
{
    PasteboardStrategy& strategy = *platformStrategies()->pasteboardStrategy();

    Vector<String> types;
    strategy.getTypes(types, m_pasteboardName);

    if (types.contains(WebArchivePboardType)) {
        if (RefPtr<SharedBuffer> buffer = strategy.bufferForType(WebArchivePboardType, m_pasteboardName)) {
            if (reader.readWebArchive(buffer.get()))
                return;
        }
    }

    if (types.contains(String(NSFilenamesPboardType))) {
        Vector<String> paths;
        strategy.getPathnamesForType(paths, NSFilenamesPboardType, m_pasteboardName);
        if (reader.readFilenames(paths))
            return;
    }

    if (types.contains(String(NSHTMLPboardType))) {
        String string = strategy.stringForType(NSHTMLPboardType, m_pasteboardName);
        if (!string.isNull() && reader.readHTML(string))
            return;
    }

    if (types.contains(String(NSRTFDPboardType))) {
        if (RefPtr<SharedBuffer> buffer = strategy.bufferForType(NSRTFDPboardType, m_pasteboardName)) {
            if (reader.readRTFD(*buffer))
                return;
        }
    }

    if (types.contains(String(NSRTFPboardType))) {
        if (RefPtr<SharedBuffer> buffer = strategy.bufferForType(NSRTFPboardType, m_pasteboardName)) {
            if (reader.readRTF(*buffer))
                return;
        }
    }

    if (types.contains(String(NSTIFFPboardType))) {
        if (RefPtr<SharedBuffer> buffer = strategy.bufferForType(NSTIFFPboardType, m_pasteboardName)) {
            if (reader.readImage(buffer.releaseNonNull(), ASCIILiteral("image/tiff")))
                return;
        }
    }

    if (types.contains(String(NSPDFPboardType))) {
        if (RefPtr<SharedBuffer> buffer = strategy.bufferForType(NSPDFPboardType, m_pasteboardName)) {
            if (reader.readImage(buffer.releaseNonNull(), ASCIILiteral("application/pdf")))
                return;
        }
    }

    if (types.contains(String(kUTTypePNG))) {
        if (RefPtr<SharedBuffer> buffer = strategy.bufferForType(kUTTypePNG, m_pasteboardName)) {
            if (reader.readImage(buffer.releaseNonNull(), ASCIILiteral("image/png")))
                return;
        }
    }

    if (types.contains(String(kUTTypeJPEG))) {
        if (RefPtr<SharedBuffer> buffer = strategy.bufferForType(kUTTypeJPEG, m_pasteboardName)) {
            if (reader.readImage(buffer.releaseNonNull(), ASCIILiteral("image/jpeg")))
                return;
        }
    }

    if (types.contains(String(NSURLPboardType))) {
        URL url = strategy.url(m_pasteboardName);
        String title = strategy.stringForType(WebURLNamePboardType, m_pasteboardName);
        if (!url.isNull() && reader.readURL(url, title))
            return;
    }

    if (types.contains(String(NSStringPboardType))) {
        String string = strategy.stringForType(NSStringPboardType, m_pasteboardName);
        if (!string.isNull() && reader.readPlainText(string))
            return;
    }

    if (types.contains(String(kUTTypeUTF8PlainText))) {
        String string = strategy.stringForType(kUTTypeUTF8PlainText, m_pasteboardName);
        if (!string.isNull() && reader.readPlainText(string))
            return;
    }
}

bool Pasteboard::hasData()
{
    Vector<String> types;
    platformStrategies()->pasteboardStrategy()->getTypes(types, m_pasteboardName);
    return !types.isEmpty();
}

static String cocoaTypeFromHTMLClipboardType(const String& type)
{
    // http://www.whatwg.org/specs/web-apps/current-work/multipage/dnd.html#dom-datatransfer-setdata
    String lowercasedType = type.convertToASCIILowercase();

    if (lowercasedType == "text")
        lowercasedType = ASCIILiteral("text/plain");
    if (lowercasedType == "url")
        lowercasedType = ASCIILiteral("text/uri-list");

    // Ignore any trailing charset - strings are already UTF-16, and the charset issue has already been dealt with.
    if (lowercasedType == "text/plain" || lowercasedType.startsWith("text/plain;"))
        return NSStringPboardType;
    if (lowercasedType == "text/uri-list") {
        // Special case because UTI doesn't work with Cocoa's URL type.
        return NSURLPboardType;
    }

    // Blacklist types that might contain subframe information.
    if (lowercasedType == "text/rtf" || lowercasedType == "public.rtf" || lowercasedType == "com.apple.traditional-mac-plain-text")
        return String();

    if (auto utiType = adoptCF(UTTypeCreatePreferredIdentifierForTag(kUTTagClassMIMEType, lowercasedType.createCFString().get(), NULL))) {
        if (auto pbType = adoptCF(UTTypeCopyPreferredTagWithClass(utiType.get(), kUTTagClassNSPboardType)))
            return pbType.get();
    }

    // No mapping, just pass the whole string though
    return lowercasedType;
}

void Pasteboard::clear(const String& type)
{
    String cocoaType = cocoaTypeFromHTMLClipboardType(type);
    if (cocoaType.isEmpty())
        return;
    m_changeCount = platformStrategies()->pasteboardStrategy()->setStringForType(emptyString(), cocoaType, m_pasteboardName);
}

static Vector<String> absoluteURLsFromPasteboardFilenames(const String& pasteboardName, bool onlyFirstURL = false)
{
    Vector<String> fileList;
    platformStrategies()->pasteboardStrategy()->getPathnamesForType(fileList, String(NSFilenamesPboardType), pasteboardName);

    if (fileList.isEmpty())
        return fileList;

    size_t count = onlyFirstURL ? 1 : fileList.size();
    Vector<String> urls;
    for (size_t i = 0; i < count; i++) {
        NSURL *url = [NSURL fileURLWithPath:fileList[i]];
        urls.append(String([url absoluteString]));
    }
    return urls;
}

static Vector<String> absoluteURLsFromPasteboard(const String& pasteboardName, bool onlyFirstURL = false)
{
    // NOTE: We must always check [availableTypes containsObject:] before accessing pasteboard data
    // or CoreFoundation will printf when there is not data of the corresponding type.
    Vector<String> availableTypes;
    Vector<String> absoluteURLs;
    platformStrategies()->pasteboardStrategy()->getTypes(availableTypes, pasteboardName);

    // Try NSFilenamesPboardType because it contains a list
    if (availableTypes.contains(String(NSFilenamesPboardType))) {
        absoluteURLs = absoluteURLsFromPasteboardFilenames(pasteboardName, onlyFirstURL);
        if (!absoluteURLs.isEmpty())
            return absoluteURLs;
    }

    // Fallback to NSURLPboardType (which is a single URL)
    if (availableTypes.contains(String(NSURLPboardType))) {
        absoluteURLs.append(platformStrategies()->pasteboardStrategy()->stringForType(String(NSURLPboardType), pasteboardName));
        return absoluteURLs;
    }

    // No file paths on the pasteboard, return nil
    return Vector<String>();
}

String Pasteboard::readString(const String& type)
{
    const String& cocoaType = cocoaTypeFromHTMLClipboardType(type);
    String cocoaValue;

    // Grab the value off the pasteboard corresponding to the cocoaType
    if (cocoaType == String(NSURLPboardType)) {
        // "url" and "text/url-list" both map to NSURLPboardType in cocoaTypeFromHTMLClipboardType(), "url" only wants the first URL
        bool onlyFirstURL = equalLettersIgnoringASCIICase(type, "url");
        Vector<String> absoluteURLs = absoluteURLsFromPasteboard(m_pasteboardName, onlyFirstURL);
        for (size_t i = 0; i < absoluteURLs.size(); i++)
            cocoaValue = i ? "\n" + absoluteURLs[i]: absoluteURLs[i];
    } else if (cocoaType == String(NSStringPboardType))
        cocoaValue = [platformStrategies()->pasteboardStrategy()->stringForType(cocoaType, m_pasteboardName) precomposedStringWithCanonicalMapping];
    else if (!cocoaType.isEmpty())
        cocoaValue = platformStrategies()->pasteboardStrategy()->stringForType(cocoaType, m_pasteboardName);

    // Enforce changeCount ourselves for security.  We check after reading instead of before to be
    // sure it doesn't change between our testing the change count and accessing the data.
    if (!cocoaValue.isEmpty() && m_changeCount == platformStrategies()->pasteboardStrategy()->changeCount(m_pasteboardName))
        return cocoaValue;

    return String();
}

static String utiTypeFromCocoaType(const String& type)
{
    if (RetainPtr<CFStringRef> utiType = adoptCF(UTTypeCreatePreferredIdentifierForTag(kUTTagClassNSPboardType, type.createCFString().get(), 0))) {
        if (RetainPtr<CFStringRef> mimeType = adoptCF(UTTypeCopyPreferredTagWithClass(utiType.get(), kUTTagClassMIMEType)))
            return String(mimeType.get());
    }
    return String();
}

static void addHTMLClipboardTypesForCocoaType(ListHashSet<String>& resultTypes, const String& cocoaType, const String& pasteboardName)
{
    // UTI may not do these right, so make sure we get the right, predictable result
    if (cocoaType == String(NSStringPboardType)) {
        resultTypes.add(ASCIILiteral("text/plain"));
        return;
    }
    if (cocoaType == String(NSURLPboardType)) {
        resultTypes.add(ASCIILiteral("text/uri-list"));
        return;
    }
    if (cocoaType == String(NSFilenamesPboardType)) {
        // If file list is empty, add nothing.
        // Note that there is a chance that the file list count could have changed since we grabbed the types array.
        // However, this is not really an issue for us doing a sanity check here.
        Vector<String> fileList;
        platformStrategies()->pasteboardStrategy()->getPathnamesForType(fileList, String(NSFilenamesPboardType), pasteboardName);
        if (!fileList.isEmpty()) {
            // It is unknown if NSFilenamesPboardType always implies NSURLPboardType in Cocoa,
            // but NSFilenamesPboardType should imply both 'text/uri-list' and 'Files'
            resultTypes.add(ASCIILiteral("text/uri-list"));
            resultTypes.add(ASCIILiteral("Files"));
        }
        return;
    }
    String utiType = utiTypeFromCocoaType(cocoaType);
    if (!utiType.isEmpty()) {
        resultTypes.add(utiType);
        return;
    }
    // No mapping, just pass the whole string through.
    resultTypes.add(cocoaType);
}

void Pasteboard::writeString(const String& type, const String& data)
{
    const String& cocoaType = cocoaTypeFromHTMLClipboardType(type);
    String cocoaData = data;

    if (cocoaType == String(NSURLPboardType) || cocoaType == String(kUTTypeFileURL)) {
        NSURL *url = [NSURL URLWithString:cocoaData];
        if ([url isFileURL])
            return;

        Vector<String> types;
        types.append(cocoaType);
        platformStrategies()->pasteboardStrategy()->setTypes(types, m_pasteboardName);
        m_changeCount = platformStrategies()->pasteboardStrategy()->setStringForType(cocoaData, cocoaType, m_pasteboardName);

        return;
    }

    if (!cocoaType.isEmpty()) {
        // everything else we know of goes on the pboard as a string
        Vector<String> types;
        types.append(cocoaType);
        platformStrategies()->pasteboardStrategy()->addTypes(types, m_pasteboardName);
        m_changeCount = platformStrategies()->pasteboardStrategy()->setStringForType(cocoaData, cocoaType, m_pasteboardName);
    }
}

Vector<String> Pasteboard::types()
{
    Vector<String> types;
    platformStrategies()->pasteboardStrategy()->getTypes(types, m_pasteboardName);

    // Enforce changeCount ourselves for security. We check after reading instead of before to be
    // sure it doesn't change between our testing the change count and accessing the data.
    if (m_changeCount != platformStrategies()->pasteboardStrategy()->changeCount(m_pasteboardName))
        return Vector<String>();

    ListHashSet<String> result;
    // FIXME: This loop could be split into two stages. One which adds all the HTML5 specified types
    // and a second which adds all the extra types from the cocoa clipboard (which is Mac-only behavior).
    for (size_t i = 0; i < types.size(); i++) {
        if (types[i] == "NeXT plain ascii pasteboard type")
            continue;   // skip this ancient type that gets auto-supplied by some system conversion

        addHTMLClipboardTypesForCocoaType(result, types[i], m_pasteboardName);
    }

    copyToVector(result, types);
    return types;
}

Vector<String> Pasteboard::readFilenames()
{
    // FIXME: Seems silly to convert paths to URLs and then back to paths. Does that do anything helpful?
    Vector<String> absoluteURLs = absoluteURLsFromPasteboardFilenames(m_pasteboardName);
    Vector<String> paths;
    paths.reserveCapacity(absoluteURLs.size());
    for (size_t i = 0; i < absoluteURLs.size(); i++) {
        NSURL *absoluteURL = [NSURL URLWithString:absoluteURLs[i]];
        ASSERT([absoluteURL isFileURL]);
        paths.uncheckedAppend([absoluteURL path]);
    }
    return paths;
}

#if ENABLE(DRAG_SUPPORT)
void Pasteboard::setDragImage(DragImage image, const IntPoint& location)
{
    // Don't allow setting the drag image if someone kept a pasteboard and is trying to set the image too late.
    if (m_changeCount != platformStrategies()->pasteboardStrategy()->changeCount(m_pasteboardName))
        return;

    // Dashboard wants to be able to set the drag image during dragging, but Cocoa does not allow this.
    // Instead we must drop down to the CoreGraphics API.
    wkSetDragImage(image.get().get(), location);

    // Hack: We must post an event to wake up the NSDragManager, which is sitting in a nextEvent call
    // up the stack from us because the CoreFoundation drag manager does not use the run loop by itself.
    // This is the most innocuous event to use, per Kristen Forster.
    NSEvent* event = [NSEvent mouseEventWithType:NSEventTypeMouseMoved location:NSZeroPoint
        modifierFlags:0 timestamp:0 windowNumber:0 context:nil eventNumber:0 clickCount:0 pressure:0];
    [NSApp postEvent:event atStart:YES];
}
#endif

}
