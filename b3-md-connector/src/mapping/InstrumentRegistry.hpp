#pragma once

#include <shared_mutex>
#include <string>
#include <unordered_map>

namespace b3::md::mapping {

  using InstrumentId = std::uint64_t;

  class InstrumentRegistry final {
   public:
    InstrumentRegistry() = default;
    InstrumentRegistry(const InstrumentRegistry &) = delete;
    InstrumentRegistry &operator=(const InstrumentRegistry &) = delete;

    // Lectura: shared_lock => muchos readers simultáneos.
    const std::string *tryResolve(InstrumentId iid) const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      auto it = byId_.find(iid);
      if (it == byId_.end())
        return nullptr;
      return &it->second;
    }

    // Escritura: unique_lock => 1 writer, bloquea readers mientras dura.
    void upsert(InstrumentId iid, std::string symbol) {
      std::unique_lock<std::shared_mutex> lock(mu_);
      byId_[iid] = std::move(symbol);
    }

    // Útil cuando recibís un fragmento de SecurityList con muchas entradas.
    template <class It>
    void bulkUpsert(It begin, It end) {
      std::unique_lock<std::shared_mutex> lock(mu_);
      for (auto it = begin; it != end; ++it) {
        byId_[it->first] = it->second;
      }
    }

    std::size_t size() const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      return byId_.size();
    }

   private:
    mutable std::shared_mutex mu_;
    std::unordered_map<InstrumentId, std::string> byId_;
  };

} // namespace b3::md::mapping
