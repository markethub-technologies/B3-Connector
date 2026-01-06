#pragma once

#include "../core/SnapshotQueueSpsc.hpp"
#include "../telemetry/SpdlogLogPublisher.hpp"
#include "../telemetry/LogEvent.hpp"

#include "IPublishSink.hpp"
#include "SerializedEnvelope.hpp"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// MarketHub.Messaging
#include <sockets/Publisher.h>

namespace b3::md::publishing {

  class ZmqPublishConcentrator final : public IPublishSink {
   public:
    static constexpr size_t kPerShardQueueCapacity = 4096;
    static constexpr uint32_t kBatchPerShard = 8;
    static constexpr size_t kLogQueueCapacity = 1024;

    explicit ZmqPublishConcentrator(std::string pubEndpoint, uint32_t shardCount)
        : pubEndpoint_(std::move(pubEndpoint)), shardCount_(shardCount) {
      queues_.reserve(shardCount_);
      for (uint32_t i = 0; i < shardCount_; ++i) {
        queues_.emplace_back(std::make_unique<QueueT>());
      }

      droppedByShard_.reserve(shardCount_);
      enqByShard_.reserve(shardCount_);
      sentByShard_.reserve(shardCount_);
      for (uint32_t i = 0; i < shardCount_; ++i) {
        droppedByShard_.emplace_back(0);
        enqByShard_.emplace_back(0);
        sentByShard_.emplace_back(0);
      }
    }

    ZmqPublishConcentrator(const ZmqPublishConcentrator &) = delete;
    ZmqPublishConcentrator &operator=(const ZmqPublishConcentrator &) = delete;

    void start() {
      bool expected = false;
      if (!running_.compare_exchange_strong(expected, true, std::memory_order_acq_rel))
        return;

      logger_.start();
      thread_ = std::thread([this] { run(); });
    }

    void stop() {
      running_.store(false, std::memory_order_release);
      if (thread_.joinable())
        thread_.join();
      logger_.stop();
    }

    // IPublishSink
    bool tryPublish(uint32_t shardId, const SerializedEnvelope &ev) noexcept override {
      if (shardId >= shardCount_)
        return false;

      if (ev.topicLen == 0 || ev.topicLen > SerializedEnvelope::kMaxTopic) {
        droppedByShard_[shardId].v.fetch_add(1, std::memory_order_relaxed);
        return false;
      }
      if (ev.size == 0 || ev.size > SerializedEnvelope::kMaxBytes) {
        droppedByShard_[shardId].v.fetch_add(1, std::memory_order_relaxed);
        return false;
      }

      auto &q = *queues_[shardId];
      if (q.try_push(ev)) {
        enqByShard_[shardId].v.fetch_add(1, std::memory_order_relaxed);
        return true;
      }

      droppedByShard_[shardId].v.fetch_add(1, std::memory_order_relaxed);
      return false;
    }

    uint64_t droppedTotal() const noexcept {
      uint64_t sum = 0;
      for (uint32_t i = 0; i < shardCount_; ++i) {
        sum += droppedByShard_[i].v.load(std::memory_order_relaxed);
      }
      return sum;
    }

   private:
    using QueueT = b3::md::SnapshotQueueSpsc<SerializedEnvelope, kPerShardQueueCapacity>;

    struct CopyableAtomicU64 {
      std::atomic<uint64_t> v;
      CopyableAtomicU64(uint64_t init = 0) noexcept : v(init) {}
      CopyableAtomicU64(const CopyableAtomicU64 &other) noexcept
          : v(other.v.load(std::memory_order_relaxed)) {}
      CopyableAtomicU64 &operator=(const CopyableAtomicU64 &other) noexcept {
        v.store(other.v.load(std::memory_order_relaxed), std::memory_order_relaxed);
        return *this;
      }
    };

    static uint64_t nowNsSteady() noexcept {
      const auto now = std::chrono::steady_clock::now().time_since_epoch();
      return static_cast<uint64_t>(
          std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
    }

    void emitHealth(uint64_t nowNs) noexcept {
      telemetry::LogEvent e{};
      e.tsNs = nowNs;
      e.level = telemetry::LogLevel::Health;
      e.component = telemetry::Component::Publishing;
      e.code = telemetry::Code::HealthTick;

      uint64_t dropped = 0, sent = 0;
      for (uint32_t i = 0; i < shardCount_; ++i) {
        dropped += droppedByShard_[i].v.load(std::memory_order_relaxed);
        sent += sentByShard_[i].v.load(std::memory_order_relaxed);
      }
      e.arg0 = dropped;
      e.arg1 = sent;
      (void)logger_.try_publish(e);
    }

    // Wrapper RAII
    struct MessagingPublisher {
      markethub::messaging::sockets::Publisher pub;

      explicit MessagingPublisher(const std::string &endpoint)
          : pub(endpoint, /*isMultiplePublisher=*/false) {}

      void start() { pub.Start(); }
      void stop() { pub.Stop(); }

      void sendSerialized(const SerializedEnvelope &ev) {
        pub.SendSerialized(ev.topic, ev.topicLen, ev.bytes, ev.size);
      }
    };

    void run() noexcept {
      using namespace std::chrono_literals;

      try {
        MessagingPublisher out(pubEndpoint_);
        out.start();

        uint32_t rr = 0;
        uint64_t nextHealth = nowNsSteady() + 5'000'000'000ull;

        SerializedEnvelope ev{};
        while (running_.load(std::memory_order_acquire)) {
          bool didWork = false;

          for (uint32_t n = 0; n < shardCount_; ++n) {
            const uint32_t sid = (rr + n) % shardCount_;
            auto &q = *queues_[sid];

            for (uint32_t k = 0; k < kBatchPerShard; ++k) {
              if (!q.try_pop(ev))
                break;

              didWork = true;
              out.sendSerialized(ev);
              sentByShard_[sid].v.fetch_add(1, std::memory_order_relaxed);
            }
          }

          rr = (rr + 1) % shardCount_;

          const uint64_t now = nowNsSteady();
          if (now >= nextHealth) {
            nextHealth = now + 5'000'000'000ull;
            emitHealth(now);
          }

          if (!didWork)
            std::this_thread::sleep_for(1ms);
        }

        // Drain final
        for (uint32_t sid = 0; sid < shardCount_; ++sid) {
          auto &q = *queues_[sid];
          while (q.try_pop(ev)) {
            out.sendSerialized(ev);  // No std::move: SerializedEnvelope is trivially copyable (16KB POD)
            sentByShard_[sid].v.fetch_add(1, std::memory_order_relaxed);
          }
        }

        out.stop();
      } catch (...) {
        // noexcept: swallow
      }
    }

   private:
    std::string pubEndpoint_;
    uint32_t shardCount_{0};

    std::vector<std::unique_ptr<QueueT>> queues_;

    std::vector<CopyableAtomicU64> droppedByShard_;
    std::vector<CopyableAtomicU64> enqByShard_;
    std::vector<CopyableAtomicU64> sentByShard_;

    telemetry::SpdlogLogPublisher<kLogQueueCapacity> logger_;

    std::atomic<bool> running_{false};
    std::thread thread_{};
  };

} // namespace b3::md::publishing
