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

#include <OnixS/B3/BOE/messaging/Messages.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Casts SBE-encoded message to a given type.
template
    <
        class Message
    >
inline
ONIXS_B3_BOE_NODISCARD
ONIXS_B3_BOE_PURE
Message
typify(
    const SbeMessage& message)
{
    return Message(message);
}

/// Casts a given binary message according to template/type
/// information and processes the cast messages by a given processor.
///
/// Returned value indicates whether message type was successfully
/// recognized and pushed to the processor for further processing. Unknown
/// messages aren't processed and thus false result is returned.
template
<
    class Processor
>
inline
ONIXS_B3_BOE_NODISCARD
bool
processTypified(
    SbeMessage binary,
    const Processor& processor)
{
    switch (binary.templateId())
    {
    case Negotiate1::TemplateId:
    {
        processor(
            typify
            <Negotiate1>
            (binary));

        return true;
    }

    case NegotiateResponse2::TemplateId:
    {
        processor(
            typify
            <NegotiateResponse2>
            (binary));

        return true;
    }

    case NegotiateReject3::TemplateId:
    {
        processor(
            typify
            <NegotiateReject3>
            (binary));

        return true;
    }

    case Establish4::TemplateId:
    {
        processor(
            typify
            <Establish4>
            (binary));

        return true;
    }

    case EstablishAck5::TemplateId:
    {
        processor(
            typify
            <EstablishAck5>
            (binary));

        return true;
    }

    case EstablishReject6::TemplateId:
    {
        processor(
            typify
            <EstablishReject6>
            (binary));

        return true;
    }

    case Terminate7::TemplateId:
    {
        processor(
            typify
            <Terminate7>
            (binary));

        return true;
    }

    case NotApplied8::TemplateId:
    {
        processor(
            typify
            <NotApplied8>
            (binary));

        return true;
    }

    case Sequence9::TemplateId:
    {
        processor(
            typify
            <Sequence9>
            (binary));

        return true;
    }

    case RetransmitRequest12::TemplateId:
    {
        processor(
            typify
            <RetransmitRequest12>
            (binary));

        return true;
    }

    case Retransmission13::TemplateId:
    {
        processor(
            typify
            <Retransmission13>
            (binary));

        return true;
    }

    case RetransmitReject14::TemplateId:
    {
        processor(
            typify
            <RetransmitReject14>
            (binary));

        return true;
    }

    case SimpleNewOrder100::TemplateId:
    {
        processor(
            typify
            <SimpleNewOrder100>
            (binary));

        return true;
    }

    case SimpleModifyOrder101::TemplateId:
    {
        processor(
            typify
            <SimpleModifyOrder101>
            (binary));

        return true;
    }

    case NewOrderSingle102::TemplateId:
    {
        processor(
            typify
            <NewOrderSingle102>
            (binary));

        return true;
    }

    case OrderCancelReplaceRequest104::TemplateId:
    {
        processor(
            typify
            <OrderCancelReplaceRequest104>
            (binary));

        return true;
    }

    case OrderCancelRequest105::TemplateId:
    {
        processor(
            typify
            <OrderCancelRequest105>
            (binary));

        return true;
    }

    case NewOrderCross106::TemplateId:
    {
        processor(
            typify
            <NewOrderCross106>
            (binary));

        return true;
    }

    case ExecutionReportNew200::TemplateId:
    {
        processor(
            typify
            <ExecutionReportNew200>
            (binary));

        return true;
    }

    case ExecutionReportModify201::TemplateId:
    {
        processor(
            typify
            <ExecutionReportModify201>
            (binary));

        return true;
    }

    case ExecutionReportCancel202::TemplateId:
    {
        processor(
            typify
            <ExecutionReportCancel202>
            (binary));

        return true;
    }

    case ExecutionReportTrade203::TemplateId:
    {
        processor(
            typify
            <ExecutionReportTrade203>
            (binary));

        return true;
    }

    case ExecutionReportReject204::TemplateId:
    {
        processor(
            typify
            <ExecutionReportReject204>
            (binary));

        return true;
    }

    case ExecutionReportForward205::TemplateId:
    {
        processor(
            typify
            <ExecutionReportForward205>
            (binary));

        return true;
    }

    case BusinessMessageReject206::TemplateId:
    {
        processor(
            typify
            <BusinessMessageReject206>
            (binary));

        return true;
    }

    case SecurityDefinitionRequest300::TemplateId:
    {
        processor(
            typify
            <SecurityDefinitionRequest300>
            (binary));

        return true;
    }

    case SecurityDefinitionResponse301::TemplateId:
    {
        processor(
            typify
            <SecurityDefinitionResponse301>
            (binary));

        return true;
    }

    case QuoteRequest401::TemplateId:
    {
        processor(
            typify
            <QuoteRequest401>
            (binary));

        return true;
    }

    case QuoteStatusReport402::TemplateId:
    {
        processor(
            typify
            <QuoteStatusReport402>
            (binary));

        return true;
    }

    case Quote403::TemplateId:
    {
        processor(
            typify
            <Quote403>
            (binary));

        return true;
    }

    case QuoteCancel404::TemplateId:
    {
        processor(
            typify
            <QuoteCancel404>
            (binary));

        return true;
    }

    case QuoteRequestReject405::TemplateId:
    {
        processor(
            typify
            <QuoteRequestReject405>
            (binary));

        return true;
    }

    case PositionMaintenanceCancelRequest501::TemplateId:
    {
        processor(
            typify
            <PositionMaintenanceCancelRequest501>
            (binary));

        return true;
    }

    case PositionMaintenanceRequest502::TemplateId:
    {
        processor(
            typify
            <PositionMaintenanceRequest502>
            (binary));

        return true;
    }

    case PositionMaintenanceReport503::TemplateId:
    {
        processor(
            typify
            <PositionMaintenanceReport503>
            (binary));

        return true;
    }

    case AllocationInstruction601::TemplateId:
    {
        processor(
            typify
            <AllocationInstruction601>
            (binary));

        return true;
    }

    case AllocationReport602::TemplateId:
    {
        processor(
            typify
            <AllocationReport602>
            (binary));

        return true;
    }

    case OrderMassActionRequest701::TemplateId:
    {
        processor(
            typify
            <OrderMassActionRequest701>
            (binary));

        return true;
    }

    case OrderMassActionReport702::TemplateId:
    {
        processor(
            typify
            <OrderMassActionReport702>
            (binary));

        return true;
    }

    default:
        return false;
    }
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
