#include <gtest/gtest.h>

#include "../../b3-md-connector/src/core/OrdersSnapshot.hpp"
#include "../../b3-md-connector/src/core/BookSnapshot.hpp"
#include "../../b3-md-connector/src/core/MboToMbpAggregator.hpp"

using namespace b3::md;

TEST(MboToMbpAggregatorTests, AggregatesSamePriceIntoSingleLevel) {
    OrdersSnapshot in{};
    in.instrumentId = 42;
    in.exchangeTsNs = 123;

    // Bid side: 3 órdenes mismo precio, + 1 orden otro precio
    in.bidsCopied = 4;
    in.bids[0] = { .priceMantissa = 1000, .qty = 10 };
    in.bids[1] = { .priceMantissa = 1000, .qty = 20 };
    in.bids[2] = { .priceMantissa = 1000, .qty = 30 };
    in.bids[3] = { .priceMantissa =  900, .qty =  5 };

    // Ask side: 2 precios distintos
    in.asksCopied = 3;
    in.asks[0] = { .priceMantissa = 1100, .qty = 7 };
    in.asks[1] = { .priceMantissa = 1100, .qty = 8 };
    in.asks[2] = { .priceMantissa = 1200, .qty = 1 };

    BookSnapshot out{};
    aggregateMboWindowToMbpTopN(in, out);

    EXPECT_EQ(out.instrumentId, 42u);
    EXPECT_EQ(out.exchangeTsNs, 123u);

    ASSERT_EQ(out.bidCount, 2u);
    EXPECT_EQ(out.bids[0].price, 1000);
    EXPECT_EQ(out.bids[0].qty,   60);
    EXPECT_EQ(out.bids[1].price,  900);
    EXPECT_EQ(out.bids[1].qty,    5);

    ASSERT_EQ(out.askCount, 2u);
    EXPECT_EQ(out.asks[0].price, 1100);
    EXPECT_EQ(out.asks[0].qty,   15);
    EXPECT_EQ(out.asks[1].price, 1200);
    EXPECT_EQ(out.asks[1].qty,    1);
}

TEST(MboToMbpAggregatorTests, ProducesAtMostTopNLevels) {
    OrdersSnapshot in{};
    in.instrumentId = 1;
    in.exchangeTsNs = 1;

    // Generar 10 precios distintos (más que Top-5)
    in.bidsCopied = 10;
    for (int i = 0; i < 10; ++i) {
        in.bids[i] = { .priceMantissa = 1000 - i, .qty = 1 };
    }

    in.asksCopied = 10;
    for (int i = 0; i < 10; ++i) {
        in.asks[i] = { .priceMantissa = 2000 + i, .qty = 1 };
    }

    BookSnapshot out{};
    aggregateMboWindowToMbpTopN(in, out);

    EXPECT_EQ(out.bidCount, BookSnapshot::DEPTH);
    EXPECT_EQ(out.askCount, BookSnapshot::DEPTH);

    // Solo chequeamos que no exceda DEPTH y que los primeros existan
    EXPECT_NE(out.bids[0].price, 0);
    EXPECT_NE(out.asks[0].price, 0);
}

TEST(MboToMbpAggregatorTests, IgnoresZeroQtyOrders) {
    OrdersSnapshot in{};
    in.instrumentId = 9;
    in.exchangeTsNs = 9;

    in.bidsCopied = 3;
    in.bids[0] = { .priceMantissa = 1000, .qty = 0 };   // ignorar
    in.bids[1] = { .priceMantissa = 1000, .qty = 10 };  // sumar
    in.bids[2] = { .priceMantissa =  900, .qty = 0 };   // ignorar

    in.asksCopied = 0;

    BookSnapshot out{};
    aggregateMboWindowToMbpTopN(in, out);

    ASSERT_EQ(out.bidCount, 1u);
    EXPECT_EQ(out.bids[0].price, 1000);
    EXPECT_EQ(out.bids[0].qty,   10);
    EXPECT_EQ(out.askCount, 0u);
}
