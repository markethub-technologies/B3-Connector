#include "AppRuntime.h"
#include "common/ConfigParser.hpp"

#include <csignal>
#include <atomic>
#include <iostream>
#include <thread>

static std::atomic<bool> g_stop{false};

static void onSig(int) { g_stop.store(true); }

int main(int argc, char *argv[]) {
  std::signal(SIGINT, onSig);
  std::signal(SIGTERM, onSig);

  // Load configuration file
  std::string configPath = "b3-oe-connector.conf";
  if (argc > 1) {
    configPath = argv[1];
  }

  std::cerr << "[startup] Loading config from: " << configPath << "\n";

  b3::oe::common::ConfigParser::ConfigMap config;
  try {
    config = b3::oe::common::ConfigParser::load(configPath);
  } catch (const std::exception &e) {
    std::cerr << "[startup] ERROR: Failed to load config: " << e.what() << "\n";
    return 1;
  }

  // Parse configuration
  AppRuntime::Settings s;

  try {
    // MD connector endpoints
    s.mdRequestEndpoint = b3::oe::common::ConfigParser::get(config, "md.request.endpoint");
    s.mdResponseEndpoint = b3::oe::common::ConfigParser::get(config, "md.response.endpoint");

    // Order messaging endpoints
    s.ordersBindEndpoint = b3::oe::common::ConfigParser::get(config, "orders.bind.endpoint");
    s.eventsPubEndpoint = b3::oe::common::ConfigParser::get(config, "events.pub.endpoint");

    // BOE session configuration
    s.boeHost = b3::oe::common::ConfigParser::get(config, "boe.host");
    s.boePort = static_cast<uint16_t>(std::stoul(b3::oe::common::ConfigParser::get(config, "boe.port")));
    s.boeSessionId = std::stoull(b3::oe::common::ConfigParser::get(config, "boe.session.id"));
    s.boeAccessKey = b3::oe::common::ConfigParser::get(config, "boe.access.key");
    s.boeEnteringFirm = std::stoul(b3::oe::common::ConfigParser::get(config, "boe.entering.firm"));
    s.boeTradingSystemName = b3::oe::common::ConfigParser::get(config, "boe.trading.system.name");

    // BOE runtime paths
    s.boeLicenseStore = b3::oe::common::ConfigParser::get(config, "boe.license.store");
    s.boeStorageDirectory = b3::oe::common::ConfigParser::get(config, "boe.storage.directory");

    // BOE identity
    s.boeSenderLocation = b3::oe::common::ConfigParser::get(config, "boe.sender.location", "");
    s.boeEnteringTrader = b3::oe::common::ConfigParser::get(config, "boe.entering.trader", "");

    // Performance tuning
    s.eventQueueCapacity = std::stoul(b3::oe::common::ConfigParser::get(config, "event.queue.capacity", "65536"));
    s.boeTcpNoDelay = (b3::oe::common::ConfigParser::get(config, "boe.tcp.no.delay", "true") == "true");

  } catch (const std::exception &e) {
    std::cerr << "[startup] ERROR: Invalid configuration: " << e.what() << "\n";
    return 1;
  }

  // Display configuration
  std::cerr << "[startup] Configuration loaded:\n";
  std::cerr << "[startup]   MD Request: " << s.mdRequestEndpoint << "\n";
  std::cerr << "[startup]   MD Response: " << s.mdResponseEndpoint << "\n";
  std::cerr << "[startup]   Orders Endpoint: " << s.ordersBindEndpoint << "\n";
  std::cerr << "[startup]   Events Endpoint: " << s.eventsPubEndpoint << "\n";
  std::cerr << "[startup]   BOE Host: " << s.boeHost << ":" << s.boePort << "\n";
  std::cerr << "[startup]   Trading System: " << s.boeTradingSystemName << "\n";

  // Start runtime
  AppRuntime app(s);

  try {
    app.start();
  } catch (const std::exception &e) {
    std::cerr << "[startup] ERROR: Failed to start: " << e.what() << "\n";
    return 1;
  }

  std::cerr << "[startup] BOE Connector started. Press Ctrl+C to stop.\n";

  while (!g_stop.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  std::cerr << "[shutdown] Stopping...\n";
  app.stop(false);
  std::cerr << "[shutdown] Stopped.\n";

  return 0;
}
