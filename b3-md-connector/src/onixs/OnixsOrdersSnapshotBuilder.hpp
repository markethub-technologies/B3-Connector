#pragma once

#include "../core/OrdersSnapshot.hpp"

#include <OnixS/B3/MarketData/UMDF/OrderBook.h>
#include <chrono>

namespace b3::md::onixs {

inline uint64_t nowNsSteady() noexcept {
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(now).count()
    );
}

// Copia una ventana acotada de órdenes desde el OrderBook del SDK.
// IMPORTANTE: saltea órdenes con precio null (ordenes a mercado) porque no aportan al agregado MBP, 
// ver si esta bien. 20251222
inline void buildOrdersSnapshotFromOnixsBook(
    const ::OnixS::B3::MarketData::UMDF::OrderBook& orderBook,
    b3::md::OrdersSnapshot& snapshot) noexcept
{
    // Zero-init POD
    snapshot = b3::md::OrdersSnapshot{};

    snapshot.instrumentId =
        static_cast<uint32_t>(static_cast<uint64_t>(orderBook.instrumentId()));

    snapshot.exchangeTsNs = nowNsSteady();

    // Secuencias del feed (útiles para orden / health / debug)
    snapshot.rptSeq =
        static_cast<uint64_t>(orderBook.lastRptSeq());

    snapshot.channelSeq =
        static_cast<uint64_t>(orderBook.lastMessageSeqNumApplied());

    // -------------------------
    // BID SIDE
    // -------------------------
    // El header del SDK indica que bids() está en orden ascendente,
    // por lo tanto el mejor bid está al final del rango.
    {
        const auto bidOrdersRange = orderBook.bids();
        const size_t totalBidOrders = bidOrdersRange.size();

        uint16_t copiedBidOrders = 0;
        bool bidSideTruncated = false;

        // Recorremos desde el mejor precio hacia peor
        for (size_t offset = 0; offset < totalBidOrders; ++offset) {
            if (copiedBidOrders >= b3::md::OrdersSnapshot::K) {
                bidSideTruncated = true;
                break;
            }

            const size_t orderIndex = (totalBidOrders - 1) - offset;
            const auto& order = bidOrdersRange[orderIndex];

            const auto price = order.price();
            if (price.isNull()) {
                // Orden a mercado: se omite (no afecta MBP).
                continue;
            }

            snapshot.bids[copiedBidOrders].priceMantissa =
                static_cast<int64_t>(price.mantissa());

            snapshot.bids[copiedBidOrders].qty =
                static_cast<int64_t>(order.quantity());

            ++copiedBidOrders;
        }

        snapshot.bidCountRaw = copiedBidOrders;
        snapshot.bidTruncated = bidSideTruncated ? 1u : 0u;
    }

    // -------------------------
    // ASK SIDE
    // -------------------------
    // El comentario del SDK es ambiguo para asks().
    // Asumimos que el mejor ask aparece primero.
    // Si en runtime se observa lo contrario, basta con invertir el recorrido.
    {
        const auto askOrdersRange = orderBook.asks();
        const size_t totalAskOrders = askOrdersRange.size();

        uint16_t copiedAskOrders = 0;
        bool askSideTruncated = false;

        for (size_t orderIndex = 0; orderIndex < totalAskOrders; ++orderIndex) {
            if (copiedAskOrders >= b3::md::OrdersSnapshot::K) {
                askSideTruncated = true;
                break;
            }

            const auto& order = askOrdersRange[orderIndex];

            const auto price = order.price();
            if (price.isNull()) {
                // Orden a mercado: se omite (no afecta MBP).
                continue;
            }

            snapshot.asks[copiedAskOrders].priceMantissa =
                static_cast<int64_t>(price.mantissa());

            snapshot.asks[copiedAskOrders].qty =
                static_cast<int64_t>(order.quantity());

            ++copiedAskOrders;
        }

        snapshot.askCountRaw = copiedAskOrders;
        snapshot.askTruncated = askSideTruncated ? 1u : 0u;
    }
}

} // namespace b3::md::onixs