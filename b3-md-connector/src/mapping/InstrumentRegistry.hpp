#pragma once

#include <cstdint>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <mutex> // <-- necesario para unique_lock

namespace b3::md::mapping {

  using InstrumentId = std::uint64_t;

  // Transparent hash for heterogeneous lookup (C++20)
  // Allows find(string_view) without creating temporary std::string
  struct StringHash {
    using is_transparent = void;
    using hash_type = std::hash<std::string_view>;

    std::size_t operator()(std::string_view str) const noexcept {
      return hash_type{}(str);
    }
    std::size_t operator()(const std::string& str) const noexcept {
      return hash_type{}(str);
    }
    std::size_t operator()(const char* str) const noexcept {
      return hash_type{}(str);
    }
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

    // iid -> symbol
    const std::string *tryResolveSymbol(InstrumentId iid) const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      auto it = byId_.find(iid);
      if (it == byId_.end())
        return nullptr;
      return &it->second;
    }

    // symbol -> iid
    const InstrumentId *tryResolveId(std::string_view symbol) const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      auto it = bySymbol_.find(symbol);  // ✅ No temp string (heterogeneous lookup)
      if (it == bySymbol_.end())
        return nullptr;
      return &it->second;
    }

    void upsert(InstrumentId iid, std::string symbol) {
      if (iid == 0 || symbol.empty())
        return;

      std::unique_lock<std::shared_mutex> lock(mu_);

      // si el iid ya existía con otro símbolo, limpiamos reverse map viejo
      auto itOld = byId_.find(iid);
      if (itOld != byId_.end()) {
        auto itRevOld = bySymbol_.find(itOld->second);
        if (itRevOld != bySymbol_.end() && itRevOld->second == iid)
          bySymbol_.erase(itRevOld);
      }

      // si el símbolo ya existía apuntando a otro iid, lo pisamos (última gana)
      bySymbol_[symbol] = iid;
      byId_[iid] = std::move(symbol);
    }

    // begin/end deben iterar pares (InstrumentId, std::string)
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
          auto itRevOld = bySymbol_.find(itOld->second);
          if (itRevOld != bySymbol_.end() && itRevOld->second == iid)
            bySymbol_.erase(itRevOld);
        }

        // insertar / actualizar ambos
        bySymbol_[symRef] = iid;
        byId_[iid] = symRef;
      }
    }

    std::size_t size() const noexcept {
      std::shared_lock<std::shared_mutex> lock(mu_);
      return byId_.size();
    }

   private:
    mutable std::shared_mutex mu_;
    std::unordered_map<InstrumentId, std::string> byId_;
    std::unordered_map<std::string, InstrumentId, StringHash, StringEqual> bySymbol_;
  };

} // namespace b3::md::mapping
