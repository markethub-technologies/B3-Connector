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

//! [MyListenerCpp]
#include <iostream>
#include <algorithm>
#include <iterator>

#include "MyListener.h"

#include <Common/Utils.h>

namespace Sample
{
    ONIXS_B3_UMDF_MD_COLDPATH
    void* Allocator::init(size_t size)
    {
        void* ptr = nullptr;

#ifdef _WIN32
        ptr = _aligned_malloc(size, 4096);
#else

#  if ONIXS_USE_HUGE_PAGE
        const int flags =  MAP_PRIVATE | MAP_ANONYMOUS | MAP_LOCKED | MAP_POPULATE | MAP_HUGETLB;

        ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, flags, -1, 0);

        if (ptr == MAP_FAILED)
            throwNoHugePage();
#  else
        if (0 != posix_memalign(&ptr, 4096, size))
            ptr = nullptr;
#  endif

#endif
        if (!ptr)
            throw std::bad_alloc();

#ifndef _WIN32
        ::madvise(ptr, size, MADV_SEQUENTIAL);
#endif

        return ptr;
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    void Allocator::fini(void* ptr)
    {
#ifdef _WIN32
        _aligned_free(ptr);
#else
#  if ONIXS_USE_HUGE_PAGE
        munmap(ptr, size_);
# else
        free(ptr);
# endif
#endif
    }

