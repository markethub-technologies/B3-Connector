// src/events/core/SerializedEnvelope.h
#pragma once

#include <cstdint>

namespace events {

/**
 * Serialized message ready to publish:
 * - topic (no allocations)
 * - payload bytes (protobuf WrapperMessage)
 *
 * Size bounds can be tuned later.
 */
struct SerializedEnvelope final
{
    uint8_t  topicLen{0};
    char     topic[128]{};

    uint32_t size{0};
    uint8_t  bytes[16 * 1024]{};
};

} // namespace events
