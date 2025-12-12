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

#include <OnixS/B3/BOE/messaging/Messages.h>


ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

// Market Data Serialization.

/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Negotiate1& obj);


/// Serializes into a string.
inline std::string toStr(const Negotiate1& obj)
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
    const Negotiate1& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Negotiate1::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const Negotiate1& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const NegotiateResponse2& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const NegotiateResponse2& obj)
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
    const NegotiateResponse2& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string NegotiateResponse2::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const NegotiateResponse2& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const NegotiateReject3& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const NegotiateReject3& obj)
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
    const NegotiateReject3& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string NegotiateReject3::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const NegotiateReject3& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Establish4& obj);


/// Serializes into a string.
inline std::string toStr(const Establish4& obj)
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
    const Establish4& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Establish4::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const Establish4& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const EstablishAck5& obj);


/// Serializes into a string.
inline std::string toStr(const EstablishAck5& obj)
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
    const EstablishAck5& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string EstablishAck5::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const EstablishAck5& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const EstablishReject6& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const EstablishReject6& obj)
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
    const EstablishReject6& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string EstablishReject6::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const EstablishReject6& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Terminate7& obj);


/// Serializes into a string.
inline std::string toStr(const Terminate7& obj)
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
    const Terminate7& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Terminate7::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const Terminate7& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const NotApplied8& obj);


/// Serializes into a string.
inline std::string toStr(const NotApplied8& obj)
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
    const NotApplied8& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string NotApplied8::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const NotApplied8& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Sequence9& obj);


/// Serializes into a string.
inline std::string toStr(const Sequence9& obj)
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
    const Sequence9& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Sequence9::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const Sequence9& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const RetransmitRequest12& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const RetransmitRequest12& obj)
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
    const RetransmitRequest12& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string RetransmitRequest12::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const RetransmitRequest12& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Retransmission13& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const Retransmission13& obj)
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
    const Retransmission13& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Retransmission13::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const Retransmission13& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const RetransmitReject14& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const RetransmitReject14& obj)
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
    const RetransmitReject14& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string RetransmitReject14::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const RetransmitReject14& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const SimpleNewOrder100& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SimpleNewOrder100& obj)
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
    const SimpleNewOrder100& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SimpleNewOrder100::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const SimpleNewOrder100& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const SimpleModifyOrder101& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SimpleModifyOrder101& obj)
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
    const SimpleModifyOrder101& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SimpleModifyOrder101::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const SimpleModifyOrder101& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const NewOrderSingle102& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const NewOrderSingle102& obj)
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
    const NewOrderSingle102& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string NewOrderSingle102::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const NewOrderSingle102& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const OrderCancelReplaceRequest104& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const OrderCancelReplaceRequest104& obj)
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
    const OrderCancelReplaceRequest104& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string OrderCancelReplaceRequest104::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const OrderCancelReplaceRequest104& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const OrderCancelRequest105& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const OrderCancelRequest105& obj)
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
    const OrderCancelRequest105& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string OrderCancelRequest105::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const OrderCancelRequest105& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const NewOrderCross106& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const NewOrderCross106& obj)
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
    const NewOrderCross106& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string NewOrderCross106::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const NewOrderCross106& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const NewOrderCross106::SidesEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const NewOrderCross106::SidesEntry& obj)
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
    const NewOrderCross106::SidesEntry& obj)
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
    const ExecutionReportNew200& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionReportNew200& obj)
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
    const ExecutionReportNew200& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionReportNew200::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionReportNew200& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const ExecutionReportModify201& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionReportModify201& obj)
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
    const ExecutionReportModify201& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionReportModify201::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionReportModify201& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const ExecutionReportCancel202& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionReportCancel202& obj)
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
    const ExecutionReportCancel202& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionReportCancel202::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionReportCancel202& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const ExecutionReportTrade203& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionReportTrade203& obj)
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
    const ExecutionReportTrade203& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionReportTrade203::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionReportTrade203& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const ExecutionReportReject204& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionReportReject204& obj)
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
    const ExecutionReportReject204& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionReportReject204::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionReportReject204& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const ExecutionReportForward205& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const ExecutionReportForward205& obj)
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
    const ExecutionReportForward205& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string ExecutionReportForward205::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const ExecutionReportForward205& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const BusinessMessageReject206& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const BusinessMessageReject206& obj)
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
    const BusinessMessageReject206& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string BusinessMessageReject206::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const BusinessMessageReject206& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const SecurityDefinitionRequest300& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SecurityDefinitionRequest300& obj)
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
    const SecurityDefinitionRequest300& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SecurityDefinitionRequest300::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const SecurityDefinitionRequest300& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const SecurityDefinitionRequest300::LegsEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const SecurityDefinitionRequest300::LegsEntry& obj)
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
    const SecurityDefinitionRequest300::LegsEntry& obj)
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
    const SecurityDefinitionResponse301& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const SecurityDefinitionResponse301& obj)
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
    const SecurityDefinitionResponse301& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string SecurityDefinitionResponse301::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const SecurityDefinitionResponse301& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const QuoteRequest401& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const QuoteRequest401& obj)
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
    const QuoteRequest401& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string QuoteRequest401::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const QuoteRequest401& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const QuoteRequest401::SidesEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const QuoteRequest401::SidesEntry& obj)
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
    const QuoteRequest401::SidesEntry& obj)
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
    const QuoteStatusReport402& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const QuoteStatusReport402& obj)
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
    const QuoteStatusReport402& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string QuoteStatusReport402::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const QuoteStatusReport402& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const Quote403& obj);


