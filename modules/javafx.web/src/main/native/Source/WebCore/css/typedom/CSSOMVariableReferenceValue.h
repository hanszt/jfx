/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
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

#pragma once

#include "CSSStyleValue.h"
#include <wtf/RefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

template<typename> class ExceptionOr;
class CSSUnparsedValue;

class CSSOMVariableReferenceValue : public RefCounted<CSSOMVariableReferenceValue> {
    WTF_MAKE_TZONE_OR_ISO_ALLOCATED(CSSOMVariableReferenceValue);
public:
    static ExceptionOr<Ref<CSSOMVariableReferenceValue>> create(String&&, RefPtr<CSSUnparsedValue>&& fallback = { });

    ExceptionOr<void> setVariable(String&&);
    String toString() const;
    void serialize(StringBuilder&, OptionSet<SerializationArguments>) const;

    const String& variable() const { return m_variable; }
    CSSUnparsedValue* fallback() { return m_fallback.get(); }

private:
    CSSOMVariableReferenceValue(String&& variable, RefPtr<CSSUnparsedValue>&& fallback)
        : m_variable(WTFMove(variable))
        , m_fallback(WTFMove(fallback)) { }

    String m_variable;
    RefPtr<CSSUnparsedValue> m_fallback;
};

} // namespace WebCore
