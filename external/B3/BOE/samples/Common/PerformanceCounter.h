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

#include <iosfwd>

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#endif

/// High-resolution performance counter.
class PerformanceCounter
{
public:
#ifdef _WIN32
    typedef LARGE_INTEGER Count;
#else
    typedef timespec Count;
#endif

    static void setToUndefinedValue(Count * value);

    static bool isUndefinedValue(const Count & value);

    /// Retrieves the current value of the high-resolution performance counter.
    static Count current();

    static void current(Count * result) ONIXS_B3_BOE_NOTHROW;

    typedef long long Span;

    static Span nsSpan(const PerformanceCounter::Count & stop,
                       const PerformanceCounter::Count & start);

    static Span usSpan(const PerformanceCounter::Count & stop,
                       const PerformanceCounter::Count & start);

    static Span elapsedNanoseconds(const PerformanceCounter::Count & start);

    static Span elapsedMicroseconds(const PerformanceCounter::Count & start);

private:
#ifdef _WIN32
    typedef LARGE_INTEGER Frequency;
    static Frequency frequency_;
#endif
};

std::ostream & operator<< (std::ostream & os, const PerformanceCounter::Count & value);

inline bool operator == (const PerformanceCounter::Count & left,
                         const PerformanceCounter::Count & right)
{
#ifdef _WIN32
    return (left.LowPart == right.LowPart && left.HighPart == right.HighPart);
#else
    return (left.tv_nsec == right.tv_nsec && left.tv_sec == right.tv_sec);
#endif
}

inline bool operator != (const PerformanceCounter::Count & left,
                         const PerformanceCounter::Count & right)
{
    return !(left == right);
}


inline
PerformanceCounter::Span PerformanceCounter::nsSpan(const PerformanceCounter::Count & stop,
                                                    const PerformanceCounter::Count & start)
{
#ifdef _WIN32
    return static_cast<PerformanceCounter::Span>((stop.QuadPart - start.QuadPart) * 1000000000.0 /
                                      frequency_.QuadPart);
#else
    return static_cast<PerformanceCounter::Span>((stop.tv_sec - start.tv_sec) * 1000000000 +
                                      (stop.tv_nsec - start.tv_nsec));
#endif
}

inline
PerformanceCounter::Span PerformanceCounter::usSpan(const PerformanceCounter::Count & stop,
                                                    const PerformanceCounter::Count & start)
{
#ifdef _WIN32
    return static_cast<PerformanceCounter::Span>((stop.QuadPart - start.QuadPart) * 1000000.0 /
                                      frequency_.QuadPart);
#else
    return static_cast<PerformanceCounter::Span>((stop.tv_sec - start.tv_sec) * 1000000 +
                                      (stop.tv_nsec - start.tv_nsec) / 1000);
#endif
}

inline
PerformanceCounter::Span PerformanceCounter::elapsedNanoseconds(const
        PerformanceCounter::Count & start)
{
    return PerformanceCounter::nsSpan(PerformanceCounter::current(), start);
}

inline
PerformanceCounter::Span PerformanceCounter::elapsedMicroseconds(const
        PerformanceCounter::Count & start)
{
    return PerformanceCounter::usSpan(PerformanceCounter::current(), start);
}

inline void PerformanceCounter::setToUndefinedValue(Count * value)
{
#ifdef _WIN32
    value->LowPart = 0;
    value->HighPart = 0;
#else
    value->tv_sec = 0;
    value->tv_nsec = 0;
#endif
}

inline bool PerformanceCounter::isUndefinedValue(const Count & value)
{
#ifdef _WIN32
    return (0 == value.LowPart && 0 == value.HighPart);
#else
    return (0 == value.tv_sec && 0 == value.tv_nsec);
#endif
}

ONIXS_B3_BOE_HOTPATH
inline void PerformanceCounter::current(PerformanceCounter::Count * result) ONIXS_B3_BOE_NOTHROW
{
#ifdef _WIN32
    ::QueryPerformanceCounter(result);
#else
    clock_gettime(CLOCK_MONOTONIC, result);
#endif

}

inline PerformanceCounter::Count PerformanceCounter::current()
{
    Count result;
    current(&result);
    return result;
}
