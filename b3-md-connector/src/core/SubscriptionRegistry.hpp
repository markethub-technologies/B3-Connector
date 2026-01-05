#pragma once
#include <cstdint>
#include <unordered_map>
#include <mutex> // <-- necesario para unique_lock
#include <shared_mutex>

namespace b3::md {

  class SubscriptionRegistry final {
   public:
    using InstrumentId = std::uint64_t;

    // Devuelve true si pasa de 0 -> 1 (primer sub)
    bool add(InstrumentId iid) {
      std::unique_lock<std::shared_mutex> lock(mu_);
      auto &subs = subscribersCount_[iid];
      const bool first = (subs == 0);
      ++subs;
      return first;
    }

    // Devuelve true si pasa de 1 -> 0 (último unsub y se borró)
    bool remove(InstrumentId iid) {
      std::unique_lock<std::shared_mutex> lock(mu_);
      auto it = subscribersCount_.find(iid);
      if (it == subscribersCount_.end())
        return false;

      if (it->second <= 1) {
        subscribersCount_.erase(it);
        return true; // last
      }

      --it->second;
      return false;
    }

    bool isActive(InstrumentId iid) const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      auto it = subscribersCount_.find(iid);
      return it != subscribersCount_.end() && it->second > 0;
    }

    std::size_t activeCount() const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      return subscribersCount_.size();
    }

   private:
    mutable std::shared_mutex mu_;
    std::unordered_map<InstrumentId, std::uint32_t> subscribersCount_;
  };

} // namespace b3::md
