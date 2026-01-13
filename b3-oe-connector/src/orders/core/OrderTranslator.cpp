#include "OrderTranslator.h"

#include <charconv>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string_view>

#include <spdlog/logger.h>

// Protobuf
#include <models/messages.pb.h>
#include <models/messageTypes.h>
#include <models/trading.pb.h>

#include "../../common/FixedString.hpp"
#include "../../common/TextParse.hpp"

// BOE (incluye Messaging + MessageHolder)
#include <OnixS/B3/BOE/Messaging.h>

#include "OwnedBoeMessage.hpp"

namespace orders {

  namespace {

    // -----------------------------
    // Helpers: price mantissa/scale
    // -----------------------------

    constexpr int kPriceScale = 4; // 10^4 => e.g. 12.3456

    inline int64_t toMantissa(double human, int scale) {
      if (!std::isfinite(human))
        return 0;

      const double factor = std::pow(10.0, static_cast<double>(scale));
      const double m = std::round(human * factor);

      if (m > static_cast<double>(std::numeric_limits<int64_t>::max()))
        return std::numeric_limits<int64_t>::max();
      if (m < static_cast<double>(std::numeric_limits<int64_t>::min()))
        return std::numeric_limits<int64_t>::min();

      return static_cast<int64_t>(m);
    }

    // -----------------------------
    // Helpers: quantity (uint64)
    // -----------------------------

    inline bool tryToQtyU64(double humanQty, std::uint64_t &out) noexcept {
      if (!(humanQty > 0.0)) // also rejects NaN
        return false;

      const long long v = std::llround(humanQty);
      if (v <= 0)
        return false;

      out = static_cast<std::uint64_t>(v);
      return true;
    }

    inline bool tryMakeQty(double humanQty, OnixS::B3::BOE::Messaging::Quantity &out,
                           std::string &errorOut) noexcept {
      using namespace OnixS::B3::BOE::Messaging;

      std::uint64_t v = 0;
      if (!tryToQtyU64(humanQty, v)) {
        errorOut = "Quantity must be > 0";
        return false;
      }

      if (v > static_cast<std::uint64_t>(std::numeric_limits<Quantity>::max())) {
        errorOut = "Quantity out of range";
        return false;
      }

      out = static_cast<Quantity>(v);
      return true;
    }

    inline bool tryMakeQtyOpt(double humanQty, OnixS::B3::BOE::Messaging::QuantityOptional &out,
                              std::string &errorOut) noexcept {
      using namespace OnixS::B3::BOE::Messaging;

      std::uint64_t v = 0;
      if (!tryToQtyU64(humanQty, v)) {
        errorOut = "Optional quantity must be > 0";
        return false;
      }

      if (v > static_cast<std::uint64_t>(std::numeric_limits<QuantityOptional>::max())) {
        errorOut = "Optional quantity out of range";
        return false;
      }

      out = static_cast<QuantityOptional>(v);
      return true;
    }

    // -----------------------------
    // Helpers: parsing numerics
    // (ONE canonical set, string_view only)
    // -----------------------------

    // inline bool tryParseU64(std::string_view s, std::uint64_t &out) noexcept {
    //   if (s.empty())
    //     return false;

    //   std::uint64_t v = 0;
    //   const char *b = s.data();
    //   const char *e = b + s.size();

    //   auto res = std::from_chars(b, e, v, 10);
    //   if (res.ec != std::errc{} || res.ptr != e)
    //     return false;

    //   out = v;
    //   return true;
    // }

    // inline bool tryParseULong(std::string_view s, unsigned long &out) noexcept {
    //   std::uint64_t v = 0;
    //   if (!tryParseU64(s, v))
    //     return false;

    //   if (v > static_cast<std::uint64_t>(std::numeric_limits<unsigned long>::max()))
    //     return false;

    //   out = static_cast<unsigned long>(v);
    //   return true;
    // }

