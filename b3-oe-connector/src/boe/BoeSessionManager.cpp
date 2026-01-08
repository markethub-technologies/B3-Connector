#include "BoeSessionManager.h"

#include <stdexcept>

#include <spdlog/logger.h>

#include <OnixS/B3/BOE/Session.h>
#include <OnixS/B3/BOE/SessionSettings.h>

#include "BoeSessionListener.h"

namespace boe {

  BoeSessionManager::BoeSessionManager(Deps deps) : deps_(std::move(deps)) {
    if (!deps_.log)
      throw std::runtime_error("BoeSessionManager: log is null");
    if (!deps_.listener)
      throw std::runtime_error("BoeSessionManager: listener is null");
  }

  BoeSessionManager::~BoeSessionManager() {
    try {
      stop();
    } catch (...) {
    }
  }

  void BoeSessionManager::createSession_() {
    using namespace OnixS::B3::BOE;

    SessionSettings s;

    // License + identity (as per docs examples)
    if (!deps_.settings.licenseStore.empty())
      s.licenseStore(deps_.settings.licenseStore);

    if (deps_.settings.sessionId != 0)
      s.sessionId(static_cast<Messaging::SessionID>(deps_.settings.sessionId));

    if (!deps_.settings.accessKey.empty())
      s.accessKey(deps_.settings.accessKey);

    if (deps_.settings.enteringFirm != 0)
      s.enteringFirm(deps_.settings.enteringFirm);

    if (!deps_.settings.tradingSystemName.empty())
      s.tradingSystemName(deps_.settings.tradingSystemName);

    // Optional: storage directory
    if (!deps_.settings.storageDirectory.empty())
      s.storageDirectory(deps_.settings.storageDirectory);

    // Latency-friendly TCP
    s.tcpNoDelayOption(deps_.settings.tcpNoDelay);

    // Construct session with settings + listener (docs)
    session_ = std::make_unique<Session>(s, deps_.listener);
  }

  void BoeSessionManager::start() {
    if (started_)
      return;

    if (!session_)
      createSession_();

    if (deps_.settings.host.empty() || deps_.settings.port == 0)
      throw std::runtime_error("BoeSessionManager: host/port not set");

    deps_.log->info("BOE connecting to {}:{} ...", deps_.settings.host, deps_.settings.port);

    // Establish connection (docs)
    session_->connect(deps_.settings.host, static_cast<int>(deps_.settings.port));

    started_ = true;
    deps_.log->info("BOE connected");
  }

  void BoeSessionManager::stop() {
    if (!started_)
      return;

    try {
      // Closing connection (docs)
      session_->disconnect();
    } catch (const std::exception &ex) {
      deps_.log->warn("BOE disconnect exception: {}", ex.what());
    } catch (...) {
      deps_.log->warn("BOE disconnect exception: unknown");
    }

    started_ = false;
    deps_.log->info("BOE disconnected");
  }

} // namespace boe
