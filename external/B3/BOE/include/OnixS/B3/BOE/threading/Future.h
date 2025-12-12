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

#include <OnixS/B3/BOE/ABI.h>

#if defined (ONIXS_B3_BOE_CXX11)
#  include <exception>
#endif

namespace OnixS {

namespace System {
class FutureSharedState;
}

namespace B3 {
namespace BOE {
namespace Threading {

/// State of a \c SharedFuture object (similar to std::future_status, @see http://en.cppreference.com/w/cpp/thread/future_status ).
struct FutureStatus
{
    enum Enum
    {
        /// the shared state is ready.
        ready,
        /// the shared state did not become ready before specified timeout duration has passed.
        timeout,
        /// the shared state contains a deferred function, so the result will be computed only when explicitly requested.
        deferred
    };
};

namespace Implementation {

class FutureHelper;

/// Base implementation of SharedFuture<T>.
class FutureBase
{
public:
    /// Check if a future instance is associated with an asynchronous result.
    ///
    /// Returns \c true if the *this has an associated asynchronous result, false otherwise.
    bool valid() const ONIXS_B3_BOE_NOTHROW {
        return state_ != ONIXS_B3_BOE_NULLPTR;
    }

    /// Returns \c true if the asynchronous result associated with this Future is ready
    /// (has a value or exception stored in the shared state), \c false otherwise.
    ///
    /// There are often situations where a \c get() call on a Future may not be a blocking call,
    /// or is only a blocking call under certain circumstances.
    /// This method gives the ability to test for early completion and allows us to avoid
    /// associating a continuation, which needs to be scheduled with some non-trivial overhead
    /// and near-certain loss of cache efficiency.
    ///
    /// @throw std::logic_error if this instance does not refer to a shared state.
    ONIXS_B3_BOE_EXPORTED bool is_ready() const;

    /// Returns \c true if the asynchronous result associated with this Future has a stored value,
    ///         \c false otherwise.
    ///
    /// @throw std::logic_error if this instance does not refer to a shared state.
    ONIXS_B3_BOE_EXPORTED bool has_value() const;

    /// Returns \c true if the asynchronous result associated with this Future has a stored exception,
    ///         \c false otherwise.
    ///
    /// @throw std::logic_error if this instance does not refer to a shared state.
    ONIXS_B3_BOE_EXPORTED bool has_exception() const;

#if defined (ONIXS_B3_BOE_CXX11)

    /// Returns the stored exception.
    ///
    /// @throw std::logic_error if this instance does not refer to a shared state.
    /// @throw std::logic_error if the operation has *not* finished with an error.
    ONIXS_B3_BOE_EXPORTED std::exception_ptr get_exception_ptr() const;

#endif

    enum { InfiniteTimeout = -1 };

    /// Waits for the result to become available during the timeout.
    ///
    /// \note Calling \c wait on the same Future from multiple threads is \e not safe;
    /// the intended use is for each thread that waits on the same shared state to have a \e copy of a Future.
    ///
    /// \throw std::logic_error if this instance does not refer to a shared state.
    ONIXS_B3_BOE_EXPORTED FutureStatus::Enum wait(int timeoutInMs) const;

protected:
    FutureBase()
        : state_() {}

    ONIXS_B3_BOE_EXPORTED FutureBase(const FutureBase & other) ONIXS_B3_BOE_NOTHROW;

    ONIXS_B3_BOE_EXPORTED FutureBase & operator=(const FutureBase & other) ONIXS_B3_BOE_NOTHROW;

#if defined (ONIXS_B3_BOE_CXX11)

    ONIXS_B3_BOE_EXPORTED FutureBase(FutureBase && other) ONIXS_B3_BOE_NOTHROW;

    ONIXS_B3_BOE_EXPORTED FutureBase & operator=(FutureBase && other) ONIXS_B3_BOE_NOTHROW;

#endif

    struct moving_init_t {};

    /// Initializes the instance with shared state.
    ONIXS_B3_BOE_EXPORTED FutureBase(const System::FutureSharedState * state) ONIXS_B3_BOE_NOTHROW;

    /// Initializes the instance with shared state.
    ONIXS_B3_BOE_EXPORTED FutureBase(const System::FutureSharedState * state, moving_init_t) ONIXS_B3_BOE_NOTHROW;

