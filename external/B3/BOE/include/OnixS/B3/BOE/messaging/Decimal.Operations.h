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

#include <OnixS/B3/BOE/messaging/Decimal.h>
#include <OnixS/B3/BOE/messaging/Composites.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// \private
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwCannotQuantizeOrConvert();

/// Universal decimal type.
typedef FloatingPointDecimal<Int64, Int32> Decimal;
//

/// \private
ONIXS_B3_BOE_CONSTEXPR
inline bool isNull(const Decimal&) ONIXS_B3_BOE_NOTHROW
{
    return false;
}

/// Quantize so its exponent is the same as that of provided value.
///
/// \return `false` if the value cannot be quantized.
ONIXS_B3_BOE_EXPORTED
bool
quantize(
    const Decimal& operand,
    Int32 exponent,
    Decimal& quantized);

/// Quantize so its exponent is the same as that of provided value.
///
/// \throw std::exception if the value cannot be quantized.
///
/// \return resulting decimal.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
Decimal quantize(const Decimal& operand, Int32 exponent);

/// Quantize so its exponent is the same as that of provided value.
///
/// \throw std::exception if the value cannot be quantized
///
/// \return resulting decimal mantissa
template <class MantissaType>
ONIXS_B3_BOE_NODISCARD
MantissaType quantizedMantissa(const Decimal& operand, Int32 exponent)
{
    const Decimal::Mantissa res =
        quantize(
            operand, exponent)
                .mantissa();

    if(static_cast<MantissaType>(
        (std::numeric_limits<MantissaType>::max)()) >= res)
    {
        return static_cast<MantissaType>(res);
    }

    throwCannotQuantizeOrConvert();
}

template
<
    class MantissaType,
    class ExponentType
>
void convert(
    FixedPointDecimal<MantissaType, ExponentType>& res,
    const Decimal& number)
{
    res =
        FixedPointDecimal<MantissaType, ExponentType>(
            quantizedMantissa<MantissaType>(number, ExponentType()));
}

template
    <
        class MantissaType,
        class ExponentType
    >
void convert(
    FloatingPointDecimal<MantissaType, ExponentType>& res,
    const Decimal& number)
{
    if(static_cast<MantissaType>(
           (std::numeric_limits<MantissaType>::max)()) < number.mantissa())
    {
        throwCannotQuantizeOrConvert();
    }

    res =
        FloatingPointDecimal<MantissaType, ExponentType>(
            static_cast<MantissaType>(number.mantissa()),
            number.exponent());
}

/// Convert the decimal in to a different one.
///
/// \throw std::exception if the value cannot be converted
///
/// \return resulting decimal
template
<
    class DecimalT
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
typename EnableIf<details::IsDecimal<DecimalT>::value, DecimalT>::type
    convert(const Decimal& number)
{
    DecimalT res;
    convert(res, number);
    return res;
}

/// \private
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_PURE
bool decimalEqual(
    const Decimal& left, const Decimal& right) ONIXS_B3_BOE_NOTHROW;

/// \private
inline bool operator ==(const Decimal& left, const Decimal& right) ONIXS_B3_BOE_NOTHROW
{
    return ((left.exponent() == right.exponent()) ? (left.mantissa() == right.mantissa()) : decimalEqual(left, right));
}

/// \private
inline bool operator!=(
    const Decimal& left, const Decimal& right)
{
    return ((left.exponent() == right.exponent()) ? (left.mantissa() != right.mantissa()) : !decimalEqual(left, right));
}

/// \private
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_PURE
bool decimalLess(
    const Decimal& left, const Decimal& right) ONIXS_B3_BOE_NOTHROW;

/// \private
inline bool operator <(
    const Decimal& left, const Decimal& right) ONIXS_B3_BOE_NOTHROW
{
    return ((left.exponent() == right.exponent()) ? (left.mantissa() < right.mantissa()) : decimalLess(left, right));
}

/// \private
inline bool operator<=(
    const Decimal& left, const Decimal& right)
{
    return !(right < left);
}

/// \private
inline
ONIXS_B3_BOE_PURE
bool
operator >(
    const Decimal& left,
    const Decimal& right)
{
    return (right < left);
}

/// \private
inline
ONIXS_B3_BOE_PURE
bool
operator >=(
    const Decimal& left,
    const Decimal& right)
{
    return (right <= left);
}

/// \private.
ONIXS_B3_BOE_EXPORTED
void
decimalToStr(
    std::string&,
    Int64,
    Int32);

