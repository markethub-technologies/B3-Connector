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

#include <string>
#include <vector>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Scheduling {

/// The day of the week.
struct ONIXS_B3_BOE_EXPORTED DayOfWeek
{
    enum Enum
    {
        Sunday,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Total
    };

    /// Transforms the string presentation into a valid constant.
    static Enum parse(const std::string & value);

    /// \return the string presentation for a given constant.
    static std::string toString(Enum value);

    /// \return the current day of the week.
    static Enum now();

    /// \return the current UTC day of the week.
    static Enum utcNow();
};

/// The number of hours.
typedef int Hours;

/// The number of minutes.
typedef int Minutes;

/// The number of seconds.
typedef int Seconds;

/// Time of day.
class ONIXS_B3_BOE_EXPORTED TimeOfDay
{
public:
    TimeOfDay() ONIXS_B3_BOE_NOTHROW;

    TimeOfDay(Hours hours, Minutes minutes, Seconds = 0) ONIXS_B3_BOE_NOTHROW;

    /// \return hours.
    Hours hours() const ONIXS_B3_BOE_NOTHROW;

    /// \return minutes.
    Minutes minutes() const ONIXS_B3_BOE_NOTHROW;

    /// \return seconds.
    Seconds seconds() const ONIXS_B3_BOE_NOTHROW;

    /// \return the total number of seconds since the midnight.
    Seconds sinceMidnight() const ONIXS_B3_BOE_NOTHROW;

    /// \return the string presentation.
    std::string toString() const;

    /// Checks whether the instance is equal to the given one.
    bool operator == (const TimeOfDay & other) const ONIXS_B3_BOE_NOTHROW;

    /// Checks whether the instance is unequal to the given one.
    bool operator != (const TimeOfDay & other) const ONIXS_B3_BOE_NOTHROW;

    /// \return the current time of day.
    static TimeOfDay now();

    /// \return the 'Zero' point of the time of day.
    static TimeOfDay midnight() ONIXS_B3_BOE_NOTHROW;

    /// \return the instance of an ill-formed time of day.
    static TimeOfDay bad();

    /// Parses the time of day from the given string presentation.
    static TimeOfDay parse(const std::string &);

private:
    Seconds seconds_;

    explicit TimeOfDay(Seconds) ONIXS_B3_BOE_NOTHROW;
};

inline
Seconds TimeOfDay::sinceMidnight() const ONIXS_B3_BOE_NOTHROW
{
    return seconds_;
}

inline
bool TimeOfDay::operator == (const TimeOfDay & other) const ONIXS_B3_BOE_NOTHROW
{
    return seconds_ == other.seconds_;
}

inline
bool TimeOfDay::operator != (const TimeOfDay & other) const ONIXS_B3_BOE_NOTHROW
{
    return seconds_ != other.seconds_;
}

/// Collection of time of day values indexed by the day of week.
typedef TimeOfDay TimeOfDayOfWeek[DayOfWeek::Total];

/// Session Schedule.
class ONIXS_B3_BOE_EXPORTED SessionSchedule
{
public:
    /// Constructor.
    ///
    /// \param firstDay the first day of the week.
    ///
    /// \param lastDay the last day of the week.
    ///
    /// \param logonTime the logon time.
    ///
    /// \param logoutTime the logout time.
    SessionSchedule(DayOfWeek::Enum firstDay, DayOfWeek::Enum lastDay, TimeOfDay logonTime, TimeOfDay logoutTime);

    SessionSchedule(const SessionSchedule & other);

    /// \return the logon time.
    ///
    /// If the logon is not performed on the given day,
    /// returns the result of TimeOfDay::bad().
    TimeOfDay logonTime(DayOfWeek::Enum day) const ONIXS_B3_BOE_NOTHROW;

    /// Sets the logon time.
    SessionSchedule& logonTime(DayOfWeek::Enum day, TimeOfDay time) ONIXS_B3_BOE_NOTHROW;

    /// \return the logout time.
    ///
    /// If the logout is not performed on the given day,
    /// returns the result of TimeOfDay::bad().
    TimeOfDay logoutTime(DayOfWeek::Enum day) const ONIXS_B3_BOE_NOTHROW;

    /// Sets the logout time.
    SessionSchedule &logoutTime(DayOfWeek::Enum day, TimeOfDay time) ONIXS_B3_BOE_NOTHROW;

    /// \return the day of the week on which the session is reset.
    DayOfWeek::Enum resetDay() const ONIXS_B3_BOE_NOTHROW;

    SessionSchedule & operator = (const SessionSchedule & other);

private:
    friend class SessionStateChanger;

    TimeOfDayOfWeek logonTimes_;
    TimeOfDayOfWeek logoutTimes_;

    DayOfWeek::Enum startOfWeek_;
};

inline
TimeOfDay SessionSchedule::logonTime(DayOfWeek::Enum day) const ONIXS_B3_BOE_NOTHROW
{
    return logonTimes_[day];
}

inline
SessionSchedule &SessionSchedule::logonTime(DayOfWeek::Enum day, TimeOfDay logonTime) ONIXS_B3_BOE_NOTHROW
{
    logonTimes_[day] = logonTime;
    return *this;
}

inline
TimeOfDay SessionSchedule::logoutTime(DayOfWeek::Enum day) const ONIXS_B3_BOE_NOTHROW
{
    return logoutTimes_[day];
}

inline
SessionSchedule& SessionSchedule::logoutTime(DayOfWeek::Enum day, TimeOfDay logoutTime) ONIXS_B3_BOE_NOTHROW
{
    logoutTimes_[day] = logoutTime;
    return *this;
}

inline
DayOfWeek::Enum SessionSchedule::resetDay() const ONIXS_B3_BOE_NOTHROW
{
    return startOfWeek_;
}
}
}
}
}
