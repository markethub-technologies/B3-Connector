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
#include <OnixS/B3/MarketData/UMDF/messaging/Integral.h>

ONIXS_B3_UMDF_MD_NAMESPACE_BEGIN

using namespace OnixS::B3::MarketData::UMDF::Messaging;

typedef std::string Option;

typedef std::string OptionArg;

typedef std::vector<OptionArg> OptionArgs;

// Implements a carriage over command line arguments.
class ArgCarriage
{
public:
    ArgCarriage(size_t qty, char** args)
        : qty_(qty)
        , args_(args)
    {
    }

    // Checks whether the carriage is in a valid state.
    operator bool() const
    {
        return (0 < qty_);
    }

    // If valid, provides access to the argument
    // which the carriage currently points to.
    const char* operator*() const
    {
        assert(0 < qty_);

        return *args_;
    }

    // Advances the carriage to the next argument.
    void advance()
    {
        --qty_;
        ++args_;
    }

private:
    size_t qty_;
    char** args_;
};

inline void throwBadOption(const Char* arg)
{
    assert(ONIXS_B3_UMDF_MD_NULLPTR != arg);

    std::string issue;

    issue += "The given argument [";
    issue += arg;

    issue += "] does not represent an option which "
             "must begin with the '--' prefix. ";

    throw std::runtime_error(issue);
}

inline void throwDuplicatedOption(const Char* option)
{
    std::string issue;

    issue += "The given option [";
    issue += option;
    issue += "] is defined twice in the argument list. ";

    throw std::runtime_error(issue);
}

// Groups the command line arguments by options.
class Options
{
public:
    // Initializes blank instance.
    Options() =default;

    // Processes application input arguments
    // and builds the option-to-values map.
    Options(size_t qty, char** args)
    {
        assert(0 < qty);
        assert(args);

        ArgCarriage carriage(qty, args);

        // Cuts application name.

        carriage.advance();

        // If there are arguments
        // except the application name.

        if (carriage)
        {
            std::string option;

            if (isOption(*carriage, &option))
            {
                do
                {
                    carriage.advance();

                    const std::pair<Items::iterator, bool> inserted =
                        items_.insert(std::make_pair(option, OptionArgs()));

                    if (inserted.second)
                    {
                        OptionArgs& optionArgs = inserted.first->second;

                        while (carriage && !isOption(*carriage, &option))
                        {
                            optionArgs.push_back(*carriage);

                            carriage.advance();
                        }
                    }
                    else
                    {
                        throwDuplicatedOption(option.c_str());
                    }
                }
                while (carriage);
            }
            else
            {
                throwBadOption(*carriage);
            }
        }
    }

    ~Options() {}

    // Transforms available options
    // into the given destination.
    template <class Iterator>
    void get(Iterator target) const
    {
        std::transform(items_.begin(), items_.end(), target, PairFirst<Option, OptionArgs>());
    }

    // Exposes arguments for the given option.
    // Returns null if option is not present.
    const OptionArgs* args(const char* option) const
    {
        return args(option ? std::string(option) : std::string());
    }

    // Exposes arguments for the given option.
    // Returns null if option is not present.
    const OptionArgs* args(const std::string& option) const
    {
        const Items::const_iterator foundItem = items_.find(option);

        return (foundItem != items_.end() ? &foundItem->second : ONIXS_B3_UMDF_MD_NULLPTR);
    }

private:
    template <typename First, typename Second>
    struct PairFirst
    {
        typedef std::pair<First, Second> Pair;

        inline First operator()(const Pair& item) const
        {
            return item.first;
        }
    };

    typedef std::map<Option, OptionArgs> Items;

    Items items_;

    // Checks whether the given argument
    // represents an option. Extracts the
    // option (cuts prefix) upon request.
    static bool isOption(const char* arg, std::string* option = ONIXS_B3_UMDF_MD_NULLPTR)
    {
        assert(ONIXS_B3_UMDF_MD_NULLPTR != arg);

        const size_t argLength = strlen(arg);

        static const StrRef prefix = toStrRef("--");

        if (argLength > prefix.size() && prefix == StrRef(arg, prefix.size()) && prefix[0] != arg[prefix.size()])
        {
            if (option)
            {
                option->assign(arg + prefix.size(), argLength - prefix.size());
            }

            return true;
        }

        return false;
    }
};

inline bool exist(const Options& options, const Char* option)
{
    assert(ONIXS_B3_UMDF_MD_NULLPTR != option);

    return (ONIXS_B3_UMDF_MD_NULLPTR != options.args(option));
}

// Enhances options manipulation services
// with data conversion facilities.

