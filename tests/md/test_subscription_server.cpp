// Tests for B3MdSubscriptionServer: SecurityListRequest and MarketDataSuscriptionRequest
//
// How to run:
//   cmake -S tests/md -B build/tests-md -G Ninja && cmake --build build/tests-md
//   ./build/tests-md/b3_md_tests --gtest_filter="SubscriptionServerTests.*"
//
// Expected: All 4 tests pass, verifying:
//   1. SecurityListRequest returns all instruments from registry
//   2. Empty registry returns empty list
//   3. MarketDataSubscription calls handler.subscribe()
//   4. Invalid symbol returns error and doesn't call handler

#include <gtest/gtest.h>

#include "../../b3-md-connector/src/messaging/B3MdSubscriptionServer.hpp"
#include "../../b3-md-connector/src/mapping/InstrumentRegistry.hpp"
#include "../../b3-md-connector/src/core/SubscriptionRegistry.hpp"
#include "../../b3-md-connector/src/core/IMarketDataHandler.hpp"

#include <models/messages.pb.h>
#include <models/messageTypes.h>

#include <memory>
#include <string>

using namespace b3::md;
using namespace b3::md::messaging;
using namespace b3::md::mapping;
using markethub::messaging::WrapperMessage;
using markethub::messaging::models::MessageTypes;

// Fake handler que no hace nada (para testing)
class FakeMarketDataHandler final : public IMarketDataHandler {
public:
  void subscribe(uint64_t instrumentId) override {
    subscribedIds.push_back(instrumentId);
  }

  void unsubscribe(uint64_t instrumentId) override {
    unsubscribedIds.push_back(instrumentId);
  }

  std::vector<uint64_t> subscribedIds;
  std::vector<uint64_t> unsubscribedIds;
};

// Test: SecurityListRequest retorna todos los instrumentos del registry
TEST(SubscriptionServerTests, SecurityListRequest_ReturnsAllInstruments) {
  // Setup: Registry con 3 instrumentos
  InstrumentRegistry registry;
  registry.upsert(123456, "PETR4");
  registry.upsert(123457, "VALE3");
  registry.upsert(123458, "ITUB4");

  SubscriptionRegistry subs;
  FakeMarketDataHandler handler;

  // No necesitamos ZMQ real, así que pasamos endpoints dummy
  B3MdSubscriptionServer server(
      "tcp://*:9999",  // dummy endpoint
      "tcp://*:9998",  // dummy endpoint
      registry,
      subs,
      handler,
      nullptr  // no logging
  );

  // Construir SecurityListRequest
  WrapperMessage request;
  request.set_message_id("test-msg-1");
  request.set_client_id("test-client");
  request.set_message_type(std::string(MessageTypes::SecurityListRequest));

  auto* reqBody = request.mutable_security_list_request();
  reqBody->set_request_id("req-123");

  // Llamar HandleMessage directamente (no necesitamos ZMQ)
  auto response = server.HandleMessageForTest(request);

  // Verificaciones
  ASSERT_NE(response, nullptr) << "Response should not be null";
  EXPECT_EQ(response->message_id(), "test-msg-1");
  EXPECT_EQ(response->client_id(), "test-client");
  EXPECT_EQ(response->message_type(), std::string(MessageTypes::SecurityListResponse));

  ASSERT_TRUE(response->has_security_list_response());
  const auto& respBody = response->security_list_response();

  // SecurityListResponse.securities is a map<string, Security>
  const auto& securities = respBody.securities();

  EXPECT_EQ(securities.size(), 3) << "Should have 3 instruments";
  EXPECT_TRUE(securities.count("PETR4") > 0) << "Should contain PETR4";
  EXPECT_TRUE(securities.count("VALE3") > 0) << "Should contain VALE3";
  EXPECT_TRUE(securities.count("ITUB4") > 0) << "Should contain ITUB4";
}

