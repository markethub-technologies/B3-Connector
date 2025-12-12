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

#include "stdafx.h"

//! [BenchmarkSample]

#include <OnixS/B3/BOE/threading/Semaphore.h>

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
#include "../Common/BenchmarkGatewayListener.h"
#endif

#include "../Common/BenchmarkSessionListener.h"
#include "../Common/Helpers.h"
#include "../Common/PerformanceCounter.h"

#include "../Settings/Defaults.h"

#ifndef _WIN32
#include <sched.h>      /* header file for POSIX scheduling */
#endif

#include <algorithm>

// #define DEBUGGING

using namespace Samples;

void usage()
{
    clog << "Usage: Benchmark [MarketSegmentId] [Host] [Port] (MainThreadAffinity) (ReceivingThreadAffinity) (AuxiliarySendingThreadAffinity)"
           " (NumberOfMessages) (IntervalBetweenSendingUsec) (WarmupIntervalUsec)" << endl;
}

int main(int argc, char* argv[])
{
    clog << "B3 BOE Benchmark Sample, version " << Session::version() << "." << endl << endl;

#if !defined(NDEBUG) && !defined(DEBUGGING)
    cerr << "Please use the RELEASE build to measure latency." << endl;
    return 1;
#endif

    MarketSegmentID marketSegmentId = DefaultMarketSegmentId;
    string host = "127.0.0.1";
    Port port = 49152;

    bool useEmulator = false;

    if (argc < 4)
    {
#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
        useEmulator = true;
        clog << "WARNING: gateway emulator is used!" << endl;
#else
        usage();
        return 1;
#endif
    }
    else
    {
        marketSegmentId = atoi(argv[1]);
        host = argv[2];
        port = atoi(argv[3]);
    }

    const Threading::CpuIndex MainThreadAffinity = argc > 4 ? atoi(argv[4]) : 1u;
    const Threading::CpuIndex ReceivingThreadAffinity = argc > 5 ? atoi(argv[5]) : 2u;
    const Threading::CpuIndex AuxiliarySendingThreadAffinity = argc > 6 ? atoi(argv[6]) : 3u;
    const unsigned int NumberOfMessages = argc > 7 ? atoi(argv[7]) : 300u;
    const unsigned int WarmupIntervalUsec = argc > 9 ? atoi(argv[9]) : 10u;
    const unsigned int IntervalBetweenSendingUsec = std::max(argc > 8 ? atoi(argv[8]) : 10000u, WarmupIntervalUsec);

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
    BenchmarkGatewayListener gatewayListener;
    std::unique_ptr<GatewayEmulatorThread> gateway;
#endif

    int result = 0;

    try
    {
        SignalHelper::manageLinuxSignals();

        SessionSettings settings = fillSettings(useEmulator);

        settings
            .receiveSpinningTimeout(1000*1000)
            .useSpinLock(true)
            .logBeforeSending(false);

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
        if(useEmulator)
            gateway.reset(new GatewayEmulatorThread(settings.licenseStores(), host, port, &gatewayListener));
#endif

        class BenchmarkListener ONIXS_B3_BOE_FINAL : public BenchmarkSessionListener
        {
        public:
            explicit BenchmarkListener(size_t numberOfMessages)
                : BenchmarkSessionListener(numberOfMessages)
                , receivedAllMessages_(0)
            {}

            void onError(SessionErrorReason::Enum reason, const std::string & description, Session * session, Messaging::SbeMessage msg) ONIXS_B3_BOE_OVERRIDE {
                BenchmarkSessionListener::onError(reason, description, session, msg);
                receivedAllMessages_.release();
            }

            ONIXS_B3_BOE_HOTPATH
            void collectSessionTimeMarks(Session & session, Samples::NewOrderSingle & order,
                unsigned int numberOfMessages, unsigned int sendPeriodUsec, unsigned int warmupPeriodUsec) {

                resetBenchmark();

                // When the session is used with the OnixS C++ B3 Market Data Handler,
                // this value can be taken from the packet receiving time
                Messaging::Timestamp sendingTime = UtcWatch::now();

                for(UInt32 messageCounter = 0; messageCounter < numberOfMessages; ++messageCounter) {
                    order->setOrderQty(messageCounter + 1);
                    order->setClOrdId(messageCounter);

                    beforeSending();
                    session.send(order, sendingTime);
                    afterSending();

                    sendingTime = UtcWatch::now();

                    if(warmupPeriodUsec) {
                        const PerformanceCounter::Count start = PerformanceCounter::current();

                        do {
                            ThisThread::spinWait(warmupPeriodUsec);
                            session.warmUp(order, sendingTime);
                        } while(PerformanceCounter::elapsedMicroseconds(start) < sendPeriodUsec);
                    }
                    else if(sendPeriodUsec) {
                        ThisThread::spinWait(sendPeriodUsec);
                    }
                }

                waitUntilReceivedAllMessages();
            }

        private:
            void onReceivedAllMessages() ONIXS_B3_BOE_OVERRIDE {
                BenchmarkSessionListener::onReceivedAllMessages();
                receivedAllMessages_.release();
            }

            void waitUntilReceivedAllMessages() {
                receivedAllMessages_.acquire();
            }

            Semaphore receivedAllMessages_;
        }
        listener(NumberOfMessages);

#if defined(DEBUGGING)
        const SessionStorageType::Enum storageType = SessionStorageType::FileBased;
#else
        const SessionStorageType::Enum storageType = SessionStorageType::MemoryBased;
#endif

        clog << "Parameters: NumberOfMessages=" << NumberOfMessages << "; IntervalBetweenSendingUsec=" << IntervalBetweenSendingUsec
             << "; warmupIntervalUsec=" << WarmupIntervalUsec
             << "; StorageType=" << SessionStorageType::toString(storageType) << '.' << endl;

        Session session(settings, &listener, storageType);

        ThisThread::affinity(MainThreadAffinity);
        setPriorityAndPolicy(&session);

        listener.measureOverhead();

        session
            .receivingThreadAffinity(ReceivingThreadAffinity)
            .sendingThreadAffinity(AuxiliarySendingThreadAffinity)
            .connect(host, port);

        NewOrderSingle order;
        Helper::setOrderFields(order, marketSegmentId, DefaultSecurityId, DefaultAccount, DefaultPriceMantissa);

        clog << "\nWarm-up phase to make first calls faster..." << endl;
        listener.collectSessionTimeMarks(session, order, NumberOfMessages, IntervalBetweenSendingUsec, WarmupIntervalUsec);

        clog << "\nMeasurement phase..." << endl;
        listener.collectSessionTimeMarks(session, order, NumberOfMessages, IntervalBetweenSendingUsec, WarmupIntervalUsec);

        TcpInfo tcpInfo;
        const bool hasTcpInfo = session.getTcpInfo(tcpInfo);

        session.disconnect();

        if(listener.packetGroupingDetected())
            clog << "Attention: packet grouping detected! Increase the interval between sending!" << endl;

        BenchmarkData::reportResults("Latency", listener.sendMarks(), listener.receiveMarks(), NumberOfMessages, listener.overhead());

        if(hasTcpInfo)
            clog << "\n\n" << tcpInfo.toString();

#ifndef _WIN32
        ThisThread::policy(SCHED_OTHER);
#endif
    }
    catch (const exception& ex)
    {
        cerr << "\nEXCEPTION: " << ex.what() << endl;
        result = 1;
    }

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
    if(gateway) {
        try {
            gateway->wait();
        }
        catch(...) {
            // Emulator exception (if any) is already reported from Emulator's thread
        }
    }
#endif

    return result;
}

#include "../Common/PerformanceCounter.inc.h"
//! [BenchmarkSample]
