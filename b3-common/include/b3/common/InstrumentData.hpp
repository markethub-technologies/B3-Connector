#pragma once

#include <cstdint>
#include <string>

namespace b3::common {

  /**
   * @brief Complete instrument/security definition data from B3 SecurityDefinition_12
   *
   * This struct captures ALL fields from OnixS SecurityDefinition_12 message
   * to enable full security list responses.
   *
   * Field mapping from B3 UMDF SecurityDefinition_12:
   * - Core identification
   * - Market/trading parameters
   * - Price/quantity specifications
   * - Corporate actions info
   * - Timestamps and status
   */
  struct InstrumentData {
    // ===== Core Identification =====
    uint64_t securityId{0};          // Unique B3 security ID
    std::string symbol;              // Trading symbol (e.g., "PETR4")
    std::string securityExchange;    // Exchange code (e.g., "BVMF")

    // ===== Classification =====
    std::string asset;               // Underlying asset code
    std::string securityType;        // Security type (e.g., "CS" = Common Stock)
    std::string securityGroup;       // Security group/segment
    std::string cfiCode;             // CFI code (ISO 10962)
    std::string marketSegmentId;     // Market segment ID

    // ===== Trading Parameters =====
    uint32_t governanceIndicator{0}; // Corporate governance level
    uint8_t securityMatchType{0};    // Match algorithm type
    uint8_t securityTradingStatus{0}; // Trading status (open, closed, halted, etc.)

    // ===== Price Specifications =====
    // Prices stored as mantissa with 4 decimal places (× 10000)
    int64_t minPriceIncrement{0};    // Minimum price increment (tick size) mantissa
    int64_t minPriceIncrementAmount{0}; // Value of one tick
    int64_t strikePrice{0};          // Strike price for options (mantissa)
    uint8_t strikeReportingCurrency{0}; // Currency for strike price

    // ===== Quantity Specifications =====
    int64_t minOrderQty{0};          // Minimum order quantity
    int64_t maxOrderQty{0};          // Maximum order quantity
    int64_t lotSize{0};              // Trading lot size (round lot)
    int64_t minTradeVol{0};          // Minimum trade volume

    // ===== Options/Derivatives (if applicable) =====
    uint32_t underlyingSecurityId{0}; // Underlying security ID for derivatives
    std::string underlyingSymbol;    // Underlying symbol
    uint32_t maturityDate{0};        // Maturity date (days since epoch or YYYYMMDD)
    uint8_t putOrCall{0};            // Put (0) or Call (1) for options
    uint8_t exerciseStyle{0};        // American, European, etc.

    // ===== Corporate Actions =====
    uint8_t corporateActionEventId{0}; // Corporate action type ID

    // ===== Timestamps =====
    uint64_t securityTradingEventTimestamp{0}; // Last trading event timestamp (ns)

    // ===== Market Making =====
    uint8_t highLimitPriceType{0};   // Price limit type (percentage, absolute, etc.)
    uint8_t lowLimitPriceType{0};
    int64_t highLimitPrice{0};       // Upper price limit (mantissa)
    int64_t lowLimitPrice{0};        // Lower price limit (mantissa)

    // ===== Auction/Circuit Breaker =====
    int64_t maxPriceVariation{0};    // Max price variation (mantissa)
    uint32_t theoreticalOpeningPrice{0}; // Theoretical opening price

    // ===== Settlement =====
    std::string settlementType;      // Settlement type code
    uint8_t productComplex{0};       // Product complexity indicator

    // ===== Flags =====
    bool isMultileg{false};          // Is this a multileg strategy?
    bool hasCorporateAction{false};  // Has pending corporate action?

    // ===== Additional Info =====
    std::string currency;            // Trading currency (e.g., "BRL")
    std::string isin;                // ISIN code (if available)
    std::string securityDesc;        // Security description/name

    InstrumentData() = default;
  };

} // namespace b3::common
