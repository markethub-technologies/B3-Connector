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

#include <OnixS/B3/MarketData/UMDF/messaging/Memory.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Decimal.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Fields.h>

#ifdef DELETE
#undef DELETE
#endif

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN
ONIXS_B3_UMDF_MD_DATA_PACKING_BEGIN(1)

/// Message identifiers and length of message root.
ONIXS_B3_UMDF_MD_LTWT_CLASS MessageHeader
{
public:
    /// Size of the composite.
    enum { Size = 8 };

    /// Root block length.
    typedef UInt16 BlockLength;

    /// Template ID.
    typedef UInt16 TemplateId;

    /// Schema ID.
    typedef UInt16 SchemaId;

    /// Schema Version.
    typedef UInt16 Version;

    /// Root block length.
    ONIXS_B3_UMDF_MD_NODISCARD
    BlockLength blockLength() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return blockLength_;
    }

    /// Template ID.
    ONIXS_B3_UMDF_MD_NODISCARD
    TemplateId templateId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return templateId_;
    }

    /// Schema ID.
    ONIXS_B3_UMDF_MD_NODISCARD
    SchemaId schemaId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return schemaId_;
    }

    /// Schema Version.
    ONIXS_B3_UMDF_MD_NODISCARD
    Version version() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return version_;
    }

private:
    BlockLength blockLength_;
    TemplateId templateId_;
    SchemaId schemaId_;
    Version version_;
};


/// Repeating group dimensions.
ONIXS_B3_UMDF_MD_LTWT_CLASS GroupSizeEncoding
{
public:
    /// Size of the composite.
    enum { Size = 3 };

    /// Root block length.
    typedef UInt16 BlockLength;

    /// A counter representing the number of entries in a repeating group.
    ///
    /// FIX type: NumInGroup.
    typedef UInt8 NumInGroup;

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string
    toString() const;

    /// Root block length.
    ONIXS_B3_UMDF_MD_NODISCARD
    BlockLength blockLength() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return blockLength_;
    }

    /// A counter representing the number of entries in a repeating group.
    ///
    /// FIX type: NumInGroup.
    ONIXS_B3_UMDF_MD_NODISCARD
    NumInGroup numInGroup() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return numInGroup_;
    }

private:
    BlockLength blockLength_;
    NumInGroup numInGroup_;
};


/// Price (4 decimal places). Usually 3 places are enough, but FX requires 4.
///
/// FIX type: Price.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -4>
>
Price;

/// Optional price (4 decimal places). Usually 3 places are enough, but FX requires 4.
///
/// FIX type: Price.
typedef
NullableFixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -4>,
    IntegralConstant<Int64, -9223372036854775807LL-1>
>
PriceOptional;

/// Null values definition for optional PriceOptional field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullPriceOptional
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef PriceOptional Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }
};

/// \return whether the given value is Null.
ONIXS_B3_UMDF_MD_NODISCARD
inline bool
isNull(
    const PriceOptional& value)
    ONIXS_B3_UMDF_MD_NOTHROW
{
    return value.isNull();
}

/// Optional percentage (4 decimal places).
///
/// FIX type: Percentage.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -4>
>
Percentage;

/// Null values definition for optional Percentage field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullPercentage
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef Percentage Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, 0LL>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// Ratio of quantity relative to the whole thing.
///
/// FIX type: Qty.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -7>
>
RatioQty;

/// Null values definition for optional RatioQty field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullRatioQty
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef RatioQty Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// Optional decimal with constant exponent -8.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -8>
>
Fixed8;

/// Null values definition for optional Fixed8 field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullFixed8
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef Fixed8 Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// Price (8 decimal places). For prices subjected to be adjusted from corporate events.
///
/// FIX type: Price.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -8>
>
Price8;

/// Price Offset (8 decimal places). Offsets related to prices subjected to be adjusted from corporate events.
///
/// FIX type: Price.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -8>
>
PriceOffset8Optional;

