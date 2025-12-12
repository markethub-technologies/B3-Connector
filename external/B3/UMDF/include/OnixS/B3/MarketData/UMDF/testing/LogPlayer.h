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

#include <limits>
#include <string>

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/Integral.h>

ONIXS_B3_UMDF_MD_TESTING_NAMESPACE_BEGIN

/// Identifies channel.
typedef UInt32 ChannelId;

struct FeedType {
    enum Enum
    {
        Unknown,

        Incremental,
        Instrument,
        Snapshot,
    };
};

/// LogPlayer's configuration settings.
ONIXS_B3_UMDF_MD_LTWT_CLASS LogPlayerSettings
{
public:
    /// Initializes parameters with default values.
    LogPlayerSettings()
    {
    }

    /// Cleans everything up.
    ~LogPlayerSettings() {}

    /// Path to the log file.
    const std::string& logFile() const
    {
        return logFile_;
    }

    /// Path to the log file.
    LogPlayerSettings& logFile(const std::string& file)
    {
        logFile_ = file;

        return *this;
    }

    /// Identifies CME market data channel.
    ChannelId channel() const
    {
        return channel_;
    }

    /// Identifies CME market data channel.
    LogPlayerSettings& channel(ChannelId value)
    {
        channel_ = value;
        return *this;
    }

    /// Path to the connectivity configuration file.
    const std::string& connectivityConfigurationFile() const
    {
        return configurationFile_;
    }

    /// Path to the connectivity configuration file from which
    /// to load feed connection settings.
    LogPlayerSettings& connectivityConfigurationFile(const std::string& configurationFile)
    {
        configurationFile_ = configurationFile;
    
        return *this;
    }

    /// Pause before sending data to the same source as it was sent before (in microseconds).
    unsigned sendDelay() const
    {
        return sendDelay_;
    }

    /// Pause before sending data to the same source as it was sent before (in microseconds).
    LogPlayerSettings& sendDelay(unsigned delay)
    {
        sendDelay_ = delay;

        return *this;
    }

    /// Use delays from the log file. If true, sendDelay will be ignored.
    bool useNaturalSendDelays() const
    {
        return useNaturalSendDelays_;
    }

    /// Use delays from the log file. If true, sendDelay will be ignored.
    LogPlayerSettings& useNaturalSendDelays(bool value)
    {
        useNaturalSendDelays_ = value;

        return *this;
    }

    /// Update the SendingTime field in the Binary Packet Header
    bool updateSendingTime() const
    {
        return updateSendingTime_;
    }

    /// Update the SendingTime field in the Binary Packet Header
    LogPlayerSettings& updateSendingTime(bool value)
    {
        updateSendingTime_ = value;

        return *this;
    }

    /// Pause before sending data to the source which differs from the source data was sent before (in microseconds).
    unsigned sourceSwitchDelay() const
    {
        return sourceSwitchDelay_;
    }

    /// Pause before sending data to the source which differs from the source data was sent before (in microseconds).
    LogPlayerSettings& sourceSwitchDelay(unsigned delay)
    {
        sourceSwitchDelay_ = delay;

        return *this;
    }

    /// Defines primary feed for the feed group. 
    const std::string& primaryFeed() const
    {
        return primaryFeed_;
    }

    /// Defines primary feed for the feed group.
    LogPlayerSettings& primaryFeed(const std::string& feed)
    {
        primaryFeed_ = feed;

        return *this;
    }

    /// Simulates arbitrage on realtime feeds. By default, data is sent through primary feed only. 
    bool simulateArbitrage() const
    {
        return simulateArbitrage_;
    }

    /// Simulates arbitrage on realtime feeds. By default, data is sent through primary feed only.
    LogPlayerSettings& simulateArbitrage(bool value)
    {
        simulateArbitrage_ = value;

        return *this;
    }

    /// Interface through which application must send data belonging to primary feed. If not specified, default network interface is used.
    const std::string& ifaceA() const
    {
        return ifaceA_;
    }

    /// Interface through which application must send data belonging to primary feed. If not specified, default network interface is used.
    LogPlayerSettings& ifaceA(const std::string& iface)
    {
        ifaceA_ = iface;

        return *this;
    }

    /// Interface through which application must send data belonging to secondary feed. If not specified, default network
    /// interface is used.
    const std::string& ifaceB() const
    {
        return ifaceA_;
    }

    /// Interface through which application must send data belonging to secondary feed. If not specified, default network
    /// interface is used.
    LogPlayerSettings& ifaceB(const std::string& iface)
    {
        ifaceA_ = iface;

        return *this;
    }

    /// The number of incremental packets to replay
    unsigned long packetsCount() const
    {
        return packetsCount_;
    }

    /// The number of incremental packets to replay
    LogPlayerSettings& packetsCount(unsigned long value)
    {
        packetsCount_ = value;

        return *this;
    }

private:
    std::string logFile_;
    ChannelId channel_ = 80;
    std::string configurationFile_;
    unsigned sendDelay_ = 100;
    bool useNaturalSendDelays_ = false;
    bool updateSendingTime_ = false;
    unsigned sourceSwitchDelay_ = 100000;
    std::string primaryFeed_ = "A";
    bool simulateArbitrage_ = false;
    std::string ifaceA_;
    std::string ifaceB_;
    unsigned long packetsCount_ = 0xffffffff;

};

struct ONIXS_B3_UMDF_MD_EXPORTED Interrupter
{
    /// Returns the Interrupter instance state.
    virtual bool activated() const = 0;
};

struct ONIXS_B3_UMDF_MD_EXPORTED PacketNotifier
{
    /// Returns the Interrupter instance state.
    virtual void onPacketProcessed(FeedType::Enum) const = 0;
};


class ONIXS_B3_UMDF_MD_EXPORTED LogPlayerStatistics
{
    size_t incrementalCounter_ = 0;
    size_t snapshotCounter_ = 0;
    size_t instrumentCounter_ = 0;

    size_t counter(FeedType::Enum type) const;
    
public:
    LogPlayerStatistics()
    {}

    void reset();

    void update(FeedType::Enum type);

    void dump(std::ostream& out) const;
};

inline std::ostream& operator<<(std::ostream& out, const LogPlayerStatistics& statistics)
{
    statistics.dump(out);

    return out;
}

/// Multicast Log Player.
class ONIXS_B3_UMDF_MD_EXPORTED LogPlayer
{
public:
    /// Initializes the instance according to the given settings.
    LogPlayer(){}

    const LogPlayerStatistics& statistics() const
    {
        return statistics_;
    }

    /// Starts playing of the log, until the interrupter is activated or the log is played totally.
    void
    run(const LogPlayerSettings& settings, const Interrupter* interrupter = nullptr, const PacketNotifier* packetNotifier = nullptr);

private:
    LogPlayerStatistics statistics_;
};

ONIXS_B3_UMDF_MD_TESTING_NAMESPACE_END
