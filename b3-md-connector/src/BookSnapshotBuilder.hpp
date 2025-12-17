#pragma once
#include "IOrderBookView.hpp"
#include "TopNBookSnapshot.hpp"
#include <algorithm>
#include <cstdint>

namespace b3::md {

inline BookSnapshot buildSnapshot(const IOrderBookView& book, uint32_t topN) noexcept {
    BookSnapshot s{};
    s.instrumentId = book.instrumentId();
    s.exchangeTsNs = book.exchangeTsNs();

    const uint32_t maxN = 10;
    const uint32_t n = std::min<uint32_t>(topN, maxN);

    const uint32_t bc = std::min<uint32_t>(book.bidCount(), n);
    const uint32_t ac = std::min<uint32_t>(book.askCount(), n);

    s.bidCount = static_cast<uint8_t>(bc);
    s.askCount = static_cast<uint8_t>(ac);

    for (uint32_t i = 0; i < bc; ++i) s.bids[i] = book.bidLevel(i);
    for (uint32_t i = 0; i < ac; ++i) s.asks[i] = book.askLevel(i);

    return s;
}

} // namespace b3::md
