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

#pragma once

//! [HelpersH]

#include <OnixS/B3/MarketData/UMDF/ABI.h>

#include <cstdio>
#include <fstream>

#ifdef _WIN32
#   include <conio.h>
#   include <ctype.h>
#else
#   include <pthread.h>
#   include <csignal>
#   include <cstdlib>
#   include <vector>
#endif

#ifdef __linux__
#include <sys/poll.h>
#else
#include <conio.h>
#endif

#ifndef _WIN32
// The code below illustrates how to manage signals:
// - Mask signals in all threads;
// - Start a separate thread to catch signals;
class SignalHelper
{
public:

    typedef std::vector<int> SuppressedSignals;

    static void manageLinuxSignals()
    {
        SuppressedSignals suppressedSignals;

        // Add signals we are waiting for.
        suppressedSignals.push_back(SIGPIPE);

        pthread_t signalThreadId;
        int status;

        // Mask signals in the primary thread.
        // Child threads will inherit this signal mask.
        sigemptyset(&signalSet());

        for (SuppressedSignals::const_iterator i = suppressedSignals.begin(), e = suppressedSignals.end(); i != e; ++i)
            sigaddset(&signalSet(), *i);

        status = pthread_sigmask(SIG_BLOCK, &signalSet(), ONIXS_B3_UMDF_MD_NULLPTR);

        if (status != 0)
            errorAbort(status, "Set signal mask");

        // Create the sigwait thread.
        status = pthread_create(&signalThreadId, ONIXS_B3_UMDF_MD_NULLPTR, signalWaiter, ONIXS_B3_UMDF_MD_NULLPTR);

        if (status != 0)
            errorAbort(status, "Create signalWaiter");
    }

    static void waitUntilSignal()
    {
        int signalNumber = 0;

        while (true)
        {
            sigwait (&signalSet(), &signalNumber);
            if (SIGINT == signalNumber)
            {
                printf ("Signal %d received, exit from waiting.\n", signalNumber);
                return;
            }
            else
                printf ("Signal %d received and suppressed.\n", signalNumber);
        }
    }

private:

    ONIXS_B3_UMDF_MD_NORETURN
    static void errorAbort(int status, const char* reason)
    {
        printf("Aborted due to status %d: %s\n", status, reason ? reason : "no error message");
        exit(1);
    }

    ONIXS_B3_UMDF_MD_NORETURN
    static void* signalWaiter(void*)
    {
        int signalNumber;

        while (true)
        {
            sigwait(&signalSet(), &signalNumber);
            printf("Signal %d received and suppressed.\n", signalNumber);
        }
    }

    static sigset_t& signalSet()
    {
        static sigset_t set;
        return set;
    }
};
#endif

inline
void manageLinuxSignals()
{
#ifndef _WIN32
    SignalHelper::manageLinuxSignals();
#endif
}

inline
void waitUntilEnterKey(const std::string& waitText = std::string())
{
    if(!waitText.empty())
        std::clog << std::endl << waitText << std::endl;

#ifdef _WIN32
    _getch();
#else
    getchar();
#endif
}

inline
bool keyPressed()
{
#ifdef __linux__
    pollfd pfd = { 0, POLLIN, 0 };
    return poll(&pfd, 1, 0) != 0 ? getchar(), true : false;
#else
    return _kbhit() != 0 ? _getch(), true : false;
#endif
}

inline
bool parseBool(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

//! [HelpersH]