inline void throwOptionArgConversionFailed(const Char* option)
{
    assert(ONIXS_B3_UMDF_MD_NULLPTR != option);

    std::string issue;

    issue += "Value for the option [";

    issue += option;

    issue += "] is not recognized. Run application help "
             "for information on valid values for the option. ";

    throw std::runtime_error(issue);
}

template <typename Value>
class OptionArgConverter
{
public:
    OptionArgConverter(const Char* option)
        : option_(option)
    {
    }

    Value operator()(const std::string& str) const
    {
        Value value = Value();

        if (!fromStr(value, str.data(), str.length()))
        {
            throwOptionArgConversionFailed(option_);
        }

        return value;
    }

private:
    const Char* option_;
};

template <>
class OptionArgConverter<std::string>
{
public:
    OptionArgConverter(const Char* = ONIXS_B3_UMDF_MD_NULLPTR) {}

    std::string operator()(const std::string& str) const
    {
        return str;
    }
};

template <>
class OptionArgConverter<const Char*>
{
public:
    OptionArgConverter(const Char* = ONIXS_B3_UMDF_MD_NULLPTR) {}

    const Char* operator()(const std::string& str) const
    {
        return str.c_str();
    }
};

template <typename Value>
inline void convertOptionArg(Value& value, const Char* option, const std::string& str)
{
    const OptionArgConverter<Value> converter(option);

    value = converter(str);
}

inline void throwBadOptionArgQty(const Char* option, size_t argQty, size_t minQty, size_t maxQty)
{
    assert(ONIXS_B3_UMDF_MD_NULLPTR != option);

    std::string issue;

    issue += "Number of arguments for the option [";

    issue += option;

    issue += "] does not meet the requirements. "
             "It must be not less than ";

    toStr(issue, minQty);

    if (maxQty != static_cast<size_t>(-1))
    {
        issue += " and not greater than ";

        toStr(issue, maxQty);
    }

    issue += ". Meanwhile, the actual number is ";

    toStr(issue, argQty);

    issue += ". ";

    throw std::runtime_error(issue);
}

inline void throwReqiredOptionArgMissing(const Char* option)
{
    assert(ONIXS_B3_UMDF_MD_NULLPTR != option);

    std::string issue;

    issue += "The required option [";

    issue += option;

    issue += "] or its argument is missing. ";

    throw std::runtime_error(issue);
}

template <typename Value, typename Iterator>
inline bool args(
    const Options& options,
    const Char* option,
    Iterator target,
    size_t minQty = 0,
    size_t maxQty = static_cast<size_t>(-1)
)
{
    if (const OptionArgs* args = options.args(option))
    {
        const size_t argQty = args->size();

        if (minQty <= argQty && maxQty >= argQty)
        {
            const OptionArgConverter<Value> converter(option);

            std::transform(args->begin(), args->end(), target, converter);

            return true;
        }
        else
        {
            throwBadOptionArgQty(option, argQty, minQty, maxQty);
        }
    }

    return false;
}

template <typename Value>
inline Value argOrDefault(const Options& options, const Char* option, const Value& defaultValue = Value())
{
    Value value = defaultValue;

    args<Value>(options, option, &value, 1, 1);

    return value;
}

template <typename Value>
inline
std::set<Value> argSetOrDefault(const Options& options, const Char* option, const Value& defaultValue = Value(), size_t minQty = 0, size_t maxQty = static_cast<size_t>(-1))
{
    std::set<Value> values;

    if (const OptionArgs* args = options.args(option))
    {
        const size_t argQty = args->size();

        if (minQty <= argQty && maxQty >= argQty)
        {
            const OptionArgConverter<Value> converter(option);

            std::transform(args->begin(), args->end(), std::inserter(values, values.begin()), converter);
        }
        else
        {
            throwBadOptionArgQty(option, argQty, minQty, maxQty);
        }
    }

    if (!values.empty())
        return values;

    return { defaultValue };
}

template <typename Value, size_t Length>
inline const Value* argOrDefault(const Options& options, const Char* option, Value (&defaultValue)[Length])
{
    return argOrDefault<const Value*>(options, option, static_cast<const Value*>(defaultValue));
}

template <typename Value>
inline Value requiredArg(const Options& options, const Char* option)
{
    const OptionArgs* args = options.args(option);

    if (ONIXS_B3_UMDF_MD_NULLPTR == args || 1 != args->size())
    {
        throwReqiredOptionArgMissing(option);
    }

    const OptionArgConverter<Value> converter(option);

    return converter((*args)[0]);
}

ONIXS_B3_UMDF_MD_NAMESPACE_END
