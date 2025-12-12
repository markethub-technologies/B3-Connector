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

#include <OnixS/B3/BOE/ABI.h>

#include <iosfwd>
#include <string>

namespace OnixS {
namespace B3 {
namespace BOE {

/// Session state ID.
struct SessionStateId
{
    enum Enum
    {
        /// Session is disconnected.
        Disconnected,

        /// Session is waiting for the `Negotiation Response` message from the exchange.
        AwaitNegotiationResponse,

        /// Session is waiting for the `Establishment Acknowledgment` message from the exchange.
        AwaitEstablishmentAck,

        /// Session is waiting for the confirming `Terminate` message from the exchange.
        AwaitConfirmingTerminate,

        /// Session is fully established.
        Established,

        /// Session is trying to restore the telecommunication link.
        Reconnecting,

        /// Session is waiting for the message retransmission from the exchange.
        WaitForRetransmission,
    };

    /// \return the session state as a string.
    ONIXS_B3_BOE_EXPORTED static const std::string& toString(Enum state);
};

inline std::ostream & operator<<(std::ostream & o, SessionStateId::Enum state) {
    return o << SessionStateId::toString(state);
}

}
}
}
