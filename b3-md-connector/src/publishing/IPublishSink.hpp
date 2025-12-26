#pragma once
#include <cstdint>
#include "PublishEvent.hpp"

namespace b3::md::publishing {

  struct IPublishSink {
    virtual ~IPublishSink() = default;
    virtual bool tryPublish(uint32_t shardId, const PublishEvent &ev) noexcept = 0;
  };

} // namespace b3::md::publishing