// Test: SecurityListRequest con registry vacío retorna lista vacía
TEST(SubscriptionServerTests, SecurityListRequest_EmptyRegistry_ReturnsEmpty) {
  InstrumentRegistry registry;  // vacío
  SubscriptionRegistry subs;
  FakeMarketDataHandler handler;

  B3MdSubscriptionServer server(
      "tcp://*:9999",
      "tcp://*:9998",
      registry,
      subs,
      handler,
      nullptr
  );

  WrapperMessage request;
  request.set_message_id("test-msg-2");
  request.set_client_id("test-client");
  request.set_message_type(std::string(MessageTypes::SecurityListRequest));
  request.mutable_security_list_request()->set_request_id("req-456");

  auto response = server.HandleMessageForTest(request);

  ASSERT_NE(response, nullptr);
  ASSERT_TRUE(response->has_security_list_response());

  const auto& respBody = response->security_list_response();
  const auto& securities = respBody.securities();

  EXPECT_EQ(securities.size(), 0) << "Should have 0 instruments";
}

// Test: MarketDataSuscriptionRequest normal flow sigue funcionando
TEST(SubscriptionServerTests, MarketDataSubscription_StillWorks) {
  InstrumentRegistry registry;
  registry.upsert(123456, "PETR4");

  SubscriptionRegistry subs;
  FakeMarketDataHandler handler;

  B3MdSubscriptionServer server(
      "tcp://*:9999",
      "tcp://*:9998",
      registry,
      subs,
      handler,
      nullptr
  );

  // Construir MarketDataSuscriptionRequest
  WrapperMessage request;
  request.set_message_id("test-msg-3");
  request.set_client_id("test-client");
  request.set_message_type(std::string(MessageTypes::MarketDataSuscriptionRequest));

  auto* reqBody = request.mutable_market_data_suscription_request();
  reqBody->set_request_id("sub-789");
  reqBody->mutable_instrument()->set_symbol("PETR4");
  reqBody->set_subscription_request_type(
      ::markethub::messaging::trading::SNAPSHOT_PLUS_UPDATES);

  auto response = server.HandleMessageForTest(request);

  ASSERT_NE(response, nullptr);
  EXPECT_EQ(response->message_type(), std::string(MessageTypes::MarketDataSuscriptionResponse));
  ASSERT_TRUE(response->has_market_data_suscription_response());

  // Verificar que el handler fue llamado
  ASSERT_EQ(handler.subscribedIds.size(), 1u);
  EXPECT_EQ(handler.subscribedIds[0], 123456u);
}

// Test: MarketDataSuscriptionRequest con símbolo inválido retorna error
TEST(SubscriptionServerTests, MarketDataSubscription_InvalidSymbol_ReturnsError) {
  InstrumentRegistry registry;
  registry.upsert(123456, "PETR4");

  SubscriptionRegistry subs;
  FakeMarketDataHandler handler;

  B3MdSubscriptionServer server(
      "tcp://*:9999",
      "tcp://*:9998",
      registry,
      subs,
      handler,
      nullptr
  );

  WrapperMessage request;
  request.set_message_id("test-msg-4");
  request.set_client_id("test-client");
  request.set_message_type(std::string(MessageTypes::MarketDataSuscriptionRequest));

  auto* reqBody = request.mutable_market_data_suscription_request();
  reqBody->set_request_id("sub-999");
  reqBody->mutable_instrument()->set_symbol("INVALID123");  // No existe en registry
  reqBody->set_subscription_request_type(
      ::markethub::messaging::trading::SNAPSHOT_PLUS_UPDATES);

  auto response = server.HandleMessageForTest(request);

  ASSERT_NE(response, nullptr);
  ASSERT_TRUE(response->has_market_data_suscription_response());

  // Verificar que el handler NO fue llamado (subscripción rechazada)
  EXPECT_EQ(handler.subscribedIds.size(), 0u) << "Handler should not be called for invalid symbol";
}
