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

//! [AllChannelsSample]
#include <iostream>

#include <Common/Configuring.h>
#include <Common/Options.h>
#include <Common/Utils.h>
#include <Common/Helpers.h>

#include <OnixS/B3/MarketData/UMDF.h>

#include "MyListener.h"


using namespace OnixS::B3::MarketData::UMDF;
using namespace OnixS::B3::MarketData::UMDF::Messaging;
using Sample::MyListener;

/////////////////////////////////////////////////////////////////////////////
typedef std::shared_ptr<Handler> HandlerPtr;
typedef std::shared_ptr<OrderBookPool> OrderBookPoolPtr;
typedef std::vector<HandlerPtr> Handlers;

void stopAndDeleteHandlers(Handlers& handlers)
{
    for (auto& handler : handlers)
        handler->stop(true);
    handlers.clear();
}

// Handles sample input parameters.
class Configuration
    : public ConnectivityConfiguration
    , public FeedConfiguration
{
public:
    Configuration(size_t qty, Char** args)
        : ConfigurationBase(qty, args)
        , ConnectivityConfiguration(qty, args)
        , FeedConfiguration(qty, args)
    {
    }

    bool buildBooks() const
    {
        return exist(options(), "buildBooks");
    }

    std::string logDir() const
    {
        return argOrDefault(options(), "logDir", "logs");
    }

private:
    void showOptions(std::ostream& out) const ONIXS_B3_UMDF_MD_OVERRIDE
    {
        ConnectivityConfiguration::showOptions(out);
        FeedConfiguration::showOptions(out);

        out << "  --buildBooks" << std::endl
            << "\tBuild order books. " << std::endl
            << std::endl;

        out << "  --logDir <directory>" << std::endl
            << "\tTells to use the given log directory. " << std::endl
            << std::endl;
    }
};

/// The main entry point.
int main(int qty, char** args)
{
    std::clog << "OnixS C++ B3 Binary UMDF Market Data Handler All Channels sample, version " << Handler::version() << '.' << std::endl << std::endl;

    try
    {
        manageLinuxSignals();

        const Configuration configuration(qty, args);

        if (configuration.show())
        {
            configuration.show(std::cout);
            return 0;
        }

        checkNetworkSettings(configuration);

        std::vector<int> channelIds;
        HandlerSettings::gatherChannelIds(channelIds, configuration.connectivityFile());

        HandlerSettings handlerSettings;

        handlerSettings.licenseDirectory = "../../license";
        handlerSettings.loggerSettings.logDirectory = configuration.logDir();
        handlerSettings.loggerSettings.logLevel = LogLevel::Info;

        handlerSettings.networkInterfaceA = configuration.ifA();
        handlerSettings.networkInterfaceB = configuration.ifB();

        SocketFeedEngine feedEngine;
        FeedEngineThreadPoolSettings feedEngineThreadPoolSettings;
        feedEngineThreadPoolSettings.threadCount( static_cast<UInt32>(channelIds.size()) / 2 + 1 );
        FeedEngineThreadPool pool(feedEngineThreadPoolSettings, &feedEngine);
        handlerSettings.feedEngine = &feedEngine;

        OrderBookPoolPtr orderBookPool;
        if(configuration.buildBooks())
        {
            OrderBookPoolSettings orderBookPoolSettings;
            orderBookPoolSettings.chunksAmount = channelIds.size() * 1000;
            orderBookPoolSettings.chunkLength = 128 * 1024;
            orderBookPool = std::make_shared<OrderBookPool>(orderBookPoolSettings);
            handlerSettings.orderBookPool = orderBookPool.get();
            handlerSettings.buildOrderBooks = true;
        }

        MyListener myListener;

        Handlers handlers;
        for (const int& channelId : channelIds)
        {
            handlerSettings.loggerSettings.logFileNamePrefix = "channel_" + toStr(channelId);
            handlerSettings.loadFeeds(channelId, configuration.connectivityFile());

            auto handler = std::make_shared<Handler>(handlerSettings);

            handler->registerErrorListener(&myListener);
            handler->registerMessageListener(&myListener);
            handler->registerWarningListener(&myListener);
            handler->registerOrderBookListener(&myListener);

            handlers.push_back(handler);

            handler->start();
        }

#ifdef _WIN32
        std::clog << "Press Enter key to to stop the handlers..." << std::endl;
        waitUntilEnterKey();
#else
        std::clog << "Send SIGINT to to stop the handlers..." << std::endl;
        SignalHelper::waitUntilSignal();
#endif

        std::clog << "Stopping..." << std::endl;

        stopAndDeleteHandlers(handlers);

        std::clog << "Handlers are stopped." << std::endl;
    }
    catch (const Exception& ex)
    {
        std::cerr << "EXCEPTION: " << ex.what() << std::endl;
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
//! [AllChannelsSample]
