#pragma once

#include <string>
#include <memory>
#include "../sockets/Publisher.h"
#include "../sockets/Subscriber.h"
#include "../models/messages.pb.h"

namespace markethub::messaging::clients {

  /**
   * @brief Base class for a client that publishes requests and subscribes to responses.
   *
   * Combines Publisher and Subscriber functionality with automatic ClientId management.
   */
  class PublisherSubscriber {
   public:
    using MessageReceivedCallback = std::function<void(const WrapperMessage &)>;
    using LogCallback = std::function<void(const std::string &level, const std::string &message)>;

    /**
     * @brief Creates a new instance of PublisherSubscriber.
     *
     * @param clientId Unique client identifier. All messages sent will have this ClientId.
     * @param requestsEndPoint Endpoint where requests will be sent (Publisher connects here)
     * @param listeningEndPoint Endpoint where responses will be received (Subscriber connects here)
     * @param logCallback Optional callback for logging
     */
    PublisherSubscriber(const std::string &clientId, const std::string &requestsEndPoint,
                        const std::string &listeningEndPoint, LogCallback logCallback = nullptr);

    /**
     * @brief Destructor. Automatically stops and cleans up resources (RAII).
     */
    virtual ~PublisherSubscriber();

    // Delete copy constructor and assignment operator (non-copyable)
    PublisherSubscriber(const PublisherSubscriber &) = delete;
    PublisherSubscriber &operator=(const PublisherSubscriber &) = delete;

    /**
     * @brief Starts the client (both Publisher and Subscriber).
     *
     * Subscriber starts first, then configures subscription, then Publisher starts.
     */
    virtual void Start();

    /**
     * @brief Stops the client (both Publisher and Subscriber).
     */
    virtual void Stop();

    /**
     * @brief Sends a message. Automatically sets the ClientId field before sending.
     *
     * Thread-safe.
     * @param message Message to send (ClientId will be overwritten)
     */
    virtual void SendMessage(WrapperMessage &message);

    /**
     * @brief Sends a message (move version - preferred for performance).
     *
     * Automatically sets the ClientId field before sending. Thread-safe.
     * @param message Message to send (will be moved, ClientId will be set)
     */
    virtual void SendMessage(WrapperMessage &&message);

    /**
     * @brief Sets the callback that will be invoked when a response message is received.
     *
     * Should be set before calling Start().
     * @param callback Callback function to invoke on message receipt
     */
    void SetMessageReceivedCallback(MessageReceivedCallback callback) {
      _messageReceivedCallback = callback;
    }

    /**
     * @brief Gets the client ID associated with this instance.
     *
     * All messages sent by this instance will have this ClientId.
     * @return The client ID string
     */
    const std::string &GetClientId() const { return _clientId; }

    /**
     * @brief Gets the startup delay for both Publisher and Subscriber.
     *
     * Default: 1.5 seconds
     * @return The startup delay in milliseconds
     */
    virtual std::chrono::milliseconds GetStartDelay() const;

    /**
     * @brief Sets the startup delay for both Publisher and Subscriber.
     *
     * @param delay The startup delay in milliseconds
     */
    virtual void SetStartDelay(std::chrono::milliseconds delay);

    /**
     * @brief Gets access to the underlying Subscriber (for advanced usage).
     *
     * @return Reference to the Subscriber instance
     */
    sockets::Subscriber &GetSubscriber() { return *_subscriber; }

    /**
     * @brief Gets access to the underlying Publisher (for advanced usage).
     *
     * @return Reference to the Publisher instance
     */
    sockets::Publisher &GetPublisher() { return *_publisher; }

    /**
     * @brief Checks if the client is currently running.
     *
     * @return True if running, false otherwise
     */
    bool IsRunning() const { return _isRunning.load(); }

   protected:
    /**
     * @brief Configures the subscription for this instance.
     *
     * Default implementation subscribes to messages with ClientId as topic.
     * Override to customize subscription behavior.
     * @param subscriber Subscriber to configure
     */
    virtual void ConfigureSubscription(sockets::Subscriber &subscriber);

    /**
     * @brief Internal callback when message is received from Subscriber.
     *
     * Forwards to user-provided callback.
     * @param message The received message
     */
    void OnMessageReceived(const WrapperMessage &message);

   protected:
    const std::string _clientId;                      ///< Unique client identifier
    const std::string _requestsEndPoint;              ///< Endpoint for sending requests
    const std::string _listeningEndPoint;             ///< Endpoint for receiving responses
    LogCallback _logCallback;                         ///< Optional logging callback
    MessageReceivedCallback _messageReceivedCallback; ///< Callback for received messages

    std::unique_ptr<sockets::Publisher> _publisher;   ///< Publisher for sending requests
    std::unique_ptr<sockets::Subscriber> _subscriber; ///< Subscriber for receiving responses

    std::atomic<bool> _isRunning; ///< Flag indicating if the client is running
    std::atomic<bool> _disposed;  ///< Flag indicating if the client is disposed
  };

} // namespace markethub::messaging::clients
