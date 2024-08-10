/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "RealtimeIncomingAudioSourceCocoa.h"

#if USE(LIBWEBRTC)

#include "AudioStreamDescription.h"
#include "CAAudioStreamDescription.h"
#include "LibWebRTCAudioFormat.h"
#include "Logging.h"
#include "WebAudioBufferList.h"
#include "WebAudioSourceProviderAVFObjC.h"
#include <pal/avfoundation/MediaTimeAVFoundation.h>

#include <pal/cf/CoreMediaSoftLink.h>

namespace WebCore {
using namespace PAL;

Ref<RealtimeIncomingAudioSource> RealtimeIncomingAudioSource::create(rtc::scoped_refptr<webrtc::AudioTrackInterface>&& audioTrack, String&& audioTrackId)
{
    auto source = RealtimeIncomingAudioSourceCocoa::create(WTFMove(audioTrack), WTFMove(audioTrackId));
    source->start();
    return WTFMove(source);
}

Ref<RealtimeIncomingAudioSourceCocoa> RealtimeIncomingAudioSourceCocoa::create(rtc::scoped_refptr<webrtc::AudioTrackInterface>&& audioTrack, String&& audioTrackId)
{
    return adoptRef(*new RealtimeIncomingAudioSourceCocoa(WTFMove(audioTrack), WTFMove(audioTrackId)));
}

RealtimeIncomingAudioSourceCocoa::RealtimeIncomingAudioSourceCocoa(rtc::scoped_refptr<webrtc::AudioTrackInterface>&& audioTrack, String&& audioTrackId)
    : RealtimeIncomingAudioSource(WTFMove(audioTrack), WTFMove(audioTrackId))
{
}

static inline AudioStreamBasicDescription streamDescription(size_t sampleRate, size_t channelCount)
{
    AudioStreamBasicDescription streamFormat;
    FillOutASBDForLPCM(streamFormat, sampleRate, channelCount, LibWebRTCAudioFormat::sampleSize, LibWebRTCAudioFormat::sampleSize, LibWebRTCAudioFormat::isFloat, LibWebRTCAudioFormat::isBigEndian, LibWebRTCAudioFormat::isNonInterleaved);
    return streamFormat;
}

void RealtimeIncomingAudioSourceCocoa::OnData(const void* audioData, int bitsPerSample, int sampleRate, size_t numberOfChannels, size_t numberOfFrames)
{
    CMTime startTime = CMTimeMake(m_numberOfFrames, sampleRate);
    auto mediaTime = PAL::toMediaTime(startTime);
    m_numberOfFrames += numberOfFrames;

    AudioStreamBasicDescription newDescription = streamDescription(sampleRate, numberOfChannels);

    // FIXME: We should not need to do the extra memory allocation and copy.
    // Instead, we should be able to directly pass audioData pointer.
    WebAudioBufferList audioBufferList { CAAudioStreamDescription(newDescription), WTF::safeCast<uint32_t>(numberOfFrames) };
    audioBufferList.buffer(0)->mDataByteSize = numberOfChannels * numberOfFrames * bitsPerSample / 8;
    audioBufferList.buffer(0)->mNumberChannels = numberOfChannels;

    if (muted())
        memset(audioBufferList.buffer(0)->mData, 0, audioBufferList.buffer(0)->mDataByteSize);
    else
        memcpy(audioBufferList.buffer(0)->mData, audioData, audioBufferList.buffer(0)->mDataByteSize);

#if !RELEASE_LOG_DISABLED
    if (!(++m_chunksReceived % 200))
        ALWAYS_LOG(LOGIDENTIFIER, "chunk ", m_chunksReceived);
#endif

    audioSamplesAvailable(mediaTime, audioBufferList, CAAudioStreamDescription(newDescription), numberOfFrames);
}

}

#endif // USE(LIBWEBRTC)
