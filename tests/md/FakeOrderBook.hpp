#pragma once
#include "../../b3-md-connector/src/core/IOrderBookView.hpp"
#include <array>

namespace b3::md::test {

class FakeOrderBook final : public b3::md::IOrderBookView {
public:
    void setInstrumentId(uint32_t v) { instrumentId_ = v; }
    void setExchangeTsNs(uint64_t v) { exchangeTsNs_ = v; }

    void setBidCount(uint32_t c) { bidCount_ = c; }
    void setAskCount(uint32_t c) { askCount_ = c; }

    void setBidLevel(uint32_t i, b3::md::Level lv) { bids_.at(i) = lv; }
    void setAskLevel(uint32_t i, b3::md::Level lv) { asks_.at(i) = lv; }

    uint32_t instrumentId() const noexcept override { return instrumentId_; }
    uint64_t exchangeTsNs() const noexcept override { return exchangeTsNs_; }

    uint32_t bidCount() const noexcept override { return bidCount_; }
    uint32_t askCount() const noexcept override { return askCount_; }

    b3::md::Level bidLevel(uint32_t i) const noexcept override { return bids_.at(i); }
    b3::md::Level askLevel(uint32_t i) const noexcept override { return asks_.at(i); }

private:
    uint32_t instrumentId_{0};
    uint64_t exchangeTsNs_{0};
    uint32_t bidCount_{0};
    uint32_t askCount_{0};
    std::array<b3::md::Level, 10> bids_{};
    std::array<b3::md::Level, 10> asks_{};
};

} // namespace b3::md::test