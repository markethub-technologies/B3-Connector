// Copyright Onix Solutions Limited [OnixS]. All rights reserved.
//
// This software owned by Onix Solutions Limited [OnixS] and is
// protected by copyright law and international copyright treaties.
//
// Access to and use of the software is governed by the terms of the applicable
// OnixS Software Services Agreement (the Agreement) and Customer end user license
// agreements granting a non-assignable, non-transferable and non-exclusive license
// to use the software for it's own data processing purposes under the terms defined
// in the Agreement.
//
// Except as otherwise granted within the terms of the Agreement, copying or
// reproduction of any part of this source code or associated reference material
// to any other location for further reproduction or redistribution, and any
// amendments to this copyright notice, are expressly prohibited.
//
// Any reproduction or redistribution for sale or hiring of the Software not in
// accordance with the terms of the Agreement is a violation of copyright law.
//

#pragma once

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Aliases.h>
#include <OnixS/B3/MarketData/UMDF/messaging/String.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Utils.h>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>

#if defined(ONIXS_B3_UMDF_MD_HAS_STRING_VIEW)
#include <string_view>
#endif


ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

#if defined(ONIXS_B3_UMDF_MD_HAS_STRING_VIEW)

using StrRef = std::basic_string_view<Char>;

#else

/// \private
/// Throws exception on invalid index
ONIXS_B3_UMDF_MD_EXPORTED
ONIXS_B3_UMDF_MD_COLDPATH
ONIXS_B3_UMDF_MD_NORETURN
void throwInvalidIndex(size_t, size_t);

/// String reference.
///
/// Provides the efficient way of accessing
/// text-based values without copying
/// content of the text being referred.
ONIXS_B3_UMDF_MD_LTWT_CLASS StrRef
{
public:
    typedef size_t size_type;

    /// STL-like iterators.
    typedef const Char* const_iterator;
    typedef const_iterator iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef const_reverse_iterator reverse_iterator;

    /// Initializes the instance referring to nothing.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    StrRef()
        : items_(ONIXS_B3_UMDF_MD_NULLPTR)
        , size_(0)
    {
    }

    /// Explicit initialization.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    StrRef(const Char* chars, size_t size) ONIXS_B3_UMDF_MD_NOTHROW
        : items_(chars)
        , size_((ONIXS_B3_UMDF_MD_ASSERT(size <= (std::numeric_limits<size_type>::max)()), static_cast<size_type>(size)))
    {
    }

    /// Explicit initialization.
    StrRef(const Char* chars) ONIXS_B3_UMDF_MD_NOTHROW
        : items_(chars)
        , size_(0)
    {
        assert(chars);

        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR size_type maxLen = (std::numeric_limits<UInt16>::max)();

        size_ = numericCast<size_type>(strnlen(chars, maxLen));

        assert(size_ < maxLen);
    }

    /// Explicit initialization.
    StrRef(const std::string& string)
        : items_(string.c_str())
        , size_(static_cast<size_type>(string.length()))
    {
        assert(string.length() <= (std::numeric_limits<size_type>::max)());
    }

    /// \return `true` if the reference is empty, otherwise - `false`.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool empty() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (0 == size_);
    }

    /// \return the read-only content.
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    const Char* data() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return items_;
    }

    /// \return the number of characters.
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    size_type size() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return size_;
    }

    ONIXS_B3_UMDF_MD_CONSTEXPR
    ONIXS_B3_UMDF_MD_NODISCARD
    /// \return the the number of characters.
    size_type length() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return size_;
    }

    /// STL-like begin().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_iterator begin() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        assert(items_);
        return items_;
    }

    /// STL-like end().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_iterator end() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        assert(items_);
        return (items_ + size_);
    }

    /// STL-like cbegin().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_iterator cbegin() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return begin();
    }

    /// STL-like cend().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_iterator cend() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return end();
    }

    /// STL-like rbegin().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_reverse_iterator rbegin() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return const_reverse_iterator(end());
    }

    /// STL-like rend().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_reverse_iterator rend() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return const_reverse_iterator(begin());
    }

    /// STL-like crbegin().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_reverse_iterator crbegin() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return rbegin();
    }

    /// STL-like crend().
    ONIXS_B3_UMDF_MD_NODISCARD
    const_reverse_iterator crend() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return rend();
    }

    /// Provides the per-item access.
    ONIXS_B3_UMDF_MD_NODISCARD
    const Char& operator [](size_type index) const ONIXS_B3_UMDF_MD_NOTHROW
    {
        assert(index < size_);
        assert(items_);

        return items_[index];
    }

    /// Provides the bound-checked per-item access.
    ONIXS_B3_UMDF_MD_NODISCARD
    const Char& at(size_type index) const
    {
        assert(items_);

        if (index < size_)
            return items_[index];

        throwInvalidIndex(index, size_);
    }

    /// \return the reference to the first character in the view.
    const Char& front() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        assert(!empty());
        return (*this)[0];
    }

    /// \return the reference to the last character in the view.
    const Char& back() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        assert(!empty());
        return (*this)[size_ - 1];
    }

    /// Swaps the content with the given instance.
    void swap(StrRef& other) ONIXS_B3_UMDF_MD_NOTHROW
    {
        std::swap(items_, other.items_);

        std::swap(size_, other.size_);
    }

    /// Converts to std::basic_string
    operator std::basic_string<Char>() const
    {
        return std::basic_string<Char>(data(), size());
    }

