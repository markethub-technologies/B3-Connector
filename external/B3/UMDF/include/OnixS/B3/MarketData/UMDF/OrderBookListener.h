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
#include <OnixS/B3/MarketData/UMDF/messaging/SbeMessage.h>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                ONIXS_B3_UMDF_MD_API_DECL (class, OrderBook);

                /// Order Book listener
                class ONIXS_B3_UMDF_MD_API OrderBookListener
                {
                    public:
                        /// Is called when the book is changed within it's depth, when Order_MBO_50, DeleteOrder_MBO_51 or MassDeleteOrders_MBO_52 are received.
                        virtual void onOrderBookChanged(const OrderBook& book, const Messaging::SbeMessage message) = 0;

                        /// Is called when the book is updated, when a message with MatchEventIndicator::EndOfEvent is received and the book was changed within it's depth.
                        virtual void onOrderBookUpdated (const OrderBook& book) = 0;

                        /// Is called when no data is coming during a reasonable
                        /// period of time. Since the moment of call books
                        /// must be considered outdated. Further
                        /// call of 'onOrderBookUpdated' members makes a particular
                        /// book as up-to-date.
                        virtual void onOrderBookOutOfDate (const OrderBook& book) = 0;

                    protected:
                        virtual ~OrderBookListener() {}
                };
            }
        }
    }
}
