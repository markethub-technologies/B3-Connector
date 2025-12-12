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

#include <OnixS/B3/BOE/messaging/Memory.h>
#include <OnixS/B3/BOE/messaging/Decimal.h>
#include <OnixS/B3/BOE/messaging/Fields.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN
ONIXS_B3_BOE_DATA_PACKING_BEGIN(1)

/// Message identifiers and length of message root.
ONIXS_B3_BOE_LTWT_CLASS MessageHeader
{
public:
    /// Size of the composite.
    enum { Size = 8 };

    /// Length of the root of the FIX message contained before repeating groups or variable/conditions fields.
    typedef UInt16 BlockLength;

    /// Template ID used to encode the message.
    typedef UInt16 TemplateId;

    /// ID of the system publishing the message.
    typedef UInt16 SchemaId;

    /// Schema version.
    typedef UInt16 Version;

    /// Length of the root of the FIX message contained before repeating groups or variable/conditions fields.
    ONIXS_B3_BOE_NODISCARD
    BlockLength blockLength() const
        ONIXS_B3_BOE_NOTHROW
    {
        return blockLength_;
    }

    /// Length of the root of the FIX message contained before repeating groups or variable/conditions fields.
    void setBlockLength(BlockLength value)
        ONIXS_B3_BOE_NOTHROW
    {
        blockLength_ = value;
    }

    /// Template ID used to encode the message.
    ONIXS_B3_BOE_NODISCARD
    TemplateId templateId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return templateId_;
    }

    /// Template ID used to encode the message.
    void setTemplateId(TemplateId value)
        ONIXS_B3_BOE_NOTHROW
    {
        templateId_ = value;
    }

    /// ID of the system publishing the message.
    ONIXS_B3_BOE_NODISCARD
    SchemaId schemaId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return schemaId_;
    }

    /// ID of the system publishing the message.
    void setSchemaId(SchemaId value)
        ONIXS_B3_BOE_NOTHROW
    {
        schemaId_ = value;
    }

    /// Schema version.
    ONIXS_B3_BOE_NODISCARD
    Version version() const
        ONIXS_B3_BOE_NOTHROW
    {
        return version_;
    }

    /// Schema version.
    void setVersion(Version value)
        ONIXS_B3_BOE_NOTHROW
    {
        version_ = value;
    }

private:
    BlockLength blockLength_;
    TemplateId templateId_;
    SchemaId schemaId_;
    Version version_;
};


/// Repeating group dimensions.
ONIXS_B3_BOE_LTWT_CLASS GroupSizeEncoding
{
public:
    /// Size of the composite.
    enum { Size = 3 };

    /// Root block length.
    typedef UInt16 BlockLength;

    /// Counter representing the number of entries in a repeating group.
    ///
    /// FIX type: NumInGroup.
    typedef UInt8 NumInGroup;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// Root block length.
    ONIXS_B3_BOE_NODISCARD
    BlockLength blockLength() const
        ONIXS_B3_BOE_NOTHROW
    {
        return blockLength_;
    }

    /// Root block length.
    void setBlockLength(BlockLength value)
        ONIXS_B3_BOE_NOTHROW
    {
        blockLength_ = value;
    }

    /// Counter representing the number of entries in a repeating group.
    ///
    /// FIX type: NumInGroup.
    ONIXS_B3_BOE_NODISCARD
    NumInGroup numInGroup() const
        ONIXS_B3_BOE_NOTHROW
    {
        return numInGroup_;
    }

    /// Counter representing the number of entries in a repeating group.
    ///
    /// FIX type: NumInGroup.
    void setNumInGroup(NumInGroup value)
        ONIXS_B3_BOE_NOTHROW
    {
        numInGroup_ = value;
    }

private:
    BlockLength blockLength_;
    NumInGroup numInGroup_;
};


/// Mandatory price.
///
/// FIX type: Price.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -4>
>
Price;

/// Optional price.
///
/// FIX type: Price.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -4>
>
PriceOptional;

/// Null values definition for optional PriceOptional field.
ONIXS_B3_BOE_LTWT_STRUCT NullPriceOptional
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef PriceOptional Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// Price (8 decimal places).
///
/// FIX type: Price.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -8>
>
Price8;

/// Optional Price (8 decimal places).
///
/// FIX type: Price.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -8>
>
Price8Optional;

/// Null values definition for optional Price8Optional field.
ONIXS_B3_BOE_LTWT_STRUCT NullPrice8Optional
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef Price8Optional Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// Optional price offset (4 decimal places). Usually 3 places are enough, but FX requires 4.
///
/// FIX type: PriceOffset.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -4>
>
PriceOffsetOptional;

