#pragma once

#include <memory>
#include <string>

#include <b3/common/InstrumentRegistry.hpp>

namespace spdlog {
  class logger;
}

namespace b3::oe::infrastructure {
  class SecurityListClient;
}

namespace events {
  class OrderEventProcessingLoop;
  class WrapperSerializer;
  class MessagingPublisherFacade;
} // namespace events

namespace boe {
  class BoeSessionManager;
  class BoeSessionListener;
  class BoeSessionSender;
} // namespace boe

namespace orders {
  class OrderMessagingServer;
  class OrderTranslator;
  class OrderCommandHandler;
} // namespace orders

template <typename T>
class MpscPodQueue;

namespace events {
  struct BoeEventPOD;
}

class AppRuntime final {
 public:
  struct Settings final {
    // MD connector endpoints (for SecurityList subscription)
    std::string mdRequestEndpoint;  // e.g. "tcp://localhost:8080"
    std::string mdResponseEndpoint; // e.g. "tcp://localhost:8081"

    // endpoints
    std::string ordersBindEndpoint; // e.g. "tcp://*:6001"
    std::string eventsPubEndpoint;  // e.g. "tcp://*:7001" (if needed by publisher)

    // BOE network
    std::string boeHost;
    uint16_t boePort{0};

    // BOE credentials/identity
    uint64_t boeSessionId{0};
    std::string boeAccessKey;
    uint32_t boeEnteringFirm{0};
    std::string boeTradingSystemName;

    // BOE runtime paths
    std::string boeLicenseStore;
    std::string boeStorageDirectory;
    bool boeTcpNoDelay{true};

    // queue sizing
    uint32_t eventQueueCapacity{65536};

    std::string boeSenderLocation;
    std::string boeEnteringTrader;
  };

  explicit AppRuntime(Settings s);
  ~AppRuntime();

  void start();
  void stop(bool drain);

  // Access to instrument registry (populated at startup)
  const b3::common::InstrumentRegistry &registry() const noexcept { return registry_; }

 private:
  void build_();
  void start_();
  void stop_(bool drain);

 private:
  Settings settings_;
  std::shared_ptr<spdlog::logger> log_;

  // ---- instrument registry (loaded at startup) ----
  b3::common::InstrumentRegistry registry_;
  std::unique_ptr<b3::oe::infrastructure::SecurityListClient> securityListClient_;

  // ---- shared infra ----
  std::unique_ptr<MpscPodQueue<events::BoeEventPOD>> eventQueue_;

  // ---- BOE ----
  std::unique_ptr<boe::BoeSessionListener> boeListener_;
  std::unique_ptr<boe::BoeSessionManager> boeSession_;
  std::unique_ptr<boe::BoeSessionSender> boeSender_;

  // ---- events ----
  std::unique_ptr<events::WrapperSerializer> serializer_;             // impl to be provided later
  std::unique_ptr<events::MessagingPublisherFacade> eventsPublisher_; // EnvelopePublisher
  std::unique_ptr<events::OrderEventProcessingLoop> eventLoop_;

  // ---- orders ----
  std::unique_ptr<orders::OrderTranslator> translator_;
  std::unique_ptr<orders::OrderCommandHandler> cmdHandler_;
  std::unique_ptr<orders::OrderMessagingServer> orderServer_;

  bool built_{false};
  bool started_{false};
};
