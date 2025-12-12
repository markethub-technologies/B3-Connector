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

#include <string>

#include <OnixS/B3/MarketData/UMDF/messaging/Fields.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Composites.h>

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

// Market Data Serialization.

/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    MessageType::Enum value);


/// Serializes into a string.
inline std::string toStr(MessageType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MessageType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MessageType::Enum value)
{
    toStr(
        str,
        static_cast<MessageType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    Boolean::Enum value);


/// Serializes into a string.
inline std::string toStr(Boolean::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    Boolean::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    Boolean::Enum value)
{
    toStr(
        str,
        static_cast<Boolean::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    TimeUnit::Enum value);


/// Serializes into a string.
inline std::string toStr(TimeUnit::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TimeUnit::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TimeUnit::Enum value)
{
    toStr(
        str,
        static_cast<TimeUnit::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    Side::Enum value);


/// Serializes into a string.
inline std::string toStr(Side::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    Side::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    Side::Enum value)
{
    toStr(
        str,
        static_cast<Side::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    SecurityUpdateAction::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityUpdateAction::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityUpdateAction::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityUpdateAction::Enum value)
{
    toStr(
        str,
        static_cast<SecurityUpdateAction::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    LotType::Enum value);


/// Serializes into a string.
inline std::string toStr(LotType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    LotType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    LotType::Enum value)
{
    toStr(
        str,
        static_cast<LotType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    Product::Enum value);


/// Serializes into a string.
inline std::string toStr(Product::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    Product::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    Product::Enum value)
{
    toStr(
        str,
        static_cast<Product::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    SecurityType::Enum value);


/// Serializes into a string.
inline std::string toStr(SecurityType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityType::Enum value)
{
    toStr(
        str,
        static_cast<SecurityType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    ExerciseStyle::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    ExerciseStyle::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ExerciseStyle::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ExerciseStyle::Enum value)
{
    toStr(
        str,
        static_cast<ExerciseStyle::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    PutOrCall::Enum value);


/// Serializes into a string.
inline std::string toStr(PutOrCall::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PutOrCall::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PutOrCall::Enum value)
{
    toStr(
        str,
        static_cast<PutOrCall::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    PriceType::Enum value);


/// Serializes into a string.
inline std::string toStr(PriceType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PriceType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PriceType::Enum value)
{
    toStr(
        str,
        static_cast<PriceType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    SecurityTradingStatus::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityTradingStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityTradingStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityTradingStatus::Enum value)
{
    toStr(
        str,
        static_cast<SecurityTradingStatus::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    TradingSessionSubID::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    TradingSessionSubID::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TradingSessionSubID::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TradingSessionSubID::Enum value)
{
    toStr(
        str,
        static_cast<TradingSessionSubID::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    GovernanceIndicator::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    GovernanceIndicator::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    GovernanceIndicator::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    GovernanceIndicator::Enum value)
{
    toStr(
        str,
        static_cast<GovernanceIndicator::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    SecurityMatchType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityMatchType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityMatchType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityMatchType::Enum value)
{
    toStr(
        str,
        static_cast<SecurityMatchType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    AggressorSide::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    AggressorSide::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    AggressorSide::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    AggressorSide::Enum value)
{
    toStr(
        str,
        static_cast<AggressorSide::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    TradingSessionID::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    TradingSessionID::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TradingSessionID::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TradingSessionID::Enum value)
{
    toStr(
        str,
        static_cast<TradingSessionID::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    SecurityTradingEvent::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityTradingEvent::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityTradingEvent::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityTradingEvent::Enum value)
{
    toStr(
        str,
        static_cast<SecurityTradingEvent::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    PriceBandType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    PriceBandType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PriceBandType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PriceBandType::Enum value)
{
    toStr(
        str,
        static_cast<PriceBandType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    OpenCloseSettlFlag::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    OpenCloseSettlFlag::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    OpenCloseSettlFlag::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    OpenCloseSettlFlag::Enum value)
{
    toStr(
        str,
        static_cast<OpenCloseSettlFlag::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    PriceLimitType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    PriceLimitType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PriceLimitType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PriceLimitType::Enum value)
{
    toStr(
        str,
        static_cast<PriceLimitType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    PriceBandMidpointPriceType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    PriceBandMidpointPriceType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PriceBandMidpointPriceType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PriceBandMidpointPriceType::Enum value)
{
    toStr(
        str,
        static_cast<PriceBandMidpointPriceType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    SettlPriceType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SettlPriceType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SettlPriceType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SettlPriceType::Enum value)
{
    toStr(
        str,
        static_cast<SettlPriceType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    UnderlyingPxType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    UnderlyingPxType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    UnderlyingPxType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    UnderlyingPxType::Enum value)
{
    toStr(
        str,
        static_cast<UnderlyingPxType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    UpdateAction::Enum value);


/// Serializes into a string.
inline std::string toStr(UpdateAction::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    UpdateAction::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    UpdateAction::Enum value)
{
    toStr(
        str,
        static_cast<UpdateAction::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    EntryType::Enum value);


/// Serializes into a string.
inline std::string toStr(EntryType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    EntryType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    EntryType::Enum value)
{
    toStr(
        str,
        static_cast<EntryType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    NewsSource::Enum value);


/// Serializes into a string.
inline std::string toStr(NewsSource::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    NewsSource::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    NewsSource::Enum value)
{
    toStr(
        str,
        static_cast<NewsSource::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    ApplVerID::Enum value);


/// Serializes into a string.
inline std::string toStr(ApplVerID::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ApplVerID::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ApplVerID::Enum value)
{
    toStr(
        str,
        static_cast<ApplVerID::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    MultiLegModel::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    MultiLegModel::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MultiLegModel::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MultiLegModel::Enum value)
{
    toStr(
        str,
        static_cast<MultiLegModel::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    MultiLegPriceMethod::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    MultiLegPriceMethod::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MultiLegPriceMethod::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MultiLegPriceMethod::Enum value)
{
    toStr(
        str,
        static_cast<MultiLegPriceMethod::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    InstrAttribType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    InstrAttribType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    InstrAttribType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    InstrAttribType::Enum value)
{
    toStr(
        str,
        static_cast<InstrAttribType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    InstrAttribValue::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    InstrAttribValue::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    InstrAttribValue::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    InstrAttribValue::Enum value)
{
    toStr(
        str,
        static_cast<InstrAttribValue::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    SecurityIDSource::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityIDSource::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityIDSource::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityIDSource::Enum value)
{
    toStr(
        str,
        static_cast<SecurityIDSource::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    TrdSubType::Enum value);


/// Serializes into a string.
inline std::string toStr(TrdSubType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TrdSubType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TrdSubType::Enum value)
{
    toStr(
        str,
        static_cast<TrdSubType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    ImpliedMarketIndicator::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    ImpliedMarketIndicator::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ImpliedMarketIndicator::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ImpliedMarketIndicator::Enum value)
{
    toStr(
        str,
        static_cast<ImpliedMarketIndicator::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    OptPayoutType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    OptPayoutType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    OptPayoutType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    OptPayoutType::Enum value)
{
    toStr(
        str,
        static_cast<OptPayoutType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    ImbalanceCondition set);


/// Serializes into a string.
inline std::string toStr(ImbalanceCondition set)
{
    std::string str;

    toStr(str, set);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ImbalanceCondition set)
{
    std::string str;

    toStr(str, set);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ImbalanceCondition set)
{
    toStr(str, set.bits());
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    TradeCondition set);


/// Serializes into a string.
inline std::string toStr(TradeCondition set)
{
    std::string str;

    toStr(str, set);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TradeCondition set)
{
    std::string str;

    toStr(str, set);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TradeCondition set)
{
    toStr(str, set.bits());
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    MatchEventIndicator set);


/// Serializes into a string.
inline std::string toStr(MatchEventIndicator set)
{
    std::string str;

    toStr(str, set);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MatchEventIndicator set)
{
    std::string str;

    toStr(str, set);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MatchEventIndicator set)
{
    toStr(str, set.bits());
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const GroupSizeEncoding& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const GroupSizeEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const GroupSizeEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const Percentage& obj);


/// Serializes into a string.
inline std::string toStr(const Percentage& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const Percentage& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const RatioQty& obj);


/// Serializes into a string.
inline std::string toStr(const RatioQty& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const RatioQty& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const UTCTimestampNanos& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const UTCTimestampNanos& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const UTCTimestampNanos& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const UTCTimestampSeconds& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const UTCTimestampSeconds& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const UTCTimestampSeconds& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const MaturityMonthYear& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const MaturityMonthYear& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const MaturityMonthYear& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const PriceOffset8Optional& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const PriceOffset8Optional& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const PriceOffset8Optional& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const TextEncoding& obj);


/// Serializes into a string.
inline std::string toStr(const TextEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const TextEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const VarString& obj);


/// Serializes into a string.
inline std::string toStr(const VarString& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const VarString& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


inline std::string ImbalanceCondition::toString() const
{
    return toStr(*this);
}

inline std::string TradeCondition::toString() const
{
    return toStr(*this);
}

inline std::string MatchEventIndicator::toString() const
{
    return toStr(*this);
}

inline std::string GroupSizeEncoding::toString() const
{
    return toStr(*this);
}

inline std::string UTCTimestampNanos::toString() const
{
    return toStr(*this);
}

inline std::string UTCTimestampSeconds::toString() const
{
    return toStr(*this);
}

inline std::string MaturityMonthYear::toString() const
{
    return toStr(*this);
}

inline std::string TextEncoding::toString() const
{
    return toStr(*this);
}

inline std::string VarString::toString() const
{
    return toStr(*this);
}

inline std::string MessageType::toString(MessageType::Enum value)
{
    return toStr(value);
}

inline std::string Boolean::toString(Boolean::Enum value)
{
    return toStr(value);
}

inline std::string TimeUnit::toString(TimeUnit::Enum value)
{
    return toStr(value);
}

inline std::string Side::toString(Side::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityUpdateAction::toString(
    SecurityUpdateAction::Enum value)
{
    return toStr(value);
}

inline std::string LotType::toString(LotType::Enum value)
{
    return toStr(value);
}

inline std::string Product::toString(Product::Enum value)
{
    return toStr(value);
}

inline std::string SecurityType::toString(SecurityType::Enum value)
{
    return toStr(value);
}

inline
std::string
ExerciseStyle::toString(
    ExerciseStyle::Enum value)
{
    return toStr(value);
}

inline std::string PutOrCall::toString(PutOrCall::Enum value)
{
    return toStr(value);
}

inline std::string PriceType::toString(PriceType::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityTradingStatus::toString(
    SecurityTradingStatus::Enum value)
{
    return toStr(value);
}

inline
std::string
TradingSessionSubID::toString(
    TradingSessionSubID::Enum value)
{
    return toStr(value);
}

inline
std::string
GovernanceIndicator::toString(
    GovernanceIndicator::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityMatchType::toString(
    SecurityMatchType::Enum value)
{
    return toStr(value);
}

inline
std::string
AggressorSide::toString(
    AggressorSide::Enum value)
{
    return toStr(value);
}

inline
std::string
TradingSessionID::toString(
    TradingSessionID::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityTradingEvent::toString(
    SecurityTradingEvent::Enum value)
{
    return toStr(value);
}

inline
std::string
PriceBandType::toString(
    PriceBandType::Enum value)
{
    return toStr(value);
}

inline
std::string
OpenCloseSettlFlag::toString(
    OpenCloseSettlFlag::Enum value)
{
    return toStr(value);
}

inline
std::string
PriceLimitType::toString(
    PriceLimitType::Enum value)
{
    return toStr(value);
}

inline
std::string
PriceBandMidpointPriceType::toString(
    PriceBandMidpointPriceType::Enum value)
{
    return toStr(value);
}

inline
std::string
SettlPriceType::toString(
    SettlPriceType::Enum value)
{
    return toStr(value);
}

inline
std::string
UnderlyingPxType::toString(
    UnderlyingPxType::Enum value)
{
    return toStr(value);
}

inline std::string UpdateAction::toString(UpdateAction::Enum value)
{
    return toStr(value);
}

inline std::string EntryType::toString(EntryType::Enum value)
{
    return toStr(value);
}

inline std::string NewsSource::toString(NewsSource::Enum value)
{
    return toStr(value);
}

inline std::string ApplVerID::toString(ApplVerID::Enum value)
{
    return toStr(value);
}

inline
std::string
MultiLegModel::toString(
    MultiLegModel::Enum value)
{
    return toStr(value);
}

inline
std::string
MultiLegPriceMethod::toString(
    MultiLegPriceMethod::Enum value)
{
    return toStr(value);
}

inline
std::string
InstrAttribType::toString(
    InstrAttribType::Enum value)
{
    return toStr(value);
}

inline
std::string
InstrAttribValue::toString(
    InstrAttribValue::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityIDSource::toString(
    SecurityIDSource::Enum value)
{
    return toStr(value);
}

inline std::string TrdSubType::toString(TrdSubType::Enum value)
{
    return toStr(value);
}

inline
std::string
ImpliedMarketIndicator::toString(
    ImpliedMarketIndicator::Enum value)
{
    return toStr(value);
}

inline
std::string
OptPayoutType::toString(
    OptPayoutType::Enum value)
{
    return toStr(value);
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
