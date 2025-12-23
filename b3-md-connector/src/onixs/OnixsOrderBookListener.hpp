#pragma once

#include "../core/MarketDataEngine.hpp"

#include <OnixS/B3/MarketData/UMDF/OrderBookListener.h>
#include <OnixS/B3/MarketData/UMDF/OrderBook.h>
#include <OnixS/B3/MarketData/UMDF/messaging/SbeMessage.h>

#include <atomic>
#include <cstdint>

namespace b3::md::onixs {

// Adapter: OnixS -> MarketDataEngine
class OnixsOrderBookListener final : public ::OnixS::B3::MarketData::UMDF::OrderBookListener {
public:
    explicit OnixsOrderBookListener(b3::md::MarketDataEngine& engine) noexcept
        : engine_(engine)
    {}

    OnixsOrderBookListener(const OnixsOrderBookListener&) = delete;
    OnixsOrderBookListener& operator=(const OnixsOrderBookListener&) = delete;

    void onOrderBookChanged(
        const ::OnixS::B3::MarketData::UMDF::OrderBook& /*book*/,
        const ::OnixS::B3::MarketData::UMDF::Messaging::SbeMessage /*message*/) override
    {
        // Por ahora no publicamos acá para evitar snapshots intermedios.
        //
        // TODO(B3): revisar si el SbeMessage trae exchange timestamp (o event time) y dónde.
        // Si existe, decidir cómo propagarlo sin heap ni mapas en hot path (ideal: usar onOrderBookUpdated
        // si el SDK expone el timestamp ahí; si no, estudiar estrategia).
        changedCount_.fetch_add(1, std::memory_order_relaxed);
    }

    void onOrderBookUpdated(const ::OnixS::B3::MarketData::UMDF::OrderBook& book) override {
        updatedCount_.fetch_add(1, std::memory_order_relaxed);
        engine_.onOrderBookUpdated(book);
    }

    void onOrderBookOutOfDate(const ::OnixS::B3::MarketData::UMDF::OrderBook& /*book*/) override {
        outOfDateCount_.fetch_add(1, std::memory_order_relaxed);
        // TODO(B3): emitir health/counter para marcar "books outdated" (sin bloquear).
    }

    uint64_t changedCount() const noexcept { return changedCount_.load(std::memory_order_relaxed); }
    uint64_t updatedCount() const noexcept { return updatedCount_.load(std::memory_order_relaxed); }
    uint64_t outOfDateCount() const noexcept { return outOfDateCount_.load(std::memory_order_relaxed); }

private:
    b3::md::MarketDataEngine& engine_;

    std::atomic<uint64_t> changedCount_{0};
    std::atomic<uint64_t> updatedCount_{0};
    std::atomic<uint64_t> outOfDateCount_{0};
};

} // namespace b3::md::onixs
