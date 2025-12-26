#include <gtest/gtest.h>

#include "../../b3-md-connector/src/core/MarketDataEngine.hpp"
#include "../../b3-md-connector/src/core/MdPublishPipeline.hpp"
#include "../../b3-md-connector/src/core/MdPublishWorker.hpp"
#include "../../b3-md-connector/src/testsupport/OrdersSnapshotFromMbpView.hpp"
#include "FakeOrderBook.hpp"

#include <atomic>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>

using namespace b3::md;
using namespace b3::md::test;

// Publisher que cuenta publicaciones (thread-safe).
struct CountingSink final : b3::md::publishing::IPublishSink {
  bool tryPublish(uint32_t, const b3::md::publishing::PublishEvent &) noexcept override {
    published.fetch_add(1, std::memory_order_relaxed);
    return true;
  }
  std::atomic<uint64_t> published{0};
};

// Mapper de test: no aloca pesado, solo dispara publish.
struct TestMapper final : MdSnapshotMapper {
  void mapAndSerialize(const BookSnapshot &, std::string &out) const { out.assign("x"); }
};

TEST(MarketDataEngineTests, EnqueuesAndPublishes) {
  TestMapper mapper;
  CountingSink sink;

  auto worker = std::make_unique<MdPublishWorker>(0, mapper, sink);
  std::vector<std::unique_ptr<MdPublishWorker>> workers;
  workers.push_back(std::move(worker));

  MdPublishPipeline pipeline(std::move(workers));
  pipeline.start();

  FakeOrderBook book;
  book.setInstrumentId(42);
  book.setExchangeTsNs(123);
  book.setBidCount(1);
  book.setAskCount(1);
  book.setBidLevel(0, b3::md::Level{10, 5});
  book.setAskLevel(0, b3::md::Level{11, 7});

  auto snapshot = b3::md::testsupport::makeOrdersSnapshotFromMbpView(book);

  pipeline.tryEnqueue(snapshot);

  const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(200);

  while (sink.published.load(std::memory_order_relaxed) < 1 &&
         std::chrono::steady_clock::now() < deadline) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  pipeline.stop(true);

  EXPECT_GE(sink.published.load(), 1u);
}

TEST(MarketDataEngineTests, EnqueueNeverBlocks) {
  CountingSink sink;
  MdSnapshotMapper mapper;

  std::vector<std::unique_ptr<MdPublishWorker>> workers;
  workers.emplace_back(std::make_unique<MdPublishWorker>(0, mapper, sink));
  MdPublishPipeline pipeline(std::move(workers));
  pipeline.start();

  FakeOrderBook book;
  book.setInstrumentId(1);
  book.setExchangeTsNs(1);
  book.setBidCount(0);
  book.setAskCount(0);

  for (int i = 0; i < 100000; ++i) {
    auto snapshot = b3::md::testsupport::makeOrdersSnapshotFromMbpView(book);
    pipeline.tryEnqueue(snapshot);
  }

  pipeline.stop(false);
  SUCCEED();
}