/// Null values definition for optional PriceOffsetOptional field.
ONIXS_B3_BOE_LTWT_STRUCT NullPriceOffsetOptional
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef PriceOffsetOptional Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// Percentage (8 decimal places).
///
/// FIX type: Percentage.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -8>
>
Percentage8;

/// Optional percentage (8 decimal places).
///
/// FIX type: Percentage.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -8>
>
Percentage8Optional;

/// Null values definition for optional Percentage8Optional field.
ONIXS_B3_BOE_LTWT_STRUCT NullPercentage8Optional
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef Percentage8Optional Value;

    /// Null value for an optional Mantissa field.
    typedef
    IntegralConstant<Int64, -9223372036854775807LL-1>
    NullMantissa;


    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           NullMantissa() ==
           other.mantissa());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value(NullMantissa());
    }
};


/// Ratio of quantity relative to the whole thing.
///
/// FIX type: float.
typedef
FixedPointDecimal
<
    Int64,
    IntegralConstant<Int8, -7>
>
RatioQty;

/// UTC timestamp with nanosecond precision.
///
/// FIX type: UTCTimestamp.
ONIXS_B3_BOE_LTWT_CLASS UTCTimestampNanos
{
public:
    /// Size of the composite.
    enum { Size = 8 };

    /// UTC timestamp with nanosecond precision (Unix Epoch).
    typedef UInt64 Time;

    /// time unit (nanoseconds).
    typedef
    IntegralConstant<UInt8, 9>
    Unit;

    /// Default constructor.
    ///
    /// Initializes fields with zero values.
    ONIXS_B3_BOE_CONSTEXPR
    UTCTimestampNanos()
        ONIXS_B3_BOE_NOTHROW
      : time_(0)
    {
    }

    /// Initializes fields with provided values
    explicit
    ONIXS_B3_BOE_CONSTEXPR
    UTCTimestampNanos(Time time)
        ONIXS_B3_BOE_NOTHROW
      : time_(time)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef Time FirstArgType;
    };

    /// Serializes to a data buffer
    void serialize(void* addr) const
        ONIXS_B3_BOE_NOTHROW
    {
        assert(addr);

        std::memcpy(addr, &time_, sizeof(time_));
    }

    /// UTC timestamp with nanosecond precision (Unix Epoch).
    ONIXS_B3_BOE_NODISCARD
    Time time() const
        ONIXS_B3_BOE_NOTHROW
    {
        return time_;
    }

    /// UTC timestamp with nanosecond precision (Unix Epoch).
    void setTime(Time value)
        ONIXS_B3_BOE_NOTHROW
    {
        time_ = value;
    }

    /// time unit (nanoseconds).
    ONIXS_B3_BOE_NODISCARD
    Unit unit() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Unit();
    }

    /// time unit (nanoseconds).
private:
    Time time_;
};


/// Optional UTC timestamp with nanosecond precision.
///
/// FIX type: UTCTimestamp.
ONIXS_B3_BOE_LTWT_CLASS UTCTimestampNanosOptional
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
    IntegralConstant<UInt8, 9>
    Unit;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// UTC timestamp with nanosecond precision (Unix Epoch).
    ONIXS_B3_BOE_NODISCARD
    Time time() const
        ONIXS_B3_BOE_NOTHROW
    {
        return time_;
    }

    /// UTC timestamp with nanosecond precision (Unix Epoch).
    void setTime(Time value)
        ONIXS_B3_BOE_NOTHROW
    {
        time_ = value;
    }

    void setTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        time_ = NullTime();
    }

    /// time unit (nanoseconds).
    ONIXS_B3_BOE_NODISCARD
    Unit unit() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Unit();
    }

    /// time unit (nanoseconds).
private:
    Time time_;
};


/// Null values definition for optional UTCTimestampNanosOptional field.
ONIXS_B3_BOE_LTWT_STRUCT NullUTCTimestampNanosOptional
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef
    UTCTimestampNanosOptional
    Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           UTCTimestampNanosOptional::NullTime() ==
           other.time());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }
};


/// Interval time expressed in milliseconds.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_CLASS DeltaInMillis
{
public:
    /// Size of the composite.
    enum { Size = 8 };

    /// Interval time expressed in milliseconds.
    typedef UInt64 Time;

    /// time unit (milliseconds).
    typedef
    IntegralConstant<UInt8, 3>
    Unit;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// Interval time expressed in milliseconds.
    ONIXS_B3_BOE_NODISCARD
    Time time() const
        ONIXS_B3_BOE_NOTHROW
    {
        return time_;
    }

    /// Interval time expressed in milliseconds.
    void setTime(Time value)
        ONIXS_B3_BOE_NOTHROW
    {
        time_ = value;
    }

    /// time unit (milliseconds).
    ONIXS_B3_BOE_NODISCARD
    Unit unit() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Unit();
    }

    /// time unit (milliseconds).
private:
    Time time_;
};


