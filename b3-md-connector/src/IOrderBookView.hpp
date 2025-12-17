#pragma once
#include "TopNBookSnapshot.hpp"
#include <cstdint>

namespace b3::md {

// Vista mínima para leer top niveles dentro del callback.
// Luego creás un adapter a OnixS que implemente esta interfaz.
class IOrderBookView {
public:
    virtual ~IOrderBookView() = default;

    virtual uint32_t instrumentId() const noexcept = 0;
    virtual uint64_t exchangeTsNs() const noexcept = 0;

    virtual uint32_t bidCount() const noexcept = 0;
    virtual uint32_t askCount() const noexcept = 0;

    // i: 0..count-1
    virtual Level bidLevel(uint32_t i) const noexcept = 0;
    virtual Level askLevel(uint32_t i) const noexcept = 0;
};

} // namespace b3::md
