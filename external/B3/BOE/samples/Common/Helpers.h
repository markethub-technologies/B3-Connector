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

//! [Helpers]

#include <OnixS/B3/BOE/B3BOE.h>

#include "../Settings/Defaults.h"

#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <fstream>

#ifdef _WIN32
#include <conio.h>
#else
#include <pthread.h>
#include <csignal>
#include <cstdlib>
#include <vector>
#include <sys/poll.h>
#endif

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
#include <thread>
#include <future>
#include <functional>
#include <chrono>
#endif

namespace Samples
{
using namespace OnixS::B3::BOE::Messaging;

typedef MessageHolder<NewOrderSingle102> NewOrderSingle;
typedef MessageHolder<OrderCancelReplaceRequest104> OrderCancelReplaceRequest;
typedef MessageHolder<OrderCancelRequest105> OrderCancelRequest;
typedef MessageHolder<OrderMassActionRequest701> OrderMassActionRequest;
typedef MessageHolder<QuoteRequest401> RequestForQuote;
typedef MessageHolder<SecurityDefinitionRequest300> SecurityDefinitionRequest;
typedef MessageHolder<NewOrderCross106> NewOrderCross;

class Helper
{
public:
    static void setOrderFields(NewOrderSingle & order, MarketSegmentID marketSegmentId, SecurityID securityId, Messaging::Account account, Int64 priceMantissa) ONIXS_B3_BOE_NOTHROW
    {
        InboundBusinessHeader & header = order->businessHeader();
        header.setMarketSegmentId(marketSegmentId);

        order->setOrdTagId(100)
            .setMmProtectionReset(Boolean::FalseValue)
            .setClOrdId(1)
            .setAccount(account)
            .setSenderLocation("DMA")
            .setEnteringTrader("TADA")
            .setSelfTradePreventionInstruction(SelfTradePreventionInstruction::None)
            .setSecurityId(securityId)
            .setSide(Side::Buy)
            .setOrdType(OrdType::Limit)
            .setTimeInForce(TimeInForce::Day)
            .setRoutingInstructionToNull()
            .setOrderQty(100)
            .setPrice(PriceOptional(priceMantissa))
            .setInvestorIdToNull()
            .setMemo("VALE3 1714479423613")
            .setDeskId("1");

        InvestorID iid;
        iid.setPrefix(300);
        iid.setDocument(123456);
        order->setInvestorId(iid);
    }

    static void waitUntilEnterKey(const std::string& message)
    {
        std::clog << "\nPress the ENTER key to " << message << ".." << std::endl;

#ifdef _WIN32
        _getch();
#else
        getchar();
#endif
    }

    static bool keyPressed()
    {
#ifdef __linux__
        pollfd pfd = { 0, POLLIN, 0 };
        return poll(&pfd, 1, 0) != 0;
#else
        return _kbhit() != 0;
#endif
    }
};

template <typename T>
T fromStr(const std::string & s)
{
    std::istringstream ss(s);
    T result = T();
    ss >> result;
    return result;
}

class IdGenerator
{
public:

    static std::string newStrId()
    {
        static UInt64 idCounter = 0;

        const size_t startOfTime = 9;

        std::string timestamp = toStr(UtcWatch::now(), TimestampFormat::YYYYMMDDHHMMSSmsec).substr(startOfTime);

        std::string id;

        id += timestamp[0];
        id += timestamp[1];
        id += timestamp[3];
        id += timestamp[4];
        id += timestamp[6];
        id += timestamp[7];
        id += timestamp[9];
        id += timestamp[10];

        id += toStr(++idCounter);

        return id;
    }

    static UInt64 newId()
    {
        return UtcWatch::now().time().nanoseconds();
    }
};

#ifndef _WIN32

// The code below illustrates how to manage signals:
// - Mask signals in all threads;
// - Start a separate thread to catch signals;
class SignalHelper
{
public:

    typedef std::vector<int> SuppressedSignals;

