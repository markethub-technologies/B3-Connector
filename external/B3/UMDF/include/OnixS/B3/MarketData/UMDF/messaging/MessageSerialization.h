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

#include <OnixS/B3/MarketData/UMDF/messaging/Messages.h>


ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

// Market Data Serialization.

/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SequenceReset_1& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SequenceReset_1& obj)
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
    const SequenceReset_1& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SequenceReset_1::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const SequenceReset_1& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const Sequence_2& obj);


/// Serializes into a string.
inline std::string toStr(const Sequence_2& obj)
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
    const Sequence_2& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Sequence_2::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const Sequence_2& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const EmptyBook_9& obj);


/// Serializes into a string.
inline std::string toStr(const EmptyBook_9& obj)
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
    const EmptyBook_9& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string EmptyBook_9::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const EmptyBook_9& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const ChannelReset_11& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ChannelReset_11& obj)
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
    const ChannelReset_11& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ChannelReset_11::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const ChannelReset_11& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SecurityStatus_3& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SecurityStatus_3& obj)
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
    const SecurityStatus_3& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SecurityStatus_3::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const SecurityStatus_3& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SecurityGroupPhase_10& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SecurityGroupPhase_10& obj)
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
    const SecurityGroupPhase_10& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SecurityGroupPhase_10::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const SecurityGroupPhase_10& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SecurityDefinition_12& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SecurityDefinition_12& obj)
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
    const SecurityDefinition_12& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SecurityDefinition_12::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const SecurityDefinition_12& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SecurityDefinition_12::UnderlyingsEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const SecurityDefinition_12::UnderlyingsEntry& obj)
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
    const SecurityDefinition_12::UnderlyingsEntry& obj)
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
    const SecurityDefinition_12::LegsEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const SecurityDefinition_12::LegsEntry& obj)
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
    const SecurityDefinition_12::LegsEntry& obj)
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
    const SecurityDefinition_12::InstrAttribsEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const SecurityDefinition_12::InstrAttribsEntry& obj)
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
    const SecurityDefinition_12::InstrAttribsEntry& obj)
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
    const News_5& obj);


/// Serializes into a string.
inline std::string toStr(const News_5& obj)
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
    const News_5& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string News_5::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const News_5& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const OpeningPrice_15& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const OpeningPrice_15& obj)
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
    const OpeningPrice_15& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string OpeningPrice_15::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const OpeningPrice_15& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const TheoreticalOpeningPrice_16& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const TheoreticalOpeningPrice_16& obj)
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
    const TheoreticalOpeningPrice_16& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string TheoreticalOpeningPrice_16::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const TheoreticalOpeningPrice_16& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const ClosingPrice_17& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ClosingPrice_17& obj)
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
    const ClosingPrice_17& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ClosingPrice_17::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const ClosingPrice_17& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const AuctionImbalance_19& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const AuctionImbalance_19& obj)
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
    const AuctionImbalance_19& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string AuctionImbalance_19::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const AuctionImbalance_19& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const QuantityBand_21& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const QuantityBand_21& obj)
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
    const QuantityBand_21& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string QuantityBand_21::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const QuantityBand_21& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const PriceBand_22& obj);


/// Serializes into a string.
inline std::string toStr(const PriceBand_22& obj)
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
    const PriceBand_22& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string PriceBand_22::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const PriceBand_22& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const HighPrice_24& obj);


/// Serializes into a string.
inline std::string toStr(const HighPrice_24& obj)
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
    const HighPrice_24& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string HighPrice_24::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const HighPrice_24& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const LowPrice_25& obj);


/// Serializes into a string.
inline std::string toStr(const LowPrice_25& obj)
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
    const LowPrice_25& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string LowPrice_25::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const LowPrice_25& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const LastTradePrice_27& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const LastTradePrice_27& obj)
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
    const LastTradePrice_27& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string LastTradePrice_27::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const LastTradePrice_27& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SettlementPrice_28& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SettlementPrice_28& obj)
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
    const SettlementPrice_28& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SettlementPrice_28::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const SettlementPrice_28& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const OpenInterest_29& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const OpenInterest_29& obj)
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
    const OpenInterest_29& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string OpenInterest_29::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const OpenInterest_29& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SnapshotFullRefresh_Header_30& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SnapshotFullRefresh_Header_30& obj)
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
    const SnapshotFullRefresh_Header_30& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SnapshotFullRefresh_Header_30::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const SnapshotFullRefresh_Header_30& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const Order_MBO_50& obj);


/// Serializes into a string.
inline std::string toStr(const Order_MBO_50& obj)
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
    const Order_MBO_50& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Order_MBO_50::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const Order_MBO_50& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const DeleteOrder_MBO_51& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const DeleteOrder_MBO_51& obj)
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
    const DeleteOrder_MBO_51& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string DeleteOrder_MBO_51::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const DeleteOrder_MBO_51& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const MassDeleteOrders_MBO_52& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const MassDeleteOrders_MBO_52& obj)
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
    const MassDeleteOrders_MBO_52& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string MassDeleteOrders_MBO_52::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const MassDeleteOrders_MBO_52& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const Trade_53& obj);


/// Serializes into a string.
inline std::string toStr(const Trade_53& obj)
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
    const Trade_53& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Trade_53::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const Trade_53& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const ForwardTrade_54& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ForwardTrade_54& obj)
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
    const ForwardTrade_54& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ForwardTrade_54::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const ForwardTrade_54& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const ExecutionSummary_55& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionSummary_55& obj)
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
    const ExecutionSummary_55& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionSummary_55::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionSummary_55& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const ExecutionStatistics_56& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionStatistics_56& obj)
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
    const ExecutionStatistics_56& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionStatistics_56::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionStatistics_56& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const TradeBust_57& obj);


/// Serializes into a string.
inline std::string toStr(const TradeBust_57& obj)
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
    const TradeBust_57& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string TradeBust_57::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const TradeBust_57& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SnapshotFullRefresh_Orders_MBO_71& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SnapshotFullRefresh_Orders_MBO_71& obj)
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
    const SnapshotFullRefresh_Orders_MBO_71& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SnapshotFullRefresh_Orders_MBO_71::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_UMDF_MD_EXPORTED
void
toFix(
    std::string& str,
    const SnapshotFullRefresh_Orders_MBO_71& obj);


/// Serializes into a string.
ONIXS_B3_UMDF_MD_EXPORTED
void
toStr(
    std::string& str,
    const SnapshotFullRefresh_Orders_MBO_71::Entry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const SnapshotFullRefresh_Orders_MBO_71::Entry& obj)
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
    const SnapshotFullRefresh_Orders_MBO_71::Entry& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
