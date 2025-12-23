#include <gtest/gtest.h>

#include "../../b3-md-connector/src/core/MdPublishPipeline.hpp"
#include "../../b3-md-connector/src/core/MdPublishWorker.hpp"
#include "../../b3-md-connector/src/testsupport/FakePublisher.hpp"
#include "../../b3-md-connector/src/mapping/MdSnapshotMapper.hpp"

#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using namespace b3::md;

namespace {

uint64_t ParseTs(const std::string& bytes) {
    auto pos = bytes.find(";ts=");
    EXPECT_NE(pos, std::string::npos);
    if (pos == std::string::npos) return 0;

    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    if (end == std::string::npos) return 0;

    return std::stoull(bytes.substr(pos, end - pos));
}

uint32_t ParseIid(const std::string& bytes) {
    auto pos = bytes.find("iid=");
    EXPECT_EQ(pos, 0u);
    if (pos != 0u) return 0;

    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    if (end == std::string::npos) return 0;

    return static_cast<uint32_t>(std::stoul(bytes.substr(pos, end - pos)));
}

MdPublishPipeline BuildPipeline(uint32_t shards,
                               MdSnapshotMapper& mapper,
                               testsupport::FakePublisher &pub) {
    std::vector<std::unique_ptr<MdPublishWorker>> workers;
    workers.reserve(shards);

    for (uint32_t i = 0; i < shards; ++i) {
        workers.emplace_back(
            std::make_unique<MdPublishWorker>(i, mapper, pub));
    }

    return MdPublishPipeline(std::move(workers));
}

} // namespace

TEST(MdPublishPipelineTests, PreservesFifoOrderPerInstrument) {
    testsupport::FakePublisher pub;
    MdSnapshotMapper mapper;


    auto pipeline = BuildPipeline(4, mapper, pub);
    pipeline.start();

    constexpr int EVENTS_PER_INSTRUMENT = 10'000;
    const std::vector<uint32_t> instruments = {1, 2, 3, 4, 5, 6};

    for (uint32_t iid : instruments) {
        for (int i = 0; i < EVENTS_PER_INSTRUMENT; ++i) {
            OrdersSnapshot s{};
            s.instrumentId = iid;
            s.exchangeTsNs = static_cast<uint64_t>(i);

            // Para que el agregador produzca bid/askCount > 0 (opcional):
            s.bidsCopied = 1;
            s.asksCopied = 1;
            s.bids[0] = { .priceMantissa = 1000 + i, .qty = 1 };
            s.asks[0] = { .priceMantissa = 2000 + i, .qty = 1 };

            while (!pipeline.tryEnqueue(s)) {
                std::this_thread::yield();
            }
        }
    }

    const size_t expected =
        instruments.size() * static_cast<size_t>(EVENTS_PER_INSTRUMENT);

    const auto deadline =
        std::chrono::steady_clock::now() + std::chrono::seconds(5);

    while (pub.count() < expected &&
           std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop(true);

    ASSERT_EQ(pub.count(), expected);

    // Agrupar timestamps por instrumento
    std::unordered_map<uint32_t, std::vector<uint64_t>> seen;
    seen.reserve(instruments.size());

    for (size_t i = 0; i < expected; ++i) {
        const auto msg = pub.at(i);
        seen[ParseIid(msg.bytes)].push_back(ParseTs(msg.bytes));
    }

    // FIFO estricto por instrumento
    for (const auto& [iid, tss] : seen) {
        ASSERT_FALSE(tss.empty());
        for (size_t i = 1; i < tss.size(); ++i) {
            EXPECT_EQ(tss[i], tss[i - 1] + 1) << "iid=" << iid;
        }
    }
}

TEST(MdPublishPipelineTests, ProgressUnderMultipleInstruments) {
    testsupport::FakePublisher pub;
    MdSnapshotMapper mapper;


    auto pipeline = BuildPipeline(2, mapper, pub);
    pipeline.start();

    constexpr int N = 50'000;

    const uint32_t iidA = 1;
    const uint32_t iidB = 2;

    for (int i = 0; i < N; ++i) {
        OrdersSnapshot a{}, b{};
        a.instrumentId = iidA;
        a.exchangeTsNs = static_cast<uint64_t>(i);
        b.instrumentId = iidB;
        b.exchangeTsNs = static_cast<uint64_t>(i);

        while (!pipeline.tryEnqueue(a)) std::this_thread::yield();
        while (!pipeline.tryEnqueue(b)) std::this_thread::yield();
    }

    const size_t expected = static_cast<size_t>(2 * N);

    const auto deadline =
        std::chrono::steady_clock::now() + std::chrono::seconds(5);

    while (pub.count() < expected &&
           std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop(true);

    ASSERT_EQ(pub.count(), expected);
}