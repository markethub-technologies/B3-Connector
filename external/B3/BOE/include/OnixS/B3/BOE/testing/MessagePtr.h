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

#include <OnixS/B3/BOE/testing/ABI.h>

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)

#include <OnixS/B3/BOE/Messaging.h>

#include <memory>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Testing {

using namespace Messaging;

ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NORETURN
void throwWrongType(UInt16, UInt16);

/// \return `true` if the instance refers to a valid message, otherwise - `false`.
inline
bool isMessageValid(const SbeMessage& msg) noexcept
{
    return msg.valid();
}

/// Message container.
template<typename Message>
class MessagePtr
{
public:
    using Container = std::shared_ptr<UInt8>;

    /// Creates from the given memory block.
    MessagePtr(Container&&, MessageSize);

    /// Create from another type.
    template <class AnotherType>
    explicit
    MessagePtr(const MessagePtr<AnotherType>& rhs)
        : size_(rhs.size_)
        , container_(rhs.container_)
        , message_()
    {
        fromAnotherType(rhs);
    }

    /// Creates from the given type.
    template <class AnotherType>
    explicit
    MessagePtr(MessagePtr<AnotherType>&& rhs)
        : size_(rhs.size_)
        , container_(std::move(rhs.container_))
        , message_()
    {
        fromAnotherType(rhs);
    }

    /// Creates an empty message container.
    MessagePtr()
        : size_(0)
        , container_()
        , message_()
    {
    }

    MessagePtr(const MessagePtr&) = default;
    MessagePtr& operator=(const MessagePtr&) = default;

    ///
    MessagePtr(MessagePtr&& rhs) noexcept
    {
        rhs.swap(*this);
        rhs.reset();
    }

    ///
    MessagePtr& operator=(MessagePtr&& rhs) noexcept
    {
        if (&rhs == this)
            return *this;

        rhs.swap(*this);
        rhs.reset();

        return *this;
    }

    ///
    bool valid() const noexcept
    {
        return isMessageValid(message_);
    }

    ///
    void swap(MessagePtr& rhs) noexcept
    {
        std::swap(rhs.size_, size_);
        std::swap(rhs.container_, container_);
        std::swap(rhs.message_, message_);
    }

    ///
    Message* operator->() noexcept
    {
        assert(valid());
        return &message_;
    }

    ///
    const Message* operator->() const noexcept
    {
        assert(valid());
        return &message_;
    }

    ///
    Message& operator*() noexcept
    {
        return message_;
    }

    ///
    const Message& operator*() const noexcept
    {
        return message_;
    }

    /// \return the underlying message.
    Message& message() noexcept
    {
        assert(valid());
        return message_;
    }

    /// \return the underlying message.
    const Message& message() const noexcept
    {
        assert(valid());
        return message_;
    }

    ///
    operator Message() noexcept
    {
        return message();
    }

    ///
    operator const Message() const noexcept
    {
        return message();
    }

    /// \return the underlying buffer.
    UInt8* buf() noexcept
    {
        return container_.get();
    }

    /// Resets the message.
    void reset()
    {
        size_ = 0;
        container_.reset();
        message_ = Message();
    }

    /// \return the human-readable presentation.
    std::string toString() const
    {
        return message_.toString();
    }

private:

    template <class AnotherType>
    void fromAnotherType(const MessagePtr<AnotherType>& rhs)
    {
        if(rhs->templateId() != Message::TemplateId)
            throwWrongType(Message::TemplateId, rhs->templateId());

        message_ = Messaging::typify<Message>(rhs);
    }

private:
    MessageSize size_;
    Container container_;
    Message message_;

    template<class T> friend class MessagePtr;
};


template<>
inline MessagePtr<SbeMessage>::MessagePtr(Container&& container, MessageSize size)
    : size_(size)
    , container_(std::move(container))
    , message_(container_.get(), size_)
{
}

/// Tries to cast to another type.
template <typename AnotherType, typename BaseType>
MessagePtr<AnotherType> cast(const MessagePtr<BaseType>& ptr)
{
    return MessagePtr<AnotherType>(ptr);
}

}}}}

#endif
