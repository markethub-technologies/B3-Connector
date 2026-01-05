#pragma once

#include "../core/BookSnapshot.hpp"
#include "../publishing/SerializedEnvelope.hpp"

#include <cstdint>
#include <string>

// Protobuf (tu lib)
#include <models/messages.pb.h>
#include <models/messageTypes.h>

namespace b3::md::mapping {

  class MdSnapshotMapper final {
   public:
    bool mapToSerializedEnvelope(const b3::md::BookSnapshot &s,
                                 b3::md::publishing::SerializedEnvelope &ev) const noexcept {
      using ::markethub::messaging::WrapperMessage;
      using ::markethub::messaging::models::MessageTypes;

      // Topic ya viene escrito por el worker (topicMapper)
      if (ev.topicLen == 0 || ev.topicLen > b3::md::publishing::SerializedEnvelope::kMaxTopic)
        return false;

      ev.size = 0;

      WrapperMessage msg;
      msg.set_message_type(std::string(MessageTypes::MarketDataUpdate));

      // C# usa ClientId como topic. Acá igual.
      msg.set_client_id(ev.topic, ev.topicLen);
      msg.set_message_id(""); // opcional

      auto *book = msg.mutable_market_data_update();

      auto *inst = book->mutable_instrument();
      inst->set_symbol(ev.topic, ev.topicLen);

      book->set_is_aggregated(true);
      book->set_depth(static_cast<int32_t>((s.bidCount > s.askCount) ? s.bidCount : s.askCount));

      // Si bidCount/askCount ya vienen cappeados por DEPTH, no hace falta min().
      for (int i = 0; i < s.bidCount; ++i) {
        auto *l = book->add_bid_lines();
        l->set_price(s.bids[i].price);
        l->set_quantity(s.bids[i].qty);
      }
      for (int i = 0; i < s.askCount; ++i) {
        auto *l = book->add_offer_lines();
        l->set_price(s.asks[i].price);
        l->set_quantity(s.asks[i].qty);
      }

      const int size = msg.ByteSizeLong();
      if (size <= 0 ||
          static_cast<size_t>(size) > b3::md::publishing::SerializedEnvelope::kMaxBytes)
        return false;

      ev.size = static_cast<uint32_t>(size);
      return msg.SerializeToArray(ev.bytes, size);
    }
  };

} // namespace b3::md::mapping
