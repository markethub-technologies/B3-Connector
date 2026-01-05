#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <cstdio>

#include "../publishing/PublishEvent.hpp"
#include "InstrumentRegistry.hpp"

namespace b3::md::mapping {

  /**
   * @brief Construye topics de marketdata en formato: "<SYMBOL>"
   *
   * las subscripciones y el publish usan SIEMPRE símbolo puro,   *
   */
  class InstrumentTopicMapper final {
   public:
    explicit InstrumentTopicMapper(const InstrumentRegistry &registry) : registry_(registry) {}

    InstrumentTopicMapper(const InstrumentTopicMapper &) = delete;
    InstrumentTopicMapper &operator=(const InstrumentTopicMapper &) = delete;

    // Llena ev.topic + ev.topicLen. Devuelve false si excede kMaxTopic.
    bool tryWriteTopic(InstrumentId iid,
                       b3::md::publishing::SerializedEnvelope &env) const noexcept {
      const std::string *sym = registry_.tryResolveSymbol(iid);
      if (!sym) {
        return writeFallback(iid, env);
      }

      const std::size_t n = sym->size();
      if (n == 0 || n > b3::md::publishing::SerializedEnvelope::kMaxTopic)
        return false;

      env.topicLen = static_cast<std::uint8_t>(n);
      std::memcpy(env.topic, sym->data(), n);
      return true;
    }

   private:
    static bool writeFallback(InstrumentId iid,
                              b3::md::publishing::SerializedEnvelope &env) noexcept {
      char buf[32];
      const int wrote =
          std::snprintf(buf, sizeof(buf), "IID:%llu", static_cast<unsigned long long>(iid));
      if (wrote <= 0)
        return false;

      const std::size_t n = static_cast<std::size_t>(wrote);
      if (n > b3::md::publishing::SerializedEnvelope::kMaxTopic)
        return false;

      env.topicLen = static_cast<std::uint8_t>(n);
      std::memcpy(env.topic, buf, n);
      return true;
    }

   private:
    const InstrumentRegistry &registry_;
  };

} // namespace b3::md::mapping
