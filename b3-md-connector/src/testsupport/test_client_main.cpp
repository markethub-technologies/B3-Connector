// b3-md-connector/src/testsupport/test_client_main.cpp
//
// Simple test client for B3 Market Data Connector Simulator
//
// This client:
// 1. Subscribes to market data for specified symbols
// 2. Listens for MarketDataUpdate messages
// 3. Prints received data
//
// Usage:
//   ./test_client PETR4 VALE3 ITUB4

#include <clients/PublisherSubscriber.h>
#include <sockets/Subscriber.h>
#include <models/messages.pb.h>

#include <atomic>
#include <chrono>
#include <csignal>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace {
  std::atomic<bool> g_running{true};

  void signalHandler(int signal) {
    std::cerr << "\n[client] Caught signal " << signal << ", shutting down...\n";
    g_running.store(false, std::memory_order_release);
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " SYMBOL1 [SYMBOL2 ...]\n";
    std::cerr << "Example: " << argv[0] << " PETR4 VALE3 ITUB4\n";
    return 1;
  }

  std::vector<std::string> symbols;
  for (int i = 1; i < argc; ++i) {
    symbols.push_back(argv[i]);
  }

  std::cerr << "╔════════════════════════════════════════════════════════════╗\n";
  std::cerr << "║  B3 Market Data Test Client (C++)                         ║\n";
  std::cerr << "╚════════════════════════════════════════════════════════════╝\n";
  std::cerr << "\n";
  std::cerr << "Subscribing to symbols: ";
  for (size_t i = 0; i < symbols.size(); ++i) {
    std::cerr << symbols[i];
    if (i < symbols.size() - 1) std::cerr << ", ";
  }
  std::cerr << "\n\n";

  // Signal handling
  std::signal(SIGINT, signalHandler);
  std::signal(SIGTERM, signalHandler);

  // -------------------------
  // 1. Send subscription request
  // -------------------------
  std::cerr << "[client] Connecting to subscription server...\n";

  using markethub::messaging::clients::PublisherSubscriber;
  using markethub::messaging::WrapperMessage;

  PublisherSubscriber subClient(
      "test-client",
      "tcp://localhost:8080",  // Subscription requests
      "tcp://localhost:8082"   // Subscription responses
  );

  // Response callback
  subClient.SetMessageReceivedCallback([](const WrapperMessage& msg) {
    std::cerr << "[client] Received response: " << msg.message_type() << "\n";
  });

  subClient.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Send subscription request for each symbol
  for (const auto& symbol : symbols) {
    WrapperMessage request;
    request.set_message_type("MarketDataSuscriptionRequest");
    request.set_client_id("test-client");
    request.set_message_id(symbol);  // Use symbol as message ID

    auto* subReq = request.mutable_market_data_suscription_request();
    subReq->mutable_instrument()->set_symbol(symbol);
    subReq->set_subscription_request_type(
        ::markethub::messaging::trading::SNAPSHOT_PLUS_UPDATES);

    std::cerr << "[client] Subscribing to: " << symbol << "\n";
    subClient.SendMessage(std::move(request));
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  // -------------------------
  // 2. Listen for market data
  // -------------------------
  std::cerr << "\n[client] Connecting to market data stream...\n";

  using markethub::messaging::sockets::Subscriber;

  // isMultipleSubscriber = true (client uses Connect, not Bind)
  Subscriber dataClient("tcp://localhost:8081", true);

  std::unordered_map<std::string, uint64_t> messageCount;
  std::unordered_map<std::string, double> lastPrice;

  dataClient.SetMessageReceivedCallback([&](const WrapperMessage& msg) {
    if (msg.has_market_data_update()) {
      const auto& update = msg.market_data_update();

      if (update.has_instrument()) {
        const std::string symbol = update.instrument().symbol();

        messageCount[symbol]++;

        // Extract bid/ask info
        const int bidCount = update.bid_lines_size();
        const int askCount = update.offer_lines_size();

        double bestBid = 0.0;
        double bestAsk = 0.0;

        if (bidCount > 0) {
          bestBid = update.bid_lines(0).price();
        }
        if (askCount > 0) {
          bestAsk = update.offer_lines(0).price();
        }

        lastPrice[symbol] = (bestBid + bestAsk) / 2.0;

        // Print update with fixed decimal format
        std::cerr << "[" << symbol << "] "
                  << "Bid=" << std::fixed << std::setprecision(2) << bestBid
                  << " (" << bidCount << " levels) | "
                  << "Ask=" << std::fixed << std::setprecision(2) << bestAsk
                  << " (" << askCount << " levels) | "
                  << "Count=" << messageCount[symbol] << "\n";
      }
    }
  });

  // Subscribe to all symbols
  for (const auto& symbol : symbols) {
    dataClient.Subscribe(symbol);
    std::cerr << "[client] Subscribed to market data topic: " << symbol << "\n";
  }

  dataClient.Start();

  std::cerr << "\n";
  std::cerr << "╔════════════════════════════════════════════════════════════╗\n";
  std::cerr << "║  LISTENING FOR MARKET DATA                                 ║\n";
  std::cerr << "╚════════════════════════════════════════════════════════════╝\n";
  std::cerr << "\n";
  std::cerr << "Press Ctrl+C to stop...\n";
  std::cerr << "\n";

  // -------------------------
  // Runtime
  // -------------------------
  const auto startTime = std::chrono::steady_clock::now();

  while (g_running.load(std::memory_order_acquire)) {
    std::this_thread::sleep_for(std::chrono::seconds(5));

    if (!g_running.load(std::memory_order_acquire)) break;

    // Print periodic stats
    uint64_t total = 0;
    for (const auto& [symbol, count] : messageCount) {
      total += count;
    }

    const auto elapsed = std::chrono::steady_clock::now() - startTime;
    const auto seconds = std::chrono::duration<double>(elapsed).count();
    const double rate = total / seconds;

    std::cerr << "\n[client] Stats: total=" << total
              << " messages, rate=" << rate << " msg/s\n\n";
  }

  // -------------------------
  // Shutdown
  // -------------------------
  std::cerr << "\n[client] Shutting down...\n";

  dataClient.Stop();
  subClient.Stop();

  std::cerr << "\n╔════════════════════════════════════════════════════════════╗\n";
  std::cerr << "║  FINAL STATISTICS                                          ║\n";
  std::cerr << "╚════════════════════════════════════════════════════════════╝\n";
  std::cerr << "\n";

  uint64_t total = 0;
  for (const auto& [symbol, count] : messageCount) {
    std::cerr << "  " << symbol << ": " << count << " messages";
    if (lastPrice.find(symbol) != lastPrice.end()) {
      std::cerr << " (last mid=" << lastPrice[symbol] << ")";
    }
    std::cerr << "\n";
    total += count;
  }

  const auto elapsed = std::chrono::steady_clock::now() - startTime;
  const auto seconds = std::chrono::duration<double>(elapsed).count();
  const double rate = total / seconds;

  std::cerr << "\n";
  std::cerr << "  Total:    " << total << " messages\n";
  std::cerr << "  Duration: " << seconds << " seconds\n";
  std::cerr << "  Rate:     " << rate << " msg/s\n";
  std::cerr << "\n";

  return 0;
}
