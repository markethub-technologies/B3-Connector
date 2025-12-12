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

//! [MessageFactoryCpp]
#include "../Settings/Defaults.h"

#include "MessageFactory.h"

namespace Samples {

const char* Location = "DMA";
const char* EnteringTrader = "TADA";
const char* DeskId = "1";
const OrdTagID OrderTag = 100;
const Account Account = 10101;

template<typename MessageType>
void setMarketSegmentId(MessageType & msg, MarketSegmentID marketSegmentId)
{
    msg->businessHeader().setMarketSegmentId(marketSegmentId);
}

MessageFactory::MessageFactory(MarketSegmentID marketSegmentId)
{
    iid_.setPrefix(300);
    iid_.setDocument(123456);
    marketSegmentId_ = marketSegmentId;
}

NewOrderSingle MessageFactory::initNewOrder() const
{
    NewOrderSingle msg;

    setMarketSegmentId(msg, marketSegmentId_);

    msg->setOrdTagId(OrderTag)
        .setMmProtectionReset(Boolean::FalseValue)
        .setSenderLocation(Location)
        .setEnteringTrader(EnteringTrader)
        .setSelfTradePreventionInstruction(SelfTradePreventionInstruction::None)
        .setMemo("ONIXS 123456789")
        .setDeskId(DeskId)
        .setAccount(Account)
        .setInvestorId(iid_);

    return msg;
}

NewOrderSingle & MessageFactory::getNewOrder(const Order& order) const
{
    static NewOrderSingle msg = initNewOrder();

    msg->setPrice(PriceOptional(order.price_))
        .setOrderQty(order.orderQty_)
        .setSecurityId(order.securityId_)
        .setClOrdId(order.cIOrdId_)
        .setStopPx(PriceOptional(order.stopPx_))
        .setMinQty(order.minQty_)
        .setOrdType(order.ordType_)
        .setTimeInForce(order.timeInForce_)
        .setSide(order.side_);

    if (order.timeInForce_ == TimeInForce::GoodTillDate)
        msg->setExpireDate(localMktDateToTimestamp(order.expireDate_));

    return msg;
}

OrderCancelReplaceRequest MessageFactory::initOrderCancelReplaceRequest() const
{
    OrderCancelReplaceRequest msg;

    setMarketSegmentId(msg, marketSegmentId_);

    msg->setOrdTagId(OrderTag)
        .setMmProtectionReset(Boolean::FalseValue)
        .setSenderLocation(Location)
        .setEnteringTrader(EnteringTrader)
        .setSelfTradePreventionInstruction(SelfTradePreventionInstruction::None)
        .setMemo("ONIXS 123456789")
        .setInvestorId(iid_)
        .setAccount(Account)
        .setDeskId(DeskId);

    return msg;
}

OrderCancelReplaceRequest & MessageFactory::getModifyRequest(const Order& order) const
{
    static OrderCancelReplaceRequest msg = initOrderCancelReplaceRequest();

    msg->setPrice(PriceOptional(order.price_))
        .setOrderQty(order.orderQty_)
        .setSecurityId(order.securityId_)
        .setClOrdId(order.cIOrdId_)
        .setOrderId(order.orderId_)
        .setStopPx(PriceOptional(order.stopPx_))
        .setMinQty(order.minQty_)
        .setOrdType(order.ordType_)
        .setTimeInForce(order.timeInForce_)
        .setSide(order.side_);

    if (order.timeInForce_ == TimeInForce::GoodTillDate)
        msg->setExpireDate(localMktDateToTimestamp(order.expireDate_));

    return msg;
}

OrderCancelRequest MessageFactory::initOrderCancelRequest() const
{
    OrderCancelRequest msg;

    setMarketSegmentId(msg, marketSegmentId_);

    msg->
        setSenderLocation(Location)
        .setEnteringTrader(EnteringTrader)
        .setMemo("ONIXS 123456789")
        .setDeskId(DeskId);

    return msg;
}

OrderCancelRequest & MessageFactory::getCancelRequest(const Order& order) const
{
    static OrderCancelRequest msg = initOrderCancelRequest();

    msg->setClOrdId(order.cIOrdId_)
        .setOrderId(order.orderId_)
        .setSecurityId(order.securityId_)
        .setSide(order.side_)
        ;

    return msg;
}

NewOrderCross MessageFactory::initNewOrderCross() const
{
    NewOrderCross msg;

    setMarketSegmentId(msg, marketSegmentId_);

    msg->
        setSenderLocation(Location)
        .setEnteringTrader(EnteringTrader)
        .setMemo("ONIXS 123456789")
        .setCrossPrioritization(CrossPrioritization::None)
        .setDeskId(DeskId)
        ;

    return msg;
}

NewOrderCross & MessageFactory::getNewOrderCross(const Order& buySideOrder, const Order& sellSideOrder) const
{
    static NewOrderCross msg = initNewOrderCross();

    msg->setPrice(PriceOptional(buySideOrder.price_))
        .setSecurityId(buySideOrder.securityId_)
        .setOrderQty(buySideOrder.orderQty_)
        .setCrossId(IdGenerator::newId())
        ;

    NewOrderCross106::Sides sides = msg->sides(2);

    NewOrderCross106::SidesEntry buyEntry = sides[0];
    NewOrderCross106::SidesEntry sellEntry = sides[1];

    buyEntry.setClOrdId(buySideOrder.cIOrdId_)
            .setSide(buySideOrder.side_)
            .setAccount(Account);

    sellEntry.setClOrdId(sellSideOrder.cIOrdId_)
             .setSide(sellSideOrder.side_)
             .setAccount(Account);

    return msg;
}

OrderMassActionRequest MessageFactory::initOrderMassActionRequest() const
{
    OrderMassActionRequest msg;

    setMarketSegmentId(msg, marketSegmentId_);

    msg->setOrdTagId(OrderTag)
        .setMassActionScope(MassActionScope::AllOrdersForATradingSession)
        .setMassActionType(MassActionType::CancelOrders)
        .setInvestorId(iid_);

    return msg;
}

OrderMassActionRequest & MessageFactory::getOrderMassActionRequest() const
{
    static OrderMassActionRequest msg = initOrderMassActionRequest();

    msg->setClOrdId(IdGenerator::newId());

    return msg;
}


SecurityDefinitionRequest MessageFactory::initSecurityDefinitionRequest() const
{
    SecurityDefinitionRequest msg;

    setMarketSegmentId(msg, marketSegmentId_);

    msg->
        setSenderLocation(Location)
        .setEnteringTrader(EnteringTrader);


    return msg;
}

SecurityDefinitionRequest & MessageFactory::getSecurityDefinitionRequest() const
{
    static SecurityDefinitionRequest msg = initSecurityDefinitionRequest();

    msg->setSecurityReqId(IdGenerator::newId());

    SecurityDefinitionRequest300::Legs legs = msg->legs(1);

    legs[0]
        .setLegSymbol("GOAU3")
        .setLegRatioQty(RatioQty(1));

    return msg;
}

}
//! [MessageFactoryCpp]
