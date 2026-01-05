#pragma once
#include <cstdint>
#include "SerializedEnvelope.hpp"

namespace b3::md::publishing {

  struct IPublishSink {
    virtual ~IPublishSink() = default;
    virtual bool tryPublish(uint32_t shardId, const SerializedEnvelope &ev) noexcept = 0;
  };

} // namespace b3::md::publishing