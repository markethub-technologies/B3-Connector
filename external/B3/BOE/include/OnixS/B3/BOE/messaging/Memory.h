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

#include <OnixS/B3/BOE/Compiler.h>
#include <OnixS/B3/BOE/messaging/Integral.h>
#include <OnixS/B3/BOE/messaging/Utils.h>

#include <cstddef>
#include <cstring>
#include <cassert>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Alias for Byte.
typedef UInt8 Byte;

/// Alias for Word.
typedef UInt16 Word;

/// Alias for Double Word.
typedef UInt32 DWord;

/// Alias for Quad Word.
typedef UInt64 QWord;

/// Makes the pointer an opaque one.
/// \private
template
<
    typename Type
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
void*
toOpaquePtr(Type* ptr)
    ONIXS_B3_BOE_NOTHROW
{
    assert(ptr);
    return static_cast<void*>(ptr);
}

/// Makes the pointer an opaque one.
/// \private
template
<
    typename Type
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
const void*
toOpaquePtr(const Type* ptr)
    ONIXS_B3_BOE_NOTHROW
{
    assert(ptr);
    return static_cast<const void*>(ptr);
}

/// \private
template
<
    typename Type
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
void* toMutable(const Type* ptr) ONIXS_B3_BOE_NOTHROW
{
    assert(ptr);
    return const_cast<void*>(static_cast<const void*>(ptr));
}

/// Reinterprets the pointer as a byte block one.
/// \private
template
<
    typename Type
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
Byte*
toByteBlock(Type* ptr)
    ONIXS_B3_BOE_NOTHROW
{
    assert(ptr);

    return
        static_cast
        <Byte*>
        (toOpaquePtr(ptr));
}

/// Reinterprets the pointer as a byte block one.
/// \private
template
<
    typename Type
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
const Byte*
toByteBlock(const Type* ptr)
    ONIXS_B3_BOE_NOTHROW
{
    assert(ptr);

    return
        static_cast
        <const Byte*>
        (toOpaquePtr(ptr));
}

/// Advances the pointer to a given offset (distance) in bytes.
/// \private
template
<
    typename Type
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
Type* advanceByBytes(Type* pointer, ptrdiff_t distance) ONIXS_B3_BOE_NOTHROW
{
    assert(pointer);

    return reinterpret_cast<Type*>(toByteBlock(pointer) + distance);
}

/// \return a pointer that is lower than
/// the given one by a given number of bytes.
/// \private
template
<
    typename Type
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
Type*
advanceBackByBytes(
    Type* pointer,
    ptrdiff_t distance)
    ONIXS_B3_BOE_NOTHROW
{
    assert(pointer);

    return
        reinterpret_cast<Type*>
        (
            toByteBlock(pointer) - distance
        );
}

/// \return the distance in bytes between two pointers.
/// \private
template
<
    typename Left,
    typename Right