/// DATA Field.
/// FIX type: data.
ONIXS_B3_BOE_LTWT_STRUCT CredentialsEncoding
{
public:
    /// Size of the composite.
    enum { Size = 1 };

    /// Length type.
    typedef UInt8 Length;

    /// VarData type.
    typedef Char VarData;

    /// \return length.
    ONIXS_B3_BOE_NODISCARD
    Length length() const
        ONIXS_B3_BOE_NOTHROW
    {
        return length_;
    }

    /// Sets the length.
    void length(Length value)
        ONIXS_B3_BOE_NOTHROW
    {
        length_ = value;
    }

    /// \return the varData field.
    ONIXS_B3_BOE_NODISCARD
    StrRef varData() const
        ONIXS_B3_BOE_NOTHROW
    {
        return StrRef(reinterpret_cast<const Char*>(this) + Size, length());
    }

    /// Sets the varData field.
    void varData(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        length(static_cast<Length>(value.size()));
        if(value.data())
            std::memcpy(reinterpret_cast<Char*>(this) + Size, value.data(), value.size());
    }

        /// \return a human-readable presentation.
        ONIXS_B3_BOE_NODISCARD
        std::string
        toString() const;


    /// \return Size of SBE-encoded data representing the field.
    ONIXS_B3_BOE_NODISCARD
    Length binarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Size + length();
    }

private:
    Length length_;
};


/// DATA Field.
/// FIX type: data.
ONIXS_B3_BOE_LTWT_STRUCT MemoEncoding
{
public:
    /// Size of the composite.
    enum { Size = 1 };

    /// Length type.
    typedef UInt8 Length;

    /// VarData type.
    typedef Char VarData;

    /// \return length.
    ONIXS_B3_BOE_NODISCARD
    Length length() const
        ONIXS_B3_BOE_NOTHROW
    {
        return length_;
    }

    /// Sets the length.
    void length(Length value)
        ONIXS_B3_BOE_NOTHROW
    {
        length_ = value;
    }

    /// \return the varData field.
    ONIXS_B3_BOE_NODISCARD
    StrRef varData() const
        ONIXS_B3_BOE_NOTHROW
    {
        return StrRef(reinterpret_cast<const Char*>(this) + Size, length());
    }

    /// Sets the varData field.
    void varData(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        length(static_cast<Length>(value.size()));
        if(value.data())
            std::memcpy(reinterpret_cast<Char*>(this) + Size, value.data(), value.size());
    }

        /// \return a human-readable presentation.
        ONIXS_B3_BOE_NODISCARD
        std::string
        toString() const;


    /// \return Size of SBE-encoded data representing the field.
    ONIXS_B3_BOE_NODISCARD
    Length binarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Size + length();
    }

private:
    Length length_;
};


/// DATA Field.
/// FIX type: data.
ONIXS_B3_BOE_LTWT_STRUCT TextEncoding
{
public:
    /// Size of the composite.
    enum { Size = 1 };

    /// Length type.
    typedef UInt8 Length;

    /// VarData type.
    typedef Char VarData;

    /// \return length.
    ONIXS_B3_BOE_NODISCARD
    Length length() const
        ONIXS_B3_BOE_NOTHROW
    {
        return length_;
    }

    /// Sets the length.
    void length(Length value)
        ONIXS_B3_BOE_NOTHROW
    {
        length_ = value;
    }

    /// \return the varData field.
    ONIXS_B3_BOE_NODISCARD
    StrRef varData() const
        ONIXS_B3_BOE_NOTHROW
    {
        return StrRef(reinterpret_cast<const Char*>(this) + Size, length());
    }

    /// Sets the varData field.
    void varData(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        length(static_cast<Length>(value.size()));
        if(value.data())
            std::memcpy(reinterpret_cast<Char*>(this) + Size, value.data(), value.size());
    }

        /// \return a human-readable presentation.
        ONIXS_B3_BOE_NODISCARD
        std::string
        toString() const;


    /// \return Size of SBE-encoded data representing the field.
    ONIXS_B3_BOE_NODISCARD
    Length binarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Size + length();
    }

private:
    Length length_;
};


