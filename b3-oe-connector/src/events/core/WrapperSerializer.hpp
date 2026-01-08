// src/events/core/WrapperSerializer.hpp
#pragma once

#include <cstdint>

#include "BoeEventPOD.hpp"
#include "SerializedEnvelope.hpp"   // este es struct simple, puede quedarse en .h

namespace events {

/**
 * Builds:
 *  - topic (from event + config)
 *  - WrapperMessage protobuf with the appropriate inner payload
 *  - serializes into SerializedEnvelope.bytes/size
 *
 * IMPORTANT:
 *  - Must NOT be called from OnixS callbacks.
 *  - Intended to be called from the single consumer thread (OrderEventProcessingLoop).
 */
class WrapperSerializer
{
public:
    virtual ~WrapperSerializer() = default;

    /**
     * @return true if serialized into out; false if cannot serialize (invalid event, overflow, etc.)
     */
    virtual bool trySerialize(const BoeEventPOD& ev, SerializedEnvelope& out) noexcept = 0;
};

} // namespace events
