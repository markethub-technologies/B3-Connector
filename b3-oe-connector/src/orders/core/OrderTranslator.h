#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <array>

namespace spdlog {
  class logger;
}

namespace orders {

  class OwnedBoeMessage;

  class OrderTranslator final {
   public:
    struct Deps final {
      std::shared_ptr<spdlog::logger> log;

      // BOE requires fixed-length fields:
      //  - senderLocation: 10 chars
      //  - enteringTrader: 5 chars
      //
      // We store them padded with spaces (no heap per send).
      std::array<char, 10> senderLocation{};
      std::array<char, 5> enteringTrader{};
    };

    OrderTranslator::OrderTranslator(Deps deps) : deps_(std::move(deps)) {
      if (!deps_.log)
        throw std::runtime_error("OrderTranslator: log is null");
    }

    bool tryBuildNewOrder(const uint8_t *req, std::size_t reqSize, OwnedBoeMessage &outMsg,
                          std::string &errorOut) noexcept;

    bool tryBuildCancel(const uint8_t *req, std::size_t reqSize, OwnedBoeMessage &outMsg,
                        std::string &errorOut) noexcept;

    bool tryBuildReplace(const uint8_t *req, std::size_t reqSize, OwnedBoeMessage &outMsg,
                         std::string &errorOut) noexcept;

   private:
    Deps deps_;
  };

} // namespace orders