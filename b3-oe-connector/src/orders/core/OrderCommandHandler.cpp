#include "OrderCommandHandler.h"

#include <cstring>
#include <stdexcept>

#include <spdlog/logger.h>

#include "OrderTranslator.h"
#include "OwnedBoeMessage.hpp"
#include <string_view>
#include <models/messages.pb.h>
#include <models/messageTypes.h>

#include "../../boe/BoeSessionSender.h"

namespace orders {

  OrderCommandHandler::OrderCommandHandler(Deps deps) : deps_(std::move(deps)) {
    if (!deps_.log)
      throw std::runtime_error("OrderCommandHandler: log is null");
    if (!deps_.translator)
      throw std::runtime_error("OrderCommandHandler: translator is null");
    if (!deps_.sender)
      throw std::runtime_error("OrderCommandHandler: sender is null");
  }

  OrderCommandHandler::CommandType OrderCommandHandler::detectCommandType_(
      const uint8_t *req, std::size_t reqSize) noexcept {
    using markethub::messaging::models::MessageTypes;

    try {
      markethub::messaging::WrapperMessage wrapper;
      if (!wrapper.ParseFromArray(req, static_cast<int>(reqSize)))
        return CommandType::Unknown;

      const std::string &mtStr = wrapper.message_type();
      const std::string_view mt{mtStr.data(), mtStr.size()};

      if (mt == MessageTypes::NewOrderRequest)
        return CommandType::NewOrder;

      if (mt == MessageTypes::CancelOrderRequest)
        return CommandType::Cancel;

      if (mt == MessageTypes::ReplaceOrderRequest)
        return CommandType::Replace;

      return CommandType::Unknown;
    } catch (...) {
      return CommandType::Unknown;
    }
  }

  void OrderCommandHandler::writeOk_(std::vector<uint8_t> &out, const char *msg) noexcept {
    const char *prefix = "OK:";
    out.assign(prefix, prefix + std::strlen(prefix));
    if (msg)
      out.insert(out.end(), msg, msg + std::strlen(msg));
  }

  void OrderCommandHandler::writeErr_(std::vector<uint8_t> &out, const char *msg) noexcept {
    const char *prefix = "ERR:";
    out.assign(prefix, prefix + std::strlen(prefix));
    if (msg)
      out.insert(out.end(), msg, msg + std::strlen(msg));
  }

  bool OrderCommandHandler::handleRequest(const uint8_t *req, std::size_t reqSize,
                                          std::vector<uint8_t> &outResp) noexcept {
    try {
      if (!req || reqSize == 0) {
        writeErr_(outResp, "empty request");
        return false;
      }

      if (!deps_.sender->isReady()) {
        writeErr_(outResp, "boe session not established");
        return false;
      }

      const auto type = detectCommandType_(req, reqSize);
      std::string err;

      switch (type) {
        case CommandType::NewOrder: {
          OwnedBoeMessage boeMsg;
          if (!deps_.translator->tryBuildNewOrder(req, reqSize, boeMsg, err)) {
            writeErr_(outResp, err.c_str());
            return false;
          }

          deps_.sender->throttle();

          if (!deps_.sender->send(boeMsg)) {
            writeErr_(outResp, "send(NewOrder) failed");
            return false;
          }

          writeOk_(outResp, "new order sent");
          return true;
        }

        case CommandType::Cancel: {
          OwnedBoeMessage boeMsg;
          if (!deps_.translator->tryBuildCancel(req, reqSize, boeMsg, err)) {
            writeErr_(outResp, err.c_str());
            return false;
          }

          deps_.sender->throttle();

          if (!deps_.sender->send(boeMsg)) {
            writeErr_(outResp, "send(Cancel) failed");
            return false;
          }

          writeOk_(outResp, "cancel sent");
          return true;
        }

        case CommandType::Replace: {
          OwnedBoeMessage boeMsg;
          if (!deps_.translator->tryBuildReplace(req, reqSize, boeMsg, err)) {
            writeErr_(outResp, err.c_str());
            return false;
          }

          deps_.sender->throttle();

          if (!deps_.sender->send(boeMsg)) {
            writeErr_(outResp, "send(Replace) failed");
            return false;
          }

          writeOk_(outResp, "replace sent");
          return true;
        }

        case CommandType::Unknown:
        default:
          writeErr_(outResp, "unknown command type (wrapper parse TODO)");
          return false;
      }
    } catch (const std::exception &ex) {
      deps_.log->error("OrderCommandHandler exception: {}", ex.what());
      writeErr_(outResp, "internal exception");
      return false;
    } catch (...) {
      deps_.log->error("OrderCommandHandler unknown exception");
      writeErr_(outResp, "internal exception");
      return false;
    }
  }

} // namespace orders
