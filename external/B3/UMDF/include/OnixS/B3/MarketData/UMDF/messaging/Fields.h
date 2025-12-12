// Copyright Onix Solutions Limited [OnixS]. All rights reserved.
//
// This software owned by Onix Solutions Limited [OnixS] and is
// protected by copyright law and international copyright treaties.
//
// Access to and use of the software is governed by the terms of the applicable
// OnixS Software Services Agreement (the Agreement) and Customer end user license
// agreements granting a non-assignable, non-transferable and non-exclusive license
// to use the software for it's own data processing purposes under the terms defined
// in the Agreement.
//
// Except as otherwise granted within the terms of the Agreement, copying or
// reproduction of any part of this source code or associated reference material
// to any other location for further reproduction or redistribution, and any
// amendments to this copyright notice, are expressly prohibited.
//
// Any reproduction or redistribution for sale or hiring of the Software not in
// accordance with the terms of the Agreement is a violation of copyright law.
//

#pragma once

#include <OnixS/B3/MarketData/UMDF/Time.h>
#include <OnixS/B3/MarketData/UMDF/messaging/StrRef.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Integral.h>

#ifdef DELETE
#undef DELETE
#endif

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

/// 1-byte signed integer, from -128 to 127; if optional, null value is -128.
typedef Int8 Int8;


/// 2-byte signed integer, from -32768 to 32767; if optional, null value is -32768.
typedef Int16 Int16;


/// 4-byte signed integer, from -2147483648 to 2147483647; if optional, null value is -2147483648.
typedef Int32 Int32;


/// 8-byte signed integer, from -9223372036854775808 (-2^63) to 9223372036854775807 (2^63-1).
typedef Int64 Int64;


/// 1-byte unsigned integer, from 0 to 255.
typedef UInt8 UInt8;


/// 2-byte unsigned integer, from 0 to 65535.
typedef UInt16 UInt16;


/// 4-byte unsigned integer, from 0 to 4294967295 (2^32-1).
typedef UInt32 UInt32;


/// 8-byte unsigned integer, from 0 to 18446744073709551615 (2^64-1).
typedef UInt64 UInt64;


/// 1-byte signed integer, from -128 to 127, NULL (optional) value = 0.
typedef Int8 Int8NULL;


/// 2-byte unsigned integer, from -32768 to 32767, NULL (optional) value = 0.
typedef Int16 Int16NULL;


/// 4-byte signed integer, from -2147483648 (-2^31) to 2147483647 (2^31-1), NULL (optional) value = 0.
typedef Int32 Int32NULL;


/// 8-byte signed integer, from -9223372036854775808 (-2^63) to 9223372036854775807 (2^63-1), NULL (optional) value = 0.
typedef Int64 Int64NULL;


/// 1 ASCII character, NULL (optional) value is '\0'.
typedef Char CharNULL;


/// 1-byte unsigned integer, from 1 to 255, NULL (optional) value = 0.
typedef UInt8 UInt8NULL;


/// 2-byte unsigned integer, from 1 to 65535, NULL (optional) value = 0.
typedef UInt16 UInt16NULL;


/// 4-byte unsigned integer, from 1 to 4294967295 (2^32-1), NULL (optional) value = 0.
typedef UInt32 UInt32NULL;


/// 8-byte unsigned integer, from 1 to 18446744073709551615 (2^64-1), NULL (optional) value = 0.
typedef UInt64 UInt64NULL;


/// Contains the number of trades executed in the session.
///
/// FIX type: Int.
typedef UInt32 NumberOfTrades;


/// Quantity in order/trade.
///
/// FIX type: Qty.
typedef Int64 Quantity;


/// Quantity in order/trade.
///
/// FIX type: Qty.
typedef Int64 QuantityOptional;


/// Volume Quantity.
///
/// FIX type: Qty.
typedef Int64 QuantityVolume;


/// Volume Quantity.
///
/// FIX type: Qty.
typedef
Int64
QuantityVolumeOptional;


/// Identifies the broker firm.
///
/// FIX type: Int.
typedef UInt32 FirmOptional;


/// Unique identifier for Order as assigned by the exchange.
///
/// FIX type: Int.
typedef UInt64 OrderID;


/// Contains the unique identifier for this trade per instrument + trading date, as assigned by the exchange. Required if reporting a Trade.
///
/// FIX type: Int.
typedef UInt32 TradeID;


/// Sequence number inside the given channel.
///
/// FIX type: Int.
typedef UInt32 SeqNum;


/// Sequence Number, fixed to 1.
///
/// FIX type: Int.
typedef
IntegralConstant<UInt32, 1>
SeqNum1;


