#include "B3MdSubscriptionServer.hpp"

#include <type_traits>
#include <utility>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <google/protobuf/reflection.h>

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

  // Intenta setear un string field (si existe y es string)
  inline void set_string_if_exists(::google::protobuf::Message *m, const char *fieldName,
                                   std::string_view v) {
    if (!m)
      return;
    const auto *d = m->GetDescriptor();
    const auto *r = m->GetReflection();
    if (!d || !r)
      return;

    const auto *f = d->FindFieldByName(fieldName);
    if (!f)
      return;
    if (f->cpp_type() != ::google::protobuf::FieldDescriptor::CPPTYPE_STRING)
      return;

    r->SetString(m, f, std::string(v));
  }

  // Intenta setear un uint64 field (si existe y es uint64/int64/int32/uint32)
  inline void set_u64_if_exists(::google::protobuf::Message *m, const char *fieldName,
                                std::uint64_t v) {
    if (!m)
      return;
    const auto *d = m->GetDescriptor();
    const auto *r = m->GetReflection();
    if (!d || !r)
      return;

    const auto *f = d->FindFieldByName(fieldName);
    if (!f)
      return;

    using FD = ::google::protobuf::FieldDescriptor;
    switch (f->cpp_type()) {
      case FD::CPPTYPE_UINT64:
        r->SetUInt64(m, f, v);
        break;
      case FD::CPPTYPE_INT64:
        r->SetInt64(m, f, static_cast<std::int64_t>(v));
        break;
      case FD::CPPTYPE_UINT32:
        r->SetUInt32(m, f, static_cast<std::uint32_t>(v));
        break;
      case FD::CPPTYPE_INT32:
        r->SetInt32(m, f, static_cast<std::int32_t>(v));
        break;
      default:
        break;
    }
  }

  // Agrega un Instrument al map "securities" (key = symbol, value = Security message)
  // Legacy version with minimal fields (symbol + iid only)
  inline void add_instrument_best_effort(
      ::markethub::messaging::trading::SecurityListResponse *resp, std::uint64_t iid,
      const std::string &symbol) {
    if (!resp)
      return;

    auto *securitiesMap = resp->mutable_securities();
    if (!securitiesMap)
      return;

    auto &security = (*securitiesMap)[symbol];

    // Set minimal fields using reflection
    set_string_if_exists(&security, "symbol", symbol);
    set_string_if_exists(&security, "ticker", symbol);
    set_string_if_exists(&security, "code", symbol);

    set_u64_if_exists(&security, "security_id", iid);
    set_u64_if_exists(&security, "instrument_id", iid);
    set_u64_if_exists(&security, "id", iid);
  }

  // Full version with complete InstrumentData mapping
  inline void add_instrument_full(::markethub::messaging::trading::SecurityListResponse *resp,
                                   const b3::md::mapping::InstrumentData &data) {
    if (!resp || data.symbol.empty())
      return;

    auto *securitiesMap = resp->mutable_securities();
    if (!securitiesMap)
      return;

    auto &security = (*securitiesMap)[data.symbol];

    // Core identification
    set_string_if_exists(&security, "symbol", data.symbol);
    set_string_if_exists(&security, "ticker", data.symbol);
    set_u64_if_exists(&security, "security_id", data.securityId);
    set_u64_if_exists(&security, "instrument_id", data.securityId);
    set_string_if_exists(&security, "exchange", data.securityExchange);

    // Classification
    set_string_if_exists(&security, "security_type", data.securityType);
    set_string_if_exists(&security, "security_group", data.securityGroup);
    set_string_if_exists(&security, "asset", data.asset);
    set_string_if_exists(&security, "cfi_code", data.cfiCode);

    // Price specifications (convert mantissa to decimal if protobuf expects double)
    if (data.minPriceIncrement != 0) {
      // Assuming protobuf uses double for price - convert from mantissa
      double tickSize = data.minPriceIncrement / 10000.0;
      // set_double_if_exists(&security, "tick_size", tickSize);
      // Or keep as mantissa if protobuf uses int64
      set_u64_if_exists(&security, "min_price_increment", static_cast<uint64_t>(data.minPriceIncrement));
    }

    if (data.strikePrice != 0) {
      double strike = data.strikePrice / 10000.0;
      // set_double_if_exists(&security, "strike_price", strike);
      set_u64_if_exists(&security, "strike_price_mantissa", static_cast<uint64_t>(data.strikePrice));
    }

    // Quantity specifications
    if (data.minOrderQty != 0) {
      set_u64_if_exists(&security, "min_order_qty", static_cast<uint64_t>(data.minOrderQty));
    }
    if (data.maxOrderQty != 0) {
      set_u64_if_exists(&security, "max_order_qty", static_cast<uint64_t>(data.maxOrderQty));
    }
    if (data.lotSize != 0) {
      set_u64_if_exists(&security, "lot_size", static_cast<uint64_t>(data.lotSize));
    }

    // Derivatives fields
    if (data.underlyingSecurityId != 0) {
      set_u64_if_exists(&security, "underlying_security_id", data.underlyingSecurityId);
    }
    set_string_if_exists(&security, "underlying_symbol", data.underlyingSymbol);

    if (data.maturityDate != 0) {
      set_u64_if_exists(&security, "maturity_date", static_cast<uint64_t>(data.maturityDate));
    }

    // Flags
    if (data.hasCorporateAction) {
      set_u64_if_exists(&security, "corporate_action_event_id", data.corporateActionEventId);
    }

    set_string_if_exists(&security, "currency", data.currency);
    set_string_if_exists(&security, "isin", data.isin);
    set_string_if_exists(&security, "description", data.securityDesc);
  }

} // namespace

namespace b3::md::messaging {

  B3MdSubscriptionServer::B3MdSubscriptionServer(const std::string &serverEndpoint,
                                                 const std::string &publishingEndpoint,
                                                 b3::md::mapping::InstrumentRegistry &registry,
                                                 b3::md::SubscriptionRegistry &subs,
                                                 b3::md::IMarketDataHandler &handler,
                                                 LogCallback logCb)
      : SubscriberPublisher(serverEndpoint, publishingEndpoint, std::move(logCb)),
        registry_(registry),
        subs_(subs),
        handler_(handler) {}

  std::unique_ptr<WrapperMessage> B3MdSubscriptionServer::HandleMessage(
      const WrapperMessage &request) {
    // -----------------------------
    // 1) SECURITY LIST
    // -----------------------------
    if (request.message_type() == std::string(MessageTypes::SecurityListRequest)) {
      if (!request.has_security_list_request()) {
        return nullptr;
      }

      // if (!registryReady_ || !registryReady_->load(std::memory_order_acquire)) { ... }

      auto resp = std::make_unique<WrapperMessage>();
      resp->set_message_id(request.message_id());
      resp->set_client_id(request.client_id());
      resp->set_message_type(std::string(MessageTypes::SecurityListResponse));

      auto *body = resp->mutable_security_list_response();

      const auto &r = request.security_list_request();
      set_request_id_if_exists(body, r.request_id());

      // Tomamos snapshot completo con todos los campos
      auto items = registry_.snapshotAllFull();

      // OK si hay algo (o siempre ok; vos definís)
      set_ok_if_exists(body, true);

      // Poblar lista con todos los campos disponibles
      for (const auto &kv : items) {
        add_instrument_full(body, kv.second);
      }

      return resp;
    }

    // -----------------------------
    // 2) MARKET DATA SUBSCRIPTION (tu lógica actual)
    // -----------------------------
    if (request.message_type() != std::string(MessageTypes::MarketDataSuscriptionRequest)) {
      return nullptr;
    }

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