/// Null values definition for optional PriceOffset8Optional field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullPriceOffset8Optional
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef PriceOffset8Optional Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// DATA Field.
/// FIX type: data.
ONIXS_B3_UMDF_MD_LTWT_STRUCT TextEncoding
{
public:
    /// Size of the composite.
    enum { Size = 1 };

    /// Length type.
    typedef UInt8 Length;

    /// VarData type.
    typedef Char VarData;

    /// \return length.
    ONIXS_B3_UMDF_MD_NODISCARD
    Length length() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return length_;
    }

    /// \return the varData field.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef varData() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return StrRef(reinterpret_cast<const Char*>(this) + Size, length());
    }

        /// \return a human-readable presentation.
        ONIXS_B3_UMDF_MD_NODISCARD
        std::string
        toString() const;


    /// \return Size of SBE-encoded data representing the field.
    ONIXS_B3_UMDF_MD_NODISCARD
    Length binarySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Size + length();
    }

private:
    Length length_;
};


/// DATA Field.
/// FIX type: data.
ONIXS_B3_UMDF_MD_LTWT_STRUCT VarString
{
public:
    /// Size of the composite.
    enum { Size = 2 };

    /// Length type.
    typedef UInt16 Length;

    /// VarData type.
    typedef UInt8 VarData;

    /// \return length.
    ONIXS_B3_UMDF_MD_NODISCARD
    Length length() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return length_;
    }

    /// \return the varData field.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef varData() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return StrRef(reinterpret_cast<const Char*>(this) + Size, length());
    }

        /// \return a human-readable presentation.
        ONIXS_B3_UMDF_MD_NODISCARD
        std::string
        toString() const;


    /// \return Size of SBE-encoded data representing the field.
    ONIXS_B3_UMDF_MD_NODISCARD
    Length binarySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Size + length();
    }

private:
    Length length_;
};


typedef MessageHeader MessageHeaderBuilder;

ONIXS_B3_UMDF_MD_DATA_PACKING_END

/// UTC timestamp with nanosecond precision (Unix Epoch).
///
/// FIX type: UTCTimestamp.
ONIXS_B3_UMDF_MD_LTWT_CLASS UTCTimestampNanos
{
public:
    /// Size of the composite.
    enum { Size = 8 };

    /// UTC timestamp with nanosecond precision (Unix Epoch).
    typedef UInt64 Time;

    /// Null value for an optional Time field.
    typedef
    IntegralConstant<UInt64, 0ULL>
    NullTime;

    /// time unit (nanoseconds).
    typedef
    IntegralConstant<UInt8, TimeUnit::NANOSECOND>
    Unit;

    /// Default constructor.
    ///
    /// Initializes fields with appropriate null values.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    UTCTimestampNanos()
        ONIXS_B3_UMDF_MD_NOTHROW
      : time_(NullTime::value())
    {
    }

    /// Initializes fields with provided values
    explicit
    ONIXS_B3_UMDF_MD_CONSTEXPR
    UTCTimestampNanos(Time time)
        ONIXS_B3_UMDF_MD_NOTHROW
      : time_(time)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string
    toString() const;

    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef Time FirstArgType;
    };

    /// UTC timestamp with nanosecond precision (Unix Epoch).
    ONIXS_B3_UMDF_MD_NODISCARD
    Time time() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return time_;
    }

    /// time unit (nanoseconds).
    ONIXS_B3_UMDF_MD_NODISCARD
    TimeUnit::Enum unit() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return TimeUnit::NANOSECOND;
    }

private:
    Time time_;
};


/// Null values definition for optional UTCTimestampNanos field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullUTCTimestampNanos
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef UTCTimestampNanos Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           UTCTimestampNanos::NullTime() ==
           other.time());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }
};


/// UTC timestamp with second precision (Unix Epoch).
///
/// FIX type: UTCTimestamp.
ONIXS_B3_UMDF_MD_LTWT_CLASS UTCTimestampSeconds
{
public:
    /// Size of the composite.
    enum { Size = 8 };

    /// UTC timestamp with second precision (Unix Epoch).
    typedef Int64 Time;

    /// Null value for an optional Time field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullTime;

    /// time unit (seconds).
    typedef
    IntegralConstant<UInt8, TimeUnit::SECOND>
    Unit;

    /// Default constructor.
    ///
    /// Initializes fields with appropriate null values.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    UTCTimestampSeconds()
        ONIXS_B3_UMDF_MD_NOTHROW
      : time_(NullTime::value())
    {
    }

    /// Initializes fields with provided values
    explicit
    ONIXS_B3_UMDF_MD_CONSTEXPR
    UTCTimestampSeconds(Time time)
        ONIXS_B3_UMDF_MD_NOTHROW
      : time_(time)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string
    toString() const;

    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef Time FirstArgType;
    };

    /// UTC timestamp with second precision (Unix Epoch).
    ONIXS_B3_UMDF_MD_NODISCARD
    Time time() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return time_;
    }

    /// time unit (seconds).
    ONIXS_B3_UMDF_MD_NODISCARD
    TimeUnit::Enum unit() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return TimeUnit::SECOND;
    }

