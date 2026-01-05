#pragma once

#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <functional>
#include <zmq.hpp>
#include "../models/messages.pb.h"
#include <variant>

namespace markethub::messaging::sockets {

  struct WireEnvelope final {
    static constexpr size_t kMaxTopic = 128;
    static constexpr size_t kMaxBytes = 16384;

    uint32_t size{0};
    uint8_t topicLen{0};
    char topic[kMaxTopic]{};
    uint8_t bytes[kMaxBytes]{};

    bool setTopic(const char *t, size_t n) noexcept {
      if (!t || n == 0 || n > kMaxTopic)
        return false;
      topicLen = static_cast<uint8_t>(n);
      std::memcpy(topic, t, n);
      return true;
    }

    bool setPayload(const void *p, size_t n) noexcept {
      if (!p || n == 0 || n > kMaxBytes)
        return false;
      size = static_cast<uint32_t>(n);
      std::memcpy(bytes, p, n);
      return true;
    }
  };
  /**
   * @brief Base class for implementing servers that publish messages.
   *
   * Thread-safe publisher that sends WrapperMessage objects via ZeroMQ PUB socket.
   */
  class Publisher {
   public:
    using LogCallback = std::function<void(const std::string &level, const std::string &message)>;

    /**
     * @brief Creates a new instance of Publisher.
     * @param publishingEndPoint ZMQ endpoint (e.g., "tcp://*:5555" or "tcp://localhost:5555")
     * @param isMultiplePublisher If false, uses Bind (single publisher). If true, uses Connect
     * (multiple publishers).
     * @param logCallback Optional callback for logging. nullptr for no logging.
     */
    Publisher(const std::string &publishingEndPoint, bool isMultiplePublisher,
              LogCallback logCallback = nullptr);

    /**
     * @brief Destructor. Automatically stops the publisher and cleans up resources (RAII).
     */
    virtual ~Publisher();

    // Delete copy constructor and assignment operator (non-copyable)
    Publisher(const Publisher &) = delete;
    Publisher &operator=(const Publisher &) = delete;

    /**
     * @brief Starts the publisher background thread.
     *
     * Blocks until the socket is initialized and ready.
     * @throws std::runtime_error If socket initialization fails
     */
    virtual void Start();

    /**
     * @brief Stops the publisher background thread and cleans up resources.
     *
     * Thread-safe, can be called multiple times.
     */
    virtual void Stop();

    /**
     * @brief Enqueues a message for sending.
     *
     * Thread-safe method that adds the message to the send queue.
     * @param message The WrapperMessage to send
     * @throws std::runtime_error If publisher is already disposed
     */
    virtual void SendMessage(const WrapperMessage &message);

    /**
     * @brief Enqueues a message for sending (move version).
     *
     * Thread-safe method that moves the message into the send queue, avoiding copy.
     * @param message The WrapperMessage to send (will be moved)
     * @throws std::runtime_error If publisher is already disposed
     */
    virtual void SendMessage(WrapperMessage &&message);

    // --- Low-latency path: topic+payload ya serializado (sin strings) ---
    virtual void SendSerialized(const char *topic, uint8_t topicLen, const void *payload,
                                uint32_t payloadLen);

    /**
     * @brief Gets the startup delay (slow joiner mitigation).
     *
     * Default: 1.5 seconds
     * @return Startup delay in milliseconds
     */
    virtual std::chrono::milliseconds GetStartDelay() const;

    /**
     * @brief Sets the startup delay (slow joiner mitigation).
     *
     * Must be >= 0. Applied after socket bind/connect.
     * @param delay Startup delay in milliseconds
     */
    virtual void SetStartDelay(std::chrono::milliseconds delay);

    /**
     * @brief Gets the delay after sending each message.
     *
     * Default: 0 (no delay)
     * @return Delay in milliseconds
     */
    virtual std::chrono::milliseconds GetDelayAfterSendMessage() const;

    /**
     * @brief Sets the delay after sending each message.
     *
     * Must be >= 0. Useful for rate limiting.
     * @param delay Delay in milliseconds
     */
    virtual void SetDelayAfterSendMessage(std::chrono::milliseconds delay);

    /**
     * @brief Checks if the publisher is currently running.
     * @return true if running, false otherwise
     */
    bool IsRunning() const { return _isRunning.load(); }

   protected:
    /**
     * @brief Configures and starts the background thread for message publishing.
     */
    virtual void ConfigurePublisherThread();

    /**
     * @brief Main loop that runs in the background thread.
     *
     * Dequeues and sends messages until stopped.
     */
    virtual void PublishingLoop();

    /**
     * @brief Logs a message using the configured log callback.
     * @param level Log level (e.g., "Info", "Warning", "Error")
     * @param message Log message
     */
    void Log(const std::string &level, const std::string &message) const;

   protected:
    // Configuration
    const std::string _publishingEndPoint; ///< ZMQ endpoint for publishing
    const bool _isSinglePublisher;         ///< false = Bind (server), true = Connect (client)
    LogCallback _logCallback;              ///< Optional logging callback

    // Timing configuration
    std::chrono::milliseconds
        _startDelay; ///< Delay after socket initialization (slow joiner mitigation)
    std::chrono::milliseconds
        _delayAfterSendMessage; ///< Delay after sending each message (rate limiting)

    // Message queue (thread-safe)}
    using QueueItem = std::variant<WrapperMessage, WireEnvelope>;
    std::queue<QueueItem> _messagesToSend;
    mutable std::mutex _queueMutex;   ///< Protects message queue
    std::condition_variable _queueCV; ///< Signals when queue has messages

    // Thread control
    std::thread _publisherThread;       ///< Background thread for publishing
    std::atomic<bool> _stopRequested;   ///< Flag to signal thread stop
    std::atomic<bool> _isRunning;       ///< Flag indicating if publisher is running
    std::atomic<bool> _disposed;        ///< Flag indicating if publisher is disposed
    mutable std::mutex _startStopMutex; ///< Protects Start/Stop operations from race conditions

    // Socket initialization synchronization
    std::mutex _initMutex;           ///< Protects socket initialization state
    std::condition_variable _initCV; ///< Signals socket initialization completion
    bool _socketInitialized;         ///< true when socket is ready
    std::string _initError;          ///< Error message if initialization failed
  };

} // namespace markethub::messaging::sockets
