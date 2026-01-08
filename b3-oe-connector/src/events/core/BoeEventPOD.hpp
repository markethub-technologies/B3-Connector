// src/events/core/BoeEventPOD.h
#pragma once

#include <cstdint>
#include <cstring>
#include <type_traits>

namespace events {

// Keep this small and memcpy-friendly.
// Text is optional and truncated to fit.
constexpr std::size_t kMaxTextLen = 96;

enum class BoeEventType : uint8_t
{
    // Trading / order lifecycle
    ExecutionReportNew,
    ExecutionReportModify,
    ExecutionReportCancel,
    ExecutionReportTrade,
    ExecutionReportReject,
    ExecutionReportForward,

    BusinessMessageReject,
    OrderMassActionReport,

    // Reference / instruments (optional for this app, but handy)
    SecurityDefinitionResponse,

    // Session / health
    SessionStateChange,
    SessionWarning,
    SessionError
};

// Single POD shape for all events.
// If some fields don't apply for a given type, they are left 0 / empty.
struct BoeEventPOD final
{
    BoeEventType type{BoeEventType::SessionWarning};

    // Timing (nanoseconds recommended; source depends on your clock)
    uint64_t tsRecvNs{0};   // when we received/handled callback (local)
    uint64_t tsVenueNs{0};  // if venue message carries a timestamp (optional)

    // Routing / identity
    uint32_t accountId{0};
    uint32_t venueInstrumentId{0};

    // Correlation / keys (hashes to avoid std::string in callback)
    uint64_t orderKey{0};      // your internal stable key if you have one (optional)
    uint64_t clOrdIdHash{0};
    uint64_t orderIdHash{0};   // venue OrderID hash if present

    // Status-like fields (interpretation depends on message type)
    uint8_t orderStatus{0};    // mapped or raw code
    uint8_t execType{0};       // mapped or raw code
    uint16_t reasonCode{0};    // reject / business reject / session reason if you want

    // Quantities / prices (mantissa/scale to avoid floating)
    int64_t qty{0};
    int64_t leavesQty{0};
    int64_t cumQty{0};
    int64_t lastQty{0};

    int64_t priceMantissa{0};
    int32_t priceScale{0};

    // Small text payload (optional) - truncated
    uint8_t textLen{0};
    char text[kMaxTextLen]{};

    void setText(const char* s, std::size_t n) noexcept
    {
        if (!s || n == 0)
        {
            textLen = 0;
            text[0] = '\0';
            return;
        }

        const std::size_t cap = kMaxTextLen - 1;
        const std::size_t copyN = (n > cap) ? cap : n;

        std::memcpy(text, s, copyN);
        text[copyN] = '\0';
        textLen = static_cast<uint8_t>(copyN);
    }

    void setTextCStr(const char* s) noexcept
    {
        if (!s)
        {
            setText(nullptr, 0);
            return;
        }
        setText(s, std::strlen(s));
    }
};

static_assert(std::is_trivially_copyable<BoeEventPOD>::value,
              "BoeEventPOD must be trivially copyable");

} // namespace events
