#pragma once

#include <memory>
#include <string>

#include <OnixS/B3/MarketData/UMDF/Handler.h>

#include "../mapping/InstrumentRegistry.hpp"
#include "../core/SubscriptionRegistry.hpp"

// Tu librería
#include <servers/SubscriberPublisher.h>
#include <models/messages.pb.h>
#include <models/messageTypes.h>

namespace b3::md::messaging {

  class B3MdSubscriptionServer final : public markethub::messaging::servers::SubscriberPublisher {
   public:
    B3MdSubscriptionServer(const std::string &serverEndpoint, const std::string &publishingEndpoint,
                           b3::md::mapping::InstrumentRegistry &registry,
                           b3::md::SubscriptionRegistry &subs,
                           ::OnixS::B3::MarketData::UMDF::Handler &handler,
                           LogCallback logCb = nullptr);

   protected:
    std::unique_ptr<markethub::messaging::WrapperMessage> HandleMessage(
        const markethub::messaging::WrapperMessage &request) override;

   private:
    b3::md::mapping::InstrumentRegistry &registry_;
    b3::md::SubscriptionRegistry &subs_;
    ::OnixS::B3::MarketData::UMDF::Handler &handler_;
  };

} // namespace b3::md::messaging