/// Serializes into a string.
inline std::string toStr(const Quote403& obj)
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
    const Quote403& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string Quote403::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const Quote403& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const QuoteCancel404& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const QuoteCancel404& obj)
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
    const QuoteCancel404& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string QuoteCancel404::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const QuoteCancel404& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const QuoteRequestReject405& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const QuoteRequestReject405& obj)
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
    const QuoteRequestReject405& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string QuoteRequestReject405::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const QuoteRequestReject405& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const QuoteRequestReject405::SidesEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const QuoteRequestReject405::SidesEntry& obj)
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
    const QuoteRequestReject405::SidesEntry& obj)
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
    const PositionMaintenanceCancelRequest501& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const PositionMaintenanceCancelRequest501& obj)
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
    const PositionMaintenanceCancelRequest501& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string PositionMaintenanceCancelRequest501::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const PositionMaintenanceCancelRequest501& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const PositionMaintenanceRequest502& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const PositionMaintenanceRequest502& obj)
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
    const PositionMaintenanceRequest502& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string PositionMaintenanceRequest502::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const PositionMaintenanceRequest502& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const PositionMaintenanceReport503& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const PositionMaintenanceReport503& obj)
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
    const PositionMaintenanceReport503& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string PositionMaintenanceReport503::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const PositionMaintenanceReport503& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const PositionMaintenanceReport503::PositionsEntry& obj);

/// Serializes into a string.
inline
std::string
toStr(
    const PositionMaintenanceReport503::PositionsEntry& obj)
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
    const PositionMaintenanceReport503::PositionsEntry& obj)
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
    const AllocationInstruction601& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const AllocationInstruction601& obj)
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
    const AllocationInstruction601& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string AllocationInstruction601::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const AllocationInstruction601& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const AllocationReport602& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const AllocationReport602& obj)
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
    const AllocationReport602& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string AllocationReport602::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const AllocationReport602& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const OrderMassActionRequest701& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const OrderMassActionRequest701& obj)
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
    const OrderMassActionRequest701& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string OrderMassActionRequest701::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const OrderMassActionRequest701& obj);


/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void
toStr(
    std::string& str,
    const OrderMassActionReport702& obj);


/// Serializes into a string.
inline
std::string
toStr(
    const OrderMassActionReport702& obj)
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
    const OrderMassActionReport702& obj)
{
    std::string str;

    toStr(str, obj);

    return stream << str;
}

inline std::string OrderMassActionReport702::toString() const
{
    return toStr(*this);
}
/// Serializes the object into FIX presentation.
ONIXS_B3_BOE_EXPORTED
void
toFix(
    std::string& str,
    const OrderMassActionReport702& obj);


ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