    static void manageLinuxSignals()
    {
        SuppressedSignals suppressedSignals;

        // Add signals we are waiting for.
        suppressedSignals.push_back(SIGPIPE);

        pthread_t signalThreadId;
        int status;

        // Mask signals in the primary thread.
        // Child threads will inherit this signal mask.
        sigemptyset(&signalSet());

        for (SuppressedSignals::const_iterator i = suppressedSignals.begin(),
            e = suppressedSignals.end();
            i != e; ++i)
            sigaddset(&signalSet(), *i);

        status = pthread_sigmask(SIG_BLOCK, &signalSet(), ONIXS_B3_BOE_NULLPTR);

        if (status != 0)
            errorAbort(status, "Set signal mask");

        // Create the sigwait thread.
        status = pthread_create(&signalThreadId, ONIXS_B3_BOE_NULLPTR, signalWaiter, ONIXS_B3_BOE_NULLPTR);

        if (status != 0)
            errorAbort(status, "Create signalWaiter");
    }

private:

    static void errorAbort(int status, const char* reason)
    {
        printf("Aborted due to status %d: %s\n", status, reason ? reason : "no error message");
        exit(1);
    }

    ONIXS_B3_BOE_NORETURN
    static void* signalWaiter(void* /*arg*/)
    {
        int signalNumber;

        while (true)
        {
            sigwait(&signalSet(), &signalNumber);
            printf("Signal %d received and suppressed.\n", signalNumber);
        }
    }

    static sigset_t& signalSet()
    {
        static sigset_t set;
        return set;
    }
};
#else
struct SignalHelper
{
    static void manageLinuxSignals(){}
};
#endif

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)

class GatewayListener : public Testing::ClientMessageListener
{
public:

    void onNewOrderSingle(const NewOrderSingle102& order, Testing::Gateway* gateway) override
    {
        updateReport(order);

        gateway->send(report_, ++reportsCounter_);
        gateway->outSeqNum(reportsCounter_ + 1);
    }


protected:

    void updateReport(const NewOrderSingle102& order)
    {
        OutboundBusinessHeader & header = report_->businessHeader();
        EventIndicator eventIndicator = header.eventIndicator();
        eventIndicator.setPossResend(false);
        header.setEventIndicator(eventIndicator);
        header.setSessionId(order.businessHeader().sessionId());

        OutboundBusinessHeader::SendingTime sendingTime;
        sendingTime.setTime(UtcWatch::now().sinceEpoch());
        header.setSendingTime(sendingTime);

        report_->setOrdTagId(1)
            .setMmProtectionResetToNull()
            .setClOrdId(1714479417808)
            .setAccount(1529)
            .setSecurityId(200000163669)
            .setSide(Side::Buy)
            .setOrdType(OrdType::Limit)
            .setTimeInForce(order.timeInForce())
            .setOrderQty(100)
            .setPrice(PriceOptional(200000))
            .setInvestorIdToNull()
            .setMemo("VALE3 1714479416336")
            .setExecId(800422000000001091)
            .setTransactTime(UTCTimestampNanos(1714479417836000000))
            .setOrdStatus(OrdStatus::New)
            .setSecondaryOrderId(804604488)
            .setOrderId(8047407153)
            .setTradeDate(Timestamp::fromStr("20240430-00:00:00.000000000", TimestampFormat::YYYYMMDDHHMMSSnsec))
            .setWorkingIndicator(Boolean::FalseValue);

        PriceOptional price;
        if (order.price(price))
            report_->setPrice(price);
        else
            report_->setPrice(PriceOptional(DefaultPriceMantissa));
    }

    MessageHolder<ExecutionReportNew200> report_;
    UInt32 reportsCounter_{ 0 };
};

