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

#include <OnixS/B3/BOE/messaging/StrRef.h>
#include <OnixS/B3/BOE/messaging/Integral.h>
#include <OnixS/B3/BOE/messaging/Time.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Null value for an optional Char field.
typedef
IntegralConstant<Char, '\x0'>
NullChar;


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


/// Unique identifier for this allocation instruction message.
///
/// FIX type: Int.
typedef UInt64 AllocID;


/// Unique identifier of the order as assigned by the market participant.
///
/// FIX type: Int.
typedef UInt64 ClOrdID;


/// Optional unique identifier of the order as assigned by the market participant.
///
/// FIX type: Int.
typedef UInt64 ClOrdIDOptional;


/// Client connection identification on the gateway assigned by B3.
///
/// FIX type: Int.
typedef UInt32 SessionID;


/// Optional client connection identification on the gateway assigned by B3.
///
/// FIX type: Int.
typedef UInt32 SessionIDOptional;


/// Session version identification: unique identification of a sequence of messages to be transmitted to exchange gateway associated with given SessionId.
///
/// FIX type: Int.
typedef UInt64 SessionVerID;


/// Optional session version identification: unique identification of a sequence of messages to be transmitted to exchange gateway associated with given SessionId.
///
/// FIX type: Int.
typedef UInt64 SessionVerIDOptional;


/// Sequence number of a given SessionID/SessionVerID.
///
/// FIX type: Int.
typedef UInt32 SeqNum;


/// Optional sequence number of a given SessionID/SessionVerID.
///
/// FIX type: Int.
typedef UInt32 SeqNumOptional;


/// Quantity in order/trade.
///
/// FIX type: Qty.
typedef UInt64 Quantity;


/// Optional quantity in order/trade.
///
/// FIX type: Qty.
typedef UInt64 QuantityOptional;


/// Local calendar date: days since Unix epoch (January 1st, 1970).
///
/// FIX type: LocalMktDate.
typedef UInt16 LocalMktDate;


/// Local calendar date: days since Unix epoch (January 1st, 1970).
///
/// FIX type: LocalMktDate.
typedef UInt16 LocalMktDateOptional;


/// Account mnemonic.
///
/// FIX type: Int.
typedef UInt32 Account;


/// Optional account mnemonic.
///
/// FIX type: Int.
typedef UInt32 AccountOptional;


/// Identification of the broker firm.
///
/// FIX type: Int.
typedef UInt32 Firm;


/// Optional identification of the broker firm.
///
/// FIX type: Int.
typedef UInt32 FirmOptional;


/// Deadline for completing the forward deal.
///
/// FIX type: Int.
typedef UInt16 DaysToSettlement;


/// Optional deadline for completing the forward deal.
///
/// FIX type: Int.
typedef
UInt16
DaysToSettlementOptional;


/// Unique identifier of execution message as assigned by exchange.
///
/// FIX type: Int.
typedef UInt64 ExecID;


/// Optional unique identifier of execution message as assigned by exchange.
///
/// FIX type: Int.
typedef UInt64 ExecIDOptional;


/// Exchange-generated order identifier.
///
/// FIX type: Int.
typedef UInt64 OrderID;


/// Optional exchange-generated order identifier.
///
/// FIX type: Int.
typedef UInt64 OrderIDOptional;


/// Code to identify reason for order rejection. Please refer to the error codes document for domain information.
///
/// FIX type: Int.
typedef UInt32 RejReason;


/// Optional code to identify reason for order rejection. Please refer to the error codes document for domain information.
///
/// FIX type: Int.
typedef UInt32 RejReasonOptional;


/// Unique identifier for this allocation report message.
///
/// FIX type: Int.
typedef UInt64 AllocReportID;


/// Unique identifier for this position maintenance report message.
///
/// FIX type: Int.
typedef UInt64 PosMaintRptID;


/// Optional unique identifier for this position maintenance report message.
///
/// FIX type: Int.
typedef
UInt64
PosMaintRptIDOptional;


/// Unique identifier for the position maintenance request.
///
/// FIX type: Int.
typedef UInt64 PosReqID;


/// Optional unique identifier for the position maintenance request.
///
/// FIX type: Int.
typedef UInt64 PosReqIDOptional;


/// Unique ID of a Security Definition Request/Response.
///
/// FIX type: Int.
typedef UInt64 SecurityReqRespID;


/// Value of business-level identification field on the message being referenced.
///
/// FIX type: Int.
typedef UInt64 BusinessRejectRefID;


/// Unique ID of Order Mass Action Report as assigned by the matching engine.
///
/// FIX type: Int.
typedef UInt64 MassActionReportID;


/// Optional unique ID of Order Mass Action Report as assigned by the matching engine.
///
/// FIX type: Int.
typedef
UInt64
MassActionReportIDOptional;


/// Identifies the order tag identification.
///
/// FIX type: Int.
typedef UInt8 OrdTagID;


/// Identifies the market segment.
///
/// FIX type: Int.
typedef UInt8 MarketSegmentID;


/// Optional identifier of the market segment.
///
/// FIX type: Int.
typedef
UInt8
MarketSegmentIDOptional;


