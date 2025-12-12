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

#include <OnixS/B3/BOE/messaging/Utils.h>
#include <OnixS/B3/BOE/messaging/Integral.h>

#include <stdexcept>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Miscellaneous time characteristics.
ONIXS_B3_BOE_LTWT_STRUCT TimeTraits
{
    /// \return the number of nanoseconds in a day.
    ONIXS_B3_BOE_CONSTEXPR
    static Int64 nanosecondsPerDay() ONIXS_B3_BOE_NOTHROW
    {
        return 86400000000000ll;
    }

    /// \return the number of nanoseconds in an hour.
    ONIXS_B3_BOE_CONSTEXPR
    static Int64 nanosecondsPerHour() ONIXS_B3_BOE_NOTHROW
    {
        return 3600000000000ll;
    }

    /// \return the number of nanoseconds in a minute.
    ONIXS_B3_BOE_CONSTEXPR
    static Int64 nanosecondsPerMinute() ONIXS_B3_BOE_NOTHROW
    {
        return 60000000000ll;
    }

    /// \return the number of nanoseconds in a second.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 nanosecondsPerSecond() ONIXS_B3_BOE_NOTHROW
    {
        return 1000000000;
    }

    /// \return the number of nanoseconds in a millisecond.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 nanosecondsPerMillisecond() ONIXS_B3_BOE_NOTHROW
    {
        return 1000000;
    }

    /// \return the number of nanoseconds in a microsecond.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 nanosecondsPerMicrosecond() ONIXS_B3_BOE_NOTHROW
    {
        return 1000;
    }

    /// \return the number of hours in a day.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 hoursPerDay() ONIXS_B3_BOE_NOTHROW
    {
        return 24;
    }

    /// \return the number of minutes in an hour.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 minutesPerHour() ONIXS_B3_BOE_NOTHROW
    {
        return 60;
    }

    /// \return the number of seconds in a minute.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 secondsPerMinute() ONIXS_B3_BOE_NOTHROW
    {
        return 60;
    }

    /// \return the number of milliseconds in a second.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 millisecondsPerSecond() ONIXS_B3_BOE_NOTHROW
    {
        return 1000;
    }

    /// \return the number of microseconds in a second.
    ONIXS_B3_BOE_CONSTEXPR
    static Int32 microsecondsPerSecond() ONIXS_B3_BOE_NOTHROW
    {
        return 1000000;
    }
};

/// Timespan formatting patterns.
ONIXS_B3_BOE_LTWT_STRUCT TimeSpanFormat
{
    enum Enum
    {
        /// Indicates a time span in the "HH:MM:SS" format.
        /// Used to represent a day time.
        HHMMSS,

        /// Indicates a time span in the "HH:MM:SS.sss" format.
        /// Used to represent a day time.
        HHMMSSmsec,

        /// Indicates a time span in the "HH:MM:SS.ssssss" format.
        /// Used to represent a day time.
        HHMMSSusec,

        /// Indicates a time span in the "HH:MM:SS.sssssssss" format.
        /// Used to represent a day time.
        HHMMSSnsec,

        /// Indicates a time span in the "HH:MM:SS.ssssssssssss" format.
        /// Used to represent a day time.
        HHMMSSpsec,

        /// Indicates a time span in the "D.HH:MM:SS.sssssssss" format.
        /// Used to represent a time interval.
        SDHHMMSSnsec
    };
};

