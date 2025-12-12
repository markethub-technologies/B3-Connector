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
#include <OnixS/B3/BOE/TcpDirectAttr.h>
#include <OnixS/B3/BOE/threading/Thread.h>

#include <cassert>

namespace OnixS {
namespace B3 {
namespace BOE {

/**
* A high-level wrapper over the TCPDirect network stack.
*/
class ONIXS_B3_BOE_EXPORTED TcpDirectStack ONIXS_B3_BOE_FINAL : public SessionReactor
{
public:
    /** Allocates a stack with the supplied attributes.
    *
    * \param attr A set of properties to apply to the stack.
    *
    * A stack binds to a single network interface, specified by the `interface` attribute in @p attr.
    *
    * Relevant attributes to set in @p attr are those in the `zf_stack`,
    * `zf_pool` and `zf_vi` categories described in the attributes documentation.
    *
    * \throws std::bad_alloc Out of memory. N.B. TCPDirect API requires huge pages.
    * \throws std::runtime_error the TCPDirect library reported an error, see the error text.
    * \throws std::exception System call reported an error, see the error text.
    */
    explicit TcpDirectStack(const TcpDirectAttr & attr);

# if defined(ONIXS_B3_BOE_CXX11)
    TcpDirectStack(const TcpDirectStack &) = delete;
    TcpDirectStack & operator=(const TcpDirectStack &) = delete;
    TcpDirectStack(TcpDirectStack &&) = delete;
    TcpDirectStack & operator=(TcpDirectStack &&) = delete;
#endif

    ~TcpDirectStack() ONIXS_B3_BOE_OVERRIDE;

    /**
     * This function processes events on a stack and performs the necessary handling.
     *
     * These events, including transmit and receive events raised by the hardware,
     * and also software events such as TCP and FIXP timers.
     *
     * Please see the "Stack polling" section in the TCPDirect User Guide for further information.
     */
    void dispatchEvents() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        assert(workingThreadId() == Threading::ThisThread::id());
        dispatchEventsImpl();
    }

    /** \return a boolean value indicating whether a stack is quiescent.
     *
     * This can be used to ensure that all connections have been closed gracefully before destroying a stack
     * (or exiting the application). Destroying a stack while it is not quiescent is permitted by the API,
     * but when doing so there is no guarantee that sent data has been acknowledged by the peer or even transmitted,
     * and there is the possibility that peers' connections will be reset.
     *
     * \note When using the Windows TCPDirect emulator, destroying a stack while it is not quiescent may cause a memory leak.
     */
    bool isQuiescent() const ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        assert(workingThreadId() == Threading::ThisThread::id());
        return isQuiescentImpl();
    }

    /// \return The Id of the thread that created the stack.
    Threading::ThreadId workingThreadId() const ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        return workingThreadId_;
    }

    ReactorType::Enum type() const ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE {
        return ReactorType::TcpDirect;
    }

private:
    void dispatchEventsImpl() ONIXS_B3_BOE_NOTHROW;

    bool isQuiescentImpl() const ONIXS_B3_BOE_NOTHROW;

    class Impl;
    Impl * const impl_;

    Threading::ThreadId const workingThreadId_;

# if !defined(ONIXS_B3_BOE_CXX11)
    TcpDirectStack(const TcpDirectStack &);
    TcpDirectStack & operator=(const TcpDirectStack &);
#endif

    friend class SessionImpl;
};

}
}
}
