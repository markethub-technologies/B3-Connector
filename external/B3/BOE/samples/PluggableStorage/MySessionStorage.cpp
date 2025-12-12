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

#include "stdafx.h"

//! [PluggableStorageSampleMySessionStorageCpp]
#include "MySessionStorage.h"

#include "../Common/Helpers.h"
#include "../Common/Listener.h"

namespace Samples
{

namespace
{
    const char* begin(const NetworkMessage& message) ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<const char*>(message.data());
    }

    const char* end(const NetworkMessage& message) ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<const char*>(advanceByBytes(message.data(), message.size()));
    }

    void storeMessage(MySessionStorage::Messages & storage, const NetworkMessage& message)
    {
        storage.push_back(MySessionStorage::Message(begin(message), end(message)));

        if (!processTypified(message.message(), MessagePrinter()))
            throw runtime_error("Unknown message type");
    }
}

MySessionStorage::MySessionStorage()
    : inSeqNum_(1)
    , outSeqNum_(1)
    , id_(IdGenerator::newStrId())
    , negotiated_(false)
    , sessionCreationTime_()
    , sessionVerId_(Session::UndefinedSessionVerID)
{}

UInt64 MySessionStorage::sessionVerId() const
{
    return sessionVerId_;
}

void MySessionStorage::sessionVerId(UInt64 value)
{
    std::clog << "\nSet sessionVerId to " << value << ".\n";
    sessionVerId_ = value;
}

void MySessionStorage::close(bool doBackup)
{
    std::clog << "\nClose the session storage (doBackup=" << doBackup <<  ").\n";

    inSeqNum_ = 1;
    outSeqNum_ = 1;
    negotiated_ = false;
    inboundMessages_.clear();
    outboundMessages_.clear();
    sessionVerId_ = Session::UndefinedSessionVerID;
}

const std::string & MySessionStorage::id() const
{
    return id_;
}

SeqNumber MySessionStorage::inSeqNum() const
{
    return inSeqNum_;
}

void MySessionStorage::inSeqNum(SeqNumber msgSeqNum)
{
    std::clog << "\nSet inSeqNum to " << msgSeqNum << ".\n";
    inSeqNum_ = msgSeqNum;
}

SeqNumber MySessionStorage::outSeqNum() const
{
    return outSeqNum_;
}

void MySessionStorage::outSeqNum(SeqNumber msgSeqNum)
{
    std::clog << "\nSet outSeqNum to " << msgSeqNum << ".\n";
    outSeqNum_ = msgSeqNum;
}

bool MySessionStorage::negotiated() const
{
    return negotiated_;
}

void MySessionStorage::negotiated(bool status)
{
    std::clog << "\nSet negotiated to " << std::boolalpha << status << std::noboolalpha << ".\n";
    negotiated_ = status;
}

Timestamp MySessionStorage::sessionCreationTime() const
{
    return sessionCreationTime_;
}

void MySessionStorage::sessionCreationTime(Timestamp time)
{
    std::clog << "\nSet sessionCreationTime to " << time << "\n";
    sessionCreationTime_ = time;
}

void MySessionStorage::storeInboundMessage(const NetworkMessage& message, SeqNumber msgSeqNum, Timestamp)
{
    std::clog << "\nStore inbound message:\n";
    storeMessage(inboundMessages_, message);

    inSeqNum_ = msgSeqNum;
}

void MySessionStorage::storeOutboundMessage(const NetworkMessage& message, SeqNumber msgSeqNum, Timestamp)
{
    std::clog << "\nStore outbound message:\n";
    storeMessage(outboundMessages_, message);

    outSeqNum_ = msgSeqNum;
}

void MySessionStorage::flush()
{
}

void MySessionStorage::warmup(size_t, Timestamp)
{
}

}
//! [PluggableStorageSampleMySessionStorageCpp]
