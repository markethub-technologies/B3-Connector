// src/common/MpscPodQueue.h
#pragma once

#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <mutex>
#include <utility>
#include <vector>

/**
 * Simple bounded MPSC queue for POD-like event structs.
 *
 * Goals:
 *  - Multi-producer safe (callbacks can be invoked concurrently)
 *  - Single consumer (one processing thread)
 *  - Bounded capacity to control memory usage and have explicit overflow behavior
 *  - Fast producers: short critical section + notify
 *
 * Notes:
 *  - This queue preserves FIFO order of enqueued events.
 *  - Overflow policy: try_enqueue() returns false if full (caller decides: drop + metric/log).
 */
template <typename T>
class MpscPodQueue final
{
public:
    explicit MpscPodQueue(std::size_t capacity)
        : capacity_(capacity)
    {
        if (capacity_ == 0)
            capacity_ = 1;
    }

    MpscPodQueue(const MpscPodQueue&) = delete;
    MpscPodQueue& operator=(const MpscPodQueue&) = delete;

    std::size_t capacity() const noexcept { return capacity_; }

    std::size_t sizeApprox() const noexcept
    {
        std::lock_guard<std::mutex> lk(mtx_);
        return q_.size();
    }

    /**
     * Non-blocking enqueue.
     * @return false if queue is full (caller should drop and count).
     */
    bool try_enqueue(T&& item)
    {
        {
            std::lock_guard<std::mutex> lk(mtx_);
            if (q_.size() >= capacity_)
                return false;

            q_.emplace_back(std::move(item));
        }
        cv_.notify_one();
        return true;
    }

    bool try_enqueue(const T& item)
    {
        {
            std::lock_guard<std::mutex> lk(mtx_);
            if (q_.size() >= capacity_)
                return false;

            q_.emplace_back(item);
        }
        cv_.notify_one();
        return true;
    }

    /**
     * Consumer API.
     * Blocks until an item is available or stop() is called.
     * @return false when stopped and queue drained.
     */
    bool wait_dequeue(T& out)
    {
        std::unique_lock<std::mutex> lk(mtx_);
        cv_.wait(lk, [&] { return stop_ || !q_.empty(); });

        if (q_.empty())
            return false; // stopped + drained

        out = std::move(q_.front());
        q_.pop_front();
        return true;
    }

    /**
     * Stop the queue: unblocks the consumer.
     * Consumer will continue draining until empty, then wait_dequeue returns false.
     */
    void stop()
    {
        {
            std::lock_guard<std::mutex> lk(mtx_);
            stop_ = true;
        }
        cv_.notify_all();
    }

    /**
     * Clear all items (typically on shutdown without drain).
     */
    void clear()
    {
        std::lock_guard<std::mutex> lk(mtx_);
        q_.clear();
    }

private:
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::deque<T> q_;
    std::size_t capacity_;
    bool stop_ = false;
};