/// DATA Field.
/// FIX type: data.
ONIXS_B3_BOE_LTWT_STRUCT DeskIDEncoding
{
public:
    /// Size of the composite.
    enum { Size = 1 };

    /// Length type.
    typedef UInt8 Length;

    /// VarData type.
    typedef Char VarData;

    /// \return length.
    ONIXS_B3_BOE_NODISCARD
    Length length() const
        ONIXS_B3_BOE_NOTHROW
    {
        return length_;
    }

    /// Sets the length.
    void length(Length value)
        ONIXS_B3_BOE_NOTHROW
    {
        length_ = value;
    }

    /// \return the varData field.
    ONIXS_B3_BOE_NODISCARD
    StrRef varData() const
        ONIXS_B3_BOE_NOTHROW
    {
        return StrRef(reinterpret_cast<const Char*>(this) + Size, length());
    }

    /// Sets the varData field.
    void varData(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        length(static_cast<Length>(value.size()));
        if(value.data())
            std::memcpy(reinterpret_cast<Char*>(this) + Size, value.data(), value.size());
    }

        /// \return a human-readable presentation.
        ONIXS_B3_BOE_NODISCARD
        std::string
        toString() const;


    /// \return Size of SBE-encoded data representing the field.
    ONIXS_B3_BOE_NODISCARD
    Length binarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Size + length();
    }

private:
    Length length_;
};


/// DATA Field.
/// FIX type: data.
ONIXS_B3_BOE_LTWT_STRUCT ClientAppEncoding
{
public:
    /// Size of the composite.
    enum { Size = 1 };

    /// Length type.
    typedef UInt8 Length;

    /// VarData type.
    typedef Char VarData;

    /// \return length.
    ONIXS_B3_BOE_NODISCARD
    Length length() const
        ONIXS_B3_BOE_NOTHROW
    {
        return length_;
    }

    /// Sets the length.
    void length(Length value)
        ONIXS_B3_BOE_NOTHROW
    {
        length_ = value;
    }

    /// \return the varData field.
    ONIXS_B3_BOE_NODISCARD
    StrRef varData() const
        ONIXS_B3_BOE_NOTHROW
    {
        return StrRef(reinterpret_cast<const Char*>(this) + Size, length());
    }

    /// Sets the varData field.
    void varData(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        length(static_cast<Length>(value.size()));
        if(value.data())
            std::memcpy(reinterpret_cast<Char*>(this) + Size, value.data(), value.size());
    }

        /// \return a human-readable presentation.
        ONIXS_B3_BOE_NODISCARD
        std::string
        toString() const;


    /// \return Size of SBE-encoded data representing the field.
    ONIXS_B3_BOE_NODISCARD
    Length binarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Size + length();
    }

private:
    Length length_;
};


/// Custodian information is required for going private offer.
ONIXS_B3_BOE_LTWT_CLASS CustodianInfo
{
public:
    /// Size of the composite.
    enum { Size = 12 };

    /// Identifies the custodian.
    typedef UInt32 Custodian;

    /// Null value for an optional Custodian field.
    typedef
    IntegralConstant<UInt32, 0>
    NullCustodian;

    /// Identifies the custody account.
    typedef UInt32 CustodyAccount;

    /// Null value for an optional CustodyAccount field.
    typedef
    IntegralConstant<UInt32, 0>
    NullCustodyAccount;

    /// Custody allocation type.
    typedef
    UInt32
    CustodyAllocationType;

    /// Null value for an optional CustodyAllocationType field.
    typedef
    IntegralConstant<UInt32, 0>
    NullCustodyAllocationType;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// Identifies the custodian.
    ONIXS_B3_BOE_NODISCARD
    Custodian custodian() const
        ONIXS_B3_BOE_NOTHROW
    {
        return custodian_;
    }

    /// Identifies the custodian.
    void setCustodian(Custodian value)
        ONIXS_B3_BOE_NOTHROW
    {
        custodian_ = value;
    }

    void setCustodianToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        custodian_ = NullCustodian();
    }

    /// Identifies the custody account.
    ONIXS_B3_BOE_NODISCARD
    bool custodyAccount(CustodyAccount& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = custodyAccount_;
        return NullCustodyAccount() != custodyAccount_;
    }

    /// Identifies the custody account.
    void setCustodyAccount(CustodyAccount value)
        ONIXS_B3_BOE_NOTHROW
    {
        custodyAccount_ = value;
    }

    void setCustodyAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        custodyAccount_ = NullCustodyAccount();
    }

    /// Custody allocation type.
    ONIXS_B3_BOE_NODISCARD
    bool
    custodyAllocationType(
        CustodyAllocationType& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = custodyAllocationType_;
        return NullCustodyAllocationType() != custodyAllocationType_;
    }

    /// Custody allocation type.
    void
    setCustodyAllocationType(
        CustodyAllocationType value)
        ONIXS_B3_BOE_NOTHROW
    {
        custodyAllocationType_ = value;
    }

    void setCustodyAllocationTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        custodyAllocationType_ = NullCustodyAllocationType();
    }

private:
    Custodian custodian_;
    CustodyAccount custodyAccount_;
    CustodyAllocationType custodyAllocationType_;
};


/// Null values definition for optional CustodianInfo field.
ONIXS_B3_BOE_LTWT_STRUCT NullCustodianInfo
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef CustodianInfo Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           CustodianInfo::NullCustodian() ==
           other.custodian());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }
};


