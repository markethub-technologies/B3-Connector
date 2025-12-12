#pragma once
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

//! [MyListenerH]
#include <fstream>

#include <OnixS/B3/MarketData/UMDF/ErrorListener.h>
#include <OnixS/B3/MarketData/UMDF/Messaging.h>
#include <OnixS/B3/MarketData/UMDF/MessageListener.h>
#include <OnixS/B3/MarketData/UMDF/WarningListener.h>

namespace Sample
{

    using namespace OnixS::B3::MarketData::UMDF;

    class MyListener :
        public MessageListener,
        public WarningListener,
        public ErrorListener
    {
        public:
            /// Constructor
            MyListener();

            /// Inherited from Warning Listener
            /// Is called when the Warning condition is detected
            void onWarning (const std::string& reason)
            ONIXS_B3_UMDF_MD_FINAL;

            /// Inherited from Error Listener
            /// Notifications about errors
            void onError (ErrorCode::Enum code, const std::string& description)
            ONIXS_B3_UMDF_MD_FINAL;

            void onSequenceReset_1(const Messaging::SequenceReset_1, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onSequence_2(const Messaging::Sequence_2, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onEmptyBook_9(const Messaging::EmptyBook_9, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onChannelReset_11(const Messaging::ChannelReset_11, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onSecurityStatus_3(const Messaging::SecurityStatus_3, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onSecurityGroupPhase_10(const Messaging::SecurityGroupPhase_10, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onSecurityDefinition_12(const Messaging::SecurityDefinition_12, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;

            void onSnapshotFullRefresh_Header_30(const Messaging::SnapshotFullRefresh_Header_30, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onSnapshotFullRefresh_Orders_MBO_71(const Messaging::SnapshotFullRefresh_Orders_MBO_71, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;

            void onNews_5(const Messaging::News_5, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onClosingPrice_17(const Messaging::ClosingPrice_17, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onQuantityBand_21(const Messaging::QuantityBand_21, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onPriceBand_22(const Messaging::PriceBand_22, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;

            void onOpeningPrice_15(const Messaging::OpeningPrice_15, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onTheoreticalOpeningPrice_16(const Messaging::TheoreticalOpeningPrice_16, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onAuctionImbalance_19(const Messaging::AuctionImbalance_19, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onHighPrice_24(const Messaging::HighPrice_24, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onLowPrice_25(const Messaging::LowPrice_25, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onLastTradePrice_27(const Messaging::LastTradePrice_27, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onSettlementPrice_28(const Messaging::SettlementPrice_28, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onOpenInterest_29(const Messaging::OpenInterest_29, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onOrder_MBO_50(const Messaging::Order_MBO_50, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onDeleteOrder_MBO_51(const Messaging::DeleteOrder_MBO_51, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onMassDeleteOrders_MBO_52(const Messaging::MassDeleteOrders_MBO_52, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onTrade_53(const Messaging::Trade_53, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onForwardTrade_54(const Messaging::ForwardTrade_54, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onExecutionSummary_55(const Messaging::ExecutionSummary_55, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onExecutionStatistics_56(const Messaging::ExecutionStatistics_56, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
            void onTradeBust_57(const Messaging::TradeBust_57, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;

        private:
            std::ofstream marketDataLog_;
    };

}
//! [MyListenerH]
