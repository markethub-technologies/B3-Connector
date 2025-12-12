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

#include <Common/Common.h>
#include <Common/Defaults.h>

// Network-related helpers.

inline std::string getIfSetting(const std::string& iface, const std::string& setting)
{
    std::string settingPath;

    settingPath += "/proc/sys/net/ipv4/conf/";
    settingPath += iface;
    settingPath += "/";
    settingPath += setting;

    std::ifstream ifs(settingPath.c_str());

    if (!ifs)
    {
        return std::string();
    }
    else
    {
        std::string value;

        getline(ifs, value);

        return value;
    }
}

inline void checkReversePathFiltering(const std::string& iface)
{
    if (!iface.empty())
    {
        const char* settingName = "rp_filter";

        std::string filtering = getIfSetting(iface, settingName);

        std::string scopedIf;

        if (filtering.empty())
        {
            const char* defaultIf = "default";

            filtering = getIfSetting("default", settingName);

            scopedIf = defaultIf;
        }
        else
        {
            scopedIf = iface;
        }

        if (!filtering.empty() && filtering != "0")
        {
            std::cout << "WARNING: reverse path filtering "
                      << " is turned ON for [" << scopedIf
                      << "] interface(s). This can be a "
                         "reason of multicast data absence "
                         "on the application level. "
                      << std::endl
                      << std::endl;
        }
    }
}

inline void checkNetworkSettings(const std::string& feedANif, const std::string& feedBNif)
{
    if (feedANif.empty() && feedBNif.empty())
    {
        std::cout << "WARNING: Handler is configured to listen to market data "
                     "on all network interfaces. Linux platform configuration may "
                     "require exact network interface(s) to be specified to receive "
                     "multicast data successfully. Either define network interfaces "
                     "using application args (see command line options using --help "
                     "key) or edit definitions of the NETWORK_INTERFACE_FOR_FEEDS_A "
                     "and NETWORK_INTERFACE_FOR_FEEDS_B macros in the Common/Defaults.h"
                     ", whose values are used as defaults. "
                  << std::endl
                  << std::endl;
    }

    checkReversePathFiltering("all");
    checkReversePathFiltering(feedANif);
    checkReversePathFiltering(feedBNif);
}

template <class Options>
void checkNetworkSettings(const Options& options)
{
#if defined(_WIN32)

    (void) options;

#else

    checkNetworkSettings(options.ifA(), options.ifB());

#endif // !_WIN32
}

// Console UI.

class InterruptDetector
{
public:
    bool detected() const noexcept
    {
        return detected_;
    }

    void setDetected(bool detected = true) noexcept
    {
        detected_ |= detected;
    }

    static InterruptDetector& instance() noexcept
    {
        static InterruptDetector detector;

        return detector;
    }

private:
    InterruptDetector() noexcept
        : detected_(false)
    {
        signal(SIGINT, &InterruptDetector::signalHandler);
    }

    ~InterruptDetector() {}

    static void signalHandler(int signal)
    {
        if (SIGINT == signal)
        {
            instance().setDetected();
        }
    }

    bool detected_;
};

// Trace facilities.

class ListDelimiter
{
public:
    ListDelimiter()
        : delimiter_(0)
    {
    }

    void output(std::ostream& stream)
    {
        if (delimiter_)
        {
            stream << delimiter_;
        }
        else
        {
            delimiter_ = ',';
        }
    }

private:
    char delimiter_;
};

inline std::ostream& operator<<(std::ostream& stream, ListDelimiter& delimiter)
{
    delimiter.output(stream);

    return stream;
}

// Life-time management.

template <class Object>
class ScopedPtr
{
public:
    typedef Object* Pointer;

    explicit ScopedPtr(Pointer obj = ONIXS_B3_UMDF_MD_NULLPTR)
        : obj_(obj)
    {
    }

    ~ScopedPtr()
    {
        delete obj_;
    }

    Pointer get() const
    {
        return obj_;
    }

    Pointer operator->() const
    {
        assert(ONIXS_B3_UMDF_MD_NULLPTR != obj_);

        return obj_;
    }

    Object& operator*() const
    {
        assert(ONIXS_B3_UMDF_MD_NULLPTR != obj_);

        return *obj_;
    }

    void reset(Pointer other = ONIXS_B3_UMDF_MD_NULLPTR)
    {
        if (obj_ != other)
        {
            const ScopedPtr<Object> disposer(obj_);

            obj_ = static_cast<Pointer>(other);
        }
    }

    Pointer release()
    {
        const Pointer released = obj_;

        obj_ = ONIXS_B3_UMDF_MD_NULLPTR;

        return released;
    }

    void swap(ScopedPtr& other)
    {
        std::swap(obj_, other.obj_);
    }

private:
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Object* obj_;
};

//
