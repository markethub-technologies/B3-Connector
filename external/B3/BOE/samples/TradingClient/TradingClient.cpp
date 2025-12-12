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

#include "stdafx.h"

//! [TradingClientSampleCpp]
#include "../Settings/Defaults.h"

#include "TradingClient.h"

namespace Samples
{
Session* createSession(
    const SessionSettings& settings, SessionListener* listener,
    UInt64 sessionVerId = Session::UndefinedSessionVerID, const std::string& customKey = "")
{
    return new Session(settings, listener, SessionStorageType::FileBased, ONIXS_B3_BOE_NULLPTR, sessionVerId, customKey);
}

template <typename MsgType>
bool isRetransmitted(const MsgType& msg)
{
    return msg.businessHeader().eventIndicator().possResend();
}

template <typename MsgType>
void setCommonFields(Order * order, const MsgType& msg)
{
    order->
         orderQty(msg.orderQty())
        .securityId(msg.securityId())
        .transactTime(msg.transactTime().time());
}

template <>
void setCommonFields<ExecutionReportReject204>(Order * order, const ExecutionReportReject204 & msg)
{
    QuantityOptional orderQty;

    if(msg.orderQty(orderQty))
        order->orderQty(orderQty);

    order->
        securityId(msg.securityId())
        .transactTime(msg.transactTime().time());
}

template <typename MsgType>
void setExpireDate(Order * order, const MsgType& msg)
{
    Timestamp expireDate;
    if(msg.expireDate(expireDate))
        order->expireDate_ = timestampToLocalMktDate(expireDate);
}

template <typename MsgType>
void setOrdStatus(OrdStatus::Enum & ordStatus, const MsgType& msg)
{
    ordStatus = msg.ordStatus();
}

using namespace CUI;

typedef ListViewer<Order> OrdersViewer;

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
void TradingClient::send(Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &msg)
{
    if (!checkSessionConnected())
        return;

    session_->send(msg);
}

Order* TradingClient::findByOrderId(ClOrdID clOrdId)
{
    Order* const msg = orderBook_.find(clOrdId);

    if (!msg)
    {
        std::stringstream ss;
        ss
            << "Cannot process received Execution Report. No order was sent with ClOrdID (tag = 11) equal to '"
            << clOrdId
            << " in the current session'";

        throw std::domain_error(ss.str());
    }

    return msg;
}

TradingClient::TradingClient(const Settings& settings)
    : settings_(settings)
    , connected_(false)
    , messageFactory_(atoi(settings.get("MarketSegment").c_str()))
    , menu_(this)
{
    createSessions();
    constructMenu();
}

void TradingClient::run()
{
    menu_.processRequests();
}

void TradingClient::constructMenu()
{
    menu_
        .add("Connect Sessions.", "Sending Negotiation/Establishment.. ", &TradingClient::processEstablishConnection)
        .add("Review the status of sessions. ", "Viewing the status of sessions.. ", &TradingClient::processViewSessions)
        .add("Send Sequence. ", "Sending Sequence.. ", &TradingClient::processSendSequence)
        .add("Review sent orders and their status. ", "Viewing sent orders and their status.. ", &TradingClient::processViewOrders)
        .add("Create and send a New Order. ", "Creating new order.. ", &TradingClient::processSendNewOrder)
        .add("Submit Order Modify Request. ", "Order Modify Request.. ", &TradingClient::processOrderModifyRequest)
        .add("Submit Order Cancel Request. ", "Order Cancel Request.. ", &TradingClient::processOrderCancelRequest)
        .add("Submit Order Mass Action Request. ", "Order Mass Action Request.. ", &TradingClient::processOrderMassActionRequest)
        .add("Submit SecurityDefinitionRequest. ", "Creating SecurityDefinition.. ", &TradingClient::processSecurityDefinitionRequest)
        .add("Submit New Order Cross. ", "Creating Cross Order.. ", &TradingClient::processCrossOrder)
        .add("Disconnect all sessions", "Closing connections...", &TradingClient::processDisconnect)
        .add("Reset Sequence Numbers", "Reset Sequence Numbers", &TradingClient::resetSequenceNumbers)
        .add("Close the connection and exit. ", "Exiting application.. ", &TradingClient::processExit);
}

bool TradingClient::checkSessionConnected()
{
    if (!connected_)
        Screen::info("Session is not connected. Please establish the connection first.");

    return connected_;
}

void TradingClient::createSessions()
{
    // 1. Creates session according to the application settings.

    Screen::info("Creating the primary BOE Session..");

    SessionSettings settings;

    settings
        .licenseStore("../../license")
        .sessionId(settings_.getAsInt("SessionId"))
        .accessKey(settings_.get("AccessKey"))
        .enteringFirm(settings_.getAsInt("FirmId"))
        .tradingSystemName(settings_.get("TradingSystemName"))
        .tradingSystemVersion(settings_.get("TradingSystemVersion"))
        .keepAliveInterval(settings_.getAsInt("KeepAliveInterval"));

    session_.reset(createSession(settings, this));

    const int incomingSequenceNumber = settings_.getAsInt("InSeqNum");

    if (incomingSequenceNumber > 0)
        session_->inSeqNum(incomingSequenceNumber);

    const int outgoingSequenceNumber = settings_.getAsInt("OutSeqNum");

    if (outgoingSequenceNumber > 0)
        session_->outSeqNum(outgoingSequenceNumber);
}

// Menu actions

void TradingClient::processEstablishConnection(CommandExecutionStatus* status)
{
    if (!connected_)
    {
        try
        {
            session_->connect(settings_.get("Host"), settings_.getAsInt("Port"));
        }
        catch (const std::exception& ex)
        {
            Screen::info("Cannot connect to the host: ", ex.what());
        }

        Screen::info("Done");
    }
    else
        Screen::info("Connection is already established.");

    *status = ContinueExecution;
}

void TradingClient::processDisconnect(CommandExecutionStatus*)
{
    if (ONIXS_B3_BOE_NULLPTR != session_.get() && session_->state() != SessionStateId::Disconnected)
    {
        Screen::info("Disconnecting from primary counterparty.. ");

        session_->disconnect();
    }

    Screen::info("Done");
}

void TradingClient::processSendSequence(CommandExecutionStatus*)
{
    if (!checkSessionConnected())
        return;

    session_->sendSequenceMessage();

    Screen::info("Done");
}

void TradingClient::processViewOrders(CommandExecutionStatus*)
{
    OrderList orderList;
    orderBook_.getEntries(orderList);
    OrdersViewer::outputItems(orderList, 10);
}

void TradingClient::processViewSessions(CommandExecutionStatus*)
{
    Screen::info("Primary BOE session: ",
                 session_->toString() + ", State=" + SessionStateId::toString(session_->state()) +
                 ".");
}

void TradingClient::processOrderMassActionRequest(CommandExecutionStatus*)
{
    if (!checkSessionConnected())
        return;

    Screen::info("Sending Order Mass Action Request to counterparty.. ");

    OrderMassActionRequest & msg = messageFactory_.getOrderMassActionRequest();

    send(msg);

    Screen::info("Done");
}


void TradingClient::processSecurityDefinitionRequest(CommandExecutionStatus*)
{
    if (!checkSessionConnected())
        return;

    Screen::info("Sending Security Definition Request to counterparty.. ");

    SecurityDefinitionRequest & msg = messageFactory_.getSecurityDefinitionRequest();

    send(msg);

    Screen::info("Done");
}

void TradingClient::processSendNewOrder(CommandExecutionStatus*)
{
    if (!checkSessionConnected())
        return;

    Screen::info("Sending new order to counterparty.. ");

    Order order = newOrder();

    NewOrderSingle & msg = messageFactory_.getNewOrder(order);

    send(msg);
    orderBook_.store(order);

    Screen::info("Done");
}

void TradingClient::processOrderCancelRequest(CommandExecutionStatus*)
{
    if (!checkSessionConnected())
        return;

    OrderList ordersInBook;
    orderBook_.getEntries(ordersInBook);

    if (ordersInBook.empty())
    {
        Screen::info("No orders found");
        return;
    }

    OrdersViewer orderViewer;
    orderViewer.outputItems(ordersInBook, 10);

    Screen::out("Enter the index of the order to be canceled ");

    const int orderIndex = atoi(Screen::getInput().c_str());

    const Order * order = ordersInBook.at(orderIndex - 1);

    OrderCancelRequest & msg = messageFactory_.getCancelRequest(*order);

    send(msg);

    Screen::info("Done");
}

void TradingClient::processOrderModifyRequest(CommandExecutionStatus*)
{
    if (!checkSessionConnected())
        return;

    OrderList ordersInBook;
    orderBook_.getEntries(ordersInBook);

    if (ordersInBook.empty())
    {
        Screen::info("No orders found");
        return;
    }

    OrdersViewer orderViewer;
    orderViewer.outputItems(ordersInBook, 10);

    Screen::out("Enter the index of the order to be modified ");

    const int orderIndex = atoi(Screen::getInput().c_str());

    Order* const order = ordersInBook.at(orderIndex - 1);

    // Changing OrderQty
    Screen::info("Enter new OrderQty (or Enter to skip): ");
    Screen::getInput(order->orderQty_, order->orderQty_);

    // Changing Price
    Screen::info("Enter new Price mantissa (or Enter to skip): ");
    Screen::getInput(order->price_, order->price_);

    OrderCancelReplaceRequest & msg = messageFactory_.getModifyRequest(*order);

    send(msg);

    Screen::info("Done");
}

void TradingClient::processCrossOrder(CommandExecutionStatus*)
{
    if (!checkSessionConnected())
        return;

    Order buySideOrder;

    Screen::info("Enter Price mantissa (default = " + toStr(DefaultPriceMantissa) + "): ");
    Screen::getInput(buySideOrder.price_, DefaultPriceMantissa);

    Screen::info("Enter SecurityId (default=" + toStr(DefaultSecurityId) + "): ");
    Screen::getInput(buySideOrder.securityId_, DefaultSecurityId);

    Screen::info("Enter Quantity (default = 100): ");
    Screen::getInput<QuantityOptional>(buySideOrder.orderQty_, 100ul);

    Order sellSideOrder;

    sellSideOrder
        .price(buySideOrder.price_)
        .securityId(buySideOrder.securityId_)
        .orderQty(buySideOrder.orderQty_)
        .side(Side::Sell);

    NewOrderCross & msg = messageFactory_.getNewOrderCross(buySideOrder, sellSideOrder);

    send(msg);

    orderBook_
        .store(buySideOrder)
        .store(sellSideOrder);

    Screen::info("Done");
}

void TradingClient::processExit(CommandExecutionStatus* status)
{
    *status = TerminateExecution;
}

void TradingClient::resetSequenceNumbers(CommandExecutionStatus*)
{
    if (ONIXS_B3_BOE_NULLPTR != session_.get() && session_->state() == SessionStateId::Disconnected)
    {
        if(session_->negotiated())
            session_->reset();
    }
    else
        Screen::info("Operation can be performed only when the sessions are disconnected");

    Screen::info("Done");
}

Order TradingClient::newOrder()
{
    Order order;

    Screen::info("Enter SecurityId (default=" + toStr(DefaultSecurityId) + "): ");
    Screen::getInput(order.securityId_, DefaultSecurityId);

    Screen::info(
        "Enter OrderType(40) (1 - Market order, 2 - Limit order (default), 3 - Stop order, 4 - Stop - Limit order, K - Market - Limit order): ");
    Screen::getInputChar(order.ordType_, OrdType::Limit);

    if (order.ordType_ == OrdType::Limit || order.ordType_ == OrdType::StopLimit)
    {
        Screen::info("Enter Price mantissa (default = " + toStr(DefaultPriceMantissa) + "): ");
        Screen::getInput(order.price_, DefaultPriceMantissa);
    }

    if (order.ordType_ == OrdType::StopLimit || order.ordType_ == OrdType::StopLoss)
    {
        Screen::info("Enter StopPx: ");
        Screen::getInput(order.stopPx_);
    }

    Screen::info("Enter OrderQuantity (default = 100): ");
    Screen::getInput<QuantityOptional>(order.orderQty_, 100ul);

    Screen::info("Enter MinQty or skip");
    Screen::getInput(order.minQty_, NullQuantityOptional().value());

    Screen::info(
        "Enter TimeInForce (0 - Day (default), 1 - Good Till Cancel, 3 - Immediate Or Cancel, 6 - Good Till Date): ");
    Screen::getInputChar(order.timeInForce_, TimeInForce::Day);

    if (order.timeInForce_ == TimeInForce::GoodTillDate)
    {
        Screen::info("Enter Expire date YYYYMMDD: ");
        Screen::getInputLocalMktDate(order.expireDate_);
    }

    Screen::info("Enter Side (1 - Buy (default), 2 - Sell): ");
    Screen::getInputChar(order.side_, Side::Buy);

    return order;
}

void TradingClient::onMessageSending(char* bytes, size_t size, Session*)
{
    Screen::out("Outbound message: ", SbeMessage(bytes, static_cast<Messaging::MessageSize>(size)));
}

void TradingClient::onBusinessMessageReject(const BusinessMessageReject206 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onNegotiateResponse(const NegotiateResponse2 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onNegotiateReject(const NegotiateReject3 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onEstablishAck(const EstablishAck5 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onEstablishReject(const EstablishReject6 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onSequence(const Sequence9 &, Session *)
{
}

void TradingClient::onTerminate(const Terminate7 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onRetransmitReject(const Messaging::RetransmitReject14 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onRetransmission(const Messaging::Retransmission13 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onNotApplied(const Messaging::NotApplied8 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onExecutionReportNew(const ExecutionReportNew200 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());

    if(isRetransmitted(msg))
        return;

    Order * const order = findByOrderId(msg.clOrdId());
    assert(order);

    setCommonFields(order, msg);
    setExpireDate(order, msg);
    setOrdStatus(order->orderStatus_, msg);
    order->orderId_ = msg.clOrdId();
    order->timeInForce_ = msg.timeInForce();
    order->orderId_ = msg.orderId();

    Screen::info("Order changed: " + order->toString());
}

void TradingClient::onExecutionReportModify(const ExecutionReportModify201 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());

    if(isRetransmitted(msg))
        return;

    Order * const order = findByOrderId(msg.clOrdId());
    assert(order);

    setCommonFields(order, msg);
    setExpireDate(order, msg);
    order->orderId_ = msg.clOrdId();
    order->timeInForce_ = msg.timeInForce();
    order->orderId_ = msg.orderId();

    setOrdStatus(order->orderStatus_, msg);
    order->leavesQty(msg.leavesQty())
          .cumQty(msg.cumQty());

    Screen::info("Order changed: " + order->toString());
}

void TradingClient::onExecutionReportCancel(const ExecutionReportCancel202 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());

    if(isRetransmitted(msg))
        return;

    Order * const order = findByOrderId(msg.clOrdId());
    assert(order);

    setCommonFields(order, msg);
    setExpireDate(order, msg);
    order->orderId_ = msg.clOrdId();
    order->timeInForce_ = msg.timeInForce();
    order->orderId_ = msg.orderId();

    setOrdStatus(order->orderStatus_, msg);
    order->leavesQty(msg.cumQty());

    Screen::info("Order changed: " + order->toString());
}

void TradingClient::onExecutionReportReject(const ExecutionReportReject204 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());

    if(isRetransmitted(msg))
        return;

    Order * const order = findByOrderId(msg.clOrdId());
    assert(order);

    setCommonFields(order, msg);
    setExpireDate(order, msg);
    order->timeInForce_ = msg.timeInForce();
    setOrdStatus(order->orderStatus_, msg);

    OrderIDOptional ordId;
    if(msg.orderId(ordId))
        order->orderId_ = ordId;

    Screen::info("Order changed: " + order->toString());
}

void TradingClient::onExecutionReportTrade(const ExecutionReportTrade203 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());

    if(isRetransmitted(msg))
        return;

    ClOrdIDOptional clOrdId;
    if(!msg.clOrdId(clOrdId))
        return;

    Order * const order = findByOrderId(clOrdId);
    assert(order);

    setCommonFields(order, msg);
    order->orderId_ = msg.orderId();
    order->orderStatus(msg.ordStatus())
          .orderId(clOrdId)
          .leavesQty(msg.leavesQty())
          .cumQty(msg.cumQty())
          .lastPx(msg.lastPx().mantissa());

    Screen::info("Order changed: " + order->toString());
}

void TradingClient::onSecurityDefinitionResponse(const SecurityDefinitionResponse301 & msg, Session *)
{
    Screen::info("Message received from counterparty: ", msg.toString());
}

void TradingClient::onOrderMassActionReport(const OrderMassActionReport702& msg, Session*)
{
    Screen::info("Received Order Mass Action Report: ", msg.toString());
    Screen::info("MassActionResponse=", toStr(msg.massActionResponse()));

    SecurityIDOptional securityId = SecurityIDOptional();

    if (msg.securityId(securityId))
        Screen::info("MarketSegmentID=", toStr(securityId));
}

void TradingClient::onStateChange(SessionStateId::Enum newState, SessionStateId::Enum /*prevState*/, Session *)
{
    Screen::info("Session state changed to ", SessionStateId::toString(newState));
    connected_ = (newState == SessionStateId::Established);
}

void TradingClient::onError(SessionErrorReason::Enum, const std::string & description, Session *, Messaging::SbeMessage)
{
    Screen::info("Session-level error: ", description);
}

void TradingClient::onWarning(SessionWarningReason::Enum, const std::string & description, Session *, Messaging::SbeMessage)
{
    Screen::info("Session-level warning: ", description);
}

}
//! [TradingClientSampleCpp]
