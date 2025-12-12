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

#include <vector>

#include <OnixS/B3/BOE/messaging/MaxMessageSize.h>
#include <OnixS/B3/BOE/messaging/SbeMessage.h>
#include <OnixS/B3/BOE/messaging/NetworkMessage.h>

namespace OnixS
{
    namespace B3
    {
        namespace BOE
        {
            ONIXS_B3_BOE_EXPORTED_CLASS Session;
        }
    }
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// \return the version of the Session’s message schema.
ONIXS_B3_BOE_EXPORTED
Messaging::SchemaVersion getMessagingVersion(const Session&) ONIXS_B3_BOE_NOTHROW;

/// The policy to create messages with null-initialized optional fields.
struct FieldsInitPolicy
{
    /// \private
    template <typename SbeMessageType>
    inline static SbeMessageType createMessage(
        void* data, MessageSize length, SchemaVersion version)
    {
        return SbeMessageType(data, length, version);
    }

    /// \private
    inline static const char* name() ONIXS_B3_BOE_NOTHROW
    {
        return "FieldsInitPolicy";
    }
};

/// The policy to create messages without initialized optional fields.
struct FieldsNoInitPolicy
{
    /// \private
    template <typename SbeMessageType>
    inline static SbeMessageType createMessage(
        void* data, MessageSize length, SchemaVersion version)
    {
        return SbeMessageType(
            data, length, SbeMessage::NoFieldsInit(), version);
    }

    /// \private
    inline static const char* name() ONIXS_B3_BOE_NOTHROW
    {
        return "FieldsNoInitPolicy";
    }
};

/// \private
template <typename MessageType>
struct HeldAdapter : public MessageType
{
    ONIXS_B3_BOE_STATIC_ASSERT((
        IsBaseOf<SbeMessage, MessageType>::value));

    enum { isFix = false };

    typedef MessageType SbeType;

    typedef typename
    SbeType::EncodedLength
        EncodedLength;

    HeldAdapter() ONIXS_B3_BOE_DEFAULT;

    HeldAdapter(
        void* data,
        EncodedLength length,
        SchemaVersion version)
        : MessageType(data, length, version)
    {
    }

    HeldAdapter(
        void* data,
        EncodedLength length,
        SbeMessage::NoFieldsInit,
        SchemaVersion version)
        : MessageType(data, length, version)
    {
    }

    HeldAdapter(
        void* data,
        EncodedLength length,
        SbeMessage::NoInit)
        : MessageType(data, length)
    {
    }

    HeldAdapter(
        void* data,
        EncodedLength length,
        SbeMessage::NoInit,
        SbeMessage::NoCheck)
    ONIXS_B3_BOE_NOTHROW
        : MessageType(
            data,
            length,
            SbeMessage::NoInit(),
            SbeMessage::NoCheck())
    {
    }
};

/// \return a human-readable presentation.
template <typename, size_t, typename>
class MessageHolder;
template <
    template <typename, size_t, typename> class HolderType,
    typename MsgType,
    size_t MaxMessageSize,
    typename MessageInitializer>
inline void toStr(
    std::string& str,
    const HolderType<MsgType, MaxMessageSize, MessageInitializer>& holder)
{
    str += "MessageHolder[";

    str += "BufferSize=";
    toStr(str, holder.BufferSize);

    str += ", MessageInitializer=";
    str += MessageInitializer::name();

    str += ", ";
    toStr(str, *holder.header());

    str += ", ";
    toStr(str, holder.message());

    str += "]";
}

/// \private
ONIXS_B3_BOE_CONST_OR_CONSTEXPR char magicDebugValue = 0x5A;

/// Default maximum number of repeating group items.
ONIXS_B3_BOE_CONST_OR_CONSTEXPR UInt8 DefaultMaxGroupItems = 100;

/**
 * Contains the SimpleOpenFramingHeader, the SBE message, and the data buffer.
 */
template <
    typename MessageTypeT,
    size_t MaxMessageSize =
        GetMaxMessageSize<typename HeldAdapter<MessageTypeT>::SbeType, DefaultMaxGroupItems>::Size,
    typename MessageInitializer = FieldsInitPolicy>
class MessageHolder
{
    typedef typename HeldAdapter<MessageTypeT>::SbeType SbeType;

    ONIXS_B3_BOE_STATIC_ASSERT_MSG(
        (MaxMessageSize >= sizeof(MessageHeader)),
        "MaxMessageSize template parameter is too small");

    ONIXS_B3_BOE_STATIC_ASSERT_MSG(
        (MaxMessageSize >= GetMinMessageSize<SbeType>::Size),
        "The buffer can not fit the message");

    ONIXS_B3_BOE_STATIC_ASSERT_MSG(
        (MaxMessageSize <= MaxB3BOEMessageSize),
        "The buffer is too large.");

public:
    /// Message type.
    typedef HeldAdapter<MessageTypeT> MessageType;

    /// Size of the data buffer.
    enum
    {
        BufferSize = MaxMessageSize + sizeof(SimpleOpenFramingHeader)
    };

