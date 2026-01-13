#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace spdlog {
  class logger;
}

namespace OnixS {
  namespace B3 {
    namespace BOE {
      class Session;
    }
  } // namespace B3
} // namespace OnixS

namespace boe {

  class BoeSessionListener;

  /**
   * Owns and manages the lifetime of an OnixS BOE Session.
   *
   * - Creates/configures session
   * - Attaches listener
   * - Connects/disconnects
   */
  class BoeSessionManager final {
   public:
    struct Settings final {
      // Network
      std::string host;
      uint16_t port{0};

      // BOE identity/credentials (per OnixS docs examples)
      uint64_t sessionId{0};         // "Value received from B3"
      std::string accessKey;         // "Value received from B3"
      uint32_t enteringFirm{0};      // "Value received from B3"
      std::string tradingSystemName; // your system name

      // Files / runtime
      std::string licenseStore;     // path to license folder
      std::string storageDirectory; // msg storage folder (optional)
      bool tcpNoDelay{true};        // latency-friendly default
    };

    struct Deps final {
      std::shared_ptr<spdlog::logger> log;
      Settings settings;
      BoeSessionListener *listener{nullptr}; // not owned
    };

    explicit BoeSessionManager(Deps deps);
    ~BoeSessionManager();

    BoeSessionManager(const BoeSessionManager &) = delete;
    BoeSessionManager &operator=(const BoeSessionManager &) = delete;

    void start();
    void stop();

    bool isStarted() const noexcept { return started_; }
    OnixS::B3::BOE::Session *session() noexcept { return session_.get(); }

    OnixS::B3::BOE::Session *session() const noexcept { return session_.get(); }
    BoeSessionListener *listener() const noexcept { return deps_.listener; }

   private:
    void createSession_();

   private:
    Deps deps_;
    std::unique_ptr<OnixS::B3::BOE::Session> session_;
    bool started_{false};
  };

} // namespace boe
