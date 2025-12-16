
#include "MarketDataEngine.hpp"
#include <clients/PublisherSubscriber.h>
#include <models/messages.pb.h>
#include <models/messageTypes.h>
#include <models/risk_management.pb.h>
#include <iostream>
#include <spdlog/spdlog.h>
//#include <OnixS/B3/MarketData/UMDF.h>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <atomic>

namespace {
    std::string GenerateSimpleUUID() {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        std::stringstream ss;
        ss << "msg-" << ms << "-" << std::this_thread::get_id();
        return ss.str();
    }

    void SimpleLogger(const std::string &level, const std::string &message) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::cout << "[" << std::put_time(std::localtime(&time), "%H:%M:%S") << "] "
                  << "[" << level << "] " << message << '\n';
    }
}

int main() {
    // spdlog::info("=== B3 Market Data Connector Test ===");
    // spdlog::info("OnixS C++ B3 Binary UMDF Market Data Handler version {}",
    //              OnixS::B3::MarketData::UMDF::Handler::version());

    // Test configuration
    const std::string SERVER = "Risk01.byma.mkthub.int";
    int RISK_UAT[] = {5955, 5956, 5557};

    std::string REQ_ENDPOINT{"tcp://" + SERVER + ":" + std::to_string(RISK_UAT[0])};
    std::string RES_ENDPOINT{"tcp://" + SERVER + ":" + std::to_string(RISK_UAT[1])};
    std::string RT_ENDPOINT{"tcp://" + SERVER + ":" + std::to_string(RISK_UAT[2])};

    std::string clientId = "95515";
    std::atomic<int> clientResponsesReceived{0};

    // Create PublisherSubscriber client
    markethub::messaging::clients::PublisherSubscriber client(
        clientId,
        REQ_ENDPOINT,
        RES_ENDPOINT,
        SimpleLogger
    );

    // Setup message received callback
    client.SetMessageReceivedCallback([&](const markethub::messaging::WrapperMessage &response) {
        int count = ++clientResponsesReceived;
        std::stringstream ss;
        ss << "Response #" << count << ": " << response.ShortDebugString();
        SimpleLogger("Info", ss.str());
    });

    // Start client
    SimpleLogger("Info", "Starting CLIENT...");
    client.Start();
    SimpleLogger("Info", "CLIENT ready");

    std::cout << "\n=== Press ENTER to send PNL Report Request ===" << std::endl;
    std::string dummy;
    std::getline(std::cin, dummy);

    // Create and send PNL Report Request
    markethub::messaging::WrapperMessage msg;
    msg.set_message_id(GenerateSimpleUUID());
    msg.set_message_type(markethub::messaging::models::MessageTypes::PNLReportRequest);

    auto *pnl = msg.mutable_pnl_report_request();
    pnl->set_market("byma");
    pnl->set_account("10410");

    client.SendMessage(std::move(msg));
    SimpleLogger("Info", "PNL Report Request sent");

    std::cout << "\n=== Press ENTER to exit ===" << std::endl;
    std::getline(std::cin, dummy);

    SimpleLogger("Info", "Shutting down...");
    client.Stop();

    spdlog::info("Total responses received: {}", clientResponsesReceived.load());
    spdlog::info("Test completed successfully");

    return 0;
}