/// Security ID as defined by B3's Trading System.
///
/// FIX type: Int.
typedef UInt64 SecurityID;


/// Security ID as defined by B3's Trading System.
///
/// FIX type: Int.
typedef UInt64 SecurityIDOptional;


/// Security Exchange Code.
///
/// FIX type: Exchange.
typedef Char SecurityExchange[4];


/// Sequence number per instrument update. It can be used to synchronize the snapshot with the incremental feed if the client is only interested in a subset of the channel's instruments.
///
/// FIX type: Int.
typedef UInt32 RptSeq;


/// ClearingHouseID (SecurityAltID).
///
/// FIX type: Int.
typedef UInt64 ClearingHouseID;


/// News ID.
///
/// FIX type: Int.
typedef UInt64 NewsID;


/// 3-letter alphabetic ISO Currency Codes (ISO 4217). Example: BRL, USD.
///
/// FIX type: Currency.
typedef Char Currency[3];


/// Indicates order settlement period in days. (e.g. 0, D1, D2, D3, D60, D120 etc.) If present, SettlDate (64) overrides this field.
typedef UInt16 SettlType;


/// Local date (as opposed to UTC). Number of days since UNIX Epoch (January 1st, 1970). Example: 18319 represents February 27, 2020.
///
/// FIX type: LocalMktDate.
typedef UInt16 LocalMktDate;


/// Optional local date (as opposed to UTC). Number of days since UNIX Epoch (January 1st, 1970). Example: 18319 represents February 27, 2020.
///
/// FIX type: LocalMktDate.
typedef UInt16 LocalMktDateOptional;


/// Local date (as opposed to UTC). Number of days since UNIX Epoch (January 1st, 1970). Example: 18319 represents February 27, 2020.
///
/// FIX type: LocalMktDate.
typedef Int32 LocalMktDate32;


/// Optional local date (as opposed to UTC). Number of days since UNIX Epoch (January 1st, 1970). Example: 18319 represents February 27, 2020.
///
/// FIX type: LocalMktDate.
typedef
Int32
LocalMktDate32Optional;


/// Identifies the market segment. Required for all tradable instruments. Not present in equity indexes, ETF indexes, BTB and Option Exercise.
///
/// FIX type: Int.
typedef UInt8 MarketSegmentID;


