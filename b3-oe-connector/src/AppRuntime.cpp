#include "AppRuntime.h"

#include <stdexcept>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "common/MpscPodQueue.hpp"
#include "common/FixedString.hpp"
#include "events/core/BoeEventPOD.hpp"
#include "events/core/OrderEventProcessingLoop.h" // .h/.cpp
#include "events/core/WrapperSerializer.hpp"
#include "events/publish/MessagingPublisherFacade.hpp"
#include "events/publish/EnvelopePublisher.hpp" // tu .hpp con markethub::messaging::sockets::Publisher

#include "boe/BoeSessionListener.h"
#include "boe/BoeSessionManager.h"
#include "boe/BoeSessionSender.h"

#include "orders/core/OrderTranslator.h"
#include "orders/core/OrderCommandHandler.h"
#include "orders/server/OrderMessagingServer.h"

namespace {

  // Minimal placeholder serializer until you implement protobuf mapping.
  // Keeps runtime wiring compilable.
  class NullWrapperSerializer final : public events::WrapperSerializer {
   public:
    bool trySerialize(const events::BoeEventPOD &, events::SerializedEnvelope &) noexcept override {
      return false; // drop everything until implemented
    }
  };

} // namespace

AppRuntime::AppRuntime(Settings s) : settings_(std::move(s)) {}

AppRuntime::~AppRuntime() {
  try {
    stop(false);
  } catch (...) {
  }
}

void AppRuntime::start() {
  if (started_)
    return;
  if (!built_)
    build_();
  start_();
}

void AppRuntime::stop(bool drain) {
  if (!started_)
    return;
  stop_(drain);
}

void AppRuntime::build_() {
  if (built_)
    return;

  // ---- logger ----
  log_ = spdlog::stdout_color_mt("b3-oe");
  log_->set_level(spdlog::level::info);

  // ---- queue ----
  eventQueue_ = std::make_unique<MpscPodQueue<events::BoeEventPOD>>(settings_.eventQueueCapacity);

  // ---- BOE listener ----
  boeListener_ = std::make_unique<boe::BoeSessionListener>(
      boe::BoeSessionListener::Deps{log_, eventQueue_.get()});

  // ---- BOE session manager ----
  boe::BoeSessionManager::Settings boeS;
  boeS.host = settings_.boeHost;
  boeS.port = settings_.boePort;

  boeS.sessionId = settings_.boeSessionId;
  boeS.accessKey = settings_.boeAccessKey;
  boeS.enteringFirm = settings_.boeEnteringFirm;
  boeS.tradingSystemName = settings_.boeTradingSystemName;

  boeS.licenseStore = settings_.boeLicenseStore;
  boeS.storageDirectory = settings_.boeStorageDirectory;
  boeS.tcpNoDelay = settings_.boeTcpNoDelay;

  boeSession_ = std::make_unique<boe::BoeSessionManager>(
      boe::BoeSessionManager::Deps{log_, boeS, boeListener_.get()});

  // ---- sender (depends on session ptr) ----
  // NOTE: session() is null until createSession_ is implemented properly.
  // You can delay this construction until after boeSession_->start() if needed.
  // For now, build with placeholder session ptr to keep compile; fix once session is created.
  // boeSender_ = std::make_unique<boe::BoeSessionSender>(...);

  // ---- events publisher ----
  // You already have EnvelopePublisher.hpp using markethub::messaging::sockets::Publisher.
  // Here you construct the underlying sockets::Publisher however your lib requires.
  // TODO: create publisher instance:
  // auto pub =
  // std::make_unique<markethub::messaging::sockets::Publisher>(settings_.eventsPubEndpoint);
  // eventsPublisher_ = std::make_unique<events::EnvelopePublisher>(events::EnvelopePublisher::Deps{
  // log_, std::move(pub) });

  // Until we wire the real publisher, keep it null and skip starting eventLoop.
  serializer_ = std::make_unique<NullWrapperSerializer>();

  // ---- event loop ----
  // eventLoop_ requires serializer + publisher; we'll create it when eventsPublisher_ is wired.
  // eventLoop_ = std::make_unique<events::OrderEventProcessingLoop>(...);

  // ---- orders translator/handler/server ----

  orders::OrderTranslator::Deps tdeps;
  tdeps.log = log_;

  // Estos dos deberían venir de settings (config):
  //  - settings_.boeSenderLocation (<=10)
  //  - settings_.boeEnteringTrader (<=5)

  // Si todavía no existen, metelos al Settings de AppRuntime y listo.
  common::fillFixedWithSpaces(tdeps.senderLocation.data(), tdeps.senderLocation.size(),
                              std::string_view{settings_.boeSenderLocation});
  common::fillFixedWithSpaces(tdeps.enteringTrader.data(), tdeps.enteringTrader.size(),
                              std::string_view{settings_.boeEnteringTrader});

  translator_ = std::make_unique<orders::OrderTranslator>(std::move(tdeps));

  // sender_ depends on a real session. We'll finalize wiring in start_() once session exists.
  built_ = true;
}

void AppRuntime::start_() {
  if (started_)
    return;

  // 1) start BOE session (connects)
  boeSession_->start();

  // 2) now we can create the sender with real session ptr
  if (!boeSender_) {
    boeSender_ = std::make_unique<boe::BoeSessionSender>(boe::BoeSessionSender::Deps{
        log_, boeSession_->session(),
        &boeListener_->establishedFlag() // o &boeListener_->establishedAtomic(), como lo nombres
    });
  }

  // 3) orders handler + server
  cmdHandler_ = std::make_unique<orders::OrderCommandHandler>(
      orders::OrderCommandHandler::Deps{log_, translator_.get(), boeSender_.get()});

  orderServer_ = std::make_unique<orders::OrderMessagingServer>(
      orders::OrderMessagingServer::Deps{log_, settings_.ordersBindEndpoint, cmdHandler_.get()});

  orderServer_->start();

  // 4) events pipeline (optional until publisher wired)
  // if (eventsPublisher_) { eventLoop_->start(); }

  started_ = true;
  log_->info("AppRuntime started");
}

void AppRuntime::stop_(bool drain) {
  // stop order server first (stop taking new requests)
  if (orderServer_)
    orderServer_->stop();

  // stop BOE session (stops callbacks)
  if (boeSession_)
    boeSession_->stop();

  // stop event loop last (drain optional)
  if (eventLoop_)
    eventLoop_->stop(drain);

  started_ = false;
  if (log_)
    log_->info("AppRuntime stopped (drain={})", drain);
}
