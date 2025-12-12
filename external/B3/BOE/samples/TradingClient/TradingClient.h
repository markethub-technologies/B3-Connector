/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable OnixS Software
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

//! [TradingClientSampleH]
#include <OnixS/B3/BOE/Session.h>

#include "MessageFactory.h"
#include "Settings.h"
#include "CUI.h"
#include "Order.h"
#include "Book.h"

namespace Samples
{
// Sample console-based trading client which sends orders to counterparty
// allows modifying and canceling them. It also handles all other issues
// like handling messages from the counterparty.
class TradingClient ONIXS_B3_BOE_FINAL : private SessionListener
{
public:
    // Initializes the client with a given behavior.
    explicit TradingClient(const Settings& settings);

    // Performs trading by processing user requests.
    void run();

private:
    // Set of control parameters that affect trading.
    const Settings& settings_;

    // Primary BOE session with the counterparty.
    PtrTraits<Session>::UniquePtr session_;

    bool connected_;

    // Store of orders sent to the counterparty.
    Book<Order> orderBook_;
    typedef Book<Order>::EntryList OrderList;

    // Creates SBE messages to be sent to the counterparty.
    MessageFactory messageFactory_;

    // UI-specific part of the trading client.
    typedef CUI::Menu<TradingClient> Menu;

    Menu menu_;

    void constructMenu();

    void createSessions();

    void processSendSequence(CUI::CommandExecutionStatus*);
    void processExit(CUI::CommandExecutionStatus*);
    void processOrderCancelRequest(CUI::CommandExecutionStatus*);
    void processOrderMassActionRequest(CUI::CommandExecutionStatus*);
    void processOrderModifyRequest(CUI::CommandExecutionStatus*);
    void processSendNewOrder(CUI::CommandExecutionStatus*);
    void processViewOrders(CUI::CommandExecutionStatus*);
    void processViewSessions(CUI::CommandExecutionStatus*);
    void processSecurityDefinitionRequest(CUI::CommandExecutionStatus*);
    void processCrossOrder(CUI::CommandExecutionStatus*);
    void resetSequenceNumbers(CUI::CommandExecutionStatus*);
    void processEstablishConnection(CUI::CommandExecutionStatus*);
    void processDisconnect(CUI::CommandExecutionStatus*);

    bool checkSessionConnected();

    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    void send(Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &msg);

    Order* findByOrderId(ClOrdID clOrdId);
    Order newOrder();

    // Listener part.
    void onMessageSending(char* bytes, size_t size, Session*) ONIXS_B3_BOE_OVERRIDE;
    void onNegotiateResponse(const NegotiateResponse2 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onNegotiateReject(const NegotiateReject3 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onEstablishAck(const EstablishAck5 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onEstablishReject(const EstablishReject6 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onSequence(const Sequence9 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onTerminate(const Terminate7 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onRetransmitReject(const Messaging::RetransmitReject14 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onRetransmission(const Messaging::Retransmission13 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onNotApplied(const Messaging::NotApplied8 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onBusinessMessageReject(const BusinessMessageReject206 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onExecutionReportNew(const ExecutionReportNew200 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onExecutionReportModify(const ExecutionReportModify201 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onExecutionReportCancel(const ExecutionReportCancel202 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onExecutionReportTrade(const ExecutionReportTrade203 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onExecutionReportReject(const ExecutionReportReject204 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onSecurityDefinitionResponse(const SecurityDefinitionResponse301 & msg, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onOrderMassActionReport(const OrderMassActionReport702& msg, Session* sn) ONIXS_B3_BOE_OVERRIDE;
    void onStateChange(SessionStateId::Enum newState, SessionStateId::Enum prevState, Session * sn) ONIXS_B3_BOE_OVERRIDE;
    void onError(SessionErrorReason::Enum reason, const std::string & description, Session * sn, Messaging::SbeMessage) ONIXS_B3_BOE_OVERRIDE;
    void onWarning(SessionWarningReason::Enum reason, const std::string & description, Session * sn, Messaging::SbeMessage) ONIXS_B3_BOE_OVERRIDE;
};

}
//! [TradingClientSampleH]
