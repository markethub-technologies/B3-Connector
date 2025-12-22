#include <OnixS/B3/MarketData/UMDF.h>

#include "core/MdPublishPipeline.hpp"
#include "core/MdPublishWorker.hpp"
#include "core/MarketDataEngine.hpp"
#include "onixs/OnixsOrderBookListener.hpp"

#include "mapping/MdSnapshotMapper.hpp"
#include "publishing/IMdPublisher.hpp"
#include "telemetry/LogEvent.hpp"

// TODO: reemplazar por tus implementaciones reales
#include "testsupport/FakePublisher.hpp"   // placeholder publisher
#include "telemetry/SpdlogLogPublisher.hpp"

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace OnixS::B3::MarketData::UMDF;

namespace {

// Config ultra simple: key=value por línea, ignora vacíos y #comentarios.
std::unordered_map<std::string, std::string> loadKeyValueFile(const std::string& path) {
    std::unordered_map<std::string, std::string> kv;

    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "[config] cannot open file: " << path << "\n";
        return kv;
    }

    std::string line;
    while (std::getline(in, line)) {
        // trim básico
        auto trim = [](std::string& s) {
            while (!s.empty() && (s.back() == ' ' || s.back() == '\r' || s.back() == '\n' || s.back() == '\t')) s.pop_back();
            size_t i = 0;
            while (i < s.size() && (s[i] == ' ' || s[i] == '\t')) ++i;
            if (i > 0) s.erase(0, i);
        };

        trim(line);
        if (line.empty()) continue;
        if (!line.empty() && line[0] == '#') continue;

        const auto eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);

        trim(key);
        trim(val);
        if (!key.empty()) kv[key] = val;
    }

    return kv;
}

std::string getOr(const std::unordered_map<std::string, std::string>& kv,
                  const std::string& key,
                  const std::string& def) {
    auto it = kv.find(key);
    return (it == kv.end()) ? def : it->second;
}

int getOrInt(const std::unordered_map<std::string, std::string>& kv,
             const std::string& key,
             int def) {
    auto it = kv.find(key);
    if (it == kv.end()) return def;
    try {
        return std::stoi(it->second);
    } catch (...) {
        return def;
    }
}

} // namespace

int main(int argc, char** argv) {
    const std::string configPath = (argc >= 2) ? argv[1] : "b3-md-connector.conf";
    const auto cfg = loadKeyValueFile(configPath);

    // -------------------------
    // Placeholders / defaults
    // -------------------------
    const std::string licenseDir       = getOr(cfg, "onixs.license_dir",       "./LICENSE_DIR_TODO");
    const std::string connectivityFile = getOr(cfg, "onixs.connectivity_file", "./CONNECTIVITY_TODO.xml");
    const int channel                  = getOrInt(cfg, "onixs.channel",        80);

    const std::string ifA              = getOr(cfg, "onixs.if_a", "");
    const std::string ifB              = getOr(cfg, "onixs.if_b", "");

    const int shards                   = getOrInt(cfg, "md.shards", 4);

    std::cerr << "[startup] config=" << configPath << "\n";
    std::cerr << "[startup] onixs.license_dir=" << licenseDir << "\n";
    std::cerr << "[startup] onixs.connectivity_file=" << connectivityFile << "\n";
    std::cerr << "[startup] onixs.channel=" << channel << "\n";
    std::cerr << "[startup] onixs.if_a=" << (ifA.empty() ? "<auto>" : ifA) << "\n";
    std::cerr << "[startup] onixs.if_b=" << (ifB.empty() ? "<auto>" : ifB) << "\n";
    std::cerr << "[startup] md.shards=" << shards << "\n";

    // -------------------------
    // Pipeline (placeholders)
    // -------------------------
    b3::md::MdSnapshotMapper mapper;
    b3::md::testsupport::FakePublisher publisher; // TODO: reemplazar por ZmqMdPublisher

    std::vector<std::unique_ptr<b3::md::MdPublishWorker>> workers;
    workers.reserve(static_cast<size_t>(shards));

    for (int i = 0; i < shards; ++i) {
        workers.emplace_back(std::make_unique<b3::md::MdPublishWorker>(
            static_cast<uint32_t>(i), mapper, publisher));
    }

    b3::md::MdPublishPipeline pipeline(std::move(workers));
    pipeline.start();

    // -------------------------
    // Engine + Listener OnixS
    // -------------------------
    b3::md::MarketDataEngine engine(pipeline);
    b3::md::onixs::OnixsOrderBookListener orderBookListener(engine);

    // -------------------------
    // OnixS Handler
    // -------------------------
    HandlerSettings settings;
    settings.licenseDirectory = licenseDir.c_str();
    settings.buildOrderBooks  = true;

    // Si conectivityFile está placeholder, igual intentamos: OnixS va a fallar con error claro.
    settings.loadFeeds(channel, connectivityFile.c_str());

    if (!ifA.empty()) settings.networkInterfaceA = ifA.c_str();
    if (!ifB.empty()) settings.networkInterfaceB = ifB.c_str();

    Handler handler(settings);
    handler.registerOrderBookListener(&orderBookListener);

    std::cerr << "[startup] starting OnixS handler...\n";
    handler.start();

    std::cerr << "[runtime] running. Press ENTER to stop...\n";
    std::cin.get();

    std::cerr << "[shutdown] stopping OnixS handler...\n";
    handler.stop(true);

    std::cerr << "[shutdown] stopping pipeline...\n";
    pipeline.stop(true);

    std::cerr << "[shutdown] done.\n";
    return 0;
}
