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

//! [OrderH]
#include <OnixS/B3/BOE/messaging/Integral.h>

#include <string>

namespace Samples
{

struct Order
{
    // Initializes an order.
    Order();

    // Human-readable presentation of the most interesting fields stored in the order.
    std::string toString() const;

    // Returns a unique order id.
    ClOrdID id() const;

    // Setters.
    Order& cIOrdId(ClOrdID value);
    Order& orderId(OrderID value);
    Order& price(UInt64 value);
    Order& orderQty(Quantity value);
    Order& minQty(Quantity value);
    Order& leavesQty(Quantity value);
    Order& cumQty(Quantity value);
    Order& securityId(SecurityID value);
    Order& side(Side::Enum value);
    Order& ordType(OrdType::Enum value);
    Order& stopPx(Int64 value);
    Order& timeInForce(TimeInForce::Enum value);
    Order& expireDate(LocalMktDate value);
    Order& orderStatus(OrdStatus::Enum value);
    Order& lastPx(Int64 value);
    Order& transactTime(UInt64 value);

    ClOrdID cIOrdId_;
    OrderID orderId_;
    Int64 price_;
    QuantityOptional orderQty_;
    QuantityOptional minQty_;
    QuantityOptional leavesQty_;
    QuantityOptional cumQty_;
    SecurityID securityId_;
    Side::Enum side_;
    OrdType::Enum ordType_;
    Int64 stopPx_;
    TimeInForce::Enum timeInForce_;
    LocalMktDate expireDate_;
    OrdStatus::Enum orderStatus_;
    Int64 lastPx_;
    UInt64 transactTime_;
};

}
//! [OrderH]
