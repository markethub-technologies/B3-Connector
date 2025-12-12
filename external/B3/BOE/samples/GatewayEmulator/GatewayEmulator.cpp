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

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)

//! [GatewayEmulatorSample]

#include "../Common/Helpers.h"
#include "../Common/Listener.h"

using namespace Samples;

/// Send `ExecutionReportNew` for an incoming `NewOrderSingle` or `BusinessReject` for any other message.
class GatewaySampleListener : public GatewayListener
{
public:
    void onNewOrderSingle(const NewOrderSingle102 & msg, Testing::Gateway* gateway) override
    {
        std::clog << "\nReceived:\n" << msg << std::endl;

        updateReport(msg);

        gateway->send(report_, ++reportsCounter_);
        gateway->outSeqNum(reportsCounter_ + 1);

        std::clog << "\nSent:\n" << report_.message() << std::endl;
    }

    void onSimpleNewOrder(const Messaging::SimpleNewOrder100& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onSimpleModifyOrder(const Messaging::SimpleModifyOrder101& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onOrderCancelReplaceRequest(const Messaging::OrderCancelReplaceRequest104& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onOrderCancelRequest(const Messaging::OrderCancelRequest105& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onNewOrderCross(const Messaging::NewOrderCross106& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onSecurityDefinitionRequest(const Messaging::SecurityDefinitionRequest300& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onQuoteRequest(const Messaging::QuoteRequest401& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onQuoteStatusReport(const Messaging::QuoteStatusReport402& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onQuote(const Messaging::Quote403& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onQuoteCancel(const Messaging::QuoteCancel404& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onQuoteRequestReject(const Messaging::QuoteRequestReject405& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onPositionMaintenanceCancelRequest(const Messaging::PositionMaintenanceCancelRequest501& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onPositionMaintenanceRequest(const Messaging::PositionMaintenanceRequest502& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onAllocationInstruction(const Messaging::AllocationInstruction601& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

    void onOrderMassActionRequest(const Messaging::OrderMassActionRequest701& msg, Testing::Gateway* gateway) override
    {
        onMessage(msg, gateway);
    }

private:
    template <typename Message>
    void onMessage(const Message& msg, Testing::Gateway * gateway)
    {
        std::clog << "\nReceived:\n" << msg << std::endl;

        MessageHolder<BusinessMessageReject206> reject;

        reject->
            setBusinessRejectReason(0)
            .setText("Rejected")
            .setRefMsgType(msg.messageType())
            .setRefSeqNum(msg.businessHeader().msgSeqNum());

        gateway->send(reject, ++reportsCounter_);
        gateway->outSeqNum(reportsCounter_ + 1);

        std::clog << "\nSent:\n" << reject.message() << std::endl;
    }
};

int main(int argc, char * argv[])
{
    clog << "B3 BOE Gateway Emulator Sample." << endl;

    Port port = 49152;
    string host = "127.0.0.1";

    if (argc > 1)
        port = atoi(argv[1]);

    try
    {
        SignalHelper::manageLinuxSignals();

        std::future<void> emulatorTaskDone;

        std::promise<void> emulatorTaskPromise;
        emulatorTaskDone = emulatorTaskPromise.get_future();

        std::unique_ptr<Testing::Gateway> gateway(
            new Testing::Gateway(fillSettings(true).licenseStores(), port, host.c_str()));

        gateway->enableLogger("GatewayEmulatorSample.log");

        std::atomic<bool> stopRequested(false);

        std::thread(std::bind([&](std::promise<void>& p)
        {
            try
            {
                GatewaySampleListener clientMessageListener;
                bool connectionAccepted = false;

                while(!stopRequested && !connectionAccepted)
                    connectionAccepted = gateway->tryAcceptConnection(std::chrono::milliseconds(1));

                if(connectionAccepted)
                {
                    std::clog << "Connection accepted." << endl;

                    gateway->acceptSession();

                    std::clog << "Session accepted." << endl;

                    const auto terminate = gateway->waitUntilTerminate(&clientMessageListener, nullptr, &stopRequested);

                    if(terminate.valid())
                        std::clog  << "The client has disconnected." << endl;
                }

                p.set_value();
            }
            catch (const std::exception& ex)
            {
                std::cerr << "Exception in Emulator's thread: " << ex.what() << '.' << std::endl;
                p.set_exception(current_exception());
            }
            catch(...)
            {
                std::cerr << "UNKNOWN Exception in Emulator's thread." << std::endl;
                p.set_exception(current_exception());
            }
        },
            std::move(emulatorTaskPromise))
        ).detach();


        Helper::waitUntilEnterKey("terminate the application");
        stopRequested = true;

        if(emulatorTaskDone.valid())
        {
            emulatorTaskDone.wait_for(std::chrono::seconds(10));
            emulatorTaskDone.get();
        }
    }
    catch(const std::exception & ex)
    {
        cerr << "\nEXCEPTION: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
//! [GatewayEmulatorSample]

#else
int main(int, char**)
{
    clog << "Gateway Emulator is not supported." << endl << endl;
    return 0;
}
#endif
