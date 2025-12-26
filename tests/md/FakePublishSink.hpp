#pragma once

#include "../../b3-md-connector/src/publishing/IPublishSink.hpp"
#include "../../b3-md-connector/src/publishing/PublishEvent.hpp"

#include <mutex>
#include <string>
#include <vector>
#include <cstdint>

namespace b3::md::testsupport {

  struct CapturedPublish {
    uint32_t shardId{0};
    std::string topic;
    std::string bytes;
  };

  class FakePublishSink final : public b3::md::publishing::IPublishSink {
   public:
    bool tryPublish(uint32_t shardId,
                    const b3::md::publishing::PublishEvent &ev) noexcept override {
      // En tests está OK usar mutex/vector (no es hot path prod)
      std::lock_guard<std::mutex> g(m_);
      CapturedPublish c;
      c.shardId = shardId;
      c.topic.assign(ev.topic, ev.topic + ev.topicLen);
      c.bytes.assign(reinterpret_cast<const char *>(ev.bytes), ev.size);
      msgs_.push_back(std::move(c));
      return true;
    }

    size_t count() const {
      std::lock_guard<std::mutex> g(m_);
      return msgs_.size();
    }

    CapturedPublish at(size_t i) const {
      std::lock_guard<std::mutex> g(m_);
      return msgs_.at(i);
    }

   private:
    mutable std::mutex m_;
    std::vector<CapturedPublish> msgs_;
  };

} // namespace b3::md::testsupport
