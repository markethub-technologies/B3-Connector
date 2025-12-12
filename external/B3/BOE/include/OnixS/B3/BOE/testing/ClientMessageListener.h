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

#include <OnixS/B3/BOE/testing/ABI.h>

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)

#include <OnixS/B3/BOE/messaging/Forwards.h>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Testing {

ONIXS_B3_BOE_API_DECL(class, Gateway);

/// Client's messages Listener.
class ONIXS_B3_BOE_EXPORTED ClientMessageListener
{
protected:

    virtual ~ClientMessageListener() = 0;

public:
    virtual void onSimpleNewOrder(const Messaging::SimpleNewOrder100& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onSimpleModifyOrder(const Messaging::SimpleModifyOrder101& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onNewOrderSingle(const Messaging::NewOrderSingle102& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onOrderCancelReplaceRequest(const Messaging::OrderCancelReplaceRequest104& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onOrderCancelRequest(const Messaging::OrderCancelRequest105& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onNewOrderCross(const Messaging::NewOrderCross106& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onSecurityDefinitionRequest(const Messaging::SecurityDefinitionRequest300& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onQuoteRequest(const Messaging::QuoteRequest401& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onQuoteStatusReport(const Messaging::QuoteStatusReport402& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onQuote(const Messaging::Quote403& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onQuoteCancel(const Messaging::QuoteCancel404& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onQuoteRequestReject(const Messaging::QuoteRequestReject405& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onPositionMaintenanceCancelRequest(const Messaging::PositionMaintenanceCancelRequest501& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onPositionMaintenanceRequest(const Messaging::PositionMaintenanceRequest502& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onAllocationInstruction(const Messaging::AllocationInstruction601& /*msg*/, Gateway* /*gateway*/) {}
    virtual void onOrderMassActionRequest(const Messaging::OrderMassActionRequest701& /*msg*/, Gateway* /*gateway*/) {}
};

/// Client's session messages Listener.
class ONIXS_B3_BOE_EXPORTED ClientSessionMessageListener
{
protected:
    virtual ~ClientSessionMessageListener() = 0;

public:
    /// By default, send Sequence9 message with gateway->outSeqNum(), KeepAliveLapsed::NotLapsed
    virtual void onRetransmitRequest(const Messaging::RetransmitRequest12 & /*msg*/, Gateway* /*gateway*/);

    /// By default, send Sequence9 message with gateway->outSeqNum(), KeepAliveLapsed::NotLapsed
    virtual void onSequence(const Messaging::Sequence9 & /*msg*/, Gateway * /*gateway*/);
};

}
}
}
}

#endif
