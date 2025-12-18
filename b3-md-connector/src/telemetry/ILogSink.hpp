#pragma once
#include "LogEvent.hpp"

namespace b3::md::telemetry {

class ILogSink {
public:
    virtual ~ILogSink() = default;
    virtual void publish(const LogEvent& e) noexcept = 0;
};

} // namespace b3::md::telemetry
