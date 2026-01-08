#pragma once

#include <memory>
#include <utility>

namespace OnixS {
  namespace B3 {
    namespace BOE {
      class Session;
      namespace Messaging {
        class SbeMessage;
      }
    } // namespace BOE
  } // namespace B3
} // namespace OnixS

namespace orders {

  /**
   * Type-erased owning wrapper for an outbound BOE message.
   *
   * The underlying BOE message must own its buffer (e.g. Messaging::MessageHolder<T>).
   * We keep ownership via a shared_ptr<void> with a custom deleter.
   *
   * Sender will call session->send(*msgPtr) via the vtable in Sender (see below).
   */
  class OwnedBoeMessage final {
   public:
    OwnedBoeMessage() = default;

    explicit operator bool() const noexcept { return sendFn_ != nullptr; }

    // Calls the stored send function with the stored object.
    bool sendVia(OnixS::B3::BOE::Session &session) const;

    template <typename HolderT>
    static OwnedBoeMessage make(HolderT holder);

   private:
    using SendFn = bool (*)(void *obj, OnixS::B3::BOE::Session &session);

    std::shared_ptr<void> obj_;
    SendFn sendFn_{nullptr};
  };

} // namespace orders

// ---- template impl ----
#include <OnixS/B3/BOE/Session.h>

namespace orders {

  inline bool OwnedBoeMessage::sendVia(OnixS::B3::BOE::Session &session) const {
    if (!sendFn_ || !obj_)
      return false;
    return sendFn_(obj_.get(), session);
  }

  template <typename HolderT>
  inline OwnedBoeMessage OwnedBoeMessage::make(HolderT holder) {
    OwnedBoeMessage out;

    // allocate on heap so lifetime is independent from stack
    auto *heapObj = new HolderT(std::move(holder));

    out.obj_.reset(heapObj, [](void *p) { delete static_cast<HolderT *>(p); });

    out.sendFn_ = [](void *p, OnixS::B3::BOE::Session &sn) -> bool {
      // OnixS docs show sn->send(order) where order is MessageHolder<T>.
      // :contentReference[oaicite:2]{index=2}
      sn.send(*static_cast<HolderT *>(p));
      return true;
    };

    return out;
  }

} // namespace orders