/// \private.
ONIXS_B3_BOE_EXPORTED
size_t
toStr(
    const Decimal&,
    Char* buf,
    size_t size);

/// Deserializes a decimal number
/// from the given text presentation.
ONIXS_B3_BOE_EXPORTED
bool
fromStr(
    Decimal&,
    const Char*,
    size_t) ONIXS_B3_BOE_NOTHROW;


/// Deserializes a decimal number
/// from the given text presentation.
inline
bool
fromStr(
    Decimal& value,
    const std::string& str) ONIXS_B3_BOE_NOTHROW
{
    return
        fromStr(
            value,
            str.c_str(),
            str.size());
}

/// \private
inline
void
toStr(
    std::string& str,
    const Decimal& number)
{
    decimalToStr
        (
            str,
            number.mantissa(),
            number.exponent()
        );
}

/// Serializes floating-point decimal into a string.
template
<
    class Mantissa,
    class Exponent
>
inline
void
toStr(
    std::string& str,
    const
    FloatingPointDecimal
        <Mantissa, Exponent>& number)
{
    if(isNull(number))
    {
        str += "[]";
        return;
    }

    toStr(str, Decimal(number));
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
    FloatingPointDecimal
        <Mantissa, Exponent>& value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes a fixed-point decimal into a string.
template
<
    class Mantissa,
    class Exponent
>
inline
void
toStr(
    std::string& str,
    const
    FixedPointDecimal
        <Mantissa, Exponent>& number)
{
    if(isNull(number))
    {
        str += "[]";
        return;
    }

    toStr(str, Decimal(number));
}

/// Serializes a floating-point decimal into a string.
template
<
    class Mantissa,
    class Exponent
>
inline ONIXS_B3_BOE_NODISCARD
std::string toStr(const FloatingPointDecimal<Mantissa, Exponent>& number)
{
    std::string str;

    toStr(str, number);

    return str;
}

/// Serializes a fixed-point decimal into a string.
template
<
    class Mantissa,
    class Exponent
>
inline
ONIXS_B3_BOE_NODISCARD
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
inline
std::ostream& operator << (std::ostream& stream, const Decimal& value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
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

///\private
template
<
    class Decimal1,
    class Decimal2
>
void checkAgsValid(
    const Decimal1& arg1, const Decimal2& arg2)
{
    if(isNull(arg1) || isNull(arg2))
        throw std::invalid_argument("Provided argument is Null.");
}

/// Compares two fixed-point decimals.
template
<
    class Mantissa,
    class Exponent
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
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
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
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
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
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
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
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
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
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
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
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

/// Compares two decimals.
template
<
    class Decimal1,
    class Decimal2
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
typename EnableIf<details::AreBothDecimals<Decimal1, Decimal2>::value, bool>::type
operator==(
    const Decimal1& left, const Decimal2& right)
{
    if(isNull(left) && isNull(right))
        return true;

    return Decimal(left) == Decimal(right);
}

/// Compares two decimals.
template
<
    class Decimal1,
    class Decimal2
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
typename EnableIf<details::AreBothDecimals<Decimal1, Decimal2>::value, bool>::type
operator!=(
    const Decimal1& left, const Decimal2& right)
{
    return !(left == right);
}

/// Compares two decimals.
template
<
    class Decimal1,
    class Decimal2
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
typename EnableIf<details::AreBothDecimals<Decimal1, Decimal2>::value, bool>::type
operator>(
    const Decimal1& left, const Decimal2& right)
{
    checkAgsValid(left, right);

    return Decimal(left) > Decimal(right);
}

/// Compares two decimals.
template
<
    class Decimal1,
    class Decimal2
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
typename EnableIf<details::AreBothDecimals<Decimal1, Decimal2>::value, bool>::type
operator>=(
    const Decimal1& left, const Decimal2& right)
{
    checkAgsValid(left, right);

    return Decimal(left) >= Decimal(right);
}

/// Compares two decimals.
template
<
    class Decimal1,
    class Decimal2
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
typename EnableIf<details::AreBothDecimals<Decimal1, Decimal2>::value, bool>::type
operator<(
    const Decimal1& left, const Decimal2& right)
{
    checkAgsValid(left, right);

    return Decimal(left) < Decimal(right);
}

/// Compares two decimals.
template
<
    class Decimal1,
    class Decimal2
>
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
typename EnableIf<details::AreBothDecimals<Decimal1, Decimal2>::value, bool>::type
operator<=(
    const Decimal1& left, const Decimal2& right)
{
    checkAgsValid(left, right);

    return Decimal(left) <= Decimal(right);
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
