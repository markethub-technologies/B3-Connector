#pragma once

#include "../core/BookSnapshot.hpp"
#include "../publishing/SerializedEnvelope.hpp"

#include <cstdint>
#include <cstring>
#include <string>

// Protobuf (tu lib)
#include <models/messages.pb.h>
#include <models/messageTypes.h>

namespace b3::md::mapping {

  class MdSnapshotMapper {
   public:
    virtual ~MdSnapshotMapper() = default;

    virtual bool mapToSerializedEnvelope(const b3::md::BookSnapshot &s,
                                         b3::md::publishing::SerializedEnvelope &ev,
                                         const char* topic,
                                         std::uint8_t topicLen) const noexcept {
      using ::markethub::messaging::WrapperMessage;
      using ::markethub::messaging::models::MessageTypes;

      // Validate topic before processing
      if (topicLen == 0 || topicLen > b3::md::publishing::SerializedEnvelope::kMaxTopic)
        return false;

      ev.size = 0;

      WrapperMessage msg;
      msg.set_message_type(std::string(MessageTypes::MarketDataUpdate));

      // C# usa ClientId como topic. Acá igual.
      msg.set_client_id(topic, topicLen);
      msg.set_message_id(""); // opcional

      auto *book = msg.mutable_market_data_update();

      auto *inst = book->mutable_instrument();
      inst->set_symbol(topic, topicLen);

      book->set_is_aggregated(true);
      book->set_depth(static_cast<int32_t>((s.bidCount > s.askCount) ? s.bidCount : s.askCount));

      // Si bidCount/askCount ya vienen cappeados por DEPTH, no hace falta min().
      // B3 prices are in mantissa format (4 decimal places): price × 10000
      // Convert to readable decimal format: 109000000 → 10900.00
      for (int i = 0; i < s.bidCount; ++i) {
        auto *l = book->add_bid_lines();
        l->set_price(s.bids[i].price / 10000.0);
        l->set_quantity(s.bids[i].qty);
      }
      for (int i = 0; i < s.askCount; ++i) {
        auto *l = book->add_offer_lines();
        l->set_price(s.asks[i].price / 10000.0);
        l->set_quantity(s.asks[i].qty);
      }

      const int size = msg.ByteSizeLong();
      if (size <= 0 ||
          static_cast<size_t>(size) > b3::md::publishing::SerializedEnvelope::kMaxBytes)
        return false;

      ev.size = static_cast<uint32_t>(size);
      if (!msg.SerializeToArray(ev.bytes, size))
        return false;

      // Only write topic if serialization succeeded (fixes state consistency)
      ev.topicLen = topicLen;
      std::memcpy(ev.topic, topic, topicLen);
      return true;
    }
  };

} // namespace b3::md::mapping
