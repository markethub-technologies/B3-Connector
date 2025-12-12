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

#include <OnixS/B3/MarketData/UMDF/ABI.h>

#include <string>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                /// Defines the state that the handler is in.
                struct HandlerState
                {
                    /// @copydoc HandlerState
                    enum Enum
                    {
                        Stopped,  ///< Stopped.
                        Stopping, ///< The intermediate state when the Handler is not Stopped but not Started.
                        Started,     ///< Started.
                        Starting,    ///< The intermediate state when the Handler is not Started but not Stopped.
                    };
                };

                /// Returns string representation of HandlerState value.
                ONIXS_B3_UMDF_MD_API std::string enumToString (HandlerState::Enum);

                /// Status Listener.
                class HandlerStateListener
                {
                    public:
                        /// Implement this member to get notifications about the handler state change.
                        virtual void onStateChanged (HandlerState::Enum newState) = 0;

                    protected:
                        /// Disables public <b>delete</b> operator in the interface class.
                        virtual ~HandlerStateListener () {}
                };
            }
        }
    }
}