    // inline bool tryParseUInt(std::string_view s, unsigned int &out) noexcept {
    //   std::uint64_t v = 0;
    //   if (!tryParseU64(s, v))
    //     return false;

    //   if (v > static_cast<std::uint64_t>(std::numeric_limits<unsigned int>::max()))
    //     return false;

    //   out = static_cast<unsigned int>(v);
    //   return true;
    // }

    // -----------------------------
    // Helpers: hashing (fallback)
    // -----------------------------

    inline std::uint64_t fnv1a64(std::string_view sv) noexcept {
      std::uint64_t h = 1469598103934665603ull;
      for (unsigned char c : sv) {
        h ^= static_cast<std::uint64_t>(c);
        h *= 1099511628211ull;
      }
      return h;
    }

    // -----------------------------
    // Helpers: enum mappings
    // -----------------------------

    inline bool mapSide(markethub::messaging::trading::Side in,
                        OnixS::B3::BOE::Messaging::Side::Enum &out) noexcept {
      using OnixS::B3::BOE::Messaging::Side;
      switch (in) {
        case markethub::messaging::trading::BUY:
          out = Side::Buy;
          return true;
        case markethub::messaging::trading::SELL:
          out = Side::Sell;
          return true;
        default:
          return false;
      }
    }

    inline OnixS::B3::BOE::Messaging::OrdType::Enum mapOrdType(
        markethub::messaging::trading::OrderType t) {
      using OnixS::B3::BOE::Messaging::OrdType;
      switch (t) {
        case markethub::messaging::trading::MARKET_:
          return OrdType::Market;
        case markethub::messaging::trading::LIMIT:
          return OrdType::Limit;
        case markethub::messaging::trading::STOP:
          return OrdType::StopLoss;
        case markethub::messaging::trading::STOP_LIMIT:
          return OrdType::StopLimit;
        default:
          return OrdType::Market;
      }
    }

    inline OnixS::B3::BOE::Messaging::TimeInForce::Enum mapTif(
        markethub::messaging::trading::TimeInForce tif) {
      using OnixS::B3::BOE::Messaging::TimeInForce;
      switch (tif) {
        case markethub::messaging::trading::DAY:
          return TimeInForce::Day;
        case markethub::messaging::trading::GOOD_TILL_CANCEL:
          return TimeInForce::GoodTillCancel;
        case markethub::messaging::trading::IMMEDIATE_OR_CANCEL:
          return TimeInForce::ImmediateOrCancel;
        case markethub::messaging::trading::FILL_OR_KILL:
          return TimeInForce::FillOrKill;
        case markethub::messaging::trading::GOOD_TILL_DATE:
          return TimeInForce::GoodTillDate;
        default:
          return TimeInForce::Day;
      }
    }

    // -----------------------------
    // Helpers: BOE scalar wrappers
    // -----------------------------

    inline OnixS::B3::BOE::Messaging::ClOrdID makeClOrdId(const std::string &clientOrderId,
                                                          spdlog::logger &log) {
      using OnixS::B3::BOE::Messaging::ClOrdID;

      std::uint64_t v = 0;
      if (common::tryParseU64(std::string_view{clientOrderId}, v))
        return static_cast<ClOrdID>(v);

      const std::uint64_t h = fnv1a64(std::string_view{clientOrderId});
      log.warn(
          "client_order_id is not numeric; using fnv1a64 hash as ClOrdID. client_order_id='{}' "
          "clordid={}",
          clientOrderId, h);

      return static_cast<ClOrdID>(h);
    }

    inline OnixS::B3::BOE::Messaging::SecurityID makeSecurityIdFromInstrument(
        const markethub::messaging::trading::Instrument &ins, std::string &errorOut) {
      using OnixS::B3::BOE::Messaging::SecurityID;

      const std::string &sid = ins.security_id();
      if (sid.empty()) {
        errorOut = "Instrument.SecurityId required for BOE (must be numeric)";
        return 0;
      }

      std::uint64_t v = 0;
      if (!common::tryParseU64(std::string_view{sid}, v)) {
        errorOut = "Instrument.SecurityId must be numeric for BOE";
        return 0;
      }

      return static_cast<SecurityID>(v);
    }

