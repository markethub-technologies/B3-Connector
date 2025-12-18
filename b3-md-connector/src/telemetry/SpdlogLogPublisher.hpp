#pragma once
#include "LogEvent.hpp"
#include "LogQueueSpsc.hpp"

#include <atomic>
#include <chrono>
#include <thread>

#include <spdlog/spdlog.h>

namespace b3::md::telemetry {

template <size_t Capacity>
class SpdlogLogPublisher {
public:
    SpdlogLogPublisher() = default;

    // Producer API (SPSC): call only from ONE producer thread (owner)
    bool try_publish(const LogEvent& e) noexcept {
        if (!queue_.try_push(e)) {
            dropped_.fetch_add(1, std::memory_order_relaxed);
            return false;
        }
        return true;
    }

    void start() {
        running_.store(true, std::memory_order_release);
        thread_ = std::thread([this] { this->run(); });
    }

    void stop() {
        running_.store(false, std::memory_order_release);
        if (thread_.joinable()) thread_.join();
    }

    uint64_t dropped() const noexcept {
        return dropped_.load(std::memory_order_relaxed);
    }

private:
    void run() noexcept {
        using namespace std::chrono_literals;

        auto nextDropReport = std::chrono::steady_clock::now() + 5s;
        uint64_t lastDropped = 0;

        LogEvent e{};
        while (running_.load(std::memory_order_acquire)) {
            bool didWork = false;

            while (queue_.try_pop(e)) {
                didWork = true;
                emit_to_spdlog(e);
            }

            const auto now = std::chrono::steady_clock::now();
            if (now >= nextDropReport) {
                const uint64_t d = dropped_.load(std::memory_order_relaxed);
                const uint64_t delta = d - lastDropped;
                lastDropped = d;
                nextDropReport = now + 5s;

                if (delta > 0) {
                    spdlog::warn("[telemetry] log queue saturated: dropped={} in last 5s", delta);
                }
            }

            if (!didWork) {
                std::this_thread::sleep_for(1ms);
            }
        }

        // Drain remaining events on shutdown
        while (queue_.try_pop(e)) {
            emit_to_spdlog(e);
        }
    }

    static const char* to_component(Component c) noexcept {
        switch (c) {
            case Component::Core:       return "core";
            case Component::Pipeline:   return "pipeline";
            case Component::Worker:     return "worker";
            case Component::Mapping:    return "mapping";
            case Component::Publishing: return "publishing";
            case Component::Adapter:    return "adapter";
            default:                    return "unknown";
        }
    }

    static const char* to_code(Code code) noexcept {
        switch (code) {
            case Code::Startup:         return "startup";
            case Code::Shutdown:        return "shutdown";
            case Code::HealthTick:      return "health_tick";
            case Code::Drops:           return "drops";
            case Code::QueueSaturated:  return "queue_saturated";
            case Code::WorkerException: return "worker_exception";
            case Code::PublishFailed:   return "publish_failed";
            case Code::SerializeFailed: return "serialize_failed";
            case Code::Backpressured:   return "backpressured";
            default:                    return "unknown";
        }
    }

    static void emit_to_spdlog(const LogEvent& e) {
        const char* comp = to_component(e.component);
        const char* code = to_code(e.code);

        // Minimal formatting; do string work here (NOT in producers)
        if (e.level == LogLevel::Error) {
            spdlog::error("[{}] code={} iid={} shard={} arg0={} arg1={}",
                          comp, code, e.instrumentId, e.shard, e.arg0, e.arg1);
        } else {
            // Health and Info -> info for now (can map Health->info too)
            spdlog::info("[{}] code={} iid={} shard={} arg0={} arg1={}",
                         comp, code, e.instrumentId, e.shard, e.arg0, e.arg1);
        }
    }

private:
    LogQueueSpsc<LogEvent, Capacity> queue_{};
    std::atomic<bool> running_{false};
    std::thread thread_{};
    std::atomic<uint64_t> dropped_{0};
};

} // namespace b3::md::telemetry