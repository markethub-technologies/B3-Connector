#include <OnixS/B3/MarketData/UMDF.h>

#include "core/MdPublishPipeline.hpp"
#include "core/MdPublishWorker.hpp"
#include "core/MarketDataEngine.hpp"
#include "core/SubscriptionRegistry.hpp"
#include "onixs/OnixsOrderBookListener.hpp"
#include "onixs/OnixsHandlerWrapper.hpp"
#include "onixs/B3InstrumentRegistryListener.hpp"
#include "mapping/MdSnapshotMapper.hpp"
#include "mapping/InstrumentTopicMapper.hpp"
#include "publishing/ZmqPublishConcentrator.hpp"
#include "messaging/B3MdSubscriptionServer.hpp"

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

using namespace OnixS::B3::MarketData::UMDF;

namespace {

  std::string trimCopy(std::string s) {
    auto is_ws = [](unsigned char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; };
    while (!s.empty() && is_ws((unsigned char)s.back())) s.pop_back();
    size_t i = 0;
    while (i < s.size() && is_ws((unsigned char)s[i])) ++i;
    if (i)
      s.erase(0, i);
    return s;
  }

  std::unordered_map<std::string, std::string> loadKeyValueFile(const std::string &path) {
    std::unordered_map<std::string, std::string> kv;
    std::ifstream in(path, std::ios::binary);
    if (!in.is_open()) {
      std::cerr << "[config] cannot open file: " << path << "\n";
      return kv;
    }

    std::string line;
    bool firstLine = true;
    while (std::getline(in, line)) {
      // BOM (UTF-8) en la primera línea
      if (firstLine) {
        firstLine = false;
        if (line.size() >= 3 && (unsigned char)line[0] == 0xEF && (unsigned char)line[1] == 0xBB &&
            (unsigned char)line[2] == 0xBF) {
          line.erase(0, 3);
        }
      }

      line = trimCopy(line);
      if (line.empty() || line[0] == '#')
        continue;

      const auto eq = line.find('=');
      if (eq == std::string::npos)
        continue;

      std::string key = trimCopy(line.substr(0, eq));
      std::string val = trimCopy(line.substr(eq + 1));

      // comentario inline: key=value # comment
      const auto hash = val.find('#');
      if (hash != std::string::npos)
        val = trimCopy(val.substr(0, hash));

      if (!key.empty())
        kv[key] = val;
    }
    return kv;
  }

  std::string getOr(const std::unordered_map<std::string, std::string> &kv, const std::string &key,
                    const std::string &def) {
    auto it = kv.find(key);
    return (it == kv.end()) ? def : it->second;
  }

  int getOrInt(const std::unordered_map<std::string, std::string> &kv, const std::string &key,
               int def) {
    auto it = kv.find(key);
    if (it == kv.end())
      return def;
    try {
      return std::stoi(it->second);
    } catch (...) {
      return def;
    }
  }

  std::string findConfigPath(std::string requested) {
    namespace fs = std::filesystem;
    fs::path p = requested;
    if (fs::exists(p))
      return p.string();

    // si es relativo, probamos subir niveles típicos (build/md)
    if (!p.is_absolute()) {
      fs::path cwd = fs::current_path();
      fs::path p1 = cwd / p;
      if (fs::exists(p1))
        return p1.string();

      fs::path p2 = cwd.parent_path() / p;
      if (fs::exists(p2))
        return p2.string();

      fs::path p3 = cwd.parent_path().parent_path() / p;
      if (fs::exists(p3))
        return p3.string();
    }

    return requested; // fallback (va a fallar y loguea)
  }

} // namespace

