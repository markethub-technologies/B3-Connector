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
#include <chrono>
#include <string>
#include <thread>

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

    // Hot path pipeline->worker: SPSC snapshot queue. No throw, no alloc, NO logging (logger is SPSC too).
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
    // -------------------------
    // Time helpers
    // -------------------------
    static uint64_t nowNsSystem() noexcept {
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
    }
    // -------------------------
    // Logging helpers (ONLY worker thread calls these; logger_ is SPSC)
    // -------------------------
    void logStartup(uint64_t nowNs) noexcept {
        telemetry::LogEvent e{};
        e.tsNs = nowNs;
        e.level = telemetry::LogLevel::Info;
        e.component = telemetry::Component::Worker;
        e.code = telemetry::Code::Startup;
        e.shard = static_cast<uint16_t>(shardId_);
        (void)logger_.try_publish(e);
    }

    void logShutdown(uint64_t nowNs) noexcept {
        telemetry::LogEvent e{};
        e.tsNs = nowNs;
        e.level = telemetry::LogLevel::Info;
        e.component = telemetry::Component::Worker;
        e.code = telemetry::Code::Shutdown;
        e.shard = static_cast<uint16_t>(shardId_);
        e.arg0 = published_.load(std::memory_order_relaxed);
        e.arg1 = dropped_.load(std::memory_order_relaxed);
        (void)logger_.try_publish(e);
    }

    void emitHealth(uint64_t nowNs,
                    uint64_t qsz,
                    uint64_t dEnq,
                    uint64_t dPub) noexcept
    {
        telemetry::LogEvent e{};
        e.tsNs = nowNs;
        e.level = telemetry::LogLevel::Health;
        e.component = telemetry::Component::Worker;
        e.code = telemetry::Code::HealthTick;
        e.shard = static_cast<uint16_t>(shardId_);
        e.arg0 = qsz;
        // pack: high32=deltaEnq, low32=deltaPub (trunc to 32 bits)
        e.arg1 = ((dEnq & 0xFFFFFFFFull) << 32) | (dPub & 0xFFFFFFFFull);
        (void)logger_.try_publish(e);
    }

    void emitDrops(uint64_t nowNs,
                   uint64_t deltaDrops,
                   uint64_t totalDrops) noexcept
    {
        telemetry::LogEvent e{};
        e.tsNs = nowNs;
        e.level = telemetry::LogLevel::Health;
        e.component = telemetry::Component::Worker;
        e.code = telemetry::Code::Drops;
        e.shard = static_cast<uint16_t>(shardId_);
        e.arg0 = deltaDrops; // drops in window
        e.arg1 = totalDrops; // total drops
        (void)logger_.try_publish(e);
    }

    void emitQueueSaturated(uint64_t nowNs,
                            uint64_t qsz,
                            uint64_t deltaDrops,
                            uint64_t totalDrops) noexcept
    {
        telemetry::LogEvent e{};
        e.tsNs = nowNs;
        e.level = telemetry::LogLevel::Health;
        e.component = telemetry::Component::Worker;
        e.code = telemetry::Code::QueueSaturated;
        e.shard = static_cast<uint16_t>(shardId_);
        e.arg0 = qsz;
        // pack: high32=deltaDrops, low32=totalDrops (trunc)
        e.arg1 = ((deltaDrops & 0xFFFFFFFFull) << 32) | (totalDrops & 0xFFFFFFFFull);
        (void)logger_.try_publish(e);
    }

    // Reuse Code::Drops but with different component to distinguish "logger queue drops"
    void emitLogDrops(uint64_t nowNs,
                      uint64_t deltaLogDrops,
                      uint64_t totalLogDrops) noexcept
    {
        telemetry::LogEvent e{};
        e.tsNs = nowNs;
        e.level = telemetry::LogLevel::Health;
        e.component = telemetry::Component::Publishing;
        e.code = telemetry::Code::Drops;
        e.shard = static_cast<uint16_t>(shardId_);
        e.arg0 = deltaLogDrops;
        e.arg1 = totalLogDrops;
        (void)logger_.try_publish(e);
    }

    void maybeLogHealthTick(uint64_t nowNs) noexcept {
        if (nowNs < nextHealthNs_) return;

        nextHealthNs_ = nowNs + kHealthEveryNs;

        const uint64_t enq  = enqueued_.load(std::memory_order_relaxed);
        const uint64_t pub  = published_.load(std::memory_order_relaxed);
        const uint64_t drop = dropped_.load(std::memory_order_relaxed);
        const uint64_t qsz  = static_cast<uint64_t>(queue_.size_approx());

        const uint64_t dEnq  = enq  - lastEnq_;
        const uint64_t dPub  = pub  - lastPub_;
        const uint64_t dDrop = drop - lastDrop_;

        lastEnq_  = enq;
        lastPub_  = pub;
        lastDrop_ = drop;

        emitHealth(nowNs, qsz, dEnq, dPub);

        if (dDrop > 0) {
            emitDrops(nowNs, dDrop, drop);
            emitQueueSaturated(nowNs, qsz, dDrop, drop);
        }

        const uint64_t logDrop = logger_.dropped();
        const uint64_t dLogDrop = logDrop - lastLogDrop_;
        lastLogDrop_ = logDrop;

        if (dLogDrop > 0) {
            emitLogDrops(nowNs, dLogDrop, logDrop);
        }
    }

    // -------------------------
    // Worker loop
    // -------------------------
    void run() noexcept {
    using namespace std::chrono_literals;

    OrdersSnapshot raw{};
    BookSnapshot   mbp{};
    std::string    outBuffer;
    outBuffer.reserve(512);

    uint64_t nowNs = nowNsSystem();
    nextHealthNs_ = nowNs + kHealthEveryNs;

    lastEnq_ = lastPub_ = lastDrop_ = 0;
    lastLogDrop_ = 0;

    logStartup(nowNs);

    auto publish_one = [&](const OrdersSnapshot& s) {
        aggregateMboWindowToMbpTopN(s, mbp);

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

        bool didWork = false;

        while (queue_.try_pop(raw)) {
            didWork = true;

            nowNs = raw.exchangeTsNs;

            publish_one(raw);
        }

        maybeLogHealthTick(nowNs);

        if (!didWork) {
            nowNs = nowNsSystem();
            std::this_thread::sleep_for(1ms);
        }
    }

    logShutdown(nowNs);
}

private:
    static constexpr uint64_t kHealthEveryNs = 5'000'000'000ull; // 5s

private:
    const uint32_t shardId_;

    // Snapshot queue: pipeline thread produces, worker thread consumes (SPSC)
    SnapshotQueueSpsc<OrdersSnapshot, kQueueCapacity> queue_;

    MdSnapshotMapper& mapper_;
    IMdPublisher& publisher_;

    // Logger: worker thread is the ONLY producer; logger thread consumes (SPSC)
    telemetry::SpdlogLogPublisher<kLogQueueCapacity> logger_;

    std::atomic<bool> running_{false};
    std::atomic<bool> drainOnStop_{true};
    std::thread thread_{};

    std::atomic<uint64_t> enqueued_{0};
    std::atomic<uint64_t> dropped_{0};
    std::atomic<uint64_t> published_{0};

    // Health tick state (only worker thread touches these)
    uint64_t nextHealthNs_{0};
    uint64_t lastEnq_{0};
    uint64_t lastPub_{0};
    uint64_t lastDrop_{0};

    // Logger drops state
    uint64_t lastLogDrop_{0};
};

} // namespace b3::md