/// Header used for inbound business messages.
ONIXS_B3_BOE_LTWT_CLASS InboundBusinessHeader
{
public:
    /// Size of the composite.
    enum { Size = 18 };

    /// Type alias for the `SessionID`.
    ///
    /// FIX type: Int.
    typedef UInt32 SessionID;

    /// Type alias for the `MsgSeqNum`.
    ///
    /// FIX type: Int.
    typedef UInt32 MsgSeqNum;

    /// Type alias for the `SendingTime`.
    ///
    /// FIX type: UTCTimestamp.
    typedef
    UTCTimestampNanosOptional
    SendingTime;

    /// Null values definition for optional SendingTime field.
    ONIXS_B3_BOE_LTWT_STRUCT NullSendingTime
    {
        /// Aliases the type whose null value
        /// traits are exposed by the given class.
        typedef SendingTime Value;

        /// Compares encoded data to NULL.
        ONIXS_B3_BOE_NODISCARD
        bool operator ==(const Value& other) const
            ONIXS_B3_BOE_NOTHROW
        {
            return (
               SendingTime::NullTime() ==
               other.time());
        }

        /// Compares encoded data to NULL.
        ONIXS_B3_BOE_NODISCARD
        bool operator !=(const Value& other) const
            ONIXS_B3_BOE_NOTHROW
        {
            return !(*this == other);
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        operator Value() const
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        Value operator()() const
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        static Value value()
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }
    };

    /// Type alias for the `MarketSegmentID`.
    ///
    /// FIX type: Int.
    typedef UInt8 MarketSegmentID;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// \return the `sessionID` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return sessionId_;
    }

    /// Sets the `sessionID` field.
    ///
    /// FIX type: Int.
    void setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        sessionId_ = value;
    }

    /// \return the `msgSeqNum` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    MsgSeqNum msgSeqNum() const
        ONIXS_B3_BOE_NOTHROW
    {
        return msgSeqNum_;
    }

    /// Sets the `msgSeqNum` field.
    ///
    /// FIX type: Int.
    void setMsgSeqNum(MsgSeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        msgSeqNum_ = value;
    }

    /// \return the `sendingTime` field.
    ///
    /// FIX type: UTCTimestamp.
    ONIXS_B3_BOE_NODISCARD
    bool sendingTime(SendingTime& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = sendingTime_;
        return NullSendingTime() != sendingTime_;
    }

    /// Sets the `sendingTime` field.
    ///
    /// FIX type: UTCTimestamp.
    void setSendingTime(SendingTime value)
        ONIXS_B3_BOE_NOTHROW
    {
        sendingTime_ = value;
    }

    /// \return the `marketSegmentID` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    MarketSegmentID marketSegmentId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return marketSegmentId_;
    }

    /// Sets the `marketSegmentID` field.
    ///
    /// FIX type: Int.
    void setMarketSegmentId(MarketSegmentID value)
        ONIXS_B3_BOE_NOTHROW
    {
        marketSegmentId_ = value;
    }

private:
    SessionID sessionId_;
    MsgSeqNum msgSeqNum_;
    SendingTime sendingTime_;
    MarketSegmentID marketSegmentId_;
    ONIXS_B3_BOE_PADDING(1);
};


