#pragma once
#include "SnapshotQueueSpsc.hpp"
#include "TopNBookSnapshot.hpp"
#include "MdSnapshotMapper.hpp"
#include "IMdPublisher.hpp"

#include <atomic>
#include <thread>
#include <string>

namespace b3::md {

class MdPublishWorker {
public:
    static constexpr size_t QUEUE_CAPACITY = 4096;

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
    bool try_enqueue(const TopNBookSnapshot10& s) noexcept {
        return queue_.try_push(s);
    }

    uint32_t queue_size_approx() const noexcept {
        return queue_.size_approx();
    }

private:
    void runLoop() {
        std::string outBuffer;
        TopNBookSnapshot10 s{};

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

    SnapshotQueueSpsc<TopNBookSnapshot10, QUEUE_CAPACITY> queue_;
    std::atomic<bool> running_{false};
    std::thread workerThread_;
};

} // namespace b3::md