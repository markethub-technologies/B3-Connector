#pragma once

#include <OnixS/B3/MarketData/UMDF/MessageListener.h>
#include <OnixS/B3/MarketData/UMDF/OrderBookListener.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Messages.h>

#include "../mapping/InstrumentRegistry.hpp"
#include "../core/OrdersSnapshot.hpp"
#include "../core/IMarketDataHandler.hpp"
#include "../onixs/OnixsOrderBookListener.hpp"

#include <atomic>
#include <chrono>
#include <cstdint>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <algorithm>

namespace b3::md::testsupport {

  struct Security {
    uint64_t securityId;
    std::string symbol;
  };

  /**
   * FakeOnixsHandler - Simulates OnixS UMDF Handler for end-to-end testing
   *
   * This class mimics the OnixS Handler interface but generates synthetic
   * market data instead of receiving it from B3 multicast feed.
   */
  class FakeOnixsHandler final : public b3::md::IMarketDataHandler {
   public:
    FakeOnixsHandler() = default;

    // Set the registry reference (needed for direct population)
    void setRegistry(b3::md::mapping::InstrumentRegistry* registry,
                     std::atomic<bool>* readyFlag) {
      registry_ = registry;
      readyFlag_ = readyFlag;
    }


    // Load securities from JSON file
    bool loadSecurities(const std::string& filepath) {
      securities_.clear();

      std::ifstream file(filepath);
      if (!file.is_open()) {
        std::cerr << "[FakeHandler] ERROR: Cannot open " << filepath << "\n";
        return false;
      }

      // Simple JSON parsing (expects array format)
      std::string line;
      uint64_t id = 0;
      while (std::getline(file, line)) {
        // Look for "symbol": "XXX" pattern
        auto symPos = line.find("\"symbol\"");
        if (symPos == std::string::npos) continue;

        auto colonPos = line.find(':', symPos);
        if (colonPos == std::string::npos) continue;

        auto quote1 = line.find('"', colonPos);
        if (quote1 == std::string::npos) continue;

        auto quote2 = line.find('"', quote1 + 1);
        if (quote2 == std::string::npos) continue;

        std::string symbol = line.substr(quote1 + 1, quote2 - quote1 - 1);
        if (!symbol.empty()) {
          ++id;
          securities_.push_back({id, symbol});
          std::cerr << "[FakeHandler] Loaded security: " << id << " -> " << symbol << "\n";
        }
      }

      std::cerr << "[FakeHandler] Total securities loaded: " << securities_.size() << "\n";
      return !securities_.empty();
    }

    // Register listeners (mimics OnixS API)
    void registerMessageListener(::OnixS::B3::MarketData::UMDF::MessageListener* listener) {
      if (listener) messageListeners_.push_back(listener);
    }

    void registerOrderBookListener(::OnixS::B3::MarketData::UMDF::OrderBookListener* listener) {
      if (listener) orderBookListeners_.push_back(listener);
    }

    // IMarketDataHandler interface implementation
    void subscribe(uint64_t instrumentId) override {
      // In real OnixS, this would subscribe to market data for this instrument
      // In simulator, we're already generating data for all instruments
      std::cerr << "[FakeHandler] Subscribe request for instrument " << instrumentId << "\n";
    }

    void unsubscribe(uint64_t instrumentId) override {
      // In real OnixS, this would unsubscribe from market data
      // In simulator, we continue generating data
      std::cerr << "[FakeHandler] Unsubscribe request for instrument " << instrumentId << "\n";
    }

    // Trigger SecurityList (populates InstrumentRegistry directly)
    void triggerSecurityList() {
      std::cerr << "[FakeHandler] Triggering SecurityList...\n";

      if (!registry_) {
        std::cerr << "[FakeHandler] ERROR: Registry not set! Call setRegistry() first.\n";
        return;
      }

      // Populate registry directly (bypassing OnixS message listeners)
      // This avoids the reinterpret_cast issues with OnixS classes
      std::vector<std::pair<uint64_t, std::string>> pairs;
      pairs.reserve(securities_.size());

      for (const auto& sec : securities_) {
        pairs.emplace_back(sec.securityId, sec.symbol);
        std::cerr << "[FakeHandler] Registering: " << sec.securityId
                  << " -> " << sec.symbol << "\n";
      }

      // Bulk upsert
      registry_->bulkUpsert(pairs.begin(), pairs.end());

      // Set ready flag
      if (readyFlag_) {
        readyFlag_->store(true, std::memory_order_release);
      }

      std::cerr << "[FakeHandler] SecurityList complete. Registry ready!\n";
    }

