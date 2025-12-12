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

#include <OnixS/B3/BOE/messaging/Integral.h>
#include <OnixS/B3/BOE/messaging/Memory.h>

#include <string>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Forward declarations
template <class MantissaType, class ExponentType> class FixedPointDecimal;
template <class MantissaType, class ExponentType> class FloatingPointDecimal;
template<class Mantissa, class Exponent> std::string toStr(const FixedPointDecimal <Mantissa, Exponent>&);
template<class Mantissa, class Exponent> std::string toStr(const FloatingPointDecimal <Mantissa, Exponent>&);

/// A real number with a floating exponent.
template <class MantissaType, class ExponentType >
class FloatingPointDecimal
{
    MantissaType mantissa_;
    ExponentType exponent_;

public:
    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 2 };

        typedef MantissaType FirstArgType;

        typedef ExponentType SecondArgType;
    };

    /// Mantissa component type.
    typedef MantissaType Mantissa;

    /// Exponent component type.
    typedef ExponentType Exponent;

    /// Traits.
    enum
    {
        /// Size of the class in bytes.
        Size = sizeof(Mantissa) + sizeof(Exponent)
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const
    {
        return toStr(*this);
    }

    /// Default (zero) initialization.
    ONIXS_B3_BOE_CONSTEXPR
    FloatingPointDecimal() ONIXS_B3_BOE_NOTHROW
        : mantissa_()
        , exponent_()
    {
    }

    /// Explicitly initializes the instance from the mantissa and exponent values.
    ONIXS_B3_BOE_CONSTEXPR
    FloatingPointDecimal(Mantissa mantissa, Exponent exponent) ONIXS_B3_BOE_NOTHROW
        : mantissa_(mantissa)
        , exponent_(exponent)
    {
    }

    /// Initializes the instance as a copy of the given one.
    ONIXS_B3_BOE_CONSTEXPR
    FloatingPointDecimal(
        const FloatingPointDecimal& other) ONIXS_B3_BOE_NOTHROW
        : mantissa_(other.mantissa_)
        , exponent_(other.exponent_)
    {
    }

    /// \return mantissa.
    Mantissa mantissa() const ONIXS_B3_BOE_NOTHROW
    {
        return mantissa_;
    }

    /// \return exponent.
    Exponent exponent() const ONIXS_B3_BOE_NOTHROW
    {
        return exponent_;
    }

    /// Re-initializes the instance as copy of the given one.
    FloatingPointDecimal& operator =(const FloatingPointDecimal& other) ONIXS_B3_BOE_NOTHROW
    {
        mantissa_ = other.mantissa_;
        exponent_ = other.exponent_;

        return *this;
    }


    /// Initializes the instance from the floating point decimal.
    template<class OtherMantissa, class OtherExponent>
    explicit FloatingPointDecimal(const FloatingPointDecimal <OtherMantissa, OtherExponent>& other) ONIXS_B3_BOE_NOTHROW
        : mantissa_(other.mantissa())
        , exponent_(other.exponent())
    {
    }

    /// Initializes the instance from the fixed point decimal.
    template <class OtherMantissa, class OtherExponent>
    explicit FloatingPointDecimal(const FixedPointDecimal <OtherMantissa, OtherExponent>& other) ONIXS_B3_BOE_NOTHROW
        : mantissa_(other.mantissa())
        , exponent_(other.exponent())
    {
    }

    /// Re-initializes instance as a copy of the floating point value.
    template
        <
            class OtherMantissa,
            class OtherExponent
        >
    FloatingPointDecimal&
    operator =(
        const FloatingPointDecimal
            <OtherMantissa, OtherExponent>& other) ONIXS_B3_BOE_NOTHROW
    {
        mantissa_ = other.mantissa();
        exponent_ = other.exponent();

        return *this;
    }

    /// Re-initializes instance as a copy of the fixed point value.
    template
        <
            class OtherMantissa,
            class OtherExponent
        >
    FloatingPointDecimal& operator = (const FixedPointDecimal <OtherMantissa, OtherExponent>& other) ONIXS_B3_BOE_NOTHROW
    {
        mantissa_ = other.mantissa();
        exponent_ = other.exponent();

        return *this;
    }

    /// Serializes to the given data buffer.
    void serialize(void* addr) const ONIXS_B3_BOE_NOTHROW
    {
        assert(addr);

        std::memcpy(addr, &mantissa_, sizeof(mantissa_));
        addr = advanceByBytes(addr, sizeof(mantissa_));

        std::memcpy(addr, &exponent_, sizeof(exponent_));
    }
};

/// A real number with a constant exponent.
template
<
    class MantissaType,
    class ExponentType
>
class FixedPointDecimal
{
    // Only mantissa is stored.
    MantissaType mantissa_;

public:
    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef MantissaType FirstArgType;
    };

    /// Mantissa component type.
    typedef MantissaType Mantissa;

    /// Exponent component type.
    typedef ExponentType Exponent;

    /// Traits.
    enum
    {
        /// Size of the class in bytes.
        Size = sizeof(Mantissa)
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const
    {
        return toStr(*this);
    }

    /// Default (zero) initialization.
    ONIXS_B3_BOE_CONSTEXPR
    FixedPointDecimal() ONIXS_B3_BOE_NOTHROW
        : mantissa_()
    {
    }

    /// Explicitly initializes the instance from the mantissa value.
    explicit ONIXS_B3_BOE_CONSTEXPR FixedPointDecimal(Mantissa mantissa) ONIXS_B3_BOE_NOTHROW
        : mantissa_(mantissa)
    {
    }

    /// Initializes the instance as a copy of the given one.
    ONIXS_B3_BOE_CONSTEXPR FixedPointDecimal(const FixedPointDecimal& other) ONIXS_B3_BOE_NOTHROW
        : mantissa_(other.mantissa_)
    {
    }

    /// \return mantissa.
    Mantissa mantissa() const ONIXS_B3_BOE_NOTHROW
    {
        return mantissa_;
    }

    /// \return exponent.
    Exponent exponent() const ONIXS_B3_BOE_NOTHROW
    {
        return Exponent();
    }

    /// Re-initializes the instance as a copy of the given one.
    FixedPointDecimal& operator = (const FixedPointDecimal& other) ONIXS_B3_BOE_NOTHROW
    {
        mantissa_ = other.mantissa_;

        return *this;
    }

    /// Serialize to the given data buffer.
    void serialize(void* addr) const ONIXS_B3_BOE_NOTHROW
    {
        assert(addr);

        std::memcpy(addr, &mantissa_, sizeof(mantissa_));
    }
};

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
