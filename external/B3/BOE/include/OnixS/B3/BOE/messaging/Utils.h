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

#include <cassert>

#include <OnixS/B3/BOE/ABI.h>

#ifdef ONIXS_B3_BOE_HAS_TYPE_TRAITS
#   include <type_traits>
#endif

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

#ifdef ONIXS_B3_BOE_HAS_TYPE_TRAITS

/// \private
template <bool B, class T = void>
using EnableIf = std::enable_if<B, T>;

/// \private
template <typename Base, typename Derived>
using IsBaseOf = std::is_base_of<Base, Derived>;

/// \private
template <class T>
using IsSigned = std::is_signed<T>;

#define CHECK_TYPE_INTEGRAL(Type) \
          static_assert( \
              std::is_integral<Type>::value, \
              #Type " must be an integral type, consider adding MemberTraits" \
              );
#else

/// \private
template <bool B, class T = void>
struct EnableIf
{
    typedef T type;
};

/// \private
template <class T>
struct EnableIf<false, T> {};

/// \private
template<typename Base, typename Derived>
struct IsBaseOf
{
    enum { value = __is_base_of(Base, Derived)};
};

/// \private
template<typename T>
struct IsSigned
{
    enum { value = (!(static_cast<T>(-1) > static_cast<T>(0))) };
};

#define CHECK_TYPE_INTEGRAL(Type)

#endif

///\private
namespace details {

    ///\private
    template <class T, class U>
    struct IsSameSignedness
    {
        enum { value = (static_cast<bool>(IsSigned<T>::value) == static_cast<bool>(IsSigned<U>::value)) };
    };

    ///\private
    template<typename T>
    struct HasMantissa
    {
        template<typename U> struct SFINAE {};
        template<typename U> static char test(SFINAE<typename U::Mantissa>*);
        template<typename U> static int test(...);
        enum { value = sizeof(test<T>(ONIXS_B3_BOE_NULLPTR)) == sizeof(char) };
    };

    ///\private
    template<typename T>
    struct HasExponent
    {
        template<typename U> struct SFINAE {};
        template<typename U> static char test(SFINAE<typename U::Exponent>*);
        template<typename U> static int test(...);
        enum { value = sizeof(test<T>(ONIXS_B3_BOE_NULLPTR)) == sizeof(char) };
    };

    ///\private
    template<typename T>
    struct IsDecimal
    {
        enum { value = HasMantissa<T>::value && HasExponent<T>::value };
    };

    ///\private
    template
        <
            class Decimal1,
            class Decimal2
        >
    struct AreBothDecimals
    {
        enum { value = IsDecimal<Decimal1>::value && IsDecimal<Decimal2>::value };
    };

    /// \private
    template<typename T>
    struct HasMemberTraits
    {
        template<typename U> struct SFINAE {};
        template<typename U> static char test(SFINAE<struct U::MemberTraits>*);
        template<typename U> static int test(...);
        enum { value = sizeof(test<T>(ONIXS_B3_BOE_NULLPTR)) == sizeof(char) };
    };

    /// \private
    template<typename T>
    struct HasValueStaticMember
    {
        template<typename U, typename U::Value (*)()> struct SFINAE {};
        template<typename U> static char test(SFINAE<U, &U::value>*);
        template<typename U> static int test(...);
        enum { value = sizeof(test<T>(ONIXS_B3_BOE_NULLPTR)) == sizeof(char) };
    };

    /// \private
    template<typename T>
    struct HasSerializeMember
    {
        template<typename U, void (U::*)(void*) const ONIXS_B3_BOE_NOTHROW> struct SFINAE {};
        template<typename U> static char test(SFINAE<U, &U::serialize>*);
        template<typename U> static int test(...);
        enum { value = sizeof(test<T>(ONIXS_B3_BOE_NULLPTR)) == sizeof(char) };
    };
}

///\private
template <class To, class From>
ONIXS_B3_BOE_PURE
inline
typename EnableIf<details::IsSameSignedness<To, From>::value, To>::type
    numericCast(From from) ONIXS_B3_BOE_NOTHROW
{
    const To to =
        static_cast<To>(from);

    assert(static_cast<From>(to) == from);

    return to;
}

///\private
template <class To, class From>
ONIXS_B3_BOE_PURE
inline
typename EnableIf<!details::IsSameSignedness<To, From>::value, To>::type
    numericCast(From from) ONIXS_B3_BOE_NOTHROW
{
    const To to =
        static_cast<To>(from);

    assert(static_cast<From>(to) == from);

    // The sign is lost during the conversion
    assert((to > static_cast<To>(0)) == (from > static_cast<From>(0)));

    return to;
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
