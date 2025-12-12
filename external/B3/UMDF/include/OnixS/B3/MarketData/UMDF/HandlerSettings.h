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

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/Defines.h>
#include <OnixS/B3/MarketData/UMDF/LogSettings.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Fields.h>

#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <limits>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                class FeedEngine;

                /// A feed-related settings.
                struct Feed
                {
                    Feed() {}

                    ///
                    Feed(const std::string& addr, unsigned int port, const std::string& nif = "", FeedEngine* fe = nullptr)
                        : address(addr)
                        , port(port)
                        , networkInterface(nif)
                        , feedEngine(fe)
                    {}

                    /// IP address
                    std::string address;

                    /// Port number
                    unsigned port = 0;

                    /// Specifies one or more network interfaces to use while joining the multicast group;
                    /// use semi-colon delimited list if more than one.
                    /// This value overrides the default one.
                    std::string networkInterface;

                    /// Feed engine to use on feed.
                    /// This value overrides the default one.
                    FeedEngine* feedEngine = nullptr;

                    /// Returns true if the descriptor points to valid ip address
                    bool valid() const
                    {
                        return !address.empty() && port > 0;
                    }
                };

                ONIXS_B3_UMDF_MD_API std::ostream& operator<<(std::ostream& stream, const Feed& descriptor);

                /// Group of feeds by role
                struct FeedGroup
                {
                    /// Feed descriptor.
                    Feed a;

                    /// Feed descriptor.
                    Feed b;
                };

                ONIXS_B3_UMDF_MD_API std::ostream& operator<<(std::ostream& stream, const FeedGroup& descriptor);

                struct HandlerSettings;

                ONIXS_B3_UMDF_MD_API std::ostream& operator<<(std::ostream& stream, const HandlerSettings& settings);

                class OrderBookPool;

                /// Handler configuration settings.
                struct ONIXS_B3_UMDF_MD_API HandlerSettings
                {
                    /// Logger settings.
                    LoggerSettings loggerSettings;

                    /// License string.
                    std::string licenseString;

                    /// Path to the license directory.
                    std::string licenseDirectory;

                    /// Feed engine.
                    FeedEngine* feedEngine = nullptr;

                    /**
                    * Specifies one or more network interfaces to use while joining the multicast group; use semi-colon delimited list if more than one.
                    *
                    * On Linux, the network interface is specified by its name, on Windows - by IP address.
                    *
                    * @note If the value is empty or absent, then the default networking interface is used.
                    */
                    std::string networkInterface;

                    /**
                    * Specifies one or more network interfaces to use while joining the multicast group A; use semi-colon delimited list if more than one.
                    *
                    * On Linux, the network interface is specified by its name, on Windows - by IP address.
                    *
                    * @note If the value is empty or absent, then the networkInterface_ filled value is used.
                    */
                    std::string networkInterfaceA;

                    /**
                    * Specifies one or more network interfaces to use while joining the multicast group B; use semi-colon delimited list if more than one.
                    *
                    * On Linux, the network interface is specified by its name, on Windows - by IP address.
                    *
                    * @note If the value is empty or absent, then the networkInterface_ filled value is used.
                    */
                    std::string networkInterfaceB;

                    /// Specifies maximal time interval between two
                    /// network packets. If no data is received during
                    /// specified time frame, corresponding warning is raised.
                    ///
                    /// Interval is measured in seconds.
                    UInt32 heartbeatInterval = 3;

                    /// Defines value of threshold used by Handler to differ
                    /// out-of-order packets from gaps.
                    ///
                    /// Due to the unreliable nature of multicast, packets transmitted by exchange
                    /// may be received in an order different to original. To differ the
                    /// case when Handler received out-of-order packets from the case when
                    /// some of packets were completely lost, the Handler uses the given parameter.
                    /// It defines the size of the interval for incoming packets starting from the
                    /// last received. A packet is considered as out-of-order if its sequence
                    /// number fits into interval [seqNumberOfLastReceivedPacket,
                    /// seqNumberOfLastReceivedPacket + outOfOrderPacketsMaxInterval].
                    /// In that case, Handler waits for other packets to fulfill the incoming
                    /// sequence. If the received packet has a greater sequence number than
                    /// 'seqNumberOfLastReceivedPacket + outOfOrderPacketsMaxInterval',
                    /// then Handler makes a decision on packets lost and gap is reported.
                    ///
                    /// @note When out-of-order packet is received, Handler makes a decision
                    /// on data loss if either waiting time is over or if newly received packet
                    /// has sequence number greater than 'seqNumberOfLastReceivedPacket +
                    /// outOfOrderPacketMaxInterval'.
                    ///
                    /// @see 'lostPacketWaitTime' parameter for more information.
                    UInt32 outOfOrderPacketMaxInterval = 3;

                    /// Indicates for how long Handler should wait for
                    /// the packet before it's considered as totally lost.
                    ///
                    /// Due to the unreliable nature of multicast, data transmitted by MDP
                    /// may come in order other than original or be completely lost. When
                    /// Handler receives packet with sequence number greater than expected,
                    /// it considers received data as out-of-order. If for a certain time
                    /// interval Handler receives missing data, Handler resumes normal data
                    /// processing. However, if no data is received for the predefined time frame,
                    /// Handler considers missing data as lost and raises packet gap event.
                    /// Given parameter defines size of time interval Handler waits for missing
                    /// data.
                    ///
                    /// @note When an out-of-order packet is received, the Handler makes a decision
                    /// on data loss if either waiting time is over or if newly received packet
                    /// has sequence number greater than 'seqNumberOfLastReceivedPacket +
                    /// outOfOrderPacketMaxInterval'.
                    ///
                    /// @see 'outOfOrderPacketMaxInterval' parameter for more information.
                    ///
                    /// Time interval is measured in microseconds (uSec).
                    UInt32 lostPacketWaitTime = 100000;

                    /// Instrument definition multicast feeds
                    FeedGroup instrumentFeeds;

                    /// Incremental multicast feeds
                    FeedGroup incrementalFeeds;

                    /// Snapshot recovery multicast feeds
                    FeedGroup snapshotFeeds;

                    /// Build order books.
                    bool buildOrderBooks = false;

                    /// A shared pool for building books.
                    /// @note If not set, it is created internally for each handler.
                    OrderBookPool* orderBookPool = nullptr;

                    /// Max depth of the order book
                    static constexpr size_t FullOrderBookDepth = std::numeric_limits<UInt32>::max();

                    /// Exposed depth of the order books
                    size_t orderBookDepth = FullOrderBookDepth;

                    /// Start incremental feeds after instrument recovery.
                    ///
                    /// By default incremental feeds will be started before instrument feed on
                    /// the handler starting.
                    bool startIncrementalFeedsAfterInstrumentRecovery = false;

                    /// Discard queued incremental packets included in snapshots.
                    bool discardQueuedIncrementalPacketsIncludedInSnapshots = false;

                    /// Max incremental queue size
                    size_t incrementalQueueSize = 50000;

                    /// Returns the string representation.
                    std::string toString() const
                    {
                        std::ostringstream out;
                        out << *this;
                        return out.str();
                    }

                    /// Loads channel feed settings from the given channel configuration file.
                    HandlerSettings& loadFeeds(int channelId, const std::string& channelConfigFile);

                    /// Gathers channel ids from the given channel configuration file.
                    static void gatherChannelIds(std::vector<int>& channelIds, const std::string& channelConfigFile);
                };
            }
        }
    }
}
