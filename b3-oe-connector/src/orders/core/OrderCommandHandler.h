#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../server/OrderMessagingServer.h" // trae IOrderCommandHandler

namespace spdlog {
  class logger;
}
namespace boe {
  class BoeSessionSender;
}

namespace orders {

  class OrderTranslator;

  /**
   * Implements the raw-bytes request handler used by the ZMQ ROUTER server.
   */
  class OrderCommandHandler final : public IOrderCommandHandler {
   public:
    struct Deps final {
      std::shared_ptr<spdlog::logger> log;
      OrderTranslator *translator{nullptr};   // not owned
      boe::BoeSessionSender *sender{nullptr}; // not owned
    };

    explicit OrderCommandHandler(Deps deps);

    // IOrderCommandHandler
    bool handleRequest(const uint8_t *req, std::size_t reqSize,
                       std::vector<uint8_t> &outResp) noexcept override;

   private:
    enum class CommandType : uint8_t {
      Unknown = 0,
      NewOrder,
      Cancel,
      Replace,
    };

    CommandType detectCommandType_(const uint8_t *req, std::size_t reqSize) noexcept;

    void writeOk_(std::vector<uint8_t> &out, const char *msg) noexcept;
    void writeErr_(std::vector<uint8_t> &out, const char *msg) noexcept;

   private:
    Deps deps_;
  };

} // namespace orders
