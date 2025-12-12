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

#include <OnixS/B3/MarketData/UMDF/messaging/Decimal.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Composites.h>

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

/// Serializes a fixed-point decimal into a string.
template
<
    class Mantissa,
    class Exponent
>
inline
ONIXS_B3_UMDF_MD_NODISCARD
std::string
toStr(
    const
    FixedPointDecimal
        <
            Mantissa,
            Exponent
        >& number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes into a stream.
template
    <
        class Mantissa,
        class Exponent
    >
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Compares two fixed-point decimals.
template
<
    class Mantissa,
    class Exponent
>
ONIXS_B3_UMDF_MD_NODISCARD
ONIXS_B3_UMDF_MD_PURE
bool
operator ==(
    const
    FixedPointDecimal
        <Mantissa, Exponent>& left,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& right)
{
    if(isNull(left) && isNull(right))
        return true;

    return left.mantissa() == right.mantissa();
}

/// Compares two fixed-point decimals.
template
<
    class Mantissa,
    class Exponent
>
ONIXS_B3_UMDF_MD_NODISCARD
ONIXS_B3_UMDF_MD_PURE
bool
operator !=(
    const
    FixedPointDecimal
        <Mantissa, Exponent>& left,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& right)
{
    return !(left == right);
}

/// Compares two fixed-point decimals.
template
<
    class Mantissa,
    class Exponent
>
ONIXS_B3_UMDF_MD_NODISCARD
ONIXS_B3_UMDF_MD_PURE
bool
operator <(
    const
    FixedPointDecimal
        <Mantissa, Exponent>& left,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& right)
{
    checkAgsValid(left, right);

    return left.mantissa() < right.mantissa();
}

/// Compares two fixed-point decimals.
template
<
    class Mantissa,
    class Exponent
>
ONIXS_B3_UMDF_MD_NODISCARD
ONIXS_B3_UMDF_MD_PURE
bool
operator >(
    const
    FixedPointDecimal
        <Mantissa, Exponent>& left,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& right)
{
    checkAgsValid(left, right);

    return left.mantissa() > right.mantissa();
}

/// Compares two fixed-point decimals.
template
<
    class Mantissa,
    class Exponent
>
ONIXS_B3_UMDF_MD_NODISCARD
ONIXS_B3_UMDF_MD_PURE
bool
operator <=(
    const
    FixedPointDecimal
        <Mantissa, Exponent>& left,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& right)
{
    checkAgsValid(left, right);

    return left.mantissa() <= right.mantissa();
}

/// Compares two fixed-point decimals.
template
<
    class Mantissa,
    class Exponent
>
ONIXS_B3_UMDF_MD_NODISCARD
ONIXS_B3_UMDF_MD_PURE
bool
operator >=(
    const
    FixedPointDecimal
        <Mantissa, Exponent>& left,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& right)
{
    checkAgsValid(left, right);

    return left.mantissa() >= right.mantissa();
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