/// Time interval.
///
/// Used primarily to present time-only stamps and to time intervals between two timestamps.
ONIXS_B3_BOE_LTWT_CLASS TimeSpan
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

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString(TimeSpanFormat::Enum = TimeSpanFormat::SDHHMMSSnsec) const;

    /// Initializes the timespan from the given number of ticks.
    explicit TimeSpan(Ticks ticks = 0) ONIXS_B3_BOE_NOTHROW
        : ticks_(ticks)
    {
    }

    /// Initializes with the given set of values.
    ///
    /// Input parameters are treated as quantities,
    /// but not as a time stamp. Therefore, there's
    /// no requirement to fit in a certain range like
    /// hours must fit into [0, 24) range. After
    /// initialization time span will be normalized.
    TimeSpan(Days days, Hours hours, Minutes minutes, Seconds seconds, Nanoseconds nanoseconds) ONIXS_B3_BOE_NOTHROW
        : ticks_(
            numericCast<Ticks>(days) *
            TimeTraits::nanosecondsPerDay() +
            numericCast<Ticks>(hours) *
            TimeTraits::nanosecondsPerHour() +
            numericCast<Ticks>(minutes) *
            TimeTraits::nanosecondsPerMinute() +
            numericCast<Ticks>(seconds) *
            TimeTraits::nanosecondsPerSecond() +
            nanoseconds)
    {
    }

    /// Initializes with the given set of values.
    ///
    /// Input parameters are treated as quantities,
    /// but not as a time stamp. Therefore, there's
    /// no requirement to fit in a certain range like
    /// hours must fit into [0, 24) range. After
    /// initialization time span will be normalized.
    TimeSpan(Hours hours, Minutes minutes, Seconds seconds, Nanoseconds nanoseconds) ONIXS_B3_BOE_NOTHROW
        : ticks_(
            numericCast<Ticks>(hours) *
            TimeTraits::nanosecondsPerHour() +
            numericCast<Ticks>(minutes) *
            TimeTraits::nanosecondsPerMinute() +
            numericCast<Ticks>(seconds) *
            TimeTraits::nanosecondsPerSecond() +
            nanoseconds)
    {
    }

    /// \return the Days component of the time interval.
    Days days() const ONIXS_B3_BOE_NOTHROW
    {
        return
            numericCast<Days>
            (ticks_ /
                TimeTraits::nanosecondsPerDay());
    }

    /// \return the Hours component of the time interval.
    ///
    /// Values are in range from `-23` through `23`.
    Hours hours() const ONIXS_B3_BOE_NOTHROW
    {
        return
            numericCast<Hours>(
                (ticks_ /
                    TimeTraits::nanosecondsPerHour()) %
                TimeTraits::hoursPerDay()
            );
    }

    /// \return the Minutes component of the time interval.
    ///
    /// Values are in range from `-59` through `59`.
    Minutes minutes() const ONIXS_B3_BOE_NOTHROW
    {
        return
            numericCast<Minutes>(
                (ticks_ /
                    TimeTraits::nanosecondsPerMinute()) %
                TimeTraits::minutesPerHour()
            );
    }

    /// \return the Seconds component of the time interval.
    ///
    /// Values are in range from `-59` through `59`.
    Seconds seconds() const ONIXS_B3_BOE_NOTHROW
    {
        return
            numericCast<Seconds>(
                (ticks_ /
                    TimeTraits::nanosecondsPerSecond()) %
                TimeTraits::secondsPerMinute()
            );
    }

    /// \return the Milliseconds component of the time interval.
    ///
    /// Values are in range from `-999` through `999`.
    Milliseconds milliseconds() const ONIXS_B3_BOE_NOTHROW
    {
        return
            numericCast<Milliseconds>
                ((ticks_ /
                    TimeTraits::nanosecondsPerMillisecond()) %
                TimeTraits::millisecondsPerSecond()
            );
    }

    /// \return the Microseconds component of the time interval.
    ///
    /// Values are in range from `-999999` through `999999`.
    Microseconds microseconds() const ONIXS_B3_BOE_NOTHROW
    {
        return
            numericCast<Microseconds>
                ((ticks_ /
                    TimeTraits::nanosecondsPerMicrosecond()) %
                TimeTraits::microsecondsPerSecond()
            );
    }

    /// \return the Nanoseconds component of the time interval.
    ///
    /// Values are in range from `-999999999` through `999999999`.
    Nanoseconds nanoseconds() const ONIXS_B3_BOE_NOTHROW
    {
        return
            numericCast<Nanoseconds>
            (ticks_ %
                TimeTraits::nanosecondsPerSecond());
    }

    /// \return the number of ticks in the time interval.
    ///
    /// Ticks are the lowest time quantity used to measure time intervals.
    /// In the current implementation ticks are nanoseconds.
    Ticks ticks() const ONIXS_B3_BOE_NOTHROW
    {
        return ticks_;
    }

    /// Adds the given time interval.
    TimeSpan& operator+=(const TimeSpan& other) ONIXS_B3_BOE_NOTHROW
    {
        ticks_ += other.ticks_;

        return *this;
    }

    /// Subtracts the given time interval.
    TimeSpan& operator-=(const TimeSpan& other) ONIXS_B3_BOE_NOTHROW
    {
        ticks_ -= other.ticks_;

        return *this;
    }

    /// Swaps.
    void swap(TimeSpan & other) ONIXS_B3_BOE_NOTHROW
    {
        std::swap(ticks_, other.ticks_);
    }

    /// De-serializes the timespan from the given string according to the specified pattern.
    ///
    /// @throw std::runtime_error if the de-serialization is impossible.
    static TimeSpan fromStr(const std::string&);