private:
    /// Items being referenced.
    const Char* items_;

    /// the number of characters being referenced.
    size_type size_;
};

/// Compares instances.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator ==(const StrRef& left, const StrRef& right)
{
    if(left.size() != right.size())
        return false;

    if(left.empty())
    {
        assert(right.empty());
        return true;
    }

    assert(left.data());
    assert(right.data());

    return (0 == memcmp(
        left.data(), right.data(), left.size()));
}

/// Compares instances.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator !=(const StrRef& left, const StrRef& right)
{
    return !(left == right);
}

/// Compares instances.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator <(const StrRef& left, const StrRef& right)
{
    const int
        result =
        memcmp(
            left.data(),
            right.data(),
            left.size() < right.size()
                ? left.size()
                : right.size());

    return (
        0 != result
            ? (0 > result)
            : (left.size() < right.size()));
}

/// Compares instances.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator >(const StrRef& left, const StrRef& right)
{
    return (right < left);
}

/// StrRef serialization operator.
inline
std::ostream& operator <<(std::ostream& stream, const StrRef& text)
{
    stream.write(text.data(), text.size());

    return stream;
}

ONIXS_B3_UMDF_MD_NODISCARD StrRef toStrRef(const std::string&);
ONIXS_B3_UMDF_MD_NODISCARD StrRef toStrRef(const Char*) ONIXS_B3_UMDF_MD_NOTHROW;

/// Compares StrRef with std::string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator ==(const StrRef& ref, const std::string& str)
{
    return ref == toStrRef(str);
}

/// Compares StrRef with std::string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator !=(const StrRef& ref, const std::string& str)
{
    return ref != toStrRef(str);
}

/// Compares StrRef with std::string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator ==(const std::string& str, const StrRef& ref)
{
    return ref == toStrRef(str);
}

/// Compares StrRef with std::string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator !=(const std::string& str, const StrRef& ref)
{
    return ref != toStrRef(str);
}

/// Compares StrRef with a zero-terminated/C-like string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator ==(const StrRef& ref, const Char* str)
{
    return ref == toStrRef(str);
}

/// Compares StrRef with a zero-terminated/C-like string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator !=(const StrRef& ref, const Char* str)
{
    return ref != toStrRef(str);
}

/// Compares StrRef with a zero-terminated/C-like string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator ==(const Char* str, const StrRef& ref)
{
    return ref == toStrRef(str);
}

/// Compares StrRef with a zero-terminated/C-like string.
ONIXS_B3_UMDF_MD_NODISCARD
inline
bool operator !=( const Char* str, const StrRef& ref)
{
    return ref != toStrRef(str);
}

#endif

/// Constructs a StrRef instance over th std::string content.
ONIXS_B3_UMDF_MD_NODISCARD
inline StrRef toStrRef(const std::string& str)
{
    return StrRef(str);
}

/// Initializes the instance from a zero-terminated/C-like string.
ONIXS_B3_UMDF_MD_NODISCARD
inline StrRef toStrRef(const Char* cStr) ONIXS_B3_UMDF_MD_NOTHROW
{
    return
        (cStr != ONIXS_B3_UMDF_MD_NULLPTR) ?
        StrRef(cStr) :
        StrRef()
        ;
}

template <size_t Size>
ONIXS_B3_UMDF_MD_NODISCARD
inline
ONIXS_B3_UMDF_MD_CONSTEXPR
StrRef constructStrRef(const char (&value)[Size])
    ONIXS_B3_UMDF_MD_NOTHROW
{
    return StrRef(value, Size - 1);
}

template <size_t Size>
ONIXS_B3_UMDF_MD_NODISCARD
inline
ONIXS_B3_UMDF_MD_CONSTEXPR
StrRef strRefFromCharArray(const char (&value)[Size])
ONIXS_B3_UMDF_MD_NOTHROW
{
    return StrRef(value, Size);
}

/// Constructs a std::string instance from the StrRef one.
ONIXS_B3_UMDF_MD_NODISCARD
inline
std::string toStr(const StrRef& ref)
{
    return std::string(ref.data(), ref.size());
}

/// Appends the text referenced by StrRef to the given std::string instance.
inline
void toStr(std::string& str, const StrRef& ref)
{
    str.append(ref.data(), ref.size());
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
