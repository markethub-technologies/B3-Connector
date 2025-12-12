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

//! [SettingsH]
#include <string>
#include <map>

namespace Samples
{

class Settings
{
public:
    explicit Settings(const std::string& filePath);

    std::string get(const std::string& key) const;
    std::string get(const std::string& key, const std::string& defaultValue) const;

    std::string getIfAny(const std::string& key) const;

    int getAsInt(const std::string& key) const;
    int getAsInt(const std::string& key, int defaultValue) const;

    bool getAsBool(const std::string& key) const;
    bool getAsBool(const std::string& key, bool defaultValue) const;

    bool isSet(const std::string& key) const;

private:
    typedef std::map<std::string, std::string> Key2ValueMap;
    typedef Key2ValueMap::const_iterator Key2ValueMapEntry;

    Key2ValueMap map_;
};

}
//! [SettingsH]
