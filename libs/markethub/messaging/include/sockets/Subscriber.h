#pragma once

#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <functional>
#include <zmq.hpp>
#include "../models/messages.pb.h"

namespace markethub::messaging::sockets {

  /**
   * @brief Base class for implementing clients that subscribe to messages.
   *
   * Thread-safe subscriber that receives WrapperMessage objects via ZeroMQ SUB socket.
   */
  class Subscriber {
   public:
    using MessageReceivedCallback = std::function<void(const WrapperMessage &)>;
    using LogCallback = std::function<void(const std::string &level, const std::string &message)>;

    /**
     * @brief Creates a new instance of Subscriber.
     * @param serverEndPoint ZMQ endpoint (e.g., "tcp://localhost:5555")
     * @param isMultipleSubscriber If false, uses Bind (single subscriber). If true, uses Connect
     * (multiple subscribers).
     * @param logCallback Optional callback for logging. nullptr for no logging.
     */
    Subscriber(const std::string &serverEndPoint, bool isMultipleSubscriber,
               LogCallback logCallback = nullptr);

    /**
     * @brief Destructor. Automatically stops the subscriber and cleans up resources (RAII).
     */
    virtual ~Subscriber();

    // Delete copy constructor and assignment operator (non-copyable)
    Subscriber(const Subscriber &) = delete;
    Subscriber &operator=(const Subscriber &) = delete;

    /**
     * @brief Starts the subscriber background thread.
     *
     * Blocks until the socket is initialized and ready.
     * @throws std::runtime_error If socket initialization fails
     */
    virtual void Start();

    /**
     * @brief Stops the subscriber background thread and cleans up resources.
     *
     * Thread-safe, can be called multiple times.
     */
    virtual void Stop();

    /**
     * @brief Subscribes to a topic (thread-safe).
     *
     * The subscription will be processed asynchronously by the background thread.
     * @param topic Topic to subscribe to. Empty string subscribes to all messages.
     */
    virtual void Subscribe(const std::string &topic);

    /**
     * @brief Unsubscribes from a topic (thread-safe).
     *
     * The unsubscription will be processed asynchronously by the background thread.
     * @param topic Topic to unsubscribe from
     */
    virtual void Unsubscribe(const std::string &topic);

    /**
     * @brief Unsubscribes from all currently subscribed topics.
     */
    virtual void UnsubscribeAll();

    /**
     * @brief Sets the callback that will be invoked when a message is received.
     *
     * Not thread-safe - should be set before calling Start().
     * @param callback Callback function to invoke on message reception
     */
    void SetMessageReceivedCallback(MessageReceivedCallback callback) {
      _messageReceivedCallback = callback;
    }

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
     * @brief Checks if the subscriber is currently running.
     * @return true if running, false otherwise
     */
    bool IsRunning() const { return _isRunning.load(); }

   protected:
    /**
     * @brief Represents a subscription or unsubscription action.
     */
    struct SubscriptionAction {
      bool isSubscribe;  ///< true = subscribe, false = unsubscribe
      std::string topic; ///< Topic name
    };

    /**
     * @brief Result of attempting to receive a message.
     */
    struct ReceiveMessageResult {
      WrapperMessage message; ///< Received message
      bool hasMessage;        ///< true if message was received successfully
      bool shouldContinue;    ///< true if loop should continue
      int errorCount;         ///< Number of consecutive errors

      ReceiveMessageResult() : hasMessage(false), shouldContinue(true), errorCount(0) {}
    };

    /**
     * @brief Configures and starts the background thread for message reception.
     */
    virtual void ConfigureSubscriberThread();

    /**
     * @brief Main loop that runs in the background thread.
     *
     * Receives and processes messages until stopped.
     */
    virtual void ReceiveLoop();

    /**
     * @brief Subscribes to a topic immediately (called from socket thread).
     * @param topic Topic to subscribe to
     * @param socket ZMQ socket reference
     */
    void DoSubscribeToTopic(const std::string &topic, zmq::socket_t &socket);

    /**
     * @brief Unsubscribes from a topic immediately (called from socket thread).
     * @param topic Topic to unsubscribe from
     * @param socket ZMQ socket reference
     */
    void DoUnsubscribeFromTopic(const std::string &topic, zmq::socket_t &socket);

    /**
     * @brief Processes any pending subscription commands from the queue.
     * @param socket ZMQ socket reference
     */
    void ProcessPendingSubscriptions(zmq::socket_t &socket);

    /**
     * @brief Receives the next message from the socket.
     * @param socket ZMQ socket reference
     * @param result Output result structure
     */
    void ReceiveNextMessage(zmq::socket_t &socket, ReceiveMessageResult &result);

    /**
     * @brief Invokes the MessageReceived callback if set.
     * @param message Received message to process
     */
    virtual void OnMessageReceived(const WrapperMessage &message);

    /**
     * @brief Logs a message using the configured log callback.
     * @param level Log level (e.g., "Info", "Warning", "Error")
     * @param message Log message
     */
    void Log(const std::string &level, const std::string &message) const;

   protected:
    // Configuration
    const std::string _serverEndPoint; ///< ZMQ endpoint for subscribing
    const bool _isSingleSubscriber;    ///< false = Bind (server), true = Connect (client)
    LogCallback _logCallback;          ///< Optional logging callback
    MessageReceivedCallback _messageReceivedCallback; ///< Callback for received messages

    // Timing configuration
    std::chrono::milliseconds
        _startDelay; ///< Delay after socket initialization (slow joiner mitigation)

    // Subscription management (thread-safe)
    std::vector<std::string> _subscriptions; ///< List of currently subscribed topics
    mutable std::mutex _subscriptionsMutex;  ///< Protects subscriptions list

    // Command queue for subscribe/unsubscribe operations (thread-safe)
    std::queue<SubscriptionAction> _commandQueue; ///< Queue of pending subscription changes
    std::mutex _commandQueueMutex;                ///< Protects command queue

    // Thread control
    std::thread _receiverThread;      ///< Background thread for receiving messages
    std::atomic<bool> _stopRequested; ///< Flag to signal thread stop
    std::atomic<bool> _isRunning;     ///< Flag indicating if subscriber is running
    std::atomic<bool> _disposed;      ///< Flag indicating if subscriber is disposed

    // Socket initialization synchronization
    std::mutex _initMutex;           ///< Protects socket initialization state
    std::condition_variable _initCV; ///< Signals socket initialization completion
    bool _socketInitialized;         ///< true when socket is ready
    std::string _initError;          ///< Error message if initialization failed
  };

} // namespace markethub::messaging::sockets
