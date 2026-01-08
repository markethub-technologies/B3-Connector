#include "BoeSessionSender.h"

#include <stdexcept>

#include <spdlog/logger.h>
#include <OnixS/B3/BOE/Session.h>

#include "../orders/core/OwnedBoeMessage.hpp"

namespace boe {

  BoeSessionSender::BoeSessionSender(Deps deps) : deps_(std::move(deps)) {
    if (!deps_.log)
      throw std::runtime_error("BoeSessionSender: log is null");
    if (!deps_.session)
      throw std::runtime_error("BoeSessionSender: session is null");
  }

  bool BoeSessionSender::isReady() const noexcept { return deps_.session != nullptr; }

  void BoeSessionSender::throttle() noexcept {
    try {
      // OnixS recommends calling before each send and it may block.
      // :contentReference[oaicite:6]{index=6}
      deps_.session->throttle();
    } catch (const std::exception &ex) {
      deps_.log->warn("BOE throttle exception: {}", ex.what());
    } catch (...) {
      deps_.log->warn("BOE throttle exception: unknown");
    }
  }

  bool BoeSessionSender::send(const orders::OwnedBoeMessage &msg) noexcept {
    if (!deps_.session)
      return false;
    if (!msg)
      return false;

    try {
      return msg.sendVia(*deps_.session);
    } catch (const std::exception &ex) {
      deps_.log->error("BOE send failed: {}", ex.what());
      return false;
    } catch (...) {
      deps_.log->error("BOE send failed: unknown exception");
      return false;
    }
  }

} // namespace boe
