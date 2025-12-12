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

#include <OnixS/B3/BOE/messaging/MessageHolder.h>
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

typedef std::vector<NetworkMessage> NetMessages;
class MessageBatchChecker;

#if defined (ONIXS_B3_BOE_CXX11)

/**
* The message batch wrapper.
*/
template <typename MessageTypeT,
size_t MaxMessageSize = GetMaxMessageSize<typename HeldAdapter<MessageTypeT>::SbeType, DefaultMaxGroupItems>::Size,
typename MessageInitializer = FieldsInitPolicy>
class MessageBatch
{
public:

    using MsgHolder = MessageHolder<MessageTypeT, MaxMessageSize, MessageInitializer>;
    using MsgHolders = std::vector<MsgHolder>;

    using iterator = typename MsgHolders::iterator;
    using const_iterator = typename MsgHolders::const_iterator;

    /**
    * Creates an empty message batch.
    * The `add` method should be used to add a message to the batch.
    */
    MessageBatch() = default;

    /**
    * Creates a message batch with the given number of default constructed messages.
    * A message in the batch can be updated via `operator[]` method.
    */
    explicit MessageBatch(size_t size) : batch_(size)
    {
        updateHeaders();
    }

    /**
    * Creates a message batch from the initializer list.
    * A message in the batch can be updated via `operator[]` method.
    */
    MessageBatch(std::initializer_list<MsgHolder> list) : batch_(list)
    {
        updateHeaders();
    }

    MessageBatch(const MessageBatch &) = delete;
    MessageBatch & operator=(const MessageBatch &) = delete;

    /**
    * Appends a message to the end of the batch.
    */
    void add(const MsgHolder & msg)
    {
        batch_.push_back(msg);
    }

    /**
    * Updates headers of SBE messages to be ready for sending.
    *
    * \note Should be called before sending after the completion of the batch filling.
    *
    * \note There is no need to call this function before sending in each case of a value updating of an existing field.
    */
    void updateHeaders()
    {
        netMsgs_.resize(batch_.size());

        for (size_t counter = 0; counter < batch_.size(); ++counter)
            netMsgs_[counter] = batch_[counter].toNetworkMessage();
    }

    MsgHolder & operator[](size_t index) { return batch_[index]; }
    const MsgHolder & operator[](size_t index) const { return batch_[index]; }

    size_t size() const { return batch_.size(); }

    const_iterator begin() const { return batch_.begin(); }
    iterator begin() { return batch_.begin(); }

    const_iterator end() const { return batch_.end(); }
    iterator end() { return batch_.end(); }

private:

    friend class OnixS::B3::BOE::Session;
    friend class OnixS::B3::BOE::Messaging::MessageBatchChecker;

    MsgHolders batch_;
    NetMessages netMsgs_;
};

/**
* The class can be used to combine messages with different types to the batch for sending.
*
* \warning The class does not copy combined messages and does not store them internally.
* Therefore, the lifetime of combined messages should be greater or equal to the lifetime of this class instance.
*/
class MessageBatchCombiner
{
public:

    /**
    * Creates an empty message batch combiner.
    * The `add` method should be used to fill the batch.
    */
    MessageBatchCombiner() = default;

    /**
    * Adds the message batch to the array of combined messages.
    * Updates headers of SBE messages to be ready for sending.
    */
    template <typename MessageTypeT,
    size_t MaxMessageSize = GetMaxMessageSize<typename HeldAdapter<MessageTypeT>::SbeType, DefaultMaxGroupItems>::Size,
    typename MessageInitializer = FieldsInitPolicy>
    void add(MessageBatch<MessageTypeT, MaxMessageSize, MessageInitializer> & batch)
    {
        for (auto & holder : batch)
            netMsgs_.push_back(holder.toNetworkMessage());
    }

    template <typename MessageTypeT,
    size_t MaxMessageSize = GetMaxMessageSize<typename HeldAdapter<MessageTypeT>::SbeType, DefaultMaxGroupItems>::Size,
    typename MessageInitializer = FieldsInitPolicy>
    void add(MessageBatch<MessageTypeT, MaxMessageSize, MessageInitializer> && batch) = delete;

    /**
    * Adds the message to the array of combined messages.
    * Updates headers of the SBE message to be ready for sending.
    */
    template <typename MessageTypeT,
    size_t MaxMessageSize = GetMaxMessageSize<typename HeldAdapter<MessageTypeT>::SbeType, DefaultMaxGroupItems>::Size,
    typename MessageInitializer = FieldsInitPolicy>
    void add(MessageHolder<MessageTypeT, MaxMessageSize, MessageInitializer> & holder)
    {
        netMsgs_.push_back(holder.toNetworkMessage());
    }

    template <typename MessageTypeT,
    size_t MaxMessageSize = GetMaxMessageSize<typename HeldAdapter<MessageTypeT>::SbeType, DefaultMaxGroupItems>::Size,
    typename MessageInitializer = FieldsInitPolicy>
    void add(MessageHolder<MessageTypeT, MaxMessageSize, MessageInitializer> && holder) = delete;

    /**
    * Removes all combined messages.
    */
    void clear()
    {
        netMsgs_.clear();
    }

    MessageBatchCombiner(const MessageBatchCombiner &) = delete;
    MessageBatchCombiner & operator=(const MessageBatchCombiner &) = delete;

private:

    friend class OnixS::B3::BOE::Session;
    friend class OnixS::B3::BOE::Messaging::MessageBatchChecker;

    NetMessages netMsgs_;
};

class MessageBatchChecker
{
public:
    /// \return The size of the message batch in bytes
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    static size_t calculateBatchSize(
        MessageBatch<SbeMessageType, MaxMessageSize, MessageInitializer> & msgs) ONIXS_B3_BOE_NOTHROW
    {
        return calculateBatchSize(msgs.netMsgs_);
    }

    /// \return true if the batch fits the size provided
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    static size_t fitSize(
        MessageBatch<SbeMessageType, MaxMessageSize, MessageInitializer> & msgs, size_t size = defaultMaxPacketSize()) ONIXS_B3_BOE_NOTHROW
    {
        return calculateBatchSize(msgs) <= size;
    }

    /// \return The size of the message batch in bytes
    static size_t calculateBatchSize(MessageBatchCombiner & msgs) ONIXS_B3_BOE_NOTHROW
    {
        return calculateBatchSize(msgs.netMsgs_);
    }

    /// \return true if the batch fits the size provided
    static bool fitSize(MessageBatchCombiner & msgs, size_t size = defaultMaxPacketSize()) ONIXS_B3_BOE_NOTHROW
    {
        return calculateBatchSize(msgs) <= size;
    }

private:
    ONIXS_B3_BOE_EXPORTED
    static size_t calculateBatchSize(const NetMessages& msgs) ONIXS_B3_BOE_NOTHROW;

    ONIXS_B3_BOE_EXPORTED
    static size_t defaultMaxPacketSize() ONIXS_B3_BOE_NOTHROW;
};

#endif

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
