/*
    Copyright (C) 2012 Intel Corporation

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

#ifndef WebPlatformStrategies_h
#define WebPlatformStrategies_h

#include <WebCore/CookiesStrategy.h>
#include <WebCore/LoaderStrategy.h>
#include <WebCore/PlatformStrategies.h>
#include <wtf/Forward.h>

class WebPlatformStrategies : public WebCore::PlatformStrategies, private WebCore::CookiesStrategy, private WebCore::LoaderStrategy
{
public:
    static void initialize();
    WebPlatformStrategies();

private:
    // WebCore::PlatformStrategies
    virtual WebCore::CookiesStrategy* createCookiesStrategy() override;
    virtual WebCore::LoaderStrategy* createLoaderStrategy() override;
    virtual WebCore::PasteboardStrategy* createPasteboardStrategy() override;
    virtual WebCore::BlobRegistry* createBlobRegistry() override;

    // WebCore::CookiesStrategy
    std::pair<String, bool> cookiesForDOM(const WebCore::NetworkStorageSession&, const WebCore::URL& firstParty, const WebCore::SameSiteInfo&, const WebCore::URL&, std::optional<uint64_t> frameID, std::optional<uint64_t> pageID, WebCore::IncludeSecureCookies) override;
    virtual void setCookiesFromDOM(const WebCore::NetworkStorageSession&, const WebCore::URL& firstParty, const WebCore::SameSiteInfo&, const WebCore::URL&, std::optional<uint64_t> frameID, std::optional<uint64_t> pageID, const String&);
    virtual bool cookiesEnabled(const WebCore::NetworkStorageSession&);
    std::pair<String, bool> cookieRequestHeaderFieldValue(const WebCore::NetworkStorageSession&, const WebCore::URL& firstParty, const WebCore::SameSiteInfo&, const WebCore::URL&, std::optional<uint64_t> frameID, std::optional<uint64_t> pageID, WebCore::IncludeSecureCookies) override;
    std::pair<String, bool> cookieRequestHeaderFieldValue(PAL::SessionID, const WebCore::URL& firstParty, const WebCore::SameSiteInfo&, const WebCore::URL&, std::optional<uint64_t> frameID, std::optional<uint64_t> pageID, WebCore::IncludeSecureCookies) override;
    virtual bool getRawCookies(const WebCore::NetworkStorageSession&, const WebCore::URL& firstParty, const WebCore::SameSiteInfo&, const WebCore::URL&, std::optional<uint64_t> frameID, std::optional<uint64_t> pageID, Vector<WebCore::Cookie>&);
    virtual void deleteCookie(const WebCore::NetworkStorageSession&, const WebCore::URL&, const String&);
    virtual void addCookie(const WebCore::NetworkStorageSession&, const WebCore::URL&, const WebCore::Cookie&);

    // WebCore::DatabaseStrategy
    // - Using default implementation.

    // WebCore::LoaderStrategy
    virtual void loadResource(WebCore::Frame&, WebCore::CachedResource&, WebCore::ResourceRequest&&, const WebCore::ResourceLoaderOptions&, CompletionHandler<void(RefPtr<WebCore::SubresourceLoader>&&)>&&) override;
    virtual void loadResourceSynchronously(WebCore::FrameLoader&, unsigned long identifier, const WebCore::ResourceRequest&, WebCore::ClientCredentialPolicy, const WebCore::FetchOptions&, const WebCore::HTTPHeaderMap&, WebCore::ResourceError&, WebCore::ResourceResponse&, Vector<char>& data) override;

    virtual void remove(WebCore::ResourceLoader*) override;
    virtual void setDefersLoading(WebCore::ResourceLoader&, bool) override;
    virtual void crossOriginRedirectReceived(WebCore::ResourceLoader*, const WebCore::URL& redirectURL) override;

    virtual void servePendingRequests(WebCore::ResourceLoadPriority minimumPriority = WebCore::ResourceLoadPriority::VeryLow) override;
    virtual void suspendPendingRequests() override;
    virtual void resumePendingRequests() override;

    void storeDerivedDataToCache(const SHA1::Digest& bodyKey, const String& type, const String& partition, WebCore::SharedBuffer&) override;
    void setCaptureExtraNetworkLoadMetricsEnabled(bool) override;

    using PingLoadCompletionHandler = WTF::Function<void(const WebCore::ResourceError&, const WebCore::ResourceResponse&)>;
    virtual void startPingLoad(WebCore::Frame&, WebCore::ResourceRequest&, const WebCore::HTTPHeaderMap& originalRequestHeaders, const WebCore::FetchOptions&, PingLoadCompletionHandler&& = { }) override;

    using PreconnectCompletionHandler = WTF::Function<void(const WebCore::ResourceError&)>;
    virtual void preconnectTo(WebCore::FrameLoader&, const WebCore::URL&, WebCore::StoredCredentialsPolicy, PreconnectCompletionHandler&&) override;

    virtual void pageLoadCompleted(uint64_t webPageID);
    virtual bool isOnLine() const;
    virtual void addOnlineStateChangeListener(Function<void(bool)>&&);
};

#endif // WebPlatformStrategies_h