/// Header used for outbound business messages.
ONIXS_B3_BOE_LTWT_CLASS OutboundBusinessHeader
{
public:
    /// Size of the composite.
    enum { Size = 18 };

    /// Type alias for the `SessionID`.
    ///
    /// FIX type: Int.
    typedef UInt32 SessionID;

    /// Type alias for the `MsgSeqNum`.
    ///
    /// FIX type: Int.
    typedef UInt32 MsgSeqNum;

    /// Type alias for the `SendingTime`.
    ///
    /// FIX type: UTCTimestamp.
    typedef
    UTCTimestampNanosOptional
    SendingTime;

    /// Null values definition for optional SendingTime field.
    ONIXS_B3_BOE_LTWT_STRUCT NullSendingTime
    {
        /// Aliases the type whose null value
        /// traits are exposed by the given class.
        typedef SendingTime Value;

        /// Compares encoded data to NULL.
        ONIXS_B3_BOE_NODISCARD
        bool operator ==(const Value& other) const
            ONIXS_B3_BOE_NOTHROW
        {
            return (
               SendingTime::NullTime() ==
               other.time());
        }

        /// Compares encoded data to NULL.
        ONIXS_B3_BOE_NODISCARD
        bool operator !=(const Value& other) const
            ONIXS_B3_BOE_NOTHROW
        {
            return !(*this == other);
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        operator Value() const
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        Value operator()() const
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        static Value value()
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }
    };

    /// Type alias for the `MarketSegmentID`.
    ///
    /// FIX type: Int.
    typedef UInt8 MarketSegmentID;

    /// Null value for an optional MarketSegmentID field.
    typedef
    IntegralConstant<UInt8, 0>
    NullMarketSegmentID;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// \return the `sessionID` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return sessionId_;
    }

    /// Sets the `sessionID` field.
    ///
    /// FIX type: Int.
    void setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        sessionId_ = value;
    }

    /// \return the `msgSeqNum` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    MsgSeqNum msgSeqNum() const
        ONIXS_B3_BOE_NOTHROW
    {
        return msgSeqNum_;
    }

    /// Sets the `msgSeqNum` field.
    ///
    /// FIX type: Int.
    void setMsgSeqNum(MsgSeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        msgSeqNum_ = value;
    }

    /// \return the `sendingTime` field.
    ///
    /// FIX type: UTCTimestamp.
    ONIXS_B3_BOE_NODISCARD
    bool sendingTime(SendingTime& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = sendingTime_;
        return NullSendingTime() != sendingTime_;
    }

    /// Sets the `sendingTime` field.
    ///
    /// FIX type: UTCTimestamp.
    void setSendingTime(SendingTime value)
        ONIXS_B3_BOE_NOTHROW
    {
        sendingTime_ = value;
    }

    /// \return the `eventIndicator` field.
    ONIXS_B3_BOE_NODISCARD
    EventIndicator eventIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        return eventIndicator_;
    }

    /// Sets the `eventIndicator` field.
    void setEventIndicator(EventIndicator value)
        ONIXS_B3_BOE_NOTHROW
    {
        eventIndicator_ = value;
    }

    /// \return the `marketSegmentID` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    bool marketSegmentId(MarketSegmentID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = marketSegmentId_;
        return NullMarketSegmentID() != marketSegmentId_;
    }

    /// Sets the `marketSegmentID` field.
    ///
    /// FIX type: Int.
    void setMarketSegmentId(MarketSegmentID value)
        ONIXS_B3_BOE_NOTHROW
    {
        marketSegmentId_ = value;
    }

    void setMarketSegmentIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        marketSegmentId_ = NullMarketSegmentID();
    }

private:
    SessionID sessionId_;
    MsgSeqNum msgSeqNum_;
    SendingTime sendingTime_;
    EventIndicator eventIndicator_;
    MarketSegmentID marketSegmentId_;
};


/// Header used for business messages that can go inbound or outbound.
ONIXS_B3_BOE_LTWT_CLASS BidirectionalBusinessHeader
{
public:
    /// Size of the composite.
    enum { Size = 20 };

    /// Type alias for the `SessionID`.
    ///
    /// FIX type: Int.
    typedef UInt32 SessionID;

    /// Type alias for the `MsgSeqNum`.
    ///
    /// FIX type: Int.
    typedef UInt32 MsgSeqNum;

    /// Type alias for the `SendingTime`.
    ///
    /// FIX type: UTCTimestamp.
    typedef
    UTCTimestampNanosOptional
    SendingTime;

    /// Null values definition for optional SendingTime field.
    ONIXS_B3_BOE_LTWT_STRUCT NullSendingTime
    {
        /// Aliases the type whose null value
        /// traits are exposed by the given class.
        typedef SendingTime Value;

        /// Compares encoded data to NULL.
        ONIXS_B3_BOE_NODISCARD
        bool operator ==(const Value& other) const
            ONIXS_B3_BOE_NOTHROW
        {
            return (
               SendingTime::NullTime() ==
               other.time());
        }

        /// Compares encoded data to NULL.
        ONIXS_B3_BOE_NODISCARD
        bool operator !=(const Value& other) const
            ONIXS_B3_BOE_NOTHROW
        {
            return !(*this == other);
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        operator Value() const
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        Value operator()() const
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }

        /// \return the value of the constant.
        ONIXS_B3_BOE_CONSTEXPR
        static Value value()
            ONIXS_B3_BOE_NOTHROW
        {
            return Value();
        }
    };

    /// Type alias for the `MarketSegmentID`.
    ///
    /// FIX type: Int.
    typedef UInt8 MarketSegmentID;

    /// Null value for an optional MarketSegmentID field.
    typedef
    IntegralConstant<UInt8, 0>
    NullMarketSegmentID;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// \return the `sessionID` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return sessionId_;
    }

    /// Sets the `sessionID` field.
    ///
    /// FIX type: Int.
    void setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        sessionId_ = value;
    }

    /// \return the `msgSeqNum` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    MsgSeqNum msgSeqNum() const
        ONIXS_B3_BOE_NOTHROW
    {
        return msgSeqNum_;
    }

    /// Sets the `msgSeqNum` field.
    ///
    /// FIX type: Int.
    void setMsgSeqNum(MsgSeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        msgSeqNum_ = value;
    }

    /// \return the `sendingTime` field.
    ///
    /// FIX type: UTCTimestamp.
    ONIXS_B3_BOE_NODISCARD
    bool sendingTime(SendingTime& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = sendingTime_;
        return NullSendingTime() != sendingTime_;
    }

    /// Sets the `sendingTime` field.
    ///
    /// FIX type: UTCTimestamp.
    void setSendingTime(SendingTime value)
        ONIXS_B3_BOE_NOTHROW
    {
        sendingTime_ = value;
    }

    /// \return the `eventIndicator` field.
    ONIXS_B3_BOE_NODISCARD
    EventIndicator eventIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        return eventIndicator_;
    }

    /// Sets the `eventIndicator` field.
    void setEventIndicator(EventIndicator value)
        ONIXS_B3_BOE_NOTHROW
    {
        eventIndicator_ = value;
    }

    /// \return the `marketSegmentID` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    bool marketSegmentId(MarketSegmentID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = marketSegmentId_;
        return NullMarketSegmentID() != marketSegmentId_;
    }

    /// Sets the `marketSegmentID` field.
    ///
    /// FIX type: Int.
    void setMarketSegmentId(MarketSegmentID value)
        ONIXS_B3_BOE_NOTHROW
    {
        marketSegmentId_ = value;
    }

    void setMarketSegmentIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        marketSegmentId_ = NullMarketSegmentID();
    }