    explicit MessageHolder(SchemaVersion version = SbeType::Schema::Version)
    {
        init(version);
    }

    explicit MessageHolder(const Session& session)
    {
        init(getMessagingVersion(session));
    }

    MessageHolder(const MessageHolder& r)
    {
        copyFrom(r);
    }

    MessageHolder& operator=(const MessageHolder& r)
    {
        copyFrom(r);
        return *this;
    }

    /// \return the buffer.
    const unsigned char* buffer() const ONIXS_B3_BOE_NOTHROW
    {
        return buffer_;
    }

    /// \return the used size of the buffer.
    UInt16 bufferSize() const ONIXS_B3_BOE_NOTHROW
    {
        return header()->size();
    }

    /// \return the SBE message.
    MessageType& message() ONIXS_B3_BOE_NOTHROW
    {
        return message_;
    }

    /// \return the SBE message.
    const MessageType& message() const ONIXS_B3_BOE_NOTHROW
    {
        return message_;
    }

    /// \return the SBE message size
    UInt16 messageSize() const ONIXS_B3_BOE_NOTHROW
    {
        return bufferSize() - sizeof(SimpleOpenFramingHeader);
    }

    MessageType* operator->() ONIXS_B3_BOE_NOTHROW
    {
        return &message();
    }

    const MessageType* operator->() const ONIXS_B3_BOE_NOTHROW
    {
        return &message();
    }

    const MessageType& operator* () const ONIXS_B3_BOE_NOTHROW
    {
        return message();
    }

    MessageType& operator* () ONIXS_B3_BOE_NOTHROW
    {
        return message();
    }

    /// \return Simple Open Framing Header
    const SimpleOpenFramingHeader* header() const ONIXS_B3_BOE_NOTHROW
    {
        return reinterpret_cast<const SimpleOpenFramingHeader*>(buffer_);
    }

     /// \return Simple Open Framing Header
    SimpleOpenFramingHeader* header() ONIXS_B3_BOE_NOTHROW
    {
        return reinterpret_cast<SimpleOpenFramingHeader*>(buffer_);
    }

    /// Calculates the binary size of the message and updates
    /// the Simple Open Framing Header accordingly.
    ///
    /// \return SBE message size
    MessageSize setHeader() ONIXS_B3_BOE_NOTHROW
    {
        const MessageSize calculatedMessageSize =
            message().calculateBinarySize();

        assert(calculatedMessageSize <= MaxMessageSize);

        assert(
            calculatedMessageSize >=
            SbeType::blockLength(message().version()) +
            MessageHeaderBuilder::Size +
            SbeType::getMinimalVariableFieldsSize(message().version()));

        messageSize(calculatedMessageSize);
        return calculatedMessageSize;
    }

    ///
    NetworkMessage toNetworkMessage() ONIXS_B3_BOE_NOTHROW
    {
        setHeader();

#ifndef NDEBUG
        NetworkMessage(buffer_, BufferSize);
#endif
        return NetworkMessage(buffer_, BufferSize, SbeMessage::NoCheck());
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const
    {
        return toStr(*this);
    }

private:
    void init(SchemaVersion version)
    {
#ifdef ONIXS_B3_BOE_MEMCHECK_DEBUG
        std::memset(buffer_, magicDebugValue, BufferSize);
#endif
        messageSize(0);

        message_ = MessageInitializer::template createMessage<MessageType>(
            buffer_ + sizeof(SimpleOpenFramingHeader), MaxMessageSize, version);
    }

    void messageSize(UInt16 size) ONIXS_B3_BOE_NOTHROW
    {
        header()->setup(
            size + sizeof(SimpleOpenFramingHeader));
    }

    void copyFrom(const MessageHolder& r)
    {
#ifdef ONIXS_B3_BOE_MEMCHECK_DEBUG
        std::memset(buffer_, magicDebugValue, BufferSize);
#endif

        const size_t sizeToCopy = r.message_.MessageType::calculateBinarySize() + sizeof(SimpleOpenFramingHeader);

        assert(r.message_.calculateBinarySize() <= MaxMessageSize);

        std::memcpy(
            buffer_,
            r.buffer_,
            sizeToCopy);

        message_ =
            MessageType(
                buffer_ + sizeof(SimpleOpenFramingHeader),
                MaxMessageSize,
                SbeMessage::NoInit(),
                SbeMessage::NoCheck());
    }

private:
    MessageType message_;
    unsigned char buffer_[BufferSize];
};

template <
    template <typename, size_t, typename> class HolderType,
    typename MsgType,
    size_t MaxMessageSize,
    typename MessageInitializer>
inline std::string toStr(
    const HolderType<MsgType, MaxMessageSize, MessageInitializer>& holder)
{
    std::string res;
    toStr(res, holder);
    return res;
}

template <
    template <typename, size_t, typename> class HolderType,
    typename MsgType,
    size_t MaxMessageSize,
    typename MessageInitializer>
std::ostream& operator<<(
    std::ostream& stream,
    const HolderType<MsgType, MaxMessageSize, MessageInitializer>& rhs)
{
    return stream << toStr(rhs);
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