>
ONIXS_B3_BOE_HOTPATH
ONIXS_B3_BOE_PURE
ptrdiff_t
byteDistance(
    Left* left,
    Right* right)
    ONIXS_B3_BOE_NOTHROW
{
    assert(left);
    assert(right);

    return (
        toByteBlock(left) -
        toByteBlock(right)
    );
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_HOTPATH
Value
extractValue(const void* location) ONIXS_B3_BOE_NOTHROW
{
    assert(location);

    // [VG] The following line must be commented to enable composite reading, though I not sure that is right:
    // CHECK_TYPE_INTEGRAL(Value);

    Value result;

    std::memcpy(
        &result,
        location,
        sizeof(Value));

    return result;
}

/// \private
template <unsigned ArgsCount>
struct CompositeExtractor;

/// \private
template <>
struct CompositeExtractor<1>
{
    template <class Value>
    static
    Value extract(const void* location) ONIXS_B3_BOE_NOTHROW
    {

#if defined (ONIXS_B3_BOE_CXX11)
        static_assert(
            noexcept(
                Value(
                    std::declval<typename Value::MemberTraits::FirstArgType>()
                )
            ) ,
            "must be noexcept");
#endif

        assert(location);

        return
            Value(
                extractValue<typename Value::MemberTraits::FirstArgType>(location)
            );
    }
};

/// \private
template <>
struct CompositeExtractor<2>
{
    template <class Value>
    static
    Value extract(const void* location) ONIXS_B3_BOE_NOTHROW
    {
        typedef typename Value::MemberTraits::FirstArgType FirstArgType;
        typedef typename Value::MemberTraits::SecondArgType SecondArgType;

#if defined (ONIXS_B3_BOE_CXX11)
        static_assert(
            noexcept(
                Value(
                    std::declval<FirstArgType>(),
                    std::declval<SecondArgType>()
                )
            ) ,
            "must be noexcept");
#endif

        assert(location);

        return
            Value(
                extractValue<FirstArgType>(location),
                extractValue<SecondArgType>(
                    advanceByBytes(location, sizeof(FirstArgType)))
            );
    }
};

/// \private
template <>
struct CompositeExtractor<4>
{
    template <class Value>
    static
    Value extract(const void* location) ONIXS_B3_BOE_NOTHROW
    {
        typedef typename Value::MemberTraits::FirstArgType FirstArgType;
        typedef typename Value::MemberTraits::SecondArgType SecondArgType;
        typedef typename Value::MemberTraits::ThirdArgType ThirdArgType;
        typedef typename Value::MemberTraits::FourthArgType FourthArgType;

#if defined (ONIXS_B3_BOE_CXX11)
        static_assert(
            noexcept(
                Value(
                    std::declval<FirstArgType>(),
                    std::declval<SecondArgType>(),
                    std::declval<ThirdArgType>(),
                    std::declval<FourthArgType>()
                )
            ) ,
            "must be noexcept");
#endif

        assert(location);

        return
            Value(
                extractValue<FirstArgType>(location),
                extractValue<SecondArgType>(
                    advanceByBytes(location, sizeof(FirstArgType))),
                extractValue<ThirdArgType>(
                    advanceByBytes(location, sizeof(FirstArgType) + sizeof(SecondArgType))),
                extractValue<FourthArgType>(
                    advanceByBytes(location, sizeof(FirstArgType) + sizeof(SecondArgType) + sizeof(ThirdArgType)))
            );
    }
};

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_HOTPATH
typename EnableIf<details::HasMemberTraits<Value>::value, Value>::type
getValue(const void* location) ONIXS_B3_BOE_NOTHROW
{
    assert(location);
    return CompositeExtractor<Value::MemberTraits::Count>:: template extract<Value>(location);
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_HOTPATH
typename EnableIf<!details::HasMemberTraits<Value>::value, Value>::type
getValue(const void* location) ONIXS_B3_BOE_NOTHROW
{
    assert(location);
    return extractValue<Value>(location);
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_CONSTEXPR
typename EnableIf<!details::HasMemberTraits<Value>::value, size_t>::type
size() ONIXS_B3_BOE_NOTHROW
{
    return sizeof(Value);
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_CONSTEXPR
typename EnableIf<details::HasMemberTraits<Value>::value, size_t>::type
size() ONIXS_B3_BOE_NOTHROW
{
    return Value::Size;
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_HOTPATH
typename EnableIf<!details::HasSerializeMember<Value>::value>::type
commitValue(void* location, Value value)
    ONIXS_B3_BOE_NOTHROW
{
    assert(location);
    std::memcpy(
        location,
        &value,
        sizeof(Value));
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_HOTPATH
typename EnableIf<details::HasSerializeMember<Value>::value>::type
commitValue(void* location, Value value)
    ONIXS_B3_BOE_NOTHROW
{
    assert(location);
    value.serialize(location);
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_HOTPATH
typename EnableIf<!details::HasValueStaticMember<Value>::value>::type
setValue(void* location, Value value)
    ONIXS_B3_BOE_NOTHROW
{
    assert(location);
    commitValue(location, value);
}

/// \private
template
<
    class Value
>
ONIXS_B3_BOE_HOTPATH
typename EnableIf<details::HasValueStaticMember<Value>::value>::type
setValue(void* location, Value)
    ONIXS_B3_BOE_NOTHROW
{
    assert(location);
    commitValue(location, Value::value());
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
