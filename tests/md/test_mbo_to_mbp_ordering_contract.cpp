#include <gtest/gtest.h>

#include "../../b3-md-connector/src/core/OrdersSnapshot.hpp"
#include "../../b3-md-connector/src/core/BookSnapshot.hpp"
#include "../../b3-md-connector/src/core/MboToMbpAggregator.hpp"

using namespace b3::md;

TEST(MboToMbpAggregatorOrderingContractTests, BestFirstInputProducesTrueTopN) {
    OrdersSnapshot in{};
    in.instrumentId = 7;
    in.exchangeTsNs = 777;

    // Queremos 10 precios únicos por lado.
    // "Contrato" para este test: input ya viene best-first.
    // - bids: best -> worst (mayor a menor)
    // - asks: best -> worst (menor a mayor)

    constexpr int N = 10;

    // BID: 2000,1999,...,1991
    in.bidCountRaw = N;
    in.bidsCopied  = N;
    for (int i = 0; i < N; ++i) {
        in.bids[i].priceMantissa = 2000 - i;
        in.bids[i].qty = 1;
    }

    // ASK: 3000,3001,...,3009
    in.askCountRaw = N;
    in.asksCopied  = N;
    for (int i = 0; i < N; ++i) {
        in.asks[i].priceMantissa = 3000 + i;
        in.asks[i].qty = 1;
    }

    BookSnapshot out{};
    aggregateMboWindowToMbpTopN(in, out);

    EXPECT_EQ(out.instrumentId, 7u);
    EXPECT_EQ(out.exchangeTsNs, 777u);

    ASSERT_EQ(out.bidCount, BookSnapshot::DEPTH);
    ASSERT_EQ(out.askCount, BookSnapshot::DEPTH);

    // Top-5 bids esperados: 2000..1996
    for (int i = 0; i < BookSnapshot::DEPTH; ++i) {
        const int64_t expectedPx = 2000 - i;
        EXPECT_EQ(out.bids[i].price, expectedPx) << "i=" << i;
        EXPECT_EQ(out.bids[i].qty, 1) << "i=" << i;
    }

    // Top-5 asks esperados: 3000..3004
    for (int i = 0; i < BookSnapshot::DEPTH; ++i) {
        const int64_t expectedPx = 3000 + i;
        EXPECT_EQ(out.asks[i].price, expectedPx) << "i=" << i;
        EXPECT_EQ(out.asks[i].qty, 1) << "i=" << i;
    }
}
