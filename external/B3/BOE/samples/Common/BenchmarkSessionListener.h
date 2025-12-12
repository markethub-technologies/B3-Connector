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

#include <OnixS/B3/BOE/CompilerDetection.h>

#include "PerformanceCounter.h"
#include "BenchmarkData.h"
#include "Helpers.h"

#define ONIXS_USE_HUGE_PAGE 1

#if ONIXS_USE_HUGE_PAGE
# ifndef _WIN32
#  include <sys/mman.h>
#  ifdef MAP_FAILED
#   undef MAP_FAILED
#  endif
# define MAP_FAILED reinterpret_cast<void*>(-1)
# endif
#endif

#ifndef MAP_HUGETLB
#  undef ONIXS_USE_HUGE_PAGE
#  define ONIXS_USE_HUGE_PAGE 0
#  undef MAP_FAILED
#endif

#ifdef __GNUC__
# define ONIXS_B3_BOE_PREFETCH(ptr) __builtin_prefetch(ptr, 1, 1);
#else
# define ONIXS_B3_BOE_PREFETCH(ptr) /**/
#endif

class Allocator
{
public:
    Allocator()
        : chunk_(init())
        , ptr_(chunk_)
        , available_(HugePageSize)
    {
    }

    ~Allocator()
    {
        fini(chunk_);
    }

    void* allocate(size_t size)
    {
        size = roundToCasheLine(size);

        if(size > available_)
            throwAllocatorExhausted();

        void* const ptr = ptr_;
        available_ -= size;
        ptr_ = Messaging::advanceByBytes(ptr_, size);

        return ptr;
    }

    template <typename T>
    T* allocate(size_t n)
    {
        return static_cast<T*>(allocate(sizeof(T) * n));
    }

private:
    enum { HugePageSize = 1 << 21 };

    void* init()
    {
        const std::size_t size = HugePageSize;
        void* ptr = ONIXS_B3_BOE_NULLPTR;

#ifdef _WIN32
        ptr = _aligned_malloc(size, 4096);
#else

#  if ONIXS_USE_HUGE_PAGE
        const int flags =  MAP_PRIVATE | MAP_ANONYMOUS | MAP_LOCKED | MAP_POPULATE | MAP_HUGETLB;

        ptr = mmap(ONIXS_B3_BOE_NULLPTR, size, PROT_READ | PROT_WRITE, flags, -1, 0);

        if (ptr == MAP_FAILED)
            throwNoHugePage();
#  else
        if (0 != posix_memalign(&ptr, 4096, size))
            ptr = ONIXS_B3_BOE_NULLPTR;
#  endif

#endif
        if (!ptr)
            throw std::bad_alloc();

        return ptr;
    }

    void fini(void* ptr) ONIXS_B3_BOE_NOTHROW
    {
#ifdef _WIN32
        _aligned_free(ptr);
#else
#  if ONIXS_USE_HUGE_PAGE
        munmap(ptr, HugePageSize);
# else
        free(ptr);
# endif
#endif
    }

    static size_t roundToCasheLine(size_t n) ONIXS_B3_BOE_NOTHROW
    {
        return (((n - 1) / ONIXS_B3_BOE_HARDWARE_DESTRUCTIVE_INTERFACE_SIZE) + 1) * ONIXS_B3_BOE_HARDWARE_DESTRUCTIVE_INTERFACE_SIZE;
    }

    ONIXS_B3_BOE_NORETURN
    static void throwNoHugePage()
    {
        struct Exception : public std::bad_alloc
        {
            const char* what() const throw() ONIXS_B3_BOE_OVERRIDE
            {
                return
                    "Unable to allocate a huge page. "
                    "Please enable it on your system (sudo sysctl -w vm.nr_hugepages=N), "
                    "or disable it's usage in the application (ONIXS_USE_HUGE_PAGE).";
            }
        };

        throw Exception();
    }