    inline OnixS::B3::BOE::Messaging::AccountOptional makeAccountOpt(const std::string &s,
                                                                     std::string &errorOut) {
      using OnixS::B3::BOE::Messaging::AccountOptional;

      if (s.empty()) {
        errorOut = "Account is empty";
        return 0;
      }

      std::uint64_t v = 0;
      if (!common::tryParseU64(std::string_view{s}, v)) {
        errorOut = "Account must be numeric for BOE";
        return 0;
      }

      if (v > std::numeric_limits<std::uint32_t>::max()) {
        errorOut = "Account out of range (uint32)";
        return 0;
      }

      return static_cast<AccountOptional>(static_cast<std::uint32_t>(v));
    }

    inline OnixS::B3::BOE::Messaging::PriceOptional makePriceOpt(double humanPrice) {
      using namespace OnixS::B3::BOE::Messaging;

      const int64_t mant = toMantissa(humanPrice, kPriceScale);
      return PriceOptional{static_cast<Int64>(mant)};
    }

    // Unix ms -> "date-only" Timestamp (days since epoch, 00:00) using OnixS localMktDate
    // conversion.
    inline OnixS::B3::BOE::Messaging::Timestamp toBoeExpireDateFromUnixMs(std::int64_t unixMs) {
      using namespace OnixS::B3::BOE::Messaging;

      const auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>{
          std::chrono::milliseconds{unixMs}};

      const auto days =
          std::chrono::duration_cast<std::chrono::days>(tp.time_since_epoch()).count();

      const auto localMktDays = static_cast<LocalMktDate>(days);
      return localMktDateToTimestamp(localMktDays);
    }

    inline void fillFixedWithSpaces(char *dst, std::size_t dstLen, std::string_view src) {
      // pad with spaces
      for (std::size_t i = 0; i < dstLen; ++i) dst[i] = ' ';
      // copy (truncate if needed)
      const std::size_t n = (src.size() < dstLen) ? src.size() : dstLen;
      for (std::size_t i = 0; i < n; ++i) dst[i] = src[i];
    }

  } // namespace

