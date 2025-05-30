/*
 * Copyright (C) 2019 Carlos Eduardo Ramalho <cadubentzen@gmail.com>.
 * Copyright (C) 2019 Apple Inc. All rights reserved.
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

#include "config.h"
#include "HTMLVideoElementPictureInPicture.h"

#if ENABLE(PICTURE_IN_PICTURE_API)

#include "EventNames.h"
#include "HTMLVideoElement.h"
#include "JSDOMPromiseDeferred.h"
#include "JSPictureInPictureWindow.h"
#include "Logging.h"
#include "PictureInPictureEvent.h"
#include "PictureInPictureSupport.h"
#include "PictureInPictureWindow.h"
#include "VideoTrackList.h"
#include <wtf/TZoneMallocInlines.h>

namespace WebCore {

WTF_MAKE_TZONE_OR_ISO_ALLOCATED_IMPL(HTMLVideoElementPictureInPicture);

HTMLVideoElementPictureInPicture::HTMLVideoElementPictureInPicture(HTMLVideoElement& videoElement)
    : m_videoElement(videoElement)
    , m_pictureInPictureWindow(PictureInPictureWindow::create(videoElement.document()))
#if !RELEASE_LOG_DISABLED
    , m_logger(videoElement.document().logger())
    , m_logIdentifier(uniqueLogIdentifier())
#endif
{
    ALWAYS_LOG(LOGIDENTIFIER);
    m_videoElement->setPictureInPictureObserver(this);
}

HTMLVideoElementPictureInPicture::~HTMLVideoElementPictureInPicture()
{
    ALWAYS_LOG(LOGIDENTIFIER);
    m_videoElement->setPictureInPictureObserver(nullptr);
}

HTMLVideoElementPictureInPicture* HTMLVideoElementPictureInPicture::from(HTMLVideoElement& videoElement)
{
    HTMLVideoElementPictureInPicture* supplement = static_cast<HTMLVideoElementPictureInPicture*>(Supplement<HTMLVideoElement>::from(&videoElement, supplementName()));
    if (!supplement) {
        auto newSupplement = makeUnique<HTMLVideoElementPictureInPicture>(videoElement);
        supplement = newSupplement.get();
        provideTo(&videoElement, supplementName(), WTFMove(newSupplement));
    }
    return supplement;
}

void HTMLVideoElementPictureInPicture::providePictureInPictureTo(HTMLVideoElement& videoElement)
{
    provideTo(&videoElement, supplementName(), makeUnique<HTMLVideoElementPictureInPicture>(videoElement));
}

void HTMLVideoElementPictureInPicture::requestPictureInPicture(HTMLVideoElement& videoElement, Ref<DeferredPromise>&& promise)
{
    if (!supportsPictureInPicture()) {
        promise->reject(ExceptionCode::NotSupportedError, "The Picture-in-Picture mode is not supported."_s);
        return;
    }

    if (videoElement.readyState() == HTMLMediaElementEnums::HAVE_NOTHING) {
        promise->reject(ExceptionCode::InvalidStateError, "The video element is not ready to enter the Picture-in-Picture mode."_s);
        return;
    }

    if (!videoElement.videoTracks() || !videoElement.videoTracks()->length()) {
        promise->reject(ExceptionCode::InvalidStateError, "The video element does not have a video track or it has not detected a video track yet."_s);
        return;
    }

    bool userActivationRequired = !videoElement.document().pictureInPictureElement();
    if (userActivationRequired && !UserGestureIndicator::processingUserGesture()) {
        promise->reject(ExceptionCode::NotAllowedError, "The request is not triggered by a user activation."_s);
        return;
    }

    auto videoElementPictureInPicture = HTMLVideoElementPictureInPicture::from(videoElement);
    if (videoElement.document().pictureInPictureElement() == &videoElement) {
        promise->resolve<IDLInterface<PictureInPictureWindow>>(*(videoElementPictureInPicture->m_pictureInPictureWindow));
        return;
    }

    if (videoElementPictureInPicture->m_enterPictureInPicturePromise || videoElementPictureInPicture->m_exitPictureInPicturePromise) {
        promise->reject(ExceptionCode::NotAllowedError, "The video element is processing a Picture-in-Picture request."_s);
        return;
    }

    if (videoElement.webkitSupportsPresentationMode(HTMLVideoElement::VideoPresentationMode::PictureInPicture)) {
        videoElementPictureInPicture->m_enterPictureInPicturePromise = WTFMove(promise);
        videoElement.webkitSetPresentationMode(HTMLVideoElement::VideoPresentationMode::PictureInPicture);
    } else
        promise->reject(ExceptionCode::NotSupportedError, "The video element does not support the Picture-in-Picture mode."_s);
}

bool HTMLVideoElementPictureInPicture::autoPictureInPicture(HTMLVideoElement& videoElement)
{
    return HTMLVideoElementPictureInPicture::from(videoElement)->m_autoPictureInPicture;
}

void HTMLVideoElementPictureInPicture::setAutoPictureInPicture(HTMLVideoElement& videoElement, bool autoPictureInPicture)
{
    HTMLVideoElementPictureInPicture::from(videoElement)->m_autoPictureInPicture = autoPictureInPicture;
}

bool HTMLVideoElementPictureInPicture::disablePictureInPicture(HTMLVideoElement& videoElement)
{
    return HTMLVideoElementPictureInPicture::from(videoElement)->m_disablePictureInPicture;
}

void HTMLVideoElementPictureInPicture::setDisablePictureInPicture(HTMLVideoElement& videoElement, bool disablePictureInPicture)
{
    HTMLVideoElementPictureInPicture::from(videoElement)->m_disablePictureInPicture = disablePictureInPicture;
}

void HTMLVideoElementPictureInPicture::exitPictureInPicture(Ref<DeferredPromise>&& promise)
{
    INFO_LOG(LOGIDENTIFIER);
    if (m_enterPictureInPicturePromise || m_exitPictureInPicturePromise) {
        promise->reject(ExceptionCode::NotAllowedError);
        return;
    }

    m_exitPictureInPicturePromise = WTFMove(promise);
    m_videoElement->webkitSetPresentationMode(HTMLVideoElement::VideoPresentationMode::Inline);
}

void HTMLVideoElementPictureInPicture::didEnterPictureInPicture(const IntSize& windowSize)
{
    INFO_LOG(LOGIDENTIFIER);
    m_videoElement->document().setPictureInPictureElement(m_videoElement.ptr());
    m_pictureInPictureWindow->setSize(windowSize);

    PictureInPictureEvent::Init initializer;
    initializer.bubbles = true;
    initializer.pictureInPictureWindow = m_pictureInPictureWindow;
    m_videoElement->scheduleEvent(PictureInPictureEvent::create(eventNames().enterpictureinpictureEvent, WTFMove(initializer)));

    if (m_enterPictureInPicturePromise) {
        m_enterPictureInPicturePromise->resolve<IDLInterface<PictureInPictureWindow>>(*m_pictureInPictureWindow);
        m_enterPictureInPicturePromise = nullptr;
    }
}

void HTMLVideoElementPictureInPicture::didExitPictureInPicture()
{
    INFO_LOG(LOGIDENTIFIER);
    m_pictureInPictureWindow->close();
    m_videoElement->document().setPictureInPictureElement(nullptr);

    PictureInPictureEvent::Init initializer;
    initializer.bubbles = true;
    initializer.pictureInPictureWindow = m_pictureInPictureWindow;
    m_videoElement->scheduleEvent(PictureInPictureEvent::create(eventNames().leavepictureinpictureEvent, WTFMove(initializer)));

    if (m_exitPictureInPicturePromise) {
        m_exitPictureInPicturePromise->resolve();
        m_exitPictureInPicturePromise = nullptr;
    }
}

void HTMLVideoElementPictureInPicture::pictureInPictureWindowResized(const IntSize& windowSize)
{
    m_pictureInPictureWindow->setSize(windowSize);
}

#if !RELEASE_LOG_DISABLED
WTFLogChannel& HTMLVideoElementPictureInPicture::logChannel() const
{
    return LogMedia;
}
#endif

} // namespace WebCore

#endif // ENABLE(PICTURE_IN_PICTURE_API)
