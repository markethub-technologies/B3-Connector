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

#include <OnixS/B3/MarketData/UMDF/ABI.h>

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

ONIXS_B3_UMDF_MD_LTWT_CLASS_DECL(SbeMessage);

ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(SequenceReset_1);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(Sequence_2);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(EmptyBook_9);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(ChannelReset_11);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(SecurityStatus_3);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(SecurityGroupPhase_10);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(SecurityDefinition_12);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(News_5);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(OpeningPrice_15);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(TheoreticalOpeningPrice_16);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(ClosingPrice_17);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(AuctionImbalance_19);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(QuantityBand_21);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(PriceBand_22);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(HighPrice_24);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(LowPrice_25);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(LastTradePrice_27);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(SettlementPrice_28);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(OpenInterest_29);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(SnapshotFullRefresh_Header_30);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(Order_MBO_50);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(DeleteOrder_MBO_51);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(MassDeleteOrders_MBO_52);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(Trade_53);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(ForwardTrade_54);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(ExecutionSummary_55);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(ExecutionStatistics_56);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(TradeBust_57);
ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(SnapshotFullRefresh_Orders_MBO_71);

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
