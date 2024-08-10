/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
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

#ifndef WebVisitedLinkStore_h
#define WebVisitedLinkStore_h

#include <WebCore/SharedStringHash.h>
#include <WebCore/VisitedLinkStore.h>

class WebVisitedLinkStore final : public WebCore::VisitedLinkStore {
public:
    static Ref<WebVisitedLinkStore> create();
    static WebVisitedLinkStore& singleton();
    virtual ~WebVisitedLinkStore();

    static void setShouldTrackVisitedLinks(bool);
    static void removeAllVisitedLinks();

    void addVisitedLink(const String& urlString);

private:
    WebVisitedLinkStore();

    virtual bool isLinkVisited(WebCore::Page&, WebCore::SharedStringHash, const WebCore::URL& baseURL, const AtomicString& attributeURL) override;
    virtual void addVisitedLink(WebCore::Page&, WebCore::SharedStringHash) override;

    void populateVisitedLinksIfNeeded(WebCore::Page&);
    void addVisitedLinkHash(WebCore::SharedStringHash);
    void removeVisitedLinkHashes();

    HashSet<WebCore::SharedStringHash, WebCore::SharedStringHashHash> m_visitedLinkHashes;
    bool m_visitedLinksPopulated;
};

#endif // WebVisitedLinkStore_h
