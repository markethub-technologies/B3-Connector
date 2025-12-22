#pragma once

#include "MdPublishWorker.hpp"
#include "OrdersSnapshot.hpp"

#include <cstdint>
#include <memory>
#include <vector>
#include <atomic>
#include <stdexcept>

namespace b3::md {

// Pipeline = orquestador de sharding + lifecycle de workers.
// NO crea threads en ctor. NO conoce IO. NO conoce OnixS.
// Enqueue único punto de entrada (hot path friendly).
class MdPublishPipeline final {
public:
    explicit MdPublishPipeline(std::vector<std::unique_ptr<MdPublishWorker>> workers)
        : workers_(std::move(workers))
    {
        if (workers_.empty()) {
            throw std::invalid_argument("MdPublishPipeline: workers empty");
        }
    }

    MdPublishPipeline(const MdPublishPipeline&) = delete;
    MdPublishPipeline& operator=(const MdPublishPipeline&) = delete;

    void start() {
        bool expected = false;
        if (!started_.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) {
            return; // idempotente
        }
        for (auto& w : workers_) {
            w->start();
        }
    }

    void stop(bool drain = true) {
        bool expected = true;
        if (!started_.compare_exchange_strong(expected, false, std::memory_order_acq_rel)) {
            return; // idempotente
        }
        for (auto& w : workers_) {
            w->stop(drain);
        }
    }

    // Hot path: no throw, no alloc.
    // Devuelve false si se dropeó (cola llena).
    bool tryEnqueue(const OrdersSnapshot& snapshot) noexcept {
        const uint32_t shard = shardFor(snapshot.instrumentId);
        return workers_[shard]->tryEnqueue(snapshot);
    }

    uint32_t shardCount() const noexcept {
        return static_cast<uint32_t>(workers_.size());
    }

private:
    // Hash multiplicativo para mejorar distribución si instrumentId tiene patrones.
    static constexpr uint64_t kKnuth = 11400714819323198485ull;

    uint32_t shardFor(uint64_t instrumentId) const noexcept {
        const uint64_t mixed = instrumentId * kKnuth;
        return static_cast<uint32_t>(mixed % workers_.size());
    }

private:
    std::vector<std::unique_ptr<MdPublishWorker>> workers_;
    std::atomic<bool> started_{false};
};

} // namespace b3::md
