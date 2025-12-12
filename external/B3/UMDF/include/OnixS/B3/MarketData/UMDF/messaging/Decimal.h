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

#include <OnixS/B3/MarketData/UMDF/messaging/Integral.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Memory.h>

#include <string>

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

/// Forward declarations
template <class MantissaType, class ExponentType> class FixedPointDecimal;
template<class Mantissa, class Exponent> std::string toStr(const FixedPointDecimal <Mantissa, Exponent>&);

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
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const
    {
        return toStr(*this);
    }

    /// Default (zero) initialization.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    FixedPointDecimal() ONIXS_B3_UMDF_MD_NOTHROW
        : mantissa_()
    {
    }

    /// Explicitly initializes the instance from the mantissa value.
    explicit ONIXS_B3_UMDF_MD_CONSTEXPR FixedPointDecimal(Mantissa mantissa) ONIXS_B3_UMDF_MD_NOTHROW
        : mantissa_(mantissa)
    {
    }

    /// \return mantissa.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Mantissa mantissa() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return mantissa_;
    }

    /// \return exponent.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    Exponent exponent() const ONIXS_B3_UMDF_MD_NOTHROW
    {
        return Exponent();
    }

    /// Serialize to the given data buffer.
    void serialize(void* addr) const ONIXS_B3_UMDF_MD_NOTHROW
    {
        assert(addr);

        std::memcpy(addr, &mantissa_, sizeof(mantissa_));
    }
};

/// A nullable real number with a constant exponent.
template
<
    class MantissaType,
    class ExponentType,
    class NullMantissaType
>
class NullableFixedPointDecimal : public FixedPointDecimal<MantissaType, ExponentType>
{
public:
    /// Default (zero) initialization.
    ONIXS_B3_UMDF_MD_CONSTEXPR
    NullableFixedPointDecimal() ONIXS_B3_UMDF_MD_NOTHROW
      : FixedPointDecimal<MantissaType, ExponentType>()
    {
    }

    /// Explicitly initializes the instance from the mantissa value.
    explicit ONIXS_B3_UMDF_MD_CONSTEXPR NullableFixedPointDecimal(MantissaType mantissa) ONIXS_B3_UMDF_MD_NOTHROW
      : FixedPointDecimal<MantissaType, ExponentType>(mantissa)
    {
    }

    ONIXS_B3_UMDF_MD_CONSTEXPR
    static NullMantissaType nullMantissa() ONIXS_B3_UMDF_MD_NOTHROW
    {
        return NullMantissaType();
    }

    ONIXS_B3_UMDF_MD_CONSTEXPR
    static NullableFixedPointDecimal nullValue() ONIXS_B3_UMDF_MD_NOTHROW
    {
        return NullableFixedPointDecimal(nullMantissa());
    }


    /// \return whether the value is `Null`.
    bool isNull() const { return nullMantissa() == this->mantissa(); }
};

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
