#pragma once

#include <cstdint>
#include <type_traits>

namespace b3::md {

// Ventana acotada de órdenes (MBO) copiada en hot path.
// Se agrega (MBO->MBP) en el worker para generar BookSnapshot (niveles de precio).
//
// Nota: las órdenes con precio null (market orders) se SALTEAN al copiar,
// porque no contribuyen al agregado por niveles de precio (MBP).
struct OrdersSnapshot {
    static constexpr uint32_t K = 256;

    struct OrderEntry {
        int64_t priceMantissa{0}; // precio con 4 decimales (mantissa)
        int64_t qty{0};           // Quantity (Int64)
    };

    uint32_t instrumentId{0};
    uint64_t exchangeTsNs{0};

    // Secuencias del SDK (las copiamos para futuro/protobuf/health)
    uint64_t rptSeq{0};      // OrderBook::lastRptSeq()
    uint64_t channelSeq{0};  // OrderBook::lastMessageSeqNumApplied()

    uint16_t bidCountRaw{0};
    uint16_t askCountRaw{0};

    uint8_t bidTruncated{0};
    uint8_t askTruncated{0};

    OrderEntry bids[K]{};
    OrderEntry asks[K]{};
};

static_assert(std::is_trivially_copyable_v<OrdersSnapshot>);
static_assert(std::is_trivially_destructible_v<OrdersSnapshot>);

} // namespace b3::md
