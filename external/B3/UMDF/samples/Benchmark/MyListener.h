#pragma once
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

//! [MyListenerH]
#include <vector>

#include <OnixS/B3/MarketData/UMDF/ErrorListener.h>
#include <OnixS/B3/MarketData/UMDF/Messaging.h>
#include <OnixS/B3/MarketData/UMDF/MessageListener.h>
#include <OnixS/B3/MarketData/UMDF/WarningListener.h>
#include <OnixS/B3/MarketData/UMDF/OrderBookListener.h>
#include <OnixS/B3/MarketData/UMDF/Handler.h>

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

namespace Sample
{

    using namespace OnixS::B3::MarketData::UMDF;

    class Allocator
    {
    public:
        Allocator(size_t size);
        ~Allocator();

        void* allocate(size_t size);

        template <typename T>
        T* allocate(size_t n)
        {
            return static_cast<T*>(allocate(sizeof(T) * n));
        }

    private:
        void* init(size_t size);
        void fini(void* ptr);

        static void throwNoHugePage();
        static void throwAllocatorExhausted();

        const size_t size_;
        void* const chunk_;
        void* ptr_;
        size_t available_;
    };

    struct alignas(64) Marks
    {
        Timestamp receiveTime;
        Timestamp messageTime;
        Messaging::MessageTemplateId messageType = 0;
        Timestamp bookTime;
    };

    typedef unsigned long long Latency;
    typedef std::vector<Latency> Latencies;

    class MyListener :
        public MessageListener,
        public OrderBookListener,
        public WarningListener,
        public ErrorListener
    {
    public:
        /// Constructor
        MyListener( size_t packetsToProcess);

        void onNews_5(const Messaging::News_5, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onClosingPrice_17(const Messaging::ClosingPrice_17, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onQuantityBand_21(const Messaging::QuantityBand_21, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onPriceBand_22(const Messaging::PriceBand_22, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onOpeningPrice_15(const Messaging::OpeningPrice_15, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onTheoreticalOpeningPrice_16(const Messaging::TheoreticalOpeningPrice_16, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onAuctionImbalance_19(const Messaging::AuctionImbalance_19, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onHighPrice_24(const Messaging::HighPrice_24, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onLowPrice_25(const Messaging::LowPrice_25, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onLastTradePrice_27(const Messaging::LastTradePrice_27, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onSettlementPrice_28(const Messaging::SettlementPrice_28, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onOpenInterest_29(const Messaging::OpenInterest_29, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onOrder_MBO_50(const Messaging::Order_MBO_50, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onDeleteOrder_MBO_51(const Messaging::DeleteOrder_MBO_51, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onMassDeleteOrders_MBO_52(const Messaging::MassDeleteOrders_MBO_52, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onTrade_53(const Messaging::Trade_53, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onForwardTrade_54(const Messaging::ForwardTrade_54, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onExecutionSummary_55(const Messaging::ExecutionSummary_55, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onExecutionStatistics_56(const Messaging::ExecutionStatistics_56, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;
        void onTradeBust_57(const Messaging::TradeBust_57, const DataSource&) ONIXS_B3_UMDF_MD_FINAL;

        /// Inherited from OrderBookListener
        /// Is called when the book is changed within it's depth, when Order_MBO_50, DeleteOrder_MBO_51 or MassDeleteOrders_MBO_52 are received.
        void onOrderBookChanged(const OrderBook& book, const Messaging::SbeMessage message) ONIXS_B3_UMDF_MD_FINAL;

        void onOrderBookUpdated(const OrderBook&) ONIXS_B3_UMDF_MD_FINAL {}
        void onOrderBookOutOfDate(const OrderBook&) ONIXS_B3_UMDF_MD_FINAL {}

        void collectOrderBookChangeMark(Messaging::MessageTemplateId templateId);

        /// Inherited from Warning Listener
        /// Is called when the Warning condition is detected
        void onWarning(const std::string& reason) ONIXS_B3_UMDF_MD_FINAL;

        /// Inherited from Error Listener
        /// Notifications about errors
        void onError(ErrorCode::Enum code, const std::string& description) ONIXS_B3_UMDF_MD_FINAL;

        /// Calculate and print latency statistics.
        void processLatencies() const;

    private:
        static constexpr size_t MaxLatenciesCount = 1000000;

        /// Add latency to list of all messaging measurement latencies.
        void collectMessageReceptionMark(const DataSource& dataSource);
        static Latency calculateAdjustment();

        Allocator allocator_;
        Marks* const receiveMarks_;

        const size_t packetsToProcess_;
        size_t marksCounter_ = 0;
        size_t packetsCounter_ = 0;
    };
}
//! [MyListenerH]