private:
    SessionID sessionId_;
    MsgSeqNum msgSeqNum_;
    SendingTime sendingTime_;
    EventIndicator eventIndicator_;
    MarketSegmentID marketSegmentId_;
    ONIXS_B3_BOE_PADDING(2);
};


/// Self trade prevention investor identification is composed of the prefix and document.
ONIXS_B3_BOE_LTWT_CLASS InvestorID
{
public:
    /// Size of the composite.
    enum { Size = 8 };

    /// Type alias for the `Prefix`.
    ///
    /// FIX type: Int.
    typedef UInt16 Prefix;

    /// Null value for an optional Prefix field.
    typedef
    IntegralConstant<UInt16, 0>
    NullPrefix;

    /// Type alias for the `Document`.
    ///
    /// FIX type: Int.
    typedef UInt32 Document;

    /// Null value for an optional Document field.
    typedef
    IntegralConstant<UInt32, 0>
    NullDocument;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// \return the `prefix` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    Prefix prefix() const
        ONIXS_B3_BOE_NOTHROW
    {
        return prefix_;
    }

    /// Sets the `prefix` field.
    ///
    /// FIX type: Int.
    void setPrefix(Prefix value)
        ONIXS_B3_BOE_NOTHROW
    {
        prefix_ = value;
    }

    void setPrefixToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        prefix_ = NullPrefix();
    }

    /// \return the `document` field.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    bool document(Document& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = document_;
        return NullDocument() != document_;
    }

    /// Sets the `document` field.
    ///
    /// FIX type: Int.
    void setDocument(Document value)
        ONIXS_B3_BOE_NOTHROW
    {
        document_ = value;
    }

    void setDocumentToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        document_ = NullDocument();
    }

private:
    Prefix prefix_;
    ONIXS_B3_BOE_PADDING(2);
    Document document_;
};


/// Null values definition for optional InvestorID field.
ONIXS_B3_BOE_LTWT_STRUCT NullInvestorID
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef InvestorID Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           InvestorID::NullPrefix() ==
           other.prefix());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }
};


/// Unique ID for all matches that occur as a result of a implied event.
ONIXS_B3_BOE_LTWT_CLASS ImpliedEventID
{
public:
    /// Size of the composite.
    enum { Size = 6 };

    /// Unique ID for all matches that occur as a result of an implied event.
    ///
    /// FIX type: Int.
    typedef UInt32 EventID;

    /// Null value for an optional EventID field.
    typedef
    IntegralConstant<UInt32, 0>
    NullEventID;

    /// Number of trades related to the same implied event.
    ///
    /// FIX type: Int.
    typedef UInt16 NoRelatedTrades;

    /// Null value for an optional NoRelatedTrades field.
    typedef
    IntegralConstant<UInt16, 0>
    NullNoRelatedTrades;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// Unique ID for all matches that occur as a result of an implied event.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    EventID eventId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return eventId_;
    }

    /// Unique ID for all matches that occur as a result of an implied event.
    ///
    /// FIX type: Int.
    void setEventId(EventID value)
        ONIXS_B3_BOE_NOTHROW
    {
        eventId_ = value;
    }

    void setEventIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        eventId_ = NullEventID();
    }

    /// Number of trades related to the same implied event.
    ///
    /// FIX type: Int.
    ONIXS_B3_BOE_NODISCARD
    bool relatedTrades(NoRelatedTrades& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = relatedTrades_;
        return NullNoRelatedTrades() != relatedTrades_;
    }

    /// Number of trades related to the same implied event.
    ///
    /// FIX type: Int.
    void setRelatedTrades(NoRelatedTrades value)
        ONIXS_B3_BOE_NOTHROW
    {
        relatedTrades_ = value;
    }

    void setRelatedTradesToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        relatedTrades_ = NullNoRelatedTrades();
    }

