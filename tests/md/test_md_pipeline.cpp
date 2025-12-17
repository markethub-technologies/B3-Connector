#include <gtest/gtest.h>

#include "../../b3-md-connector/src/MdPublishPipeline.hpp"
#include "../../b3-md-connector/src/FakePublisher.hpp"
#include "../../b3-md-connector/src/MdSnapshotMapper.hpp"

#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>

using namespace b3::md;

static uint64_t ParseTs(const std::string& bytes) {
    auto pos = bytes.find(";ts=");
    EXPECT_NE(pos, std::string::npos);
    if (pos == std::string::npos) return 0;

    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    if (end == std::string::npos) return 0;

    return std::stoull(bytes.substr(pos, end - pos));
}

static uint32_t ParseIid(const std::string& bytes) {
    auto pos = bytes.find("iid=");
    EXPECT_EQ(pos, 0u);
    if (pos != 0u) return 0;

    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    if (end == std::string::npos) return 0;

    return static_cast<uint32_t>(std::stoul(bytes.substr(pos, end - pos)));
}

TEST(MdPublishPipelineTests, ShardingAndOrderPerInstrument) {
    FakePublisher pub;
    MdSnapshotMapper mapper;

    constexpr uint32_t SHARDS = 4;
    MdPublishPipeline pipeline(SHARDS, mapper, pub, "md.snapshot");
    pipeline.start();

    constexpr int EVENTS_PER_INSTRUMENT = 10000;
    std::vector<uint32_t> instruments = {1, 2, 3, 4, 5, 6};

    for (uint32_t iid : instruments) {
        for (int i = 0; i < EVENTS_PER_INSTRUMENT; ++i) {
            BookSnapshot s{};
            s.instrumentId = iid;
            s.exchangeTsNs = static_cast<uint64_t>(i);

            while (!pipeline.enqueue(s)) {
                std::this_thread::yield();
            }
        }
    }

    const size_t expected = instruments.size() * static_cast<size_t>(EVENTS_PER_INSTRUMENT);

    // Esperar drenado con timeout para evitar hang
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (pub.count() < expected && std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop();

    ASSERT_EQ(pub.count(), expected);

    // Agrupar por instrumento
    std::unordered_map<uint32_t, std::vector<uint64_t>> seen;
    seen.reserve(instruments.size());

    for (size_t i = 0; i < expected; ++i) {
        auto msg = pub.at(i);
        uint32_t iid = ParseIid(msg.bytes);
        uint64_t ts  = ParseTs(msg.bytes);
        seen[iid].push_back(ts);
    }

    // FIFO por instrumento
    for (const auto& [iid, tss] : seen) {
        ASSERT_FALSE(tss.empty());
        for (size_t i = 1; i < tss.size(); ++i) {
            EXPECT_EQ(tss[i], tss[i - 1] + 1) << "iid=" << iid;
        }
    }
}

TEST(MdPublishPipelineTests, MultipleShardsProgress) {
    FakePublisher pub;
    MdSnapshotMapper mapper;

    MdPublishPipeline pipeline(2, mapper, pub, "md.snapshot");
    pipeline.start();

    constexpr int N = 50000;

    // Instrumentos que caen en shards distintos (id % 2)
    const uint32_t iidA = 1; // shard 1
    const uint32_t iidB = 2; // shard 0

    for (int i = 0; i < N; ++i) {
        BookSnapshot s1{}, s2{};
        s1.instrumentId = iidA;
        s1.exchangeTsNs = static_cast<uint64_t>(i);
        s2.instrumentId = iidB;
        s2.exchangeTsNs = static_cast<uint64_t>(i);

        while (!pipeline.enqueue(s1)) std::this_thread::yield();
        while (!pipeline.enqueue(s2)) std::this_thread::yield();
    }

    const size_t expected = static_cast<size_t>(2 * N);

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (pub.count() < expected && std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop();

    ASSERT_EQ(pub.count(), expected);
}
