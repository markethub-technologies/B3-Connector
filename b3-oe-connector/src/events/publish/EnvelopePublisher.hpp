#pragma once

#include <memory>
#include <stdexcept>

#include <sockets/Publisher.h> 
#include <spdlog/logger.h>

#include "MessagingPublisherFacade.hpp"
#include "../core/SerializedEnvelope.hpp"

namespace events {

/**
 * Concrete publisher that forwards SerializedEnvelope to the messaging library Publisher.
 * The library is expected to provide its own internal queue.
 */
class EnvelopePublisher final : public MessagingPublisherFacade
{
public:
    struct Deps final
    {
        std::shared_ptr<spdlog::logger> log;
        std::unique_ptr<markethub::messaging::sockets::Publisher> publisher;
    };

    explicit EnvelopePublisher(Deps deps)
        : deps_(std::move(deps))
    {
        if (!deps_.log)
            throw std::runtime_error("EnvelopePublisher: log is null");
        if (!deps_.publisher)
            throw std::runtime_error("EnvelopePublisher: publisher is null");
    }

    ~EnvelopePublisher() override = default;

    EnvelopePublisher(const EnvelopePublisher&) = delete;
    EnvelopePublisher& operator=(const EnvelopePublisher&) = delete;

    bool publish(const SerializedEnvelope& env) noexcept override
    {
        try
        {
            // Low-latency path you added in the library:
            // SendSerialized(const char* topic, uint8_t topicLen, const void* payload, uint32_t payloadLen)
            deps_.publisher->SendSerialized(
                env.topic,
                env.topicLen,
                env.bytes,
                env.size);

            return true;
        }
        catch (const std::exception& ex)
        {
            deps_.log->error("EnvelopePublisher publish failed: {}", ex.what());
            return false;
        }
        catch (...)
        {
            deps_.log->error("EnvelopePublisher publish failed: unknown exception");
            return false;
        }
    }

private:
    Deps deps_;
};

} // namespace events
