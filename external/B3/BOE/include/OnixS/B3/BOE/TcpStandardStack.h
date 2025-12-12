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

#include <OnixS/B3/BOE/SessionReactor.h>
#include <OnixS/B3/BOE/threading/Thread.h>

namespace OnixS {
namespace B3 {
namespace BOE {

/**
 * A high-level wrapper over the TCP standard stack.
 */
class ONIXS_B3_BOE_EXPORTED TcpStandardStack ONIXS_B3_BOE_FINAL : public SessionReactor
{
public:
    /**
    * Allocates a TCP stack.
    */
    TcpStandardStack();

#if defined(ONIXS_B3_BOE_CXX11)
    TcpStandardStack(const TcpStandardStack &) = delete;
    TcpStandardStack(TcpStandardStack &&) = delete;

    TcpStandardStack & operator=(const TcpStandardStack &) = delete;
    TcpStandardStack & operator=(TcpStandardStack &&) = delete;
#endif

    ~TcpStandardStack() ONIXS_B3_BOE_OVERRIDE;

    /**
     * Processes events on a stack and performs the necessary handling.
     *
     * These events, including transmit and receive events raised by the hardware,
     * and also software events such as TCP and FIXP protocol timers.
     *
     */
    void dispatchEvents() ONIXS_B3_BOE_OVERRIDE {
        dispatchEventsImpl();
    }

    /**
    * \return a boolean value indicating whether a stack is quiescent.
     *
     * This can be used to ensure that all connections have been closed gracefully before destroying a stack
     * (or exiting the application). Destroying a stack while it is not quiescent is permitted by the API,
     * but when doing so there is no guarantee that sent data has been acknowledged by the peer or even transmitted,
     * and there is the possibility that peers' connections will be reset.
     */
    bool isQuiescent() const ONIXS_B3_BOE_OVERRIDE {
        return isQuiescentImpl();
    }

    /**
     * \return the ID of the thread that created the stack.
     */
    Threading::ThreadId workingThreadId() const ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        return threadId_;
    }

    ReactorType::Enum type() const ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        return ReactorType::TcpStandard;
    }

private:
    void dispatchEventsImpl();

    bool isQuiescentImpl() const;

    class Impl;
    Impl * const impl_;

    Threading::ThreadId const threadId_;

#if !defined(ONIXS_B3_BOE_CXX11)
    TcpStandardStack(const TcpStandardStack &);
    TcpStandardStack & operator=(const TcpStandardStack &);
#endif

    friend class SessionImpl;
};

}}}
