#pragma once

#include <atomic>
#include <cstdint>
#include <memory>

#include <OnixS/B3/BOE/SessionListener.h>

#include "../common/MpscPodQueue.hpp"
#include "../events/core/BoeEventPOD.hpp"

namespace spdlog {
  class logger;
}

namespace boe {

  /**
   * OnixS BOE SessionListener implementation.
   *
   * HARD RULE:
   *  - Do the minimum work in each callback:
   *      - build a tiny BoeEventPOD
   *      - enqueue to MPSC queue
   *      - return immediately
   *
   * All serialization / wrapper building happens in the consumer thread (events side).
   */
  class BoeSessionListener final : public OnixS::B3::BOE::SessionListener {
   public:
    struct Deps final {
      std::shared_ptr<spdlog::logger> log;
      MpscPodQueue<events::BoeEventPOD> *queue{nullptr};
    };

    explicit BoeSessionListener(Deps deps);
    ~BoeSessionListener() override = default;

    BoeSessionListener(const BoeSessionListener &) = delete;
    BoeSessionListener &operator=(const BoeSessionListener &) = delete;

    uint64_t enqueued() const noexcept { return enqueued_.load(std::memory_order_relaxed); }
    uint64_t dropped() const noexcept { return dropped_.load(std::memory_order_relaxed); }

    // ---- Key BOE callbacks we care about for order flow ----
    void onExecutionReportNew(const OnixS::B3::BOE::Messaging::ExecutionReportNew200 &msg,
                              OnixS::B3::BOE::Session *sn) override;

    void onExecutionReportModify(const OnixS::B3::BOE::Messaging::ExecutionReportModify201 &msg,
                                 OnixS::B3::BOE::Session *sn) override;

    void onExecutionReportCancel(const OnixS::B3::BOE::Messaging::ExecutionReportCancel202 &msg,
                                 OnixS::B3::BOE::Session *sn) override;

    void onExecutionReportTrade(const OnixS::B3::BOE::Messaging::ExecutionReportTrade203 &msg,
                                OnixS::B3::BOE::Session *sn) override;

    void onExecutionReportReject(const OnixS::B3::BOE::Messaging::ExecutionReportReject204 &msg,
                                 OnixS::B3::BOE::Session *sn) override;

    void onBusinessMessageReject(const OnixS::B3::BOE::Messaging::BusinessMessageReject206 &msg,
                                 OnixS::B3::BOE::Session *sn) override;

    void onOrderMassActionReport(const OnixS::B3::BOE::Messaging::OrderMassActionReport702 &msg,
                                 OnixS::B3::BOE::Session *sn) override;

    // ---- Session lifecycle / observability (optional but useful) ----
    void onEstablishAck(const OnixS::B3::BOE::Messaging::EstablishAck5 &msg,
                        OnixS::B3::BOE::Session *sn) override;

    void onTerminate(const OnixS::B3::BOE::Messaging::Terminate7 &msg,
                     OnixS::B3::BOE::Session *sn) override;

    void onStateChange(OnixS::B3::BOE::SessionStateId::Enum newState,
                       OnixS::B3::BOE::SessionStateId::Enum prevState,
                       OnixS::B3::BOE::Session *sn) override;

    void onError(OnixS::B3::BOE::SessionErrorReason::Enum reason, const std::string &description,
                 OnixS::B3::BOE::Session *sn, OnixS::B3::BOE::Messaging::SbeMessage msg) override;

    void onWarning(OnixS::B3::BOE::SessionWarningReason::Enum reason,
                   const std::string &description, OnixS::B3::BOE::Session *sn,
                   OnixS::B3::BOE::Messaging::SbeMessage msg) override;

    bool isEstablished() const noexcept { return established_.load(std::memory_order_acquire); }

    // Para wiring con BoeSessionSender (gating sin locks).
    const std::atomic_bool &establishedFlag() const noexcept { return established_; }

   private:
    static uint64_t nowNs_() noexcept;
    inline void tryEnqueue_(events::BoeEventPOD &&ev) noexcept;

   private:
    Deps deps_;
    std::atomic<uint64_t> enqueued_{0};
    std::atomic<uint64_t> dropped_{0};
    std::atomic_bool established_{false};
  };

} // namespace boe
