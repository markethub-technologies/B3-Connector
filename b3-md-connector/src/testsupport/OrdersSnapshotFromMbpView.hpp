#pragma once

#include "../core/OrdersSnapshot.hpp"
#include "../core/IOrderBookView.hpp"

namespace b3::md::testsupport {

// Adapter MBP (niveles) -> OrdersSnapshot (ventana MBO fake)
// Uso exclusivo para tests.
// Cada nivel se copia como si fuera una "orden agregada".
inline OrdersSnapshot makeOrdersSnapshotFromMbpView(
    const IOrderBookView& book) noexcept
{
    OrdersSnapshot snapshot{};

    snapshot.instrumentId = book.instrumentId();
    snapshot.exchangeTsNs = book.exchangeTsNs();

    const uint32_t bidN = book.bidCount();
    const uint32_t askN = book.askCount();

    uint16_t writtenBid = 0;
    for (uint32_t i = 0;
         i < bidN && writtenBid < OrdersSnapshot::K;
         ++i)
    {
        const auto lv = book.bidLevel(i);
        snapshot.bids[writtenBid].priceMantissa = lv.price;
        snapshot.bids[writtenBid].qty = lv.qty;
        ++writtenBid;
    }

    snapshot.bidCountRaw = writtenBid;
    snapshot.bidsCopied  = writtenBid;
    snapshot.bidTruncated = (bidN > OrdersSnapshot::K) ? 1u : 0u;

    uint16_t writtenAsk = 0;
    for (uint32_t i = 0;
         i < askN && writtenAsk < OrdersSnapshot::K;
         ++i)
    {
        const auto lv = book.askLevel(i);
        snapshot.asks[writtenAsk].priceMantissa = lv.price;
        snapshot.asks[writtenAsk].qty = lv.qty;
        ++writtenAsk;
    }

    snapshot.askCountRaw = writtenAsk;
    snapshot.asksCopied  = writtenAsk;
    snapshot.askTruncated = (askN > OrdersSnapshot::K) ? 1u : 0u;

    return snapshot;
}

} // namespace b3::md::testsupport