    /// Destroys a future object.
    ///
    /// If this is the last reference to the asynchronous result associated with *this (if any), then destroy that asynchronous result.
    ONIXS_B3_BOE_EXPORTED ~FutureBase() ONIXS_B3_BOE_NOTHROW;

    ONIXS_B3_BOE_EXPORTED void swap(FutureBase & other) ONIXS_B3_BOE_NOTHROW;

    ONIXS_B3_BOE_EXPORTED const void * getValuePtr() const;

    ONIXS_B3_BOE_EXPORTED void getVoid() const;

private:
    const System::FutureSharedState * state_;

    friend class FutureHelper;
};

template<typename T>
struct FutureGetReturn {
    typedef const T & Type;
};

template<>
struct FutureGetReturn<void> {
    typedef void Type;
};

}

/// Represents a future result of an asynchronous operation - a result that will eventually appear in the Future after
/// the processing is complete.
///
/// The class template Future provides a mechanism to access the result of \e asynchronous operations :
/// \li An asynchronous operation (e.g. created via Promise) can provide a Future object to the creator of that asynchronous
/// operation (e.g. via Promise::get_future).
/// \li The creator of the asynchronous operation can then use a variety of methods to query, wait for, or extract a value from Future.
/// These methods may block if the asynchronous operation has not yet provided a value.
/// \li When the asynchronous operation is ready to send a result to the creator, it can do so by modifying <em> shared state </em>
/// (e.g. via Promise::set_value) that is linked to the creator's Future.
///
/// Future is the synchronization object constructed around the \e receiving end of the Promise channel. It allows for the separation
/// of the initiation of an operation and the act of waiting for its result.
///
/// Future is \e copiable and multiple SharedFuture objects may refer to the same shared state.
///
/// Unlike std::future, this implementation has an extended API, allowing you to query the state of SharedFuture.
/// The internal implementation is lock-free; therefore, setting and polling states do not lead to blocking of threads and/or switching
/// of an execution context.
///
/// \note Access to the same shared state from multiple threads is safe if each thread does it through its own copy of
/// a SharedFuture object.
///
/// \see http://en.cppreference.com/w/cpp/thread/shared_future .
template <typename T>
class SharedFuture : public Implementation::FutureBase
{
public:
    SharedFuture() ONIXS_B3_BOE_NOTHROW
        : FutureBase() {}

    /// Copy constructor.
    SharedFuture(const SharedFuture<T> & other) ONIXS_B3_BOE_NOTHROW
        : FutureBase(other) {}

    /// Copy assignment.
    SharedFuture<T> & operator=(const SharedFuture<T> & other) ONIXS_B3_BOE_NOTHROW {
        FutureBase::operator=(other);
        return *this;
    }

#if defined (ONIXS_B3_BOE_CXX11)

    SharedFuture(SharedFuture<T> && other) ONIXS_B3_BOE_NOTHROW
        : FutureBase(std::move(other)) {}

    FutureBase & operator=(SharedFuture<T> && other) ONIXS_B3_BOE_NOTHROW {
        FutureBase::operator=(std::move(other));
        return *this;
    }

#endif

    /// Returns the result. If the result is not ready, the method will block. When completes, it either returns a value or throws an exception.
    ///
    /// This method waits until the Future has a valid result and retrieves it. It effectively calls wait() in order to wait for the result.
    ///
    /// \exception If an exception was stored in the shared state referenced by this Future (e.g. via a call to Promise::set_exception()) then that exception will be thrown.
    typename Implementation::FutureGetReturn<T>::Type get() const {
        return *reinterpret_cast<const T *>(getValuePtr());
    }

    /// swaps two SharedFuture objects
    void swap(SharedFuture<T> & other) ONIXS_B3_BOE_NOTHROW {
        FutureBase::swap(other);
    }

private:
    /// Initializes the instance with shared state.
    SharedFuture(const System::FutureSharedState * state)
        : FutureBase(state) {}

    /// Initializes the instance with shared state.
    SharedFuture(const System::FutureSharedState * state, moving_init_t t) ONIXS_B3_BOE_NOTHROW
        : FutureBase(state, t) {}

    friend class Implementation::FutureHelper;
};

template<>
inline void SharedFuture<void>::get() const {
    getVoid();
}

}
}
}
}
