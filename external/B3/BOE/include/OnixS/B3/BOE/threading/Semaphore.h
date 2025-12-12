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

/// Semaphore.
///
/// Limits number of threads that can access the shared resource simultaneously.
class ONIXS_B3_BOE_EXPORTED Semaphore
{
public:
    /// Constructor.
    ///
    /// The state of the semaphore is signaled
    /// when its counter is greater than zero and
    /// non-signaled when it is zero.
    ///
    /// \param count the counter value.
    Semaphore(unsigned int count = 1);

    ~Semaphore();

    /// Decrements the counter by one.
    ///
    /// If the counter is already zero,
    /// blocks the thread until the counter
    /// becomes greater than zero.
    void acquire();

    /// Tries to decrement the counter by one.
    ///
    /// \return `false' if the counter is already zero,
    /// otherwise - `true`.
    bool tryAcquire();

    /// Increments the counter by one.
    void release();

private:
    void * impl_;

    // Copying & assignment is prohibited.
    Semaphore(const Semaphore &);
    Semaphore & operator = (const Semaphore &);
};
}
}
}
}
