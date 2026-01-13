#pragma once
#include <cstddef>
#include <string_view>

namespace common {

  inline void fillFixedWithSpaces(char *dst, std::size_t dstLen, std::string_view src) {
    for (std::size_t i = 0; i < dstLen; ++i) dst[i] = ' ';
    const std::size_t n = (src.size() < dstLen) ? src.size() : dstLen;
    for (std::size_t i = 0; i < n; ++i) dst[i] = src[i];
  }

} // namespace common
