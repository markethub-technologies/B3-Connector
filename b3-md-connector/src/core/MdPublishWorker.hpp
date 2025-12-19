#pragma once

#include "SnapshotQueueSpsc.hpp"
#include "BookSnapshot.hpp"

#include "../mapping/MdSnapshotMapper.hpp"
#include "../publishing/IMdPublisher.hpp"
#include "../telemetry/SpdlogLogPublisher.hpp"
#include "../telemetry/LogEvent.hpp"

#include <atomic>
#include <thread>
#include <string>
#include <cstdint>

namespace b3::md {

class MdPublishWorker {
public:
    static constexpr size_t QUEUE_CAPACITY = 4096;
                //tamaño estimado (10 niveles * 16) + ~32 = ~192 bytes
                //4096 * 192 ≈ 786,432 bytes ≈ 768 KB  (por worker)

    MdPublishWorker(uint32_t shard,
                    MdSnapshotMapper& mapper,
                    IMdPublisher& publisher,
                    std::string_view topic)
        : shard_(shard)
        , mapper_(mapper)
        , publisher_(publisher)
        , topic_(topic)
    {}

    ~MdPublishWorker() {
        stop();
    }

    // Producer-side API (single producer): called by pipeline/engine thread(s)
    bool try_enqueue(const BookSnapshot& s) noexcept {
        const bool ok = queue_.try_push(s);
        if (!ok) {
            snapshotsDropped_.fetch_add(1, std::memory_order_relaxed);
        }
        return ok;
    }

    void start() {
        const bool wasRunning = running_.exchange(true, std::memory_order_acq_rel);
        if (wasRunning) return;

        logger_.start();
        log_info(telemetry::Code::Startup);

        workerThread_ = std::thread([this] { run(); });
    }

    void stop() {
        const bool wasRunning = running_.exchange(false, std::memory_order_acq_rel);
        if (!wasRunning) return;

        if (workerThread_.joinable()) {
            workerThread_.join();
        }

        log_info(telemetry::Code::Shutdown);
        logger_.stop();
    }

    // --- counters (para health/tests más adelante) ---
    uint64_t snapshots_dropped() const noexcept {
        return snapshotsDropped_.load(std::memory_order_relaxed);
    }

    uint64_t published_total() const noexcept {
        return publishedTotal_.load(std::memory_order_relaxed);
    }

    uint64_t log_dropped() const noexcept {
        return logger_.dropped();
    }

private:
    void run() noexcept {
        BookSnapshot s{};
        std::string outBuffer;
        outBuffer.reserve(256); // buffer reutilizable (tamaño conservador)

        // drenar mientras esté corriendo o queden items (si tenés size_approx())
        while (running_.load(std::memory_order_acquire) || queue_.size_approx() > 0) {
            if (!queue_.try_pop(s)) {
                std::this_thread::yield();
                continue;
            }

            outBuffer.clear();
            mapper_.mapAndSerialize(s, outBuffer);

            publisher_.publish(
                topic_,
                reinterpret_cast<const uint8_t*>(outBuffer.data()),
                outBuffer.size()
            );

            publishedTotal_.fetch_add(1, std::memory_order_relaxed);
        }
    }

    void log_info(telemetry::Code code, uint64_t arg0 = 0, uint64_t arg1 = 0) noexcept {
        telemetry::LogEvent e{};
        e.level = telemetry::LogLevel::Info;
        e.component = telemetry::Component::Worker;
        e.code = code;
        e.shard = shard_;
        e.arg0 = arg0;
        e.arg1 = arg1;
        logger_.try_publish(e); // si falla, el logger incrementa dropped()
    }

private:
    uint16_t shard_{0};

    MdSnapshotMapper& mapper_;
    IMdPublisher& publisher_;
    std::string topic_;

    SnapshotQueueSpsc<BookSnapshot, QUEUE_CAPACITY> queue_;

    static constexpr size_t LOG_QUEUE_CAPACITY = 4096;
    telemetry::SpdlogLogPublisher<LOG_QUEUE_CAPACITY> logger_;

    std::atomic<bool> running_{false};
    std::thread workerThread_;

    std::atomic<uint64_t> snapshotsDropped_{0};
    std::atomic<uint64_t> publishedTotal_{0};
};

} // namespace b3::md
