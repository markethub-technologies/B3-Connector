#pragma once

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
      OnixS::B3::BOE::Session *session{nullptr}; // not owned
    };

    explicit BoeSessionSender(Deps deps);

    bool isReady() const noexcept;

    void throttle() noexcept; // will call Session::throttle() :contentReference[oaicite:5]{index=5}

    bool send(const orders::OwnedBoeMessage &msg) noexcept;

   private:
    Deps deps_;
  };

} // namespace boe
