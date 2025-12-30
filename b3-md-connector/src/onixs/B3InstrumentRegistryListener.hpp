// b3-md-connector/src/onixs/B3InstrumentRegistryListener.hpp
#pragma once

#include <OnixS/B3/MarketData/UMDF/MessageListener.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Messages.h>

#include <atomic>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "../mapping/InstrumentRegistry.hpp"

namespace b3::md::onixs {

  class B3InstrumentRegistryListener final : public ::OnixS::B3::MarketData::UMDF::MessageListener {
   public:
    explicit B3InstrumentRegistryListener(b3::md::mapping::InstrumentRegistry &registry) noexcept
        : registry_(registry) {}

    const std::atomic<bool> &readyAtomic() const noexcept { return ready_; }

    // -------- UMDF callbacks --------

    void onSequenceReset_1(const ::OnixS::B3::MarketData::UMDF::Messaging::SequenceReset_1,
                           const ::OnixS::B3::MarketData::UMDF::DataSource &) override {
      if (ready_.load(std::memory_order_acquire))
        return;

      // First reset: start capture
      if (!capturing_.exchange(true, std::memory_order_acq_rel)) {
        staging_.clear();
        return;
      }

      // Second reset: close loop → commit
      registry_.bulkUpsert(staging_.begin(), staging_.end());
      ready_.store(true, std::memory_order_release);
    }

    void onSecurityDefinition_12(
        const ::OnixS::B3::MarketData::UMDF::Messaging::SecurityDefinition_12 msg,
        const ::OnixS::B3::MarketData::UMDF::DataSource &) override {
      const std::uint64_t iid = static_cast<std::uint64_t>(msg.securityId());
      if (iid == 0)
        return;

      std::string sym = trimRight(msg.symbol());
      if (sym.empty())
        return;

      if (ready_.load(std::memory_order_acquire)) {
        registry_.upsert(iid, std::move(sym)); // incremental update
        return;
      }

      if (!capturing_.load(std::memory_order_acquire))
        return; // ignore until first reset

      staging_[iid] = std::move(sym);
    }

   private:
    template <typename StrLike>
    static std::string trimRight(const StrLike &s) {
      const char *p = s.data();
      std::size_t n = static_cast<std::size_t>(s.size());
      while (n > 0 && (p[n - 1] == ' ' || p[n - 1] == '\0' || p[n - 1] == '\t')) --n;
      return std::string(p, n);
    }

   private:
    b3::md::mapping::InstrumentRegistry &registry_;

    std::atomic<bool> capturing_{false};
    std::atomic<bool> ready_{false};

    std::unordered_map<std::uint64_t, std::string> staging_;
  };

} // namespace b3::md::onixs