  // -----------------------------
  // NewOrder mapping
  // -----------------------------
  bool OrderTranslator::tryBuildNewOrder(const uint8_t *req, std::size_t reqSize,
                                         OwnedBoeMessage &outMsg, std::string &errorOut) noexcept {
    try {
      markethub::messaging::WrapperMessage w;
      if (!w.ParseFromArray(req, static_cast<int>(reqSize))) {
        errorOut = "wrapper parse failed";
        return false;
      }

      if (w.message_type() !=
          std::string(markethub::messaging::models::MessageTypes::NewOrderRequest)) {
        errorOut = "wrapper message_type is not NewOrderRequest";
        return false;
      }

      if (!w.has_new_order_request()) {
        errorOut = "missing new_order_request payload";
        return false;
      }

      const auto &r = w.new_order_request();

      if (r.client_order_id().empty()) {
        errorOut = "ClientOrderId required";
        return false;
      }
      if (!r.has_instrument()) {
        errorOut = "Instrument required";
        return false;
      }
      if (r.quantity() <= 0.0) {
        errorOut = "Quantity must be > 0";
        return false;
      }
      if (r.side() == markethub::messaging::trading::SIDE_UNSPECIFIED) {
        errorOut = "Side required";
        return false;
      }
      if (r.order_type() == markethub::messaging::trading::ORDER_TYPE_UNSPECIFIED) {
        errorOut = "OrderType required";
        return false;
      }

      const auto &ins = r.instrument();
      if (ins.symbol().empty() && ins.security_id().empty()) {
        errorOut = "Instrument.Symbol or Instrument.SecurityId required";
        return false;
      }

      using namespace OnixS::B3::BOE::Messaging;

      MessageHolder<NewOrderSingle102> holder;
      auto &msg = holder.message();
      msg.reset();

      msg.setClOrdId(makeClOrdId(r.client_order_id(), *deps_.log));

      std::string sidErr;
      auto secId = makeSecurityIdFromInstrument(ins, sidErr);
      if (!sidErr.empty()) {
        errorOut = sidErr;
        return false;
      }
      msg.setSecurityId(secId);

      Side::Enum boeSide{};
      if (!mapSide(r.side(), boeSide)) {
        errorOut = "NewOrderRequest.side invalid/unsupported";
        return false;
      }
      msg.setSide(boeSide);

      msg.setOrdType(mapOrdType(r.order_type()));
      msg.setTimeInForce(mapTif(r.time_in_force()));

      Quantity q{};
      if (!tryMakeQty(r.quantity(), q, errorOut))
        return false;
      msg.setOrderQty(q);

      // Account optional
      if (!r.account().empty()) {
        std::string accErr;
        const auto acc = makeAccountOpt(r.account(), accErr);
        if (!accErr.empty()) {
          errorOut = accErr;
          return false;
        }
        msg.setAccount(acc);
      } else {
        msg.setAccountToNull();
      }

      // Iceberg (maxFloor)
      if (r.is_iceberg()) {
        QuantityOptional dq{};
        if (!tryMakeQtyOpt(r.display_quantity(), dq, errorOut))
          return false;
        msg.setMaxFloor(dq);
      } else {
        msg.setMaxFloorToNull();
      }

      const auto ordType = r.order_type();

      const bool needsPrice = (ordType == markethub::messaging::trading::LIMIT) ||
                              (ordType == markethub::messaging::trading::STOP_LIMIT);

      const bool needsStop = (ordType == markethub::messaging::trading::STOP) ||
                             (ordType == markethub::messaging::trading::STOP_LIMIT);

      if (needsPrice) {
        if (r.price() <= 0.0) {
          errorOut = "Price must be > 0 for Limit/StopLimit";
          return false;
        }
        msg.setPrice(makePriceOpt(r.price()));
      } else {
        msg.setPriceToNull();
      }

      if (needsStop) {
        if (r.stop_price() <= 0.0) {
          errorOut = "StopPrice must be > 0 for Stop/StopLimit";
          return false;
        }
        msg.setStopPx(makePriceOpt(r.stop_price()));
      } else {
        msg.setStopPxToNull();
      }

      // GTD expiration (BOE expireDate = local market date only)
      if (r.time_in_force() == markethub::messaging::trading::GOOD_TILL_DATE) {
        if (r.expiration_time() <= 0) {
          errorOut = "ExpirationTime required for GoodTillDate";
          return false;
        }
        msg.setExpireDate(toBoeExpireDateFromUnixMs(r.expiration_time()));
      } else {
        msg.setExpireDateToNull();
      }

      msg.setSelfTradePreventionInstruction(SelfTradePreventionInstruction::None);

      using OnixS::B3::BOE::Messaging::StrRef;
      msg.setSenderLocation(StrRef{deps_.senderLocation.data(), deps_.senderLocation.size()});
      msg.setEnteringTrader(StrRef{deps_.enteringTrader.data(), deps_.enteringTrader.size()});

      outMsg = OwnedBoeMessage::make(std::move(holder));
      return true;
    } catch (const std::exception &ex) {
      errorOut = ex.what();
      return false;
    } catch (...) {
      errorOut = "unknown exception building NewOrderSingle102";
      return false;
    }
  }