/// Security identification as defined by exchange. For the SecurityID list, see the Security List/Definition message in Market Data feed.
///
/// FIX type: Int.
typedef UInt64 SecurityID;


/// Optional security identification as defined by exchange. For the SecurityID list, see the Security List/Definition message in Market Data feed.
///
/// FIX type: Int.
typedef UInt64 SecurityIDOptional;


/// Identifier for a cross order. Must be unique during a given trading day.
///
/// FIX type: Int.
typedef UInt64 CrossID;


/// Identifier for a cross order.
///
/// FIX type: Int.
typedef UInt64 CrossIDOptional;


/// The unique identification assigned to the trade entity once it is received or matched by the exchange or central counterparty.
///
/// FIX type: Int.
typedef UInt32 TradeID;


/// Optional unique identification assigned to the trade entity once it is received or matched by the exchange or central counterparty.
///
/// FIX type: Int.
typedef UInt32 TradeIDOptional;


/// Unique identifier for quote.
///
/// FIX type: Int.
typedef UInt64 QuoteID;


/// Optional unique identifier for quote.
///
/// FIX type: Int.
typedef UInt64 QuoteIDOptional;


/// Unique identifier for quote request.
///
/// FIX type: Int.
typedef UInt64 QuoteReqID;


/// Optional unique identifier for quote request.
///
/// FIX type: Int.
typedef UInt64 QuoteReqIDOptional;


/// Number of leg fill notice messages sent with spread summary.
///
/// FIX type: Int.
typedef UInt8 TotNoRelatedSym;


/// Counter of related messages.
///
/// FIX type: Int.
typedef UInt32 MessageCounter;


/// Optional unique identification of a client-assigned strategy.
///
/// FIX type: Int.
typedef Int32 StrategyIDOptional;


/// Type used to encode enum with zero nullValue.
///
/// FIX type: Int.
typedef UInt8 Uint8EnumEncoding;


/// Type used to encode enum with zero nullValue.
///
/// FIX type: Int.
typedef UInt16 Uint16EnumEncoding;


