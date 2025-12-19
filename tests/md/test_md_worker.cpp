#include "../../b3-md-connector/src/core/MdPublishWorker.hpp"
#include "../../b3-md-connector/src/testsupport/FakePublisher.hpp"
#include "../../b3-md-connector/src/mapping/MdSnapshotMapper.hpp"
#include "../../b3-md-connector/src/telemetry/ILogSink.hpp"
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
        BookSnapshot s{};
        s.instrumentId = 77;
        s.exchangeTsNs = static_cast<uint64_t>(i);

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
        BookSnapshot s{};
        s.instrumentId = 1;
        s.exchangeTsNs = i;
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
        BookSnapshot s{};
        s.instrumentId = 1;
        s.exchangeTsNs = i;
        worker.tryEnqueue(s);
    }

    worker.stop(true);

    EXPECT_EQ(pub.count(), 1000u);
}

TEST(MdPublishWorkerTests, StopWithDrainPublishesAll) {
    FakePublisher pub;
    MdSnapshotMapper mapper;
    NullLogSink logger;

    MdPublishWorker worker(0, mapper, pub, logger);
    worker.start();

    for (int i = 0; i < 1000; ++i) {
        BookSnapshot s{};
        s.instrumentId = 1;
        s.exchangeTsNs = i;
        worker.tryEnqueue(s);
    }

    worker.stop(true);

    EXPECT_EQ(pub.count(), 1000u);
}


