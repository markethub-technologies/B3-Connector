#pragma once
#include "BookSnapshotBuilder.hpp"
#include "MdPublishPipeline.hpp"   // tu pipeline actual
#include <atomic>
#include <cstdint>

namespace b3::md {

class MarketDataEngine {
public:
    explicit MarketDataEngine(MdPublishPipeline& pipeline)
        : pipeline_(pipeline) {}

    void onOrderBookUpdated(const IOrderBookView& book) noexcept {
        auto snap = buildSnapshot(book);
        if (!pipeline_.tryEnqueue(snap)) {
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
