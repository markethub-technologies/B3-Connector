#pragma once
#include <cstdint>
#include <string_view>

namespace b3::md {

class IMdPublisher {
public:
    virtual ~IMdPublisher() = default;
    virtual void publish(std::string_view topic,
                         const uint8_t* data,
                         size_t size) = 0;
};

} // namespace b3::md