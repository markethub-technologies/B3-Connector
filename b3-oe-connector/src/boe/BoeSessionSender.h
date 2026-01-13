#pragma once

#include <atomic>
#include <memory>

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

namespace orders {
  class OwnedBoeMessage;
}

namespace boe {

  class BoeSessionSender final {
   public:
    struct Deps final {
      std::shared_ptr<spdlog::logger> log;
      OnixS::B3::BOE::Session *session{nullptr};    // not owned
      const std::atomic_bool *established{nullptr}; // not owned (owned by listener/manager)
    };

    explicit BoeSessionSender(Deps deps);

    bool isReady() const noexcept;

    void throttle() noexcept;

    bool send(const orders::OwnedBoeMessage &msg) noexcept;

   private:
    Deps deps_;
  };

} // namespace boe
