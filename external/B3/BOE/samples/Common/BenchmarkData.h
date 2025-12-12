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

#include "PerformanceCounter.h"

#include <numeric>

#ifndef _WIN32
#include <stdlib.h>
#endif

struct BenchmarkData
{
    struct SendMarks {
        PerformanceCounter::Count sendStart;
        PerformanceCounter::Count sendFinish;
        PerformanceCounter::Count overallSendFinish; // includes the OS kernel ::send(..) time

        SendMarks()
            : sendStart()
            , sendFinish()
            , overallSendFinish()
        {}

        PerformanceCounter::Span sendSpanNano() const {
            return PerformanceCounter::nsSpan(sendFinish, sendStart);
        }

        PerformanceCounter::Span overallSendSpanNano() const {
            return PerformanceCounter::nsSpan(overallSendFinish, sendStart);
        }
    };

    struct ReceiveMarks {
        PerformanceCounter::Count recvStart;
        PerformanceCounter::Count recvFinish;

        ReceiveMarks()
            : recvStart()
            , recvFinish()
        {}

        PerformanceCounter::Span recvSpanNano() const {
            return PerformanceCounter::nsSpan(recvFinish, recvStart);
        }
    };

    // Measurement overhead
    struct Overhead
    {
        PerformanceCounter::Span receive;
        PerformanceCounter::Span send;
        PerformanceCounter::Span overallSend;
        PerformanceCounter::Span oneWay;

        Overhead()
            : receive()
            , send()
            , overallSend()
            , oneWay()
        {}
    };

    static PerformanceCounter::Span oneWaySpanNano(const SendMarks & sm, const ReceiveMarks & rm) {
        return PerformanceCounter::nsSpan(rm.recvFinish, sm.sendStart);
    }

    typedef vector<PerformanceCounter::Span> Latencies;

    struct SquareVariance
    {
        explicit SquareVariance(double mean)
            : mean_(mean)
        {}

        double operator()(double sum, PerformanceCounter::Span value) const {
            return sum + std::pow(static_cast<double>(value) - mean_, 2u);
        }

        double mean_;
    };

    static double stdDev(const Latencies& data) {
        const size_t size = data.size();
        assert(size > 1);

        const double mean = std::accumulate(data.begin(), data.end(), static_cast<double>(0.0f)) / size;

        return std::sqrt(
            std::accumulate(data.begin(), data.end(), static_cast<double>(0.0f), SquareVariance(mean)) / (size - 1));
    }

    static void processAndReportLatencies(const std::string & name, Latencies & latencies) {
        sort(latencies.begin(), latencies.end());

        const size_t NameWidth = 23;

        clog << setw(NameWidth) << left << name;

        if(name.length() > NameWidth)
            clog << endl << setw(NameWidth) << ' ';

        clog
            << std::right
            << "min: " << setw(7) << *latencies.begin()
            << "   median: " << setw(7) << latencies.at(latencies.size() / 2)
            << "   99th percentile: " << setw(6)
            << latencies.at(static_cast<size_t>(ceil((latencies.size() * 99) / 100.0)) - 1)
            << "   stdDev: " << setw(10) << fixed << setprecision(2) << stdDev(latencies)
            << endl;
    }

    static void reportResults(const string & name, const SendMarks * sendMarksArray, const ReceiveMarks * receiveMarksArray, size_t count, const Overhead & overhead) {
        const string baseName = name + '_';

        ofstream receiveStream(string(baseName + "recv.csv").c_str(), ios_base::ate);
        ofstream sendStream(string(baseName + "send.csv").c_str(), ios_base::ate);
        ofstream overallSendStream(string(baseName + "overallsend.csv").c_str(), ios_base::ate);
        ofstream sendAndReceiveStream(string(baseName + "sendrecv.csv").c_str(), ios_base::ate);

#define MEASURE_NETWORK_LATENCY 1 // Includes the network-related latency and B3's or emulator processing time.

#if MEASURE_NETWORK_LATENCY
        ofstream oneWayStream(string(baseName + "oneway.csv").c_str(), ios_base::ate);
        Latencies oneWayLatencies;
#endif

        Latencies sendLatencies, overallSendLatencies, receiveLatencies, sendAndReceiveLatencies;

        for(size_t i = 0; i < count; ++i) {
            const SendMarks & sendMarks = sendMarksArray[i];
            const ReceiveMarks & receiveMarks = receiveMarksArray[i];

            assert(!PerformanceCounter::isUndefinedValue(receiveMarks.recvStart));

            receiveLatencies.push_back(receiveMarks.recvSpanNano() - overhead.receive);
            receiveStream << *receiveLatencies.rbegin() << endl;

            sendLatencies.push_back(sendMarks.sendSpanNano() - overhead.send);
            sendStream << *sendLatencies.rbegin() << endl;

            overallSendLatencies.push_back(sendMarks.overallSendSpanNano() - overhead.overallSend);
            overallSendStream << *overallSendLatencies.rbegin() << endl;

            const PerformanceCounter::Span sendAndReceiveLatency = *sendLatencies.rbegin() + *receiveLatencies.rbegin();
            sendAndReceiveLatencies.push_back(sendAndReceiveLatency);
            sendAndReceiveStream << *sendAndReceiveLatencies.rbegin() << endl;

#if MEASURE_NETWORK_LATENCY
            oneWayLatencies.push_back((oneWaySpanNano(sendMarks, receiveMarks) - overhead.oneWay) / 2);
            oneWayStream << *oneWayLatencies.rbegin() << endl;
#endif
        }

        clog << endl << name << " (nanoseconds): \n" << endl;

        processAndReportLatencies("Handler Receive", receiveLatencies);
        processAndReportLatencies("Handler Send", sendLatencies);
        processAndReportLatencies("Handler Send+Receive", sendAndReceiveLatencies);
        processAndReportLatencies(
            "OS + Handler Send (depends on the network card, kernel bypass software, OS load)",
            overallSendLatencies
        );

#if MEASURE_NETWORK_LATENCY
        processAndReportLatencies("One-Way (Round-Trip/2)", oneWayLatencies);
#endif

#define REPORT_OVERHEAD 1

#if REPORT_OVERHEAD
        clog
            << endl << "Measurement overhead:" << endl
            << "Send: " << overhead.send << endl
            << "Receive: " << overhead.receive << endl
            << "Send+Receive: " << overhead.send + overhead.receive << endl
            << "OS + Handler Send: " << overhead.overallSend << endl;
#endif

#if MEASURE_NETWORK_LATENCY
        clog << "One way:" << overhead.oneWay << endl;
#endif
    }
};
