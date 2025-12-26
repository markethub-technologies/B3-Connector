#pragma once
#include <cstdint>
#include <cstddef>

namespace b3::md::publishing {

  struct PublishEvent final {
    // HARD CAP global (longitud del topic, NO cantidad de tópicos)
    static constexpr size_t kMaxTopic = 128;
    static constexpr size_t kMaxBytes = 4096;

    // payload
    uint32_t size{0};

    // topic bytes (NO null-terminated)
    uint8_t topicLen{0};
    char topic[kMaxTopic]{};

    uint8_t bytes[kMaxBytes]{};
  };

} // namespace b3::md::publishing
