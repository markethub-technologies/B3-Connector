// b3-md-connector/src/publishing/WireEnvelope.hpp
#pragma once
#include <cstdint>
#include <cstddef>

namespace b3::md::publishing {

  struct SerializedEnvelope final {
    static constexpr size_t kMaxTopic = 128;
    static constexpr size_t kMaxBytes = 16384;

    uint32_t size{0};
    uint8_t topicLen{0};
    char topic[kMaxTopic]{};
    uint8_t bytes[kMaxBytes]{};
  };

} // namespace b3::md::publishing
