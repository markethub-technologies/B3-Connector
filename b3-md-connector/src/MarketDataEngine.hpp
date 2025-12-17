#pragma once
#include "MdPublishPipeline.hpp"
#include "BookSnapshotBuilder.hpp"
#include <atomic>
#include <cstdint>

namespace b3::md {

// Entry point: recibe callback (vía adapter) y encola snapshots.
// No bloquea: si la cola está llena, drop + métrica.
class MarketDataEngine {
public:
    MarketDataEngine(MdPublishPipeline& pipeline, uint32_t topN)
        : pipeline_(pipeline), topN_(topN) {}

    void onOrderBookUpdated(const IOrderBookView& book) noexcept {
        auto snapshot = buildSnapshot(book, topN_);
        if (!pipeline_.enqueue(snapshot)) {
            drops_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    uint64_t drops() const noexcept {
        return drops_.load(std::memory_order_relaxed);
    }

private:
    MdPublishPipeline& pipeline_;
    uint32_t topN_;
    std::atomic<uint64_t> drops_{0};
};

} // namespace b3::md
