#pragma once

#include "../core/IOrderBookView.hpp"
#include "../core/BookSnapshot.hpp" // Level + kTopN (o el const que uses)

#include <OnixS/B3/MarketData/UMDF/OrderBook.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace b3::md::onixs {

class OnixsOrderBookView final : public b3::md::IOrderBookView {
public:
    explicit OnixsOrderBookView(const ::OnixS::B3::MarketData::UMDF::OrderBook& book) noexcept
        : book_(book) {}

    uint32_t instrumentId() const noexcept override {
        // SDK: InstrumentId es UInt64
        const auto iid64 = static_cast<uint64_t>(book_.instrumentId());
        return static_cast<uint32_t>(iid64); // asumimos entra en 32 bits (si no, subimos el tipo en core)
    }

    uint64_t exchangeTsNs() const noexcept override {
        // OrderBook no expone timestamp.
        // Fallback: monotonic now (sirve para detectar backlog/jitter, no latencia real exchange->publish).
        const auto now = std::chrono::steady_clock::now().time_since_epoch();
        return static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(now).count()
        );
    }

    uint32_t bidCount() const noexcept override {
        const auto n = book_.bids().size();
        return clampToTopN(n);
    }

    uint32_t askCount() const noexcept override {
        const auto n = book_.asks().size();
        return clampToTopN(n);
    }

    b3::md::Level bidLevel(uint32_t i) const noexcept override {
        const auto r = book_.bids();
        const auto n = r.size();
        const auto top = clampToTopN(n);

        if (i >= top || n == 0) return b3::md::Level{};

        // bids() en header dice "ascending bid prices" => mejor bid al final
        const size_t idx = (n - 1) - static_cast<size_t>(i);
        return mapOrderToLevel(r[idx]);
    }

    b3::md::Level askLevel(uint32_t i) const noexcept override {
        const auto r = book_.asks();
        const auto n = r.size();
        const auto top = clampToTopN(n);

        if (i >= top || n == 0) return b3::md::Level{};

        // Asumimos mejor ask al principio (lo típico).
        // Si ves que asks() viene descending realmente, cambiá a: idx = (n - 1) - i
        const size_t idx = static_cast<size_t>(i);
        return mapOrderToLevel(r[idx]);
    }

private:
    static uint32_t clampToTopN(size_t n) noexcept {
        // si tu TopN está en otro lado, ajustá este nombre:
        constexpr size_t TopN = static_cast<size_t>(5);
        return static_cast<uint32_t>(std::min(n, TopN));
    }

    static b3::md::Level mapOrderToLevel(const ::OnixS::B3::MarketData::UMDF::Order& o) noexcept {
        b3::md::Level lv{};

        // ---- qty ----
        // SDK: Quantity = Int64
        using QtyFieldT = decltype(lv.qty);
        lv.qty = static_cast<QtyFieldT>(o.quantity());

        // ---- price ----
        // SDK: PriceOptional (4 decimals), marketOrder => isNull()
        const auto p = o.price();
        if (p.isNull()) {
            // market order: precio "sin valor"
            // mantenemos default 0
            return lv;
        }

        const auto mant = p.mantissa(); // entero con 4 decimales

        using PriceFieldT = decltype(lv.price);
        if constexpr (std::is_floating_point_v<PriceFieldT>) {
            // Guardamos como double/float en unidades reales
            lv.price = static_cast<PriceFieldT>(static_cast<double>(mant) / 10000.0);
        } else {
            // Guardamos como entero "mantissa" (4 decimales)
            lv.price = static_cast<PriceFieldT>(mant);
        }

        return lv;
    }

private:
    const ::OnixS::B3::MarketData::UMDF::OrderBook& book_;
};

} // namespace b3::md::onixs
