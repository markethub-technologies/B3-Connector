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

//! [MainCpp]
#include "Settings.h"
#include "TradingClient.h"

using namespace Samples;

namespace
{
    void ensureSettingsAreUpToDate(const Settings& appSettings)
    {
        const std::string upToDateParameter("settingsAreUpToDate");

        if (!appSettings.getAsBool(upToDateParameter))
        {
            std::string errReason("Please update the configuration file (settings.ini) with values received from B3 Support Team and set the '");

            errReason += upToDateParameter;

            errReason += "' configuration parameter to 'true'";

            throw std::domain_error(errReason);
        }
    }
}

int main(int argc, char * argv[])
{
    try
    {
        std::cout << "B3 BOE Trading Client sample." << std::endl
            << "Usage: " << argv[0] << " {ConfigurationFileName}" << std::endl;

        std::string configurationFileName = (argc > 1) ? argv[1] : "settings.ini";

        Settings settings(configurationFileName);

        ensureSettingsAreUpToDate(settings);

        TradingClient client(settings);

        client.run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << std::endl << "Error: " << ex.what() << "." << std::endl;
        return 1;
    }

    return 0;
}
//! [MainCpp]
