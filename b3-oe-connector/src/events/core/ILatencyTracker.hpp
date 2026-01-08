// src/common/ILatencyTracker.hpp
#pragma once
#include <cstdint>

class ILatencyTracker {
public:
    virtual ~ILatencyTracker() = default;
    virtual void onTerminal(uint64_t orderKey, uint64_t tsNs) = 0;
};