#pragma once

#include "../core/OrdersSnapshot.hpp"

#include <cstddef>
#include <cstdint>
#include <chrono>

// OnixS
#include <OnixS/B3/MarketData/UMDF/OrderBook.h> // o el include correcto en tu entorno

namespace b3::md::onixs {

// Builder hot-path: copia una ventana acotada de órdenes (MBO) desde el OrderBook de OnixS.
// Reglas:
// - NO aloca
// - NO loguea
// - NO agrupa por niveles (eso se hace en worker)
// - saltea órdenes con precio null (market orders), porque no aportan a MBP por niveles de precio.
struct OnixsOrdersSnapshotBuilder final {
    using OrderBook = OnixS::B3::MarketData::UMDF::OrderBook;

    static inline void buildFromBook(const OrderBook& book, uint64_t nowNs, b3::md::OrdersSnapshot& out) noexcept {
        // Reset POD
        out = b3::md::OrdersSnapshot{};

        // Metadata base
        out.instrumentId = static_cast<uint32_t>(book.instrumentId());
        out.rptSeq       = static_cast<uint64_t>(book.lastRptSeq());
        out.channelSeq   = static_cast<uint64_t>(book.lastMessageSeqNumApplied());

        //TODO: tratar de meter el timestamp del exchange.
        using clock = std::chrono::system_clock;
        const auto now = clock::now().time_since_epoch();
        out.exchangeTsNs = nowNs;

        // TODO: validar orden real de bids() en runtime.
        // Si bids() viene ascending (mejor al final) => true.
        // Si bids() viene descending (mejor al principio) => false.
        static constexpr bool kBidsBestAtEnd = true;

        // Copia bids (según header: bids() => ascending bid prices
        // TODO: el comentario del SDK parece raro, que viene al revés, validar en runtime, 
        {
            const auto bidsRange = book.bids();
            const size_t raw = bidsRange.size();
            out.bidCountRaw = static_cast<uint16_t>(raw > 0xFFFFu ? 0xFFFFu : raw);

            uint16_t copied = 0;
            bool truncated = false;

            // Recorremos y copiamos solo precios válidos hasta K
            if constexpr (kBidsBestAtEnd) {
                // mejor bid al final => iterar al revés
                for (size_t i = raw; i > 0; --i) {
                    const auto& ord = bidsRange[i - 1];

                    const auto px = ord.price();
                    if (px.isNull()) continue;

                    if (copied >= b3::md::OrdersSnapshot::K) {
                        truncated = true;
                        break;
                    }

                    out.bids[copied].priceMantissa = static_cast<int64_t>(px.mantissa());
                    out.bids[copied].qty          = static_cast<int64_t>(ord.quantity());
                    ++copied;
                }
            } else {
                // mejor bid al principio => iterar normal
                for (size_t i = 0; i < raw; ++i) {
                    const auto& ord = bidsRange[i];

                    const auto px = ord.price();
                    if (px.isNull()) continue;

                    if (copied >= b3::md::OrdersSnapshot::K) {
                        truncated = true;
                        break;
                    }

                    out.bids[copied].priceMantissa = static_cast<int64_t>(px.mantissa());
                    out.bids[copied].qty          = static_cast<int64_t>(ord.quantity());
                    ++copied;
                }
            }

            out.bidsCopied   = copied;
            out.bidTruncated = truncated ? 1 : 0;
        }

        // Copia asks
        {
            const auto asksRange = book.asks();
            const size_t raw = asksRange.size();
            out.askCountRaw = static_cast<uint16_t>(raw > 0xFFFFu ? 0xFFFFu : raw);

            uint16_t copied = 0;
            bool truncated = false;

            for (size_t i = 0; i < raw; ++i) {
                const auto& ord = asksRange[i];

                const auto px = ord.price();
                if (px.isNull()) {
                    // Market order: se saltea; no contribuye al agregado MBP por niveles de precio.
                    continue;
                }

                if (copied >= b3::md::OrdersSnapshot::K) {
                    truncated = true;
                    break;
                }

                out.asks[copied].priceMantissa = static_cast<int64_t>(px.mantissa());
                out.asks[copied].qty          = static_cast<int64_t>(ord.quantity());
                ++copied;
            }

            out.asksCopied   = copied;
            out.askTruncated = truncated ? 1 : 0;
        }
    }
};

} // namespace b3::md::onixs
