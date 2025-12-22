#pragma once

#include "MdPublishPipeline.hpp"
#include "../onixs/OnixsOrdersSnapshotBuilder.hpp"

#include <atomic>
#include <cstdint>

#include <OnixS/B3/MarketData/UMDF/OrderBook.h>

namespace b3::md {

class MarketDataEngine {
public:
    explicit MarketDataEngine(MdPublishPipeline& pipeline)
        : pipeline_(pipeline)
    {}

    // Vive en el thread del feed (listener OnixS).
    // Construye OrdersSnapshot (ventana MBO) y encola al pipeline.
    void onOrderBookUpdated(const ::OnixS::B3::MarketData::UMDF::OrderBook& orderBook) noexcept {
        OrdersSnapshot snapshot{};
        b3::md::onixs::buildOrdersSnapshotFromOnixsBook(orderBook, snapshot);

        if (!pipeline_.tryEnqueue(snapshot)) {
            drops_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // Overload para tests/fakes (IOrderBookView = MBP).
    // Copiamos niveles como "órdenes" (1 orden por precio) para poder usar la misma pipeline OrdersSnapshot.
    // Esto permite tests determinísticos sin OnixS.
    void onOrderBookUpdated(const IOrderBookView& book) noexcept {
        OrdersSnapshot snapshot{};
        snapshot.instrumentId = book.instrumentId();
        snapshot.exchangeTsNs = book.exchangeTsNs();

        // rptSeq/channelSeq quedan 0 en tests

        const uint32_t bidN = book.bidCount();
        const uint32_t askN = book.askCount();

        uint16_t writtenBid = 0;
        for (uint32_t i = 0; i < bidN && writtenBid < OrdersSnapshot::K; ++i) {
            const auto lv = book.bidLevel(i);
            // Level ya viene MBP (precio/cantidad)
            snapshot.bids[writtenBid].priceMantissa = lv.price;
            snapshot.bids[writtenBid].qty = lv.qty;
            ++writtenBid;
        }
        snapshot.bidCountRaw = writtenBid;
        snapshot.bidTruncated = (bidN > OrdersSnapshot::K) ? 1u : 0u;

        uint16_t writtenAsk = 0;
        for (uint32_t i = 0; i < askN && writtenAsk < OrdersSnapshot::K; ++i) {
            const auto lv = book.askLevel(i);
            snapshot.asks[writtenAsk].priceMantissa = lv.price;
            snapshot.asks[writtenAsk].qty = lv.qty;
            ++writtenAsk;
        }
        snapshot.askCountRaw = writtenAsk;
        snapshot.askTruncated = (askN > OrdersSnapshot::K) ? 1u : 0u;

        if (!pipeline_.tryEnqueue(snapshot)) {
            drops_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    uint64_t drops() const noexcept {
        return drops_.load(std::memory_order_relaxed);
    }

private:
    MdPublishPipeline& pipeline_;
    std::atomic<uint64_t> drops_{0};
};

} // namespace b3::md
