/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable ONIXS Software
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
#include "stdafx.h"

//! [SessionSchedulerSample]
#include <OnixS/B3/BOE/Session.h>
#include <OnixS/B3/BOE/scheduling/SessionScheduler.h>
#include <OnixS/B3/BOE/threading/Thread.h>

#include "../Common/Helpers.h"

using namespace OnixS::B3::BOE;
using namespace OnixS::B3::BOE::Scheduling;
using namespace Samples;

TimeOfDay operator+ (TimeOfDay time, Scheduling::Seconds seconds)
{
    const Scheduling::Seconds SecondsPerMinute = 60;
    const int MinutesPerHour = 60;
    const Scheduling::Seconds SecondsPerHour = SecondsPerMinute * MinutesPerHour;

    const Scheduling::Seconds sinceMidnight = time.sinceMidnight() + seconds;

    return TimeOfDay(
        sinceMidnight / SecondsPerHour,
        (sinceMidnight / SecondsPerMinute) % MinutesPerHour,
        sinceMidnight % SecondsPerMinute);
}

class SessionStateChangeTracer : public SessionListener
{
    void onStateChange(SessionStateId::Enum newState, SessionStateId::Enum /*prevState*/, Session * session) ONIXS_B3_BOE_OVERRIDE
    {
        std::cout << session->toString() << " changed its state to " << SessionStateId::toString(newState) << '.' << std::endl;
    }
};

class SchedulingIssueDetector : public SessionSchedulerListener
{
public:
    SchedulingIssueDetector() ONIXS_B3_BOE_DEFAULT;

    ~SchedulingIssueDetector() ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    void onLoggingOut(const SessionScheduler & /*scheduler*/, Session * /*session*/, bool * /*allowLogout*/) ONIXS_B3_BOE_OVERRIDE
    {
    }

    void onWarning(const SessionScheduler & /*scheduler*/, Session * session, const std::string & warningReason) ONIXS_B3_BOE_OVERRIDE
    {
        std::cout << "Scheduler reported a warning for the session " << session->toString() << ": " << warningReason;
    }

    void onError(const SessionScheduler & /*scheduler*/, Session * session, const std::string & errorReason) ONIXS_B3_BOE_OVERRIDE
    {
        std::cout << "Error occurred while scheduling session " << session->toString() << ": " << errorReason;
    }
};

class Sample
{
public:
    Sample()
        : session_(ONIXS_B3_BOE_NULLPTR)
        , scheduler_(ONIXS_B3_BOE_NULLPTR)
    {
        about();
    }

    ~Sample()
    {
        if(session_)
            session_->disconnect();

        delete session_;
        delete scheduler_;
    }

    void run(const std::string& host, Scheduling::Port port)
    {
        constructSession();

        constructScheduler();

        std::cout << "Scheduling session " << session_->toString() << " for automatic connection." << std::endl;

        const SessionSchedule sessionSchedule = constructShortTimeActivitySchedule();

        const SessionConnectionSettings sessionConnectivity(host, port);

        scheduler_->add(session_, sessionSchedule, sessionConnectivity);

        std::cout << "Waiting for activity on scheduled session " << session_->toString() << '.' << std::endl << std::endl;

        // Should sleep for a while to let Scheduler connect session.
        Threading::ThisThread::sleep(1000 * sessionActivityTimeInSeconds());

        waitUntilLogout(session_);

        std::cout << std::endl << "Removing session " << session_->toString() << " from scheduling service." << std::endl;

        // The session had to 'pulse' connection till this time so that scheduling could be destroyed.
        scheduler_->remove(session_);
    }

    void useConfigurationFile()
    {
        SessionSchedulerOptions schedulerOptions;

        schedulerOptions.configurationFile("SchedulerConfiguration.xml");

        SessionScheduler scheduler(schedulerOptions);

        scheduler.add(session_, "ScheduleId", "ConnectionId");

        Threading::ThisThread::sleep(1000 * sessionActivityTimeInSeconds());

        scheduler_->remove(session_);
    }

private:
    Session* session_;
    SessionStateChangeTracer sessionStateChangeTracer_;

    SessionScheduler* scheduler_;
    SchedulingIssueDetector schedulingIssueDetector_;

    void constructScheduler()
    {
        SessionSchedulerOptions schedulerOptions;
        schedulerOptions.eventListener(&schedulingIssueDetector_);

        scheduler_ = new SessionScheduler(schedulerOptions);
    }

    void constructSession()
    {
        const SessionSettings settings = Samples::fillSettings();
        session_ = new Session(settings, &sessionStateChangeTracer_);
    }

    static SessionSchedule constructShortTimeActivitySchedule()
    {
        const TimeOfDay now = TimeOfDay::now();

        const TimeOfDay logonTime = now + Scheduling::Seconds(5);

        const TimeOfDay logoutTime = logonTime + Scheduling::Seconds(sessionActivityTimeInSeconds());

        return SessionSchedule(DayOfWeek::now(), DayOfWeek::now(), logonTime, logoutTime);
    }

    static void waitUntilLogout(Session * session)
    {
        const unsigned oneSecondPause = 1000;

        while(session->state() != SessionStateId::Disconnected)
            Threading::ThisThread::sleep(oneSecondPause);
    }

    static int sessionActivityTimeInSeconds()
    {
        return 30;
    }

    static void about()
    {
        std::cout << "OnixS C++ B3 BOE Session Scheduling Sample." << std::endl << std::endl;
    }
};

void usage()
{
    std::cerr << "usage: [MarketSegmentId] [Host] [Port]" << std::endl;
}

int main(int argc, char * argv[])
{
    try
    {
        MarketSegmentID marketSegmentId = DefaultMarketSegmentId;
        std::string host;
        Scheduling::Port port = 0;

        if (argc >= 2)
            marketSegmentId = atoi(argv[1]);

        if (argc >= 3)
            host = argv[2];

        if (argc >= 4)
            port = atoi(argv[3]);

        if (marketSegmentId == 0 || host.empty() || port == 0)
        {
            usage();
            return 1;
        }

        Sample sample;

        sample.run(host, port);

        std::cout << std::endl << "Done." << std::endl;
    }
    catch(const std::exception & ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
//! [SessionSchedulerSample]