/// FIX Message Type.
///
/// FIX type: char.
ONIXS_B3_UMDF_MD_LTWT_STRUCT MessageType
{
    typedef Char Base;

    /// FIX Message Type.
    enum Enum
    {
        /// Sequence message for heartbeat.
        Sequence = '0',

        /// Sequence Reset.
        SequenceReset = '4',

        /// Market Data Incremental Refresh.
        MarketDataIncrementalRefresh = 'X',

        /// Security Status.
        SecurityStatus = 'f',

        /// Security Definition.
        SecurityDefinition = 'd',

        /// News.
        News = 'B',

        /// Market Data Full Refresh.
        MarketDataSnapshotFullRefresh = 'W'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Boolean type.
///
/// FIX type: Boolean.
ONIXS_B3_UMDF_MD_LTWT_STRUCT Boolean
{
    typedef UInt8 Base;

    /// Boolean type.
    enum Enum
    {
        /// false, N, 0.
        FALSE_VALUE = 0,

        /// true, Y, 1.
        TRUE_VALUE = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Unit of time.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT TimeUnit
{
    typedef UInt8 Base;

    /// Unit of time.
    enum Enum
    {
        /// SECOND
        SECOND = 0,

        /// MILLISECOND
        MILLISECOND = 3,

        /// MICROSECOND
        MICROSECOND = 6,

        /// NANOSECOND
        NANOSECOND = 9
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Side of order.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT Side
{
    typedef UInt8 Base;

    /// Side of order.
    enum Enum
    {
        /// BUY
        BUY = 1,

        /// SELL
        SELL = 2
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Action used when updating the security.
ONIXS_B3_UMDF_MD_LTWT_STRUCT SecurityUpdateAction
{
    typedef Char Base;

    /// Action used when updating the security.
    enum Enum
    {
        /// Add.
        ADD = 'A',

        /// Delete.
        DELETE = 'D',

        /// Modify.
        MODIFY = 'M'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Describes the lot type for the instruments. Used for the Equities segment.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT LotType
{
    typedef UInt8 Base;

    /// Describes the lot type for the instruments. Used for the Equities segment.
    enum Enum
    {
        /// Odd lot.
        ODD_LOT = 1,

        /// Round lot.
        ROUND_LOT = 2,

        /// Block lot.
        BLOCK_LOT = 3
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates the type of product the security is associated with.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT Product
{
    typedef UInt8 Base;

    /// Indicates the type of product the security is associated with.
    enum Enum
    {
        /// Commodity.
        COMMODITY = 2,

        /// Corporate Fixed Income.
        CORPORATE = 3,

        /// Currency.
        CURRENCY = 4,

        /// Equity.
        EQUITY = 5,

        /// Public debt.
        GOVERNMENT = 6,

        /// Index.
        INDEX = 7,

        /// Economic indicator.
        ECONOMIC_INDICATOR = 15,

        /// Multileg.
        MULTILEG = 16
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates the type of the security.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT SecurityType
{
    typedef UInt8 Base;

    /// Indicates the type of the security.
    enum Enum
    {
        /// Rights, etc.
        CASH = 1,

        /// Corporate Fixed Income.
        CORP = 2,

        /// Common Stock.
        CS = 3,

        /// Derivative Forward or 'Termo'.
        DTERM = 4,

        /// Exchange Traded Fund.
        ETF = 5,

        /// Future Options.
        FOPT = 6,

        /// Equity Forward or 'Termo'.
        FORWARD = 7,

        /// Futures.
        FUT = 8,

        /// Non-Tradable index.
        INDEX = 9,

        /// INDEXOPT
        INDEXOPT = 10,

        /// Multileg Instrument.
        MLEG = 11,

        /// Option.
        OPT = 12,

        /// Option Exercise.
        OPTEXER = 13,

        /// Preferred Stock.
        PS = 14,

        /// SECLOAN
        SECLOAN = 15,

        /// Spot Options.
        SOPT = 16,

        /// Spot Market.
        SPOT = 17
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of exercise of a derivatives security.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT ExerciseStyle
{
    typedef UInt8 Base;

    /// Type of exercise of a derivatives security.
    enum Enum
    {
        /// European.
        EUROPEAN = 0,

        /// American.
        AMERICAN = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates whether an option contract is a put or call.
ONIXS_B3_UMDF_MD_LTWT_STRUCT PutOrCall
{
    typedef UInt8 Base;

    /// Indicates whether an option contract is a put or call.
    enum Enum
    {
        /// Put Option.
        PUT = 0,

        /// Call Option.
        CALL = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Code to represent the price type. If absent (zero), the default value is DECIMALS.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT PriceType
{
    typedef UInt8 Base;

    /// Code to represent the price type. If absent (zero), the default value is DECIMALS.
    enum Enum
    {
        /// Percentage.
        PERCENTAGE = 1,

        /// Per unit (i.e., per share or contract).
        PU = 2,

        /// Fixed amount (absolute value).
        FIXED_AMOUNT = 3
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Status related to a given Instrument or phase related to a SecurityGroup where the instrument belongs to.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT SecurityTradingStatus
{
    typedef UInt8 Base;

    /// Status related to a given Instrument or phase related to a SecurityGroup where the instrument belongs to.
    enum Enum
    {
        /// Trading Halt (Pause).
        PAUSE = 2,

        /// No-Open (Close).
        CLOSE = 4,

        /// Ready To Trade (Open).
        OPEN = 17,

        /// Not Available For Trading (Forbidden).
        FORBIDDEN = 18,

        /// Unknown Or Invalid.
        UNKNOWN_OR_INVALID = 20,

        /// Pre Open (Reserved).
        RESERVED = 21,

        /// Final Closing Call.
        FINAL_CLOSING_CALL = 101
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Status related to a given Instrument or phase related to a SecurityGroup where the instrument belongs to.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT TradingSessionSubID
{
    typedef UInt8 Base;

    /// Status related to a given Instrument or phase related to a SecurityGroup where the instrument belongs to.
    enum Enum
    {
        /// Trading Halt (Pause).
        PAUSE = 2,

        /// No-Open (Close).
        CLOSE = 4,

        /// Ready To Trade (Open).
        OPEN = 17,

        /// Not Available For Trading (Forbidden).
        FORBIDDEN = 18,

        /// Unknown Or Invalid.
        UNKNOWN_OR_INVALID = 20,

        /// Pre Open (Reserved).
        RESERVED = 21,

        /// Final Closing Call.
        FINAL_CLOSING_CALL = 101
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Corporative governance level indicator. Required for cash equities.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT GovernanceIndicator
{
    typedef UInt8 Base;

    /// Corporative governance level indicator. Required for cash equities.
    enum Enum
    {
        /// Unspecified.
        No = 0,

        /// Level 1.
        N1 = 1,

        /// Level 2.
        N2 = 2,

        /// New Market.
        NM = 4,

        /// Bovespa Mais.
        MA = 5,

        /// Over the counter (SOMA Market).
        MB = 6,

        /// Bovespa Mais Level 2.
        M2 = 7
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of matching that occurred. Required for Special Auctions.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT SecurityMatchType
{
    typedef UInt8 Base;

    /// Type of matching that occurred. Required for Special Auctions.
    enum Enum
    {
        /// Issuing/Buy Back Auction.
        ISSUING_BUY_BACK_AUCTION = 8
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Which side is aggressor of this trade.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT AggressorSide
{
    typedef UInt8 Base;

    /// Which side is aggressor of this trade.
    enum Enum
    {
        /// Trade has no aggressor.
        NO_AGGRESSOR = 0,

        /// Buy.
        BUY = 1,

        /// Sell.
        SELL = 2
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Phase related to a SecurityGroup where the instrument belongs to.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT TradingSessionID
{
    typedef UInt8 Base;

    /// Phase related to a SecurityGroup where the instrument belongs to.
    enum Enum
    {
        /// Regular day session.
        REGULAR_TRADING_SESSION = 1,

        /// Non-Regular Session (after hours).
        NON_REGULAR_TRADING_SESSION = 6
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies an event related to a Trade. This tag is also used to mark when an instrument state is kept separate from the group phase, or when the instrument state follows the default group phase (stops having a separate, defined state).
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT SecurityTradingEvent
{
    typedef UInt8 Base;

    /// Identifies an event related to a Trade. This tag is also used to mark when an instrument state is kept separate from the group phase, or when the instrument state follows the default group phase (stops having a separate, defined state).
    enum Enum
    {
        /// Change of Trading Session.
        TRADING_SESSION_CHANGE = 4,

        /// Security Status maintained separately from Group Status.
        SECURITY_STATUS_CHANGE = 101,

        /// Security Status following Group Status.
        SECURITY_REJOINS_SECURITY_GROUP_STATUS = 102
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates the type of price banding (tunnel).
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT PriceBandType
{
    typedef UInt8 Base;

    /// Indicates the type of price banding (tunnel).
    enum Enum
    {
        /// Hard Limit.
        HARD_LIMIT = 1,

        /// Auction Limits.
        AUCTION_LIMITS = 2,

        /// Rejection Band.
        REJECTION_BAND = 3,

        /// Static Limits.
        STATIC_LIMITS = 4
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Flag that identifies if the opening/closing/settlement price is related to theoretical, daily, previous business day or just an updated value.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT OpenCloseSettlFlag
{
    typedef UInt8 Base;

    /// Flag that identifies if the opening/closing/settlement price is related to theoretical, daily, previous business day or just an updated value.
    enum Enum
    {
        /// Daily settlement entry.
        DAILY = 0,

        /// Session settlement entry.
        SESSION = 1,

        /// Expected entry (preliminary price).
        EXPECTED_ENTRY = 3,

        /// Entry from previous business day.
        ENTRY_FROM_PREVIOUS_BUSINESS_DAY = 4,

        /// Theoretical Price.
        THEORETICAL_PRICE = 5
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Describes how the price limits are expressed.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT PriceLimitType
{
    typedef UInt8 Base;

    /// Describes how the price limits are expressed.
    enum Enum
    {
        /// Price Unit.
        PRICE_UNIT = 0,

        /// Ticks.
        TICKS = 1,

        /// Percentage.
        PERCENTAGE = 2
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Band Midpoint Type, used with Auction Price Banding.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT PriceBandMidpointPriceType
{
    typedef UInt8 Base;

    /// Band Midpoint Type, used with Auction Price Banding.
    enum Enum
    {
        /// Last traded price.
        LAST_TRADED_PRICE = 0,

        /// Complementary last price.
        COMPLEMENTARY_LAST_PRICE = 1,

        /// Theoretical Price.
        THEORETICAL_PRICE = 2
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of settlement price.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT SettlPriceType
{
    typedef UInt8 Base;

    /// Type of settlement price.
    enum Enum
    {
        /// Final.
        FINAL = 1,

        /// Theoretical / Preview.
        THEORETICAL = 2,

        /// Updated.
        UPDATED = 3
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates the Underlying Instrument price type reflected in Index value. Used for Composite Underlying Price.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT UnderlyingPxType
{
    typedef UInt8 Base;

    /// Indicates the Underlying Instrument price type reflected in Index value. Used for Composite Underlying Price.
    enum Enum
    {
        /// Trade.
        TRADE = 0,

        /// Average of TOB.
        AVERAGE_OF_TOB = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Types of Market Data update action.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT UpdateAction
{
    typedef UInt8 Base;

    /// Types of Market Data update action.
    enum Enum
    {
        /// New.
        NEW = 0,

        /// Change.
        CHANGE = 1,

        /// Delete.
        DELETE = 2,

        /// Delete Thru - only for MBO.
        DELETE_THRU = 3,

        /// Delete From - only for MBO.
        DELETE_FROM = 4,

        /// Overlay - not used.
        OVERLAY = 5
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of the Market Data Entry.
///
/// FIX type: Char.
ONIXS_B3_UMDF_MD_LTWT_STRUCT EntryType
{
    typedef Char Base;

    /// Type of the Market Data Entry.
    enum Enum
    {
        /// Bid.
        BID = '0',

        /// Offer.
        OFFER = '1',

        /// Trade or Trade Summary or Last Trade Price.
        TRADE = '2',

        /// Index Value.
        INDEX_VALUE = '3',

        /// Opening Price.
        OPENING_PRICE = '4',

        /// Closing Price.
        CLOSING_PRICE = '5',

        /// Settlement Price.
        SETTLEMENT_PRICE = '6',

        /// Session High Price.
        SESSION_HIGH_PRICE = '7',

        /// Session Low Price.
        SESSION_LOW_PRICE = '8',

        /// Execution Statistics for related Trades.
        EXECUTION_STATISTICS = '9',

        /// Imbalance.
        IMBALANCE = 'A',

        /// Trade Volume.
        TRADE_VOLUME = 'B',

        /// Open Interest.
        OPEN_INTEREST = 'C',

        /// Empty Book.
        EMPTY_BOOK = 'J',

        /// Security Trading State / Phase.
        SECURITY_TRADING_STATE_PHASE = 'c',

        /// Price band.
        PRICE_BAND = 'g',

        /// Quantity band.
        QUANTITY_BAND = 'h',

        /// Composite Underlying Price.
        COMPOSITE_UNDERLYING_PRICE = 'D',

        /// Execution Summary for related Trades.
        EXECUTION_SUMMARY = 's',

        /// Volatility price.
        VOLATILITY_PRICE = 'v',

        /// Trade busted by Market Supervision.
        TRADE_BUST = 'u'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Source for the news.
ONIXS_B3_UMDF_MD_LTWT_STRUCT NewsSource
{
    typedef UInt8 Base;

    /// Source for the news.
    enum Enum
    {
        /// Other news source.
        OTHER = 0,

        /// DCM.
        DCM = 1,

        /// BBMNet.
        BBMNET = 2,

        /// MarketSurveillance.
        MARKET_SURVEILLANCE = 3,

        /// Internet.
        INTERNET = 4,

        /// DPR-VE.
        DPR_VE = 5,

        /// Mkt Ops FX Agency.
        MKT_OPS_FX_AGENCY = 19,

        /// Mkt Ops Derivatives Agency.
        MKT_OPS_DERIVATIVES_AGENCY = 20,

        /// Over-the-counter News Agency.
        OVER_THE_COUNTER_NEWS_AGENCY = 11,

        /// Electronic Purchase Exchange.
        ELECTRONIC_PURCHASE_EXCHANGE = 13,

        /// CBLC News Agency.
        CBLC_NEWS_AGENCY = 14,

        /// BOVESPA – Index Agency.
        BOVESPA_INDEX_AGENCY = 15,

        /// BOVESPA – Institutional Agency.
        BOVESPA_INSTITUTIONAL_AGENCY = 16,

        /// Mkt Ops Equities Agency.
        MKT_OPS_EQUITIES_AGENCY = 17,

        /// BOVESPA – Companies Agency.
        BOVESPA_COMPANIES_AGENCY = 18
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies the service pack release being applied at message level.
ONIXS_B3_UMDF_MD_LTWT_STRUCT ApplVerID
{
    typedef UInt8 Base;

    /// Specifies the service pack release being applied at message level.
    enum Enum
    {
        /// FIX 2.7.
        FIX27 = 0,

        /// FIX 3.0.
        FIX30 = 1,

        /// FIX 4.0.
        FIX40 = 2,

        /// FIX 4.1.
        FIX41 = 3,

        /// FIX 4.2.
        FIX42 = 4,

        /// FIX 4.3.
        FIX43 = 5,

        /// FIX 4.4.
        FIX44 = 6,

        /// FIX 5.0.
        FIX50 = 7,

        /// FIX 5.0 SP1.
        FIX50SP1 = 8,

        /// FIX 5.0 SP2.
        FIX50SP2 = 9
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies the type of multileg order. Defines whether the security is pre-defined or user-defined.
ONIXS_B3_UMDF_MD_LTWT_STRUCT MultiLegModel
{
    typedef UInt8 Base;

    /// Specifies the type of multileg order. Defines whether the security is pre-defined or user-defined.
    enum Enum
    {
        /// Predefined Multileg Security.
        PREDEFINED = 0,

        /// User-Defined Multileg Security.
        USER_DEFINED = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Code to represent how the multileg price is to be interpreted when applied to the legs.
ONIXS_B3_UMDF_MD_LTWT_STRUCT MultiLegPriceMethod
{
    typedef UInt8 Base;

    /// Code to represent how the multileg price is to be interpreted when applied to the legs.
    enum Enum
    {
        /// Net Price.
        NET_PRICE = 0,

        /// Reversed Net Price.
        REVERSED_NET_PRICE = 1,

        /// Yield Difference.
        YIELD_DIFFERENCE = 2,

        /// Individual.
        INDIVIDUAL = 3,

        /// Contract Weighted Average Price.
        CONTRACT_WEIGHTED_AVERAGE_PRICE = 4,

        /// Multiplied Price.
        MULTIPLIED_PRICE = 5
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Code to represent the type of instrument attributes.
ONIXS_B3_UMDF_MD_LTWT_STRUCT InstrAttribType
{
    typedef UInt8 Base;

    /// Code to represent the type of instrument attributes.
    enum Enum
    {
        /// Trade type eligibility details for security.
        TRADE_TYPE_ELIGIBILITY = 24,

        /// Eligibility for GTD/GTC.
        GTD_GTC_ELIGIBILITY = 34
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Code to represent the type of instrument attributes.
ONIXS_B3_UMDF_MD_LTWT_STRUCT InstrAttribValue
{
    typedef UInt8 Base;

    /// Code to represent the type of instrument attributes.
    enum Enum
    {
        /// Electronic Match Eligible (871=24) or GTD/GTC Eligible (871=34).
        ELECTRONIC_MATCH_OR_GTD_GTC_ELIGIBLE = 1,

        /// Order Cross Eligible (871=24).
        ORDER_CROSS_ELIGIBLE = 2,

        /// Block Trade Eligible (871=24).
        BLOCK_TRADE_ELIGIBLE = 3,

        /// Request for Quote (RFQ) for Cross Eligible (871=24).
        FLAG_RFQ_FOR_CROSS_ELIGIBLE = 14,

        /// Negotiated Quote Eligible (871=24).
        NEGOTIATED_QUOTE_ELIGIBLE = 17
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies class or source of the SecurityID value.
///
/// FIX type: Char.
ONIXS_B3_UMDF_MD_LTWT_STRUCT SecurityIDSource
{
    typedef Char Base;

    /// Identifies class or source of the SecurityID value.
    enum Enum
    {
        /// ISIN
        ISIN = '4',

        /// EXCHANGE_SYMBOL
        EXCHANGE_SYMBOL = '8'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Sub type of trade assigned to a trade.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT TrdSubType
{
    typedef UInt8 Base;

    /// Sub type of trade assigned to a trade.
    enum Enum
    {
        /// Multi Asset Trade (Termo Vista).
        MULTI_ASSET_TRADE = 101,

        /// Leg Trade (UDS/EDS).
        LEG_TRADE = 102,

        /// Midpoint Trade (MP).
        MIDPOINT_TRADE = 103,

        /// Block Book Trade (PT).
        BLOCK_BOOK_TRADE = 104,

        /// Equities: RFQ Trade, Futures: Fixed Income Trade (RF).
        RF_TRADE = 105,

        /// RLP Trade (RL).
        RLP_TRADE = 106,

        /// Trade at Close Trade (TC).
        TAC_TRADE = 107,

        /// Trade at Average Trade (TA).
        TAA_TRADE = 108,

        /// Sweep Trade (SW).
        SWEEP_TRADE = 109
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates that an implied order can be created for the instrument.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT ImpliedMarketIndicator
{
    typedef UInt8 Base;

    /// Indicates that an implied order can be created for the instrument.
    enum Enum
    {
        /// Not implied.
        NOT_IMPLIED = 0,

        /// Implied enabled.
        IMPLIED = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates the type of payout that will result from an in-the-money option.
///
/// FIX type: Int.
ONIXS_B3_UMDF_MD_LTWT_STRUCT OptPayoutType
{
    typedef UInt8 Base;

    /// Indicates the type of payout that will result from an in-the-money option.
    enum Enum
    {
        /// VANILLA
        VANILLA = 1,

        /// CAPPED
        CAPPED = 2,

        /// BINARY
        BINARY = 3
    };

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Set of conditions describing an imbalance.
ONIXS_B3_UMDF_MD_LTWT_STRUCT ImbalanceCondition
{
public:
    /// Aliases integral type whose bits
    /// are used to indicate flag presence.
    typedef UInt16 Bits;

    enum
    {
        Size = sizeof(Bits)
    };


    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef Bits FirstArgType;
    };

    /// Indicates whether ImbalanceMoreBuyers bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool imbalanceMoreBuyers() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x100);
    }

    /// Indicates whether ImbalanceMoreSellers bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool imbalanceMoreSellers() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x200);
    }

    /// \return elements as they packed in the set.
    Bits bits() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return bits_;
    }

    /// Constructs from a value.
    explicit
    ImbalanceCondition(Bits bits = 0)
        ONIXS_B3_UMDF_MD_NOTHROW
      : bits_(bits)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string
    toString() const;

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator!=(
        const ImbalanceCondition& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator==(
        const ImbalanceCondition& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return this->bits_ == other.bits_;
    }

private:
    Bits bits_;
};

/// Set of conditions describing a trade.
ONIXS_B3_UMDF_MD_LTWT_STRUCT TradeCondition
{
public:
    /// Aliases integral type whose bits
    /// are used to indicate flag presence.
    typedef UInt16 Bits;

    enum
    {
        Size = sizeof(Bits)
    };


    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef Bits FirstArgType;
    };

    /// Indicates whether OpeningPrice bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool openingPrice() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x1);
    }

    /// Indicates whether Crossed bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool crossed() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x2);
    }

    /// Indicates whether LastTradeAtTheSamePrice bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool lastTradeAtTheSamePrice() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x4);
    }

    /// Indicates whether OutOfSequence bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool outOfSequence() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x8);
    }

    /// Indicates whether TradeOnBehalf bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool tradeOnBehalf() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x40);
    }

    /// Indicates whether RegularTrade bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool regularTrade() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x2000);
    }

    /// Indicates whether BlockTrade bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool blockTrade() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x4000);
    }

    /// \return elements as they packed in the set.
    Bits bits() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return bits_;
    }

    /// Constructs from a value.
    explicit
    TradeCondition(Bits bits = 0)
        ONIXS_B3_UMDF_MD_NOTHROW
      : bits_(bits)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string
    toString() const;

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator!=(
        const TradeCondition& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator==(
        const TradeCondition& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return this->bits_ == other.bits_;
    }

private:
    Bits bits_;
};

/// Set of indicators that identify some market data events.
ONIXS_B3_UMDF_MD_LTWT_STRUCT MatchEventIndicator
{
public:
    /// Aliases integral type whose bits
    /// are used to indicate flag presence.
    typedef UInt8 Bits;

    enum
    {
        Size = sizeof(Bits)
    };


    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef Bits FirstArgType;
    };

    /// Indicates whether Implied bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool implied() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x10);
    }

    /// Indicates whether RecoveryMsg bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool recoveryMsg() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x20);
    }

    /// Indicates whether EndOfEvent bit is set.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool endOfEvent() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return 0 != (bits_ & 0x80);
    }

    /// \return elements as they packed in the set.
    Bits bits() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return bits_;
    }

    /// Constructs from a value.
    explicit
    MatchEventIndicator(Bits bits = 0)
        ONIXS_B3_UMDF_MD_NOTHROW
      : bits_(bits)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string
    toString() const;

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator!=(
        const MatchEventIndicator& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return !(*this == other);
    }

    /// Compares encoded data
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    operator==(
        const MatchEventIndicator& other) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return this->bits_ == other.bits_;
    }

private:
    Bits bits_;
};


/// Null value for an optional Int8 field.
typedef
IntegralConstant<Int8, -128>
NullInt8;


/// Null value for an optional Int16 field.
typedef
IntegralConstant<Int16, -32768>
NullInt16;


/// Null value for an optional Int32 field.
typedef
IntegralConstant<Int32, -2147483647-1>
NullInt32;


/// Null value for an optional Int64 field.
typedef
IntegralConstant<Int64, -9223372036854775807LL-1>
NullInt64;


/// Null value for an optional UInt8 field.
typedef
IntegralConstant<UInt8, 255>
NullUInt8;


/// Null value for an optional UInt16 field.
typedef
IntegralConstant<UInt16, 65535>
NullUInt16;


/// Null value for an optional UInt32 field.
typedef
IntegralConstant<UInt32, 4294967295>
NullUInt32;


/// Null value for an optional UInt64 field.
typedef
IntegralConstant<UInt64, 18446744073709551615ULL>
NullUInt64;


/// Null value for an optional Int8NULL field.
typedef
IntegralConstant<Int8, 0>
NullInt8NULL;


/// Null value for an optional Int16NULL field.
typedef
IntegralConstant<Int16, 0>
NullInt16NULL;


/// Null value for an optional Int32NULL field.
typedef
IntegralConstant<Int32, 0>
NullInt32NULL;


/// Null value for an optional Int64NULL field.
typedef
IntegralConstant<Int64, 0LL>
NullInt64NULL;


/// Null value for an optional CharNULL field.
typedef
IntegralConstant<Char, 0>
NullCharNULL;


/// Null value for an optional UInt8NULL field.
typedef
IntegralConstant<UInt8, 0>
NullUInt8NULL;


/// Null value for an optional UInt16NULL field.
typedef
IntegralConstant<UInt16, 0>
NullUInt16NULL;


/// Null value for an optional UInt32NULL field.
typedef
IntegralConstant<UInt32, 0>
NullUInt32NULL;


/// Null value for an optional UInt64NULL field.
typedef
IntegralConstant<UInt64, 0ULL>
NullUInt64NULL;


/// Null value for an optional NumberOfTrades field.
typedef
IntegralConstant<UInt32, 4294967295>
NullNumberOfTrades;


/// Null value for an optional Quantity field.
typedef
IntegralConstant<Int64, -9223372036854775807LL-1>
NullQuantity;


/// Null value for an optional QuantityOptional field.
typedef
IntegralConstant<Int64, -9223372036854775807LL-1>
NullQuantityOptional;


/// Null value for an optional QuantityVolume field.
typedef
IntegralConstant<Int64, -9223372036854775807LL-1>
NullQuantityVolume;


/// Null value for an optional QuantityVolumeOptional field.
typedef
IntegralConstant<Int64, -9223372036854775807LL-1>
NullQuantityVolumeOptional;


/// Null value for an optional FirmOptional field.
typedef
IntegralConstant<UInt32, 0>
NullFirmOptional;


/// Null value for an optional OrderID field.
typedef
IntegralConstant<UInt64, 18446744073709551615ULL>
NullOrderID;


/// Null value for an optional TradeID field.
typedef
IntegralConstant<UInt32, 4294967295>
NullTradeID;


/// Null value for an optional SeqNum field.
typedef
IntegralConstant<UInt32, 4294967295>
NullSeqNum;


/// Null value for an optional SeqNum1 field.
typedef
IntegralConstant<UInt32, 4294967295>
NullSeqNum1;


/// Null value for an optional SecurityID field.
typedef
IntegralConstant<UInt64, 18446744073709551615ULL>
NullSecurityID;


/// Null value for an optional SecurityIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullSecurityIDOptional;


/// Null value for an optional RptSeq field.
typedef
IntegralConstant<UInt32, 0>
NullRptSeq;


/// Null value for an optional ClearingHouseID field.
typedef
IntegralConstant<UInt64, 0ULL>
NullClearingHouseID;


/// Null value for an optional NewsID field.
typedef
IntegralConstant<UInt64, 0ULL>
NullNewsID;


/// Null value for an optional SettlType field.
typedef
IntegralConstant<UInt16, 65535>
NullSettlType;


/// Null value for an optional LocalMktDate field.
typedef
IntegralConstant<UInt16, 65535>
NullLocalMktDate;


/// Null value for an optional LocalMktDateOptional field.
typedef
IntegralConstant<UInt16, 0>
NullLocalMktDateOptional;


/// Null value for an optional LocalMktDate32 field.
typedef
IntegralConstant<Int32, -2147483647-1>
NullLocalMktDate32;


/// Null value for an optional LocalMktDate32Optional field.
typedef
IntegralConstant<Int32, 0>
NullLocalMktDate32Optional;


/// Null value for an optional EntryPositionNo field.
typedef
IntegralConstant<UInt32, 0>
NullEntryPositionNo;


/// Null value for an optional MarketSegmentID field.
typedef
IntegralConstant<UInt8, 0>
NullMarketSegmentID;



/// Converts days since epoch to Timestamp value.
inline
ONIXS_B3_UMDF_MD_NODISCARD
Timestamp
localMktDateToTimestamp(LocalMktDate days) ONIXS_B3_UMDF_MD_NOTHROW
{
    return Timestamp(TimeSpan(days, 0, 0, 0, 0).ticks());
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
