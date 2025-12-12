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
#include <OnixS/B3/MarketData/UMDF/Time.h>

#include <string>
#include <ostream>
#include <memory>
#include <set>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                typedef char Char;

                struct NoCheck {};

                /// Alias for Packet Sequence Number type (PSN).
                typedef UInt32 PacketSequenceNumber;

                /// Data source
                struct ONIXS_B3_UMDF_MD_API DataSource
                {
                    DataSource() {}
                    DataSource(Timestamp ts) noexcept : packetReceptionTime(ts) {}

                    enum Origin : UInt8
                    {
                        Instrument,
                        Incremental,
                        Snapshot,
                    };

                    /// Time when the packet was received by Handler from UDP, in system ticks, @see Time.h
                    Timestamp packetReceptionTime;

                    /// UTC date and time of packet transmission, in nanoseconds since Unix epoch (Jan 1st., 1970), with microsecond-level precision*.
                    UInt64 sendingTime;

                    /// Packet Sequence Number. Always incremented by one in the same channel and same SequenceVersion.
                    PacketSequenceNumber packetSequenceNumber;

                    /// Packet Sequence Version.
                    /// For incremental stream, it starts with 1 at the rollout in the production
                    /// environment and incremented on weekly basis or in case of failover events.
                    /// For instrument definition and snapshot streams, its value changes for each new loop.
                    /// its value will be rolled back to 1 if incremented beyond 65534.
                    UInt16 packetSequenceVersion;

                    /// Channel identification.
                    UInt8 channelId;

                    /// Number of message in the packet
                    UInt8 packetMessageNumber;

                    /// Indicates if the message is the last in the packet
                    bool lastMessage;

                    /// the way data received
                    Origin origin;

                    /// The packet was cached due to incorrect sequence
                    bool cached;

                    std::string toString () const;
                };

                ONIXS_B3_UMDF_MD_API std::ostream& operator << (std::ostream& stream, const DataSource& ds);

                namespace System
                {
                    /// Zero-based index of CPU.
                    typedef size_t CpuIndex;

                    /// Represents set of CPU indices.
                    class ONIXS_B3_UMDF_MD_API ThreadAffinity
                    {
                        typedef std::set<CpuIndex> CpuIndexes;

                    public:
                        /// Initializes empty set.
                        ThreadAffinity();

                        /// Initializes as copy of other set.
                        ThreadAffinity(const ThreadAffinity&);

                        /// Utilizes all the resources.
                        ~ThreadAffinity();

                        /// Indicates whether is empty.
                        bool empty() const;

                        /// Copies set into another set.
                        void copyTo(CpuIndexes&) const;

                        /// Adds CPU index into set.
                        bool insert(CpuIndex index);

                        /// Removes CPU index from the set.
                        bool erase(CpuIndex index);

                        /// Makes set empty.
                        void clear();

                        /// Re-initializes instance as copy of other set.
                        ThreadAffinity& operator = (const ThreadAffinity&);

                        /// Returns the string representation.
                        std::string toString() const;

                    private:

                        /// System index.
                        CpuIndexes* indices_;
                    };
                }
            }
        }
    }
}
