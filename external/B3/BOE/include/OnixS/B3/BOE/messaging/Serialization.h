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

#include <string>

#include <OnixS/B3/BOE/messaging/Fields.h>
#include <OnixS/B3/BOE/messaging/Composites.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

// Market Data Serialization.

/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    Boolean::Enum value);


/// Serializes into a string.
inline std::string toStr(Boolean::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    Boolean::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    Boolean::Enum value)
{
    toStr(
        str,
        static_cast<Boolean::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    AllocTransType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    AllocTransType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    AllocTransType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    AllocTransType::Enum value)
{
    toStr(
        str,
        static_cast<AllocTransType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    AllocReportType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    AllocReportType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    AllocReportType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    AllocReportType::Enum value)
{
    toStr(
        str,
        static_cast<AllocReportType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    AllocType::Enum value);


/// Serializes into a string.
inline std::string toStr(AllocType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    AllocType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    AllocType::Enum value)
{
    toStr(
        str,
        static_cast<AllocType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    AllocNoOrdersType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    AllocNoOrdersType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    AllocNoOrdersType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    AllocNoOrdersType::Enum value)
{
    toStr(
        str,
        static_cast<AllocNoOrdersType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    AllocStatus::Enum value);


/// Serializes into a string.
inline std::string toStr(AllocStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    AllocStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    AllocStatus::Enum value)
{
    toStr(
        str,
        static_cast<AllocStatus::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    QuoteStatus::Enum value);


/// Serializes into a string.
inline std::string toStr(QuoteStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    QuoteStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    QuoteStatus::Enum value)
{
    toStr(
        str,
        static_cast<QuoteStatus::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    QuoteStatusResponseTo::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    QuoteStatusResponseTo::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    QuoteStatusResponseTo::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    QuoteStatusResponseTo::Enum value)
{
    toStr(
        str,
        static_cast<QuoteStatusResponseTo::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    QuoteCancelType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    QuoteCancelType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    QuoteCancelType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    QuoteCancelType::Enum value)
{
    toStr(
        str,
        static_cast<QuoteCancelType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    PosType::Enum value);


/// Serializes into a string.
inline std::string toStr(PosType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PosType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PosType::Enum value)
{
    toStr(
        str,
        static_cast<PosType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    MassActionScope::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    MassActionScope::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MassActionScope::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MassActionScope::Enum value)
{
    toStr(
        str,
        static_cast<MassActionScope::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    MassActionType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    MassActionType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MassActionType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MassActionType::Enum value)
{
    toStr(
        str,
        static_cast<MassActionType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    MassActionResponse::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    MassActionResponse::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MassActionResponse::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MassActionResponse::Enum value)
{
    toStr(
        str,
        static_cast<MassActionResponse::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    MassActionRejectReason::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    MassActionRejectReason::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MassActionRejectReason::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MassActionRejectReason::Enum value)
{
    toStr(
        str,
        static_cast<MassActionRejectReason::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    SecurityResponseType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityResponseType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityResponseType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityResponseType::Enum value)
{
    toStr(
        str,
        static_cast<SecurityResponseType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    PosMaintStatus::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    PosMaintStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PosMaintStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PosMaintStatus::Enum value)
{
    toStr(
        str,
        static_cast<PosMaintStatus::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    ExecuteUnderlyingTrade::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    ExecuteUnderlyingTrade::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ExecuteUnderlyingTrade::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ExecuteUnderlyingTrade::Enum value)
{
    toStr(
        str,
        static_cast<ExecuteUnderlyingTrade::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    PosTransType::Enum value);


/// Serializes into a string.
inline std::string toStr(PosTransType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PosTransType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PosTransType::Enum value)
{
    toStr(
        str,
        static_cast<PosTransType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    PosMaintAction::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    PosMaintAction::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PosMaintAction::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PosMaintAction::Enum value)
{
    toStr(
        str,
        static_cast<PosMaintAction::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    SettlType::Enum value);


/// Serializes into a string.
inline std::string toStr(SettlType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SettlType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SettlType::Enum value)
{
    toStr(
        str,
        static_cast<SettlType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    SelfTradePreventionInstruction::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SelfTradePreventionInstruction::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SelfTradePreventionInstruction::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SelfTradePreventionInstruction::Enum value)
{
    toStr(
        str,
        static_cast<SelfTradePreventionInstruction::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    TimeUnit::Enum value);


/// Serializes into a string.
inline std::string toStr(TimeUnit::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TimeUnit::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TimeUnit::Enum value)
{
    toStr(
        str,
        static_cast<TimeUnit::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    MessageType::Enum value);


/// Serializes into a string.
inline std::string toStr(MessageType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MessageType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MessageType::Enum value)
{
    toStr(
        str,
        static_cast<MessageType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    FlowType::Enum value);


/// Serializes into a string.
inline std::string toStr(FlowType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    FlowType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    FlowType::Enum value)
{
    toStr(
        str,
        static_cast<FlowType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    NegotiationRejectCode::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    NegotiationRejectCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    NegotiationRejectCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    NegotiationRejectCode::Enum value)
{
    toStr(
        str,
        static_cast<NegotiationRejectCode::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    EstablishRejectCode::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    EstablishRejectCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    EstablishRejectCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    EstablishRejectCode::Enum value)
{
    toStr(
        str,
        static_cast<EstablishRejectCode::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    TerminationCode::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    TerminationCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TerminationCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TerminationCode::Enum value)
{
    toStr(
        str,
        static_cast<TerminationCode::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    RetransmitRejectCode::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    RetransmitRejectCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    RetransmitRejectCode::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    RetransmitRejectCode::Enum value)
{
    toStr(
        str,
        static_cast<RetransmitRejectCode::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    CancelOnDisconnectType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    CancelOnDisconnectType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    CancelOnDisconnectType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    CancelOnDisconnectType::Enum value)
{
    toStr(
        str,
        static_cast<CancelOnDisconnectType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    Side::Enum value);


/// Serializes into a string.
inline std::string toStr(Side::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    Side::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    Side::Enum value)
{
    toStr(
        str,
        static_cast<Side::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    TimeInForce::Enum value);


/// Serializes into a string.
inline std::string toStr(TimeInForce::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TimeInForce::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TimeInForce::Enum value)
{
    toStr(
        str,
        static_cast<TimeInForce::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    SimpleTimeInForce::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SimpleTimeInForce::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SimpleTimeInForce::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SimpleTimeInForce::Enum value)
{
    toStr(
        str,
        static_cast<SimpleTimeInForce::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    OrdType::Enum value);


/// Serializes into a string.
inline std::string toStr(OrdType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    OrdType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    OrdType::Enum value)
{
    toStr(
        str,
        static_cast<OrdType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    SimpleOrdType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SimpleOrdType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SimpleOrdType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SimpleOrdType::Enum value)
{
    toStr(
        str,
        static_cast<SimpleOrdType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    RoutingInstruction::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    RoutingInstruction::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    RoutingInstruction::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    RoutingInstruction::Enum value)
{
    toStr(
        str,
        static_cast<RoutingInstruction::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    ExecType::Enum value);


/// Serializes into a string.
inline std::string toStr(ExecType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ExecType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ExecType::Enum value)
{
    toStr(
        str,
        static_cast<ExecType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    OrdStatus::Enum value);


/// Serializes into a string.
inline std::string toStr(OrdStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    OrdStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    OrdStatus::Enum value)
{
    toStr(
        str,
        static_cast<OrdStatus::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    ExecRestatementReasonValidForSingleCancel::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    ExecRestatementReasonValidForSingleCancel::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ExecRestatementReasonValidForSingleCancel::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ExecRestatementReasonValidForSingleCancel::Enum value)
{
    toStr(
        str,
        static_cast<ExecRestatementReasonValidForSingleCancel::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    ExecRestatementReasonValidForMassCancel::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    ExecRestatementReasonValidForMassCancel::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ExecRestatementReasonValidForMassCancel::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ExecRestatementReasonValidForMassCancel::Enum value)
{
    toStr(
        str,
        static_cast<ExecRestatementReasonValidForMassCancel::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    ExecRestatementReason::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    ExecRestatementReason::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    ExecRestatementReason::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    ExecRestatementReason::Enum value)
{
    toStr(
        str,
        static_cast<ExecRestatementReason::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    MultiLegReportingType::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    MultiLegReportingType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    MultiLegReportingType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    MultiLegReportingType::Enum value)
{
    toStr(
        str,
        static_cast<MultiLegReportingType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    OrderCategory::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    OrderCategory::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    OrderCategory::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    OrderCategory::Enum value)
{
    toStr(
        str,
        static_cast<OrderCategory::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    AccountType::Enum value);


/// Serializes into a string.
inline std::string toStr(AccountType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    AccountType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    AccountType::Enum value)
{
    toStr(
        str,
        static_cast<AccountType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    CxlRejResponseTo::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    CxlRejResponseTo::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    CxlRejResponseTo::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    CxlRejResponseTo::Enum value)
{
    toStr(
        str,
        static_cast<CxlRejResponseTo::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    PossResend::Enum value);


/// Serializes into a string.
inline std::string toStr(PossResend::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    PossResend::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    PossResend::Enum value)
{
    toStr(
        str,
        static_cast<PossResend::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    SecurityIDSource::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityIDSource::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityIDSource::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityIDSource::Enum value)
{
    toStr(
        str,
        static_cast<SecurityIDSource::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    CrossedIndicator::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    CrossedIndicator::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    CrossedIndicator::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    CrossedIndicator::Enum value)
{
    toStr(
        str,
        static_cast<CrossedIndicator::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    TradingSessionID::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    TradingSessionID::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TradingSessionID::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TradingSessionID::Enum value)
{
    toStr(
        str,
        static_cast<TradingSessionID::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    TradingSessionSubID::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    TradingSessionSubID::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    TradingSessionSubID::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    TradingSessionSubID::Enum value)
{
    toStr(
        str,
        static_cast<TradingSessionSubID::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    SecurityTradingStatus::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    SecurityTradingStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    SecurityTradingStatus::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    SecurityTradingStatus::Enum value)
{
    toStr(
        str,
        static_cast<SecurityTradingStatus::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    CrossType::Enum value);


/// Serializes into a string.
inline std::string toStr(CrossType::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    CrossType::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    CrossType::Enum value)
{
    toStr(
        str,
        static_cast<CrossType::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    CrossPrioritization::Enum value);


/// Serializes into a string.
inline
std::string
toStr(
    CrossPrioritization::Enum value)
{
    std::string str;

    toStr(str, value);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    CrossPrioritization::Enum value)
{
    std::string str;

    toStr(str, value);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    CrossPrioritization::Enum value)
{
    toStr(
        str,
        static_cast<CrossPrioritization::Base>(value));
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    EventIndicator set);


/// Serializes into a string.
inline std::string toStr(EventIndicator set)
{
    std::string str;

    toStr(str, set);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    EventIndicator set)
{
    std::string str;

    toStr(str, set);

    return stream << str;
}

/// Serializes the object into FIX presentation.
inline
void
toFix(
    std::string& str,
    EventIndicator set)
{
    toStr(str, set.bits());
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const GroupSizeEncoding& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const GroupSizeEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const GroupSizeEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const PriceOffsetOptional& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const PriceOffsetOptional& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const PriceOffsetOptional& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Percentage8Optional& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const Percentage8Optional& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const Percentage8Optional& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const RatioQty& obj);


/// Serializes into a string.
inline std::string toStr(const RatioQty& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const RatioQty& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const UTCTimestampNanos& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const UTCTimestampNanos& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const UTCTimestampNanos& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const UTCTimestampNanosOptional& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const UTCTimestampNanosOptional& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const UTCTimestampNanosOptional& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const DeltaInMillis& obj);


/// Serializes into a string.
inline std::string toStr(const DeltaInMillis& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const DeltaInMillis& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const CredentialsEncoding& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const CredentialsEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const CredentialsEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const MemoEncoding& obj);


/// Serializes into a string.
inline std::string toStr(const MemoEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const MemoEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const TextEncoding& obj);


/// Serializes into a string.
inline std::string toStr(const TextEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const TextEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const DeskIDEncoding& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const DeskIDEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const DeskIDEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const ClientAppEncoding& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ClientAppEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const ClientAppEncoding& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const CustodianInfo& obj);


/// Serializes into a string.
inline std::string toStr(const CustodianInfo& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const CustodianInfo& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const InboundBusinessHeader& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const InboundBusinessHeader& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const InboundBusinessHeader& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const OutboundBusinessHeader& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const OutboundBusinessHeader& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const OutboundBusinessHeader& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const BidirectionalBusinessHeader& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const BidirectionalBusinessHeader& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const BidirectionalBusinessHeader& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const InvestorID& obj);


/// Serializes into a string.
inline std::string toStr(const InvestorID& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const InvestorID& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const ImpliedEventID& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ImpliedEventID& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const ImpliedEventID& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Version& obj);


/// Serializes into a string.
inline std::string toStr(const Version& obj)
{
    std::string str;

    toStr(str, obj);

    return str;
}

/// Serializes into a stream.
inline
std::ostream&
operator<<(
    std::ostream& stream,
    const Version& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}


inline std::string EventIndicator::toString() const
{
    return toStr(*this);
}

inline std::string GroupSizeEncoding::toString() const
{
    return toStr(*this);
}

inline std::string UTCTimestampNanos::toString() const
{
    return toStr(*this);
}

inline std::string UTCTimestampNanosOptional::toString() const
{
    return toStr(*this);
}

inline std::string DeltaInMillis::toString() const
{
    return toStr(*this);
}

inline std::string CredentialsEncoding::toString() const
{
    return toStr(*this);
}

inline std::string MemoEncoding::toString() const
{
    return toStr(*this);
}

inline std::string TextEncoding::toString() const
{
    return toStr(*this);
}

inline std::string DeskIDEncoding::toString() const
{
    return toStr(*this);
}

inline std::string ClientAppEncoding::toString() const
{
    return toStr(*this);
}

inline std::string CustodianInfo::toString() const
{
    return toStr(*this);
}

inline std::string InboundBusinessHeader::toString() const
{
    return toStr(*this);
}

inline std::string OutboundBusinessHeader::toString() const
{
    return toStr(*this);
}

inline std::string BidirectionalBusinessHeader::toString() const
{
    return toStr(*this);
}

inline std::string InvestorID::toString() const
{
    return toStr(*this);
}

inline std::string ImpliedEventID::toString() const
{
    return toStr(*this);
}

inline std::string Version::toString() const
{
    return toStr(*this);
}

inline std::string Boolean::toString(Boolean::Enum value)
{
    return toStr(value);
}

inline
std::string
AllocTransType::toString(
    AllocTransType::Enum value)
{
    return toStr(value);
}

inline
std::string
AllocReportType::toString(
    AllocReportType::Enum value)
{
    return toStr(value);
}

inline std::string AllocType::toString(AllocType::Enum value)
{
    return toStr(value);
}

inline
std::string
AllocNoOrdersType::toString(
    AllocNoOrdersType::Enum value)
{
    return toStr(value);
}

inline std::string AllocStatus::toString(AllocStatus::Enum value)
{
    return toStr(value);
}

inline std::string QuoteStatus::toString(QuoteStatus::Enum value)
{
    return toStr(value);
}

inline
std::string
QuoteStatusResponseTo::toString(
    QuoteStatusResponseTo::Enum value)
{
    return toStr(value);
}

inline
std::string
QuoteCancelType::toString(
    QuoteCancelType::Enum value)
{
    return toStr(value);
}

inline std::string PosType::toString(PosType::Enum value)
{
    return toStr(value);
}

inline
std::string
MassActionScope::toString(
    MassActionScope::Enum value)
{
    return toStr(value);
}

inline
std::string
MassActionType::toString(
    MassActionType::Enum value)
{
    return toStr(value);
}

inline
std::string
MassActionResponse::toString(
    MassActionResponse::Enum value)
{
    return toStr(value);
}

inline
std::string
MassActionRejectReason::toString(
    MassActionRejectReason::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityResponseType::toString(
    SecurityResponseType::Enum value)
{
    return toStr(value);
}

inline
std::string
PosMaintStatus::toString(
    PosMaintStatus::Enum value)
{
    return toStr(value);
}

inline
std::string
ExecuteUnderlyingTrade::toString(
    ExecuteUnderlyingTrade::Enum value)
{
    return toStr(value);
}

inline std::string PosTransType::toString(PosTransType::Enum value)
{
    return toStr(value);
}

inline
std::string
PosMaintAction::toString(
    PosMaintAction::Enum value)
{
    return toStr(value);
}

inline std::string SettlType::toString(SettlType::Enum value)
{
    return toStr(value);
}

inline
std::string
SelfTradePreventionInstruction::toString(
    SelfTradePreventionInstruction::Enum value)
{
    return toStr(value);
}

inline std::string TimeUnit::toString(TimeUnit::Enum value)
{
    return toStr(value);
}

inline std::string MessageType::toString(MessageType::Enum value)
{
    return toStr(value);
}

inline std::string FlowType::toString(FlowType::Enum value)
{
    return toStr(value);
}

inline
std::string
NegotiationRejectCode::toString(
    NegotiationRejectCode::Enum value)
{
    return toStr(value);
}

inline
std::string
EstablishRejectCode::toString(
    EstablishRejectCode::Enum value)
{
    return toStr(value);
}

inline
std::string
TerminationCode::toString(
    TerminationCode::Enum value)
{
    return toStr(value);
}

inline
std::string
RetransmitRejectCode::toString(
    RetransmitRejectCode::Enum value)
{
    return toStr(value);
}

inline
std::string
CancelOnDisconnectType::toString(
    CancelOnDisconnectType::Enum value)
{
    return toStr(value);
}

inline std::string Side::toString(Side::Enum value)
{
    return toStr(value);
}

inline std::string TimeInForce::toString(TimeInForce::Enum value)
{
    return toStr(value);
}

inline
std::string
SimpleTimeInForce::toString(
    SimpleTimeInForce::Enum value)
{
    return toStr(value);
}

inline std::string OrdType::toString(OrdType::Enum value)
{
    return toStr(value);
}

inline
std::string
SimpleOrdType::toString(
    SimpleOrdType::Enum value)
{
    return toStr(value);
}

inline
std::string
RoutingInstruction::toString(
    RoutingInstruction::Enum value)
{
    return toStr(value);
}

inline std::string ExecType::toString(ExecType::Enum value)
{
    return toStr(value);
}

inline std::string OrdStatus::toString(OrdStatus::Enum value)
{
    return toStr(value);
}

inline
std::string
ExecRestatementReasonValidForSingleCancel::toString(
    ExecRestatementReasonValidForSingleCancel::Enum value)
{
    return toStr(value);
}

inline
std::string
ExecRestatementReasonValidForMassCancel::toString(
    ExecRestatementReasonValidForMassCancel::Enum value)
{
    return toStr(value);
}

inline
std::string
ExecRestatementReason::toString(
    ExecRestatementReason::Enum value)
{
    return toStr(value);
}

inline
std::string
MultiLegReportingType::toString(
    MultiLegReportingType::Enum value)
{
    return toStr(value);
}

inline
std::string
OrderCategory::toString(
    OrderCategory::Enum value)
{
    return toStr(value);
}

inline std::string AccountType::toString(AccountType::Enum value)
{
    return toStr(value);
}

inline
std::string
CxlRejResponseTo::toString(
    CxlRejResponseTo::Enum value)
{
    return toStr(value);
}

inline std::string PossResend::toString(PossResend::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityIDSource::toString(
    SecurityIDSource::Enum value)
{
    return toStr(value);
}

inline
std::string
CrossedIndicator::toString(
    CrossedIndicator::Enum value)
{
    return toStr(value);
}

inline
std::string
TradingSessionID::toString(
    TradingSessionID::Enum value)
{
    return toStr(value);
}

inline
std::string
TradingSessionSubID::toString(
    TradingSessionSubID::Enum value)
{
    return toStr(value);
}

inline
std::string
SecurityTradingStatus::toString(
    SecurityTradingStatus::Enum value)
{
    return toStr(value);
}

inline std::string CrossType::toString(CrossType::Enum value)
{
    return toStr(value);
}

inline
std::string
CrossPrioritization::toString(
    CrossPrioritization::Enum value)
{
    return toStr(value);
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
