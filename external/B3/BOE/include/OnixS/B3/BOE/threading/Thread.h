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

#include <set>

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/threading/Definitions.h>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Threading {

/// Logical processors that a thread is allowed to run on (first logical CPU has index 0).
typedef size_t CpuIndex;
typedef std::set < CpuIndex > CpuIndexes;

/// Represents set of CPU indices.
class ONIXS_B3_BOE_EXPORTED ThreadAffinity
{
public:

    /// Constructs thread affinity from the string presentation.
    /// Symbol ',' is used as the CPU index delimiter.
    explicit ThreadAffinity(const std::string & str);

    /// Destructs the instance.
    ~ThreadAffinity();

    /// Read-only access to index collection.
    const CpuIndexes & cpuIndexes() const;

    /// Collection of CPU indices.
    CpuIndexes & cpuIndexes();

    /// Serializes thread affinity to the string presentation.
    std::string toString();

private:
    ThreadAffinity(const ThreadAffinity &);
    ThreadAffinity & operator = (const ThreadAffinity &);

    CpuIndexes * indexes_;
};

/// Current thread related tasks.
class ONIXS_B3_BOE_EXPORTED ThisThread
{
public:
    /// Suspends the execution of the current thread for
    /// the given amount of time.
    static void sleep(unsigned int milliseconds);

    /// Executes a single instruction during the given number of microseconds.
    static void spinWait(unsigned int microseconds);

    /// Sets the processor affinity mask for the current thread.
    static void affinity(const CpuIndexes & cpuIndexes);

    /// Sets the processor affinity mask for the current thread.
    static void affinity(CpuIndex cpuIndex);

    /// Sets the priority for the current thread.
    static void priority(int priority);

    /// Sets the scheduling policy for the current thread.
    ///
    /// \note This method also sets the priority to the minimal value for the new policy,
    /// therefore, the priority should be set to a necessary value afterwards.
    static void policy(int policy);

    /// \return the platform identifier for the current thread.
    static ThreadId id();

    /// \return the processor number the current thread is running on during the call to this method.
    static unsigned int processorNumber();

private:
    ThisThread(const ThisThread &);
    ThisThread & operator = (const ThisThread &);
};

}
}
}
}
