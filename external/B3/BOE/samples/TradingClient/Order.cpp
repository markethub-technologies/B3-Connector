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

//! [OrderCpp]
#include "Order.h"

#include "../Common/Helpers.h"

namespace Samples
{

Order::Order()
    : cIOrdId_(IdGenerator::newId())
    , orderId_()
    , price_(NullPriceOptional::NullMantissa().value())
    , orderQty_()
    , minQty_(NullQuantityOptional().value())
    , leavesQty_(NullQuantityOptional().value())
    , cumQty_(NullQuantityOptional().value())
    , securityId_()
    , side_(Side::Buy)
    , ordType_(OrdType::Limit)
    , stopPx_(NullPriceOptional::NullMantissa().value())
    , timeInForce_(TimeInForce::Day)
    , expireDate_(NullUInt16().value())
    , orderStatus_(OrdStatus::New)
    , lastPx_()
    , transactTime_()
{
}

template<typename T>
std::string toStrOptional(T value, T emptyValue)
{
    return value == emptyValue ? std::string() : toStr(value);
}

std::string Order::toString() const
{
    std::ostringstream builder;

    builder
        << "ClOrdID = " << cIOrdId_
        << ", OrderID = " << toStr(orderId_)
        << ", SecurityId = " << toStr(securityId_)
        << ", OrderStatus = " << toStr(orderStatus_)
        << ", Type = " << toStr(ordType_)
        << ", Price = " << toStr(price_)
        << ", Quantity = " << toStr(orderQty_)
        << ", MinQty = " << toStrOptional(minQty_, NullQuantityOptional().value())
        << ", LeavesQty = " << toStrOptional(leavesQty_, NullQuantityOptional().value())
        << ", CumQty = " << toStrOptional(cumQty_, NullQuantityOptional().value())
        << ", Side = " << toStr(side_)
        << ", StopPx = " << toStrOptional(stopPx_, NullPriceOptional::NullMantissa().value())
        << ", LastFillPrice = " << toStr(lastPx_)
        << ", TimeInForce = " << toStr(timeInForce_)
        << ", ExpireDate = " << toStr(localMktDateToTimestamp(expireDate_), TimestampFormat::YYYYMMDD)
        << ", TransactTime = " << Timestamp(transactTime_).toString();

    return builder.str();
}

ClOrdID Order::id() const
{
    return cIOrdId_;
}

Order& Order::cIOrdId(ClOrdID value)
{
    cIOrdId_ = value;
    return *this;
}

Order& Order::orderId(OrderID value)
{
    orderId_ = value;
    return *this;
}

Order& Order::price(UInt64 value)
{
    price_ = value;
    return *this;
}

Order& Order::orderQty(Quantity value)
{
    orderQty_ = value;
    return *this;
}

Order& Order::minQty(Quantity value)
{
    minQty_ = value;
    return *this;
}

Order& Order::leavesQty(Quantity value)
{
    leavesQty_ = value;
    return *this;
}

Order& Order::cumQty(Quantity value)
{
    cumQty_ = value;
    return *this;
}

Order& Order::securityId(SecurityID value)
{
    securityId_ = value;
    return *this;
}

Order& Order::side(Side::Enum value)
{
    side_ = value;
    return *this;
}

Order& Order::ordType(OrdType::Enum value)
{
    ordType_ = value;
    return *this;
}

Order& Order::stopPx(Int64 value)
{
    stopPx_ = value;
    return *this;
}

Order& Order::timeInForce(TimeInForce::Enum value)
{
    timeInForce_ = value;
    return *this;
}

Order& Order::expireDate(LocalMktDate value)
{
    expireDate_ = value;
    return *this;
}

Order& Order::orderStatus(OrdStatus::Enum value)
{
    orderStatus_ = value;
    return *this;
}

Order& Order::lastPx(Int64 value)
{
    lastPx_ = value;
    return *this;
}

Order& Order::transactTime(UInt64 value)
{
    transactTime_ = value;
    return *this;
}

}
//! [OrderCpp]