    ONIXS_B3_BOE_NORETURN
    static void throwAllocatorExhausted()
    {
        struct Exception : public std::bad_alloc
        {
            const char* what() const throw() ONIXS_B3_BOE_OVERRIDE
            {
                return "The allocator is exhausted.";
            }
        };

        throw Exception();
    }

    void * const chunk_;
    void * ptr_;
    size_t available_;
};

class BenchmarkSessionListener : public SessionListener
{
public:
    explicit BenchmarkSessionListener(size_t numberOfMessages)
        : allocator_()
        , active_(false)
        , packetGroupingDetected_()
        , numberOfMessages_(numberOfMessages)
        , receiveMarks_(allocator_.allocate<BenchmarkData::ReceiveMarks>(numberOfMessages))
        , receiveCounter_(0)
        , sendMarks_(allocator_.allocate<BenchmarkData::SendMarks>(numberOfMessages))
        , sendCounter_(0)
    {
        for(size_t i = 0; i < numberOfMessages; ++i)
            new (sendMarks_ + i) BenchmarkData::SendMarks();

        for(size_t i = 0; i < numberOfMessages; ++i)
            new (receiveMarks_ + i) BenchmarkData::ReceiveMarks();
    }

    ~BenchmarkSessionListener() ONIXS_B3_BOE_OVERRIDE {
    }

    bool active() const ONIXS_B3_BOE_NOTHROW {
        return active_;
    }

    bool packetGroupingDetected() const ONIXS_B3_BOE_NOTHROW {
        return packetGroupingDetected_;
    }

    const BenchmarkData::SendMarks * sendMarks() const ONIXS_B3_BOE_NOTHROW {
        return sendMarks_;
    }

    const BenchmarkData::ReceiveMarks * receiveMarks() const ONIXS_B3_BOE_NOTHROW {
        return receiveMarks_;
    }

    const BenchmarkData::Overhead & overhead() const ONIXS_B3_BOE_NOTHROW {
        return overhead_;
    }

    void measureOverhead() {
        ReceivedDataTimestamp dummy;
        resetBenchmark();

        const size_t iterations = numberOfMessages_ - 1;

        for(size_t i = 0; i < iterations; i++) {
            beforeSending();
            onMessageSending(ONIXS_B3_BOE_NULLPTR, 0, ONIXS_B3_BOE_NULLPTR);
            afterSending();
            onReceivedBytes(ONIXS_B3_BOE_NULLPTR, 0, dummy, ONIXS_B3_BOE_NULLPTR);
            onReceivedApplicationMessage();
        }

        const size_t median = iterations / 2;

        vector<PerformanceCounter::Span> data;
        data.reserve(iterations);

        for(size_t i = 0; i < iterations; i++)
            data.push_back(receiveMarks_[i].recvSpanNano());

        sort(data.begin(), data.end());
        overhead_.receive = data[median];

        data.clear();
        for(size_t i = 0; i < iterations; i++)
            data.push_back(sendMarks_[i].sendSpanNano());

        sort(data.begin(), data.end());
        overhead_.send = data[median];

        data.clear();
        for(size_t i = 0; i < iterations; i++)
            data.push_back(sendMarks_[i].overallSendSpanNano());

        sort(data.begin(), data.end());
        overhead_.overallSend = data[median];

        data.clear();
        for(size_t i = 0; i < iterations; i++)
            data.push_back(BenchmarkData::oneWaySpanNano(sendMarks_[i], receiveMarks_[i]));

        sort(data.begin(), data.end());
        overhead_.oneWay = data[median];

        resetBenchmark();
        active_ = false;
    }

    virtual void resetBenchmark() ONIXS_B3_BOE_NOTHROW {
        for(size_t i = 0; i < numberOfMessages_; ++i) {
            sendMarks_[i] = BenchmarkData::SendMarks();
            receiveMarks_[i] = BenchmarkData::ReceiveMarks();
        }

        sendCounter_ = 0;
        receiveCounter_ = 0;
        packetGroupingDetected_ = false;
        active_ = true;

        ONIXS_B3_BOE_PREFETCH(&sendMarks_[sendCounter_]);
    }

