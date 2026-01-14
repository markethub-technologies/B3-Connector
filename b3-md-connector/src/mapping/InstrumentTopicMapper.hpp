#pragma once

#include <cstdint>
#include <cstring>
#include <string>
#include <cstdio>
#include <utility>

#include <b3/common/InstrumentRegistry.hpp>
#include "../publishing/SerializedEnvelope.hpp"

namespace b3::md::mapping {

  /**
   * @brief Construye topics de marketdata en formato: "<SYMBOL>"
   *
   * las subscripciones y el publish usan SIEMPRE símbolo puro,   *
   */
  class InstrumentTopicMapper final {
   public:
    explicit InstrumentTopicMapper(const b3::common::InstrumentRegistry &registry) : registry_(registry) {}

    InstrumentTopicMapper(const InstrumentTopicMapper &) = delete;
    InstrumentTopicMapper &operator=(const InstrumentTopicMapper &) = delete;

    /**
     * @brief Get topic string for publishing
     *
     * Returns the symbol string for the given instrument ID.
     *
     * @param iid Instrument ID to resolve
     * @return Pair of (topic_ptr, topic_len). Returns (nullptr, 0) if symbol not in registry.
     *
     * @note NO FALLBACK: If the symbol cannot be resolved, returns nullptr.
     *       The caller (MdPublishWorker) will drop the message and increment dropped counter.
     *       This ensures clients only receive messages with real symbols they can filter on.
     */
    std::pair<const char*, std::uint8_t> getTopic(b3::common::InstrumentId iid) const noexcept {
      const std::string *sym = registry_.tryResolveSymbol(iid);
      if (sym) {
        const std::size_t n = sym->size();
        if (n > 0 && n <= b3::md::publishing::SerializedEnvelope::kMaxTopic) {
          return {sym->data(), static_cast<std::uint8_t>(n)};
        }
      }

      // No fallback - if symbol not in registry, drop the message
      return {nullptr, 0};
    }

   private:
    const b3::common::InstrumentRegistry &registry_;
  };

} // namespace b3::md::mapping
