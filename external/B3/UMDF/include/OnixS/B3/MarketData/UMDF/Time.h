// Copyright Onix Solutions Limited [OnixS]. All rights reserved.
//
// This software owned by Onix Solutions Limited [OnixS] and is
// protected by copyright law and international copyright treaties.
//
// Access to and use of the software is governed by the terms of the applicable
// OnixS Software Services Agreement (the Agreement) and Customer end user license
// agreements granting a non-assignable, non-transferable and non-exclusive license
// to use the software for it's own data processing purposes under the terms defined
// in the Agreement.
//
// Except as otherwise granted within the terms of the Agreement, copying or
// reproduction of any part of this source code or associated reference material
// to any other location for further reproduction or redistribution, and any
// amendments to this copyright notice, are expressly prohibited.
//
// Any reproduction or redistribution for sale or hiring of the Software not in
// accordance with the terms of the Agreement is a violation of copyright law.
//
#pragma once

#include <string>
#include <algorithm>
#include <stdexcept>

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/Compiler.h>
#include <OnixS/B3/MarketData/UMDF/Integral.h>


namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                /// Miscellaneous time characteristics.
                struct TimeTraits
                {
                    /// Returns number of nanoseconds in single day.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int64 nanosecondsPerDay()
                    {
                        return 86400000000000ll;
                    }

                    /// Returns number of nanoseconds in single hour.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int64 nanosecondsPerHour()
                    {
                        return 3600000000000ll;
                    }

                    /// Returns number of nanoseconds in single minute.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int64 nanosecondsPerMinute()
                    {
                        return 60000000000ll;
                    }

                    /// Returns number of nanoseconds in single second.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 nanosecondsPerSecond()
                    {
                        return 1000000000;
                    }

                    /// Returns number of nanoseconds in single millisecond.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 nanosecondsPerMillisecond()
                    {
                        return 1000000;
                    }

                    /// Returns number of nanoseconds in single microsecond.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 nanosecondsPerMicrosecond()
                    {
                        return 1000;
                    }

                    /// Returns number of hours in single day.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 hoursPerDay()
                    {
                        return 24;
                    }

                    /// Returns number of minutes in single hour.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 minutesPerHour()
                    {
                        return 60;
                    }

                    /// Returns number of seconds in single minute.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 secondsPerMinute()
                    {
                        return 60;
                    }

                    /// Returns number of milliseconds in single second.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 millisecondsPerSecond()
                    {
                        return 1000;
                    }

                    /// Returns number of microseconds in single second.
                    ONIXS_B3_UMDF_MD_CONSTEXPR
                    static Int32 microsecondsPerSecond()
                    {
                        return 1000000;
                    }
                };

                /// Represents time interval. Used primarily to present time-only
                /// stamps and to measure time intervals between two timestamps.
                class TimeSpan
                {
                    public:
                    /// Integral type presenting internal ticks.
                    typedef Int64 Ticks;

                    /// Integral type for number of days.
                    typedef Int32 Days;

                    /// Integral type for number of hours.
                    typedef Int32 Hours;

                    /// Integral type for number of minutes.
                    typedef Int32 Minutes;

                    /// Integral type for number of seconds.
                    typedef Int32 Seconds;

                    /// Integral type for number of milliseconds.
                    typedef Int32 Milliseconds;

                    /// Integral type for number of microseconds.
                    typedef Int32 Microseconds;

                    /// Integral type for number of nanoseconds.
                    typedef Int32 Nanoseconds;

                    /// Initializes timespan from given number of ticks.
                    explicit TimeSpan(Ticks ticks = 0) ONIXS_B3_UMDF_MD_NOTHROW
                        : ticks_(ticks)
                    {
                    }

                    /// Initializes with given set of values.
                    ///
                    /// Input parameters are treated as quantities,
                    /// but not as a time stamp. Therefore, there's
                    /// no requirement to fit in a certain range like
                    /// hours must fit into [0, 24) range. After
                    /// initialization time span will be normalized.
                    TimeSpan(
                        Days days,
                        Hours hours,
                        Minutes minutes,
                        Seconds seconds,
                        Nanoseconds nanoseconds)
                        : ticks_(
                            static_cast<Ticks>(days) *
                            TimeTraits::nanosecondsPerDay() +
                            static_cast<Ticks>(hours) *
                            TimeTraits::nanosecondsPerHour() +
                            static_cast<Ticks>(minutes) *
                            TimeTraits::nanosecondsPerMinute() +
                            static_cast<Ticks>(seconds) *
                            TimeTraits::nanosecondsPerSecond() +
                            nanoseconds)
                    {
                    }

                    /// Initializes with given set of values.
                    ///
                    /// Input parameters are treated as quantities,
                    /// but not as a time stamp. Therefore, there's
                    /// no requirement to fit in a certain range like
                    /// hours must fit into [0, 24) range. After
                    /// initialization time span will be normalized.
                    TimeSpan(
                        Hours hours,
                        Minutes minutes,
                        Seconds seconds,
                        Nanoseconds nanoseconds)
                        : ticks_(
                            static_cast<Ticks>(hours) *
                            TimeTraits::nanosecondsPerHour() +
                            static_cast<Ticks>(minutes) *
                            TimeTraits::nanosecondsPerMinute() +
                            static_cast<Ticks>(seconds) *
                            TimeTraits::nanosecondsPerSecond() +
                            nanoseconds)
                    {
                    }

                    /// Days component of time interval.
                    /// Whole number of days in time interval.
                    Days days() const
                    {
                        return
                            static_cast<Days>
                            (ticks_ /
                             TimeTraits::nanosecondsPerDay());
                    }

                    /// Hours component of time interval.
                    /// Values are in range from -23 through 23.
                    Hours hours() const
                    {
                        return
                            static_cast<Hours>(
                                (ticks_ /
                                 TimeTraits::nanosecondsPerHour()) %
                                TimeTraits::hoursPerDay()
                            );
                    }

                    /// Minutes component of time interval.
                    /// Values are in range from -59 through 59.
                    Int32 minutes() const
                    {
                        return
                            static_cast<Minutes>(
                                (ticks_ /
                                 TimeTraits::nanosecondsPerMinute()) %
                                TimeTraits::minutesPerHour()
                            );
                    }

                    /// Seconds component of time interval.
                    /// Values are in range from -59 through 59.
                    Int32 seconds() const
                    {
                        return
                            static_cast<Seconds>(
                                (ticks_ /
                                 TimeTraits::nanosecondsPerSecond()) %
                                TimeTraits::secondsPerMinute()
                            );
                    }

                    /// Milliseconds component of time interval.
                    /// Values are in range from -999 through 999.
                    Milliseconds milliseconds() const
                    {
                        return
                            static_cast<Milliseconds>
                            ((ticks_ /
                              TimeTraits::nanosecondsPerMillisecond()) %
                             TimeTraits::millisecondsPerSecond()
                            );
                    }

                    /// Microseconds component of time interval.
                    /// Values are in range from -999999 through 999999.
                    Microseconds microseconds() const
                    {
                        return
                            static_cast<Microseconds>
                            ((ticks_ /
                              TimeTraits::nanosecondsPerMicrosecond()) %
                             TimeTraits::microsecondsPerSecond()
                            );
                    }

                    /// Nanoseconds component of time interval.
                    /// Values are in range from -999999999 through 999999999.
                    Nanoseconds nanoseconds() const
                    {
                        return
                            static_cast<Nanoseconds>
                            (ticks_ %
                             TimeTraits::nanosecondsPerSecond());
                    }

                    /// Number of ticks in given time interval.
                    ///
                    /// Ticks are the lowest time quantity used
                    /// to measure time intervals. In current
                    /// implementation ticks are nanoseconds.
                    Ticks ticks() const
                    {
                        return ticks_;
                    }

                    /// Adds time interval to current one.
                    TimeSpan&
                    operator +=(
                    const TimeSpan& other)
                    {
                        ticks_ += other.ticks_;
                        return *this;
                    }

                    /// Subtracts time interval from current one.
                    TimeSpan&
                    operator -=(
                    const TimeSpan& other)
                    {
                        ticks_ -= other.ticks_;
                        return *this;
                    }

                    /// Exchanges with given instance.
                    void
                    swap(TimeSpan& other)
                        ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        std::swap(ticks_, other.ticks_);
                    }

                    private:
                    Ticks ticks_;
                };

                /// Compares with other instance for equality.
                inline
                bool
                operator ==(
                    const TimeSpan& left,
                    const TimeSpan& right)
                {
                    return left.ticks() == right.ticks();
                }

                /// Compares with other instance for in-equality.
                inline
                bool
                operator !=(
                    const TimeSpan& left,
                    const TimeSpan& right)
                {
                    return left.ticks() != right.ticks();
                }

                /// Checks whether left time interval less than right one.
                inline
                bool
                operator <(
                    const TimeSpan& left,
                    const TimeSpan& right)
                {
                    return left.ticks() < right.ticks();
                }

                /// Checks whether left time interval greater than right one.
                inline
                bool
                operator >(
                    const TimeSpan& left,
                    const TimeSpan& right)
                {
                    return left.ticks() > right.ticks();
                }

                // TimeSpan serialization.

                // Serializes timespan according to HH:MM:SS pattern.
                ONIXS_B3_UMDF_MD_API
                void
                toStrAsHHMMSS(std::string&, TimeSpan);

                // Serializes timespan according to HH:MM:SS.sss pattern.
                ONIXS_B3_UMDF_MD_API
                void
                toStrAsHHMMSSmsec(std::string&, TimeSpan);

                // Serializes timespan according to D.HH:MM:SS.sssssssss pattern.
                ONIXS_B3_UMDF_MD_API
                void
                toStrAsSDHHMMSSnsec(std::string&, TimeSpan);

                /// Collection of timespan formatting patterns.
                struct TimeSpanFormat
                {
                    enum Enum
                    {
                        /// HH:MM:SS.
                        HHMMSS,

                            /// HH:MM:SS.sss.
                            HHMMSSmsec,

                            /// D.HH:MM:SS.sssssssss.
                            SDHHMMSSnsec
                    };
                };


                /// Appends timespan formatted in specified pattern to given string.
                inline
                void toStr(
                    std::string& str,
                    TimeSpan timeSpan,
                    TimeSpanFormat::Enum format =
                    TimeSpanFormat::SDHHMMSSnsec)
                {
                    switch (format)
                    {
                        case TimeSpanFormat::HHMMSS:
                            toStrAsHHMMSS(str, timeSpan);
                            break;

                        case TimeSpanFormat::HHMMSSmsec:
                            toStrAsHHMMSSmsec(str, timeSpan);
                            break;

                        case TimeSpanFormat::SDHHMMSSnsec:
                            toStrAsSDHHMMSSnsec(str, timeSpan);
                            break;

                        default:
                        {
                            throw std::invalid_argument(
                                "Unknown timespan format pattern specified. ");
                        }
                    }
                }

                /// Formats timespan according to specified pattern.
                inline
                std::string toStr(
                    TimeSpan timeSpan,
                    TimeSpanFormat::Enum format =
                    TimeSpanFormat::SDHHMMSSnsec)
                {
                    std::string str;

                    toStr(str, timeSpan, format);

                    return str;
                }

                /// Identifies months in year.
                struct Month
                {
                    enum Enum
                    {
                        January = 1,
                        February,
                        March,
                        April,
                        May,
                        June,
                        July,
                        August,
                        September,
                        October,
                        November,
                        December
                    };
                };

                /// Collection of timestamp formatting patterns.
                struct TimestampFormat
                {
                    enum Enum
                    {
                        /// YYYYMMDD.
                        YYYYMMDD,

                        /// YYYYMMDD-HH:MM:SS.
                        YYYYMMDDHHMMSS,

                        /// YYYYMMDD-HH:MM:SS.sss.
                        YYYYMMDDHHMMSSmsec,

                        /// YYYYMMDD-HH:MM:SS.sssssssss.
                        YYYYMMDDHHMMSSnsec
                    };
                };

                /// Represents time point without time-zone information.
                class Timestamp
                {
                    public:
                    /// Integral type storing internal ticks.
                    typedef UInt64 Ticks;

                    /// Integral type presenting year component.
                    typedef UInt32 Year;

                    /// Type presenting month component.
                    typedef
                    OnixS::B3::MarketData::UMDF::Month::Enum
                    Month;

                    /// Integral type presenting day component.
                    typedef UInt32 Day;

                    /// Integral type presenting hour component.
                    typedef UInt32 Hour;

                    /// Integral type presenting minute component.
                    typedef UInt32 Minute;

                    /// Integral type presenting second component.
                    typedef UInt32 Second;

                    /// Integral type presenting millisecond component.
                    typedef UInt32 Millisecond;

                    /// Integral type presenting microsecond component.
                    typedef UInt32 Microsecond;

                    /// Integral type presenting nanosecond component.
                    typedef UInt32 Nanosecond;

                    /// Returns current UTC time.
                    ONIXS_B3_UMDF_MD_API
                    static
                    Timestamp utcNow();

                    /// Returns current local time.
                    ONIXS_B3_UMDF_MD_API
                    static
                    Timestamp now();

                    /// Initializes from number of ticks since epoch.
                    explicit
                    Timestamp(
                        Ticks ticks = 0) ONIXS_B3_UMDF_MD_NOTHROW
                        : sinceEpoch_(ticks)
                    {
                    }

                    /// Explicit time-stamp initialization.
                    ///
                    /// Input parameters are validated, therefore
                    /// constructor throws exception if input values
                    /// do not fit into their valid ranges.
                    Timestamp(
                        Year year,
                        Month month,
                        Day day,
                        Hour hour = 0,
                        Minute minute = 0,
                        Second second = 0,
                        Nanosecond nanosecond = 0)
                        : sinceEpoch_(
                            toTicks(
                                year, month, day,
                                hour, minute, second, nanosecond)
                            )
                    {
                    }

                    /// Initializes as copy of other instance.
                    Timestamp(
                        const Timestamp& other)
                        : sinceEpoch_(other.sinceEpoch_)
                    {
                    }

                    /// Year component of given time point.
                    Year year() const
                    {
                        Year year; Month month; Day day;

                        toDate(sinceEpoch_, year, month, day);

                        return year;
                    }

                    /// Month component of given time point.
                    Month month() const
                    {
                        Year year; Month month; Day day;

                        toDate(sinceEpoch_, year, month, day);

                        return month;
                    }

                    /// Day component of given time point.
                    Day day() const
                    {
                        Year year; Month month; Day day;

                        toDate(sinceEpoch_, year, month, day);

                        return day;
                    }

                    /// Hour component of given time point.
                    Hour hour() const
                    {
                        return static_cast<Hour>(time().hours());
                    }

                    /// Minute component of given time point.
                    Minute minute() const
                    {
                        return static_cast<Minute>(time().minutes());
                    }

                    /// Second component of given time point.
                    Second second() const
                    {
                        return static_cast<Second>(time().seconds());
                    }

                    /// Millisecond component of given time point.
                    Millisecond millisecond() const
                    {
                        return static_cast<Millisecond>(time().milliseconds());
                    }

                    /// Microsecond component of given time point.
                    Microsecond microsecond() const
                    {
                        return static_cast<Microsecond>(time().microseconds());
                    }

                    /// Nanosecond component of given time point.
                    Nanosecond nanosecond() const
                    {
                        return static_cast<Nanosecond>(time().nanoseconds());
                    }

                    /// Timestamp without a time part.
                    Timestamp date() const
                    {
                        return
                            Timestamp(
                                sinceEpoch_ -
                                sinceEpoch_ %
                                TimeTraits::nanosecondsPerDay());
                    }

                    /// Time part of timestamp.
                    TimeSpan time() const
                    {
                        return
                            TimeSpan(
                                sinceEpoch_ %
                                TimeTraits::nanosecondsPerDay());
                    }

                    /// Number of nanoseconds since the Epoch (01-01-1970).
                    Ticks sinceEpoch() const
                        ONIXS_B3_UMDF_MD_NOTHROW
                    {
                        return sinceEpoch_;
                    }

                    /// Reinitializes as copy of given instance.
                    Timestamp&
                    operator =(
                    const Timestamp& other)
                    {
                        sinceEpoch_ = other.sinceEpoch_;

                        return *this;
                    }

                    /// Exchanges value with other instance.
                    void
                    swap(
                    Timestamp& other)
                    {
                        std::swap(
                            sinceEpoch_,
                            other.sinceEpoch_);
                    }

                    /// Parses timestamp from its numeric presentation (like 20201115)
                    /// only YYYYMMDD is supported
                    static
                    Timestamp
                    parse (
                        unsigned long long presentation,
                        TimestampFormat::Enum format = TimestampFormat::YYYYMMDD);

                private:
                    // Time interval in nanoseconds since the 01-01-1970.
                    Ticks sinceEpoch_;

                    // Converts structured date-time into ticks.
                    ONIXS_B3_UMDF_MD_API
                    static
                    Ticks toTicks(
                        Year, Month, Day,
                        Hour, Minute, Second,
                        Nanosecond);

                    // Extracts date components from ticks.
                    ONIXS_B3_UMDF_MD_API
                    static
                    void toDate(Ticks, Year&, Month&, Day&);
                };

                /// Create Timestamp from whole seconds since the Epoch
                inline
                Timestamp fromSeconds(UInt32 secondsSinceEpoch)
                {
                    return Timestamp(
                        static_cast<Timestamp::Ticks>(
                            secondsSinceEpoch) * TimeTraits::nanosecondsPerSecond());
                }

                /// Compares with instances for equality.
                inline
                bool
                operator ==(
                    const Timestamp& left,
                    const Timestamp& right)
                {
                    return (
                        left.sinceEpoch() ==
                        right.sinceEpoch()
                    );
                }

                /// Compares with instances for inequality.
                inline
                bool
                operator !=(
                    const Timestamp& left,
                    const Timestamp& right)
                {
                    return (
                        left.sinceEpoch() !=
                        right.sinceEpoch()
                    );
                }

                /// Establishes order between two instances.
                inline
                bool
                operator <(
                    const Timestamp& left,
                    const Timestamp& right)
                {
                    return (
                        left.sinceEpoch() <
                        right.sinceEpoch()
                    );
                }

                /// Establishes order between two instances.
                inline
                bool
                operator <=(
                    const Timestamp& left,
                    const Timestamp& right)
                {
                    return (
                        left.sinceEpoch() <=
                        right.sinceEpoch()
                    );
                }

                /// Establishes order between two instances.
                inline
                bool
                operator >(
                    const Timestamp& left,
                    const Timestamp& right)
                {
                    return (
                        left.sinceEpoch() >
                        right.sinceEpoch()
                    );
                }

                /// Establishes order between two instances.
                inline
                bool
                operator >=(
                    const Timestamp& left,
                    const Timestamp& right)
                {
                    return (
                        left.sinceEpoch() >=
                        right.sinceEpoch()
                    );
                }

                /// Adds time interval to given time point.
                inline
                Timestamp
                operator +(
                    const Timestamp& timestamp,
                    const TimeSpan& timeSpan)
                {
                    return
                        Timestamp(
                            timestamp.sinceEpoch() +
                            timeSpan.ticks()
                        );
                }

                /// Subtracts time interval from given time point.
                inline
                Timestamp
                operator -(
                    const Timestamp& timestamp,
                    const TimeSpan& timeSpan)
                {
                    return
                        Timestamp(
                            timestamp.sinceEpoch() -
                            timeSpan.ticks()
                        );
                }

                /// Calculates time interval between two time points.
                inline
                TimeSpan
                operator -(
                    const Timestamp& left,
                    const Timestamp& right)
                {
                    return
                        TimeSpan(
                            left.sinceEpoch() -
                            right.sinceEpoch()
                        );
                }

                // Serialization.

                /// Serializes timestamp in YYYYMMDD format.
                ONIXS_B3_UMDF_MD_API
                void
                toStrAsYYYYMMDD
                    (
                        std::string&,
                        Timestamp
                    );

                /// Serializes timestamp in YYYYMMDDHHMMSS format.
                ONIXS_B3_UMDF_MD_API
                void
                toStrAsYYYYMMDDHHMMSS
                    (
                        std::string&,
                        Timestamp
                    );

                /// Serializes timestamp in YYYYMMDDHHMMSSmsec format.
                ONIXS_B3_UMDF_MD_API
                void
                toStrAsYYYYMMDDHHMMSSmsec
                    (
                        std::string&,
                        Timestamp
                    );

                /// Serializes timestamp in YYYYMMDDHHMMSSnsec format.
                ONIXS_B3_UMDF_MD_API
                void
                toStrAsYYYYMMDDHHMMSSnsec
                    (
                        std::string&,
                        Timestamp
                    );

                /// Serializes timestamp according to specified pattern.
                ONIXS_B3_UMDF_MD_API
                void
                toStr(
                    std::string& str,
                    Timestamp timestamp,
                    TimestampFormat::Enum format =
                    TimestampFormat::YYYYMMDDHHMMSSnsec);

                /// Serializes timestamp according to specified pattern.
                inline
                std::string
                toStr(
                    Timestamp timestamp,
                    TimestampFormat::Enum format =
                    TimestampFormat::YYYYMMDDHHMMSSnsec)
                {
                    std::string str;

                    toStr(str, timestamp, format);

                    return str;
                }

                /// De-serializes a timestamp from the given string.
                ONIXS_B3_UMDF_MD_API
                bool
                fromStr(
                    Timestamp&,
                    const char*,
                    size_t);

                inline
                bool
                fromStr(
                    Timestamp& ts,
                    const std::string& str)
                {
                    return
                        fromStr(
                            ts, str.c_str(), str.size());
                }




            }
        }
    }
}
