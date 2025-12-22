#pragma once
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace b3::md {

// FIFO SPSC ring buffer.
// Producer: 1 thread (pipeline/callback)
// Consumer: 1 thread (worker)
template <typename T, size_t CapacityPow2>
class SnapshotQueueSpsc {
    static_assert((CapacityPow2 & (CapacityPow2 - 1)) == 0, "Capacity must be power of two");

public:
    SnapshotQueueSpsc()
        : buffer_(std::make_unique<T[]>(CapacityPow2))
    {}

    bool try_push(const T& v) noexcept {
        const uint32_t t = tail_.load(std::memory_order_relaxed);
        const uint32_t h = head_.load(std::memory_order_acquire);

        if ((t - h) >= CapacityPow2) return false; // full

        buffer_[t & (CapacityPow2 - 1)] = v;
        tail_.store(t + 1, std::memory_order_release);
        return true;
    }

    bool try_pop(T& out) noexcept {
        const uint32_t h = head_.load(std::memory_order_relaxed);
        const uint32_t t = tail_.load(std::memory_order_acquire);

        if (h == t) return false; // empty

        out = buffer_[h & (CapacityPow2 - 1)];
        head_.store(h + 1, std::memory_order_release);
        return true;
    }

    uint32_t size_approx() const noexcept {
        const uint32_t h = head_.load(std::memory_order_acquire);
        const uint32_t t = tail_.load(std::memory_order_acquire);
        return t - h;
    }

private:
    alignas(64) std::atomic<uint32_t> head_{0};
    alignas(64) std::atomic<uint32_t> tail_{0};

    std::unique_ptr<T[]> buffer_;
};

} // namespace b3::md
