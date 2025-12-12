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

#include <OnixS/B3/MarketData/UMDF/messaging/Messages.h>

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

/// Casts SBE-encoded message to a given type.
template
    <
        class Message
    >
inline
ONIXS_B3_UMDF_MD_NODISCARD
ONIXS_B3_UMDF_MD_PURE
Message
typify(
    const SbeMessage message)
{
    return Message(message);
}

/// Casts a given binary message according to template/type
/// information and processes the cast messages by a given processor.
///
/// Returned value indicates whether message type was successfully
/// recognized and pushed to the processor for further processing. Unknown
/// messages aren't processed and thus false result is returned.
template
<
    class Processor
>
inline
ONIXS_B3_UMDF_MD_NODISCARD
bool
processTypified(
    const SbeMessage binary,
    Processor&& processor)
{
    switch (binary.templateId())
    {
    case SequenceReset_1::TemplateId:
    {
        processor(
            typify
            <SequenceReset_1>
            (binary));

        return true;
    }

    case Sequence_2::TemplateId:
    {
        processor(
            typify
            <Sequence_2>
            (binary));

        return true;
    }

    case EmptyBook_9::TemplateId:
    {
        processor(
            typify
            <EmptyBook_9>
            (binary));

        return true;
    }

    case ChannelReset_11::TemplateId:
    {
        processor(
            typify
            <ChannelReset_11>
            (binary));

        return true;
    }

    case SecurityStatus_3::TemplateId:
    {
        processor(
            typify
            <SecurityStatus_3>
            (binary));

        return true;
    }

    case SecurityGroupPhase_10::TemplateId:
    {
        processor(
            typify
            <SecurityGroupPhase_10>
            (binary));

        return true;
    }

    case SecurityDefinition_12::TemplateId:
    {
        processor(
            typify
            <SecurityDefinition_12>
            (binary));

        return true;
    }

    case News_5::TemplateId:
    {
        processor(
            typify
            <News_5>
            (binary));

        return true;
    }

    case OpeningPrice_15::TemplateId:
    {
        processor(
            typify
            <OpeningPrice_15>
            (binary));

        return true;
    }

    case TheoreticalOpeningPrice_16::TemplateId:
    {
        processor(
            typify
            <TheoreticalOpeningPrice_16>
            (binary));

        return true;
    }

    case ClosingPrice_17::TemplateId:
    {
        processor(
            typify
            <ClosingPrice_17>
            (binary));

        return true;
    }

    case AuctionImbalance_19::TemplateId:
    {
        processor(
            typify
            <AuctionImbalance_19>
            (binary));

        return true;
    }

    case QuantityBand_21::TemplateId:
    {
        processor(
            typify
            <QuantityBand_21>
            (binary));

        return true;
    }

    case PriceBand_22::TemplateId:
    {
        processor(
            typify
            <PriceBand_22>
            (binary));

        return true;
    }

    case HighPrice_24::TemplateId:
    {
        processor(
            typify
            <HighPrice_24>
            (binary));

        return true;
    }

    case LowPrice_25::TemplateId:
    {
        processor(
            typify
            <LowPrice_25>
            (binary));

        return true;
    }

    case LastTradePrice_27::TemplateId:
    {
        processor(
            typify
            <LastTradePrice_27>
            (binary));

        return true;
    }

    case SettlementPrice_28::TemplateId:
    {
        processor(
            typify
            <SettlementPrice_28>
            (binary));

        return true;
    }

    case OpenInterest_29::TemplateId:
    {
        processor(
            typify
            <OpenInterest_29>
            (binary));

        return true;
    }

    case SnapshotFullRefresh_Header_30::TemplateId:
    {
        processor(
            typify
            <SnapshotFullRefresh_Header_30>
            (binary));

        return true;
    }

    case Order_MBO_50::TemplateId:
    {
        processor(
            typify
            <Order_MBO_50>
            (binary));

        return true;
    }

    case DeleteOrder_MBO_51::TemplateId:
    {
        processor(
            typify
            <DeleteOrder_MBO_51>
            (binary));

        return true;
    }

    case MassDeleteOrders_MBO_52::TemplateId:
    {
        processor(
            typify
            <MassDeleteOrders_MBO_52>
            (binary));

        return true;
    }

    case Trade_53::TemplateId:
    {
        processor(
            typify
            <Trade_53>
            (binary));

        return true;
    }

    case ForwardTrade_54::TemplateId:
    {
        processor(
            typify
            <ForwardTrade_54>
            (binary));

        return true;
    }

    case ExecutionSummary_55::TemplateId:
    {
        processor(
            typify
            <ExecutionSummary_55>
            (binary));

        return true;
    }

    case ExecutionStatistics_56::TemplateId:
    {
        processor(
            typify
            <ExecutionStatistics_56>
            (binary));

        return true;
    }

    case TradeBust_57::TemplateId:
    {
        processor(
            typify
            <TradeBust_57>
            (binary));

        return true;
    }

    case SnapshotFullRefresh_Orders_MBO_71::TemplateId:
    {
        processor(
            typify
            <SnapshotFullRefresh_Orders_MBO_71>
            (binary));

        return true;
    }

    default:
        return false;
    }
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
