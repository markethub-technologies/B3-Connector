// src/events/publish/MessagingPublisherFacade.h
#pragma once

#include <cstddef>
#include <cstdint>

namespace events {

struct SerializedEnvelope;

/**
 * Output boundary for publishing already-serialized messages.
 *
 * Implementations may queue internally (MarketHub.Messaging does).
 * This interface keeps events/core independent from messaging headers.
 */
class MessagingPublisherFacade
{
public:
    virtual ~MessagingPublisherFacade() = default;

    /**
     * Publish a message (topic + payload).
     * Return false on failure (closed, not ready, etc).
     */
    virtual bool publish(const SerializedEnvelope& env) noexcept = 0;
};

} // namespace events
