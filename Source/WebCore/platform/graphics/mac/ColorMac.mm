/*
 * Copyright (C) 2003, 2004, 2005, 2006 Apple Inc.  All rights reserved.
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
#import "ColorMac.h"

#import <wtf/BlockObjCExceptions.h>
#import <wtf/NeverDestroyed.h>
#import <wtf/RetainPtr.h>
#import <wtf/StdLibExtras.h>

namespace WebCore {

static bool useOldAquaFocusRingColor;

Color oldAquaFocusRingColor()
{
    return 0xFF7DADD9;
}

void setUsesTestModeFocusRingColor(bool newValue)
{
    useOldAquaFocusRingColor = newValue;
}

bool usesTestModeFocusRingColor()
{
    return useOldAquaFocusRingColor;
}

static RGBA32 makeRGBAFromNSColor(NSColor *c)
{
    CGFloat redComponent;
    CGFloat greenComponent;
    CGFloat blueComponent;
    CGFloat alpha;

    BEGIN_BLOCK_OBJC_EXCEPTIONS;
    NSColor *rgbColor = [c colorUsingColorSpaceName:NSDeviceRGBColorSpace];
    if (!rgbColor)
        return makeRGBA(0, 0, 0, 0);

    [rgbColor getRed:&redComponent green:&greenComponent blue:&blueComponent alpha:&alpha];
    END_BLOCK_OBJC_EXCEPTIONS;

    return makeRGBA(255 * redComponent, 255 * greenComponent, 255 * blueComponent, 255 * alpha);
}

Color colorFromNSColor(NSColor *c)
{
    return Color(makeRGBAFromNSColor(c));
}

NSColor *nsColor(const Color& color)
{
    if (!color.isValid()) {
        // Need this to avoid returning nil because cachedRGBAValues will default to 0.
        static NeverDestroyed<NSColor *> clearColor = [[NSColor colorWithDeviceRed:0 green:0 blue:0 alpha:0] retain];
        return clearColor;
    }

    if (Color::isBlackColor(color)) {
        static NeverDestroyed<NSColor *> blackColor = [[NSColor colorWithDeviceRed:0 green:0 blue:0 alpha:1] retain];
        return blackColor;
    }

    if (Color::isWhiteColor(color)) {
        static NeverDestroyed<NSColor *> whiteColor = [[NSColor colorWithDeviceRed:1 green:1 blue:1 alpha:1] retain];
        return whiteColor;
    }

    const int cacheSize = 32;
    static unsigned cachedRGBAValues[cacheSize];
    static RetainPtr<NSColor>* cachedColors = new RetainPtr<NSColor>[cacheSize];

    unsigned hash = color.hash();
    for (int i = 0; i < cacheSize; ++i) {
        if (cachedRGBAValues[i] == hash)
            return cachedColors[i].get();
    }

    NSColor *result = [NSColor colorWithCGColor:cachedCGColor(color)];

    static int cursor;
    cachedRGBAValues[cursor] = hash;
    cachedColors[cursor] = result;
    if (++cursor == cacheSize)
        cursor = 0;
    return result;
}


} // namespace WebCore
