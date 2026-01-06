#pragma once

#include "../core/IMarketDataHandler.hpp"

#include <OnixS/B3/MarketData/UMDF/Handler.h>

#include <cstdint>

namespace b3::md::onixs {

  /**
   * @brief Wrapper that adapts OnixS Handler to IMarketDataHandler interface
   *
   * This allows the subscription server to call subscribe/unsubscribe
   * on the OnixS Handler without direct coupling to OnixS types.
   *
   * OnixS UMDF requires explicit subscriptions per instrument. Without
   * subscribing, no market data updates will be received for that instrument.
   */
  class OnixsHandlerWrapper final : public IMarketDataHandler {
   public:
    explicit OnixsHandlerWrapper(::OnixS::B3::MarketData::UMDF::Handler& handler)
        : handler_(handler) {}

    void subscribe(uint64_t instrumentId) override {
      // OnixS Handler.subscribe(SecurityID) API
      // SecurityID is typedef for uint64_t
      handler_.subscribe(instrumentId);
    }

    void unsubscribe(uint64_t instrumentId) override {
      // OnixS Handler.unsubscribe(SecurityID) API
      handler_.unsubscribe(instrumentId);
    }

   private:
    ::OnixS::B3::MarketData::UMDF::Handler& handler_;
  };

} // namespace b3::md::onixs
