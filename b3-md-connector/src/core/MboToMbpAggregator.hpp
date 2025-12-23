#pragma once

#include "OrdersSnapshot.hpp"
#include "BookSnapshot.hpp"
#include <cstdint>

namespace b3::md {

// Agrega órdenes (MBO) por precio para producir niveles (MBP Top-N).
// No aloca. No tira exceptions. Diseñado para ejecutarse en worker.
inline void aggregateMboWindowToMbpTopN(const OrdersSnapshot& in, BookSnapshot& out) noexcept {
    out.instrumentId = in.instrumentId;
    out.exchangeTsNs = in.exchangeTsNs;
    out.bidCount = 0;
    out.askCount = 0;

    // Limpieza explícita (por si Level no es trivially-zero-safe)
    for (int i = 0; i < BookSnapshot::DEPTH; ++i) {
        out.bids[i] = Level{};
        out.asks[i] = Level{};
    }

    auto add_level = [](Level* levels, uint8_t& count, int64_t priceMantissa, int64_t qty) noexcept {
        // Buscar si ya existe ese precio dentro de los niveles armados
        for (uint8_t i = 0; i < count; ++i) {
            const auto existingPrice = static_cast<int64_t>(levels[i].price);
            if (existingPrice == priceMantissa) {
                levels[i].qty = static_cast<decltype(levels[i].qty)>(
                    static_cast<int64_t>(levels[i].qty) + qty
                );
                return;
            }
        }

        // Nuevo precio si todavía hay espacio
        if (count < BookSnapshot::DEPTH) {
            levels[count].price = static_cast<decltype(levels[count].price)>(priceMantissa);
            levels[count].qty   = static_cast<decltype(levels[count].qty)>(qty);
            ++count;
        }
    };

    // BID side
    {
        
        const uint16_t n = in.bidsCopied; // // solo lo copiado porque hubo descartes de raw donde order == market
        for (uint16_t i = 0; i < n && out.bidCount < BookSnapshot::DEPTH; ++i) {
            const auto& e = in.bids[i];
            if (e.qty == 0) continue;
            if (e.priceMantissa == 0) continue;

            add_level(out.bids, out.bidCount, e.priceMantissa, e.qty);
        }
    }

    // ASK side
    {
        const uint16_t n = in.asksCopied; // solo lo copiado porque hubo descartes de raw donde order == market
        for (uint16_t i = 0; i < n && out.askCount < BookSnapshot::DEPTH; ++i) {
            const auto& e = in.asks[i];
            if (e.qty == 0) continue;
            if (e.priceMantissa == 0) continue;

            add_level(out.asks, out.askCount, e.priceMantissa, e.qty);
        }
    }
}

} // namespace b3::md
