#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace spdlog {
  class logger;
}

namespace orders {

  /**
   * Request handler boundary for the REP/ROUTER server.
   * Input/Output are raw bytes (wrapper protobuf, etc).
   */
  class IOrderCommandHandler {
   public:
    virtual ~IOrderCommandHandler() = default;

    // Return true => ok response (still bytes)
    // Return false => error response (still bytes; handler decides format)
    virtual bool handleRequest(const uint8_t *req, std::size_t reqSize,
                               std::vector<uint8_t> &outResp) noexcept = 0;
  };

  /**
   * ZMQ ROUTER server for order entry requests.
   *
   * Message framing (ROUTER):
   *   [identity][empty][payload]
   * Response:
   *   [identity][empty][payload]
   *
   * This is intentionally standalone and uses libzmq C API to avoid extra deps.
   */
  class OrderMessagingServer final {
   public:
    struct Deps final {
      std::shared_ptr<spdlog::logger> log;
      std::string bindEndpoint;               // e.g. "tcp://*:6001"
      IOrderCommandHandler *handler{nullptr}; // not owned
    };

    explicit OrderMessagingServer(Deps deps);
    ~OrderMessagingServer();

    OrderMessagingServer(const OrderMessagingServer &) = delete;
    OrderMessagingServer &operator=(const OrderMessagingServer &) = delete;

    void start();
    void stop();

    uint64_t received() const noexcept { return received_.load(std::memory_order_relaxed); }
    uint64_t replied() const noexcept { return replied_.load(std::memory_order_relaxed); }
    uint64_t errors() const noexcept { return errors_.load(std::memory_order_relaxed); }

   private:
    void run_();

   private:
    Deps deps_;

    std::thread th_;
    std::atomic<bool> running_{false};

    void *ctx_{nullptr};
    void *sock_{nullptr};

    std::atomic<uint64_t> received_{0};
    std::atomic<uint64_t> replied_{0};
    std::atomic<uint64_t> errors_{0};
  };

} // namespace orders
