#pragma once

#include <initializer_list>
#include <string>
#include <utility>

#include "../mapping/InstrumentRegistry.hpp"
#include "../mapping/InstrumentTopicMapper.hpp"

namespace b3::md::testsupport {

  /**
   * FakeInstrumentTopicMapper
   * ------------------------
   * Test helper that creates a real InstrumentTopicMapper with preloaded data.
   * Use this in tests instead of mocking - provides same semantics as production.
   */
  class FakeInstrumentTopicMapper final {
   public:
    using InstrumentId = b3::md::mapping::InstrumentId;

    // Construct with list of {instrumentId, "SYMBOL"} pairs
    explicit FakeInstrumentTopicMapper(
        std::initializer_list<std::pair<InstrumentId, std::string>> items = {})
        : mapper_(registry_) {
      for (const auto& kv : items) {
        registry_.upsert(kv.first, kv.second);
      }
    }

    // Access the real mapper that MdPublishWorker needs
    const b3::md::mapping::InstrumentTopicMapper& get() const noexcept {
      return mapper_;
    }

    b3::md::mapping::InstrumentTopicMapper& get() noexcept {
      return mapper_;
    }

    // Helper for fluent API: with(id, "symbol")
    FakeInstrumentTopicMapper& with(InstrumentId id, std::string symbol) {
      registry_.upsert(id, std::move(symbol));
      return *this;
    }

   private:
    b3::md::mapping::InstrumentRegistry registry_;
    b3::md::mapping::InstrumentTopicMapper mapper_;
  };

} // namespace b3::md::testsupport