int main(int argc, char **argv) {
  namespace fs = std::filesystem;
  std::cerr << "[startup] cwd=" << fs::current_path().string() << "\n";

  std::string requestedConfig = (argc >= 2) ? argv[1] : "b3-md-connector.conf";
  const std::string configPath = findConfigPath(requestedConfig);
  const auto cfg = loadKeyValueFile(configPath);

  // -------------------------
  // Configuration Loading
  // -------------------------
  // Load from b3-md-connector.conf (or file specified as first argument)
  // See b3-md-connector.conf.example for detailed documentation

  // OnixS B3 UMDF Connection Settings
  // TODO: Before running, configure these in b3-md-connector.conf:
  const std::string licenseDir = getOr(cfg, "onixs.license_dir", "./LICENSE_DIR_TODO");
  const std::string connectivityFile =
      getOr(cfg, "onixs.connectivity_file", "./CONNECTIVITY_TODO.xml");
  const int channel = getOrInt(cfg, "onixs.channel", 80);

  // Network interfaces for multicast (Linux only, optional)
  // OnixS will bind to these interfaces to receive B3 multicast feeds
  const std::string ifA = getOr(cfg, "onixs.if_a", "");
  const std::string ifB = getOr(cfg, "onixs.if_b", "");

  // Pipeline Configuration
  const int shards = getOrInt(cfg, "md.shards", 4);

  // Client Communication Endpoints
  // Subscription server: Clients send MarketDataSuscriptionRequest here
  const std::string subEndpoint = getOr(cfg, "sub.endpoint", "tcp://*:8080");
  const std::string subResponseEndpoint = "tcp://*:8082";  // SubscriberPublisher response port (hardcoded)

  // Market data publishing: Clients subscribe to symbols and receive MarketDataUpdate here
  const std::string pubEndpoint = getOr(cfg, "pub.endpoint", "tcp://*:8081");

  std::cerr << "[startup] config=" << configPath << "\n";
  std::cerr << "[startup] onixs.license_dir=" << licenseDir << "\n";
  std::cerr << "[startup] onixs.connectivity_file=" << connectivityFile << "\n";
  std::cerr << "[startup] onixs.channel=" << channel << "\n";
  std::cerr << "[startup] onixs.if_a=" << (ifA.empty() ? "<auto>" : ifA) << "\n";
  std::cerr << "[startup] onixs.if_b=" << (ifB.empty() ? "<auto>" : ifB) << "\n";
  std::cerr << "[startup] md.shards=" << shards << "\n";
  std::cerr << "[startup] sub.endpoint=" << subEndpoint << " (requests)\n";
  std::cerr << "[startup] sub.response.endpoint=" << subResponseEndpoint << " (responses)\n";
  std::cerr << "[startup] pub.endpoint=" << pubEndpoint << " (market data)\n";

  // -------------------------
  // Pipeline publish
  // -------------------------
  b3::md::mapping::InstrumentRegistry registry;
  b3::md::mapping::InstrumentTopicMapper topicMapper(registry);

  b3::md::publishing::ZmqPublishConcentrator concentrator(pubEndpoint,
                                                          static_cast<uint32_t>(shards));
  concentrator.start();

  b3::md::mapping::MdSnapshotMapper mapper;

  std::vector<std::unique_ptr<b3::md::MdPublishWorker>> workers;
  workers.reserve(static_cast<size_t>(shards));
  for (int i = 0; i < shards; ++i) {
    workers.emplace_back(std::make_unique<b3::md::MdPublishWorker>(static_cast<uint32_t>(i), mapper,
                                                                   concentrator, topicMapper));
  }

  b3::md::MdPublishPipeline pipeline(std::move(workers));
  pipeline.start();

  b3::md::MarketDataEngine engine(pipeline);

  b3::md::onixs::B3InstrumentRegistryListener instrumentListener(registry);
  engine.setRegistryReadyFlag(&instrumentListener.readyAtomic());

  b3::md::onixs::OnixsOrderBookListener orderBookListener(engine);

  // -------------------------
  // Subscription Registry (tracks active subscriptions)
  // -------------------------
  b3::md::SubscriptionRegistry subscriptionRegistry;

  // -------------------------
  // OnixS Handler (lifetime fuera del try)
  // -------------------------
  std::unique_ptr<Handler> handler;

  // -------------------------
  // Subscription Server (lifetime fuera del try)
  // -------------------------
  std::unique_ptr<b3::md::messaging::B3MdSubscriptionServer> subscriptionServer;

  try {
    // -------------------------
    // OnixS Handler Configuration
    // -------------------------
    // This is where we configure the connection to B3 UMDF multicast feeds
    HandlerSettings settings;

    // 1. OnixS License (required)
    settings.licenseDirectory = licenseDir.c_str();

    // 2. Enable OrderBook building (required for our use case)
    settings.buildOrderBooks = true;

    // 3. Load B3 multicast feed addresses from XML connectivity file
    // This configures three feeds:
    // - instrumentFeeds: Receives SecurityDefinitions (security list)
    // - incrementalFeeds: Receives real-time OrderBook updates
    // - snapshotFeeds: Recovery feed for missed packets
    settings.loadFeeds(channel, connectivityFile.c_str());

    // 4. Network Interface Configuration (Linux only, optional)
    // If specified, OnixS will bind to these NICs to receive multicast traffic
    // Feed A and B are redundant feeds from B3 for reliability
    if (!ifA.empty())
      settings.networkInterfaceA = ifA.c_str();
    if (!ifB.empty())
      settings.networkInterfaceB = ifB.c_str();

    // -------------------------
    // OnixS Handler Initialization
    // -------------------------
    handler = std::make_unique<Handler>(settings);

    // Register Listeners
    // 1. OrderBookListener: Receives real-time OrderBook updates → MarketDataEngine → Pipeline
    handler->registerOrderBookListener(&orderBookListener);

    // 2. MessageListener: Receives SecurityDefinitions → InstrumentRegistry
    // SecurityDefinitions arrive automatically from the instrumentFeed when handler starts
    // They are sent between two SequenceReset_1 messages (marks the security list batch)
    handler->registerMessageListener(&instrumentListener);

    // -------------------------
    // Start B3 Connection
    // -------------------------
    // This connects to B3 multicast feeds and starts receiving data:
    // 1. InstrumentFeed: SecurityDefinitions populate the InstrumentRegistry
    // 2. After registry is ready, IncrementalFeed: OrderBook updates flow through the pipeline
    // 3. SnapshotFeed: Used for recovery if packets are lost
    std::cerr << "[startup] starting OnixS handler...\n";
    handler->start();

    // At this point:
    // - OnixS is listening on multicast groups
    // - SecurityDefinitions will start arriving and populate the registry
    // - Once registry is ready, OrderBook updates will be processed
    // - Clients can connect and subscribe to symbols

    // -------------------------
    // Subscription Server (on-demand subscriptions)
    // -------------------------
    auto logCallback = [](const std::string& level, const std::string& msg) {
      std::cerr << "[sub-server][" << level << "] " << msg << "\n";
    };

    // Wrap OnixS Handler to implement IMarketDataHandler interface
    b3::md::onixs::OnixsHandlerWrapper handlerWrapper(*handler);

    subscriptionServer = std::make_unique<b3::md::messaging::B3MdSubscriptionServer>(
        subEndpoint,           // tcp://*:8080 - receives MarketDataSuscriptionRequest
        subResponseEndpoint,   // tcp://*:8082 - sends MarketDataSuscriptionResponse
        registry,
        subscriptionRegistry,
        handlerWrapper,
        logCallback);

    std::cerr << "[startup] starting subscription server...\n";
    subscriptionServer->Start();

    std::cerr << "[runtime] running. Press ENTER to stop...\n";
    std::cin.get();

    std::cerr << "[shutdown] stopping subscription server...\n";
    if (subscriptionServer) {
      subscriptionServer->Stop();
    }

    std::cerr << "[shutdown] stopping OnixS handler...\n";
    handler->stop(true);
  } catch (const std::exception &ex) {
    std::cerr << "[fatal] exception: " << ex.what() << "\n";
  } catch (...) {
    std::cerr << "[fatal] unknown exception\n";
  }

  // -------------------------
  // Shutdown (cleanup if exception during startup)
  // -------------------------
  if (subscriptionServer) {
    std::cerr << "[shutdown] stopping subscription server (cleanup)...\n";
    subscriptionServer->Stop();
  }

  std::cerr << "[shutdown] stopping pipeline...\n";
  pipeline.stop(true);

  std::cerr << "[shutdown] stopping publisher concentrator...\n";
  concentrator.stop();

  std::cerr << "[shutdown] done.\n";
  return 0;
}
