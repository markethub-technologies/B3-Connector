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
#include <Common/Options.h>

ONIXS_B3_UMDF_MD_NAMESPACE_BEGIN

// Configuration grouped by semantic/application basis.

class ConfigurationBase
{
public:
    bool show() const
    {
        return exist(options(), "help");
    }

    void show(std::ostream& out) const
    {
        out << "Options affecting application behavior: " << std::endl << std::endl;

        showOptions(out);

        out << "  --help" << std::endl << "\tDisplays this message. " << std::endl;
    }

    virtual ~ConfigurationBase() {}

protected:
    ConfigurationBase(size_t qty, char** args)
        : opts_(qty, args)
    {
    }

    const Options& options() const
    {
        return opts_;
    }

    virtual void showOptions(std::ostream&) const {}

private:
    Options opts_;
};

// Connectivity-related configuration parameters.

class ConnectivityConfiguration : public virtual ConfigurationBase
{
public:
    std::string connectivityFile() const
    {
        return argOrDefault(options(), "connectivity", CONNECTIVITY_CONFIGURATION_FILE);
    }

protected:
    ConnectivityConfiguration(size_t qty, char** args)
        : ConfigurationBase(qty, args)
    {
    }

    void showOptions(std::ostream& out) const ONIXS_B3_UMDF_MD_OVERRIDE
    {
        out << "  --connectivity <file>" << std::endl
            << "\tTells to use the given connectivity configuration file. " << std::endl
            << std::endl;
    }
};

// Feed-related configuration parameters.
class FeedConfiguration : public virtual ConfigurationBase
{
public:
    std::string ifA() const
    {
        return argOrDefault(options(), "ifA", NETWORK_INTERFACE_FOR_FEEDS_A);
    }

    std::string ifB() const
    {
        return argOrDefault(options(), "ifB", NETWORK_INTERFACE_FOR_FEEDS_B);
    }

protected:
    FeedConfiguration(size_t qty, char** args)
        : ConfigurationBase(qty, args)
    {
    }

    void showOptions(std::ostream& out) const ONIXS_B3_UMDF_MD_OVERRIDE
    {
        out << "  --ifA <interface>" << std::endl
            << "\tSpecifies a network interface for primary feeds. " << std::endl
            << std::endl
            << "  --ifB <interface>" << std::endl
            << "\tSpecifies a network interface for secondary feeds. " << std::endl
            << std::endl;
    }
};

typedef Int32 ChannelId;

class ChannelConfiguration : public virtual ConfigurationBase
{
public:
    ChannelId channel() const
    {
        const char* const option = "channel";

        const OptionArgs* args = options().args(option);

        if (ONIXS_B3_UMDF_MD_NULLPTR == args)
        {
            if (0 == default_)
            {
                throwReqiredOptionArgMissing(option);
            }

            return default_;
        }
        else if (1 != args->size())
        {
            throwBadOptionArgQty(option, args->size(), 1, 1);
        }

        const OptionArgConverter<ChannelId> converter(option);

        return converter((*args)[0]);
    }

protected:
    ChannelConfiguration(size_t qty, char** args, ChannelId defaultId = 0)
        : ConfigurationBase(qty, args)
        , default_(defaultId)
    {
    }

    void showOptions(std::ostream& out) const ONIXS_B3_UMDF_MD_OVERRIDE
    {
        out << "  --channel <id> " << std::endl
            << "\tDefines which market data is to be processed. " << std::endl
            << '\t';

        if (0 < default_)
        {
            out << "If not specified, the default [" << default_ << "] value will be used. ";
        }
        else
        {
            out << "The given parameter is required. ";
        }

        out << std::endl << std::endl;
    }

private:
    ChannelId default_;
};

ONIXS_B3_UMDF_MD_NAMESPACE_END
