#pragma once
#include "IMdPublisher.hpp"
#include <mutex>
#include <string>
#include <vector>

namespace b3::md {

struct PublishedMessage {
    std::string topic;
    std::string bytes;
};

class FakePublisher final : public IMdPublisher {
public:
    void publish(std::string_view topic,
                 const uint8_t* data,
                 size_t size) override {
        std::lock_guard<std::mutex> g(m_);
        PublishedMessage m;
        m.topic.assign(topic.data(), topic.size());
        m.bytes.assign(reinterpret_cast<const char*>(data), size);
        msgs_.push_back(std::move(m));
    }

    size_t count() const {
        std::lock_guard<std::mutex> g(m_);
        return msgs_.size();
    }

    PublishedMessage at(size_t i) const {
        std::lock_guard<std::mutex> g(m_);
        return msgs_.at(i);
    }

private:
    mutable std::mutex m_;
    std::vector<PublishedMessage> msgs_;
};

} // namespace b3::md