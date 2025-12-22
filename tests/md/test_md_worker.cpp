#include "../../b3-md-connector/src/core/MdPublishWorker.hpp"
#include "../../b3-md-connector/src/testsupport/FakePublisher.hpp"
#include "../../b3-md-connector/src/mapping/MdSnapshotMapper.hpp"
#include "../../b3-md-connector/src/telemetry/ILogSink.hpp"
#include "../../b3-md-connector/src/core/OrdersSnapshot.hpp"
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using namespace b3::md;

static uint64_t parse_ts(const std::string& bytes) {
    auto pos = bytes.find(";ts=");
    EXPECT_NE(pos, std::string::npos);
    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    return std::stoull(bytes.substr(pos, end - pos));
}

namespace {
struct NullLogSink final : b3::md::telemetry::ILogSink {
    void publish(const b3::md::telemetry::LogEvent&) noexcept override {}
};
}

TEST(MdPublishWorkerTests, PublishesFifoOrder) {
    FakePublisher pub;
    MdSnapshotMapper mapper;
    NullLogSink logger;
    uint32_t shard = 1;

    MdPublishWorker worker(shard, mapper, pub, logger);
    worker.start();

    constexpr int N = 100000;
    for (int i = 0; i < N; ++i) {
        OrdersSnapshot s{};
        s.instrumentId = 77;
        s.exchangeTsNs = static_cast<uint64_t>(i);

        // opcional para bid/ask count:
        s.bidCountRaw = 1;
        s.askCountRaw = 1;
        s.bids[0] = { .priceMantissa = 1000, .qty = 1 };
        s.asks[0] = { .priceMantissa = 2000, .qty = 1 };

        while (!worker.tryEnqueue(s)) {
            std::this_thread::yield();
        }
    }

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (pub.count() < static_cast<size_t>(N) && std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    worker.stop(true);

    ASSERT_EQ(pub.count(), static_cast<size_t>(N));

    uint64_t last = 0;
    for (int i = 0; i < N; ++i) {
        auto m = pub.at(i);
        EXPECT_EQ(m.topic, "b3.md.book"); // topic fijo del worker
        uint64_t ts = parse_ts(m.bytes);
        if (i == 0) EXPECT_EQ(ts, 0);
        else EXPECT_EQ(ts, last + 1);
        last = ts;
    }
}

TEST(MdPublishWorkerTests, StopClean) {
    FakePublisher pub;
    MdSnapshotMapper mapper;
    NullLogSink logger;
    uint32_t shard = 1;

    MdPublishWorker worker(shard, mapper, pub, logger);
    worker.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    worker.stop(false);
    SUCCEED();
}

TEST(MdPublishWorkerTests, StopWithoutDrainDropsPending) {
    FakePublisher pub;
    MdSnapshotMapper mapper;
    NullLogSink logger;

    MdPublishWorker worker(0, mapper, pub, logger);
    worker.start();

    for (int i = 0; i < 1000; ++i) {
        OrdersSnapshot s{};
        s.instrumentId = 77;
        s.exchangeTsNs = static_cast<uint64_t>(i);

        // opcional para bid/ask count:
        s.bidCountRaw = 1;
        s.askCountRaw = 1;
        s.bids[0] = { .priceMantissa = 1000, .qty = 1 };
        s.asks[0] = { .priceMantissa = 2000, .qty = 1 };
        worker.tryEnqueue(s);
    }

    worker.stop(false);

    EXPECT_LT(pub.count(), 1000u); // no drenó todo
}

TEST(MdPublishWorkerTests, StopWithDrainPublishesAll) {
    FakePublisher pub;
    MdSnapshotMapper mapper;
    NullLogSink logger;

    MdPublishWorker worker(0, mapper, pub, logger);
    worker.start();

    for (int i = 0; i < 1000; ++i) {
    OrdersSnapshot s{};
    s.instrumentId = 77;
    s.exchangeTsNs = static_cast<uint64_t>(i);

    s.bidCountRaw = 1;
    s.askCountRaw = 1;
    s.bids[0] = { .priceMantissa = 1000, .qty = 1 };
    s.asks[0] = { .priceMantissa = 2000, .qty = 1 };

        while (!worker.tryEnqueue(s)) {
            std::this_thread::yield();
        }
    }

    worker.stop(true);
    EXPECT_EQ(pub.count(), 1000u);
}

static uint32_t parse_count(const std::string& bytes, const char* key) {
    std::string needle = std::string(";") + key + "="; // ";bc=" o ";ac="
    auto pos = bytes.find(needle);
    EXPECT_NE(pos, std::string::npos);
    if (pos == std::string::npos) return 0;

    pos += needle.size();
    auto end = bytes.find(';', pos);
    // si es el último campo, end puede ser npos; lo toleramos
    const std::string value = (end == std::string::npos)
        ? bytes.substr(pos)
        : bytes.substr(pos, end - pos);

    return static_cast<uint32_t>(std::stoul(value));
}

TEST(MdPublishWorkerTests, AggregationAffectsCountsInSerializedOutput) {
    FakePublisher pub;
    MdSnapshotMapper mapper;
    NullLogSink logger;

    MdPublishWorker worker(0, mapper, pub, logger);
    worker.start();

    OrdersSnapshot raw{};
    raw.instrumentId = 77;
    raw.exchangeTsNs = 999;

    // bids: dos órdenes mismo precio + una de otro -> 2 niveles
    raw.bidCountRaw = 3;
    raw.bids[0] = { .priceMantissa = 1000, .qty = 10 };
    raw.bids[1] = { .priceMantissa = 1000, .qty = 20 };
    raw.bids[2] = { .priceMantissa =  900, .qty =  1 };

    // asks: dos precios -> 2 niveles
    raw.askCountRaw = 3;
    raw.asks[0] = { .priceMantissa = 1100, .qty = 7 };
    raw.asks[1] = { .priceMantissa = 1100, .qty = 8 };
    raw.asks[2] = { .priceMantissa = 1200, .qty = 1 };

    while (!worker.tryEnqueue(raw)) {
        std::this_thread::yield();
    }

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(2);
    while (pub.count() < 1 && std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    worker.stop(true);

    ASSERT_GE(pub.count(), 1u);

    const auto msg = pub.at(0);
    EXPECT_EQ(msg.topic, "b3.md.book");

    const uint32_t bc = parse_count(msg.bytes, "bc");
    const uint32_t ac = parse_count(msg.bytes, "ac");

    EXPECT_EQ(bc, 2u);
    EXPECT_EQ(ac, 2u);
}



