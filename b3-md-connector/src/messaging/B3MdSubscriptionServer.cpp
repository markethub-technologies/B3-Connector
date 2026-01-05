#include "B3MdSubscriptionServer.hpp"

#include <type_traits>
#include <utility>

using markethub::messaging::WrapperMessage;
using markethub::messaging::models::MessageTypes;

namespace {

  template <class T>
  static std::string extractSymbolFromInstrument(const T &inst) {
    if constexpr (requires { inst.symbol(); })
      return inst.symbol();
    else if constexpr (requires { inst.ticker(); })
      return inst.ticker();
    else if constexpr (requires { inst.code(); })
      return inst.code();
    else if constexpr (requires { inst.name(); })
      return inst.name();
    else
      return {};
  }

  template <class Resp>
  static void set_ok_if_exists(Resp *r, bool ok) {
    if constexpr (requires { r->set_ok(ok); })
      r->set_ok(ok);
    else if constexpr (requires { r->set_success(ok); })
      r->set_success(ok);
  }

  template <class Resp>
  static void set_error_if_exists(Resp *r, const std::string &s) {
    if constexpr (requires { r->set_error(s); })
      r->set_error(s);
    else if constexpr (requires { r->set_message(s); })
      r->set_message(s);
    else if constexpr (requires { r->set_reason(s); })
      r->set_reason(s);
  }

  template <class Resp>
  static void set_request_id_if_exists(Resp *r, const std::string &s) {
    if constexpr (requires { r->set_request_id(s); })
      r->set_request_id(s);
    else if constexpr (requires { r->set_original_request_id(s); })
      r->set_original_request_id(s);
  }

} // namespace

namespace b3::md::messaging {

  B3MdSubscriptionServer::B3MdSubscriptionServer(const std::string &serverEndpoint,
                                                 const std::string &publishingEndpoint,
                                                 b3::md::mapping::InstrumentRegistry &registry,
                                                 b3::md::SubscriptionRegistry &subs,
                                                 ::OnixS::B3::MarketData::UMDF::Handler &handler,
                                                 LogCallback logCb)
      : SubscriberPublisher(serverEndpoint, publishingEndpoint, std::move(logCb)),
        registry_(registry),
        subs_(subs),
        handler_(handler) {}

  std::unique_ptr<WrapperMessage> B3MdSubscriptionServer::HandleMessage(
      const WrapperMessage &request) {
    // Filtrar por tipo (lo que manda C#)
    if (request.message_type() != std::string(MessageTypes::MarketDataSuscriptionRequest)) {
      return nullptr;
    }

    // C++ field name típico: has_market_data_suscription_request()
    if (!request.has_market_data_suscription_request()) {
      return nullptr;
    }

    const auto &r = request.market_data_suscription_request();
    if (!r.has_instrument()) {
      return nullptr;
    }

    const std::string symbol = extractSymbolFromInstrument(r.instrument());
    if (symbol.empty()) {
      auto resp = std::make_unique<WrapperMessage>();
      resp->set_message_id(request.message_id());
      resp->set_client_id(request.client_id());
      resp->set_message_type(std::string(MessageTypes::MarketDataSuscriptionResponse));

      auto *body = resp->mutable_market_data_suscription_response();
      set_request_id_if_exists(body, r.request_id());
      set_ok_if_exists(body, false);
      set_error_if_exists(body, "Instrument without symbol");
      return resp;
    }

    // Validar símbolo existe en security list (freeze strict)
    const auto *iid = registry_.tryResolveId(symbol);
    if (!iid) {
      auto resp = std::make_unique<WrapperMessage>();
      resp->set_message_id(request.message_id());
      resp->set_client_id(request.client_id());
      resp->set_message_type(std::string(MessageTypes::MarketDataSuscriptionResponse));

      auto *body = resp->mutable_market_data_suscription_response();
      set_request_id_if_exists(body, r.request_id());
      set_ok_if_exists(body, false);
      set_error_if_exists(body, "Symbol is not on security list: " + symbol);
      return resp;
    }

    // Tipo de request (según tu enum)
    const auto t = r.subscription_request_type();
    const bool enable = (t == ::markethub::messaging::trading::SNAPSHOT ||
                         t == ::markethub::messaging::trading::SNAPSHOT_PLUS_UPDATES);
    const bool disable =
        (t == ::markethub::messaging::trading::DISABLE_PREVIOUS ||
         t == ::markethub::messaging::trading::DISABLE_PREVIOUS_SNAPSHOT_PLUS_UPDATE_REQUEST);

    if (enable) {
      const bool first = subs_.add(*iid);
      if (first) {
        handler_.subscribe(static_cast<std::uint64_t>(*iid));
      }
    } else if (disable) {
      const bool last = subs_.remove(*iid);
      if (last) {
        handler_.unsubscribe(static_cast<std::uint64_t>(*iid));
      }
    } else {
      // UNSPECIFIED u otro: lo tratamos como no-op pero respondemos ok=false
      auto resp = std::make_unique<WrapperMessage>();
      resp->set_message_id(request.message_id());
      resp->set_client_id(request.client_id());
      resp->set_message_type(std::string(MessageTypes::MarketDataSuscriptionResponse));

      auto *body = resp->mutable_market_data_suscription_response();
      set_request_id_if_exists(body, r.request_id());
      set_ok_if_exists(body, false);
      set_error_if_exists(body, "Unsupported subscription_request_type");
      return resp;
    }

    // Respuesta OK (snapshot: el primer update hace de snapshot)
    auto resp = std::make_unique<WrapperMessage>();
    resp->set_message_id(request.message_id());
    resp->set_client_id(request.client_id());
    resp->set_message_type(std::string(MessageTypes::MarketDataSuscriptionResponse));

    auto *body = resp->mutable_market_data_suscription_response();
    set_request_id_if_exists(body, r.request_id());
    set_ok_if_exists(body, true);
    return resp;
  }

} // namespace b3::md::messaging
