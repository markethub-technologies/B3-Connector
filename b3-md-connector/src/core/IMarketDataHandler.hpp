#pragma once

#include <cstdint>

namespace b3::md {

  /**
   * @brief Interface for market data handler (abstracts OnixS Handler)
   *
   * This allows both real OnixS Handler and test fakes to be used
   * with the subscription server.
   */
  class IMarketDataHandler {
   public:
    virtual ~IMarketDataHandler() = default;

    /**
     * @brief Subscribe to market data for an instrument
     * @param instrumentId The instrument ID to subscribe to
     */
    virtual void subscribe(uint64_t instrumentId) = 0;

    /**
     * @brief Unsubscribe from market data for an instrument
     * @param instrumentId The instrument ID to unsubscribe from
     */
    virtual void unsubscribe(uint64_t instrumentId) = 0;
  };

} // namespace b3::md
