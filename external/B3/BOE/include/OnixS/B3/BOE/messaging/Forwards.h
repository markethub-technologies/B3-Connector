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

#include <OnixS/B3/BOE/ABI.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

ONIXS_B3_BOE_LTWT_STRUCT_DECL(Negotiate1);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(NegotiateResponse2);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(NegotiateReject3);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(Establish4);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(EstablishAck5);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(EstablishReject6);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(Terminate7);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(NotApplied8);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(Sequence9);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(RetransmitRequest12);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(Retransmission13);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(RetransmitReject14);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(SimpleNewOrder100);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(SimpleModifyOrder101);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(NewOrderSingle102);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(OrderCancelReplaceRequest104);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(OrderCancelRequest105);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(NewOrderCross106);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(ExecutionReportNew200);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(ExecutionReportModify201);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(ExecutionReportCancel202);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(ExecutionReportTrade203);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(ExecutionReportReject204);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(ExecutionReportForward205);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(BusinessMessageReject206);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(SecurityDefinitionRequest300);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(SecurityDefinitionResponse301);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(QuoteRequest401);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(QuoteStatusReport402);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(Quote403);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(QuoteCancel404);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(QuoteRequestReject405);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(PositionMaintenanceCancelRequest501);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(PositionMaintenanceRequest502);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(PositionMaintenanceReport503);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(AllocationInstruction601);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(AllocationReport602);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(OrderMassActionRequest701);
ONIXS_B3_BOE_LTWT_STRUCT_DECL(OrderMassActionReport702);

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
