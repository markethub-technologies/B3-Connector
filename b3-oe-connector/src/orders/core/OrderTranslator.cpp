#include "OrderTranslator.h"

#include <stdexcept>

#include <spdlog/logger.h>
#include <OnixS/B3/BOE/Messaging.h>
#include <OnixS/B3/BOE/Session.h>

#include "OwnedBoeMessage.hpp"

namespace orders {

  OrderTranslator::OrderTranslator(Deps deps) : deps_(std::move(deps)) {
    if (!deps_.log)
      throw std::runtime_error("OrderTranslator: log is null");
  }

  bool OrderTranslator::tryBuildNewOrder(const uint8_t * /*req*/, std::size_t /*reqSize*/,
                                         OwnedBoeMessage &outMsg, std::string &errorOut) noexcept {
    try {
      using namespace OnixS::B3::BOE::Messaging;

      // Per OnixS docs: typedef MessageHolder<NewOrderSingle102> NewOrderSingle;
      // :contentReference[oaicite:3]{index=3}
      using NewOrder = MessageHolder<NewOrderSingle102>;

      NewOrder
          order; // optional fields set to null by default :contentReference[oaicite:4]{index=4}

      // TODO: map wrapper fields into *order (order->field(...))
      // e.g.: order->clOrdId(...), order->side(...), etc.

      outMsg = OwnedBoeMessage::make(std::move(order));
      return true;
    } catch (const std::exception &ex) {
      errorOut = ex.what();
      return false;
    } catch (...) {
      errorOut = "unknown exception building NewOrder";
      return false;
    }
  }

  bool OrderTranslator::tryBuildCancel(const uint8_t * /*req*/, std::size_t /*reqSize*/,
                                       OwnedBoeMessage & /*outMsg*/,
                                       std::string &errorOut) noexcept {
    errorOut = "Cancel not implemented";
    return false;
  }

  bool OrderTranslator::tryBuildReplace(const uint8_t * /*req*/, std::size_t /*reqSize*/,
                                        OwnedBoeMessage & /*outMsg*/,
                                        std::string &errorOut) noexcept {
    errorOut = "Replace not implemented";
    return false;
  }

} // namespace orders
