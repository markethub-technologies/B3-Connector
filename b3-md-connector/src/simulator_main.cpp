// b3-md-connector/src/simulator_main.cpp
//
// End-to-End Simulator for B3 Market Data Connector
//
// This executable simulates the complete market data pipeline without
// requiring a real B3 connection. It generates synthetic market data
// for testing the full stack: registry, pipeline, workers, concentrator,
// and subscription server.

#include "core/MdPublishPipeline.hpp"
#include "core/MdPublishWorker.hpp"
#include "core/MarketDataEngine.hpp"
#include "core/SubscriptionRegistry.hpp"
#include "onixs/OnixsOrderBookListener.hpp"
#include "onixs/B3InstrumentRegistryListener.hpp"
#include "mapping/MdSnapshotMapper.hpp"
#include "mapping/InstrumentTopicMapper.hpp"
#include "publishing/ZmqPublishConcentrator.hpp"
#include "messaging/B3MdSubscriptionServer.hpp"
#include "testsupport/FakeOnixsHandler.hpp"

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace {
  std::atomic<bool> g_running{true};

  void signalHandler(int signal) {
    std::cerr << "\n[simulator] Caught signal " << signal << ", shutting down...\n";
    g_running.store(false, std::memory_order_release);
  }
} // namespace

int main(int argc, char **argv) {
  namespace fs = std::filesystem;

  std::cerr << "╔════════════════════════════════════════════════════════════╗\n";
  std::cerr << "║  B3 Market Data Connector - End-to-End Simulator          ║\n";
  std::cerr << "╚════════════════════════════════════════════════════════════╝\n";
  std::cerr << "\n";
  std::cerr << "[simulator] Working directory: " << fs::current_path().string() << "\n";

  // Signal handling
  std::signal(SIGINT, signalHandler);
  std::signal(SIGTERM, signalHandler);

  // -------------------------
  // Configuration
  // -------------------------
  const int shards = 4;
  const std::string subEndpoint = "tcp://*:8080";
  const std::string subResponseEndpoint = "tcp://*:8082";
  const std::string pubEndpoint = "tcp://*:8081";
  const std::string securitiesFile = "b3-md-connector/src/testsupport/securities.json";

  std::cerr << "[simulator] Configuration:\n";
  std::cerr << "  - Shards: " << shards << "\n";
  std::cerr << "  - Subscription endpoint: " << subEndpoint << " (requests)\n";
  std::cerr << "  - Subscription response: " << subResponseEndpoint << " (responses)\n";
  std::cerr << "  - Market data publishing: " << pubEndpoint << "\n";
  std::cerr << "  - Securities file: " << securitiesFile << "\n";
  std::cerr << "\n";

  // -------------------------
  // Pipeline Setup (same as production)
  // -------------------------
  std::cerr << "[simulator] Setting up market data pipeline...\n";

  b3::common::InstrumentRegistry registry;
  b3::md::mapping::InstrumentTopicMapper topicMapper(registry);

  b3::md::publishing::ZmqPublishConcentrator concentrator(pubEndpoint,
                                                          static_cast<uint32_t>(shards));
  concentrator.start();
  std::cerr << "[simulator]   ✓ ZMQ Publisher started on " << pubEndpoint << "\n";

  b3::md::mapping::MdSnapshotMapper mapper;

  std::vector<std::unique_ptr<b3::md::MdPublishWorker>> workers;
  workers.reserve(static_cast<size_t>(shards));
  for (int i = 0; i < shards; ++i) {
    workers.emplace_back(std::make_unique<b3::md::MdPublishWorker>(static_cast<uint32_t>(i), mapper,
                                                                   concentrator, topicMapper));
  }

  b3::md::MdPublishPipeline pipeline(std::move(workers));
  pipeline.start();
  std::cerr << "[simulator]   ✓ Pipeline started with " << shards << " workers\n";

  b3::md::MarketDataEngine engine(pipeline);

  // -------------------------
  // Instrument Registry Setup
  // -------------------------
  std::cerr << "[simulator] Setting up instrument registry...\n";

  b3::md::onixs::B3InstrumentRegistryListener instrumentListener(registry);
  engine.setRegistryReadyFlag(&instrumentListener.readyAtomic());

  b3::md::onixs::OnixsOrderBookListener orderBookListener(engine);

  // -------------------------
  // Subscription Registry & Server
  // -------------------------
  std::cerr << "[simulator] Setting up subscription server...\n";

  b3::md::SubscriptionRegistry subscriptionRegistry;

  // Fake OnixS handler for subscription management
  b3::md::testsupport::FakeOnixsHandler fakeHandler;

  auto logCallback = [](const std::string &level, const std::string &msg) {
    std::cerr << "[sub-server][" << level << "] " << msg << "\n";
  };

  auto subscriptionServer = std::make_unique<b3::md::messaging::B3MdSubscriptionServer>(
      subEndpoint, subResponseEndpoint, registry, subscriptionRegistry,
      fakeHandler, logCallback);

  subscriptionServer->Start();
  std::cerr << "[simulator]   ✓ Subscription server started\n";
  std::cerr << "              (listening on " << subEndpoint << ")\n";

  // -------------------------
  // Load Securities & Trigger SecurityList
  // -------------------------
  std::cerr << "\n[simulator] Loading securities from " << securitiesFile << "...\n";

  if (!fakeHandler.loadSecurities(securitiesFile)) {
    std::cerr << "[simulator] ERROR: Failed to load securities file!\n";
    std::cerr << "[simulator] Make sure " << securitiesFile << " exists.\n";
    return 1;
  }

  std::cerr << "\n[simulator] Setting up registry...\n";
  // Give fake handler access to registry for direct population
  fakeHandler.setRegistry(&registry, &instrumentListener.readyAtomic());

  // Register OrderBook listener (still needed for market data updates)
  fakeHandler.registerOrderBookListener(&orderBookListener);
  std::cerr << "[simulator]   ✓ Handlers configured\n";

  std::cerr << "\n[simulator] Triggering SecurityList (populating registry)...\n";
  fakeHandler.triggerSecurityList();

  if (!instrumentListener.readyAtomic().load(std::memory_order_acquire)) {
    std::cerr << "[simulator] WARNING: Registry not ready after SecurityList!\n";
  } else {
    std::cerr << "[simulator]   ✓ Registry ready!\n";
  }

  // -------------------------
  // Start Market Data Generation
  // -------------------------
  std::cerr << "\n[simulator] Starting market data generation...\n";
  std::cerr << "[simulator] Generating synthetic OrderBook updates every 100ms\n";
  std::cerr << "\n";

  fakeHandler.startUpdateLoop(std::chrono::milliseconds(100));

  // -------------------------
  // Runtime
  // -------------------------
  std::cerr << "╔════════════════════════════════════════════════════════════╗\n";
  std::cerr << "║  SIMULATOR RUNNING                                         ║\n";
  std::cerr << "╚════════════════════════════════════════════════════════════╝\n";
  std::cerr << "\n";
  std::cerr << "  Connect clients to:\n";
  std::cerr << "    - Subscribe: tcp://localhost:8080 (MarketDataSuscriptionRequest)\n";
  std::cerr << "    - Responses: tcp://localhost:8082 (MarketDataSubscriptionResponse)\n";
  std::cerr << "    - Data:      tcp://localhost:8081 (MarketDataUpdate)\n";
  std::cerr << "\n";
  std::cerr << "  Press Ctrl+C to stop...\n";
  std::cerr << "\n";
  std::cerr << "  Note: Worker stats are logged via spdlog every 5 seconds.\n";
  std::cerr << "\n";

  // Wait for shutdown signal
  while (g_running.load(std::memory_order_acquire)) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // -------------------------
  // Shutdown
  // -------------------------
  std::cerr << "\n[simulator] Shutting down...\n";

  std::cerr << "[simulator] Stopping market data generation...\n";
  fakeHandler.stopUpdateLoop();

  std::cerr << "[simulator] Stopping subscription server...\n";
  subscriptionServer->Stop();

  std::cerr << "[simulator] Stopping pipeline...\n";
  pipeline.stop(true);

  std::cerr << "[simulator] Stopping concentrator...\n";
  concentrator.stop();

  std::cerr << "\n[simulator] Shutdown complete.\n";
  return 0;
}
