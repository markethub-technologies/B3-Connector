#pragma once
#include <cstdint>
#include <type_traits>

namespace b3::md::telemetry {

enum class LogLevel : uint8_t { Health = 0, Info = 1, Error = 2 };

enum class Component : uint8_t {
    Core = 0, Pipeline = 1, Worker = 2, Mapping = 3, Publishing = 4, Adapter = 5
};

enum class Code : uint16_t {
    Startup = 1,
    Shutdown = 2,

    HealthTick = 10,
    Drops = 11,
    QueueSaturated = 12,

    WorkerException = 100,
    PublishFailed = 101,
    SerializeFailed = 102,
    Backpressured = 103,
};

struct LogEvent {
    uint64_t tsNs{0};

    LogLevel level{LogLevel::Info};
    Component component{Component::Core};
    Code code{Code::HealthTick};

    uint32_t instrumentId{0}; // 0 = n/a
    uint16_t shard{0};        // 0 = n/a
    uint16_t reserved{0};

    uint64_t arg0{0};
    uint64_t arg1{0};
};

static_assert(std::is_trivially_copyable_v<LogEvent>);
static_assert(std::is_trivially_destructible_v<LogEvent>);

} // namespace b3::md::telemetry
