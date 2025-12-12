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
#include <OnixS/B3/BOE/Session.h>
#include <OnixS/B3/BOE/scheduling/SessionConnectionSettings.h>
#include <OnixS/B3/BOE/scheduling/SessionSchedule.h>
#include <OnixS/B3/BOE/threading/Thread.h>

#include <set>
#include <string>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Scheduling {

class SessionScheduler;

typedef std::string SessionScheduleId;
typedef std::string SessionConnectionSettingsId;

/// SessionScheduler events notifications.
class ONIXS_B3_BOE_EXPORTED SessionSchedulerListener
{
public:
    /// Notifies that the session is about to be closed.
    ///
    /// \param scheduler the instance the of session
    /// scheduler that is about to close the session.
    ///
    /// \param session the session that is about to be closed.
    ///
    /// \param allowLogout indicates whether the scheduler must perform the logout.
    /// To prohibit the logout set this parameter to `false`.
    virtual void onLoggingOut(const SessionScheduler & scheduler, Session * session, bool * allowLogout) = 0;

    /// Notifies about a non-critical issue.
    virtual void onWarning(const SessionScheduler & scheduler, Session * session, const std::string & warningReason) = 0;

    /// Notifies about an error.
    virtual void onError(const SessionScheduler & scheduler, Session * session,  const std::string & errorReason) = 0;

protected:
    virtual ~SessionSchedulerListener() ONIXS_B3_BOE_DEFAULT;
};

/// Scheduler options.
class ONIXS_B3_BOE_EXPORTED SessionSchedulerOptions
{
public:
    SessionSchedulerOptions();

    ~SessionSchedulerOptions();

    /// \return the path to the scheduler configuration file.
    const std::string & configurationFile() const ONIXS_B3_BOE_NOTHROW;

    /// Sets the path to the scheduler configuration file.
    SessionSchedulerOptions &configurationFile(const std::string &file);

    /// \return the event listener.
    SessionSchedulerListener * eventListener() const ONIXS_B3_BOE_NOTHROW;

    /// Sets the event listener.
    SessionSchedulerOptions &eventListener(SessionSchedulerListener *listener) ONIXS_B3_BOE_NOTHROW;

private:
    std::string * configurationFile_;
    SessionSchedulerListener * eventListener_;
};

/// Session Scheduler.
class ONIXS_B3_BOE_EXPORTED SessionScheduler
{
public:
    SessionScheduler(const SessionSchedulerOptions & options);

    /// Performs the graceful shutdown of scheduling sessions.
    ~SessionScheduler();

    /// Looks for the predefined session schedule associated with the given id
    /// that was specified in Scheduler's configuration file.
    ///
    /// \return `NULL` if no schedule is available for the given id.
    const SessionSchedule * findSchedule(const SessionScheduleId & id) const;

    /// Looks for the predefined session connection settings associated with the given id
    /// that was specified in Scheduler's configuration file.
    ///
    /// \return `NULL` if no settings are available for the given id.
    const SessionConnectionSettings * findConnectionSettings(const SessionConnectionSettingsId & id) const;

    /// Adds the session to the automatic connection management.
    ///
    /// - If the session is being added during the active time frame, it will be connected immediately.
    /// - If the session is being registered during the inactive time frame and is in the active state, it will be disconnected.
    /// - If the session is already registered, an exception will be thrown.
    ///
    /// \param session the instance of the session to be maintained.
    /// \param schedule Session's schedule.
    /// \param connection Session's connection settings.
    SessionScheduler& add(Session *session, const SessionSchedule &schedule, const SessionConnectionSettings &connection);

    /// Adds the session to the automatic connection management.
    ///
    /// - If the session is being added during the active time frame, it will be connected immediately.
    /// - If the session is being registered during the inactive time frame and is in the active state, it will be disconnected.
    /// - If the session is already registered, and exception will be thrown.
    ///
    /// \param session the instance of the session to be maintained.
    /// \param scheduleId the ID of the predefined schedule.
    /// \param connectionId the ID of the predefined connection settings.
    SessionScheduler &add(Session *session, const SessionScheduleId &scheduleId, const SessionConnectionSettingsId &connectionId);

    /// Removes the session from the automatic connection management services.
    SessionScheduler &remove(Session *session);

    /// Sets the CPU affinity for the Scheduler service thread.
    SessionScheduler &serviceThreadAffinity(const OnixS::B3::BOE::CpuIndexes &cpuIndexes);

    /// \return the CPU affinity for the Scheduler service thread.
    const OnixS::B3::BOE::CpuIndexes &serviceThreadAffinity() const ONIXS_B3_BOE_NOTHROW;

    /// Sets the number of logon attempts in case of a logon failure.
    SessionScheduler &reconnectAttempts(int value);

    /// \return the number of logon attempts in case of a logon failure.
    ///
    /// The default value is `3`.
    int reconnectAttempts() const;

    /// Sets the time interval between the logon attempts in case of a logon failure (in seconds).
    SessionScheduler &reconnectInterval(int value);

    /// \return the time interval between the logon attempts in case of a logon failure (in seconds).
    ///
    /// The default value is `180` seconds.
    int reconnectInterval() const;

    /// Activates the UTC usage.
    SessionScheduler &utcTimeUsage(bool value);

    /// \return `true` if the UTC is used, otherwise - `false`.
    ///
    /// The default value is `false`.
    bool utcTimeUsage() const;

private:
    class Impl;
    Impl * impl_;
};
}
}
}
}
