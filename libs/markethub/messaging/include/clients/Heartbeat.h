#ifndef MARKETHUB_MESSAGING_CLIENTS_HEARTBEAT_H
#define MARKETHUB_MESSAGING_CLIENTS_HEARTBEAT_H

#include <string>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>
#include <mutex>
#include "../models/messages.pb.h"

namespace markethub::messaging::clients {

  /**
   * @brief Periodic heartbeat generator.
   *
   * Generates heartbeat messages at configurable intervals and notifies via callback.
   */
  class HeartbeatGenerator {
   public:
    /**
     * @brief Callback type invoked when generating a heartbeat.
     */
    using HeartbeatCallback = std::function<void(const WrapperMessage &)>;

    /**
     * @brief Callback type for logging.
     */
    using LogCallback = std::function<void(const std::string &level, const std::string &message)>;

    /**
     * @brief Constructor.
     *
     * @param clientId Client ID to include in heartbeat messages
     * @param logCallback Optional callback for logging
     */
    HeartbeatGenerator(const std::string &clientId, LogCallback logCallback = nullptr);

    /**
     * @brief Destructor. Automatically stops the generator if running.
     */
    virtual ~HeartbeatGenerator();

    // Non-copyable
    HeartbeatGenerator(const HeartbeatGenerator &) = delete;
    HeartbeatGenerator &operator=(const HeartbeatGenerator &) = delete;

    /**
     * @brief Starts heartbeat generation.
     */
    virtual void Start();

    /**
     * @brief Stops heartbeat generation.
     */
    virtual void Stop();

    /**
     * @brief Gets the interval between heartbeat transmissions.
     *
     * @return Interval in seconds
     */
    std::chrono::seconds GetHeartbeatPeriod() const;

    /**
     * @brief Sets the interval between heartbeat transmissions.
     *
     * Template method that accepts any std::chrono::duration type (seconds, milliseconds, hours, etc.)
     * Mimics C# TimeSpan behavior where any duration can be passed and validation occurs at runtime.
     *
     * @tparam Rep Arithmetic type representing the number of ticks
     * @tparam Period std::ratio representing the tick period
     * @param period Interval as a std::chrono::duration (minimum 1 second)
     * @throws std::invalid_argument if period is less than 1 second
     */
    template <typename Rep, typename Period>
    void SetHeartbeatPeriod(std::chrono::duration<Rep, Period> period) {
      // Convert to seconds for comparison and storage
      auto periodInSeconds = std::chrono::duration_cast<std::chrono::seconds>(period);

      // Validate: must be at least 1 second (matching C# behavior)
      if (periodInSeconds.count() < 1) {
        throw std::invalid_argument("Heartbeat period cannot be less than 1 second.");
      }

      std::lock_guard<std::mutex> lock(_mutex);
      _heartbeatPeriod = periodInSeconds;

      Log("Info", "Heartbeat period set to " + std::to_string(_heartbeatPeriod.count()) + " seconds");
    }

    /**
     * @brief Sets the callback to be invoked when generating a heartbeat.
     *
     * @param callback Callback function
     */
    void SetHeartbeatCallback(HeartbeatCallback callback);

   protected:
    /**
     * @brief Main loop that generates heartbeats periodically.
     *
     * Runs in background thread.
     */
    void ProcessHeartbeatLoop();

    /**
     * @brief Logging helper.
     *
     * @param level Log level
     * @param message Log message
     */
    void Log(const std::string &level, const std::string &message) const;

   private:
    const std::string _clientId;           ///< Client identifier
    std::chrono::seconds _heartbeatPeriod; ///< Interval between heartbeats
    HeartbeatCallback _heartbeatCallback;  ///< Callback for heartbeat events
    LogCallback _logCallback;              ///< Optional logging callback

    std::thread _heartbeatThread;     ///< Background thread for heartbeat generation
    std::atomic<bool> _stopRequested; ///< Flag to signal thread stop
    std::atomic<bool> _isRunning;     ///< Flag indicating if generator is running
    std::atomic<bool> _disposed;      ///< Flag indicating if generator is disposed

    mutable std::mutex _mutex; ///< Mutex for thread-safe property access
  };

} // namespace markethub::messaging::clients

#endif // MARKETHUB_MESSAGING_CLIENTS_HEARTBEAT_H