/// Boolean type.
///
/// FIX type: Boolean.
ONIXS_B3_BOE_LTWT_STRUCT Boolean
{
    typedef UInt8 Base;

    /// Boolean type
    enum Enum
    {
        /// false, N, 0.
        FalseValue = 0,

        /// true, Y, 1.
        TrueValue = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies allocation transaction type.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT AllocTransType
{
    typedef Char Base;

    /// Identifies allocation transaction type.
    enum Enum
    {
        /// New
        New = '0',

        /// Cancel
        Cancel = '2'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Describes the specific type or purpose of an Allocation Report message.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT AllocReportType
{
    typedef Char Base;

    /// Describes the specific type or purpose of an Allocation Report message.
    enum Enum
    {
        /// RequestToIntermediary
        RequestToIntermediary = '8'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Describes the specific type or purpose of an Allocation message.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT AllocType
{
    typedef Char Base;

    /// Describes the specific type or purpose of an Allocation message.
    enum Enum
    {
        /// RequestToIntermediary
        RequestToIntermediary = '8'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates how the orders being booked and allocated by an Allocation Instruction.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT AllocNoOrdersType
{
    typedef Char Base;

    /// Indicates how the orders being booked and allocated by an Allocation Instruction.
    enum Enum
    {
        /// NotSpecified
        NotSpecified = '0'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies status of allocation.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT AllocStatus
{
    typedef Char Base;

    /// Identifies status of allocation.
    enum Enum
    {
        /// Accepted
        Accepted = '0',

        /// RejectedByIntermediary
        RejectedByIntermediary = '5'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the status of the quote acknowledgement.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT QuoteStatus
{
    typedef UInt8 Base;

    /// Identifies the status of the quote acknowledgement.
    enum Enum
    {
        /// Expired
        Expired = 7,

        /// Accepted
        Accepted = 0,

        /// Rejected
        Rejected = 5,

        /// QuoteNotFound
        QuoteNotFound = 9,

        /// Pending
        Pending = 10,

        /// Pass
        Pass = 11,

        /// Canceled
        Canceled = 17
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the type of request that a Quote Status Report is in response to.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT QuoteStatusResponseTo
{
    typedef Char Base;

    /// Identifies the type of request that a Quote Status Report is in response to
    enum Enum
    {
        /// Quote
        Quote = '0',

        /// QuoteRequest
        QuoteRequest = '1',

        /// QuoteCancel
        QuoteCancel = '2',

        /// QuoteRequestReject
        QuoteRequestReject = '3'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the type of quote cancel.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT QuoteCancelType
{
    typedef UInt8 Base;

    /// Identifies the type of quote cancel.
    enum Enum
    {
        /// CancelForQuoteId
        CancelForQuoteId = 5
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Used to identify the type of quantity.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT PosType
{
    typedef Char Base;

    /// Used to identify the type of quantity.
    enum Enum
    {
        /// TransactionQuantity
        TransactionQuantity = 'T',

        /// StartOfDayQty
        StartOfDayQty = 'S',

        /// OptionExerciseQty
        OptionExerciseQty = 'E',

        /// BlockedQty
        BlockedQty = 'B',

        /// UncoveredQty
        UncoveredQty = 'U',

        /// CoveredQty
        CoveredQty = 'C'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies the scope of the action. All Day and MOC orders will be cancelled. GTC, GTD and MOA orders will not be cancelled.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT MassActionScope
{
    typedef UInt8 Base;

    /// Specifies the scope of the action. All Day and MOC orders will be cancelled. GTC, GTD and MOA orders will not be cancelled.
    enum Enum
    {
        /// AllOrdersForATradingSession
        AllOrdersForATradingSession = 6
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies the type of action requested.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT MassActionType
{
    typedef UInt8 Base;

    /// Specifies the type of action requested.
    enum Enum
    {
        /// ReleaseOrdersFromSuspension
        ReleaseOrdersFromSuspension = 2,

        /// CancelOrders
        CancelOrders = 3,

        /// CancelAndSuspendOrders
        CancelAndSuspendOrders = 4
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies the action taken by matching engine when it receives the Order Mass Action Request.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT MassActionResponse
{
    typedef Char Base;

    /// Specifies the action taken by matching engine when it receives the Order Mass Action Request.
    enum Enum
    {
        /// Rejected
        Rejected = '0',

        /// Accepted
        Accepted = '1'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Reason Order Mass Action Request was rejected.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT MassActionRejectReason
{
    typedef UInt8 Base;

    /// Reason Order Mass Action Request was rejected.
    enum Enum
    {
        /// MassActionNotSupported
        MassActionNotSupported = 0,

        /// InvalidOrUnknownMarketSegment
        InvalidOrUnknownMarketSegment = 8,

        /// Other
        Other = 99
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of Security Definition message response.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT SecurityResponseType
{
    typedef UInt8 Base;

    /// Type of Security Definition message response.
    enum Enum
    {
        /// AcceptSecurityProposalAsIs
        AcceptSecurityProposalAsIs = 1,

        /// RejectSecurityProposal
        RejectSecurityProposal = 5,

        /// AcceptSecurityAsProposalWithRevisions
        AcceptSecurityAsProposalWithRevisions = 2
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Status of Position Maintenance Request.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT PosMaintStatus
{
    typedef Char Base;

    /// Status of Position Maintenance Request.
    enum Enum
    {
        /// Accepted
        Accepted = '0',

        /// Rejected
        Rejected = '2',

        /// Completed
        Completed = '3',

        /// NotExecuted
        NotExecuted = '9'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies if a simultaneous trade of the underlying is to be performed.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT ExecuteUnderlyingTrade
{
    typedef Char Base;

    /// Specifies if a simultaneous trade of the underlying is to be performed.
    enum Enum
    {
        /// NoUnderlyingTrade
        NoUnderlyingTrade = '0',

        /// UnderlyingOpposingTrade
        UnderlyingOpposingTrade = '1'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the type of position transaction.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT PosTransType
{
    typedef UInt8 Base;

    /// Identifies the type of position transaction.
    enum Enum
    {
        /// Exercise
        Exercise = 1,

        /// AutomaticExercise
        AutomaticExercise = 105,

        /// ExerciseNotAutomatic
        ExerciseNotAutomatic = 106
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Maintenance Action to be performed.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT PosMaintAction
{
    typedef Char Base;

    /// Maintenance Action to be performed.
    enum Enum
    {
        /// New
        New = '1',

        /// Cancel
        Cancel = '3'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates who in the contract has control over evoking settlement.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT SettlType
{
    typedef Char Base;

    /// Indicates who in the contract has control over evoking settlement.
    enum Enum
    {
        /// BuyersDiscretion
        BuyersDiscretion = '0',

        /// SellersDiscretion
        SellersDiscretion = '8',

        /// Mutual
        Mutual = 'X'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates which order should be cancelled due to self-trade prevention.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT SelfTradePreventionInstruction
{
    typedef UInt8 Base;

    /// Indicates which order should be cancelled due to self-trade prevention.
    enum Enum
    {
        /// None
        None = 0,

        /// CancelAggressorOrder
        CancelAggressorOrder = 1,

        /// CancelRestingOrder
        CancelRestingOrder = 2,

        /// CancelBothOrders
        CancelBothOrders = 3
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Unit of time used for measurement.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT TimeUnit
{
    typedef UInt8 Base;

    /// Unit of time used for measurement.
    enum Enum
    {
        /// Second
        Second = 0,

        /// Millisecond
        Millisecond = 3,

        /// Microsecond
        Microsecond = 6,

        /// Nanosecond
        Nanosecond = 9
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Defines message type.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT MessageType
{
    typedef UInt8 Base;

    /// Defines message type.
    enum Enum
    {
        /// Negotiate
        Negotiate = 0,

        /// NegotiateResponse
        NegotiateResponse = 1,

        /// NegotiateReject
        NegotiateReject = 2,

        /// Establish
        Establish = 3,

        /// EstablishAck
        EstablishAck = 4,

        /// EstablishReject
        EstablishReject = 5,

        /// Terminate
        Terminate = 6,

        /// NotApplied
        NotApplied = 9,

        /// RetransmitRequest
        RetransmitRequest = 10,

        /// Retransmission
        Retransmission = 11,

        /// RetransmitReject
        RetransmitReject = 12,

        /// Sequence
        Sequence = 13,

        /// BusinessMessageReject
        BusinessMessageReject = 14,

        /// SimpleNewOrder
        SimpleNewOrder = 15,

        /// SimpleModifyOrder
        SimpleModifyOrder = 16,

        /// NewOrderSingle
        NewOrderSingle = 17,

        /// OrderCancelReplaceRequest
        OrderCancelReplaceRequest = 18,

        /// OrderCancelRequest
        OrderCancelRequest = 19,

        /// NewOrderCross
        NewOrderCross = 20,

        /// ExecutionReportNew
        ExecutionReportNew = 21,

        /// ExecutionReportModify
        ExecutionReportModify = 22,

        /// ExecutionReportCancel
        ExecutionReportCancel = 23,

        /// ExecutionReportTrade
        ExecutionReportTrade = 24,

        /// ExecutionReportReject
        ExecutionReportReject = 25,

        /// ExecutionReportForward
        ExecutionReportForward = 26,

        /// SecurityDefinitionRequest
        SecurityDefinitionRequest = 27,

        /// SecurityDefinitionResponse
        SecurityDefinitionResponse = 28,

        /// OrderMassActionRequest
        OrderMassActionRequest = 29,

        /// OrderMassActionReport
        OrderMassActionReport = 30,

        /// QuoteRequest
        QuoteRequest = 31,

        /// QuoteStatusReport
        QuoteStatusReport = 32,

        /// Quote
        Quote = 33,

        /// QuoteCancel
        QuoteCancel = 34,

        /// QuoteRequestReject
        QuoteRequestReject = 35,

        /// PositionMaintenanceCancelRequest
        PositionMaintenanceCancelRequest = 36,

        /// PositionMaintenanceRequest
        PositionMaintenanceRequest = 37,

        /// PositionMaintenanceReport
        PositionMaintenanceReport = 38,

        /// AllocationInstruction
        AllocationInstruction = 39,

        /// AllocationReport
        AllocationReport = 40
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of message flow from client to server or from server to client.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT FlowType
{
    typedef UInt8 Base;

    /// Type of message flow from client to server or from server to client.
    enum Enum
    {
        /// None
        None = 0,

        /// Recoverable
        Recoverable = 1,

        /// Unsequenced
        Unsequenced = 2,

        /// Idempotent
        Idempotent = 3
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the code of reject negotiation.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT NegotiationRejectCode
{
    typedef UInt8 Base;

    /// Identifies the code of reject negotiation.
    enum Enum
    {
        /// Unspecified
        Unspecified = 0,

        /// Credentials
        Credentials = 1,

        /// FlowtypeNotSupported
        FlowtypeNotSupported = 2,

        /// AlreadyNegotiated
        AlreadyNegotiated = 3,

        /// SessionBlocked
        SessionBlocked = 4,

        /// InvalidSessionid
        InvalidSessionid = 5,

        /// InvalidSessionverid
        InvalidSessionverid = 6,

        /// InvalidTimestamp
        InvalidTimestamp = 7,

        /// InvalidFirm
        InvalidFirm = 8,

        /// NegotiateNotAllowed
        NegotiateNotAllowed = 20,

        /// DuplicateSessionConnection
        DuplicateSessionConnection = 21,

        /// AuthenticationInProgress
        AuthenticationInProgress = 22,

        /// ProtocolVersionNotSupported
        ProtocolVersionNotSupported = 23
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the code of reject establishment.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT EstablishRejectCode
{
    typedef UInt8 Base;

    /// Identifies the code of reject establishment.
    enum Enum
    {
        /// Unspecified
        Unspecified = 0,

        /// Credentials
        Credentials = 1,

        /// Unnegotiated
        Unnegotiated = 2,

        /// AlreadyEstablished
        AlreadyEstablished = 3,

        /// SessionBlocked
        SessionBlocked = 4,

        /// InvalidSessionid
        InvalidSessionid = 5,

        /// InvalidSessionverid
        InvalidSessionverid = 6,

        /// InvalidTimestamp
        InvalidTimestamp = 7,

        /// InvalidKeepaliveInterval
        InvalidKeepaliveInterval = 8,

        /// InvalidNextseqno
        InvalidNextseqno = 9,

        /// EstablishAttemptsExceeded
        EstablishAttemptsExceeded = 10,

        /// EstablishNotAllowed
        EstablishNotAllowed = 20,

        /// DuplicateSessionConnection
        DuplicateSessionConnection = 21,

        /// AuthenticationInProgress
        AuthenticationInProgress = 22,

        /// ProtocolVersionNotSupported
        ProtocolVersionNotSupported = 23
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the code of termination.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT TerminationCode
{
    typedef UInt8 Base;

    /// Identifies the code of termination.
    enum Enum
    {
        /// Unspecified
        Unspecified = 0,

        /// Finished
        Finished = 1,

        /// Unnegotiated
        Unnegotiated = 2,

        /// NotEstablished
        NotEstablished = 3,

        /// SessionBlocked
        SessionBlocked = 4,

        /// NegotiationInProgress
        NegotiationInProgress = 5,

        /// EstablishInProgress
        EstablishInProgress = 6,

        /// KeepaliveIntervalLapsed
        KeepaliveIntervalLapsed = 10,

        /// InvalidSessionid
        InvalidSessionid = 11,

        /// InvalidSessionverid
        InvalidSessionverid = 12,

        /// InvalidTimestamp
        InvalidTimestamp = 13,

        /// InvalidNextseqno
        InvalidNextseqno = 14,

        /// UnrecognizedMessage
        UnrecognizedMessage = 15,

        /// InvalidSofh
        InvalidSofh = 16,

        /// DecodingError
        DecodingError = 17,

        /// TerminateNotAllowed
        TerminateNotAllowed = 20,

        /// TerminateInProgress
        TerminateInProgress = 21,

        /// ProtocolVersionNotSupported
        ProtocolVersionNotSupported = 23,

        /// BackupTakeoverInProgress
        BackupTakeoverInProgress = 30
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the code of reject retransmission.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT RetransmitRejectCode
{
    typedef UInt8 Base;

    /// Identifies the code of reject retransmission.
    enum Enum
    {
        /// OutOfRange
        OutOfRange = 0,

        /// InvalidSession
        InvalidSession = 1,

        /// RequestLimitExceeded
        RequestLimitExceeded = 2,

        /// RetransmitInProgress
        RetransmitInProgress = 3,

        /// InvalidTimestamp
        InvalidTimestamp = 4,

        /// InvalidFromseqno
        InvalidFromseqno = 5,

        /// InvalidCount
        InvalidCount = 9,

        /// ThrottleReject
        ThrottleReject = 10,

        /// SystemBusy
        SystemBusy = 11
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Criteria used to initiate cancel on disconnect mechanism by the gateway.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT CancelOnDisconnectType
{
    typedef UInt8 Base;

    /// Criteria used to initiate cancel on disconnect mechanism by the gateway.
    enum Enum
    {
        /// DoNotCancelOnDisconnectOrTerminate
        DoNotCancelOnDisconnectOrTerminate = 0,

        /// CancelOnDisconnectOnly
        CancelOnDisconnectOnly = 1,

        /// CancelOnTerminateOnly
        CancelOnTerminateOnly = 2,

        /// CancelOnDisconnectOrTerminate
        CancelOnDisconnectOrTerminate = 3
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Side of order.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT Side
{
    typedef Char Base;

    /// Side of order.
    enum Enum
    {
        /// Buy
        Buy = '1',

        /// Sell
        Sell = '2'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies how long the order remains in effect.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT TimeInForce
{
    typedef Char Base;

    /// Specifies how long the order remains in effect.
    enum Enum
    {
        /// Day
        Day = '0',

        /// GoodTillCancel
        GoodTillCancel = '1',

        /// ImmediateOrCancel
        ImmediateOrCancel = '3',

        /// FillOrKill
        FillOrKill = '4',

        /// GoodTillDate
        GoodTillDate = '6',

        /// AtTheClose
        AtTheClose = '7',

        /// GoodForAuction
        GoodForAuction = 'A'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Specifies how long the order remains in effect.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT SimpleTimeInForce
{
    typedef Char Base;

    /// Specifies how long the order remains in effect.
    enum Enum
    {
        /// Day
        Day = '0',

        /// ImmediateOrCancel
        ImmediateOrCancel = '3',

        /// FillOrKill
        FillOrKill = '4'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Order type.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT OrdType
{
    typedef Char Base;

    /// Order type.
    enum Enum
    {
        /// Market
        Market = '1',

        /// Limit
        Limit = '2',

        /// StopLoss
        StopLoss = '3',

        /// StopLimit
        StopLimit = '4',

        /// MarketWithLeftoverAsLimit
        MarketWithLeftoverAsLimit = 'K',

        /// Rlp
        Rlp = 'W',

        /// PeggedMidpoint
        PeggedMidpoint = 'P'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Order type.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT SimpleOrdType
{
    typedef Char Base;

    /// Order type.
    enum Enum
    {
        /// Market
        Market = '1',

        /// Limit
        Limit = '2'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates additional order instruction.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT RoutingInstruction
{
    typedef UInt8 Base;

    /// Indicates additional order instruction.
    enum Enum
    {
        /// RetailLiquidityTaker
        RetailLiquidityTaker = 1,

        /// WaivedPriority
        WaivedPriority = 2,

        /// BrokerOnly
        BrokerOnly = 3,

        /// BrokerOnlyRemoval
        BrokerOnlyRemoval = 4
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Describes the action that triggered this specific Execution Report - see the OrdStatus (39) tag for the current order status (e.g, Partially Filled).
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT ExecType
{
    typedef Char Base;

    /// Describes the action that triggered this specific Execution Report - see the OrdStatus (39) tag for the current order status (e.g, Partially Filled).
    enum Enum
    {
        /// Trade
        Trade = 'F',

        /// TradeCancel
        TradeCancel = 'H'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies current status of order.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT OrdStatus
{
    typedef Char Base;

    /// Identifies current status of order.
    enum Enum
    {
        /// New
        New = '0',

        /// PartiallyFilled
        PartiallyFilled = '1',

        /// Filled
        Filled = '2',

        /// Canceled
        Canceled = '4',

        /// Replaced
        Replaced = '5',

        /// Rejected
        Rejected = '8',

        /// Expired
        Expired = 'C',

        /// Restated
        Restated = 'R',

        /// PreviousFinalState
        PreviousFinalState = 'Z'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Used to communicate a reason for a solicited cancel.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT ExecRestatementReasonValidForSingleCancel
{
    typedef UInt8 Base;

    /// Used to communicate a reason for a solicited cancel.
    enum Enum
    {
        /// CancelOrderDueToOperationalError
        CancelOrderDueToOperationalError = 203
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Used to communicate event type which triggers mass cancelation.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT ExecRestatementReasonValidForMassCancel
{
    typedef UInt8 Base;

    /// Used to communicate event type which triggers mass cancelation.
    enum Enum
    {
        /// OrderMassActionFromClientRequest
        OrderMassActionFromClientRequest = 202,

        /// MassCancelOrderDueToOperationalErrorRequest
        MassCancelOrderDueToOperationalErrorRequest = 207
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates reason of cancelation, if available.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT ExecRestatementReason
{
    typedef UInt8 Base;

    /// Indicates reason of cancelation, if available.
    enum Enum
    {
        /// MarketOption
        MarketOption = 8,

        /// CancelOnHardDisconnection
        CancelOnHardDisconnection = 100,

        /// CancelOnTerminate
        CancelOnTerminate = 101,

        /// CancelOnDisconnectAndTerminate
        CancelOnDisconnectAndTerminate = 102,

        /// SelfTradingPrevention
        SelfTradingPrevention = 103,

        /// CancelFromFirmsoft
        CancelFromFirmsoft = 105,

        /// CancelRestingOrderOnSelfTrade
        CancelRestingOrderOnSelfTrade = 107,

        /// MarketMakerProtection
        MarketMakerProtection = 200,

        /// RiskManagementCancellation
        RiskManagementCancellation = 201,

        /// OrderMassActionFromClientRequest
        OrderMassActionFromClientRequest = 202,

        /// CancelOrderDueToOperationalError
        CancelOrderDueToOperationalError = 203,

        /// OrderCancelledDueToOperationalError
        OrderCancelledDueToOperationalError = 204,

        /// CancelOrderFirmsoftDueToOperationalError
        CancelOrderFirmsoftDueToOperationalError = 205,

        /// OrderCancelledFirmsoftDueToOperationalError
        OrderCancelledFirmsoftDueToOperationalError = 206,

        /// MassCancelOrderDueToOperationalErrorRequest
        MassCancelOrderDueToOperationalErrorRequest = 207,

        /// MassCancelOrderDueToOperationalErrorEffective
        MassCancelOrderDueToOperationalErrorEffective = 208,

        /// CancelOnMidpointBrokerOnlyRemoval
        CancelOnMidpointBrokerOnlyRemoval = 209,

        /// CancelRemainingFromSweepCross
        CancelRemainingFromSweepCross = 210,

        /// MassCancelOnBehalf
        MassCancelOnBehalf = 211,

        /// MassCancelOnBehalfDueToOperationalErrorEffective
        MassCancelOnBehalfDueToOperationalErrorEffective = 212
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Used to indicate what an Execution Report represents.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT MultiLegReportingType
{
    typedef Char Base;

    /// Used to indicate what an Execution Report represents.
    enum Enum
    {
        /// SingleSecurity
        SingleSecurity = '1',

        /// IndividuallegOfMultilegSecurity
        IndividuallegOfMultilegSecurity = '2',

        /// MultilegSecurity
        MultilegSecurity = '3'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Defines the type of interest behind a trade i.e. why a trade occurred.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT OrderCategory
{
    typedef Char Base;

    /// Defines the type of interest behind a trade i.e. why a trade occurred.
    enum Enum
    {
        /// ResultOfOptionsExercise
        ResultOfOptionsExercise = 'B',

        /// ResultOfAssignmentFromAnOptionsExercise
        ResultOfAssignmentFromAnOptionsExercise = 'C',

        /// ResultOfAutomaticOptionsExercise
        ResultOfAutomaticOptionsExercise = 'D',

        /// ResultOfMidpointOrder
        ResultOfMidpointOrder = 'E',

        /// ResultOfBlockBookTrade
        ResultOfBlockBookTrade = 'F',

        /// ResultOfTradeAtClose
        ResultOfTradeAtClose = 'G',

        /// ResultOfTradeAtAverage
        ResultOfTradeAtAverage = 'H',

        /// ImpliedOrder
        ImpliedOrder = '7'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of Account associated with an order.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT AccountType
{
    typedef UInt8 Base;

    /// Type of Account associated with an order.
    enum Enum
    {
        /// RemoveAccountInformation
        RemoveAccountInformation = 38,

        /// RegularAccount
        RegularAccount = 39
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the type of request that this cancel reject is in response to.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT CxlRejResponseTo
{
    typedef UInt8 Base;

    /// Identifies the type of request that this cancel reject is in response to.
    enum Enum
    {
        /// New
        New = 0,

        /// Cancel
        Cancel = 1,

        /// Replace
        Replace = 2
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates that message may contain information that has been sent under another sequence number.
///
/// FIX type: Boolean.
ONIXS_B3_BOE_LTWT_STRUCT PossResend
{
    typedef UInt8 Base;

    /// Indicates that message may contain information that has been sent under another sequence number.
    enum Enum
    {
        /// false, N, 0.
        FalseValue = 0,

        /// true, Y, 1.
        TrueValue = 1
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifies the class of the SecurityID.
///
/// FIX type: Char.
ONIXS_B3_BOE_LTWT_STRUCT SecurityIDSource
{
    typedef Char Base;

    /// Identifies the class of the SecurityID.
    enum Enum
    {
        /// Isin
        Isin = '4',

        /// ExchangeSymbol
        ExchangeSymbol = '8'
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates cross order purpose.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT CrossedIndicator
{
    typedef UInt16 Base;

    /// Indicates cross order purpose.
    enum Enum
    {
        /// StructuredTransaction
        StructuredTransaction = 1001,

        /// OperationalError
        OperationalError = 1002,

        /// TwapVwap
        TwapVwap = 1003
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifier for Trading Session.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT TradingSessionID
{
    typedef UInt8 Base;

    /// Identifier for Trading Session.
    enum Enum
    {
        /// RegularDaySession
        RegularDaySession = 1,

        /// NonRegularSession
        NonRegularSession = 6
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifier for the instrument group phase.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT TradingSessionSubID
{
    typedef UInt8 Base;

    /// Identifier for the instrument group phase.
    enum Enum
    {
        /// Pause
        Pause = 2,

        /// Close
        Close = 4,

        /// Open
        Open = 17,

        /// PreClose
        PreClose = 18,

        /// PreOpen
        PreOpen = 21,

        /// FinalClosingCall
        FinalClosingCall = 101
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Identifier for the instrument status.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT SecurityTradingStatus
{
    typedef UInt8 Base;

    /// Identifier for the instrument status.
    enum Enum
    {
        /// TradingHalt
        TradingHalt = 2,

        /// NoOpen
        NoOpen = 4,

        /// ReadyToTrade
        ReadyToTrade = 17,

        /// Forbidden
        Forbidden = 18,

        /// UnknownOrInvalid
        UnknownOrInvalid = 20,

        /// PreOpen
        PreOpen = 21,

        /// FinalClosingCall
        FinalClosingCall = 101,

        /// Reserved
        Reserved = 110
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Type of cross being submitted to a market.
///
/// FIX type: Int.
ONIXS_B3_BOE_LTWT_STRUCT CrossType
{
    typedef UInt8 Base;

    /// Type of cross being submitted to a market.
    enum Enum
    {
        /// AllOrNoneCross
        AllOrNoneCross = 1,

        /// CrossExecutedAgainstBookFromClient
        CrossExecutedAgainstBookFromClient = 4
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Indicates if one side or the other of a cross order should be prioritized.
ONIXS_B3_BOE_LTWT_STRUCT CrossPrioritization
{
    typedef UInt8 Base;

    /// Indicates if one side or the other of a cross order should be prioritized.
    enum Enum
    {
        /// None
        None = 0,

        /// BuySideIsPrioritized
        BuySideIsPrioritized = 1,

        /// SellSideIsPrioritized
        SellSideIsPrioritized = 2
    };

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    static
    std::string
    toString(
        Enum);
};

/// Set of indicators for a given event. First use case: indicates possible retransmission of message during recovery process.
ONIXS_B3_BOE_LTWT_STRUCT EventIndicator
{
public:
    /// Aliases integral type whose bits
    /// are used to indicate flag presence.
    typedef UInt8 Bits;

    enum
    {
        Size = sizeof(Bits)
    };

    /// This type alias.
    typedef EventIndicator ThisType;

    /// \private
    /// Init traits.
    struct MemberTraits
    {
        enum { Count = 1 };

        typedef Bits FirstArgType;
    };

    /// Indicates whether PossResend bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool possResend() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x1);
    }

    /// Modifies PossResend bit.
    ThisType& setPossResend(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x1; else bits_ &= ~0x1;
        return *this;
    }

    /// Indicates whether LowPriority bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool lowPriority() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x2);
    }

    /// Modifies LowPriority bit.
    ThisType& setLowPriority(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x2; else bits_ &= ~0x2;
        return *this;
    }

    /// Indicates whether Reserved2 bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool reserved2() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x4);
    }

    /// Modifies Reserved2 bit.
    ThisType& setReserved2(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x4; else bits_ &= ~0x4;
        return *this;
    }

    /// Indicates whether Reserved3 bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool reserved3() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x8);
    }

    /// Modifies Reserved3 bit.
    ThisType& setReserved3(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x8; else bits_ &= ~0x8;
        return *this;
    }

    /// Indicates whether Reserved4 bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool reserved4() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x10);
    }

    /// Modifies Reserved4 bit.
    ThisType& setReserved4(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x10; else bits_ &= ~0x10;
        return *this;
    }

    /// Indicates whether Reserved5 bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool reserved5() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x20);
    }

    /// Modifies Reserved5 bit.
    ThisType& setReserved5(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x20; else bits_ &= ~0x20;
        return *this;
    }

    /// Indicates whether Reserved6 bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool reserved6() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x40);
    }

    /// Modifies Reserved6 bit.
    ThisType& setReserved6(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x40; else bits_ &= ~0x40;
        return *this;
    }

    /// Indicates whether Reserved7 bit is set.
    ONIXS_B3_BOE_NODISCARD
    bool reserved7() const
        ONIXS_B3_BOE_NOTHROW
    {
        return 0 != (bits_ & 0x80);
    }

    /// Modifies Reserved7 bit.
    ThisType& setReserved7(bool value)
        ONIXS_B3_BOE_NOTHROW
    {
        if (value) bits_ |= 0x80; else bits_ &= ~0x80;
        return *this;
    }

    /// \return elements as they packed in the set.
    Bits bits() const
        ONIXS_B3_BOE_NOTHROW
    {
        return bits_;
    }

    /// Constructs from a value.
    explicit
    EventIndicator(Bits bits = 0)
        ONIXS_B3_BOE_NOTHROW
      : bits_(bits)
    {
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string
    toString() const;

    /// Compares encoded data
    ONIXS_B3_BOE_NODISCARD
    bool
    operator!=(
        const EventIndicator& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return !(*this == other);
    }

    /// Compares encoded data
    ONIXS_B3_BOE_NODISCARD
    bool
    operator==(
        const EventIndicator& other) const
        ONIXS_B3_BOE_NOTHROW
    {
        return this->bits_ == other.bits_;
    }

private:
    Bits bits_;
};


/// Null value for an optional ClOrdIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullClOrdIDOptional;


/// Null value for an optional SessionIDOptional field.
typedef
IntegralConstant<UInt32, 0>
NullSessionIDOptional;


/// Null value for an optional SessionVerIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullSessionVerIDOptional;


/// Null value for an optional SeqNumOptional field.
typedef
IntegralConstant<UInt32, 0>
NullSeqNumOptional;


/// Null value for an optional QuantityOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullQuantityOptional;


/// Null value for an optional LocalMktDateOptional field.
typedef
IntegralConstant<UInt16, 0>
NullLocalMktDateOptional;


/// Null value for an optional AccountOptional field.
typedef
IntegralConstant<UInt32, 0>
NullAccountOptional;


/// Null value for an optional FirmOptional field.
typedef
IntegralConstant<UInt32, 0>
NullFirmOptional;


/// Null value for an optional DaysToSettlementOptional field.
typedef
IntegralConstant<UInt16, 65535>
NullDaysToSettlementOptional;


/// Null value for an optional ExecIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullExecIDOptional;


/// Null value for an optional OrderIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullOrderIDOptional;


/// Null value for an optional RejReasonOptional field.
typedef
IntegralConstant<UInt32, 0>
NullRejReasonOptional;


/// Null value for an optional PosMaintRptIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullPosMaintRptIDOptional;


/// Null value for an optional PosReqIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullPosReqIDOptional;


/// Null value for an optional BusinessRejectRefID field.
typedef
IntegralConstant<UInt64, 0ULL>
NullBusinessRejectRefID;


/// Null value for an optional MassActionReportIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullMassActionReportIDOptional;


/// Null value for an optional OrdTagID field.
typedef
IntegralConstant<UInt8, 0>
NullOrdTagID;


/// Null value for an optional MarketSegmentIDOptional field.
typedef
IntegralConstant<UInt8, 0>
NullMarketSegmentIDOptional;


/// Null value for an optional SecurityIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullSecurityIDOptional;


/// Null value for an optional CrossIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullCrossIDOptional;


/// Null value for an optional TradeIDOptional field.
typedef
IntegralConstant<UInt32, 0>
NullTradeIDOptional;


/// Null value for an optional QuoteIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullQuoteIDOptional;


/// Null value for an optional QuoteReqIDOptional field.
typedef
IntegralConstant<UInt64, 0ULL>
NullQuoteReqIDOptional;


/// Null value for an optional TotNoRelatedSym field.
typedef
IntegralConstant<UInt8, 0>
NullTotNoRelatedSym;


/// Null value for an optional StrategyIDOptional field.
typedef
IntegralConstant<Int32, 0>
NullStrategyIDOptional;


/// Null value for an optional Uint8EnumEncoding field.
typedef
IntegralConstant<UInt8, 0>
NullUint8EnumEncoding;


/// Null value for an optional Uint16EnumEncoding field.
typedef
IntegralConstant<UInt16, 0>
NullUint16EnumEncoding;



/// Converts days since epoch to Timestamp value.
inline
ONIXS_B3_BOE_NODISCARD
Timestamp
localMktDateToTimestamp(LocalMktDate days) ONIXS_B3_BOE_NOTHROW
{
    return Timestamp(TimeSpan(days, 0, 0, 0, 0).ticks());
}

inline
ONIXS_B3_BOE_NODISCARD
LocalMktDate
timestampToLocalMktDate(const Timestamp& timestamp) ONIXS_B3_BOE_NOTHROW
{
    return static_cast<LocalMktDate>(TimeSpan(timestamp.sinceEpoch()).days());
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