private:
    EventID eventId_;
    NoRelatedTrades relatedTrades_;
};


/// Null values definition for optional ImpliedEventID field.
ONIXS_B3_BOE_LTWT_STRUCT NullImpliedEventID
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef ImpliedEventID Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           ImpliedEventID::NullEventID() ==
           other.eventId());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }
};


/// Identifies the version of what the field relates to.
ONIXS_B3_BOE_LTWT_CLASS Version
{
public:
    /// Size of the composite.
    enum { Size = 4 };

    /// Major release number.
    typedef UInt8 MajorNumber;

    /// Null value for an optional MajorNumber field.
    typedef
    IntegralConstant<UInt8, 255>
    NullMajorNumber;

    /// Minor release number.
    typedef UInt8 MinorNumber;

    /// Null value for an optional MinorNumber field.
    typedef
    IntegralConstant<UInt8, 255>
    NullMinorNumber;

    /// Maintenance release number.
    typedef UInt8 PatchNumber;

    /// Null value for an optional PatchNumber field.
    typedef
    IntegralConstant<UInt8, 255>
    NullPatchNumber;

    /// Build number.
    typedef UInt8 BuildNumber;

    /// Null value for an optional BuildNumber field.
    typedef
    IntegralConstant<UInt8, 255>
    NullBuildNumber;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// Major release number.
    ONIXS_B3_BOE_NODISCARD
    MajorNumber majorNumber() const
        ONIXS_B3_BOE_NOTHROW
    {
        return majorNumber_;
    }

    /// Major release number.
    void setMajorNumber(MajorNumber value)
        ONIXS_B3_BOE_NOTHROW
    {
        majorNumber_ = value;
    }

    void setMajorNumberToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        majorNumber_ = NullMajorNumber();
    }

    /// Minor release number.
    ONIXS_B3_BOE_NODISCARD
    bool minorNumber(MinorNumber& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = minorNumber_;
        return NullMinorNumber() != minorNumber_;
    }

    /// Minor release number.
    void setMinorNumber(MinorNumber value)
        ONIXS_B3_BOE_NOTHROW
    {
        minorNumber_ = value;
    }

    void setMinorNumberToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        minorNumber_ = NullMinorNumber();
    }

    /// Maintenance release number.
    ONIXS_B3_BOE_NODISCARD
    bool patchNumber(PatchNumber& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = patchNumber_;
        return NullPatchNumber() != patchNumber_;
    }

    /// Maintenance release number.
    void setPatchNumber(PatchNumber value)
        ONIXS_B3_BOE_NOTHROW
    {
        patchNumber_ = value;
    }

    void setPatchNumberToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        patchNumber_ = NullPatchNumber();
    }

    /// Build number.
    ONIXS_B3_BOE_NODISCARD
    bool buildNumber(BuildNumber& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        value = buildNumber_;
        return NullBuildNumber() != buildNumber_;
    }

    /// Build number.
    void setBuildNumber(BuildNumber value)
        ONIXS_B3_BOE_NOTHROW
    {
        buildNumber_ = value;
    }

    void setBuildNumberToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        buildNumber_ = NullBuildNumber();
    }

private:
    MajorNumber majorNumber_;
    MinorNumber minorNumber_;
    PatchNumber patchNumber_;
    BuildNumber buildNumber_;
};


/// Null values definition for optional Version field.
ONIXS_B3_BOE_LTWT_STRUCT NullVersion
{
    /// Aliases the type whose null value
    /// traits are exposed by the given class.
    typedef Version Value;

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator ==(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return (
           Version::NullMajorNumber() ==
           other.majorNumber());
    }

    /// Compares encoded data to NULL.
    ONIXS_B3_BOE_NODISCARD
    bool operator !=(const Value& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    operator Value() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    Value operator()() const
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }

    /// \return the value of the constant.
    ONIXS_B3_BOE_CONSTEXPR
    static Value value()
        ONIXS_B3_BOE_NOTHROW
    {
        return Value();
    }
};



/// \private
inline bool isNull(const PriceOptional& value) ONIXS_B3_BOE_NOTHROW
{
    return NullPriceOptional() == value;
}

/// \private
inline bool isNull(const Price8Optional& value) ONIXS_B3_BOE_NOTHROW
{
    return NullPrice8Optional() == value;
}

typedef MessageHeader MessageHeaderBuilder;

ONIXS_B3_BOE_DATA_PACKING_END
ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
