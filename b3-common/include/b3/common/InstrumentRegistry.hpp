#pragma once

#include <cstdint>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <mutex>

#include "InstrumentData.hpp"

namespace b3::common {

  using InstrumentId = std::uint64_t;

  // Transparent hash for heterogeneous lookup (C++20)
  // Allows find(string_view) without creating temporary std::string
  struct StringHash {
    using is_transparent = void;
    using hash_type = std::hash<std::string_view>;

    std::size_t operator()(std::string_view str) const noexcept { return hash_type{}(str); }
    std::size_t operator()(const std::string &str) const noexcept { return hash_type{}(str); }
    std::size_t operator()(const char *str) const noexcept { return hash_type{}(str); }
  };

  // Transparent equality for heterogeneous lookup (C++20)
  struct StringEqual {
    using is_transparent = void;

    bool operator()(std::string_view lhs, std::string_view rhs) const noexcept {
      return lhs == rhs;
    }
  };

  class InstrumentRegistry final {
   public:
    InstrumentRegistry() = default;
    InstrumentRegistry(const InstrumentRegistry &) = delete;
    InstrumentRegistry &operator=(const InstrumentRegistry &) = delete;

    // iid -> symbol (legacy API for backward compatibility)
    const std::string *tryResolveSymbol(InstrumentId iid) const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      auto it = byId_.find(iid);
      if (it == byId_.end())
        return nullptr;
      return &it->second.symbol;
    }

    // iid -> full instrument data
    const InstrumentData *tryResolveData(InstrumentId iid) const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      auto it = byId_.find(iid);
      if (it == byId_.end())
        return nullptr;
      return &it->second;
    }

    // symbol -> iid
    const InstrumentId *tryResolveId(std::string_view symbol) const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      auto it = bySymbol_.find(symbol); // ✅ No temp string (heterogeneous lookup)
      if (it == bySymbol_.end())
        return nullptr;
      return &it->second;
    }

    // Legacy API: upsert with symbol only (creates minimal InstrumentData)
    void upsert(InstrumentId iid, std::string symbol) {
      InstrumentData data;
      data.securityId = iid;
      data.symbol = std::move(symbol);
      upsertFull(iid, std::move(data));
    }

    // Full API: upsert with complete instrument data
    void upsertFull(InstrumentId iid, InstrumentData data) {
      if (iid == 0 || data.symbol.empty())
        return;

      // Ensure securityId matches iid
      data.securityId = iid;

      std::unique_lock<std::shared_mutex> lock(mu_);

      // si el iid ya existía con otro símbolo, limpiamos reverse map viejo
      auto itOld = byId_.find(iid);
      if (itOld != byId_.end()) {
        auto itRevOld = bySymbol_.find(itOld->second.symbol);
        if (itRevOld != bySymbol_.end() && itRevOld->second == iid)
          bySymbol_.erase(itRevOld);
      }

      // si el símbolo ya existía apuntando a otro iid, lo pisamos (última gana)
      const std::string &symbol = data.symbol;
      bySymbol_[symbol] = iid;
      byId_[iid] = std::move(data);
    }

    // bulkUpsert with symbol only (legacy, for backward compatibility)
    // begin/end must iterate pairs (InstrumentId, std::string)
    template <class It>
    void bulkUpsert(It begin, It end) {
      std::unique_lock<std::shared_mutex> lock(mu_);

      for (auto it = begin; it != end; ++it) {
        const InstrumentId iid = static_cast<InstrumentId>(it->first);
        const std::string &symRef = it->second;

        if (iid == 0 || symRef.empty())
          continue;

        // remover reverse viejo si iid ya existía
        auto itOld = byId_.find(iid);
        if (itOld != byId_.end()) {
          auto itRevOld = bySymbol_.find(itOld->second.symbol);
          if (itRevOld != bySymbol_.end() && itRevOld->second == iid)
            bySymbol_.erase(itRevOld);
        }

        // Create minimal InstrumentData with symbol
        InstrumentData data;
        data.securityId = iid;
        data.symbol = symRef;

        // insertar / actualizar ambos
        bySymbol_[symRef] = iid;
        byId_[iid] = std::move(data);
      }
    }

    // bulkUpsertFull with complete instrument data
    // begin/end must iterate pairs (InstrumentId, InstrumentData)
    template <class It>
    void bulkUpsertFull(It begin, It end) {
      std::unique_lock<std::shared_mutex> lock(mu_);

      for (auto it = begin; it != end; ++it) {
        const InstrumentId iid = static_cast<InstrumentId>(it->first);
        InstrumentData data = it->second;

        if (iid == 0 || data.symbol.empty())
          continue;

        // Ensure securityId matches iid
        data.securityId = iid;

        // remover reverse viejo si iid ya existía
        auto itOld = byId_.find(iid);
        if (itOld != byId_.end()) {
          auto itRevOld = bySymbol_.find(itOld->second.symbol);
          if (itRevOld != bySymbol_.end() && itRevOld->second == iid)
            bySymbol_.erase(itRevOld);
        }

        const std::string &symbol = data.symbol;
        bySymbol_[symbol] = iid;
        byId_[iid] = std::move(data);
      }
    }

    std::size_t size() const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      return byId_.size();
    }

    // Legacy: snapshot with symbol only
    std::vector<std::pair<InstrumentId, std::string>> snapshotAll() const {
      std::vector<std::pair<InstrumentId, std::string>> out;
      std::shared_lock<std::shared_mutex> lock(mu_);
      out.reserve(byId_.size());
      for (const auto &[iid, data] : byId_) {
        out.emplace_back(iid, data.symbol);
      }
      return out;
    }

    // Full: snapshot with complete instrument data
    std::vector<std::pair<InstrumentId, InstrumentData>> snapshotAllFull() const {
      std::vector<std::pair<InstrumentId, InstrumentData>> out;
      std::shared_lock<std::shared_mutex> lock(mu_);
      out.reserve(byId_.size());
      for (const auto &[iid, data] : byId_) {
        out.emplace_back(iid, data);
      }
      return out;
    }

   private:
    mutable std::shared_mutex mu_;
    std::unordered_map<InstrumentId, InstrumentData> byId_; // Changed from string to InstrumentData
    std::unordered_map<std::string, InstrumentId, StringHash, StringEqual> bySymbol_;
  };

} // namespace b3::common
