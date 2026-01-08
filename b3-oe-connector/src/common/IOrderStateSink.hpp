// src/common/IOrderStateSink.hpp
#pragma once
#include <cstdint>
namespace events { struct BoeEventPOD; }

class IOrderStateSink {
public:
    virtual ~IOrderStateSink() = default;
    virtual void updateFromEventPod(const events::BoeEventPOD& ev) = 0;
};