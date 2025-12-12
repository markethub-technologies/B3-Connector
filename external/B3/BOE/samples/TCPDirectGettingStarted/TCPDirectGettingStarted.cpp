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

//! [TCPDirectGettingStartedSample]
#include <OnixS/B3/BOE/TcpDirectStack.h>

#include "../Common/Helpers.h"
#include "../Common/Listener.h"
#include "../Settings/Defaults.h"

using namespace Samples;
using namespace Threading;

SecurityID securityId;
Int64 priceMantissa;
MarketSegmentID marketSegmentId;

int main(int argc, char * argv[]) {
    clog << "B3 BOE TCPDirect Getting Started Sample." << endl << endl;

    marketSegmentId = DefaultMarketSegmentId;
    // Use the IP address belonging to the TcpDirectStack interface in emulator mode.
    string host = "192.168.0.1";
    Port port = 62000;

    bool useEmulator = false;

    if(argc < 4) {
#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
        useEmulator = true;
#else
        std::cerr << "usage: [MarketSegmentId] [Host] [Port] (SecurityId) (PriceMantissa)" << std::endl;
        return 1;
#endif
    }
    else {
        marketSegmentId = atoi(argv[1]);
        host = argv[2];
        port = atoi(argv[3]);
    }

    securityId = argc > 4 ? fromStr<SecurityID>(argv[4]) : DefaultSecurityId;
    priceMantissa = argc > 5 ? fromStr<Int64>(argv[5]) : DefaultPriceMantissa;

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
    std::unique_ptr<GatewayEmulatorThread> gateway;
#endif

    int result = 0;

    try {
        SignalHelper::manageLinuxSignals();

        const SessionSettings settings = fillSettings(useEmulator);

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
        if(useEmulator)
            gateway.reset(new GatewayEmulatorThread(settings.licenseStores(), host, port));
#endif

        TcpDirectAttr attr;

        // The default interface name could be provided by the environment variable
        //     ZF_ATTR="interface=<interface-name>", see TCPDirect specs,
        //
        // or could be set manually:
        //     attr.set("interface", "interface-name");

        TcpDirectStack tcpDirectStack(attr);

        bool finished = false;

        class TcpDirectListener : public Listener
        {
        public:
            explicit TcpDirectListener(bool & finished)
                : finished_(finished) {}

            void onStateChange(SessionStateId::Enum newState, SessionStateId::Enum prevState, Session * session) ONIXS_B3_BOE_OVERRIDE
            {
                Listener::onStateChange(newState, prevState, session);

                switch(newState) {
                case SessionStateId::Established:
                {
                    NewOrderSingle order;
                    Helper::setOrderFields(order, marketSegmentId, securityId, DefaultAccount, priceMantissa);

                    // The TCPDirect technology is NOT thread-safe.
                    // Therefore, the event dispatching and message sending should be performed from the same thread.
                    session->send(order);
                    clog << "\nThe order was sent." << endl;

                    break;
                }

                case SessionStateId::Disconnected:
                    finished_ = true;
                    break;

                default:
                    break;
                }
            }

            void onError(
                SessionErrorReason::Enum reason, const std::string & text, Session * session, Messaging::SbeMessage msg) ONIXS_B3_BOE_OVERRIDE
            {
                Listener::onError(reason, text, session, msg);
                finished_ = true;
            }

        private:
            bool & finished_;
        }
        listener(finished);

        Session session(tcpDirectStack, settings, &listener);

        session.connectAsync(host, port);

        while(!finished)
        {
            // The TCPDirect technology is NOT thread-safe.
            // Therefore, the event dispatching and message sending should be performed from the same thread.
            tcpDirectStack.dispatchEvents();

            if(Helper::keyPressed())
                break;
        }

        session.disconnectAsync();

        while(!tcpDirectStack.isQuiescent())
            tcpDirectStack.dispatchEvents();
    }
    catch(const std::exception & ex) {
        cerr << "\nEXCEPTION: " << ex.what() << endl;
        result = 1;
    }

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)
    if(gateway) {
        try {
            gateway->wait();
        }
        catch(...) {
            // Emulator exception (if any) is already reported from Emulator's thread
        }
    }
#endif

    return result;
}
//! [TCPDirectGettingStartedSample]