private:
    Ticks ticks_;
};

/// Compares Timespans.
ONIXS_B3_BOE_PURE
inline bool operator==(const TimeSpan& left, const TimeSpan& right) ONIXS_B3_BOE_NOTHROW
{
    return left.ticks() == right.ticks();
}

/// Compares Timespans.
ONIXS_B3_BOE_PURE
inline bool operator!=(const TimeSpan& left, const TimeSpan& right) ONIXS_B3_BOE_NOTHROW
{
    return left.ticks() != right.ticks();
}

/// Compares Timespans.
ONIXS_B3_BOE_PURE
inline bool operator<(const TimeSpan& left, const TimeSpan& right) ONIXS_B3_BOE_NOTHROW
{
    return left.ticks() < right.ticks();
}

/// Compares Timespans.
ONIXS_B3_BOE_PURE
inline bool operator>(const TimeSpan& left, const TimeSpan& right) ONIXS_B3_BOE_NOTHROW
{
    return left.ticks() > right.ticks();
}

/// Changes the sign of the Timestamp.
ONIXS_B3_BOE_PURE
inline TimeSpan operator - (const TimeSpan& timeSpan) ONIXS_B3_BOE_NOTHROW
{
    return TimeSpan(-timeSpan.ticks());
}

/// Serializes the timespan according to the HH:MM:SS pattern.
ONIXS_B3_BOE_EXPORTED
void toStrAsHHMMSS(std::string&, TimeSpan);

/// Serializes the timespan according to the  HH:MM:SS.sss pattern.
ONIXS_B3_BOE_EXPORTED
void toStrAsHHMMSSmsec(std::string&, TimeSpan);

/// Serializes the timespan according to the HH:MM:SS.ssssss pattern.
ONIXS_B3_BOE_EXPORTED
void toStrAsHHMMSSusec(std::string&, TimeSpan);

/// Serializes the timespan according to the HH:MM:SS.sssssssss pattern.
ONIXS_B3_BOE_EXPORTED
void toStrAsHHMMSSnsec(std::string&, TimeSpan);

/// Serializes the timespan according to the HH:MM:SS.ssssssssssss pattern.
ONIXS_B3_BOE_EXPORTED
void toStrAsHHMMSSpsec(std::string&, TimeSpan);

/// Serializes the timespan according to the D.HH:MM:SS.sssssssss pattern.
ONIXS_B3_BOE_EXPORTED
void toStrAsSDHHMMSSnsec(std::string&, TimeSpan);

/// Appends the timespan.
ONIXS_B3_BOE_EXPORTED
void toStr(std::string&, TimeSpan, TimeSpanFormat::Enum = TimeSpanFormat::SDHHMMSSnsec);

/// Formats the timespan.
inline
std::string toStr(TimeSpan timeSpan, TimeSpanFormat::Enum format = TimeSpanFormat::SDHHMMSSnsec)
{
    std::string str;

    toStr(str, timeSpan, format);

    return str;
}

/// The months in year.
ONIXS_B3_BOE_LTWT_STRUCT Month
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

