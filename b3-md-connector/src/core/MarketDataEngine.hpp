#pragma once

#include "MdPublishPipeline.hpp"
#include "IOrderBookView.hpp"
#include "OrdersSnapshot.hpp"

#include "../onixs/OnixsOrdersSnapshotBuilder.hpp"

#include <atomic>
#include <cstdint>

#include <OnixS/B3/MarketData/UMDF/OrderBook.h>

namespace b3::md {

class MarketDataEngine final {
public:
    explicit MarketDataEngine(MdPublishPipeline& pipeline)
        : pipeline_(pipeline)
    {}

    // Vive en el thread del feed (listener OnixS).
    // Construye OrdersSnapshot (ventana MBO) y encola al pipeline.
    void onOrderBookUpdated(const ::OnixS::B3::MarketData::UMDF::OrderBook& orderBook) noexcept {
        OrdersSnapshot snapshot{};
        b3::md::onixs::OnixsOrdersSnapshotBuilder::buildFromBook(orderBook, snapshot);

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
