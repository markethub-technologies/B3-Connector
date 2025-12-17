#include "../../b3-md-connector/src/MdPublishWorker.hpp"
#include "../../b3-md-connector/src/FakePublisher.hpp"
#include "../../b3-md-connector/src/MdSnapshotMapper.hpp"
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

TEST(MdPublishWorkerTests, PublishesFifoOrder) {
    FakePublisher pub;
    MdSnapshotMapper mapper;

    MdPublishWorker worker(mapper, pub, "md.snapshot");
    worker.start();

    constexpr int N = 100000;
    for (int i = 0; i < N; ++i) {
        BookSnapshot s{};
        s.instrumentId = 77;
        s.exchangeTsNs = static_cast<uint64_t>(i);

        while (!worker.try_enqueue(s)) {
            std::this_thread::yield();
        }
    }

    while (pub.count() < static_cast<size_t>(N)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    worker.stop();

    uint64_t last = 0;
    for (int i = 0; i < N; ++i) {
        auto m = pub.at(i);
        EXPECT_EQ(m.topic, "md.snapshot");
        uint64_t ts = parse_ts(m.bytes);
        if (i == 0) {
            EXPECT_EQ(ts, 0);
        } else {
            EXPECT_EQ(ts, last + 1);
        }
        last = ts;
    }
}

TEST(MdPublishWorkerTests, StopClean) {
    FakePublisher pub;
    MdSnapshotMapper mapper;

    MdPublishWorker worker(mapper, pub, "md.snapshot");
    worker.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    worker.stop();
    SUCCEED();
}