    ONIXS_B3_BOE_HOTPATH
    void beforeSending() ONIXS_B3_BOE_NOTHROW {
        assert(sendCounter_ < numberOfMessages_);
        PerformanceCounter::current(&sendMarks_[sendCounter_].sendStart);
    }

    ONIXS_B3_BOE_HOTPATH
    void afterSending() ONIXS_B3_BOE_NOTHROW {
        assert(sendCounter_ < numberOfMessages_);
        PerformanceCounter::current(&sendMarks_[sendCounter_++].overallSendFinish);

        ONIXS_B3_BOE_PREFETCH(&sendMarks_[sendCounter_]);
    }

    void onStateChange(SessionStateId::Enum newState, SessionStateId::Enum /* prevState */, Session * /*sn*/) ONIXS_B3_BOE_OVERRIDE {
        switch(newState) {
        case SessionStateId::Established:
            active_ = true;
            ONIXS_B3_BOE_PREFETCH(&receiveMarks_[receiveCounter_]);
            break;

        case SessionStateId::Disconnected:
            active_ = false;
            break;

        default:
            break;
        }
    }

    ONIXS_B3_BOE_HOTPATH
    void onBusinessMessageReject(const BusinessMessageReject206 & /*msg*/, Session * /*sn*/) ONIXS_B3_BOE_OVERRIDE {
        onReceivedApplicationMessage();
    }

    ONIXS_B3_BOE_HOTPATH
    void onExecutionReportNew(const ExecutionReportNew200 & /*msg*/, Session * /*sn*/) ONIXS_B3_BOE_OVERRIDE {
        onReceivedApplicationMessage();
    }

    ONIXS_B3_BOE_HOTPATH
    void onExecutionReportReject(const ExecutionReportReject204 & /*msg*/, Session * /*sn*/) ONIXS_B3_BOE_OVERRIDE {
        onReceivedApplicationMessage();
    }

    ONIXS_B3_BOE_HOTPATH
    void onReceivedBytes(const char * /*bytes*/, size_t /*size*/, const ReceivedDataTimestamp&, Session * /* sn*/) ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        if ONIXS_B3_BOE_UNLIKELY(!active_)
            return;

        // More than one SBE message could be received in one IP packet.
        assert(receiveCounter_ < numberOfMessages_);
        PerformanceCounter::current(&receiveMarks_[receiveCounter_].recvStart);
    }

    ONIXS_B3_BOE_HOTPATH
    void onMessageSending(char * /*bytes*/, size_t /*size*/, Session * /*sn*/) ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        if ONIXS_B3_BOE_UNLIKELY(!active_)
            return;

        assert(sendCounter_ < numberOfMessages_);
        PerformanceCounter::current(&sendMarks_[sendCounter_].sendFinish);
    }

    void onError(
        SessionErrorReason::Enum /* reason */, const string & description, Session * /* sn*/, Messaging::SbeMessage) ONIXS_B3_BOE_OVERRIDE {
        cerr << "\nSession-level error: " << description << endl;
        active_ = false;
    }

    void onWarning(
        SessionWarningReason::Enum /*reason*/, const string & description, Session * /*sn*/, Messaging::SbeMessage) ONIXS_B3_BOE_OVERRIDE {
        cerr << "\nSession-level warning: " << description << endl;
    }

protected:
    virtual void onReceivedAllMessages() {
        active_ = false;
    }

