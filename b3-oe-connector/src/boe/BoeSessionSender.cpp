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
    if (!deps_.established)
      throw std::runtime_error("BoeSessionSender: established flag is null");
  }

  bool BoeSessionSender::isReady() const noexcept {
    if (!deps_.session)
      return false;
    if (!deps_.established)
      return false;
    return deps_.established->load(std::memory_order_acquire);
  }

  void BoeSessionSender::throttle() noexcept {
    // Si no está established, evitamos bloquear al pedo.
    if (!isReady())
      return;

    try {
      deps_.session->throttle();
    } catch (const std::exception &ex) {
      deps_.log->warn("BOE throttle exception: {}", ex.what());
    } catch (...) {
      deps_.log->warn("BOE throttle exception: unknown");
    }
  }

  bool BoeSessionSender::send(const orders::OwnedBoeMessage &msg) noexcept {
    if (!isReady())
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
