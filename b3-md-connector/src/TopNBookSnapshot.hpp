#pragma once
#include <cstdint>
#include <type_traits>

namespace b3::md {

struct Level {
    int64_t price{0}; // escala a defianir (ej: price * 1e4)
    int64_t qty{0};   // unidades / lots
};

template <int TOP_N>
struct TopNBookSnapshotT {
    static_assert(TOP_N > 0 && TOP_N <= 10, "TOP_N must be 1..10");

    uint32_t instrumentId{0};
    uint64_t exchangeTsNs{0};

    uint8_t bidCount{0};
    uint8_t askCount{0};

    Level bids[TOP_N]{};
    Level asks[TOP_N]{};
};

// Base “max” para no cambiar ABI si publicás 5/10
using TopNBookSnapshot10 = TopNBookSnapshotT<10>;

static_assert(std::is_trivially_copyable_v<TopNBookSnapshot10>);
static_assert(std::is_trivially_destructible_v<TopNBookSnapshot10>);

} // namespace b3::md
