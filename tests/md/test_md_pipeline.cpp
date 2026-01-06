#include <gtest/gtest.h>

#include "../../b3-md-connector/src/core/MdPublishPipeline.hpp"
#include "../../b3-md-connector/src/core/MdPublishWorker.hpp"
#include "../../b3-md-connector/src/mapping/MdSnapshotMapper.hpp"
#include "../../b3-md-connector/src/testsupport/FakeInstrumentTopicMapper.hpp"
#include "FakePublishSink.hpp"
#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

using namespace b3::md;
using b3::md::mapping::MdSnapshotMapper;

namespace {

  // Test mapper that uses simple text format (not protobuf) for easy parsing
  class TestMdSnapshotMapper final : public b3::md::mapping::MdSnapshotMapper {
   public:
    bool mapToSerializedEnvelope(const b3::md::BookSnapshot &s,
                                 b3::md::publishing::SerializedEnvelope &ev,
                                 const char* topic,
                                 std::uint8_t topicLen) const noexcept override {
      if (topicLen == 0 || topicLen > b3::md::publishing::SerializedEnvelope::kMaxTopic)
        return false;

      // Simple text format: iid=123;ts=456;bc=1;ac=1
      char buf[256];
      int n = std::snprintf(buf, sizeof(buf), "iid=%llu;ts=%llu;bc=%u;ac=%u",
                            static_cast<unsigned long long>(s.instrumentId),
                            static_cast<unsigned long long>(s.exchangeTsNs),
                            static_cast<unsigned>(s.bidCount),
                            static_cast<unsigned>(s.askCount));
      if (n <= 0 || static_cast<size_t>(n) >= sizeof(buf))
        return false;

      ev.size = static_cast<uint32_t>(n);
      if (ev.size > b3::md::publishing::SerializedEnvelope::kMaxBytes)
        return false;

      std::memcpy(ev.bytes, buf, n);
      ev.topicLen = topicLen;
      std::memcpy(ev.topic, topic, topicLen);
      return true;
    }
  };

  uint64_t ParseTs(const std::string &bytes) {
    auto pos = bytes.find(";ts=");
    EXPECT_NE(pos, std::string::npos);
    if (pos == std::string::npos)
      return 0;

    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    if (end == std::string::npos)
      return 0;

    return std::stoull(bytes.substr(pos, end - pos));
  }

  uint32_t ParseIid(const std::string &bytes) {
    auto pos = bytes.find("iid=");
    EXPECT_EQ(pos, 0u);
    if (pos != 0u)
      return 0;

    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    if (end == std::string::npos)
      return 0;

    return static_cast<uint32_t>(std::stoul(bytes.substr(pos, end - pos)));
  }

  MdPublishPipeline BuildPipeline(uint32_t shards, TestMdSnapshotMapper &mapper,
                                  testsupport::FakePublishSink &sink) {
    std::vector<std::unique_ptr<MdPublishWorker>> workers;
    workers.reserve(shards);

    // IMPORTANT:
    // El worker guarda un puntero/referencia al mapper de topics para armar el topic en hot path.
    // Si el mapper vive en stack (local) y devolvés el pipeline, queda dangling y crashea.
    static testsupport::FakeInstrumentTopicMapper fakeTopics{
        {1, "AAA"}, {2, "BBB"}, {3, "CCC"}, {4, "DDD"}, {5, "EEE"}, {6, "FFF"},
    };

    for (uint32_t i = 0; i < shards; ++i) {
      workers.emplace_back(std::make_unique<MdPublishWorker>(i, mapper, sink, fakeTopics.get()));
    }

    return MdPublishPipeline(std::move(workers));
  }
} // namespace

TEST(MdPublishPipelineTests, PreservesFifoOrderPerInstrument) {
  testsupport::FakePublishSink sink;
  TestMdSnapshotMapper mapper;

  auto pipeline = BuildPipeline(4, mapper, sink);
  pipeline.start();

  constexpr int EVENTS_PER_INSTRUMENT = 10'000;
  const std::vector<uint64_t> instruments = {1, 2, 3, 4, 5, 6};

  for (uint64_t iid : instruments) {
    for (int i = 0; i < EVENTS_PER_INSTRUMENT; ++i) {
      OrdersSnapshot s{};
      s.instrumentId = iid;
      s.exchangeTsNs = static_cast<uint64_t>(i);

      // Para que el agregador produzca bid/askCount > 0 (opcional):
      s.bidsCopied = 1;
      s.asksCopied = 1;
      s.bids[0] = {.priceMantissa = 1000 + i, .qty = 1};
      s.asks[0] = {.priceMantissa = 2000 + i, .qty = 1};

      while (!pipeline.tryEnqueue(s)) {
        std::this_thread::yield();
      }
    }
  }

  const size_t expected = instruments.size() * static_cast<size_t>(EVENTS_PER_INSTRUMENT);

  const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);

  while (sink.count() < expected && std::chrono::steady_clock::now() < deadline) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  pipeline.stop(true);

  ASSERT_EQ(sink.count(), expected);

  // Agrupar timestamps por instrumento
  std::unordered_map<uint64_t, std::vector<uint64_t>> seen;
  seen.reserve(instruments.size());

  for (size_t i = 0; i < expected; ++i) {
    const auto msg = sink.at(i);
    seen[ParseIid(msg.bytes)].push_back(ParseTs(msg.bytes));
  }

  // FIFO estricto por instrumento
  for (const auto &[iid, tss] : seen) {
    ASSERT_FALSE(tss.empty());
    for (size_t i = 1; i < tss.size(); ++i) {
      EXPECT_EQ(tss[i], tss[i - 1] + 1) << "iid=" << iid;
    }
  }
}

TEST(MdPublishPipelineTests, ProgressUnderMultipleInstruments) {
  testsupport::FakePublishSink sink;
  TestMdSnapshotMapper mapper;

  auto pipeline = BuildPipeline(2, mapper, sink);
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

  const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);

  while (sink.count() < expected && std::chrono::steady_clock::now() < deadline) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  pipeline.stop(true);

  ASSERT_EQ(sink.count(), expected);
}