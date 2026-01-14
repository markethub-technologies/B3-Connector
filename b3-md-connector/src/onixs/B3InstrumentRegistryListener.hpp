// b3-md-connector/src/onixs/B3InstrumentRegistryListener.hpp
#pragma once

#include <OnixS/B3/MarketData/UMDF/MessageListener.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Messages.h>

#include <atomic>
#include <cstdint>
#include <string>
#include <unordered_map>

#include <b3/common/InstrumentRegistry.hpp>

namespace b3::md::onixs {

  class B3InstrumentRegistryListener final : public ::OnixS::B3::MarketData::UMDF::MessageListener {
   public:
    explicit B3InstrumentRegistryListener(b3::common::InstrumentRegistry &registry) noexcept
        : registry_(registry) {}

    std::atomic<bool> &readyAtomic() noexcept { return ready_; }
    const std::atomic<bool> &readyAtomic() const noexcept { return ready_; }

    void onSequenceReset_1(const ::OnixS::B3::MarketData::UMDF::Messaging::SequenceReset_1,
                           const ::OnixS::B3::MarketData::UMDF::DataSource &) override {
      if (ready_.load(std::memory_order_acquire))
        return;

      // First reset: start capture
      if (!capturing_.exchange(true, std::memory_order_acq_rel)) {
        staging_.clear();
        return;
      }

      // Second reset: close loop → commit full instrument data
      registry_.bulkUpsertFull(staging_.begin(), staging_.end());
      ready_.store(true, std::memory_order_release);
    }

    void onSecurityDefinition_12(
        const ::OnixS::B3::MarketData::UMDF::Messaging::SecurityDefinition_12 msg,
        const ::OnixS::B3::MarketData::UMDF::DataSource &) override {
      const std::uint64_t iid = static_cast<std::uint64_t>(msg.securityId());
      if (iid == 0)
        return;

      std::string sym = trimRight(msg.symbol());
      if (sym.empty())
        return;

      // Después de ready=true: freeze estricto (lista fija, cargada al inicio del día)
      if (ready_.load(std::memory_order_acquire)) {
        return; // Freeze: ignora SecurityDefinitions posteriores
        // registry_.upsertFull(iid, extractInstrumentData(msg)); // Descomentar para permitir
        // updates
      }

      if (!capturing_.load(std::memory_order_acquire))
        return; // ignore until first reset

      staging_[iid] = extractInstrumentData(msg);
    }

   private:
    template <typename StrLike>
    static std::string trimRight(const StrLike &s) {
      const char *p = s.data();
      std::size_t n = static_cast<std::size_t>(s.size());
      while (n > 0 && (p[n - 1] == ' ' || p[n - 1] == '\0' || p[n - 1] == '\t')) --n;
      return std::string(p, n);
    }

