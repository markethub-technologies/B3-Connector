#include "OrderMessagingServer.h"

#include <stdexcept>

#include <spdlog/logger.h>
#include <zmq.h>

namespace orders {

  static void closeNoThrow(void *s) noexcept {
    if (s)
      zmq_close(s);
  }
  static void ctxTermNoThrow(void *c) noexcept {
    if (c)
      zmq_ctx_term(c);
  }

  OrderMessagingServer::OrderMessagingServer(Deps deps) : deps_(std::move(deps)) {
    if (!deps_.log)
      throw std::runtime_error("OrderMessagingServer: log is null");
    if (!deps_.handler)
      throw std::runtime_error("OrderMessagingServer: handler is null");
    if (deps_.bindEndpoint.empty())
      throw std::runtime_error("OrderMessagingServer: bindEndpoint is empty");
  }

  OrderMessagingServer::~OrderMessagingServer() {
    try {
      stop();
    } catch (...) {
    }
  }

  void OrderMessagingServer::start() {
    bool expected = false;
    if (!running_.compare_exchange_strong(expected, true))
      return;

    th_ = std::thread([this] { run_(); });
    deps_.log->info("OrderMessagingServer started at {}", deps_.bindEndpoint);
  }

  void OrderMessagingServer::stop() {
    bool expected = true;
    if (!running_.compare_exchange_strong(expected, false))
      return;

    // Best-effort: closing socket unblocks recv
    closeNoThrow(sock_);
    sock_ = nullptr;

    ctxTermNoThrow(ctx_);
    ctx_ = nullptr;

    if (th_.joinable())
      th_.join();

    deps_.log->info("OrderMessagingServer stopped");
  }

  void OrderMessagingServer::run_() {
    ctx_ = zmq_ctx_new();
    if (!ctx_) {
      deps_.log->error("zmq_ctx_new failed");
      running_.store(false);
      return;
    }

    sock_ = zmq_socket(ctx_, ZMQ_ROUTER);
    if (!sock_) {
      deps_.log->error("zmq_socket(ZMQ_ROUTER) failed");
      ctxTermNoThrow(ctx_);
      ctx_ = nullptr;
      running_.store(false);
      return;
    }

    // Router mandatory identity? not required. Tuning options can be added here.
    // Example: int linger = 0; zmq_setsockopt(sock_, ZMQ_LINGER, &linger, sizeof(linger));

    if (zmq_bind(sock_, deps_.bindEndpoint.c_str()) != 0) {
      deps_.log->error("zmq_bind failed: {}", zmq_strerror(zmq_errno()));
      closeNoThrow(sock_);
      sock_ = nullptr;
      ctxTermNoThrow(ctx_);
      ctx_ = nullptr;
      running_.store(false);
      return;
    }

    while (running_.load(std::memory_order_relaxed)) {
      zmq_msg_t idMsg;
      zmq_msg_init(&idMsg);
      zmq_msg_t emptyMsg;
      zmq_msg_init(&emptyMsg);
      zmq_msg_t payloadMsg;
      zmq_msg_init(&payloadMsg);

      // Receive identity
      if (zmq_msg_recv(&idMsg, sock_, 0) < 0) {
        zmq_msg_close(&idMsg);
        zmq_msg_close(&emptyMsg);
        zmq_msg_close(&payloadMsg);
        if (running_.load(std::memory_order_relaxed))
          deps_.log->warn("recv identity failed: {}", zmq_strerror(zmq_errno()));
        break;
      }

      // Receive empty delimiter
      if (zmq_msg_recv(&emptyMsg, sock_, 0) < 0) {
        zmq_msg_close(&idMsg);
        zmq_msg_close(&emptyMsg);
        zmq_msg_close(&payloadMsg);
        errors_.fetch_add(1, std::memory_order_relaxed);
        continue;
      }

      // Receive payload
      if (zmq_msg_recv(&payloadMsg, sock_, 0) < 0) {
        zmq_msg_close(&idMsg);
        zmq_msg_close(&emptyMsg);
        zmq_msg_close(&payloadMsg);
        errors_.fetch_add(1, std::memory_order_relaxed);
        continue;
      }

      received_.fetch_add(1, std::memory_order_relaxed);

      const auto *reqPtr = static_cast<const uint8_t *>(zmq_msg_data(&payloadMsg));
      const std::size_t reqSize = zmq_msg_size(&payloadMsg);

      std::vector<uint8_t> resp;
      resp.reserve(1024);

      const bool ok = deps_.handler->handleRequest(reqPtr, reqSize, resp);
      if (!ok)
        errors_.fetch_add(1, std::memory_order_relaxed);

      // Reply: [identity][empty][payload]
      // Send identity
      zmq_msg_send(&idMsg, sock_, ZMQ_SNDMORE);

      // Send empty
      zmq_msg_t outEmpty;
      zmq_msg_init_size(&outEmpty, 0);
      zmq_msg_send(&outEmpty, sock_, ZMQ_SNDMORE);
      zmq_msg_close(&outEmpty);

      // Send payload
      zmq_msg_t outPayload;
      zmq_msg_init_size(&outPayload, resp.size());
      if (!resp.empty())
        std::memcpy(zmq_msg_data(&outPayload), resp.data(), resp.size());

      zmq_msg_send(&outPayload, sock_, 0);
      zmq_msg_close(&outPayload);

      replied_.fetch_add(1, std::memory_order_relaxed);

      zmq_msg_close(&idMsg);
      zmq_msg_close(&emptyMsg);
      zmq_msg_close(&payloadMsg);
    }

    closeNoThrow(sock_);
    sock_ = nullptr;
    ctxTermNoThrow(ctx_);
    ctx_ = nullptr;
  }

} // namespace orders