    Allocator::Allocator(size_t size)
        : size_(size)
        , chunk_(init(size_))
        , ptr_(chunk_)
        , available_(size_)
    {
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    Allocator::~Allocator()
    {
        fini(chunk_);
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    void Allocator::throwNoHugePage()
    {
        struct Exception : public std::bad_alloc
        {
            const char* what() const throw() override
            {
                return
                    "Unable to allocate a huge page. "
                    "Please enable it on your system (sudo sysctl -w vm.nr_hugepages=N), "
                    "or disable it's usage in the application (ONIXS_USE_HUGE_PAGE).";
            }
        };

        throw Exception();
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    void Allocator::throwAllocatorExhausted()
    {
        struct Exception : public std::bad_alloc
        {
            const char* what() const throw() override
            {
                return "The allocator is exhausted.";
            }
        };

        throw Exception();
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    void* Allocator::allocate(size_t size)
    {
        if(size > available_)
            throwAllocatorExhausted();

        void* const ptr = ptr_;
        available_ -= size;
        ptr_ = Messaging::advanceByBytes(ptr_, size);

        return ptr;
    }

    Latency MyListener::calculateAdjustment()
    {
        const int iterations = 10000;
        Latencies latencies;

        latencies.reserve(iterations);

        for(int i = 0; i < iterations; ++i)
        {
            const TimeSpan latency = Timestamp::utcNow() - Timestamp::utcNow();
            latencies.push_back (latency.ticks());
        }

        std::sort (latencies.begin(), latencies.end());

        return (latencies[latencies.size() / 2]);
    }

    MyListener::MyListener(size_t packetsToProcess)
        : allocator_(MaxLatenciesCount * sizeof(Marks))
        , receiveMarks_(new (allocator_.allocate<Marks>(MaxLatenciesCount)) Marks[MaxLatenciesCount])
        , packetsToProcess_(packetsToProcess)
    {
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onNews_5(const Messaging::News_5, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onClosingPrice_17(const Messaging::ClosingPrice_17, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onQuantityBand_21(const Messaging::QuantityBand_21, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onPriceBand_22(const Messaging::PriceBand_22, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onOpeningPrice_15(const Messaging::OpeningPrice_15, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onTheoreticalOpeningPrice_16(const Messaging::TheoreticalOpeningPrice_16, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onAuctionImbalance_19(const Messaging::AuctionImbalance_19, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onHighPrice_24(const Messaging::HighPrice_24, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onLowPrice_25(const Messaging::LowPrice_25, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onLastTradePrice_27(const Messaging::LastTradePrice_27, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onSettlementPrice_28(const Messaging::SettlementPrice_28, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onOpenInterest_29(const Messaging::OpenInterest_29, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onOrder_MBO_50(const Messaging::Order_MBO_50, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onDeleteOrder_MBO_51(const Messaging::DeleteOrder_MBO_51, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onMassDeleteOrders_MBO_52(const Messaging::MassDeleteOrders_MBO_52, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onTrade_53(const Messaging::Trade_53, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onForwardTrade_54(const Messaging::ForwardTrade_54, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onExecutionSummary_55(const Messaging::ExecutionSummary_55, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onExecutionStatistics_56(const Messaging::ExecutionStatistics_56, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    void
    ONIXS_B3_UMDF_MD_HOTPATH
    MyListener::onTradeBust_57(const Messaging::TradeBust_57, const DataSource& dataSource)
    {
        collectMessageReceptionMark(dataSource);
    }

    ONIXS_B3_UMDF_MD_HOTPATH
    void MyListener::collectOrderBookChangeMark(Messaging::MessageTemplateId templateId)
    {
        receiveMarks_[marksCounter_].bookTime = Timestamp::utcNow();
        receiveMarks_[marksCounter_].messageType = templateId;
    }

    ONIXS_B3_UMDF_MD_HOTPATH
    void MyListener::onOrderBookChanged(const OrderBook&, const Messaging::SbeMessage message)
    {
        collectOrderBookChangeMark(message.templateId());
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    void MyListener::onWarning(const std::string& reason)
    {
        std::clog << "Warning occurred. Description: '" << reason << "'" << std::endl;
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    void MyListener::onError(ErrorCode::Enum code, const std::string& description)
    {
        std::clog << "Error occurred, errorCode = " << enumToString (code) << ". Description: '" << description << "'" << std::endl;
    }

    ONIXS_B3_UMDF_MD_HOTPATH
    void MyListener::collectMessageReceptionMark(const DataSource& dataSource)
    {
        ++marksCounter_;
        receiveMarks_[marksCounter_].messageTime = Timestamp::utcNow();

        const bool store = (0 == dataSource.packetMessageNumber) && (dataSource.origin == DataSource::Incremental) && !dataSource.cached;

        packetsCounter_ += store;
        receiveMarks_[marksCounter_ * store].receiveTime = dataSource.packetReceptionTime;

        InterruptDetector::instance().setDetected(packetsCounter_ >= packetsToProcess_ || marksCounter_ >= MaxLatenciesCount);
    }

    namespace
    {
        ONIXS_B3_UMDF_MD_COLDPATH
        Latency average(const Latencies& diffs)
        {
            const size_t sampleQty = diffs.size();

            assert(0 < sampleQty);

            return (std::accumulate(diffs.begin(), diffs.end(), Latency(0)) / sampleQty);
        }

        ONIXS_B3_UMDF_MD_COLDPATH
        Latency percentile(const Latencies& diffs, unsigned percent)
        {
            const size_t sampleQty = diffs.size();

            assert(0 < sampleQty);

            assert(50 <= percent && 100 > percent);

            const size_t multipliedIndex = sampleQty * percent;

            const size_t index = multipliedIndex / 100;

            return (0 == (multipliedIndex % 100) && 1 < sampleQty) ? (diffs[index] + diffs[index - 1]) / 2
                                                                   : (diffs[index]);
        }

        class Summary
        {
        public:
            ONIXS_B3_UMDF_MD_COLDPATH
            explicit Summary(const Latencies& latencies, Latency adjustment)
                : latencies_(latencies)
                , length_(latencies.size())
                , min_(latencies[0] - adjustment)
                , max_(*latencies.rbegin() - adjustment)
                , average_(average(latencies) - adjustment)
                , p50_(percentile(latencies, 50) - adjustment)
                , p95_(percentile(latencies, 95) - adjustment)
                , p99_(percentile(latencies, 99) - adjustment)
            {
                std::transform(latencies_.begin(), latencies_.end(), latencies_.begin(), [adjustment](Latency elem) { return elem - adjustment; });
            }


            ONIXS_B3_UMDF_MD_COLDPATH
            const Summary& dump(std::ostream& output, unsigned unitScale, const char* unitName) const
            {
                assert(0 < unitScale);

                const double realScale = static_cast<double>(unitScale);

                output << std::fixed << std::setprecision(3)
                       << "Data processing result (in " << unitName << "): " << std::endl
                       << "Minimal: " << (min_ / realScale) << std::endl
                       << "Median:  " << (p50_ / realScale) << std::endl
                       << "Mean:    " << (average_ / realScale) << std::endl
                       << "95%:     " << (p95_ / realScale) << std::endl
                       << "99%:     " << (p99_ / realScale) << std::endl
                       << "Maximal: " << (max_ / realScale) << std::endl
                       << "Samples: " << length_ << ". " << std::endl << std::endl;

                return *this;
            }

            ONIXS_B3_UMDF_MD_COLDPATH
            const Summary& histogram(std::ostream& output) const
            {
                std::vector<Latency> bins;
                const auto stride = static_cast<Latency>((p99_ - min_) / 10);
                for(Latency i = min_; i <= p99_; i += stride)
                    bins.push_back(i);

                std::vector<int> histogram(bins.size(), 0);

                for (Latency value : latencies_)
                {
                    auto it = std::upper_bound(bins.begin(), bins.end(), value);
                    const auto binIndex = std::distance(bins.begin(), --it);

                    histogram[binIndex]++;
                }

                const int maxCount = *std::max_element(histogram.begin(), histogram.end());

                output << "Histogram (nanoseconds):\n";

                const char dividerChar = '|';
                const char barChar = '*';

                std::string inf = "inf";
                const auto width = std::max(std::to_string(p99_).size(), inf.size());
                inf = (width > inf.size() ? std::string(" ", width - inf.size()) : "") + inf;

                for (size_t i = 1; i <= bins.size(); i++)
                {
                    Latency rangeStart = bins[i - 1];

                    const int percentage = (maxCount > 0) ? histogram[i - 1] * 100 / maxCount : 0;

                    std::cout << std::fixed << std::setprecision(2);

                    if (i < bins.size())
                    {
                        Latency rangeEnd = bins[i];
                        output
                            << "[" << std::setw(width) << std::right << rangeStart << " - " << std::setw(width) << std::right << rangeEnd << "): "
                            << std::setw(8) << std::right << histogram[i - 1] << ' ' << dividerChar
                            << std::string(percentage, barChar) << std::endl;
                    }
                    else
                        output
                            << "[" << std::setw(width) << std::right << rangeStart << " - " << inf << "): "
                            << std::setw(8) << std::right << histogram[i - 1] << ' ' << dividerChar
                            << std::string(percentage, barChar) << std::endl;
                }

                return *this;
            }

        private:
            Latencies latencies_;
            size_t length_;

            Latency min_;
            Latency max_;
            Latency average_;

            Latency p50_;
            Latency p95_;
            Latency p99_;
        };
    }

    ONIXS_B3_UMDF_MD_COLDPATH
    void MyListener::processLatencies() const
    {
        if (marksCounter_ == 0)
        {
            std::clog << "Nothing to process (latencies list is empty)." << std::endl;
            return;
        }

        Latencies messagingLatencies;
        Latencies orderMessageLatencies;
        Latencies deleteOrderMessageLatencies;
        Latencies massDeleteOrderMessageLatencies;

        std::for_each(receiveMarks_ + 1, receiveMarks_ + marksCounter_, [&](const Marks& marks)
        {
            if(marks.receiveTime != Timestamp())
                messagingLatencies.push_back((marks.messageTime - marks.receiveTime).ticks());

            switch (marks.messageType)
            {
                case Messaging::Order_MBO_50::TemplateId:
                    if(marks.bookTime != Timestamp()) orderMessageLatencies.push_back((marks.bookTime - marks.messageTime).ticks());
                    break;
                case Messaging::DeleteOrder_MBO_51::TemplateId:
                    if(marks.bookTime != Timestamp()) deleteOrderMessageLatencies.push_back((marks.bookTime - marks.messageTime).ticks());
                    break;
                case Messaging::MassDeleteOrders_MBO_52::TemplateId:
                    if(marks.bookTime != Timestamp()) massDeleteOrderMessageLatencies.push_back((marks.bookTime - marks.messageTime).ticks());
                    break;
            }
        });

        constexpr unsigned int nanosecondsInMicroseconds = 1000;
        const Latency adjustment = calculateAdjustment();

        {
            std::ofstream csvFile("results.csv");
            if(csvFile)
                std::copy(messagingLatencies.begin(), messagingLatencies.end(), std::ostream_iterator<Latency>(csvFile, "\n"));
        }

        {
            std::sort(messagingLatencies.begin(), messagingLatencies.end());

            std::cout << "Messaging" << std::endl;
            Summary(messagingLatencies, adjustment)
                .dump(std::cout, nanosecondsInMicroseconds, "microseconds")
                .histogram(std::cout);
            std::cout << std::endl;
        }

        if(!orderMessageLatencies.empty())
        {
            std::sort(orderMessageLatencies.begin(), orderMessageLatencies.end());

            std::clog << "Order_MBO_50" << std::endl;
            Summary(orderMessageLatencies, adjustment)
                .dump(std::cout, nanosecondsInMicroseconds, "microseconds")
                .histogram(std::cout);
            std::cout << std::endl;
        }

        if (!deleteOrderMessageLatencies.empty())
        {
            std::sort(deleteOrderMessageLatencies.begin(), deleteOrderMessageLatencies.end());

            std::clog << "DeleteOrder_MBO_51" << std::endl;
            Summary(deleteOrderMessageLatencies, adjustment)
                .dump(std::cout, nanosecondsInMicroseconds, "microseconds")
                .histogram(std::cout);
            std::cout << std::endl;
        }

        if (!massDeleteOrderMessageLatencies.empty())
        {
            std::sort(massDeleteOrderMessageLatencies.begin(), massDeleteOrderMessageLatencies.end());

            std::clog << "MassDeleteOrders_MBO_52" << std::endl;
            Summary(massDeleteOrderMessageLatencies, adjustment)
                .dump(std::cout, nanosecondsInMicroseconds, "microseconds")
                .histogram(std::cout);
            std::cout << std::endl;
        }
    }
}
//! [MyListenerCpp]
