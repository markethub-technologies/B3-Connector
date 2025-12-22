#include <gtest/gtest.h>

#include "../../b3-md-connector/src/core/MarketDataEngine.hpp"
#include "../../b3-md-connector/src/core/MdPublishPipeline.hpp"
#include "../../b3-md-connector/src/core/MdPublishWorker.hpp"
#include "../../b3-md-connector/src/testsupport/FakePublisher.hpp"

#include "FakeOrderBook.hpp"

#include <atomic>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>

using namespace b3::md;
using namespace b3::md::test;


// Publisher que cuenta publicaciones (thread-safe).
struct CountingPublisher final : IMdPublisher {
    void publish(std::string_view, const uint8_t*, size_t) override {
        published.fetch_add(1, std::memory_order_relaxed);
    }
    std::atomic<uint64_t> published{0};
};

// Mapper de test: no aloca pesado, solo dispara publish.
struct TestMapper final : MdSnapshotMapper {
    void mapAndSerialize(const BookSnapshot&, std::string& out) const {
        out.assign("x");
    }
};


TEST(MarketDataEngineTests, EnqueuesAndPublishes) {
    TestMapper mapper;
    CountingPublisher publisher;

    auto worker = std::make_unique<MdPublishWorker>(0, mapper, publisher);
    std::vector<std::unique_ptr<MdPublishWorker>> workers;
    workers.push_back(std::move(worker));     // o emplace_back(std::move(worker))

    MdPublishPipeline pipeline(std::move(workers));

    pipeline.start();

    MarketDataEngine engine(pipeline);

    FakeOrderBook book;
    book.setInstrumentId(42);
    book.setExchangeTsNs(123);

    book.setBidCount(1);
    book.setAskCount(1);

    book.setBidLevel(0, b3::md::Level{ .price = 10, .qty = 5 });
    book.setAskLevel(0, b3::md::Level{ .price = 11, .qty = 7 });

    engine.onOrderBookUpdated(book);

    // Espera activa acotada a que el worker publique 1 vez
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(200);
    while (publisher.published.load(std::memory_order_relaxed) < 1 &&
           std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop(true);

    EXPECT_EQ(engine.drops(), 0u);
    EXPECT_GE(publisher.published.load(std::memory_order_relaxed), 1u);
}

TEST(MarketDataEngineTests, EnqueueNeverBlocks) {
    testsupport::FakePublisher pub;
    MdSnapshotMapper mapper;


    std::vector<std::unique_ptr<MdPublishWorker>> workers;
    workers.emplace_back(std::make_unique<MdPublishWorker>(0, mapper, pub));
    MdPublishPipeline pipeline(std::move(workers));
    pipeline.start();

    MarketDataEngine engine(pipeline);

    b3::md::test::FakeOrderBook book;
    book.setInstrumentId(1);
    book.setExchangeTsNs(1);
    book.setBidCount(0);
    book.setAskCount(0);

    for (int i = 0; i < 100000; ++i) {
        engine.onOrderBookUpdated(book);
    }

    pipeline.stop(false);
    SUCCEED();
}