/// Timestamp formatting patterns.
ONIXS_B3_BOE_LTWT_STRUCT TimestampFormat
{
    enum Enum
    {
        /// YYYYMMDD.
        YYYYMMDD,

        /// YYYYMMDD-HH:MM:SS.
        YYYYMMDDHHMMSS,

        /// YYYYMMDD-HH:MM:SS.sss.
        YYYYMMDDHHMMSSmsec,

        /// Indicates timestamp in "YYYYMMDD-HH:MM:SS.ssssss" format.
        YYYYMMDDHHMMSSusec,

        /// YYYYMMDD-HH:MM:SS.sssssssss.
        YYYYMMDDHHMMSSnsec,

        /// Indicates timestamp in "YYYYMMDD-HH:MM:SS.ssssssssssss" format.
        YYYYMMDDHHMMSSpsec
    };
};

/// The time point without the time-zone information.
ONIXS_B3_BOE_LTWT_CLASS Timestamp
{
public:
    /// Integral type storing internal ticks.
    typedef UInt64 Ticks;

    /// Integral type presenting the year component.
    typedef UInt32 Year;

    /// Type presenting the month component.
    typedef
    OnixS::B3::BOE::Messaging::Month::Enum
    Month;

    /// Integral type presenting the day component.
    typedef UInt32 Day;

    /// Integral type presenting the hour component.
    typedef UInt32 Hour;

    /// Integral type presenting the minute component.
    typedef UInt32 Minute;

    /// Integral type presenting the second component.
    typedef UInt32 Second;

    /// Integral type presenting the millisecond component.
    typedef UInt32 Millisecond;

    /// Integral type presenting the microsecond component.
    typedef UInt32 Microsecond;

    /// Integral type presenting the nanosecond component.
    typedef UInt32 Nanosecond;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString(TimestampFormat::Enum = TimestampFormat::YYYYMMDDHHMMSSnsec) const;

    /// Initializes from the number of ticks since epoch.
    explicit Timestamp(Ticks ticks = 0) ONIXS_B3_BOE_NOTHROW
        : sinceEpoch_(ticks)
    {
    }

    /// Explicit time-stamp initialization.
    ///
    /// Input parameters are validated, therefore constructor throws an exception if input values do not fit into their valid ranges.
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

    Timestamp(const Timestamp& other) ONIXS_B3_BOE_NOTHROW
        : sinceEpoch_(other.sinceEpoch_)
    {
    }

    /// \return the Year component.
    Year year() const
    {
        Year year; Month month; Day day;

        toDate(sinceEpoch_, year, month, day);

        return year;
    }

    /// \return the Month component.
    Month month() const
    {
        Year year; Month month; Day day;

        toDate(sinceEpoch_, year, month, day);

        return month;
    }

    /// \return Day component
    Day day() const
    {
        Year year; Month month; Day day;

        toDate(sinceEpoch_, year, month, day);

        return day;
    }

    /// \return the Hour component
    Hour hour() const ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<Hour>(time().hours());
    }

    /// \return the Minute component.
    Minute minute() const ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<Minute>(time().minutes());
    }

    /// \return the Second component.
    Second second() const ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<Second>(time().seconds());
    }

    /// \return the Millisecond component.
    Millisecond millisecond() const ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<Millisecond>(time().milliseconds());
    }

    /// \return the Microsecond component.
    Microsecond microsecond() const ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<Microsecond>(time().microseconds());
    }

    /// \return the Nanosecond component.
    Nanosecond nanosecond() const ONIXS_B3_BOE_NOTHROW
    {
        return static_cast<Nanosecond>(time().nanoseconds());
    }

    /// \return the Timestamp without a time part.
    Timestamp date() const ONIXS_B3_BOE_NOTHROW
    {
        return
            Timestamp(
                sinceEpoch_ -
                    sinceEpoch_ %
                    TimeTraits::nanosecondsPerDay());
    }

    /// \return the Time part of timestamp.
    TimeSpan time() const ONIXS_B3_BOE_NOTHROW
    {
        return
            TimeSpan(
                sinceEpoch_ %
                TimeTraits::nanosecondsPerDay());
    }

    /// \return the number of nanoseconds since the Epoch (01-01-1970).
    Ticks sinceEpoch() const ONIXS_B3_BOE_NOTHROW
    {
        return sinceEpoch_;
    }

    Timestamp& operator=(const Timestamp& other) ONIXS_B3_BOE_NOTHROW
    {
        sinceEpoch_ = other.sinceEpoch_;

        return *this;
    }

    /// Exchanges the value.
    void swap(Timestamp & other) ONIXS_B3_BOE_NOTHROW
    {
        std::swap(sinceEpoch_, other.sinceEpoch_);
    }

    /// De-serializes a timestamp from the given string.
    ///
    /// @throw std::runtime_error if the de-serialization is impossible.
    static Timestamp fromStr(const std::string&, TimestampFormat::Enum = TimestampFormat::YYYYMMDDHHMMSSnsec);

