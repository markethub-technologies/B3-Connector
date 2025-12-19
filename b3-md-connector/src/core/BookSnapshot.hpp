#pragma once
#include "IOrderBookView.hpp"   // o donde esté Level
#include <cstdint>
#include <type_traits>

namespace b3::md {

template<int N>
struct BookSnapshotT {
    static constexpr int DEPTH = N;

    uint32_t instrumentId{0};
    uint64_t exchangeTsNs{0};
    uint8_t bidCount{0};
    uint8_t askCount{0};

    Level bids[N]{};
    Level asks[N]{};
};

using BookSnapshot = BookSnapshotT<5>;

static_assert(std::is_trivially_copyable_v<BookSnapshot>);
static_assert(std::is_trivially_destructible_v<BookSnapshot>);

} // namespace b3::md
