#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

namespace spdlog {
  class logger;
}

namespace orders {

  class OwnedBoeMessage;

  class OrderTranslator final {
   public:
    struct Deps final {
      std::shared_ptr<spdlog::logger> log;
    };

    explicit OrderTranslator(Deps deps);

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