private:
    /// Time interval in nanoseconds since the 01-01-1970.
    Ticks sinceEpoch_;

    /// Converts structured date-time into ticks.
    ONIXS_B3_BOE_EXPORTED
    static Ticks toTicks(Year, Month, Day, Hour, Minute, Second, Nanosecond);

    // Extracts the ddate components from ticks.
    ONIXS_B3_BOE_LTWT_EXPORTED
    static void toDate(Ticks, Year&, Month&, Day&);
};

/// Make Timestamp helper.
ONIXS_B3_BOE_PURE
inline Timestamp makeTimestamp(Timestamp::Ticks  ticks) ONIXS_B3_BOE_NOTHROW
{
    return Timestamp(ticks);
}

/// Compares instances.
ONIXS_B3_BOE_PURE
inline bool operator==(const Timestamp& left, const Timestamp& right) ONIXS_B3_BOE_NOTHROW
{
    return (
        left.sinceEpoch() ==
        right.sinceEpoch()
    );
}

/// Compares instances.
ONIXS_B3_BOE_PURE
inline bool operator!=(const Timestamp& left, const Timestamp& right) ONIXS_B3_BOE_NOTHROW
{
    return (
        left.sinceEpoch() !=
        right.sinceEpoch()
    );
}

/// Compares instances.
ONIXS_B3_BOE_PURE
inline bool operator<(const Timestamp& left, const Timestamp& right) ONIXS_B3_BOE_NOTHROW
{
    return (
        left.sinceEpoch() <
        right.sinceEpoch()
    );
}

/// Compares instances.
ONIXS_B3_BOE_PURE
inline bool operator<=(const Timestamp& left, const Timestamp& right) ONIXS_B3_BOE_NOTHROW
{
    return (
        left.sinceEpoch() <=
        right.sinceEpoch()
    );
}

/// Compares instances.
ONIXS_B3_BOE_PURE
inline bool operator>(const Timestamp& left, const Timestamp& right) ONIXS_B3_BOE_NOTHROW
{
    return (
        left.sinceEpoch() >
        right.sinceEpoch()
    );
}

/// Compares instances.
ONIXS_B3_BOE_PURE
inline bool operator>=(const Timestamp& left, const Timestamp& right) ONIXS_B3_BOE_NOTHROW
{
    return (
        left.sinceEpoch() >=
        right.sinceEpoch()
    );
}

/// Adds the time interval.
ONIXS_B3_BOE_PURE
inline Timestamp operator +(const Timestamp& timestamp, const TimeSpan& timeSpan) ONIXS_B3_BOE_NOTHROW
{
    return
        Timestamp(
            timestamp.sinceEpoch() +
            timeSpan.ticks()
        );
}

/// Subtracts the time interval.
ONIXS_B3_BOE_PURE
inline Timestamp operator -(const Timestamp& timestamp, const TimeSpan& timeSpan) ONIXS_B3_BOE_NOTHROW
{
    return
        Timestamp(
            timestamp.sinceEpoch() -
            timeSpan.ticks()
        );
}

