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

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/Defines.h>
#include <OnixS/B3/MarketData/UMDF/ErrorListener.h>
#include <OnixS/B3/MarketData/UMDF/Exception.h>
#include <OnixS/B3/MarketData/UMDF/FeedEngine.h>
#include <OnixS/B3/MarketData/UMDF/Handler.h>
#include <OnixS/B3/MarketData/UMDF/HandlerSettings.h>
#include <OnixS/B3/MarketData/UMDF/HandlerStateListener.h>
#include <OnixS/B3/MarketData/UMDF/Integral.h>
#include <OnixS/B3/MarketData/UMDF/LogSettings.h>
#include <OnixS/B3/MarketData/UMDF/MessageListener.h>
#include <OnixS/B3/MarketData/UMDF/Messaging.h>
#include <OnixS/B3/MarketData/UMDF/Replay.h>
#include <OnixS/B3/MarketData/UMDF/Semaphore.h>
#include <OnixS/B3/MarketData/UMDF/Time.h>
#include <OnixS/B3/MarketData/UMDF/WarningListener.h>
#include <OnixS/B3/MarketData/UMDF/WatchService.h>
#include <OnixS/B3/MarketData/UMDF/OrderBook.h>
#include <OnixS/B3/MarketData/UMDF/OrderBookListener.h>

#include <OnixS/B3/MarketData/UMDF/testing/LogPlayer.h>