private:
    ONIXS_B3_BOE_HOTPATH
    void onReceivedApplicationMessage() ONIXS_B3_BOE_NOTHROW {
        if ONIXS_B3_BOE_UNLIKELY(!active_)
            return;

        BenchmarkData::ReceiveMarks & rm = receiveMarks_[receiveCounter_];
        PerformanceCounter::current(&rm.recvFinish);

        if ONIXS_B3_BOE_UNLIKELY(PerformanceCounter::isUndefinedValue(rm.recvStart)) {
            // The received IP packet contained more than one message.
            rm.recvStart = receiveMarks_[receiveCounter_ - 1].recvFinish;
            packetGroupingDetected_ = true;
        }

        if ONIXS_B3_BOE_UNLIKELY(numberOfMessages_ == ++receiveCounter_)
            onReceivedAllMessages();

        ONIXS_B3_BOE_PREFETCH(&receiveMarks_[receiveCounter_]);
    }

    Allocator allocator_;
    bool active_;
    bool packetGroupingDetected_;

    const size_t numberOfMessages_;

    BenchmarkData::Overhead overhead_;

    ONIXS_B3_BOE_ALIGNAS(ONIXS_B3_BOE_HARDWARE_DESTRUCTIVE_INTERFACE_SIZE) BenchmarkData::ReceiveMarks * const receiveMarks_;
    size_t receiveCounter_;

    ONIXS_B3_BOE_ALIGNAS(ONIXS_B3_BOE_HARDWARE_DESTRUCTIVE_INTERFACE_SIZE) BenchmarkData::SendMarks * const sendMarks_;
    size_t sendCounter_;
};

class ReactorBenchmarkListener ONIXS_B3_BOE_FINAL : public BenchmarkSessionListener
{
public:
    explicit ReactorBenchmarkListener(size_t numberOfMessages)
        : BenchmarkSessionListener(numberOfMessages)
        , receivedAllMessages_()
    {}

    bool receivedAllMessages() const ONIXS_B3_BOE_NOTHROW {
        return receivedAllMessages_;
    }

    void resetBenchmark() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        BenchmarkSessionListener::resetBenchmark();
        receivedAllMessages_ = false;
    }

    template <typename Stack>
    void collectSessionTimeMarks(
        Stack& stack, Session & session, Samples::NewOrderSingle & order,
        unsigned int numberOfMessages, unsigned int sendPeriodUsec, unsigned int warmupPeriodUsec);

protected:
    void onReceivedAllMessages() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        BenchmarkSessionListener::onReceivedAllMessages();
        receivedAllMessages_ = true;
    }

private:
    bool receivedAllMessages_;
};


template <typename Stack>
ONIXS_B3_BOE_HOTPATH
void ReactorBenchmarkListener::collectSessionTimeMarks(
    Stack& stack, Session & session, Samples::NewOrderSingle & order,
    unsigned int numberOfMessages, unsigned int sendPeriodUsec, unsigned int warmupPeriodUsec)
{
    resetBenchmark();

    // When the session is used with the OnixS C++ B3 Market Data Handler,
    // this value can be taken from the packet receiving time
    Messaging::Timestamp sendingTime = UtcWatch::now();

    for(unsigned int messageCounter = 0; messageCounter < numberOfMessages; ++messageCounter)
    {
        order->setOrderQty(messageCounter + 1);
        order->setClOrdId(messageCounter);

        beforeSending();
        session.send(order, sendingTime);
        afterSending();

        stack.dispatchEvents();

        sendingTime = UtcWatch::now();

        if(warmupPeriodUsec || sendPeriodUsec)
        {
            const PerformanceCounter::Count start = PerformanceCounter::current();

            PerformanceCounter::Span elapsedMicroseconds = 0;
            do
            {
                do
                {
                    stack.dispatchEvents();
                    session.warmUp(order, sendingTime);
                }
                while((elapsedMicroseconds = PerformanceCounter::elapsedMicroseconds(start)) < warmupPeriodUsec);

                stack.dispatchEvents();
                elapsedMicroseconds = PerformanceCounter::elapsedMicroseconds(start);
            }
            while(elapsedMicroseconds < sendPeriodUsec);
        }
    }

    while(active())
        stack.dispatchEvents();
}
