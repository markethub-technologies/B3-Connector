#include "BoeSessionListener.h"

#include <chrono>

#include <spdlog/logger.h>

namespace boe {

  BoeSessionListener::BoeSessionListener(Deps deps) : deps_(std::move(deps)) {
    if (!deps_.queue)
      throw std::runtime_error("BoeSessionListener: queue is null");
    if (!deps_.log)
      throw std::runtime_error("BoeSessionListener: log is null");
  }

  uint64_t BoeSessionListener::nowNs_() noexcept {
    // Use steady_clock for monotonic measurements. If you prefer wall-clock, switch to
    // system_clock.
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
  }

  void BoeSessionListener::tryEnqueue_(events::BoeEventPOD &&ev) noexcept {
    if (deps_.queue->try_enqueue(std::move(ev))) {
      enqueued_.fetch_add(1, std::memory_order_relaxed);
      return;
    }

    // Queue full → drop (caller’s policy). Keep callback fast.
    dropped_.fetch_add(1, std::memory_order_relaxed);
  }

  void BoeSessionListener::onExecutionReportNew(
      const OnixS::B3::BOE::Messaging::ExecutionReportNew200 & /*msg*/,
      OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::ExecutionReportNew;
    ev.tsRecvNs = nowNs_();

    // TODO: copy minimal fields from msg (no heap, no strings):
    // - venueInstrumentId, accountId
    // - clOrdId hash, orderId hash
    // - status/execType/qty/price mantissa/scale
    // - optional text truncated
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onExecutionReportModify(
      const OnixS::B3::BOE::Messaging::ExecutionReportModify201 & /*msg*/,
      OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::ExecutionReportModify;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onExecutionReportCancel(
      const OnixS::B3::BOE::Messaging::ExecutionReportCancel202 & /*msg*/,
      OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::ExecutionReportCancel;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onExecutionReportTrade(
      const OnixS::B3::BOE::Messaging::ExecutionReportTrade203 & /*msg*/,
      OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::ExecutionReportTrade;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onExecutionReportReject(
      const OnixS::B3::BOE::Messaging::ExecutionReportReject204 & /*msg*/,
      OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::ExecutionReportReject;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onBusinessMessageReject(
      const OnixS::B3::BOE::Messaging::BusinessMessageReject206 & /*msg*/,
      OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::BusinessMessageReject;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onOrderMassActionReport(
      const OnixS::B3::BOE::Messaging::OrderMassActionReport702 & /*msg*/,
      OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::OrderMassActionReport;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onStateChange(OnixS::B3::BOE::SessionStateId::Enum /*newState*/,
                                         OnixS::B3::BOE::SessionStateId::Enum /*prevState*/,
                                         OnixS::B3::BOE::Session * /*sn*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::SessionStateChange;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onError(OnixS::B3::BOE::SessionErrorReason::Enum /*reason*/,
                                   const std::string & /*description*/,
                                   OnixS::B3::BOE::Session * /*sn*/,
                                   OnixS::B3::BOE::Messaging::SbeMessage /*msg*/) {
    established_.store(false, std::memory_order_release);

    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::SessionError;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onWarning(OnixS::B3::BOE::SessionWarningReason::Enum /*reason*/,
                                     const std::string & /*description*/,
                                     OnixS::B3::BOE::Session * /*sn*/,
                                     OnixS::B3::BOE::Messaging::SbeMessage /*msg*/) {
    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::SessionWarning;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));
  }

  void BoeSessionListener::onEstablishAck(const OnixS::B3::BOE::Messaging::EstablishAck5 & /*msg*/,
                                          OnixS::B3::BOE::Session * /*sn*/) {
    established_.store(true, std::memory_order_release);

    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::SessionEstablished;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));

    deps_.log->info("BOE session established (onEstablishAck)");
  }

  void BoeSessionListener::onTerminate(const OnixS::B3::BOE::Messaging::Terminate7 & /*msg*/,
                                       OnixS::B3::BOE::Session * /*sn*/) {
    established_.store(false, std::memory_order_release);

    events::BoeEventPOD ev{};
    ev.type = events::BoeEventType::SessionTerminated;
    ev.tsRecvNs = nowNs_();
    tryEnqueue_(std::move(ev));

    deps_.log->warn("BOE session terminated (onTerminate)");
  }

} // namespace boe
