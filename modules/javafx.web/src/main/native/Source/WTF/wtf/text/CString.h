/*
 * Copyright (C) 2003-2019 Apple Inc. All rights reserved.
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

#include <span>
#include <wtf/DebugHeap.h>
#include <wtf/HashFunctions.h>
#include <wtf/HashTraits.h>
#include <wtf/Ref.h>
#include <wtf/RefCounted.h>
#include <wtf/StdLibExtras.h>

namespace WTF {

DECLARE_ALLOCATOR_WITH_HEAP_IDENTIFIER(CStringBuffer);

// CStringBuffer is the ref-counted storage class for the characters in a CString.
// The data is implicitly allocated 1 character longer than length(), as it is zero-terminated.
class CStringBuffer final : public RefCounted<CStringBuffer> {
    WTF_MAKE_FAST_ALLOCATED_WITH_HEAP_IDENTIFIER(CStringBuffer);
public:
    const char* data() { return mutableData(); }
    size_t length() const { return m_length; }

private:
    friend class CString;

    static Ref<CStringBuffer> createUninitialized(size_t length);

    CStringBuffer(size_t length) : m_length(length) { }
    char* mutableData() { return reinterpret_cast_ptr<char*>(this + 1); }

    const size_t m_length;
};

// A container for a null-terminated char array supporting copy-on-write assignment.
// The contained char array may be null.
class CString final {
    WTF_MAKE_FAST_ALLOCATED;
public:
    CString() { }
    WTF_EXPORT_PRIVATE CString(const char*);
    WTF_EXPORT_PRIVATE CString(std::span<const char>);
    CString(std::span<const uint8_t>);
    CString(std::span<const char8_t> characters) : CString(byteCast<uint8_t>(characters)) { }
    CString(CStringBuffer* buffer) : m_buffer(buffer) { }
    WTF_EXPORT_PRIVATE static CString newUninitialized(size_t length, char*& characterBuffer);
    CString(HashTableDeletedValueType) : m_buffer(HashTableDeletedValue) { }

    const char* data() const;

    std::string toStdString() const { return m_buffer ? std::string(m_buffer->data()) : std::string(); }

    const uint8_t* dataAsUInt8Ptr() const { return reinterpret_cast<const uint8_t*>(data()); }
    std::span<const uint8_t> span() const;
    std::span<const char> spanIncludingNullTerminator() const;

    WTF_EXPORT_PRIVATE char* mutableData();
    size_t length() const;

    bool isNull() const { return !m_buffer; }
    bool isSafeToSendToAnotherThread() const;

    CStringBuffer* buffer() const { return m_buffer.get(); }

    bool isHashTableDeletedValue() const { return m_buffer.isHashTableDeletedValue(); }

    WTF_EXPORT_PRIVATE unsigned hash() const;

    // Useful if you want your CString to hold dynamic data.
    WTF_EXPORT_PRIVATE void grow(size_t newLength);

private:
    void copyBufferIfNeeded();
    void init(std::span<const char>);
    RefPtr<CStringBuffer> m_buffer;
};

WTF_EXPORT_PRIVATE bool operator==(const CString&, const CString&);
WTF_EXPORT_PRIVATE bool operator==(const CString&, const char*);
WTF_EXPORT_PRIVATE bool operator<(const CString&, const CString&);

struct CStringHash {
    static unsigned hash(const CString& string) { return string.hash(); }
    WTF_EXPORT_PRIVATE static bool equal(const CString& a, const CString& b);
    static constexpr bool safeToCompareToEmptyOrDeleted = true;
};

template<typename> struct DefaultHash;
template<> struct DefaultHash<CString> : CStringHash { };

template<typename> struct HashTraits;
template<> struct HashTraits<CString> : SimpleClassHashTraits<CString> { };

inline CString::CString(std::span<const uint8_t> bytes)
    : CString(byteCast<char>(bytes))
{
}

inline const char* CString::data() const
{
    return m_buffer ? m_buffer->data() : nullptr;
}

inline std::span<const uint8_t> CString::span() const
{
    if (m_buffer)
        return { byteCast<uint8_t>(m_buffer->data()), m_buffer->length() };
    return { };
}

inline std::span<const char> CString::spanIncludingNullTerminator() const
{
    if (m_buffer)
        return { m_buffer->data(), m_buffer->length() + 1 };
    return { };
}

inline size_t CString::length() const
{
    return m_buffer ? m_buffer->length() : 0;
}

} // namespace WTF

using WTF::CString;
