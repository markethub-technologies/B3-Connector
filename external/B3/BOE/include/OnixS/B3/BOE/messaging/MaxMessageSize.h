// Copyright Onix Solutions Limited [OnixS]. All rights reserved.
//
// This software owned by Onix Solutions Limited [OnixS] and is
// protected by copyright law and international copyright treaties.
//
// Access to and use of the software is governed by the terms of the applicable
// OnixS Software Services Agreement (the Agreement) and Customer end user license
// agreements granting a non-assignable, non-transferable and non-exclusive license
// to use the software for it's own data processing purposes under the terms defined
// in the Agreement.
//
// Except as otherwise granted within the terms of the Agreement, copying or
// reproduction of any part of this source code or associated reference material
// to any other location for further reproduction or redistribution, and any
// amendments to this copyright notice, are expressly prohibited.
//
// Any reproduction or redistribution for sale or hiring of the Software not in
// accordance with the terms of the Agreement is a violation of copyright law.
//

#pragma once

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/Compiler.h>

#include <OnixS/B3/BOE/messaging/Fields.h>
#include <OnixS/B3/BOE/messaging/Composites.h>
#include <OnixS/B3/BOE/messaging/SimpleOpenFramingHeader.h>

#include <OnixS/B3/BOE/messaging/MessageSizeTraits.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Maximum supported message size.
ONIXS_B3_BOE_CONST_OR_CONSTEXPR UInt16 MaxB3BOEMessageSize = 65535 - sizeof(SimpleOpenFramingHeader);

#if defined(ONIXS_B3_BOE_CXX11)

/// \private
template <typename Message>
struct MaxMessageSizeTraits
{
    static constexpr bool UseCustomValue = false;
};

/// Calculates the buffer size for a message with the given number of repeating group items.
template<typename Message>
constexpr
MessageSize calculateMaxMessageSize(UInt8 maxGroupItems)
{
    return
        ONIXS_B3_BOE_ASSERT(Message::getMaxMessageSize(maxGroupItems) <= MaxB3BOEMessageSize),
        static_cast<MessageSize>(Message::getMaxMessageSize(maxGroupItems));
}

/// Calculates the buffer size for a message with the given number of repeating group items.
template<typename Message>
constexpr
typename std::enable_if<MaxMessageSizeTraits<Message>::UseCustomValue, MessageSize>::type
getMaxMessageSize(UInt8)
{
    return
        MaxMessageSizeTraits<Message>::calculateMaxMessageSize();
}

/// Calculates the buffer size for a message with the given number of repeating group items.
template<typename Message>
constexpr
typename std::enable_if<!MaxMessageSizeTraits<Message>::UseCustomValue, MessageSize>::type
getMaxMessageSize(UInt8 maxGroupItems)
{
    return calculateMaxMessageSize<Message>(maxGroupItems);
}

/// \private
template<typename Message, UInt8 MaxGroupItems>
struct GetMaxMessageSize
{
    enum {Size = getMaxMessageSize<Message>(MaxGroupItems)};
};

/// \private
template<typename Message>
constexpr
UInt16 getMinMessageSize()
{
    return
        Message::blockLength(Message::Schema::Version)
        + MessageHeader::Size
        + Message::getMinimalVariableFieldsSize(Message::Schema::Version);
}

/// \private
template<typename Message>
struct GetMinMessageSize
{
    enum {Size = getMinMessageSize<Message>()};
};

#else

/// \private
template<typename Message, UInt8>
struct GetMaxMessageSize
{
    enum {Size = MaxB3BOEMessageSize};
};

/// \private
template<typename Message>
struct GetMinMessageSize
{
    enum {Size = sizeof(SimpleOpenFramingHeader) + sizeof(MessageHeader) + 1};
};

#endif

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
