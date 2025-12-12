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

//! [BenchmarkSample]
#include <iostream>

#include <Common/Configuring.h>
#include <Common/Options.h>
#include <Common/Utils.h>

#include "MyListener.h"

#include <OnixS/B3/MarketData/UMDF/Handler.h>
#include <OnixS/B3/MarketData/UMDF/HandlerSettings.h>

#define ONIXS_USE_EF_VI 0


using namespace OnixS::B3::MarketData::UMDF;
using Sample::MyListener;

typedef std::shared_ptr<OrderBookPool> OrderBookPoolPtr;

constexpr UInt32 MaxProcessedPackets = 1000000;

// Handles sample input parameters.
class Configuration
    : public ChannelConfiguration
    , public ConnectivityConfiguration
    , public FeedConfiguration
{
public:
    Configuration(size_t qty, Char** args)
        : ConfigurationBase(qty, args)
        , ChannelConfiguration(qty, args, 80)
        , ConnectivityConfiguration(qty, args)
        , FeedConfiguration(qty, args)
    {
    }

    UInt32 packetsCount() const
    {
        return argOrDefault(options(), "packetsCount", MaxProcessedPackets);
    }

    bool measureBookChanges() const
    {
        return exist(options(), "measureBookChanges");
    }

    UInt32 chunksLength() const
    {
        return argOrDefault<UInt32>(options(), "chunksLength", 2 * 1024 * 1024);
    }

    std::set<Messaging::SecurityID> instruments() const
    {
        return argSetOrDefault<Messaging::SecurityID>(options(), "instruments", 10018438);
    }

private:
    void showOptions(std::ostream& out) const ONIXS_B3_UMDF_MD_OVERRIDE
    {
        ChannelConfiguration::showOptions(out);

        out << "  --packetsCount <target>" << std::endl
            << "\tDefines the number of incremental packets to process. The MaxProcessedPackets value is used by default." << std::endl
            << std::endl;

        out << "  --instruments <list>" << std::endl
            << "\tA comma-separated list of `SecurityID`'s of interest." << std::endl
            << std::endl;

        out << "  --measureBookChanges" << std::endl
            << "\tMeasure book change latency." << std::endl
            << std::endl
            << "  --chunksLength <number>" << std::endl
            << "\tDefines the amount of memory chunks used for book building, see OrderBookPoolSettings::chunkLength." << std::endl
            << std::endl;


        ConnectivityConfiguration::showOptions(out);
        FeedConfiguration::showOptions(out);
    }
};

template <typename T>
bool run(T & engine)
{
    try
    {
        return process(engine);
    }
    catch(const std::exception& ex)
    {
        std::cerr << std::endl
                  << "WARNING! Feed engine raised an issue while processing incoming data. "
                  << ex.what() << std::endl;
    }

    return false;
}

/// The main entry point.
int main(int qty, char** args)
{
    std::clog << "OnixS C++ B3 Binary UMDF Market Data Handler Benchmark sample, version " << Handler::version() << '.' << std::endl << std::endl;

    const Configuration configuration(qty, args);

    if (configuration.show())
    {
        configuration.show(std::cout);
        return 0;
    }

    try
    {
        HandlerSettings handlerSettings;

        handlerSettings.loadFeeds(configuration.channel(), configuration.connectivityFile());

        handlerSettings.networkInterfaceA = configuration.ifA();
        handlerSettings.networkInterfaceB = configuration.ifB();

        handlerSettings.licenseDirectory                           = "../../license";
        handlerSettings.loggerSettings.logDirectory                = "logs";
        handlerSettings.loggerSettings.logLevel                    = LogLevel::Disabled;
        handlerSettings.loggerSettings.logSettings                 = LogSettings::TraceToFile;

        const auto instruments = configuration.instruments();

        OrderBookPoolPtr orderBookPool;
        if (configuration.measureBookChanges())
        {
            OrderBookPoolSettings orderBookPoolSettings;
            orderBookPoolSettings.orderBooksAmount = instruments.size();

            orderBookPoolSettings.chunkLength = configuration.chunksLength();

            static constexpr auto oneMb = 1024 * 1024;
#ifndef _WIN32
            if(configuration.chunksLength() > oneMb)
                orderBookPoolSettings.preferHugePage = true;
#endif

            orderBookPoolSettings.chunksAmount =
                orderBookPoolSettings.chunkLength < oneMb ?
                    orderBookPoolSettings.orderBooksAmount * 4 :
                    orderBookPoolSettings.orderBooksAmount;

            orderBookPool = std::make_shared<OrderBookPool>(orderBookPoolSettings);
            handlerSettings.orderBookPool = orderBookPool.get();
            handlerSettings.buildOrderBooks = true;
        }

        System::ThisThread::affinity(1);

        MyListener myListener(configuration.packetsCount());

        LoggerSettings feLoggerSettings = handlerSettings.loggerSettings;

        feLoggerSettings.logFileNamePrefix += "_feedEngine";

#if ONIXS_USE_EF_VI
        #error "Please make sure the NIC time is synchronized with the host"
        SingleThreadedEfViFeedEngine feedEngine(feLoggerSettings, handlerSettings.networkInterfaceA);
#else
        checkNetworkSettings(configuration);
        SingleThreadedSocketFeedEngine feedEngine(feLoggerSettings);
#endif

        handlerSettings.feedEngine = &feedEngine;
        Handler handler(handlerSettings);

        for(auto instrumentId: instruments)
            handler.subscribe(instrumentId);

        handler.registerErrorListener(&myListener);
        handler.registerWarningListener(&myListener);
        handler.registerMessageListener(&myListener);

        if (configuration.measureBookChanges())
            handler.registerOrderBookListener(&myListener);

        std::clog << "Will start the Handler ..." << std::endl;

        handler.start();

        while(!InterruptDetector::instance().detected())
            run(feedEngine);

        std::clog << "Stopping..." << std::endl;

        handler.stop(true);

        std::clog << "The Handler has been stopped." << std::endl;

        /// Print statistics
        myListener.processLatencies();
    }
    catch(const std::exception& ex)
    {
        std::cerr << "EXCEPTION: " << ex.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "UNKNOWN EXCEPTION" << std::endl;
    }

    return 0;
}
//! [BenchmarkSample]
