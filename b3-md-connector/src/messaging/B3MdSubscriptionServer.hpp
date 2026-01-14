#pragma once

#include <memory>
#include <string>

#include <b3/common/InstrumentRegistry.hpp>
#include "../core/SubscriptionRegistry.hpp"
#include "../core/IMarketDataHandler.hpp"

// Tu librería
#include <servers/SubscriberPublisher.h>
#include <models/messages.pb.h>
#include <models/messageTypes.h>

namespace b3::md::messaging {

  class B3MdSubscriptionServer final : public markethub::messaging::servers::SubscriberPublisher {
   public:
    B3MdSubscriptionServer(const std::string &serverEndpoint, const std::string &publishingEndpoint,
                           b3::common::InstrumentRegistry &registry,
                           b3::md::SubscriptionRegistry &subs, b3::md::IMarketDataHandler &handler,
                           LogCallback logCb = nullptr);

    // Test accessor - exposes HandleMessage for unit testing
    std::unique_ptr<markethub::messaging::WrapperMessage> HandleMessageForTest(
        const markethub::messaging::WrapperMessage &request) {
      return HandleMessage(request);
    }

   protected:
    std::unique_ptr<markethub::messaging::WrapperMessage> HandleMessage(
        const markethub::messaging::WrapperMessage &request) override;

   private:
    b3::common::InstrumentRegistry &registry_;
    b3::md::SubscriptionRegistry &subs_;
    b3::md::IMarketDataHandler &handler_;
  };

} // namespace b3::md::messaging