    /**
     * @brief Extract all available fields from SecurityDefinition_12 message
     */
    static b3::common::InstrumentData extractInstrumentData(
        const ::OnixS::B3::MarketData::UMDF::Messaging::SecurityDefinition_12 &msg) {
      b3::common::InstrumentData data;

      using namespace ::OnixS::B3::MarketData::UMDF::Messaging;

      // ===== Core Identification =====
      data.securityId = static_cast<std::uint64_t>(msg.securityId());
      data.symbol = trimRight(msg.symbol());
      data.securityExchange = trimRight(msg.securityExchange());

      // ===== Classification =====
      data.securityGroup = trimRight(msg.securityGroup());
      data.securityType = std::to_string(static_cast<int>(msg.securityType()));
      data.asset = trimRight(msg.asset());
      data.cfiCode = trimRight(msg.cfiCode());
      data.currency = trimRight(msg.currency());

      // Market Segment
      MarketSegmentID mktSegId;
      if (msg.marketSegmentId(mktSegId)) {
        data.marketSegmentId = std::to_string(static_cast<uint32_t>(mktSegId));
      }

      // ===== Price Specifications (mantissa with 4 decimals) =====
      Fixed8 minPriceInc;
      if (msg.minPriceIncrement(minPriceInc)) {
        data.minPriceIncrement = static_cast<int64_t>(minPriceInc.mantissa());
      }

      PriceOptional strike;
      if (msg.strikePrice(strike)) {
        data.strikePrice = static_cast<int64_t>(strike.mantissa());
      }

      Fixed8 mult;
      if (msg.contractMultiplier(mult)) {
        // Store as int64 (mantissa)
        data.minPriceIncrementAmount = static_cast<int64_t>(mult.mantissa());
      }

      // ===== Quantity Specifications =====
      QuantityOptional minOrderQ;
      if (msg.minOrderQty(minOrderQ)) {
        data.minOrderQty = static_cast<int64_t>(minOrderQ);
      }

      QuantityOptional maxOrderQ;
      if (msg.maxOrderQty(maxOrderQ)) {
        data.maxOrderQty = static_cast<int64_t>(maxOrderQ);
      }

      QuantityOptional minLot;
      if (msg.minLotSize(minLot)) {
        data.lotSize = static_cast<int64_t>(minLot);
      }

      QuantityOptional minTrade;
      if (msg.minTradeVol(minTrade)) {
        data.minTradeVol = static_cast<int64_t>(minTrade);
      }

      // ===== Options/Derivatives =====
      PutOrCall::Enum putOrCallEnum;
      if (msg.putOrCall(putOrCallEnum)) {
        data.putOrCall = static_cast<uint8_t>(putOrCallEnum);
      }

      ExerciseStyle::Enum exStyleEnum;
      if (msg.exerciseStyle(exStyleEnum)) {
        data.exerciseStyle = static_cast<uint8_t>(exStyleEnum);
      }

      // Underlying security (from repeating group - take first entry if present)
      auto underlyings = msg.underlyings();
      if (underlyings.size() > 0) {
        auto firstUnderlying = underlyings[0];
        data.underlyingSecurityId = static_cast<uint32_t>(firstUnderlying.underlyingSecurityId());
        data.underlyingSymbol = trimRight(firstUnderlying.underlyingSymbol());
      }

      // ===== Corporate Actions =====
      UInt32NULL corpAction;
      if (msg.corporateActionEventId(corpAction)) {
        data.corporateActionEventId = static_cast<uint8_t>(corpAction);
        data.hasCorporateAction = (corpAction != 0);
      }

      // ===== Trading Parameters =====
      GovernanceIndicator::Enum govEnum;
      if (msg.governanceIndicator(govEnum)) {
        data.governanceIndicator = static_cast<uint32_t>(govEnum);
      }

      SecurityMatchType::Enum matchTypeEnum;
      if (msg.securityMatchType(matchTypeEnum)) {
        data.securityMatchType = static_cast<uint8_t>(matchTypeEnum);
      }

      // Multileg indicator (if multileg field is present and valid, it's a multileg)
      MultiLegModel::Enum multiLegEnum;
      if (msg.multiLegModel(multiLegEnum)) {
        data.isMultileg = true;  // If the field is present, it's a multileg security
      }

      // ===== Timestamps =====
      OnixS::B3::MarketData::UMDF::Timestamp maturity;
      if (msg.maturityDate(maturity)) {
        const auto ns = maturity.sinceEpoch(); // UInt64 nanoseconds since 1970-01-01
        data.maturityDate = static_cast<uint32_t>(ns / 1000000000ULL); // ns → seconds
      }

      // ===== Additional Info =====
      StrRef isinRef;
      if (msg.isinNumber(isinRef)) {
        data.isin = trimRight(isinRef);
      }

      data.securityDesc = trimRight(msg.securityDesc());

      // Settlement type
      SettlType settlTypeVal;
      if (msg.settlType(settlTypeVal)) {
        data.settlementType = std::to_string(static_cast<uint32_t>(settlTypeVal));
      }

      // Product (map to productComplex)
      data.productComplex = static_cast<uint8_t>(msg.product());

      return data;
    }

   private:
    b3::common::InstrumentRegistry &registry_;

    std::atomic<bool> ready_{false};
    std::atomic<bool> capturing_{false};

    std::unordered_map<std::uint64_t, b3::common::InstrumentData> staging_;
  };

} // namespace b3::md::onixs