  // -----------------------------
  // Cancel mapping
  // -----------------------------
  bool OrderTranslator::tryBuildCancel(const uint8_t *req, std::size_t reqSize,
                                       OwnedBoeMessage &outMsg, std::string &errorOut) noexcept {
    using namespace OnixS::B3::BOE::Messaging;
    using markethub::messaging::models::MessageTypes;

    outMsg = OwnedBoeMessage{};

    markethub::messaging::WrapperMessage w;
    if (!w.ParseFromArray(req, static_cast<int>(reqSize))) {
      errorOut = "Invalid WrapperMessage";
      return false;
    }

    if (std::string_view(w.message_type()) != MessageTypes::CancelOrderRequest) {
      errorOut = "Wrapper message_type != CancelOrderRequest";
      return false;
    }

    if (!w.has_cancel_order_request()) {
      errorOut = "Wrapper missing cancel_order_request";
      return false;
    }

    const auto &r = w.cancel_order_request();

    if (r.client_order_id().empty()) {
      errorOut = "CancelOrderRequest.client_order_id required";
      return false;
    }

    if (!r.has_instrument() || r.instrument().security_id().empty()) {
      errorOut = "CancelOrderRequest.instrument.security_id required";
      return false;
    }

    Side::Enum boeSide{};
    if (!mapSide(r.side(), boeSide)) {
      errorOut = "CancelOrderRequest.side invalid/unsupported";
      return false;
    }

    if (r.client_order_id_to_cancel().empty() && r.order_id_to_cancel().empty()) {
      errorOut = "CancelOrderRequest requires client_order_id_to_cancel or order_id_to_cancel";
      return false;
    }

    MessageHolder<OrderCancelRequest105> holder;
    auto &msg = holder.message();
    msg.reset();

    // clOrdId (required)
    {
      unsigned long cl{};
      if (!common::tryParseUnsignedLong(std::string_view{r.client_order_id()}, cl)) {
        errorOut = "client_order_id must be numeric for BOE ClOrdID";
        return false;
      }
      msg.setClOrdId(static_cast<ClOrdID>(cl));
    }

    // securityId (required)
    {
      unsigned long sec{};
      if (!common::tryParseUnsignedLong(std::string_view{r.instrument().security_id()}, sec)) {
        errorOut = "instrument.security_id must be numeric for BOE SecurityID";
        return false;
      }
      msg.setSecurityId(static_cast<SecurityID>(sec));
    }

    msg.setSide(boeSide);

    // origClOrdId (optional)
    if (!r.client_order_id_to_cancel().empty()) {
      unsigned long orig{};
      if (!common::tryParseUnsignedLong(std::string_view{r.client_order_id_to_cancel()}, orig)) {
        errorOut = "client_order_id_to_cancel must be numeric for BOE OrigClOrdID";
        return false;
      }
      msg.setOrigClOrdId(static_cast<ClOrdIDOptional>(orig));
    } else {
      msg.setOrigClOrdIdToNull();
    }

    // orderId (optional)
    if (!r.order_id_to_cancel().empty()) {
      unsigned int oid{};
      if (!common::tryParseUnsignedInt(std::string_view{r.order_id_to_cancel()}, oid)) {
        errorOut = "order_id_to_cancel must be numeric and fit BOE OrderIDOptional";
        return false;
      }
      msg.setOrderId(static_cast<OrderIDOptional>(oid));
    } else {
      msg.setOrderIdToNull();
    }

    msg.setExecRestatementReasonToNull();

    msg.setSenderLocation(StrRef{deps_.senderLocation.data(), deps_.senderLocation.size()});
    msg.setEnteringTrader(StrRef{deps_.enteringTrader.data(), deps_.enteringTrader.size()});

    msg.setExecutingTraderToNull();
    msg.resetVariableFields();

    // NOTE: proto has quantity for partial cancel; BOE 105 has no qty.
    // For now, treat as full cancel.

    outMsg = OwnedBoeMessage::make(std::move(holder));
    return true;
  }

  // -----------------------------
  // Replace stub (as requested)
  // -----------------------------
  bool OrderTranslator::tryBuildReplace(const uint8_t * /*req*/, std::size_t /*reqSize*/,
                                        OwnedBoeMessage &outMsg, std::string &errorOut) noexcept {
    outMsg = OwnedBoeMessage{};
    errorOut = "Replace not implemented yet";
    return false;
  }

} // namespace orders
