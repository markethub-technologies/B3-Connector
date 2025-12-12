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

//! [MyListenerCpp]
#include <iostream>

#include "MyListener.h"

namespace Sample
{
    MyListener::MyListener()
    {
        const std::string marketDataLogName = "logs/MarketData.txt";
        marketDataLog_.open (marketDataLogName.c_str() );

        if (!marketDataLog_)
            throw std::domain_error ("Cannot open " + marketDataLogName);
    }

    void MyListener::onWarning (const std::string& reason)
    {
        std::clog << "Warning occurred. Description: '" << reason << "'" << std::endl;
    }

    void MyListener::onError (ErrorCode::Enum code, const std::string& description)
    {
        std::clog << "Error occurred, errorCode = " << enumToString (code) << ". Description: '" << description << "'" << std::endl;
    }

    void MyListener::onSequenceReset_1(const Messaging::SequenceReset_1 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onSequence_2(const Messaging::Sequence_2 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onEmptyBook_9(const Messaging::EmptyBook_9 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onChannelReset_11(const Messaging::ChannelReset_11 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onSecurityStatus_3(const Messaging::SecurityStatus_3 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onSecurityGroupPhase_10(const Messaging::SecurityGroupPhase_10 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onSecurityDefinition_12(const Messaging::SecurityDefinition_12 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }


    void MyListener::onSnapshotFullRefresh_Header_30(const Messaging::SnapshotFullRefresh_Header_30 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onSnapshotFullRefresh_Orders_MBO_71(const Messaging::SnapshotFullRefresh_Orders_MBO_71 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }


    void MyListener::onNews_5(const Messaging::News_5 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onClosingPrice_17(const Messaging::ClosingPrice_17 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onQuantityBand_21(const Messaging::QuantityBand_21 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onPriceBand_22(const Messaging::PriceBand_22 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onOpeningPrice_15(const Messaging::OpeningPrice_15 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onTheoreticalOpeningPrice_16(const Messaging::TheoreticalOpeningPrice_16 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onAuctionImbalance_19(const Messaging::AuctionImbalance_19 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onHighPrice_24(const Messaging::HighPrice_24 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onLowPrice_25(const Messaging::LowPrice_25 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onLastTradePrice_27(const Messaging::LastTradePrice_27 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onSettlementPrice_28(const Messaging::SettlementPrice_28 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onOpenInterest_29(const Messaging::OpenInterest_29 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onOrder_MBO_50(const Messaging::Order_MBO_50 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onDeleteOrder_MBO_51(const Messaging::DeleteOrder_MBO_51 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onMassDeleteOrders_MBO_52(const Messaging::MassDeleteOrders_MBO_52 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onTrade_53(const Messaging::Trade_53 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onForwardTrade_54(const Messaging::ForwardTrade_54 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onExecutionSummary_55(const Messaging::ExecutionSummary_55 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onExecutionStatistics_56(const Messaging::ExecutionStatistics_56 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }

    void MyListener::onTradeBust_57(const Messaging::TradeBust_57 msg, const DataSource&)
    {
        marketDataLog_ << msg << std::endl;
    }
}
//! [MyListenerCpp]
