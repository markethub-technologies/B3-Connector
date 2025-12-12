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

#include "stdafx.h"

//! [SettingsCpp]
#include "Settings.h"

namespace
{
    void trimSpaces(std::string* str)
    {
        const char whiteSpace[] = " \t\r";

        size_t found = str->find_last_not_of(whiteSpace);

        if (std::string::npos == found)
            str->resize(0);
        else
            str->resize(found + 1);

        found = str->find_first_not_of(whiteSpace);

        if (std::string::npos != found && 0 != found)
            str->erase(0, found);
    }

    int lexicalCompare(const std::string& left, const std::string& right)
    {
#if defined(_WIN32)
        return _stricmp(left.c_str(), right.c_str());
#else
        return strcasecmp(left.c_str(), right.c_str());
#endif
    }
}

namespace Samples
{

Settings::Settings(const std::string& filePath)
{
    std::ifstream in(filePath.c_str());

    if (!in)
    {
        std::string errReason("Cannot open the settings file '");

        errReason += filePath;
        errReason += "'";

        throw std::domain_error(errReason);
    }

    std::string line;

    while (getline(in, line))
    {
        const std::string::size_type comment = line.find('#');

        if (std::string::npos != comment)
            line.resize(comment);

        std::string::size_type separator = line.find('=');

        if (std::string::npos == separator)
            continue;

        std::string key = line.substr(0, separator);

        trimSpaces(&key);

        std::string value = line.substr(separator + 1);

        trimSpaces(&value);

        map_.insert(make_pair(key, value));
    }
}

std::string Settings::get(const std::string& key) const
{
    const Key2ValueMapEntry it = map_.find(key);

    if (map_.end() == it)
    {
        std::string errReason("There's no setting '");

        errReason += key;
        errReason += "' available";

        throw std::domain_error(errReason);
    }

    return it->second;
}

std::string Settings::get(const std::string& key, const std::string& defaultValue) const
{
    const Key2ValueMapEntry it = map_.find(key);
    return (map_.end() == it) ? defaultValue : it->second;
}

std::string Settings::getIfAny(const std::string& key) const
{
    return get(key, std::string());
}

int Settings::getAsInt(const std::string& key) const
{
    const std::string value = get(key);
    return atoi(value.c_str());
}

int Settings::getAsInt(const std::string& key, int defaultValue) const
{
    const std::string value = getIfAny(key);
    return value.empty() ? defaultValue : atoi(value.c_str());
}

bool Settings::getAsBool(const std::string& key) const
{
    const std::string value = get(key);
    return 0 == lexicalCompare("true", value);
}

bool Settings::getAsBool(const std::string& key, bool defaultValue) const
{
    const std::string value = getIfAny(key);

    return !value.empty() ? 0 == lexicalCompare("true", value) : defaultValue;
}

bool Settings::isSet(const std::string& key) const
{
    return map_.count(key) > 0;
}

}
//! [SettingsCpp]
