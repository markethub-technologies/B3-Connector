#pragma once

#include "SnapshotQueueSpsc.hpp"
#include "BookSnapshot.hpp"
#include "../mapping/MdSnapshotMapper.hpp"
#include "../publishing/IMdPublisher.hpp"
#include "../telemetry/ILogSink.hpp"
#include "../telemetry/LogEvent.hpp"

#include <atomic>
#include <thread>
#include <chrono>

namespace b3::md {

class MdPublishWorker final {
public:
    MdPublishWorker(uint32_t shardId,
                    MdSnapshotMapper& mapper,
                    IMdPublisher& publisher,
                    telemetry::ILogSink& logger)
        : shardId_(shardId)
        , mapper_(mapper)
        , publisher_(publisher)
        , logger_(logger)
    {}

    MdPublishWorker(const MdPublishWorker&) = delete;
    MdPublishWorker& operator=(const MdPublishWorker&) = delete;

    void start() {
        bool expected = false;
        if (!running_.compare_exchange_strong(expected, true,
                                              std::memory_order_acq_rel)) {
            return; // idempotente
        }

        drainOnStop_.store(true, std::memory_order_relaxed);
        thread_ = std::thread([this] { run(); });
    }

    void stop(bool drain = true) {
        drainOnStop_.store(drain, std::memory_order_relaxed);
        running_.store(false, std::memory_order_release);

        if (thread_.joinable()) {
            thread_.join();
        }
    }

    // Hot path: SPSC, no throw, no alloc.
    bool tryEnqueue(const BookSnapshot& snapshot) noexcept {
        if (queue_.try_push(snapshot)) {
            ++enqueued_;
            return true;
        }

        ++dropped_;
        return false;
    }

    uint64_t enqueued() const noexcept { return enqueued_.load(); }
    uint64_t dropped()  const noexcept { return dropped_.load(); }
    uint64_t published() const noexcept { return published_.load(); }

private:
    void run() {
        BookSnapshot snapshot{};
        std::string outBuffer;
        outBuffer.reserve(512); // evita reallocs

        while (running_.load(std::memory_order_acquire) ||
               (drainOnStop_.load(std::memory_order_relaxed) &&
                queue_.size_approx() > 0)) {

            if (!queue_.try_pop(snapshot)) {
                // worker idle: no busy spin agresivo
                std::this_thread::yield();
                continue;
            }

            try {
                outBuffer.clear();
                mapper_.mapAndSerialize(snapshot, outBuffer);
                publisher_.publish("b3.md.book",
                                   reinterpret_cast<const uint8_t*>(outBuffer.data()),
                                   outBuffer.size());
                ++published_;
            }
            catch (...) {
                // Borde defensivo: el worker nunca muere
                telemetry::LogEvent e{};
                e.level = telemetry::LogLevel::Error;
                e.component = telemetry::Component::Publishing;   // enum
                e.code = telemetry::Code::WorkerException;         // enum
                e.instrumentId = snapshot.instrumentId;
                e.shard = shardId_;
                logger_.publish(e);
                //e.arg0 = static_cast<uint64_t>(telemetry::Stage::Publish); // info adicional si hace falta
                // e.arg1 = 0; /                                               // info adicional si hace falta
            }
        }

        // Drenado final defensivo (por si size_approx falló)
        while (drainOnStop_.load(std::memory_order_relaxed) &&
               queue_.try_pop(snapshot)) {

            outBuffer.clear();
            mapper_.mapAndSerialize(snapshot, outBuffer);
            publisher_.publish("b3.md.book",
                               reinterpret_cast<const uint8_t*>(outBuffer.data()),
                               outBuffer.size());
            ++published_;
        }
    }

private:
    static constexpr size_t kQueueCapacity = 4096;

    const uint32_t shardId_;

    SnapshotQueueSpsc<BookSnapshot, kQueueCapacity> queue_;

    MdSnapshotMapper& mapper_;
    IMdPublisher& publisher_;
    telemetry::ILogSink& logger_;

    std::atomic<bool> running_{false};
    std::atomic<bool> drainOnStop_{true};

    std::thread thread_;

    std::atomic<uint64_t> enqueued_{0};
    std::atomic<uint64_t> dropped_{0};
    std::atomic<uint64_t> published_{0};
};

} // namespace b3::md
