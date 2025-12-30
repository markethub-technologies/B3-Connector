#pragma once
#include <cstdint>

namespace b3::md {

  struct Level {
    int64_t price{0};
    int64_t qty{0};
  };

  class IOrderBookView {
   public:
    virtual ~IOrderBookView() = default;

    virtual uint64_t instrumentId() const noexcept = 0;
    virtual uint64_t exchangeTsNs() const noexcept = 0;

    virtual uint32_t bidCount() const noexcept = 0;
    virtual uint32_t askCount() const noexcept = 0;

    virtual Level bidLevel(uint32_t i) const noexcept = 0;
    virtual Level askLevel(uint32_t i) const noexcept = 0;
  };

} // namespace b3::md