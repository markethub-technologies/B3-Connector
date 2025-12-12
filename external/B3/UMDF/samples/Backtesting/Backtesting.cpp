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

//! [BacktestingSample]
#include <iostream>

#include <OnixS/B3/MarketData/UMDF.h>

#include "OnixS/B3/MarketData/UMDF/Messaging.h"


using namespace OnixS::B3::MarketData::UMDF;

class MyListener
    : public ErrorListener
    , public WarningListener
    , public ReplayListener
    , public MessageListener
{

public:
    /// Notifications about errors.
    void onError(ErrorCode::Enum code, const std::string& description) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog
            << "Error occurred, errorCode = "
            << enumToString (code)
            << ". Description: '"
            << description
            << "'"
            << std::endl;
    }

    /// Notifications about warnings.
    void onWarning(const std::string& description) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog
            << "Warning occurred. Description: '"
            << description
            << "'"
            << std::endl;
    };

    void onReplayError(const std::string& errorDescription) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << "Replay error: " << errorDescription << std::endl;
        replaySemaphore_.release();
    }

    void onReplayFinished() ONIXS_B3_UMDF_MD_FINAL
    {
        replaySemaphore_.release();
    }

    /// Wait for reference data snapshot cycle end.
    void waitUntilReplayFinished()
    {
        replaySemaphore_.acquire();
    }

    void onSequenceReset_1(const Messaging::SequenceReset_1 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onSequence_2(const Messaging::Sequence_2 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onEmptyBook_9(const Messaging::EmptyBook_9 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onChannelReset_11(const Messaging::ChannelReset_11 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onSecurityStatus_3(const Messaging::SecurityStatus_3 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onSecurityGroupPhase_10(const Messaging::SecurityGroupPhase_10 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onSecurityDefinition_12(const Messaging::SecurityDefinition_12 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onSnapshotFullRefresh_Header_30(const Messaging::SnapshotFullRefresh_Header_30 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onSnapshotFullRefresh_Orders_MBO_71(const Messaging::SnapshotFullRefresh_Orders_MBO_71 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onNews_5(const Messaging::News_5 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onClosingPrice_17(const Messaging::ClosingPrice_17 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onQuantityBand_21(const Messaging::QuantityBand_21 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onPriceBand_22(const Messaging::PriceBand_22 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onOpeningPrice_15(const Messaging::OpeningPrice_15 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onTheoreticalOpeningPrice_16(const Messaging::TheoreticalOpeningPrice_16 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onAuctionImbalance_19(const Messaging::AuctionImbalance_19 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onHighPrice_24(const Messaging::HighPrice_24 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onLowPrice_25(const Messaging::LowPrice_25 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onLastTradePrice_27(const Messaging::LastTradePrice_27 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onSettlementPrice_28(const Messaging::SettlementPrice_28 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onOpenInterest_29(const Messaging::OpenInterest_29 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onOrder_MBO_50(const Messaging::Order_MBO_50 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onDeleteOrder_MBO_51(const Messaging::DeleteOrder_MBO_51 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onMassDeleteOrders_MBO_52(const Messaging::MassDeleteOrders_MBO_52 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onTrade_53(const Messaging::Trade_53 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onForwardTrade_54(const Messaging::ForwardTrade_54 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onExecutionSummary_55(const Messaging::ExecutionSummary_55 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onExecutionStatistics_56(const Messaging::ExecutionStatistics_56 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }

    void onTradeBust_57(const Messaging::TradeBust_57 msg, const DataSource&) ONIXS_B3_UMDF_MD_FINAL
    {
        std::clog << msg << std::endl;
    }


private:
    /// Signaled when all reference data is received.
    System::Semaphore replaySemaphore_;
};

void replayLog(HandlerSettings settings)
{
    MyListener listener;
    Handler handler(settings);
    handler.log(LogLevel::Trace, "Replay log sample.");

    handler.registerMessageListener(&listener);

    ReplayOptions replayOptions;
    replayOptions.listener = &listener;
    replayOptions.files.push_back ("data/log.log");

    handler.replayLogs(replayOptions);
    listener.waitUntilReplayFinished();
}

void replayPcap(HandlerSettings settings)
{
    settings.snapshotFeeds.a = Feed("233.252.8.4", 30068);
    settings.instrumentFeeds.a = Feed("233.252.8.6", 10068);
    settings.incrementalFeeds.a = Feed("233.252.8.5", 20068);

    MyListener listener;
    Handler handler(settings);
    handler.log(LogLevel::Trace, "Replay pcap sample.");

    handler.registerMessageListener(&listener);

    ReplayOptions replayOptions;
    replayOptions.listener = &listener;
    replayOptions.files.push_back("data/Incremental.pcap.gz");
    handler.replayPcap(replayOptions, {"data/Instrument.pcap.gz"}, {"data/Snapshot.pcap.gz"});

    listener.waitUntilReplayFinished();
}

/// The main entry point.
int main ()
{
    std::clog
        << "OnixS C++ B3 Binary UMDF Market Data Handler Backtesting sample, version "
        << Handler::version ()
        << '.'
        << std::endl
        << std::endl;

    HandlerSettings settings;
    settings.licenseDirectory = "../../license";
    settings.loggerSettings.logDirectory = "logs";
    settings.loggerSettings.logLevel = LogLevel::Debug;
    settings.buildOrderBooks = true;

    try
    {
        std::clog << "Will start the Handler in replay mode ..." << std::endl;

        replayLog(settings);
        replayPcap(settings);

        std::clog << "Replay finished" << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "EXCEPTION: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "UNKNOWN EXCEPTION" << std::endl;
    }

    return 0;
}
//! [BacktestingSample]