class GatewayEmulatorThread
{
public:
    GatewayEmulatorThread(const SessionSettings::LicenseStores& licenseStores, const std::string & host, Port port, Testing::ClientMessageListener * clientMessageListener = nullptr,
        const std::chrono::seconds& acceptTimeout = std::chrono::seconds(10), const std::chrono::seconds& sendReceiveTimeout = std::chrono::seconds(10))
        : gateway_(licenseStores, port, host.c_str(), acceptTimeout, sendReceiveTimeout)
        , clientMessageListener_(clientMessageListener)
    {
        std::promise<void> emulatorTaskPromise;
        emulatorTaskDone_ = emulatorTaskPromise.get_future();

        std::thread(
            std::bind(
                [&](std::promise<void>& p)
                {
                    try
                    {
                        if(clientMessageListener_)
                        {
                            gateway_.run(*clientMessageListener_);
                        }
                        else
                        {
                            GatewayListener clientMessageListener;
                            gateway_.run(clientMessageListener);
                        }
                        p.set_value();
                    }
                    catch (const std::exception& ex)
                    {
                        std::cerr << "Exception in Emulator's thread: " << ex.what() << '.' << std::endl;

                        p.set_exception(
                            std::current_exception());
                    }
                    catch (...)
                    {
                        std::cerr << "UNKNOWN Exception in Emulator's thread." << std::endl;

                        p.set_exception(
                            std::current_exception());
                    }
                },
                std::move(emulatorTaskPromise)))
            .detach();
    }

    ~GatewayEmulatorThread()
    {
        if(emulatorTaskDone_.valid())
            emulatorTaskDone_.wait_for(std::chrono::seconds(10));
    }

    void wait(std::chrono::seconds timeout = std::chrono::seconds(10)) {
        if(emulatorTaskDone_.valid()) {
            std::future<void> f = std::move(emulatorTaskDone_);
            f.wait_for(timeout);
            f.get();
        }
    }

private:

    Testing::Gateway gateway_;
    Testing::ClientMessageListener * clientMessageListener_;
    std::future<void> emulatorTaskDone_;
};

#endif

template <typename Object>
class ScopedPtr
{
public:
    explicit ScopedPtr(Object* obj) ONIXS_B3_BOE_NOTHROW
        : obj_(obj)
    {
    }

    ~ScopedPtr()
    {
        delete obj_;
    }

    Object* operator->() const ONIXS_B3_BOE_NOTHROW
    {
        assert(ONIXS_B3_BOE_NULLPTR != obj_);
        return obj_;
    }

    Object& operator*() const ONIXS_B3_BOE_NOTHROW
    {
        assert(ONIXS_B3_BOE_NULLPTR != obj_);
        return *obj_;
    }

private:
    Object * const obj_;

    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator =(const ScopedPtr&);
};

inline
SessionSettings fillSettings(bool useEmulator = false)
{
    SessionSettings settings;

    const std::string settingsFilename("settings.ini");
    std::ifstream settingsFile(settingsFilename.c_str());
    if (settingsFile)
    {
        settingsFile.close();
        settings.load(settingsFilename);
    }
    else
    {
        settings
            .licenseStore("../../license")
            .tradingSystemVersion("1.0.0");

        if(useEmulator)
            settings
                .sessionId(100000121)
                .enteringFirm(900)
                .accessKey("AccessKey")
                .tradingSystemName("OnixS 1");
        else
            settings
                .sessionId(100000121 /* "Value Received From B3" */)
                .accessKey("Value Received From B3")
                .enteringFirm(900 /* "Value Received From B3" */)
                .tradingSystemName("OnixS 1");
    }

    if(useEmulator)
        settings.keepAliveInterval(5000).reconnectAttempts(0);

    return settings;
}

inline void setPriorityAndPolicy(OnixS::B3::BOE::Session* session = ONIXS_B3_BOE_NULLPTR)
{
#ifdef _WIN32
    OnixS::B3::BOE::Threading::ThisThread::priority(THREAD_PRIORITY_ABOVE_NORMAL);

    if(session)
        session->receivingThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
#else
    const int policy = SCHED_RR;
    try
    {
        OnixS::B3::BOE::Threading::ThisThread::policy(policy);

        if(session)
            session->receivingThreadPolicy(policy);
    }
    catch (const std::exception&)
    {
        std::cerr << "\nWARNING: Cannot change the scheduling policy to " << policy <<
             ", it requires root permissions, so you either have to be root or run it with sudo." << std::endl;
    }
#endif
}

}
//! [Helpers]
