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

#include <OnixS/B3/BOE/threading/Mutex.h>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Threading {

/// Condition variable - a synchronization objects that
/// allows threads to wait for certain events (conditions)
/// to occur.
///
/// Condition variable enables threads to atomically block
/// and test condition under protection of mutual exclusion
/// lock (Mutex) until condition is satisfied.
class ONIXS_B3_BOE_EXPORTED Condition
{
public:
    /// Initializes the instance.
    Condition();

    /// Destructs the instance.
    ~Condition();

    /// Signals one waiting thread.
    void signal();

    /// Signals all waiting threads.
    void signalAll();

    /// Blocks on a condition.
    ///
    /// \param lock Represents a reference to Mutex
    /// that is used to protect the condition testing.
    void wait(Mutex & lock);

private:
    void * impl_;

    // Copying & assignment is prohibited.
    Condition(const Condition &);
    Condition & operator = (const Condition &);
};
}
}
}
}
