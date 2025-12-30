// ===== OPTIONAL GATING: b3-md-connector/src/core/MarketDataEngine.hpp =====
#pragma once

#include "MdPublishPipeline.hpp"
#include "OrdersSnapshot.hpp"
#include "../onixs/OnixsOrdersSnapshotBuilder.hpp"

#include <atomic>
#include <cstdint>

#include <OnixS/B3/MarketData/UMDF/OrderBook.h>

namespace b3::md {

  class MarketDataEngine final {
   public:
    explicit MarketDataEngine(MdPublishPipeline &pipeline) : pipeline_(pipeline) {}

    // Set once during wiring
    void setRegistryReadyFlag(const std::atomic<bool> *ready) noexcept { registryReady_ = ready; }

    void onOrderBookUpdated(const ::OnixS::B3::MarketData::UMDF::OrderBook &orderBook,
                            uint64_t nowNs) noexcept {
      // STRICT prod mode: don't enqueue anything until registry is ready.
      // If you prefer fallback topics during warmup, remove this block.
      if (registryReady_ && !registryReady_->load(std::memory_order_acquire)) {
        warmupDrops_.fetch_add(1, std::memory_order_relaxed);
        return;
      }

      OrdersSnapshot snapshot{};
      b3::md::onixs::OnixsOrdersSnapshotBuilder::buildFromBook(orderBook, nowNs, snapshot);

      if (!pipeline_.tryEnqueue(snapshot)) {
        drops_.fetch_add(1, std::memory_order_relaxed);
      }
    }

    uint64_t drops() const noexcept { return drops_.load(std::memory_order_relaxed); }
    uint64_t warmupDrops() const noexcept { return warmupDrops_.load(std::memory_order_relaxed); }

   private:
    MdPublishPipeline &pipeline_;
    const std::atomic<bool> *registryReady_{nullptr};

    std::atomic<uint64_t> drops_{0};
    std::atomic<uint64_t> warmupDrops_{0};
  };

} // namespace b3::md
