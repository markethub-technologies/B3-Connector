#pragma once

#include <b3/common/InstrumentRegistry.hpp>

#include <clients/PublisherSubscriber.h>
#include <models/messages.pb.h>
#include <models/messageTypes.h>

#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <thread>

namespace b3::oe::infrastructure {

  /**
   * @brief Client for loading SecurityList from MD connector at startup
   *
   * Uses SubscriberPublisher pattern to request security lists from MD.
   * Retries every 5 seconds for up to 10 minutes if connection fails.
   * Never aborts - always retries on corrupted/invalid responses.
   */
  class SecurityListClient final {
   public:
    using LogCallback = std::function<void(const std::string &level, const std::string &msg)>;

    struct Config {
      std::string mdRequestEndpoint;   // e.g., "tcp://localhost:8080"
      std::string mdResponseEndpoint;  // e.g., "tcp://localhost:8081"
      std::chrono::seconds retryInterval{5};
      int maxRetries{120};  // 5s * 120 = 10 minutes
    };

    explicit SecurityListClient(b3::common::InstrumentRegistry &registry, const Config &config,
                                LogCallback logCb = nullptr)
        : registry_(registry), config_(config), logCb_(std::move(logCb)) {}

    SecurityListClient(const SecurityListClient &) = delete;
    SecurityListClient &operator=(const SecurityListClient &) = delete;

    ~SecurityListClient() { stop(); }

    /**
     * @brief Load security list from MD connector (blocking)
     *
     * Retries until successful or max retries reached.
     * Returns true if loaded successfully, false if all retries exhausted.
     */
    bool loadSecurityList() {
      log("INFO", "Starting SecurityList load from MD...");
      log("INFO", "  MD Request: " + config_.mdRequestEndpoint);
      log("INFO", "  MD Response: " + config_.mdResponseEndpoint);
      log("INFO", "  Retry interval: " + std::to_string(config_.retryInterval.count()) + "s");
      log("INFO", "  Max retries: " + std::to_string(config_.maxRetries));

      int attempt = 0;
      while (attempt < config_.maxRetries) {
        ++attempt;
        log("INFO", "Attempt " + std::to_string(attempt) + "/" + std::to_string(config_.maxRetries));

        try {
          if (tryLoadOnce()) {
            log("INFO", "SecurityList loaded successfully! Total instruments: " +
                            std::to_string(registry_.size()));
            ready_.store(true, std::memory_order_release);
            return true;
          }
        } catch (const std::exception &e) {
          log("ERROR", "Exception during load attempt: " + std::string(e.what()));
        } catch (...) {
          log("ERROR", "Unknown exception during load attempt");
        }

        if (attempt < config_.maxRetries) {
          log("INFO", "Retrying in " + std::to_string(config_.retryInterval.count()) + " seconds...");
          std::this_thread::sleep_for(config_.retryInterval);
        }
      }

      log("ERROR", "Failed to load SecurityList after " + std::to_string(config_.maxRetries) +
                       " attempts. Giving up.");
      return false;
    }

    bool isReady() const noexcept { return ready_.load(std::memory_order_acquire); }

    void stop() {
      // No background threads to stop in current implementation
      // Future: could add async loading support here
    }

   private:
    bool tryLoadOnce() {
      using namespace markethub::messaging;

      // Create client with unique ID
      std::string clientId = "b3-oe-connector-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());

      log("INFO", "  Creating PublisherSubscriber client...");
      clients::PublisherSubscriber client(clientId, config_.mdRequestEndpoint,
                                          config_.mdResponseEndpoint);

      // Start client
      log("INFO", "  Starting client...");
      client.Start();

      // Give client time to establish connection
      std::this_thread::sleep_for(std::chrono::milliseconds(100));

      // Build SecurityListRequest
      log("INFO", "  Sending SecurityListRequest...");
      WrapperMessage request;
      request.set_message_id(generateMessageId());
      request.set_client_id(clientId);
      request.set_message_type(std::string(models::MessageTypes::SecurityListRequest));

      auto *body = request.mutable_security_list_request();
      body->set_request_id(generateMessageId());

      // Send with 5 second timeout
      auto responses = client.SendAndWaitForResponse(request, std::chrono::seconds(5));

      if (responses.empty()) {
        log("WARN", "  No response received (timeout or MD not ready)");
        return false;
      }

      // Process first response
      const auto &response = responses[0];

      if (response.message_type() != std::string(models::MessageTypes::SecurityListResponse)) {
        log("WARN", "  Unexpected message type: " + response.message_type());
        return false;  // Retry
      }

      if (!response.has_security_list_response()) {
        log("WARN", "  Response missing security_list_response body");
        return false;  // Retry
      }

      const auto &slr = response.security_list_response();

      // Extract securities (success is implied by non-empty list)
      const auto &securities = slr.securities();
      if (securities.empty()) {
        log("WARN", "  MD returned empty security list (may not be ready yet)");
        return false;  // Retry
      }

      log("INFO", "  Received " + std::to_string(securities.size()) + " securities");

      // Populate registry
      int loaded = 0;
      for (const auto &kv : securities) {
        const std::string &symbol = kv.first;
        const auto &security = kv.second;

        // Use protobuf reflection to extract security_id field
        const auto *descriptor = security.GetDescriptor();
        const auto *reflection = security.GetReflection();

        uint64_t securityId = 0;
        const auto *secIdField = descriptor->FindFieldByName("security_id");
        if (!secIdField) {
          secIdField = descriptor->FindFieldByName("instrument_id");
        }
        if (!secIdField) {
          secIdField = descriptor->FindFieldByName("id");
        }

        if (secIdField && secIdField->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
          securityId = reflection->GetUInt64(security, secIdField);
        } else if (secIdField && secIdField->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64) {
          securityId = static_cast<uint64_t>(reflection->GetInt64(security, secIdField));
        }

        if (securityId == 0 || symbol.empty()) {
          log("WARN", "  Skipping invalid security: symbol=" + symbol +
                          ", id=" + std::to_string(securityId));
          continue;
        }

        // Create InstrumentData with minimal fields (symbol + id)
        // Full field extraction would require extensive protobuf reflection
        b3::common::InstrumentData data;
        data.securityId = securityId;
        data.symbol = symbol;

        registry_.upsertFull(securityId, std::move(data));
        ++loaded;
      }

      log("INFO", "  Successfully loaded " + std::to_string(loaded) + " instruments into registry");
      return true;
    }

    std::string generateMessageId() const {
      return "msg-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    }

    void log(const std::string &level, const std::string &msg) const {
      if (logCb_) {
        logCb_(level, "[SecurityListClient] " + msg);
      }
    }

   private:
    b3::common::InstrumentRegistry &registry_;
    Config config_;
    LogCallback logCb_;
    std::atomic<bool> ready_{false};
  };

} // namespace b3::oe::infrastructure
