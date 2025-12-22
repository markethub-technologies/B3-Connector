#pragma once

#include <OnixS/B3/MarketData/UMDF/OrderBookListener.h>
#include <OnixS/B3/MarketData/UMDF/messaging/SbeMessage.h>
#include "../core/MarketDataEngine.hpp"

#include "OnixOrderBookView.hpp"

namespace b3::md::onixs {

class OnixsOrderBookListener final
    : public ::OnixS::B3::MarketData::UMDF::OrderBookListener
{
public:
    explicit OnixsOrderBookListener(b3::md::MarketDataEngine& engine) noexcept
        : engine_(engine) {}

    // Se llama en cambios dentro de profundidad (puede ser muy frecuente).
    // Por diseño, NO hacemos trabajo acá; nos quedamos con "Updated" que ya
    // llega al EndOfEvent y consolida.
    void onOrderBookChanged(const ::OnixS::B3::MarketData::UMDF::OrderBook& /*book*/,
                            const ::OnixS::B3::MarketData::UMDF::Messaging::SbeMessage /*message*/) override
    {
        // intencionalmente vacío
        // (si más adelante necesitás algo, tiene que seguir el mismo contrato:
        // no block, no alloc, no log)
    }

    // Punto principal: libro consolidado (EndOfEvent) y dentro de profundidad.
    void onOrderBookUpdated(const ::OnixS::B3::MarketData::UMDF::OrderBook& book) override
    {
        // Stack-local view (no se guarda book_ ni refs afuera del callback)
        OnixsOrderBookView view(book);

        // Hot path: snapshot+enqueue (engine maneja drops)
        engine_.onOrderBookUpdated(view);
    }

    // Cuando el SDK avisa que está out of date.
    // No bloquea. No loguea (si querés, solo contador atómico y health thread).
    void onOrderBookOutOfDate(const ::OnixS::B3::MarketData::UMDF::OrderBook& /*book*/) override
    {
        // opcional: ++outOfDate_;
        // o marcar flag por instrumento si tenés estructura lock-free para eso
    }

private:
    b3::md::MarketDataEngine& engine_;
    // std::atomic<uint64_t> outOfDate_{0}; // si querés, sin overhead
};

} // namespace b3::md::onixs
