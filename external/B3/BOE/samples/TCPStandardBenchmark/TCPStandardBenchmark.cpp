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

//! [TCPStandardBenchmarkSample]
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
    clog << "Usage: Benchmark [MarketSegmentId] [Host] [Port] (MainThreadAffinity)"
           " (NumberOfMessages) (IntervalBetweenSendingUsec) (WarmupIntervalUsec)" << endl;
}

int main(int argc, char* argv[])
{
    clog << "B3 BOE TCPStandardBenchmark Sample, version " << Session::version() << "." << endl << endl;

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
    const unsigned int NumberOfMessages = argc > 5 ? atoi(argv[5]) : 300u;
    const unsigned int WarmupIntervalUsec = argc > 7 ? atoi(argv[7]) : 10u;
    const unsigned int IntervalBetweenSendingUsec = std::max(argc > 6 ? atoi(argv[6]) : 10000u, WarmupIntervalUsec);

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

        ThisThread::affinity(MainThreadAffinity);
        setPriorityAndPolicy();

        TcpStandardStack stack;

        ReactorBenchmarkListener listener(NumberOfMessages);
        listener.measureOverhead();

        try {
#if defined(DEBUGGING)
            const SessionStorageType::Enum storageType = SessionStorageType::FileBased;
#else
            const SessionStorageType::Enum storageType = SessionStorageType::MemoryBased;
#endif

            clog << "Parameters: NumberOfMessages=" << NumberOfMessages << "; IntervalBetweenSendingUsec=" << IntervalBetweenSendingUsec
                << "; warmupIntervalUsec=" << WarmupIntervalUsec
                << "; StorageType=" << SessionStorageType::toString(storageType) << '.' << endl;

            Session session(stack, settings, &listener, storageType);

            SharedFuture<void> connected = session.connectAsync(host, port);

            while(!connected.is_ready())
                stack.dispatchEvents();

            if(connected.has_exception())
                connected.get();

            NewOrderSingle order;
            Helper::setOrderFields(order, marketSegmentId, DefaultSecurityId, DefaultAccount, DefaultPriceMantissa);

            clog << "\nWarm-up phase to make first calls faster..." << endl;

            listener.collectSessionTimeMarks(
                stack, session, order, NumberOfMessages, IntervalBetweenSendingUsec, WarmupIntervalUsec);

            if(listener.receivedAllMessages()) {
                clog << "\nMeasurement phase..." << endl;

                listener.collectSessionTimeMarks(
                    stack, session, order, NumberOfMessages, IntervalBetweenSendingUsec, WarmupIntervalUsec);
            }

            SharedFuture<void> disconnected = session.disconnectAsync();

            while(!disconnected.is_ready())
                stack.dispatchEvents();

            if(disconnected.has_exception())
                disconnected.get();

        } catch(const exception& ex) {
            cerr << "\nEXCEPTION: " << ex.what() << endl;
            result = 1;
        }

        while(!stack.isQuiescent())
            stack.dispatchEvents();

        if(listener.receivedAllMessages()) {
            if(listener.packetGroupingDetected())
                clog << "Attention: packet grouping detected! Increase the interval between sending!" << endl;

            BenchmarkData::reportResults("Latency", listener.sendMarks(), listener.receiveMarks(), NumberOfMessages, listener.overhead());
        }

#ifndef _WIN32
        ThisThread::policy(SCHED_OTHER);
#endif
    }
    catch (const exception& ex) {
        cerr << "\nEXCEPTION: " << ex.what() << endl;
        result = 1;
    }

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
    if(gateway) {
        try {
            gateway->wait();
        }
        catch(...) {
            // emulator exception (if any) is already reported from Emulator's thread
        }
    }
#endif

    return result;
}

#include "../Common/PerformanceCounter.inc.h"
//! [TCPStandardBenchmarkSample]
