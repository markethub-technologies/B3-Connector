#pragma once

#include "SnapshotQueueSpsc.hpp"
#include "BookSnapshot.hpp"
#include "OrdersSnapshot.hpp" 
#include "MboToMbpAggregator.hpp"

#include "../mapping/MdSnapshotMapper.hpp" // BookSnapshot -> bytes
#include "../publishing/IMdPublisher.hpp"
#include "../telemetry/SpdlogLogPublisher.hpp"
#include "../telemetry/LogEvent.hpp"

#include <atomic>
#include <thread>
#include <string>

namespace b3::md {

class MdPublishWorker final {
public:
    static constexpr size_t kQueueCapacity    = 4096;
    static constexpr size_t kLogQueueCapacity = 1024;

    MdPublishWorker(uint32_t shardId,
                    MdSnapshotMapper& mapper,
                    IMdPublisher& publisher)
        : shardId_(shardId)
        , mapper_(mapper)
        , publisher_(publisher)
    {}

    MdPublishWorker(const MdPublishWorker&) = delete;
    MdPublishWorker& operator=(const MdPublishWorker&) = delete;

    void start() {
        bool expected = false;
        if (!running_.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) {
            return; // idempotente
        }

        // Logger propio del worker (thread separado)
        logger_.start();

        drainOnStop_.store(true, std::memory_order_relaxed);
        thread_ = std::thread([this] { run(); });
    }

    void stop(bool drain = true) {
        drainOnStop_.store(drain, std::memory_order_relaxed);
        running_.store(false, std::memory_order_release);

        if (thread_.joinable()) {
            thread_.join();
        }

        // Drenar y detener logger al final
        logger_.stop();
    }

    // Hot path del pipeline->worker: SPSC, no throw, no alloc.
    bool tryEnqueue(const OrdersSnapshot& snapshot) noexcept {
        if (queue_.try_push(snapshot)) {
            enqueued_.fetch_add(1, std::memory_order_relaxed);
            return true;
        }

        dropped_.fetch_add(1, std::memory_order_relaxed);
        return false;
    }

    uint64_t enqueued()  const noexcept { return enqueued_.load(std::memory_order_relaxed); }
    uint64_t dropped()   const noexcept { return dropped_.load(std::memory_order_relaxed); }
    uint64_t published() const noexcept { return published_.load(std::memory_order_relaxed); }

private:
    void run() noexcept {
        OrdersSnapshot raw{};
        BookSnapshot   mbp{};        // Top-N agregado (MBP)
        std::string    outBuffer;
        outBuffer.reserve(512);

        auto publish_one = [&](const OrdersSnapshot& s) {
            // 1) Agregar MBO window -> MBP Top-N
            aggregateMboWindowToMbpTopN(s, mbp);

            // 2) Serializar y publicar
            outBuffer.clear();
            mapper_.mapAndSerialize(mbp, outBuffer);

            publisher_.publish(
                "b3.md.book",
                reinterpret_cast<const uint8_t*>(outBuffer.data()),
                outBuffer.size());

            published_.fetch_add(1, std::memory_order_relaxed);
        };

        while (running_.load(std::memory_order_acquire) ||
               (drainOnStop_.load(std::memory_order_relaxed) && queue_.size_approx() > 0)) {

            if (!queue_.try_pop(raw)) {
                std::this_thread::yield();
                continue;
            }

            try {
                publish_one(raw);
            }
            catch (...) {
                telemetry::LogEvent e{};
                e.level        = telemetry::LogLevel::Error;
                e.component    = telemetry::Component::Worker;
                e.code         = telemetry::Code::WorkerException;
                e.instrumentId = raw.instrumentId;
                e.shard        = shardId_;
                logger_.try_publish(e);
            }
        }

        // Drenado final defensivo
        while (drainOnStop_.load(std::memory_order_relaxed) && queue_.try_pop(raw)) {
            try {
                publish_one(raw);
            }
            catch (...) {
                telemetry::LogEvent e{};
                e.level        = telemetry::LogLevel::Error;
                e.component    = telemetry::Component::Worker;
                e.code         = telemetry::Code::WorkerException;
                e.instrumentId = raw.instrumentId;
                e.shard        = shardId_;
                logger_.try_publish(e);
            }
        }
    }

private:
    const uint32_t shardId_;

    // OJO: ahora encolamos OrdersSnapshot (MBO window), no BookSnapshot
    SnapshotQueueSpsc<OrdersSnapshot, kQueueCapacity> queue_;

    MdSnapshotMapper& mapper_;
    IMdPublisher& publisher_;

    telemetry::SpdlogLogPublisher<kLogQueueCapacity> logger_;

    std::atomic<bool> running_{false};
    std::atomic<bool> drainOnStop_{true};
    std::thread thread_;

    std::atomic<uint64_t> enqueued_{0};
    std::atomic<uint64_t> dropped_{0};
    std::atomic<uint64_t> published_{0};
};

} // namespace b3::md
