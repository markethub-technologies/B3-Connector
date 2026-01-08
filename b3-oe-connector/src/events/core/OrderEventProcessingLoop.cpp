#include "OrderEventProcessingLoop.h"

#include <exception>
#include <stdexcept>

#include <spdlog/logger.h>

#include "WrapperSerializer.hpp"
#include "../publish/MessagingPublisherFacade.hpp"
#include "SerializedEnvelope.hpp"

namespace events {

OrderEventProcessingLoop::OrderEventProcessingLoop(Deps deps)
    : deps_(std::move(deps))
{
    if (!deps_.queue)      throw std::runtime_error("OrderEventProcessingLoop: queue is null");
    if (!deps_.serializer) throw std::runtime_error("OrderEventProcessingLoop: serializer is null");
    if (!deps_.publisher)  throw std::runtime_error("OrderEventProcessingLoop: publisher is null");
    if (!deps_.log)        throw std::runtime_error("OrderEventProcessingLoop: log is null");
}

OrderEventProcessingLoop::~OrderEventProcessingLoop()
{
    try { stop(false); } catch (...) {}
}

void OrderEventProcessingLoop::start()
{
    bool expected = false;
    if (!running_.compare_exchange_strong(expected, true))
        return;

    th_ = std::thread([this] { run_(); });
    deps_.log->info("OrderEventProcessingLoop started");
}

void OrderEventProcessingLoop::stop(bool drain)
{
    bool expected = true;
    if (!running_.compare_exchange_strong(expected, false))
        return;

    if (!drain)
        deps_.queue->clear();

    deps_.queue->stop();

    if (th_.joinable())
        th_.join();

    deps_.log->info("OrderEventProcessingLoop stopped (drain={})", drain);
}

uint64_t OrderEventProcessingLoop::publishedCount() const noexcept
{
    return publishedCount_.load(std::memory_order_relaxed);
}

uint64_t OrderEventProcessingLoop::droppedCount() const noexcept
{
    return droppedCount_.load(std::memory_order_relaxed);
}

void OrderEventProcessingLoop::run_()
{
    try
    {
        BoeEventPOD ev{};
        while (running_.load(std::memory_order_relaxed))
        {
            if (!deps_.queue->wait_dequeue(ev))
                break; // stopped + drained

            handleEvent_(ev);
        }

        // If stop(drain=true) was used, we still want to drain whatever is left.
        // Our queue's stop() unblocks the consumer; wait_dequeue will return false once empty.
        BoeEventPOD tail{};
        while (deps_.queue->wait_dequeue(tail))
        {
            handleEvent_(tail);
        }
    }
    catch (const std::exception& ex)
    {
        deps_.log->error("OrderEventProcessingLoop fatal error: {}", ex.what());
    }
    catch (...)
    {
        deps_.log->error("OrderEventProcessingLoop fatal error: unknown exception");
    }
}

void OrderEventProcessingLoop::handleEvent_(const BoeEventPOD& ev)
{
    SerializedEnvelope env{};
    if (!deps_.serializer->trySerialize(ev, env))
    {
        droppedCount_.fetch_add(1, std::memory_order_relaxed);
        return;
    }

    if (!deps_.publisher->publish(env))
    {
        droppedCount_.fetch_add(1, std::memory_order_relaxed);
        return;
    }

    publishedCount_.fetch_add(1, std::memory_order_relaxed);
}

} // namespace events
