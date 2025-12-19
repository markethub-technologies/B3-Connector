#pragma once
#include "SnapshotQueueSpsc.hpp"
#include "BookSnapshot.hpp"
#include "../mapping/MdSnapshotMapper.hpp"
#include "../publishing/IMdPublisher.hpp"
#include "../telemetry/SpdlogLogPublisher.hpp"
#include <atomic>
#include <thread>
#include <string>

namespace b3::md {

class MdPublishWorker {
public:
    static constexpr size_t QUEUE_CAPACITY = 4096; 
                //tamaño estimado (10 niveles * 16) + ~32 = ~192 bytes
                //4096 * 192 ≈ 786,432 bytes ≈ 768 KB  (por worker)

    MdPublishWorker(MdSnapshotMapper& mapper,
                    IMdPublisher& publisher,
                    std::string_view topic)
        : mapper_(mapper),
          publisher_(publisher),
          topic_(topic) {}

    ~MdPublishWorker() {
        stop();
    }

    void start() {
        bool expected = false;
        if (!running_.compare_exchange_strong(expected, true)) return;
        workerThread_ = std::thread([this] { runLoop(); });
    }

    void stop() {
        bool expected = true;
        if (!running_.compare_exchange_strong(expected, false)) return;
        if (workerThread_.joinable())
            workerThread_.join();
    }

    // Producer side
    bool try_enqueue(const BookSnapshot& s) noexcept {
        return queue_.try_push(s);
    }

    uint32_t queue_size_approx() const noexcept {
        return queue_.size_approx();
    }

private:
    void runLoop() {
        std::string outBuffer;
        BookSnapshot s{};

        while (running_.load(std::memory_order_acquire) ||
               queue_.size_approx() > 0) {

            if (queue_.try_pop(s)) {
                mapper_.mapAndSerialize(s, outBuffer);
                publisher_.publish(
                    topic_,
                    reinterpret_cast<const uint8_t*>(outBuffer.data()),
                    outBuffer.size()
                );
            } else {
                std::this_thread::yield();
            }
        }
    }

private:
    MdSnapshotMapper& mapper_;
    IMdPublisher& publisher_;
    std::string topic_;

    SnapshotQueueSpsc<BookSnapshot, QUEUE_CAPACITY> queue_;
    std::atomic<bool> running_{false};
    std::thread workerThread_;
};

} // namespace b3::md