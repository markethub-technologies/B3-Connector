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

#include <OnixS/B3/BOE/messaging/SimpleOpenFramingHeader.h>
#include <OnixS/B3/BOE/messaging/ExceptionHelpers.h>
#include <OnixS/B3/BOE/messaging/SbeMessage.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// A network BOE message.
ONIXS_B3_BOE_LTWT_CLASS NetworkMessage
{
public:
    /// Constructs an empty instance.
    NetworkMessage() ONIXS_B3_BOE_NOTHROW
        : data_(ONIXS_B3_BOE_NULLPTR)
        , size_(0)
    {}

    /// Constructs NetworkMessage from a data block. Performs no checks.
    NetworkMessage(const void* data, ONIXS_B3_BOE_UNUSED size_t size, SbeMessage::NoCheck) ONIXS_B3_BOE_NOTHROW
        : data_(ONIXS_B3_BOE_NULLPTR)
        , size_(0)
    {
        assert(size >= sizeof(SimpleOpenFramingHeader));

        const SimpleOpenFramingHeader* const header = reinterpret_cast<const SimpleOpenFramingHeader*>(data);

        assert(header->encoding() == B3BOESbeEncodingType);
        assert(header->size() <= size);

#ifndef NDEBUG
        SbeMessage(toByteBlock(toMutable(data)) + sizeof(SimpleOpenFramingHeader), header->size() - sizeof(SimpleOpenFramingHeader));
#endif

        data_ = data;
        size_ = header->size();
    }

    /// Constructs NetworkMessage from a data block.
    NetworkMessage(const void* data, size_t size)
        : data_(ONIXS_B3_BOE_NULLPTR)
        , size_(0)
    {
         if ONIXS_B3_BOE_UNLIKELY(size < sizeof(SimpleOpenFramingHeader))
             throwBinaryBlockIsTooSmall(static_cast<MessageSize>(size), sizeof(SimpleOpenFramingHeader), "SimpleOpenFramingHeader");

        const SimpleOpenFramingHeader* const header = reinterpret_cast<const SimpleOpenFramingHeader*>(data);

        if ONIXS_B3_BOE_UNLIKELY(header->encoding() != B3BOESbeEncodingType)
            throwIncorrectEncoding(header->encoding(), data, static_cast<MessageSize>(size));

        if ONIXS_B3_BOE_UNLIKELY(header->size() > size)
            throwNetPacketIsTooSmall(static_cast<MessageSize>(size), header->size());

        SbeMessage(toByteBlock(toMutable(data)) + sizeof(SimpleOpenFramingHeader), header->size() - sizeof(SimpleOpenFramingHeader));

        data_ = data;
        size_ = header->size();
    }

    ///
    const void* data() const ONIXS_B3_BOE_NOTHROW
    {
        return data_;
    }

    ///
    MessageSize size() const ONIXS_B3_BOE_NOTHROW
    {
        return size_;
    }

    /// Blank the instance.
    void clear() ONIXS_B3_BOE_NOTHROW
    {
        *this = NetworkMessage();
        assert(!valid());
    }

    /// \return `true` if the instance refers to a valid packet, otherwise - `false`.

    bool valid() const ONIXS_B3_BOE_NOTHROW
    {
        return (ONIXS_B3_BOE_NULLPTR != data_);
    }

    /// Retrieves the underlying SBE message.

    SbeMessage message() const ONIXS_B3_BOE_NOTHROW
    {
        assert(valid());

#ifndef NDEBUG
        SbeMessage(toByteBlock(toMutable(data_)) + sizeof(SimpleOpenFramingHeader), size_ - sizeof(SimpleOpenFramingHeader));
#endif

        return SbeMessage(
            toByteBlock(toMutable(data_)) + sizeof(SimpleOpenFramingHeader),
            size_ - sizeof(SimpleOpenFramingHeader), SbeMessage::NoCheck());
    }

private:
    const void* data_;
    MessageSize size_;
};

/// Serializes into a string.
ONIXS_B3_BOE_EXPORTED
void toStr(std::string&, const NetworkMessage&);

inline
std::string toStr(const NetworkMessage& message)
{
    std::string res;
    toStr(res, message);
    return res;
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
