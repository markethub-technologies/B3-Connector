#pragma once
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace b3::md::telemetry {

template <typename T, size_t Capacity>
class LogQueueSpsc {
    static_assert(Capacity >= 2, "Capacity must be >= 2");
    static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

public:
    bool try_push(const T& v) noexcept {
        const uint32_t t = tail_.load(std::memory_order_relaxed);
        const uint32_t next = inc(t);
        if (next == head_.load(std::memory_order_acquire)) return false; // full
        buffer_[t] = v;
        tail_.store(next, std::memory_order_release);
        return true;
    }

    bool try_pop(T& out) noexcept {
        const uint32_t h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire)) return false; // empty
        out = buffer_[h];
        head_.store(inc(h), std::memory_order_release);
        return true;
    }

private:
    static constexpr uint32_t inc(uint32_t v) noexcept {
        v++;
        if (v >= Capacity) v = 0;
        return v;
    }

    alignas(64) T buffer_[Capacity]{};
    alignas(64) std::atomic<uint32_t> head_{0};
    alignas(64) std::atomic<uint32_t> tail_{0};
};

} // namespace b3::md::telemetry
