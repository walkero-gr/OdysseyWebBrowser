/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
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

#import <WebKit/WKFoundation.h>

#if WK_API_ENABLED

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, _WKDiagnosticLoggingResultType) {
    _WKDiagnosticLoggingResultPass,
    _WKDiagnosticLoggingResultFail,
    _WKDiagnosticLoggingResultNoop,
} WK_API_AVAILABLE(macosx(10.11), ios(9.0));

@protocol _WKDiagnosticLoggingDelegate <NSObject>
@optional

- (void)_webView:(WKWebView *)webView logDiagnosticMessage:(NSString *)message description:(NSString *)description;
- (void)_webView:(WKWebView *)webView logDiagnosticMessageWithResult:(NSString *)message description:(NSString *)description result:(_WKDiagnosticLoggingResultType)result;
- (void)_webView:(WKWebView *)webView logDiagnosticMessageWithValue:(NSString *)message description:(NSString *)description value:(NSString *) value;
- (void)_webView:(WKWebView *)webView logDiagnosticMessageWithEnhancedPrivacy:(NSString *)message description:(NSString *)description;

@end

#endif // WK_API_ENABLED

