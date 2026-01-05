// B3MdSubscriptionServer.hpp
#pragma once

#include <atomic>
#include <memory>
#include <string>

#include <OnixS/B3/MarketData/UMDF/Handler.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Fields.h> // SecurityID typedef

#include <servers/SubscriberPublisher.h> // markethub::messaging::servers::SubscriberPublisher
#include <models/messages.pb.h>
#include <models/messageTypes.h>

#include "../mapping/InstrumentRegistry.hpp"
#include "../core/SubscriptionRegistry.hpp"

namespace b3::md::svc {

  class B3MdSubscriptionServer final : public markethub::messaging::servers::SubscriberPublisher {
   public:
    B3MdSubscriptionServer(const std::string &serverEndpoint, const std::string &publishingEndpoint,
                           std::function<void(const std::string &, const std::string &)> logCb,
                           std::atomic<bool> &registryReady,
                           b3::md::mapping::InstrumentRegistry &registry,
                           b3::md::SubscriptionRegistry &subs,
                           ::OnixS::B3::MarketData::UMDF::Handler &umdfHandler)
        : SubscriberPublisher(serverEndpoint, publishingEndpoint, std::move(logCb)),
          registryReady_(registryReady),
          registry_(registry),
          subs_(subs),
          umdfHandler_(umdfHandler) {}

   protected:
    std::unique_ptr<markethub::messaging::WrapperMessage> HandleMessage(
        const markethub::messaging::WrapperMessage &req) override {
      using markethub::messaging::WrapperMessage;

      // STRICT: no aceptamos subs hasta tener registry completo
      if (!registryReady_.load(std::memory_order_acquire)) {
        return nullptr; // o respondé "not ready" si tu contrato lo pide
      }

      if (req.message_type() !=
          std::string(markethub::messaging::models::MessageTypes::MarketDataSuscriptionRequest))
        return nullptr;

      // --------- ADAPTAR ESTO a tu proto real ----------
      // Ejemplo conceptual:
      //   bool subscribe = req.market_data_suscription_request().subscribe();
      //   std::string symbol = req.market_data_suscription_request().symbol();
      bool subscribe = true;
      std::string symbol;
      // --------------------------------------------------

      if (symbol.empty())
        return nullptr;

      b3::md::mapping::InstrumentId iid = 0;
      if (!registry_.tryResolveId(symbol) || iid == 0) {
        return nullptr; // símbolo inválido (no está en security definition)
      }

      const auto sid = static_cast<::OnixS::B3::MarketData::UMDF::Messaging::SecurityID>(iid);

      if (subscribe) {
        const bool first = subs_.add(iid);
        if (first) {
          umdfHandler_.subscribe(sid); // ✅ filtrado en OnixS
        }
      } else {
        const bool last = subs_.remove(iid);
        if (last) {
          umdfHandler_.unsubscribe(sid);
        }
      }

      // Respuesta opcional (si tu API espera ack)
      // Si no querés responder, devolvé nullptr.
      auto resp = std::make_unique<WrapperMessage>();
      resp->set_message_id(req.message_id());
      resp->set_message_type(
          std::string(markethub::messaging::models::MessageTypes::MarketDataSuscriptionResponse));
      resp->set_client_id(req.client_id());
      return resp;
    }

   private:
    std::atomic<bool> &registryReady_;
    b3::md::mapping::InstrumentRegistry &registry_;
    b3::md::SubscriptionRegistry &subs_;
    ::OnixS::B3::MarketData::UMDF::Handler &umdfHandler_;
  };

} // namespace b3::md::svc
