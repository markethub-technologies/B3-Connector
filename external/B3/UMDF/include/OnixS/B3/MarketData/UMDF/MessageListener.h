/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable ONIXS Software
* Services Agreement (the Agreement) and Customer end user license agreements granting
* a non-assignable, non-transferable and non-exclusive license to use the software
* for it's own data processing purposes under the terms defined in the Agreement.
*
* Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
* of this source code or associated reference material to any other location for further reproduction
* or redistribution, and any amendments to this copyright notice, are expressly prohibited.
*
* Any reproduction or redistribution for sale or hiring of the Software not in accordance with
* the terms of the Agreement is a violation of copyright law.
*/

#pragma once

#include <OnixS/B3/MarketData/UMDF/messaging/Messages.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Forwards.h>
#include <OnixS/B3/MarketData/UMDF/Defines.h>

namespace OnixS {
namespace B3 {
namespace MarketData {
namespace UMDF {

    /// Message listener
    class ONIXS_B3_UMDF_MD_API MessageListener
    {
        public:
            virtual void onSequenceReset_1(const Messaging::SequenceReset_1, const DataSource&) {}
            virtual void onSequence_2(const Messaging::Sequence_2, const DataSource&) {}
            virtual void onEmptyBook_9(const Messaging::EmptyBook_9, const DataSource&) {}
            virtual void onChannelReset_11(const Messaging::ChannelReset_11, const DataSource&) {}
            virtual void onSecurityStatus_3(const Messaging::SecurityStatus_3, const DataSource&) {}
            virtual void onSecurityGroupPhase_10(const Messaging::SecurityGroupPhase_10, const DataSource&) {}
            virtual void onSecurityDefinition_12(const Messaging::SecurityDefinition_12, const DataSource&) {}

            virtual void onSnapshotFullRefresh_Header_30(const Messaging::SnapshotFullRefresh_Header_30, const DataSource&) {}
            virtual void onSnapshotFullRefresh_Orders_MBO_71(const Messaging::SnapshotFullRefresh_Orders_MBO_71, const DataSource&) {}

            virtual void onNews_5(const Messaging::News_5, const DataSource&) {}
            virtual void onClosingPrice_17(const Messaging::ClosingPrice_17, const DataSource&) {}
            virtual void onQuantityBand_21(const Messaging::QuantityBand_21, const DataSource&) {}
            virtual void onPriceBand_22(const Messaging::PriceBand_22, const DataSource&) {}

            virtual void onOpeningPrice_15(const Messaging::OpeningPrice_15, const DataSource&) {}
            virtual void onTheoreticalOpeningPrice_16(const Messaging::TheoreticalOpeningPrice_16, const DataSource&) {}
            virtual void onAuctionImbalance_19(const Messaging::AuctionImbalance_19, const DataSource&) {}
            virtual void onHighPrice_24(const Messaging::HighPrice_24, const DataSource&) {}
            virtual void onLowPrice_25(const Messaging::LowPrice_25, const DataSource&) {}
            virtual void onLastTradePrice_27(const Messaging::LastTradePrice_27, const DataSource&) {}
            virtual void onSettlementPrice_28(const Messaging::SettlementPrice_28, const DataSource&) {}
            virtual void onOpenInterest_29(const Messaging::OpenInterest_29, const DataSource&) {}
            virtual void onOrder_MBO_50(const Messaging::Order_MBO_50, const DataSource&) {}
            virtual void onDeleteOrder_MBO_51(const Messaging::DeleteOrder_MBO_51, const DataSource&) {}
            virtual void onMassDeleteOrders_MBO_52(const Messaging::MassDeleteOrders_MBO_52, const DataSource&) {}
            virtual void onTrade_53(const Messaging::Trade_53, const DataSource&) {}
            virtual void onForwardTrade_54(const Messaging::ForwardTrade_54, const DataSource&) {}
            virtual void onExecutionSummary_55(const Messaging::ExecutionSummary_55, const DataSource&) {}
            virtual void onExecutionStatistics_56(const Messaging::ExecutionStatistics_56, const DataSource&) {}
            virtual void onTradeBust_57(const Messaging::TradeBust_57, const DataSource&) {}

            virtual void onUnknownMessage(const Messaging::SbeMessage, const DataSource&) {}

            virtual void onInstrumentChannelGap() {}
            virtual void onInstrumentChannelInactivity() {}
            virtual void onInstrumentRecoveryStarted() {}
            virtual void onInstrumentRecoveryFinished() {}

            virtual void onSnapshotChannelGap() {}
            virtual void onSnapshotChannelInactivity() {}
            virtual void onSnapshotRecoveryStarted() {}
            virtual void onSnapshotRecoveryFinished() {}

            virtual void onIncrementalChannelGap() {}
            virtual void onIncrementalChannelInactivity() {}

            virtual void onInstrumentSequenceGap(Messaging::SecurityID) {}

        protected:
            virtual ~MessageListener() = 0;
    };
}
}
}
}
