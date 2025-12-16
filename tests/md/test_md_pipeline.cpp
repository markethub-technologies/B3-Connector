#include "../../b3-md-connector/src/MdPublishPipeline.hpp"
#include "../../b3-md-connector/src/FakePublisher.hpp"
#include "../../b3-md-connector/src/MdSnapshotMapper.hpp"

#include <cassert>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace b3::md;

static uint64_t parse_ts(const std::string& bytes) {
    auto pos = bytes.find(";ts=");
    assert(pos != std::string::npos);
    pos += 4;
    auto end = bytes.find(';', pos);
    assert(end != std::string::npos);
    return std::stoull(bytes.substr(pos, end - pos));
}

static uint32_t parse_iid(const std::string& bytes) {
    auto pos = bytes.find("iid=");
    assert(pos == 0);
    pos += 4;
    auto end = bytes.find(';', pos);
    assert(end != std::string::npos);
    return static_cast<uint32_t>(std::stoul(bytes.substr(pos, end - pos)));
}

static void test_pipeline_sharding_and_order() {
    FakePublisher pub;
    MdSnapshotMapper mapper;

    constexpr uint32_t SHARDS = 4;
    MdPublishPipeline pipeline(SHARDS, mapper, pub, "md.snapshot");
    pipeline.start();

    constexpr int EVENTS_PER_INSTRUMENT = 10000;
    std::vector<uint32_t> instruments = {1, 2, 3, 4, 5, 6};

    // Produce
    for (uint32_t iid : instruments) {
        for (int i = 0; i < EVENTS_PER_INSTRUMENT; ++i) {
            TopNBookSnapshot10 s{};
            s.instrumentId = iid;
            s.exchangeTsNs = static_cast<uint64_t>(i);

            while (!pipeline.enqueue(s)) {
                std::this_thread::yield();
            }
        }
    }

    const size_t expected =
        instruments.size() * EVENTS_PER_INSTRUMENT;

    // Esperar drenado
    while (pub.count() < expected) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop();

    // Agrupar por instrumento
    std::unordered_map<uint32_t, std::vector<uint64_t>> seen;
    for (size_t i = 0; i < expected; ++i) {
        auto msg = pub.at(i);
        uint32_t iid = parse_iid(msg.bytes);
        uint64_t ts  = parse_ts(msg.bytes);
        seen[iid].push_back(ts);
    }

    // FIFO por instrumento
    for (auto& [iid, tss] : seen) {
        for (size_t i = 1; i < tss.size(); ++i) {
            assert(tss[i] == tss[i - 1] + 1);
        }
    }
}

static void test_pipeline_multiple_instruments_progress() {
    FakePublisher pub;
    MdSnapshotMapper mapper;

    MdPublishPipeline pipeline(2, mapper, pub, "md.snapshot");
    pipeline.start();

    constexpr int N = 50000;

    // Instrumentos que caen en shards distintos
    uint32_t iidA = 1; // shard 1
    uint32_t iidB = 2; // shard 0

    for (int i = 0; i < N; ++i) {
        TopNBookSnapshot10 s1{}, s2{};
        s1.instrumentId = iidA;
        s1.exchangeTsNs = i;
        s2.instrumentId = iidB;
        s2.exchangeTsNs = i;

        while (!pipeline.enqueue(s1)) std::this_thread::yield();
        while (!pipeline.enqueue(s2)) std::this_thread::yield();
    }

    while (pub.count() < static_cast<size_t>(2 * N)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop();

    // Si llegamos acá, ambos shards progresaron
    assert(pub.count() == static_cast<size_t>(2 * N));
}

int main() {
    test_pipeline_sharding_and_order();
    test_pipeline_multiple_instruments_progress();
    std::cout << "test_md_pipeline: OK\n";
    return 0;
}
