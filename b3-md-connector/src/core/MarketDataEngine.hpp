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
    explicit MarketDataEngine(MdPublishPipeline &pipeline) noexcept : pipeline_(pipeline) {}

    // Strict gate opcional:
    // - si lo seteás: NO publica hasta que *ready == true
    // - si no lo seteás: publica siempre (modo legacy / tests)
    void setRegistryReadyFlag(const std::atomic<bool> *ready) noexcept { registryReady_ = ready; }

    void onOrderBookUpdated(const ::OnixS::B3::MarketData::UMDF::OrderBook &book,
                            uint64_t nowNs) noexcept {
      // Strict gating
      if (registryReady_ && !registryReady_->load(std::memory_order_acquire)) {
        gatedDrops_.fetch_add(1, std::memory_order_relaxed);
        return;
      }

      OrdersSnapshot snapshot{};
      b3::md::onixs::OnixsOrdersSnapshotBuilder::buildFromBook(book, nowNs, snapshot);

      if (!pipeline_.tryEnqueue(snapshot))
        drops_.fetch_add(1, std::memory_order_relaxed);
    }

    uint64_t drops() const noexcept { return drops_.load(std::memory_order_relaxed); }
    uint64_t gatedDrops() const noexcept { return gatedDrops_.load(std::memory_order_relaxed); }

   private:
    MdPublishPipeline &pipeline_;
    const std::atomic<bool> *registryReady_{nullptr};

    std::atomic<uint64_t> drops_{0};
    std::atomic<uint64_t> gatedDrops_{0};
  };

} // namespace b3::md
