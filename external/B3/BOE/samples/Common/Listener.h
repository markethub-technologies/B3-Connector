/*
 * Copyright Onix Solutions Limited [OnixS]. All rights reserved.
 *
 * This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
 * and international copyright treaties.
 *
 * Access to and use of the software is governed by the terms of the applicable ONIXS Software
 * Services Agreement (the Agreement) and Customer end user license agreements granting
 * a non-assignable, non-transferable and non-exclusive license to use the software
 * for it's own data processing purposes under the terms defined in the Agreement.
 *
 * Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
 * of this source code or associated reference material to any other location for further reproduction
 * or redistribution, and any amendments to this copyright notice, are expressly prohibited.
 *
 * Any reproduction or redistribution for sale or hiring of the Software not in accordance with
 * the terms of the Agreement is a violation of copyright law.
 */

#pragma once

#include <OnixS/B3/BOE/SessionListener.h>

#include <functional>

namespace Samples
{
    using namespace OnixS::B3::BOE;
    using namespace OnixS::B3::BOE::Messaging;

    struct MessagePrinter
    {
        template <typename MessageType>
        void operator()(const MessageType& msg) const
        {
            std::clog << msg << std::endl;
        }

        static void printMsg(const Messaging::SbeMessage msg)
        {
            if (!processTypified(msg, MessagePrinter()))
                std::clog << "Unknown message type";
        }
    };

class Listener : public SessionListener
{
public:

    ~Listener() ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    void onMessageSending(char* bytes, size_t size, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nOutbound message:\n";
        MessagePrinter::printMsg(SbeMessage(bytes, static_cast<Messaging::MessageSize>(size)));
    }

    void onBusinessMessageReject(const BusinessMessageReject206& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl << "\tReject reason: " << msg.businessRejectReason() << std::endl;
    }

    void onNegotiateResponse(const NegotiateResponse2& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onNegotiateReject(const NegotiateReject3& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onEstablishAck(const EstablishAck5& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onEstablishReject(const EstablishReject6& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onSequence(const Sequence9& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n"
             << msg << std::endl;
    }

    void onTerminate(const Terminate7& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onRetransmitReject(const RetransmitReject14& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onRetransmission(const Retransmission13& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onNotApplied(const NotApplied8& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportNew(const ExecutionReportNew200& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportModify(const ExecutionReportModify201& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportCancel(const ExecutionReportCancel202& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    /*void onExecutionReportStatus(const ExecutionReportStatus532& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportTradeOutright(const ExecutionReportTradeOutright525& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportTradeSpread(const ExecutionReportTradeSpread526& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportTradeSpreadLeg(const ExecutionReportTradeSpreadLeg527& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportElimination(const ExecutionReportElimination524& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }*/

    void onExecutionReportReject(const ExecutionReportReject204& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    /*void onExecutionReportTradeAddendumOutright(const ExecutionReportTradeAddendumOutright548& msg, Session* ) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportTradeAddendumSpread(const ExecutionReportTradeAddendumSpread549& msg, Session* ) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportTradeAddendumSpreadLeg(const ExecutionReportTradeAddendumSpreadLeg550& msg, Session* ) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onOrderCancelReject(const OrderCancelReject535& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onOrderCancelReplaceReject(const OrderCancelReplaceReject536& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }*/

    void onSecurityDefinitionResponse(const SecurityDefinitionResponse301& msg, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    /*void onMassQuoteAck(const MassQuoteAck545& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onRequestForQuoteAck(const RequestForQuoteAck546& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onQuoteCancelAck(const QuoteCancelAck563& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onOrderMassActionReport(const OrderMassActionReport562& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onPartyDetailsDefinitionRequestAck(const PartyDetailsDefinitionRequestAck519& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onPartyDetailsListReport(const PartyDetailsListReport538& msg, Session*) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportPendingCancel(const Messaging::ExecutionReportPendingCancel564& msg, Session *) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }

    void onExecutionReportPendingReplace(const Messaging::ExecutionReportPendingReplace565& msg, Session *) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog << "\nReceived:\n" << msg << std::endl;
    }*/

    void onStateChange(SessionStateId::Enum newState, SessionStateId::Enum prevState, Session* /*sn*/) ONIXS_B3_BOE_OVERRIDE
    {
        std::clog
            << "\nSession's state is changed, prevState="
            << SessionStateId::toString(prevState)
            << ", newState="
            << SessionStateId::toString(newState)
            << std::endl;
    }

    void onError(
        SessionErrorReason::Enum /*reason*/, const std::string& description, Session* /*sn*/, Messaging::SbeMessage msg) ONIXS_B3_BOE_OVERRIDE
    {
        std::cerr << "\nSession-level error: " << description;

        if(msg.valid())
        {
            std::cerr << ",\nCaused by the message: ";
            MessagePrinter::printMsg(msg);
        }

        std::cerr << std::endl;
    }

    void onWarning(
        SessionWarningReason::Enum /*reason*/, const std::string& description, Session* /*sn*/, Messaging::SbeMessage msg) ONIXS_B3_BOE_OVERRIDE
    {
        std::cerr << "\nSession-level warning: " << description;

        if(msg.valid())
        {
            std::cerr << ",\nCaused by the message: ";
            MessagePrinter::printMsg(msg);
        }

        std::cerr << std::endl;
    }
};

}
