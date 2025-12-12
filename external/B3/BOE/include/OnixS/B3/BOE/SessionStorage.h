#pragma once

/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable OnixS Software
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

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/Messaging.h>
#include <OnixS/B3/BOE/messaging/Integral.h>
#include <OnixS/B3/BOE/messaging/Time.h>
#include <OnixS/B3/BOE/messaging/NetworkMessage.h>

#include <string>
#include <vector>

namespace OnixS {
namespace B3 {
namespace BOE {

using namespace OnixS::B3::BOE::Messaging;

/// Session Storage Type.
struct SessionStorageType
{
    enum Enum
    {
        /// Undefined Session Storage.
        Undefined = 0,

        /// File-based Session Storage.
        FileBased,

        /// Asynchronous File-Based Session Storage.
        AsyncFileBased,

        /// Memory-based Session Storage.
        MemoryBased,

        /// Pluggable Session Storage
        Pluggable
    };

    ONIXS_B3_BOE_EXPORTED static Enum parse(const std::string &);

    /// \return the session storage type as a string.
    ONIXS_B3_BOE_EXPORTED static const char * toString(SessionStorageType::Enum);
};

/// Session's storage.
class ONIXS_B3_BOE_EXPORTED SessionStorage
{
public:
    /// Destructor.
    virtual ~SessionStorage() ONIXS_B3_BOE_DEFAULT;

    /// \return Storage Id.
    virtual const std::string & id() const = 0;

    /// \return Session Version Identification (sessionVerId).
    virtual UInt64 sessionVerId() const = 0;

    /// Sets Session Version Identification (sessionVerId).
    virtual void sessionVerId(UInt64 value) = 0;

    /// \return the expected sequence number of the next inbound message.
    virtual SeqNumber inSeqNum() const = 0;

    /// Sets the expected sequence number of the next inbound message.
    virtual void inSeqNum(SeqNumber msgSeqNum) = 0;

    /// \return the sequence number of the next outgoing message.
    virtual SeqNumber outSeqNum() const = 0;

    /// Sets the sequence number of the next outgoing message.
    virtual void outSeqNum(SeqNumber msgSeqNum) = 0;

    /// \return `true` if the session is negotiated (the Negotiation Response message has been received in reply to the Negotiation message);
    /// otherwise - `false`.
    virtual bool negotiated() const = 0;

    /// Sets the "negotiated" status.
    ///
    /// The session is negotiated when the Negotiation Response message has been received in reply to the Negotiation message.
    virtual void negotiated(bool negotiated) = 0;

    /// \return the session creation time.
    virtual Timestamp sessionCreationTime() const = 0;

    /// Sets the session creation time.
    virtual void sessionCreationTime(Timestamp) = 0;

    /// Closes the storage.
    virtual void close(bool doBackup = false) = 0;

    /// Logs the given inbound message.
    virtual void storeInboundMessage(const NetworkMessage& message, SeqNumber msgSeqNum, Timestamp messageReceivingUtcTimestamp = Timestamp()) = 0;

    /// Logs the given outgoing message.
    virtual void storeOutboundMessage(const NetworkMessage& message, SeqNumber msgSeqNum, Timestamp messageSendingUtcTimestamp = Timestamp()) = 0;

    /// Flushes all internal buffers.
    virtual void flush() = 0;

    /// Warmup the storage.
    virtual void warmup(size_t messageSize, Timestamp ts = Timestamp()) = 0;
};

}
}
}
