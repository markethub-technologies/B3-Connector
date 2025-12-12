#pragma once

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

#include <string>

#include <OnixS/B3/BOE/ABI.h>

namespace OnixS {
namespace B3 {
namespace BOE {

    /// Threading model.
    struct ThreadingModel
    {
        enum Enum
        {
            /// Each session has a sender thread and a receiving thread.
            Dedicated,

            /// Sessions share a thread pool.
            Pool,

            /// Session events are handled by rolling an event loop in a user thread.
            External,

            /// The default mode.
            Default = Dedicated,
        };

        /// \return a string that represents the given value.
        ONIXS_B3_BOE_EXPORTED static const char * toString(Enum type) ONIXS_B3_BOE_NOTHROW;

        ONIXS_B3_BOE_EXPORTED static Enum parse(const std::string & text);
    };
}
}
}