private:
    Time time_;
};


/// Null values definition for optional UTCTimestampSeconds field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullUTCTimestampSeconds
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef UTCTimestampSeconds Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           UTCTimestampSeconds::NullTime() ==
           other.time());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }
};


/// Week, month and year of the maturity (used for standardized futures and options).
///
/// FIX type: MonthYear.
ONIXS_B3_UMDF_MD_LTWT_CLASS MaturityMonthYear
{
public:
    /// Size of the composite.
    enum { Size = 5 };

    /// 4-digit year.
    typedef UInt16 Year;

    /// Null value for an optional Year field.
    typedef
    IntegralConstant<UInt16, 0>
    NullYear;

    /// Month (1 to 12).
    typedef UInt8 Month;

    /// Null value for an optional Month field.
    typedef
    IntegralConstant<UInt8, 0>
    NullMonth;

    /// Day of month (1 to 31).
    typedef UInt8 Day;

    /// Null value for an optional Day field.
    typedef
    IntegralConstant<UInt8, 0>
    NullDay;

    /// Week of month (1 to 5).
    typedef UInt8 Week;

    /// Null value for an optional Week field.
    typedef
    IntegralConstant<UInt8, 0>
    NullWeek;

    /// Default constructor.
    ///
    /// Initializes fields with appropriate null values.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    MaturityMonthYear()
        ONIXS_B3_UMDF_MD_NOTHROW
      : year_(NullYear::value()),
        month_(NullMonth::value()),
        day_(NullDay::value()),
        week_(NullWeek::value())
    {
    }

    /// Initializes fields with provided values
    ONIXS_B3_UMDF_MD_CONSTEXPR
    MaturityMonthYear(
        Year year,
        Month month,
        Day day,
        Week week)
        ONIXS_B3_UMDF_MD_NOTHROW
      : year_(year),
        month_(month),
        day_(day),
        week_(week)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string
    toString() const;

    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 4 };

        typedef Year FirstArgType;

        typedef Month SecondArgType;

        typedef Day ThirdArgType;

        typedef Week FourthArgType;
    };

    /// 4-digit year.
    ONIXS_B3_UMDF_MD_NODISCARD
    Year year() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return year_;
    }

    /// Month (1 to 12).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool month(Month& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        value = month_;
        return NullMonth() != month_;
    }

    /// Day of month (1 to 31).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool day(Day& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        value = day_;
        return NullDay() != day_;
    }

    /// Week of month (1 to 5).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool week(Week& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        value = week_;
        return NullWeek() != week_;
    }

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator==(
        const MaturityMonthYear& other) const
        ONIXS_B3_UMDF_MD_NOTHROW ;

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator!=(
        const MaturityMonthYear& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

private:
    Year year_;
    Month month_;
    Day day_;
    Week week_;
};


/// Null values definition for optional MaturityMonthYear field.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NullMaturityMonthYear
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef MaturityMonthYear Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return (
           MaturityMonthYear::NullYear() ==
           other.year());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    operator Value() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Value operator()() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static Value value()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Value();
    }
};

inline
bool
MaturityMonthYear::operator==(
    const MaturityMonthYear& other) const
    ONIXS_B3_UMDF_MD_NOTHROW
{
    if((NullMaturityMonthYear() == *this) &&
            (NullMaturityMonthYear() == other))
        return true;

    return
        (this->year_ == other.year_) &&
        (this->month_ == other.month_) &&
        (this->day_ == other.day_) &&
        (this->week_ == other.week_);
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
