#include <gtest/gtest.h>

#include "../../b3-md-connector/src/core/IOrderBookView.hpp"
#include "../../b3-md-connector/src/core/BookSnapshotBuilder.hpp"
#include "../../b3-md-connector/src/core/MarketDataEngine.hpp"
#include "../../b3-md-connector/src/core/MdPublishPipeline.hpp"
#include "../../b3-md-connector/src/testsupport/FakePublisher.hpp"
#include "../../b3-md-connector/src/mapping/MdSnapshotMapper.hpp"

#include <array>
#include <chrono>
#include <thread>

using namespace b3::md;

namespace {

class FakeOrderBook final : public IOrderBookView {
public:
    void setInstrumentId(uint32_t v) { instrumentId_ = v; }
    void setExchangeTsNs(uint64_t v) { exchangeTsNs_ = v; }

    void setBidCount(uint32_t c) { bidCount_ = c; }
    void setAskCount(uint32_t c) { askCount_ = c; }

    void setBidLevel(uint32_t i, Level lv) { bids_.at(i) = lv; }
    void setAskLevel(uint32_t i, Level lv) { asks_.at(i) = lv; }

    uint32_t instrumentId() const noexcept override { return instrumentId_; }
    uint64_t exchangeTsNs() const noexcept override { return exchangeTsNs_; }

    uint32_t bidCount() const noexcept override { return bidCount_; }
    uint32_t askCount() const noexcept override { return askCount_; }

    Level bidLevel(uint32_t i) const noexcept override { return bids_.at(i); }
    Level askLevel(uint32_t i) const noexcept override { return asks_.at(i); }

private:
    uint32_t instrumentId_{0};
    uint64_t exchangeTsNs_{0};
    uint32_t bidCount_{0};
    uint32_t askCount_{0};
    std::array<Level, 5> bids_{};
    std::array<Level, 5> asks_{};
};

static uint32_t ParseBc(const std::string& bytes) {
    auto pos = bytes.find(";bc=");
    EXPECT_NE(pos, std::string::npos);
    if (pos == std::string::npos) return 0;
    pos += 4;
    auto end = bytes.find(';', pos);
    EXPECT_NE(end, std::string::npos);
    if (end == std::string::npos) return 0;
    return static_cast<uint32_t>(std::stoul(bytes.substr(pos, end - pos)));
}

static uint32_t ParseAc(const std::string& bytes) {
    auto pos = bytes.find(";ac=");
    EXPECT_NE(pos, std::string::npos);
    if (pos == std::string::npos) return 0;
    pos += 4;
    return static_cast<uint32_t>(std::stoul(bytes.substr(pos)));
}

} // namespace

TEST(BookSnapshotBuilderTests, CopiesLevelsAndClampsToDepth) {
    FakeOrderBook book;
    book.setInstrumentId(123);
    book.setExchangeTsNs(999);
    book.setBidCount(7); // > 5
    book.setAskCount(6); // > 5

    for (int i = 0; i < 5; ++i) {
        book.setBidLevel(i, Level{100 - i, 10 + i});
        book.setAskLevel(i, Level{101 + i, 20 + i});
    }

    auto s = buildSnapshot(book);

    EXPECT_EQ(s.instrumentId, 123u);
    EXPECT_EQ(s.exchangeTsNs, 999u);
    EXPECT_EQ(s.bidCount, 5);
    EXPECT_EQ(s.askCount, 5);

    EXPECT_EQ(s.bids[0].price, 100);
    EXPECT_EQ(s.asks[0].price, 101);
}

TEST(MarketDataEngineTests, EnqueuesAndPublishes) {
    FakePublisher pub;
    MdSnapshotMapper mapper;

    MdPublishPipeline pipeline(/*shards*/1, mapper, pub, "md.snapshot");
    pipeline.start();

    MarketDataEngine engine(pipeline);

    FakeOrderBook book;
    book.setInstrumentId(77);
    book.setExchangeTsNs(123456);
    book.setBidCount(5);
    book.setAskCount(5);

    for (int i = 0; i < 5; ++i) {
        book.setBidLevel(i, Level{100 - i, 10 + i});
        book.setAskLevel(i, Level{101 + i, 20 + i});
    }

    engine.onOrderBookUpdated(book);

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(2);
    while (pub.count() < 1 && std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pipeline.stop();

    ASSERT_GE(pub.count(), 1u);
    auto msg = pub.at(0);

    EXPECT_EQ(msg.topic, "md.snapshot");
    EXPECT_EQ(ParseBc(msg.bytes), 5u);
    EXPECT_EQ(ParseAc(msg.bytes), 5u);
    EXPECT_EQ(engine.drops(), 0u);
}