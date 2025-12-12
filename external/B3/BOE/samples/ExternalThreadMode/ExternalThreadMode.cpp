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

//! [ExternalThreadModeSample]
#include "../Common/Helpers.h"
#include "../Common/Listener.h"

int main(int argc, char * argv[])
{
    clog << "B3 BOE ExternalThreadMode Sample." << endl << endl;

    MarketSegmentID marketSegmentId = DefaultMarketSegmentId;
    string host = "127.0.0.1";
    Port port = 62000;

    bool useEmulator = false;

    if (argc < 4)
    {
#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
        useEmulator = true;
#else
        std::cerr << "usage: [MarketSegmentId] [Host] [Port] (SecurityId) (PriceMantissa)" << std::endl;
        return 1;
#endif
    }
    else
    {
        marketSegmentId = atoi(argv[1]);
        host = argv[2];
        port = atoi(argv[3]);
    }

    const SecurityID securityId = argc > 4 ? static_cast<SecurityID>(atoi(argv[4])) : DefaultSecurityId;
    const Int64 priceMantissa = argc > 5 ? fromStr<Int64>(argv[5]) : DefaultPriceMantissa;

    try
    {
        SignalHelper::manageLinuxSignals();

        SessionSettings settings = fillSettings(useEmulator);

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
        std::unique_ptr<GatewayEmulatorThread> gateway;

        if (useEmulator)
            gateway.reset(new GatewayEmulatorThread(settings.licenseStores(), host, port));
#endif

        settings.threadingModel(ThreadingModel::External);

        NewOrderSingle order;
        Helper::setOrderFields(order, marketSegmentId, securityId, DefaultAccount, priceMantissa);
        //Messaging::validate(order);

        TcpStandardStack stack;

        Listener listener;
        Session session(stack, settings, &listener);

        Threading::SharedFuture<void> connectTask = session.connectAsync(host, port);

        while(!connectTask.is_ready())
            stack.dispatchEvents();

        if(connectTask.has_exception())
            connectTask.get();

        session.send(order);

        clog << "\nThe order was sent." << endl;

        clog << "\nPress any key to disconnect the session and terminate the application." << endl;

        while(!Helper::keyPressed())
            stack.dispatchEvents();

        Threading::SharedFuture<void> disconnectTask = session.disconnectAsync();

        while(!disconnectTask.is_ready() || !stack.isQuiescent())
            stack.dispatchEvents();
    }
    catch(const std::exception & ex)
    {
        cerr << "\nEXCEPTION: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
//! [ExternalThreadModeSample]
