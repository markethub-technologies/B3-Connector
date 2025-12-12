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

#include "OnixS/B3/MarketData/UMDF/Handler.h"
#include "OnixS/B3/MarketData/UMDF/testing/LogPlayer.h"

#include <Common/Common.h>
#include <Common/Configuring.h>

//! [LogPlayerSample]

using namespace OnixS::B3::MarketData::UMDF;
using namespace OnixS::B3::MarketData::UMDF::Testing;

// Options.

class Configuration
    : public ChannelConfiguration
    , public ConnectivityConfiguration
{
public:
    Configuration(size_t qty, char** args)
        : ConfigurationBase(qty, args)
        , ChannelConfiguration(qty, args, 310)
        , ConnectivityConfiguration(qty, args)
    {
    }

    std::string logFile() const
    {
        return requiredArg<std::string>(options(), "log");
    }

    std::string ifA() const
    {
        return argOrDefault(options(), "ifA", NETWORK_INTERFACE_FOR_FEEDS_A);
    }

    std::string ifB() const
    {
        return argOrDefault(options(), "ifB", NETWORK_INTERFACE_FOR_FEEDS_B);
    }

    UInt32 sendDelay() const
    {
        return argOrDefault(options(), "sendDelay", 100);
    }

    bool useNaturalSendDelays() const
    {
        return exist(options(), "useNaturalSendDelays");
    }

    UInt32 sourceSwitchDelay() const
    {
        return argOrDefault(options(), "sourceSwitchDelay", 100000);
    }

    UInt32 packetsCount() const
    {
        return argOrDefault(options(), "packetsCount", 10000);
    }

    bool updateSendingTime() const
    {
        return exist(options(), "updateSendingTime");
    }

private:

    void showOptions(std::ostream& out) const ONIXS_B3_UMDF_MD_OVERRIDE
    {
        out << "  --log <file>" << std::endl
            << "\tTells to use the given log file. " << std::endl
            << std::endl;

        ChannelConfiguration::showOptions(out);
        ConnectivityConfiguration::showOptions(out);

        out << "  --ifA <interface>" << std::endl
            << "\tSpecifies a network interface for primary feeds. " << std::endl
            << std::endl
            << "  --ifB <interface>" << std::endl
            << "\tSpecifies a network interface for secondary feeds. " << std::endl
            << std::endl
            << "  --sendDelay <number>" << std::endl
            << "\tDefines the pause before sending data to the same source as it was sent before (in microseconds). " << std::endl
            << std::endl
            << "  --useNaturalSendDelays" << std::endl
            << "\tUse delays from the log file. If true, sendDelay will be ignored. " << std::endl
            << std::endl
            << "  --sourceSwitchDelay <number>" << std::endl
            << "\tDefines the pause before sending data to the source which differs from the source data was sent before (in microseconds). " << std::endl
            << std::endl
            << "  --packetsCount <number>" << std::endl
            << "\tDefines the number of incremental packets to play. " << std::endl
            << std::endl
            << "  --updateSendingTime" << std::endl
            << "\tUpdate the SendingTime field in the Binary Packet Header. " << std::endl
            << std::endl;
    }
};

struct LogPlayerInterrupter
    : Interrupter
{
    bool activated_;

    LogPlayerInterrupter()
        : activated_(false)
    {
        signal(SIGINT, &LogPlayerInterrupter::signalHandler);
    }

    ~LogPlayerInterrupter() {}

    static void signalHandler(int signal)
    {
        if (SIGINT == signal)
        {
            instance().activated_ = true;
        }
    }

public:
    bool activated() const override
    {
        return activated_;
    }

    static LogPlayerInterrupter& instance()
    {
        static LogPlayerInterrupter interrupter;

        return interrupter;
    }
};

struct CoutPacketNotifier : PacketNotifier
{
    void onPacketProcessed(FeedType::Enum type) const override
    {
        switch (type)
        {
        case FeedType::Incremental:
            std::cout << 'I';
            break;

        case FeedType::Instrument:
            std::cout << 'N';
            break;

        case FeedType::Snapshot:
            std::cout << 'S';
            break;

        default:
            break;
        }

        std::cout << std::flush;
    }
};

int main(int qty, char** args)
{
    try
    {
        std::cout << "Log Player for the B3 Binary UMDF Market Data Handler, version " << Handler::version() << ". "
                  << std::endl
                  << std::endl;

        const Configuration configuration(qty, args);

        if (configuration.show())
        {
            configuration.show(std::cout);
        }
        else
        {
            // Configures log player.
            LogPlayerSettings settings;

            settings.logFile(configuration.logFile())
                .channel(configuration.channel())
                .connectivityConfigurationFile(configuration.connectivityFile())
                .ifaceA(configuration.ifA())
                .ifaceB(configuration.ifA())
                .sendDelay(configuration.sendDelay())
                .useNaturalSendDelays(configuration.useNaturalSendDelays())
                .sourceSwitchDelay(configuration.sourceSwitchDelay())
                .packetsCount(configuration.packetsCount())
                .updateSendingTime(configuration.updateSendingTime());

            LogPlayer logPlayer;

            CoutPacketNotifier packetNotifier;

            logPlayer.run(settings, &LogPlayerInterrupter::instance(), &packetNotifier);
        }

        return 0;
    }
    catch (const std::exception& ex)
    {
        std::cerr << std::endl << "ERROR: " << ex.what() << std::endl;

        return 1;
    }
}

//! [LogPlayerSample]
