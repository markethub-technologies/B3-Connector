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

//! [MessageFactoryH]
#include "../Common/Helpers.h"

#include "Order.h"

namespace Samples {

// Constructs SBE messages of specific types according to the given parameters.
class MessageFactory
{
public:
    explicit MessageFactory(MarketSegmentID marketSegmentId);

    // Constructs a reusable NewOrderSingle message according to the given order traits.
    NewOrderSingle & getNewOrder(const Order& order) const;

    // Constructs a reusable OrderCancelReplaceRequest message for the given order.
    OrderCancelReplaceRequest & getModifyRequest(const Order& order) const;

    // Constructs a reusable OrderCancelRequest message for the given order.
    OrderCancelRequest & getCancelRequest(const Order& order) const;

    // Constructs a reusable NewOrderCross message according to the given order traits.
    NewOrderCross & getNewOrderCross(const Order& buySideOrder, const Order& sellSideOrder) const;

    // Constructs a reusable OrderMassActionRequest message.
    OrderMassActionRequest & getOrderMassActionRequest() const;

    // Constructs a reusable SecurityDefinitionRequest message.
    SecurityDefinitionRequest & getSecurityDefinitionRequest() const;

private:
    NewOrderSingle initNewOrder() const;
    OrderCancelReplaceRequest initOrderCancelReplaceRequest() const;
    OrderCancelRequest initOrderCancelRequest() const;
    NewOrderCross initNewOrderCross() const;
    OrderMassActionRequest initOrderMassActionRequest() const;
    SecurityDefinitionRequest initSecurityDefinitionRequest() const;

    InvestorID iid_;
    MarketSegmentID marketSegmentId_;
};

}
//! [MessageFactoryH]
