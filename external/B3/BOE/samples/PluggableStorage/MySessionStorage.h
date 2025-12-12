
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
#pragma once

//! [PluggableStorageSampleMySessionStorageH]

#include <OnixS/B3/BOE/SessionStorage.h>

#include <vector>
#include <list>

namespace Samples
{

using namespace OnixS::B3::BOE;
using namespace OnixS::B3::BOE::Messaging;

class MySessionStorage : public SessionStorage
{
public:
    MySessionStorage();

    UInt64 sessionVerId() const ONIXS_B3_BOE_OVERRIDE;

    void sessionVerId(UInt64 value) ONIXS_B3_BOE_OVERRIDE;

    const std::string & id() const ONIXS_B3_BOE_OVERRIDE;

    SeqNumber inSeqNum() const ONIXS_B3_BOE_OVERRIDE;

    void inSeqNum(SeqNumber msgSeqNum) ONIXS_B3_BOE_OVERRIDE;

    SeqNumber outSeqNum() const ONIXS_B3_BOE_OVERRIDE;

    void outSeqNum(SeqNumber msgSeqNum) ONIXS_B3_BOE_OVERRIDE;

    bool negotiated() const ONIXS_B3_BOE_OVERRIDE;

    void negotiated(bool status) ONIXS_B3_BOE_OVERRIDE;

    Timestamp sessionCreationTime() const ONIXS_B3_BOE_OVERRIDE;

    void sessionCreationTime(Timestamp) ONIXS_B3_BOE_OVERRIDE;

    void close(bool doBackup = false) ONIXS_B3_BOE_OVERRIDE;

    void storeInboundMessage(const NetworkMessage& message, SeqNumber msgSeqNum, Timestamp messageReceivingUtcTimestamp = Timestamp()) ONIXS_B3_BOE_OVERRIDE;

    void storeOutboundMessage(const NetworkMessage& message, SeqNumber msgSeqNum, Timestamp messageSendingUtcTimestamp = Timestamp()) ONIXS_B3_BOE_OVERRIDE;

    void flush() ONIXS_B3_BOE_OVERRIDE;

    void warmup(size_t, Timestamp) ONIXS_B3_BOE_OVERRIDE;

    typedef std::vector<char> Message;
    typedef std::list<Message> Messages;

private:
    SeqNumber inSeqNum_;
    SeqNumber outSeqNum_;
    std::string id_;
    bool negotiated_;
    Timestamp sessionCreationTime_;
    UInt64 sessionVerId_;
    Messages inboundMessages_;
    Messages outboundMessages_;
};

}
//! [PluggableStorageSampleMySessionStorageH]