/// Calculates the time interval between two time points.
ONIXS_B3_BOE_PURE
inline TimeSpan operator -(const Timestamp& left, const Timestamp& right) ONIXS_B3_BOE_NOTHROW
{
    return TimeSpan(left.sinceEpoch() - right.sinceEpoch());
}

/// Serializes the timestamp using the YYYYMMDD format.
ONIXS_B3_BOE_EXPORTED
void toStrAsYYYYMMDD(std::string&, Timestamp);

/// Serializes the timestamp using the YYYYMMDDHHMMSS format.
ONIXS_B3_BOE_EXPORTED
void toStrAsYYYYMMDDHHMMSS(std::string&, Timestamp
);

/// Serializes the timestamp using the YYYYMMDDHHMMSSmsec format.
ONIXS_B3_BOE_EXPORTED
void toStrAsYYYYMMDDHHMMSSmsec(std::string&, Timestamp);

/// Serializes the timestamp using the YYYYMMDDHHMMSSusec format.
ONIXS_B3_BOE_EXPORTED
void toStrAsYYYYMMDDHHMMSSusec(std::string&, Timestamp);

/// Serializes the timestamp using the YYYYMMDDHHMMSSnsec format.
ONIXS_B3_BOE_EXPORTED
void toStrAsYYYYMMDDHHMMSSnsec(std::string&, Timestamp);

/// Serializes the timestamp using the YYYYMMDDHHMMSSpsec format.
ONIXS_B3_BOE_EXPORTED
void toStrAsYYYYMMDDHHMMSSpsec(std::string&, Timestamp);

/// Serializes the timestamp.
ONIXS_B3_BOE_EXPORTED
void toStr(std::string&, Timestamp, TimestampFormat::Enum = TimestampFormat::YYYYMMDDHHMMSSnsec);

/// Serializes the timestamp.
inline ONIXS_B3_BOE_NODISCARD
std::string toStr(Timestamp timestamp, TimestampFormat::Enum format = TimestampFormat::YYYYMMDDHHMMSSnsec)
{
    std::string str;

    toStr(str, timestamp, format);

    return str;
}

/// Serializes the timestamp.
ONIXS_B3_BOE_EXPORTED
size_t toStr(Timestamp, Char*, size_t);

inline std::ostream & operator <<(std::ostream & os, const Timestamp& value)
{
    return os << toStr(value);
}

inline
std::ostream & operator <<(std::ostream & os, const TimeSpan& value)
{
    return os << toStr(value);
}

/// De-serializes a timespan from the given string
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool fromStr(TimeSpan&, const Char*, size_t);

/// De-serializes a timespan from the given string.
inline ONIXS_B3_BOE_NODISCARD
bool fromStr(TimeSpan& ts, const std::string& str)
{
    return
        fromStr(
            ts, str.c_str(), str.size());
}

/// De-serializes a timestamp from the given string.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NODISCARD
bool fromStr(Timestamp&, const Char*, size_t, TimestampFormat::Enum = TimestampFormat::YYYYMMDDHHMMSSnsec);

/// De-serializes a timestamp from the given string.
inline ONIXS_B3_BOE_NODISCARD
bool fromStr(Timestamp& ts, const std::string& str, TimestampFormat::Enum format= TimestampFormat::YYYYMMDDHHMMSSnsec)
{
    return
        fromStr(
            ts, str.c_str(), str.size(), format);
}

inline
Timestamp Timestamp::fromStr(const std::string& str, TimestampFormat::Enum format)
{
    Timestamp ts;

    const bool result =
        Messaging::fromStr(ts, str, format);

    if(!result)
        throw std::runtime_error("Error parsing timestamp.");

    return ts;
}

inline
TimeSpan TimeSpan::fromStr(const std::string& str)
{
    TimeSpan ts;

    const bool result =
        Messaging::fromStr(ts, str);

    if(!result)
        throw std::runtime_error("Error parsing timespan.");

    return ts;
}

inline
std::string TimeSpan::toString(TimeSpanFormat::Enum format) const
{
    return toStr(*this, format);
}

inline
std::string Timestamp::toString(TimestampFormat::Enum format) const
{
    return toStr(*this, format);
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
