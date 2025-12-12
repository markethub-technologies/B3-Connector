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

//! [GettingStartedSample]
#include <iostream>

#include <Common/Configuring.h>
#include <Common/Options.h>
#include <Common/Utils.h>

#include <OnixS/B3/MarketData/UMDF.h>

#include "MyListener.h"


using namespace OnixS::B3::MarketData::UMDF;
using Sample::MyListener;

/// Wait until the user presses the button
void waitUntilEnterKey ()
{
    std::string tmp;
    std::getline (std::cin, tmp);
}

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

private:
    void showOptions(std::ostream& out) const ONIXS_B3_UMDF_MD_OVERRIDE
    {
        ChannelConfiguration::showOptions(out);
        ConnectivityConfiguration::showOptions(out);
        FeedConfiguration::showOptions(out);
    }
};

/// The main entry point.
int main (int qty, char** args)
{
    std::clog << "OnixS C++ B3 Binary UMDF Market Data Handler Getting Started sample, version " << Handler::version() << '.' << std::endl << std::endl;

    const Configuration configuration(qty, args);

    if (configuration.show())
    {
        configuration.show(std::cout);
        return 0;
    }

    checkNetworkSettings(configuration);

    HandlerSettings handlerSettings;

    handlerSettings.licenseDirectory                           = "../../license";
    handlerSettings.loggerSettings.logDirectory                = "logs";
    handlerSettings.loggerSettings.logLevel                    = LogLevel::Debug;
    handlerSettings.buildOrderBooks = true;

    handlerSettings.loadFeeds(configuration.channel(), configuration.connectivityFile());

    handlerSettings.networkInterfaceA = configuration.ifA();
    handlerSettings.networkInterfaceB = configuration.ifB();

    try
    {
        MyListener myListener;

        Handler handler(handlerSettings);

        handler.registerWarningListener(&myListener);
        handler.registerErrorListener (&myListener);
        handler.registerMessageListener (&myListener);

        std::clog << "Will start the Handler ..." << std::endl;

        try
        {
            handler.start();
        }
        catch (const std::exception& ex)
        {
            std::clog << "Unable to start the handler: " << ex.what() << std::endl;
        }
        catch (...)
        {
            std::clog << "Unable to start the handler" << std::endl;
        }

        std::clog << "Please press Enter key to stop the handler..." << std::endl;

        waitUntilEnterKey ();

        std::clog << "Stopping..." << std::endl;

        handler.stop (true);

        std::clog << "The Handler has been stopped." << std::endl;
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

    std::clog << "Press Enter key to close application..." << std::endl;

    waitUntilEnterKey();

    return 0;
}
//! [GettingStartedSample]