    // Generate synthetic OrderBook update
    void generateOrderBookUpdate(const std::string& symbol, uint64_t basePrice) {
      auto it = std::find_if(securities_.begin(), securities_.end(),
                            [&](const Security& s) { return s.symbol == symbol; });
      if (it == securities_.end()) {
        return; // Skip unknown symbols silently
      }

      // Build OrdersSnapshot directly (bypasses OnixS OrderBook parsing)
      b3::md::OrdersSnapshot snapshot{};
      snapshot.instrumentId = it->securityId;
      snapshot.exchangeTsNs = nowNs();
      snapshot.rptSeq = 0;  // Not used in simulator
      snapshot.channelSeq = 0;  // Not used in simulator

      // Generate random bid/ask levels
      std::uniform_int_distribution<int> qtyDist(10, 100);

      // 3 bid levels (prices in mantissa format: 4 decimals)
      snapshot.bidCountRaw = 3;
      snapshot.bidsCopied = 3;
      snapshot.bidTruncated = 0;
      for (int i = 0; i < 3; ++i) {
        snapshot.bids[i].qty = qtyDist(rng_);
        snapshot.bids[i].priceMantissa = (basePrice - (i + 1) * 100) * 10000;  // Convert to mantissa
      }

      // 3 ask levels (prices in mantissa format: 4 decimals)
      snapshot.askCountRaw = 3;
      snapshot.asksCopied = 3;
      snapshot.askTruncated = 0;
      for (int i = 0; i < 3; ++i) {
        snapshot.asks[i].qty = qtyDist(rng_);
        snapshot.asks[i].priceMantissa = (basePrice + (i + 1) * 100) * 10000;  // Convert to mantissa
      }

      // Inject via testing-only path (bypasses OnixS reinterpret_cast issues)
      for (auto* listener : orderBookListeners_) {
        // Cast to our listener type to access the test method
        auto* ourListener = dynamic_cast<b3::md::onixs::OnixsOrderBookListener*>(listener);
        if (ourListener) {
          ourListener->injectTestSnapshot(snapshot);
        }
      }
    }

    // Start update generation loop
    void startUpdateLoop(std::chrono::milliseconds interval = std::chrono::milliseconds(100)) {
      running_.store(true, std::memory_order_release);
      updateThread_ = std::thread([this, interval] {
        std::cerr << "[FakeHandler] Update loop started (interval=" << interval.count() << "ms)\n";

        uint64_t updateCount = 0;
        while (running_.load(std::memory_order_acquire)) {
          // Generate updates for all securities
          for (const auto& sec : securities_) {
            uint64_t basePrice = 10000 + (sec.securityId * 1000);
            // Add some randomness to price
            basePrice += (updateCount % 10) * 10;
            generateOrderBookUpdate(sec.symbol, basePrice);
          }

          ++updateCount;
          std::this_thread::sleep_for(interval);
        }

        std::cerr << "[FakeHandler] Update loop stopped. Total updates: " << updateCount << "\n";
      });
    }

    void stopUpdateLoop() {
      running_.store(false, std::memory_order_release);
      if (updateThread_.joinable()) {
        updateThread_.join();
      }
    }

   private:
    static uint64_t nowNs() {
      const auto now = std::chrono::system_clock::now().time_since_epoch();
      return static_cast<uint64_t>(
          std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
    }

    // Fake SecurityDefinition_12 that mimics OnixS interface
    struct FakeSecurityDefinition {
      uint64_t securityId_;
      std::string symbol_;

      uint64_t securityId() const { return securityId_; }

      // OnixS returns a StrRef which has data() and size()
      struct StrRef {
        const char* ptr;
        size_t len;
        const char* data() const { return ptr; }
        size_t size() const { return len; }
      };

      StrRef symbol() const {
        return {symbol_.data(), symbol_.size()};
      }
    };

   private:
    std::vector<Security> securities_;
    std::vector<::OnixS::B3::MarketData::UMDF::MessageListener*> messageListeners_;
    std::vector<::OnixS::B3::MarketData::UMDF::OrderBookListener*> orderBookListeners_;

    b3::md::mapping::InstrumentRegistry* registry_{nullptr};
    std::atomic<bool>* readyFlag_{nullptr};

    std::atomic<bool> running_{false};
    std::thread updateThread_;
    std::mt19937 rng_{std::random_device{}()};
  };

} // namespace b3::md::testsupport
