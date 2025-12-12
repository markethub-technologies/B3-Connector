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
#include <OnixS/B3/MarketData/UMDF/Integral.h>
#include <OnixS/B3/MarketData/UMDF/Defines.h>
#include <OnixS/B3/MarketData/UMDF/CompilerDetection.h>
#include <OnixS/B3/MarketData/UMDF/Time.h>

#include <string>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                /// Abstract watch service.
                class ONIXS_B3_UMDF_MD_API WatchService
                {
                public:
                    /// Returns current UTC time.
                    Timestamp now();

                    /// Identifies watch service.
                    const char* id() const;

                    ///
                    virtual ~WatchService();

                protected:
                    WatchService(void* impl) ONIXS_B3_UMDF_MD_NOTHROW;

                private:
                    void* const impl_;
                    friend struct FeHelper;
                };

                /// UTC watch.
                class ONIXS_B3_UMDF_MD_API UtcWatch : public WatchService
                {
                public:
                    /// Returns watch service
                    static UtcWatch& service();

                    ///
                    ~UtcWatch() ONIXS_B3_UMDF_MD_OVERRIDE;

                private:
                    UtcWatch();
                };

                /// The network interface watch.
                ///
                /// This class is designed to use the network adapter's watch if the capability is supported.
                /// When an instance of the class is linked to a feed engine supporting hardware timestamps retrieval,
                /// the feed engine extracts hardware timestamps and assigns them to the incoming multicast packets.
                ///
                /// An ordinary system (UTC) clock is used in all other cases.
                /// \note Network interface card must be synchronized with the host's clock.
                class ONIXS_B3_UMDF_MD_API NicWatch : public WatchService
                {
                public:
                    /// Returns watch service
                    static NicWatch& service();

                    ///
                    ~NicWatch() ONIXS_B3_UMDF_MD_OVERRIDE;

                private:
                    NicWatch();
                };
            }
        }
    }
}
