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

#include <OnixS/B3/BOE/threading/Definitions.h>

namespace OnixS {
namespace B3 {
namespace BOE {

/// Network reactor type.
struct ReactorType {
    enum Enum {
        /// Undefined reactor.
        Undefined = 0,

        /// Solarflare TCPDirect reactor.
        TcpDirect = 1,

        /// Standard TCP reactor.
        TcpStandard = 2
    };
};

/// Session's network stack reactor interface.
class ONIXS_B3_BOE_EXPORTED SessionReactor
{
public:
    /// Destructor.
    virtual ~SessionReactor() ONIXS_B3_BOE_DEFAULT;

    /// Processes events on a stack and performs the necessary handling.
    ///
    /// These events, including transmit and receive events raised by the hardware,
    /// and also software events such as TCP and FIXP protocol timers.
    virtual void dispatchEvents() = 0;

    /// \return a boolean value indicating whether a stack is quiescent.
    virtual bool isQuiescent() const = 0;

    /// \return the ID of the thread that created the stack.
    virtual Threading::ThreadId workingThreadId() const ONIXS_B3_BOE_NOTHROW = 0;

    /// \return the type of the stack.
    virtual ReactorType::Enum type() const ONIXS_B3_BOE_NOTHROW = 0;
};
}
}
}
