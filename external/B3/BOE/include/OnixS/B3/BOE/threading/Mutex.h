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

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Threading {

/// Mutex.
///
/// Protects resources from simultaneous access by multiple threads.
///
/// Only one thread at a time can own instance of this class.
///
/// This implementation is optimized for locking threads that are in the same process.
///
/// \note It is NOT suitable for interprocess synchronization.
/// \note Recursive locking is NOT supported.
class ONIXS_B3_BOE_EXPORTED Mutex
{
public:
    friend ONIXS_B3_BOE_API_DECL(class, Condition);

    /// Initializes the instance.
    Mutex();

    /// Destructs the instance.
    ~Mutex();

    /// Acquires the lock ownership.
    ///
    /// If the mutex is already occupied by another thread
    /// blocks the current thread and waits until it
    /// will be released by the owner.
    void acquire();

    /// Tries to acquires the lock ownership.
    ///
    /// \return `false` if the mutex is already occupied by another thread,
    /// otherwise - `true`.
    bool tryAcquire();

    /// Releases the ownership (lock) and
    /// unblocks one of the waiting threads.
    void release();

private:
    void * impl_;

    // Copying & assignment is prohibited.
    Mutex(const Mutex &);
    Mutex & operator = (const Mutex &);
};
}
}
}
}
