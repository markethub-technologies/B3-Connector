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

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/messaging/String.h>

#include <string>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

#if defined (_MSC_VER)

typedef signed char Int8;
typedef unsigned char UInt8;

typedef signed short Int16;
typedef unsigned short UInt16;

typedef signed int Int32;
typedef unsigned int UInt32;

typedef signed long long Int64;
typedef unsigned long long UInt64;

#elif defined (__GNUC__)

typedef signed char Int8;
typedef unsigned char UInt8;

typedef signed short Int16;
typedef unsigned short UInt16;

#if defined (__LP64__)

typedef signed int Int32;
typedef unsigned int UInt32;

typedef signed long Int64;
typedef unsigned long UInt64;

#else

typedef signed int Int32;
typedef unsigned int UInt32;

typedef signed long long Int64;
typedef unsigned long long UInt64;

#endif

#else

// Compiler is not (yet) supported.
// Integral types must be defined explicitly.

#error \
    Cannot identify compiler toolset to define integral types. \
    Please contact support@onixs.biz on further assistance.

#endif

/// Integral constant.
template
<
    typename Type,
    Type Constant
>
struct IntegralConstant
{
    /// Type of the constant.
    typedef Type Value;

    /// \return value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const ONIXS_B3_BOE_NOTHROW
    {
        return Constant;
    }

    /// \return value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const ONIXS_B3_BOE_NOTHROW
    {
        return Constant;
    }

    /// \return value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value() ONIXS_B3_BOE_NOTHROW
    {
        return Constant;
    }
};

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void toStr(std::string&, Int8);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    Int8 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string&,
    UInt8);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    UInt8 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string&,
    Int16);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    Int16 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string&,
    UInt16);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    UInt16 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string&,
    Int32);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    Int32 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string&,
    UInt32);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    UInt32 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string&,
    Int64);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    Int64 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the given integer into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string&,
    UInt64);

/// Serializes the given integer into a string.
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    UInt64 number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
size_t
toStr(
    Int8,
    Char*,
    size_t);


/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
size_t
toStr(
    UInt8,
    Char*,
    size_t);

/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
size_t
toStr(
    Int16,
    Char*,
    size_t);


/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
size_t
toStr(
    UInt16,
    Char*,
    size_t);


/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
size_t
toStr(
    Int32,
    Char*,
    size_t);


/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
size_t
ONIXS_B3_BOE_NODISCARD
toStr(
    UInt32,
    Char*,
    size_t);

/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
size_t
toStr(
    Int64,
    Char*,
    size_t);


/// Serializes the integer into the given buffer.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
size_t
toStr(
    UInt64,
    Char*,
    size_t);

/// Serializes the given constant into a string.
template
<
    typename Type,
    Type Constant
>
inline
void
toStr(
    std::string& str,
    IntegralConstant<Type, Constant> constant)
{
    toStr(str, constant());
}

/// Serializes the given constant into a string.
template
<
    typename Type,
    Type Constant
>
inline
ONIXS_B3_BOE_NODISCARD
std::string
toStr(
    IntegralConstant
    <Type, Constant> constant)
{
    std::string str;

    toStr(str, constant);

    return str;
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool fromStr(Int8&, const Char*, size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline ONIXS_B3_BOE_NODISCARD
bool fromStr(Int8& value, const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool
fromStr(
    UInt8&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline
ONIXS_B3_BOE_NODISCARD
bool fromStr(
    UInt8& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool
fromStr(
    Int16&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline
ONIXS_B3_BOE_NODISCARD
bool fromStr(
    Int16& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool
fromStr(
    UInt16&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline ONIXS_B3_BOE_NODISCARD
bool fromStr(
    UInt16& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool
fromStr(
    Int32&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline
ONIXS_B3_BOE_NODISCARD
bool fromStr(
    Int32& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool
fromStr(
    UInt32&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline
ONIXS_B3_BOE_NODISCARD
bool fromStr(
    UInt32& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool
fromStr(
    Int64&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline
ONIXS_B3_BOE_NODISCARD
bool fromStr(
    Int64& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool
fromStr(
    UInt64&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;

/// Deserializes a numeric value from its text representation.
///
/// \return `true` if the given buffer contains a valid representation
/// of a number. Otherwise, `false` is returned.
inline
ONIXS_B3_BOE_NODISCARD
bool fromStr(
    UInt64& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
