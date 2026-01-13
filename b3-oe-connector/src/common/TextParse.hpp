#pragma once
#include <charconv>
#include <cstdint>
#include <limits>
#include <string_view>
#include <system_error>

namespace common {

  inline bool tryParseU64(std::string_view s, std::uint64_t &out) noexcept {
    if (s.empty())
      return false;
    std::uint64_t v = 0;
    const char *b = s.data();
    const char *e = b + s.size();
    auto res = std::from_chars(b, e, v, 10);
    if (res.ec != std::errc{} || res.ptr != e)
      return false;
    out = v;
    return true;
  }

  inline bool tryParseUnsignedLong(std::string_view s, unsigned long &out) noexcept {
    std::uint64_t v = 0;
    if (!tryParseU64(s, v))
      return false;
    if (v > static_cast<std::uint64_t>(std::numeric_limits<unsigned long>::max()))
      return false;
    out = static_cast<unsigned long>(v);
    return true;
  }

  inline bool tryParseUnsignedInt(std::string_view s, unsigned int &out) noexcept {
    std::uint64_t v = 0;
    if (!tryParseU64(s, v))
      return false;
    if (v > static_cast<std::uint64_t>(std::numeric_limits<unsigned int>::max()))
      return false;
    out = static_cast<unsigned int>(v);
    return true;
  }

  inline std::uint64_t fnv1a64(std::string_view sv) noexcept {
    std::uint64_t h = 1469598103934665603ull;
    for (unsigned char c : sv) {
      h ^= static_cast<std::uint64_t>(c);
      h *= 1099511628211ull;
    }
    return h;
  }

} // namespace common
