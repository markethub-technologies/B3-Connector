#ifndef MARKETHUB_MESSAGING_SERVERS_SUBSCRIBERPUBLISHER_H
#define MARKETHUB_MESSAGING_SERVERS_SUBSCRIBERPUBLISHER_H

#include <string>
#include <memory>
#include <functional>
#include <chrono>
#include "../sockets/Subscriber.h"
#include "../sockets/Publisher.h"
#include "../models/messages.pb.h"

namespace markethub::messaging::servers {

  /**
   * @brief Base class for servers that receive requests (Subscriber) and send responses
   * (Publisher).
   *
   * Server-side pattern: listens for incoming requests and publishes responses.
   */
  class SubscriberPublisher {
   public:
    /**
     * @brief Callback type for logging.
     */
    using LogCallback = std::function<void(const std::string &level, const std::string &message)>;

    /**
     * @brief Constructor.
     *
     * @param serverEndpoint Endpoint to listen for requests (BIND mode)
     * @param publishingEndpoint Endpoint to publish responses (BIND mode)
     * @param logCallback Optional callback for logging
     */
    SubscriberPublisher(const std::string &serverEndpoint, const std::string &publishingEndpoint,
                        LogCallback logCallback = nullptr);

    /**
     * @brief Virtual destructor. Automatically stops if running.
     */
    virtual ~SubscriberPublisher();

    // Non-copyable
    SubscriberPublisher(const SubscriberPublisher &) = delete;
    SubscriberPublisher &operator=(const SubscriberPublisher &) = delete;

    /**
     * @brief Starts the server. Begins receiving requests and is ready to send responses.
     *
     * Automatically subscribes to all topics ("").
     */
    virtual void Start();

    /**
     * @brief Stops the server. Stops receiving requests and sending responses.
     */
    virtual void Stop();

    /**
     * @brief Gets the startup delay (wait time after Start before operating).
     *
     * @return The startup delay in milliseconds
     */
    std::chrono::milliseconds GetStartDelay() const;

    /**
     * @brief Sets the startup delay. Applies to both Subscriber and Publisher.
     *
     * Default: 1000ms (1 second).
     * @param delay The startup delay in milliseconds
     */
    void SetStartDelay(std::chrono::milliseconds delay);

    /**
     * @brief Gets the delay after sending each message.
     *
     * @return The delay in milliseconds
     */
    std::chrono::milliseconds GetDelayAfterSendMessage() const;

    /**
     * @brief Sets the delay after sending each message.
     *
     * Default: 0ms (no delay).
     * @param delay The delay in milliseconds
     */
    void SetDelayAfterSendMessage(std::chrono::milliseconds delay);

    /**
     * @brief Sends a message (response) via Publisher.
     *
     * @param message The message to send
     */
    void SendMessage(const WrapperMessage &message);

   protected:
    /**
     * @brief Abstract method that must be implemented by derived classes.
     *
     * Processes a request and returns a response (or nullptr if no response).
     * @param request The received request message
     * @return Response message to send, or nullptr if no response
     */
    virtual std::unique_ptr<WrapperMessage> HandleMessage(const WrapperMessage &request) = 0;

    /**
     * @brief Logging helper.
     *
     * @param level Log level
     * @param message Log message
     */
    void Log(const std::string &level, const std::string &message) const;

    /**
     * @brief Internal callback invoked when a message is received.
     *
     * Calls HandleMessage and sends the response if it exists.
     * @param request The received request message
     */
    void OnMessageReceived(const WrapperMessage &request);

   private:
    std::unique_ptr<sockets::Subscriber> _subscriber; ///< Subscriber for receiving requests
    std::unique_ptr<sockets::Publisher> _publisher;   ///< Publisher for sending responses
    LogCallback _logCallback;                         ///< Optional logging callback

    bool _isRunning; ///< Flag indicating if the server is running
    bool _disposed;  ///< Flag indicating if the server is disposed
  };

} // namespace markethub::messaging::servers

#endif // MARKETHUB_MESSAGING_SERVERS_SUBSCRIBERPUBLISHER_H
