#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <thread>

#include "../../common/MpscPodQueue.hpp"
#include "BoeEventPOD.hpp"

namespace spdlog { class logger; }

namespace events {

struct SerializedEnvelope;
class WrapperSerializer;
class MessagingPublisherFacade;

/**
 * Single-consumer loop:
 *  - drains BoeEventPOD from MpscPodQueue (multi-producer)
 *  - serializes into SerializedEnvelope
 *  - publishes via MessagingPublisherFacade (which queues internally)
 *
 * This is intentionally .h/.cpp to keep dependencies (protobuf, messaging, etc.)
 * out of headers and avoid incomplete-type problems.
 */
class OrderEventProcessingLoop final
{
public:
    struct Deps final
    {
        std::shared_ptr<spdlog::logger> log;

        MpscPodQueue<BoeEventPOD>* queue{nullptr};
        WrapperSerializer* serializer{nullptr};
        MessagingPublisherFacade* publisher{nullptr};
    };

    explicit OrderEventProcessingLoop(Deps deps);
    ~OrderEventProcessingLoop();

    OrderEventProcessingLoop(const OrderEventProcessingLoop&) = delete;
    OrderEventProcessingLoop& operator=(const OrderEventProcessingLoop&) = delete;

    void start();
    void stop(bool drain);

    uint64_t publishedCount() const noexcept;
    uint64_t droppedCount() const noexcept;

private:
    void run_();
    void handleEvent_(const BoeEventPOD& ev);

private:
    Deps deps_;
    std::thread th_;
    std::atomic<bool> running_{false};

    std::atomic<uint64_t> publishedCount_{0};
    std::atomic<uint64_t> droppedCount_{0};
};

} // namespace events
