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

#include <cassert>
#include <stdexcept>

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Composites.h>
#include <OnixS/B3/MarketData/UMDF/messaging/SbeMessage.h>
#include <OnixS/B3/MarketData/UMDF/messaging/Forwards.h>

#ifdef DELETE
#undef DELETE
#endif

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

/// Used to reset the incremental stream or indicate the loop on instrument definition or snapshot recovery is restarting.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
SequenceReset_1
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 1 };

    /// Initializes a blank instance.
    SequenceReset_1() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    SequenceReset_1(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SequenceReset_1(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SequenceReset_1(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::SequenceReset;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// New sequence number. Always one.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SeqNum1 newSeqNo()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SeqNum1();
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "SequenceReset_1";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("4");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Sent in incremental, snapshot and instrument list feeds in periods of no activity.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
Sequence_2
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 2 };

    /// Initializes a blank instance.
    Sequence_2() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    Sequence_2(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Sequence_2(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Sequence_2(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::Sequence;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// The next application sequence number in the feed. Always 1
    /// (one) for snapshot replay and instrument replay feeds.
    ONIXS_B3_UMDF_MD_NODISCARD
    SeqNum nextSeqNo() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SeqNum>(offset);
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            4;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "Sequence_2";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("0");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Market Data Incremental Refresh - Empty Book.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
EmptyBook_9
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 9 };

    /// Initializes a blank instance.
    EmptyBook_9() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    EmptyBook_9(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    EmptyBook_9(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    EmptyBook_9(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Type of the Market Data Entry.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::EMPTY_BOOK;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 5-RecoveryMsg and
    /// 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            20;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "EmptyBook_9";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("EmptyBook_9");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Channel Reset (remove all instruments, empty all books and statistics).
ONIXS_B3_UMDF_MD_LTWT_STRUCT
ChannelReset_11
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 11 };

    /// Initializes a blank instance.
    ChannelReset_11() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    ChannelReset_11(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ChannelReset_11(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ChannelReset_11(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Type of the Market Data Entry.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::EMPTY_BOOK;
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 5-RecoveryMsg and
    /// 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            12;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "ChannelReset_11";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("ChannelReset_11");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Trading status for instruments.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
SecurityStatus_3
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 3 };

    /// Initializes a blank instance.
    SecurityStatus_3() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    SecurityStatus_3(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SecurityStatus_3(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SecurityStatus_3(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::SecurityStatus;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Identifier for trading session.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionID::Enum tradingSessionId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<TradingSessionID>(offset);
    }

    /// Status related to a given instrument.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityTradingStatus::Enum
    securityTradingStatus() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<SecurityTradingStatus>(offset);
    }

    /// Identifies an event related to a Trading. This tag is also
    /// used to mark when an instrument state is kept separate
    /// from the group phase, or when the instrument state follows
    /// the default group phase (stops having a separate, defined
    /// state). Always sent when tag 48 is present.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    securityTradingEvent(
        SecurityTradingEvent::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 11;

        return enumeration<SecurityTradingEvent>(value, offset, NullUInt8());
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Estimated end of the current auction. Only present when
    /// SecurityTradingStatus=21 (Pre-open/Reserved).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool tradSesOpenTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Timestamp when status of the security changed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. (Zeroed in snapshot
    /// feed).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "SecurityStatus_3";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("SecurityStatus_3");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Trading status for security groups.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
SecurityGroupPhase_10
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 10 };

    /// Initializes a blank instance.
    SecurityGroupPhase_10() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    SecurityGroupPhase_10(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SecurityGroupPhase_10(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SecurityGroupPhase_10(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::SecurityStatus;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security Group.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef securityGroup() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 3;

        return fixedStr<length>(offset);
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Identifier for trading session.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionID::Enum tradingSessionId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<TradingSessionID>(offset);
    }

    /// Phase related to a given SecurityGroup.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionSubID::Enum
    tradingSessionSubId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<TradingSessionSubID>(offset);
    }

    /// Indicates if the trading session changed in order to reset
    /// some statistics for this group.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    securityTradingEvent(
        SecurityTradingEvent::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 11;

        return enumeration<SecurityTradingEvent>(value, offset, NullUInt8());
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Estimated end of the current auction. Only present when
    /// TradingSessionSubID=21 (Pre-open/Reserved).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool tradSesOpenTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Timestamp when phase of the security group changed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            32;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "SecurityGroupPhase_10";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("SecurityGroupPhase_10");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Security Definition.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
SecurityDefinition_12
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 12 };

    /// Underlying instruments.
    /// Entry of UnderlyingsEntry repeating group.
    ONIXS_B3_UMDF_MD_LTWT_STRUCT
    UnderlyingsEntry : SbeGroupEntry
    <
        GroupSizeEncoding::BlockLength
    >
    {
        /// Base class type.
        typedef
        SbeGroupEntry
        <
            GroupSizeEncoding::BlockLength
        >
        Base;

        /// Initializes instance of given
        /// version over given memory block.
        UnderlyingsEntry(
            const void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Underlying instrument's security ID.
        ONIXS_B3_UMDF_MD_NODISCARD
        SecurityID underlyingSecurityId() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return ordinary<SecurityID>(offset);
        }

        /// Identifies the class of the underlying instrument's
        /// SecurityID (Exchange Symbol).
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static SecurityIDSource::Enum underlyingSecurityIdSource()
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return SecurityIDSource::EXCHANGE_SYMBOL;
        }

        /// Underlying instrument's Exchange Code.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_NODISCARD
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static StrRef underlyingSecurityExchange()
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return constructStrRef("BVMF");
        }

        /// Underlying instrument's ticker symbol.
        ONIXS_B3_UMDF_MD_NODISCARD
        StrRef underlyingSymbol() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 20;

            return fixedStr<length>(offset);
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static BlockLength blockLength(SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                minimalBlockLength(version);
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static
        BlockLength
        minimalBlockLength(
            ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                28;
        }

        /// Entity class name.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_NODISCARD
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static const Char* className()
        {
            return "SecurityDefinition_12.UnderlyingsEntry";
        }
    };

    /// Repeating group containing UnderlyingsEntry entries.
    typedef
    SbeGroup<UnderlyingsEntry, GroupSizeEncoding, MessageSize>
    Underlyings;

    /// Instrument legs.
    /// Entry of LegsEntry repeating group.
    ONIXS_B3_UMDF_MD_LTWT_STRUCT
    LegsEntry : SbeGroupEntry
    <
        GroupSizeEncoding::BlockLength
    >
    {
        /// Base class type.
        typedef
        SbeGroupEntry
        <
            GroupSizeEncoding::BlockLength
        >
        Base;

        /// Initializes instance of given
        /// version over given memory block.
        LegsEntry(
            const void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Leg's security ID.
        ONIXS_B3_UMDF_MD_NODISCARD
        SecurityID legSecurityId() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return ordinary<SecurityID>(offset);
        }

        /// Identifies the class of the leg instrument's SecurityID
        /// (Exchange Symbol).
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static SecurityIDSource::Enum legSecurityIdSource()
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return SecurityIDSource::EXCHANGE_SYMBOL;
        }

        /// Leg's Exchange Code.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_NODISCARD
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static StrRef legSecurityExchange()
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return constructStrRef("BVMF");
        }

        /// Ratio of quantity for this leg relative to the entire
        /// security.
        ONIXS_B3_UMDF_MD_NODISCARD
        bool legRatioQty(RatioQty& value) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

            return decimal(value, offset, NullRatioQty());
        }

        /// Leg's security type.
        ONIXS_B3_UMDF_MD_NODISCARD
        SecurityType::Enum legSecurityType() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;

            return enumeration<SecurityType>(offset);
        }

        /// Side of this leg.
        ONIXS_B3_UMDF_MD_NODISCARD
        Side::Enum legSide() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 17;

            return enumeration<Side>(offset);
        }

        /// Leg symbol.
        ONIXS_B3_UMDF_MD_NODISCARD
        StrRef legSymbol() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 18;
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 20;

            return fixedStr<length>(offset);
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static BlockLength blockLength(SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                minimalBlockLength(version);
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static
        BlockLength
        minimalBlockLength(
            ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                38;
        }

        /// Entity class name.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_NODISCARD
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static const Char* className()
        {
            return "SecurityDefinition_12.LegsEntry";
        }
    };

    /// Repeating group containing LegsEntry entries.
    typedef
    SbeGroup<LegsEntry, GroupSizeEncoding, MessageSize>
    Legs;

    /// Specifies the number of the application ID occurrences
    /// (number of channels).
    /// Entry of InstrAttribsEntry repeating group.
    ONIXS_B3_UMDF_MD_LTWT_STRUCT
    InstrAttribsEntry : SbeGroupEntry
    <
        GroupSizeEncoding::BlockLength
    >
    {
        /// Base class type.
        typedef
        SbeGroupEntry
        <
            GroupSizeEncoding::BlockLength
        >
        Base;

        /// Initializes instance of given
        /// version over given memory block.
        InstrAttribsEntry(
            const void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Code to represent the type of instrument attributes.
        ONIXS_B3_UMDF_MD_NODISCARD
        InstrAttribType::Enum instrAttribType() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return enumeration<InstrAttribType>(offset);
        }

        /// Attribute value appropriate to the InstrAttribType (871)
        /// field.
        ONIXS_B3_UMDF_MD_NODISCARD
        InstrAttribValue::Enum instrAttribValue() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 1;

            return enumeration<InstrAttribValue>(offset);
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static BlockLength blockLength(SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                minimalBlockLength(version);
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static
        BlockLength
        minimalBlockLength(
            ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                2;
        }

        /// Entity class name.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_NODISCARD
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static const Char* className()
        {
            return "SecurityDefinition_12.InstrAttribsEntry";
        }
    };

    /// Repeating group containing InstrAttribsEntry entries.
    typedef
    SbeGroup<InstrAttribsEntry, GroupSizeEncoding, MessageSize>
    InstrAttribs;

    /// Initializes a blank instance.
    SecurityDefinition_12() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    SecurityDefinition_12(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SecurityDefinition_12(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SecurityDefinition_12(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::SecurityDefinition;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Exchange Code.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef securityExchange() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 4;

        return fixedStr<length>(offset);
    }

    /// Identifies the class of the SecurityID.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityIDSource::Enum securityIdSource() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return enumeration<SecurityIDSource>(offset);
    }

    /// Security Group.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef securityGroup() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 13;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 3;

        return fixedStr<length>(offset);
    }

    /// Instrument's ticker symbol.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef symbol() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 20;

        return fixedStr<length>(offset);
    }

    /// Action used when updating the security.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityUpdateAction::Enum
    securityUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return enumeration<SecurityUpdateAction>(offset);
    }

    /// Instrument's security type.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityType::Enum securityType() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 37;

        return enumeration<SecurityType>(offset);
    }

    /// Instrument's security sub type. List of values defined at
    /// Message Reference document.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt16 securitySubType() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 38;

        return ordinary<UInt16>(offset);
    }

    /// Total number of instruments to be returned in the current
    /// replay loop.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt32 totNoRelatedSym() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return ordinary<UInt32>(offset);
    }

    /// Number of minimum price increments.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool minPriceIncrement(Fixed8& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return decimal(value, offset, NullFixed8());
    }

    /// Strike price of an option.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool strikePrice(PriceOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Specifies the ratio or multiply factor to convert from
    /// “nominal” units (e.g. contracts) to total units (e.g.
    /// shares) (e.g. 1.0, 100, 1000, 0.00025 etc).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool contractMultiplier(Fixed8& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return decimal(value, offset, NullFixed8());
    }

    /// Value that divides the Price field to produce the actual
    /// order price (based on Step of Quotation). (e.g. 1, 100,
    /// 1000, etc). Default value is 1. Also used for index
    /// instruments to disseminate the index reducer, in this
    /// case, there is no default value.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool priceDivisor(Fixed8& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return decimal(value, offset, NullFixed8());
    }

    /// Indicates the UTC timestamp when trading for this security
    /// expires, i.e. when it is not eligible to trade anymore.
    /// Different from MaturityDate.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    securityValidityTimestamp(
        UTCTimestampSeconds& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 76;

        return ordinary(value, offset, NullUTCTimestampSeconds());
    }

    /// Share capital.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool sharesIssued(UInt64NULL& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 84;

        return ordinary(value, offset, NullUInt64NULL());
    }

    /// Clearing House ID.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool clearingHouseId(ClearingHouseID& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 92;

        return ordinary(value, offset, NullClearingHouseID());
    }

    /// Minimum quantity for an order.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool minOrderQty(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 100;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum quantity for an order.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool maxOrderQty(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 108;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Minimum lot size allowed based on lot type specified in
    /// LotType(1093). Used for the equities segment.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool minLotSize(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 116;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// The minimum trading volume for the security.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool minTradeVol(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 124;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Corporate Action Event ID.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool corporateActionEventId(UInt32NULL& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 132;

        return ordinary(value, offset, NullUInt32NULL());
    }

    /// The date on which the security is issued/activated.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp issueDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 136;

        return localMktDateToTimestamp(ordinary<LocalMktDate32>(offset));
    }

    /// Date of instrument maturity.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool maturityDate(Timestamp& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        typedef LocalMktDate32Optional FieldValue;

        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 140;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDate32Optional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// ISO 3166-1 alpha-2 country code.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool countryOfIssue(StrRef& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 144;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 2;

        return fixedStr<length>(value, offset);
    }

    /// Start date of a financing deal, i.e. the date the buyer
    /// pays the seller cash and takes control of the collateral.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool startDate(Timestamp& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        typedef LocalMktDate32Optional FieldValue;

        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 146;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDate32Optional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// End date of a financing deal, i.e. the date the seller
    /// reimburses the buyer and takes back control of the
    /// collateral.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool endDate(Timestamp& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        typedef LocalMktDate32Optional FieldValue;

        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 150;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDate32Optional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Order settlement period in days.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool settlType(SettlType& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 154;

        return ordinary(value, offset, NullSettlType());
    }

    /// Specific date of trade settlement.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool settlDate(Timestamp& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        typedef LocalMktDate32Optional FieldValue;

        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 156;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDate32Optional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// The date of the security activation, if different from the
    /// IssueDate.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool datedDate(Timestamp& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        typedef LocalMktDate32Optional FieldValue;

        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 160;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDate32Optional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// ISIN Number.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool isinNumber(StrRef& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 164;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 12;

        return fixedStr<length>(value, offset);
    }

    /// Asset associated to the security.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef asset() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 176;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 6;

        return fixedStr<length>(offset);
    }

    /// Classification of Financial Instruments (CFI code) values,
    /// which indicate the type of security using the ISO 10962
    /// standard.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef cfiCode() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 182;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 6;

        return fixedStr<length>(offset);
    }

    /// Week, month and year of the maturity (used for
    /// standardized futures and options).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool maturityMonthYear(MaturityMonthYear& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 188;

        return ordinary(value, offset, NullMaturityMonthYear());
    }

    /// Specifies when the contract will settle.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool contractSettlMonth(MaturityMonthYear& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 193;

        return ordinary(value, offset, NullMaturityMonthYear());
    }

    /// Currency code.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef currency() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 198;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 3;

        return fixedStr<length>(offset);
    }

    /// Currency of option's strike price.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool strikeCurrency(StrRef& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 201;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 3;

        return fixedStr<length>(value, offset);
    }

    /// Currency used for the settlement.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool settlCurrency(StrRef& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 204;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 3;

        return fixedStr<length>(value, offset);
    }

    /// Strategy type definition.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool securityStrategyType(StrRef& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 207;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 3;

        return fixedStr<length>(value, offset);
    }

    /// Lot type.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool lotType(LotType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 210;

        return enumeration<LotType>(value, offset, NullUInt8());
    }

    /// Number of decimals for pricing the instrument.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool tickSizeDenominator(UInt8& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 211;

        return ordinary(value, offset, NullUInt8());
    }

    /// Type of product.
    ONIXS_B3_UMDF_MD_NODISCARD
    Product::Enum product() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 212;

        return enumeration<Product>(offset);
    }

    /// Exercise Style.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    exerciseStyle(
        ExerciseStyle::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 213;

        return enumeration<ExerciseStyle>(value, offset, NullUInt8());
    }

    /// Indicates whether an option contract is a put or call.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool putOrCall(PutOrCall::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 214;

        return enumeration<PutOrCall>(value, offset, NullUInt8());
    }

    /// Price type of the instrument.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool priceType(PriceType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 215;

        return enumeration<PriceType>(value, offset, NullUInt8NULL());
    }

    /// Market segment.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool marketSegmentId(MarketSegmentID& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 216;

        return ordinary(value, offset, NullMarketSegmentID());
    }

    /// Corporative Governance Level Indicator.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    governanceIndicator(
        GovernanceIndicator::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 217;

        return enumeration<GovernanceIndicator>(value, offset, NullUInt8());
    }

    /// Type of matching that occurred.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    securityMatchType(
        SecurityMatchType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 218;

        return enumeration<SecurityMatchType>(value, offset, NullUInt8());
    }

    /// Indicates whether this message is the last in the sequence
    /// of messages.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool lastFragment(Boolean::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 219;

        return enumeration<Boolean>(value, offset, NullUInt8());
    }

    /// Defines whether the security is pre-defined or user-
    /// defined. Used for multileg security only.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    multiLegModel(
        MultiLegModel::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 220;

        return enumeration<MultiLegModel>(value, offset, NullUInt8());
    }

    /// Defines the method used when applying the multileg price
    /// to the legs. When this tag is set, it indicates spreads
    /// that have leg prices generated by the trading engine.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    multiLegPriceMethod(
        MultiLegPriceMethod::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 221;

        return enumeration<MultiLegPriceMethod>(value, offset, NullUInt8());
    }

    /// Minimum quantity of a cross order for the security.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool minCrossQty(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 222;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Indicates that an implied order can be created for the
    /// instrument.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    impliedMarketIndicator(
        ImpliedMarketIndicator::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 230;

        return enumeration<ImpliedMarketIndicator>(value, offset, NullUInt8());
    }

    /// Indicates the type of payout that will result from an in-
    /// the-money option.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    optPayoutType(
        OptPayoutType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 231;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR SchemaVersion since = 16;

        return enumeration<OptPayoutType>(value, offset, NullUInt8NULL(), since);
    }

    /// \return instance of Underlyings repeating group.
    ONIXS_B3_UMDF_MD_NODISCARD
    Underlyings underlyings() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getGroup<Underlyings>(
            UnderlyingsAccess(),
            *this);
    }

    /// \return instance of Legs repeating group.
    ONIXS_B3_UMDF_MD_NODISCARD
    Legs legs() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getGroup<Legs>(LegsAccess(), *this);
    }

    /// \return instance of InstrAttribs repeating group.
    ONIXS_B3_UMDF_MD_NODISCARD
    InstrAttribs instrAttribs() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getGroup<InstrAttribs>(
            InstrAttribsAccess(),
            *this);
    }

    /// Non-normative textual description for the financial instrument.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef securityDesc() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getVariableLengthField(
            securityDescAccess(),
            *this);
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            (version >= 16)
                ? 232
                : 231;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(TextEncoding::Size) + static_cast<MessageSize>(Underlyings::EmptySize) + static_cast<MessageSize>(Legs::EmptySize) + static_cast<MessageSize>(InstrAttribs::EmptySize);
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "SecurityDefinition_12";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("SecurityDefinition_12");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    /// Checks variable fields consistency.
    void checkVarLenFields() const
    {
        groups().
            tail<Underlyings>().
            tail<Legs>().
            checkVariableLengthFields<InstrAttribs>().
            checkTail<TextEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct UnderlyingsAccess
    {
        Underlyings
        operator()(
            const SecurityDefinition_12& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                groups().
                    head<Underlyings>();
        }
    };

    /// Access helper.
    struct LegsAccess
    {
        Legs
        operator()(
            const SecurityDefinition_12& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                groups().
                    tail<Underlyings>().
                    head<Legs>();
        }
    };

    /// Access helper.
    struct InstrAttribsAccess
    {
        InstrAttribs
        operator()(
            const SecurityDefinition_12& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                groups().
                    tail<Underlyings>().
                    tail<Legs>().
                    head<InstrAttribs>();
        }
    };

    /// Access helper.
    struct securityDescAccess
    {
        TextEncoding&
        operator()(
            const SecurityDefinition_12& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                groups().
                    tail<Underlyings>().
                    tail<Legs>().
                    variableLengthFields<InstrAttribs>().
                    head<TextEncoding>();
        }
    };
};

/// Conveys market information of B3 market surveillance notifications and news produced by agencies.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
News_5
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 5 };

    /// Initializes a blank instance.
    News_5() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    News_5(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    News_5(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    News_5(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::News;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    securityId(
        SecurityIDOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary(value, offset, NullSecurityIDOptional());
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Source of the News.
    ONIXS_B3_UMDF_MD_NODISCARD
    NewsSource::Enum newsSource() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<NewsSource>(offset);
    }

    /// Indicates the language the news is in. If null, it's 'pt'
    /// = Portuguese.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool languageCode(StrRef& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength length = 2;

        return fixedStr<length>(value, offset);
    }

    /// Total number of parts for the text of a News message.
    /// Usually 1.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt16 partCount() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UInt16>(offset);
    }

    /// Number of the part for this message. Starts from 1.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt16 partNumber() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 14;

        return ordinary<UInt16>(offset);
    }

    /// Unique identifier for News message. Included in the News
    /// messages sent in the Unified News Channel. Not sent for
    /// trading engine News messages.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool newsId(NewsID& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary(value, offset, NullNewsID());
    }

    /// Time of message origination.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool origTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Total size, in bytes, for the text of a News message.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt32 totalTextLength() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary<UInt32>(offset);
    }

    /// The headline of a News message.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef headline() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getVariableLengthField(headlineAccess(), *this);
    }

    /// Free format text string.
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef text() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getVariableLengthField(textAccess(), *this);
    }

    /// A URL (Uniform Resource Locator) link to additional information (e.g. http://www.b3.com.br).
    ONIXS_B3_UMDF_MD_NODISCARD
    StrRef uRLLink() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getVariableLengthField(uRLLinkAccess(), *this);
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(VarString::Size) + static_cast<MessageSize>(VarString::Size) + static_cast<MessageSize>(VarString::Size);
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "News_5";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("B");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    /// Checks variable fields consistency.
    void checkVarLenFields() const
    {
        variableLengthFields().
            checkTail<VarString>().
            checkTail<VarString>().
            checkTail<VarString>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct headlineAccess
    {
        VarString& operator()(const News_5& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<VarString>();
        }
    };

    /// Access helper.
    struct textAccess
    {
        VarString& operator()(const News_5& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<VarString>().
                    head<VarString>();
        }
    };

    /// Access helper.
    struct uRLLinkAccess
    {
        VarString& operator()(const News_5& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<VarString>().
                    tail<VarString>().
                    head<VarString>();
        }
    };
};

/// Carries the summary information about opening trading session events per market data stream.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
OpeningPrice_15
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 15 };

    /// Initializes a blank instance.
    OpeningPrice_15() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    OpeningPrice_15(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    OpeningPrice_15(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    OpeningPrice_15(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW or DELETE).
    ONIXS_B3_UMDF_MD_NODISCARD
    UpdateAction::Enum mDUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<UpdateAction>(offset);
    }

    /// Entry type: Opening Price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::OPENING_PRICE;
    }

    /// Identifies if the opening price represents or not a daily
    /// opening price.
    ONIXS_B3_UMDF_MD_NODISCARD
    OpenCloseSettlFlag::Enum openCloseSettlFlag() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<OpenCloseSettlFlag>(offset);
    }

    /// Value of the statistics.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Net change from previous trading day’s closing price vs.
    /// last traded price.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    netChgPrevDay(
        PriceOffset8Optional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return decimal(value, offset, NullPriceOffset8Optional());
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 30;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 38;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            44;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            44;
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "OpeningPrice_15";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("OpeningPrice_15");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// The theoretical opening price is also sent on this block and is calculated and updated based on the orders presented in the book during every auction including the pre-opening / pre-closing auction.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
TheoreticalOpeningPrice_16
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 16 };

    /// Initializes a blank instance.
    TheoreticalOpeningPrice_16() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    TheoreticalOpeningPrice_16(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    TheoreticalOpeningPrice_16(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    TheoreticalOpeningPrice_16(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW or DELETE).
    ONIXS_B3_UMDF_MD_NODISCARD
    UpdateAction::Enum mDUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<UpdateAction>(offset);
    }

    /// Entry type: Opening Price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::OPENING_PRICE;
    }

    /// Indicates this is a theoretical opening price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static OpenCloseSettlFlag::Enum openCloseSettlFlag()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return OpenCloseSettlFlag::THEORETICAL_PRICE;
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Theoretical Opening Price.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryPx(PriceOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Theoretical Opening Quantity.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntrySize(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            40;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "TheoreticalOpeningPrice_16";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef(
            "TheoreticalOpeningPrice_16");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Summary information about closing trading sessions per market data stream.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
ClosingPrice_17
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 17 };

    /// Initializes a blank instance.
    ClosingPrice_17() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    ClosingPrice_17(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ClosingPrice_17(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ClosingPrice_17(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Closing Price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::CLOSING_PRICE;
    }

    /// Identifies if the closing price represents a daily or
    /// entry from previous business day.
    ONIXS_B3_UMDF_MD_NODISCARD
    OpenCloseSettlFlag::Enum openCloseSettlFlag() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<OpenCloseSettlFlag>(offset);
    }

    /// Closing price. May be adjusted by corporate events.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price8 mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price8>(offset);
    }

    /// Date the instrument last traded.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool lastTradeDate(Timestamp& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 22;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "ClosingPrice_17";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("ClosingPrice_17");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Carries auction imbalance information, indicating the remaining quantity and to which side (buyer or seller) the auction is pending towards.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
AuctionImbalance_19
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 19 };

    /// Initializes a blank instance.
    AuctionImbalance_19() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    AuctionImbalance_19(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    AuctionImbalance_19(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    AuctionImbalance_19(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW or DELETE).
    ONIXS_B3_UMDF_MD_NODISCARD
    UpdateAction::Enum mDUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<UpdateAction>(offset);
    }

    /// Entry type: Imbalance.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::IMBALANCE;
    }

    /// IMBALANCE_MORE_BUYERS, IMBALANCE_MORE_SELLERS, All bits
    /// off => BALANCED.
    ONIXS_B3_UMDF_MD_NODISCARD
    ImbalanceCondition imbalanceCondition() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return ordinary<ImbalanceCondition>(offset);
    }

    /// Remaining auction quantity.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntrySize(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            32;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "AuctionImbalance_19";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("AuctionImbalance_19");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Quantity Band.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
QuantityBand_21
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 21 };

    /// Initializes a blank instance.
    QuantityBand_21() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    QuantityBand_21(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    QuantityBand_21(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    QuantityBand_21(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Quantity Band.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::QUANTITY_BAND;
    }

    /// Daily average shares traded within 30 days – equity market
    /// only. Previously known as DailyAvgShares30D. Always 0 for
    /// Derivatives.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    avgDailyTradedQty(
        QuantityVolumeOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary(value, offset, NullQuantityVolumeOptional());
    }

    /// The maximum order quantity that can be submitted for a
    /// security. The value is the minimum between % of shares
    /// issued and % of average traded quantity within 30 days.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    maxTradeVol(
        QuantityVolumeOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullQuantityVolumeOptional());
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            40;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "QuantityBand_21";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("QuantityBand_21");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Price Banding (tunnel).
ONIXS_B3_UMDF_MD_LTWT_STRUCT
PriceBand_22
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 22 };

    /// Initializes a blank instance.
    PriceBand_22() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    PriceBand_22(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    PriceBand_22(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    PriceBand_22(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Price Band.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::PRICE_BAND;
    }

    /// Indicates the type of price banding (tunnel).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    priceBandType(
        PriceBandType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<PriceBandType>(value, offset, NullUInt8());
    }

    /// Describes how the price limits are expressed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    priceLimitType(
        PriceLimitType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<PriceLimitType>(value, offset, NullUInt8());
    }

    /// Band Midpoint Type, used with Auction Price Banding. Only
    /// sent for Rejection and Auction Bands when PriceLimitType
    /// (1306) equals to 2 (Percentage).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    priceBandMidpointPriceType(
        PriceBandMidpointPriceType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 11;

        return enumeration<PriceBandMidpointPriceType>(value, offset, NullUInt8());
    }

    /// Allowable low limit price for the trading day. A key
    /// parameter in validating order price. Used as the lower
    /// band for validating order prices. Orders submitted with
    /// prices below the lower limit will be rejected.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool lowLimitPrice(PriceOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Allowable high limit price for the trading day. A key
    /// parameter in validating order price. Used as the upper
    /// band for validating order prices. Orders submitted with
    /// prices above the upper limit will be rejected.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool highLimitPrice(PriceOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Reference price for the current trading price range. The
    /// value may be the reference price, settlement price or
    /// closing price of the prior trading day. Sent only for
    /// Economic Indicators.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool tradingReferencePrice(Fixed8& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return decimal(value, offset, NullFixed8());
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            48;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "PriceBand_22";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("PriceBand_22");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// The highest price traded for the security in the trading session.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
HighPrice_24
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 24 };

    /// Initializes a blank instance.
    HighPrice_24() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    HighPrice_24(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    HighPrice_24(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    HighPrice_24(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW or DELETE).
    ONIXS_B3_UMDF_MD_NODISCARD
    UpdateAction::Enum mDUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<UpdateAction>(offset);
    }

    /// Entry type: Trading Session High Price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::SESSION_HIGH_PRICE;
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Trading Session High Price.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            32;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "HighPrice_24";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("HighPrice_24");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// The lowest price traded for the security in the trading session.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
LowPrice_25
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 25 };

    /// Initializes a blank instance.
    LowPrice_25() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    LowPrice_25(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    LowPrice_25(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    LowPrice_25(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW or DELETE).
    ONIXS_B3_UMDF_MD_NODISCARD
    UpdateAction::Enum mDUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<UpdateAction>(offset);
    }

    /// Entry type: Trading Session Low Price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::SESSION_LOW_PRICE;
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Trading Session Low Price.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            32;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "LowPrice_25";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("LowPrice_25");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// The latest price traded for the security in the trading session.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
LastTradePrice_27
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 27 };

    /// Initializes a blank instance.
    LastTradePrice_27() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    LastTradePrice_27(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    LastTradePrice_27(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    LastTradePrice_27(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 4-Implied and 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Last Trade Price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::TRADE;
    }

    /// Identifier for trading session.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionID::Enum tradingSessionId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<TradingSessionID>(offset);
    }

    /// Set of conditions describing a trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradeCondition tradeCondition() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return ordinary<TradeCondition>(offset);
    }

    /// Last Trade Price.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Quantity or volume represented by the Market Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity mDEntrySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Quantity>(offset);
    }

    /// Contains the unique identifier for this trade per
    /// instrument + trading date, as assigned by the exchange.
    /// Required if reporting a Trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradeID tradeId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<TradeID>(offset);
    }

    /// For reporting trades (buying party).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryBuyer(FirmOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// For reporting trades (selling party).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntrySeller(FirmOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 42;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 50;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Specifies the number of days that may elapse before
    /// delivery of the security. Only used for trades in forward
    /// market.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool sellerDays(UInt16NULL& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 54;

        return ordinary(value, offset, NullUInt16NULL());
    }

    /// Interest Rate of the Termo Trade. Expressed in decimal
    /// form. For example, 1% points is expressed and sent as
    /// 0.01. One basis point is represented as 0.0001.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryInterestRate(Percentage& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return decimal(value, offset, NullPercentage());
    }

    /// Sub type of trade assigned to a trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool trdSubType(TrdSubType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return enumeration<TrdSubType>(value, offset, NullUInt8NULL());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            68;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            68;
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "LastTradePrice_27";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("LastTradePrice_27");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Settlement price or the previous day’s adjusted closing price.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
SettlementPrice_28
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 28 };

    /// Initializes a blank instance.
    SettlementPrice_28() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    SettlementPrice_28(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SettlementPrice_28(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SettlementPrice_28(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Settlement Price.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::SETTLEMENT_PRICE;
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Settlement Price.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Identifies if the settlement price represents a daily,
    /// preliminary or an entry from previous business day.
    ONIXS_B3_UMDF_MD_NODISCARD
    OpenCloseSettlFlag::Enum openCloseSettlFlag() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return enumeration<OpenCloseSettlFlag>(offset);
    }

    /// Code to represent the price type.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool priceType(PriceType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 29;

        return enumeration<PriceType>(value, offset, NullUInt8NULL());
    }

    /// Type of settlement price: FINAL, THEORETICAL or UPDATED.
    ONIXS_B3_UMDF_MD_NODISCARD
    SettlPriceType::Enum settlPriceType() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 30;

        return enumeration<SettlPriceType>(offset);
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 31;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "SettlementPrice_28";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("SettlementPrice_28");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Total number of contracts in a commodity or options market that are still open.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
OpenInterest_29
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 29 };

    /// Initializes a blank instance.
    OpenInterest_29() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    OpenInterest_29(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    OpenInterest_29(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    OpenInterest_29(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Open Interest.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::OPEN_INTEREST;
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Indicates volume of contracts currently open.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity mDEntrySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<Quantity>(offset);
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            32;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            32;
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "OpenInterest_29";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("OpenInterest_29");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Header for the snapshot of a single instrument.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
SnapshotFullRefresh_Header_30
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 30 };

    /// Initializes a blank instance.
    SnapshotFullRefresh_Header_30() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    SnapshotFullRefresh_Header_30(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SnapshotFullRefresh_Header_30(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SnapshotFullRefresh_Header_30(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataSnapshotFullRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// The last processed packet sequence number of the
    /// incremental channel as of the time the snapshot was
    /// generated. This value is used to synchronize the snapshot
    /// with the incremental feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SeqNum lastMsgSeqNumProcessed() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<SeqNum>(offset);
    }

    /// Total number of snapshots to be returned in the current
    /// replay loop.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt32 totNumReports() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UInt32>(offset);
    }

    /// Total number of bid orders that constitute this snapshot.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt32 totNumBids() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary<UInt32>(offset);
    }

    /// Total number of ask orders that constitute this snapshot.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt32 totNumOffers() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<UInt32>(offset);
    }

    /// Total number of statistics (incremental and security
    /// status messages) that constitute this snapshot.
    ONIXS_B3_UMDF_MD_NODISCARD
    UInt16 totNumStats() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary<UInt16>(offset);
    }

    /// Last processed RptSeq (sequence number per instrument
    /// update) for this instrument. Can be used to synchronize
    /// the snapshot with the incremental feed if the client is
    /// only interested in a subset of the channel's instruments.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool lastRptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullRptSeq());
    }

    /// The last processed packet sequence version of the
    /// incremental channel as of the time the snapshot was
    /// generated. This value is used to synchronize the snapshot
    /// with the incremental feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool lastSequenceVersion(UInt16NULL& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullUInt16NULL());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength 
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            34;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "SnapshotFullRefresh_Header_30";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef(
            "SnapshotFullRefresh_Header_30");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Disseminates the creation or modification of a new order.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
Order_MBO_50
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 50 };

    /// Initializes a blank instance.
    Order_MBO_50() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    Order_MBO_50(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Order_MBO_50(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Order_MBO_50(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 4-Implied, 5-RecoveryMsg and
    /// 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW, CHANGE).
    ONIXS_B3_UMDF_MD_NODISCARD
    UpdateAction::Enum mDUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<UpdateAction>(offset);
    }

    /// Entry Type (BID or OFFER).
    ONIXS_B3_UMDF_MD_NODISCARD
    EntryType::Enum mDEntryType() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<EntryType>(offset);
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryPx(PriceOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Displayed quantity or volume represented by the Market
    /// Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity mDEntrySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Quantity>(offset);
    }

    /// Identifies the broker firm.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool enteringFirm(FirmOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// The date and time when the order was inserted or re-
    /// inserted into the order book or manually altered by
    /// MktOps.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDInsertTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Exchange-generated identifier of the order that updates
    /// with each order modification event involving a loss of
    /// priority, price change, or quantity replenishment in
    /// disclosed orders. This identifier reflects the order's
    /// priority relative to other orders at the same price level
    /// in an ascending manner, where smaller values indicate
    /// higher priority.
    ONIXS_B3_UMDF_MD_NODISCARD
    OrderID secondaryOrderId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary<OrderID>(offset);
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Timestamp when the order event occurred.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Previously displayed quantity or volume represented by the
    /// Market Data Entry. Present only in when
    /// mDUpdateAction=CHANGE and represents the previous quantity
    /// of the order before the modification. Absent for new
    /// order.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryPrevSize(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 64;
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR SchemaVersion since = 16;

        return ordinary(value, offset, NullQuantityOptional(), since);
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            (version >= 16)
                ? 72
                : 64;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "Order_MBO_50";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("Order_MBO_50");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Disseminates the deletion of a new order.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
DeleteOrder_MBO_51
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 51 };

    /// Initializes a blank instance.
    DeleteOrder_MBO_51() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    DeleteOrder_MBO_51(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    DeleteOrder_MBO_51(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    DeleteOrder_MBO_51(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 4-Implied and 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (DELETE).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::DELETE;
    }

    /// Entry Type (BID or OFFER).
    ONIXS_B3_UMDF_MD_NODISCARD
    EntryType::Enum mDEntryType() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<EntryType>(offset);
    }

    /// Quantity of the deleted order.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity mDEntrySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary<Quantity>(offset);
    }

    /// Exchange-generated identifier of the order that is deleted
    /// from the book. This identifier reflects the order's
    /// priority relative to other orders at the same price level
    /// in an ascending manner, where smaller values indicate
    /// higher priority.
    ONIXS_B3_UMDF_MD_NODISCARD
    OrderID secondaryOrderId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary<OrderID>(offset);
    }

    /// Timestamp when the order event occurred.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Price per share or contract of the deleted order.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryPx(PriceOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            52;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "DeleteOrder_MBO_51";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("DeleteOrder_MBO_51");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Disseminates mass deletion of orders.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
MassDeleteOrders_MBO_52
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 52 };

    /// Initializes a blank instance.
    MassDeleteOrders_MBO_52() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    MassDeleteOrders_MBO_52(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    MassDeleteOrders_MBO_52(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    MassDeleteOrders_MBO_52(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (always DELETE_THRU).
    ONIXS_B3_UMDF_MD_NODISCARD
    UpdateAction::Enum mDUpdateAction() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<UpdateAction>(offset);
    }

    /// Entry Type (BID or OFFER).
    ONIXS_B3_UMDF_MD_NODISCARD
    EntryType::Enum mDEntryType() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<EntryType>(offset);
    }

    /// Timestamp when the mass delete order event occurred.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            28;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "MassDeleteOrders_MBO_52";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef(
            "MassDeleteOrders_MBO_52");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Relays trade information on one instrument.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
Trade_53
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 53 };

    /// Initializes a blank instance.
    Trade_53() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    Trade_53(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Trade_53(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Trade_53(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 4-Implied and 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Trade.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::TRADE;
    }

    /// Identifier for trading session.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionID::Enum tradingSessionId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<TradingSessionID>(offset);
    }

    /// Set of conditions describing a trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradeCondition tradeCondition() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return ordinary<TradeCondition>(offset);
    }

    /// Price of the Market Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Quantity or volume represented by the Market Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity mDEntrySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Quantity>(offset);
    }

    /// Contains the unique identifier for this trade per
    /// instrument + trading date, as assigned by the exchange.
    /// Required if reporting a Trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradeID tradeId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<TradeID>(offset);
    }

    /// For reporting trades (buying party).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryBuyer(FirmOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// For reporting trades (selling party).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntrySeller(FirmOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Sub type of trade assigned to a trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool trdSubType(TrdSubType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 42;

        return enumeration<TrdSubType>(value, offset, NullUInt8NULL());
    }

    /// Timestamp when the trade event occurred. If a trade is
    /// amended, the value of the field is set manually by MktOps.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            56;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "Trade_53";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("Trade_53");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Relays trade information on one Forward instrument.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
ForwardTrade_54
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 54 };

    /// Initializes a blank instance.
    ForwardTrade_54() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    ForwardTrade_54(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ForwardTrade_54(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ForwardTrade_54(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Trade.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::TRADE;
    }

    /// Identifier for trading session.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionID::Enum tradingSessionId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<TradingSessionID>(offset);
    }

    /// Set of conditions describing a trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradeCondition tradeCondition() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return ordinary<TradeCondition>(offset);
    }

    /// Price of the Market Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Quantity or volume represented by the Market Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity mDEntrySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Quantity>(offset);
    }

    /// Contains the unique identifier for this trade per
    /// instrument + trading date, as assigned by the exchange.
    /// Required if reporting a Trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradeID tradeId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<TradeID>(offset);
    }

    /// For reporting trades (buying party).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryBuyer(FirmOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// For reporting trades (selling party).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntrySeller(FirmOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Timestamp when the trade event occurred. If a trade is
    /// amended, the value of the field is set manually by MktOps.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 42;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 50;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Specifies the number of days that may elapse before
    /// delivery of the security. Only used for trades in forward
    /// market.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool sellerDays(UInt16NULL& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 54;

        return ordinary(value, offset, NullUInt16NULL());
    }

    /// Interest Rate of the Termo Trade. Expressed in decimal
    /// form. For example, 1% points is expressed and sent as
    /// 0.01. One basis point is represented as 0.0001.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryInterestRate(Percentage& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return decimal(value, offset, NullPercentage());
    }

    /// Sub type of trade assigned to a trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool trdSubType(TrdSubType::Enum& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return enumeration<TrdSubType>(value, offset, NullUInt8NULL());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            68;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            68;
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "ForwardTrade_54";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("ForwardTrade_54");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Relays execution summary information on one instrument.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
ExecutionSummary_55
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 55 };

    /// Initializes a blank instance.
    ExecutionSummary_55() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    ExecutionSummary_55(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionSummary_55(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionSummary_55(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Execution Summary.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::EXECUTION_SUMMARY;
    }

    /// Which side is aggressor of all fills.
    ONIXS_B3_UMDF_MD_NODISCARD
    AggressorSide::Enum aggressorSide() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return enumeration<AggressorSide>(offset);
    }

    /// Price of the last fill (i.e. worst price of this match).
    ONIXS_B3_UMDF_MD_NODISCARD
    Price lastPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Quantity of all fills.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity fillQty() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Quantity>(offset);
    }

    /// Total quantity of matched passive orders that is not
    /// displayed to the market.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool tradedHiddenQty(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Total quantity canceled during matching process (e.g. due
    /// to self trade).
    ONIXS_B3_UMDF_MD_NODISCARD
    bool cxlQty(QuantityOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Timestamp of aggressive order resulting in match event.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool aggressorTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Timestamp when the last trade of the execution event
    /// occurred.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            64;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionSummary_55";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("ExecutionSummary_55");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Relays execution summary statistics information on one instrument.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
ExecutionStatistics_56
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 56 };

    /// Initializes a blank instance.
    ExecutionStatistics_56() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    ExecutionStatistics_56(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionStatistics_56(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionStatistics_56(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (NEW) - always replace.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::NEW;
    }

    /// Entry type: Execution Statistics.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::EXECUTION_STATISTICS;
    }

    /// Identifier for trading session.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionID::Enum tradingSessionId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<TradingSessionID>(offset);
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 10;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Total traded volume for the session.
    ONIXS_B3_UMDF_MD_NODISCARD
    QuantityVolume tradeVolume() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<QuantityVolume>(offset);
    }

    /// Volume-weighted average price.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool vwapPx(PriceOptional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Net change from previous trading day’s closing price vs.
    /// last traded price.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool
    netChgPrevDay(
        PriceOffset8Optional& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return decimal(value, offset, NullPriceOffset8Optional());
    }

    /// Number of trades executed in the session.
    ONIXS_B3_UMDF_MD_NODISCARD
    NumberOfTrades numberOfTrades() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<NumberOfTrades>(offset);
    }

    /// Date and time of market data entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool mDEntryTimestamp(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            52;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionStatistics_56";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("ExecutionStatistics_56");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Relays trade bust (trade reversal) information on one instrument.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
TradeBust_57
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 57 };

    /// Initializes a blank instance.
    TradeBust_57() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    TradeBust_57(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    TradeBust_57(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    TradeBust_57(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataIncrementalRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Set of indicators that identify some market data events.
    /// Bits applied to this message: 4-Implied and 7-EndOfEvent.
    ONIXS_B3_UMDF_MD_NODISCARD
    MatchEventIndicator matchEventIndicator() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

        return ordinary<MatchEventIndicator>(offset);
    }

    /// Update Action (DELETE) = always delete.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static UpdateAction::Enum mDUpdateAction()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return UpdateAction::DELETE;
    }

    /// Entry type: Trade Bust.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static EntryType::Enum mDEntryType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return EntryType::TRADE_BUST;
    }

    /// Identifier for trading session.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradingSessionID::Enum tradingSessionId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 9;

        return enumeration<TradingSessionID>(offset);
    }

    /// Price of the Market Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Price mDEntryPx() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return decimal<Price>(offset);
    }

    /// Quantity or volume represented by the Market Data Entry.
    ONIXS_B3_UMDF_MD_NODISCARD
    Quantity mDEntrySize() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Quantity>(offset);
    }

    /// Contains the unique identifier for this trade per
    /// instrument + trading date, as assigned by the exchange.
    /// Required if reporting a Trade.
    ONIXS_B3_UMDF_MD_NODISCARD
    TradeID tradeId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<TradeID>(offset);
    }

    /// Used to specify the trading date for which a set of market
    /// data applies.
    ONIXS_B3_UMDF_MD_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Timestamp when the trade bust event occurred.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool transactTime(UTCTimestampNanos& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullUTCTimestampNanos());
    }

    /// Sequence number per instrument update. Zeroed in snapshot
    /// feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    bool rptSeq(RptSeq& value) const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullRptSeq());
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            48;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "TradeBust_57";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("TradeBust_57");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
    }
};

/// Partial list of orders for the snapshot of a single instrument.
ONIXS_B3_UMDF_MD_LTWT_STRUCT
SnapshotFullRefresh_Orders_MBO_71
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// Message template ID from SBE schema.
    enum { TemplateId = 71 };

    /// Partial list of orders.
    /// Entry of Entry repeating group.
    ONIXS_B3_UMDF_MD_LTWT_STRUCT
    Entry : SbeGroupEntry
    <
        GroupSizeEncoding::BlockLength
    >
    {
        /// Base class type.
        typedef
        SbeGroupEntry
        <
            GroupSizeEncoding::BlockLength
        >
        Base;

        /// Initializes instance of given
        /// version over given memory block.
        Entry(
            const void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Price per share or contract. Conditionally required if the
        /// order type requires a price (not market orders).
        ONIXS_B3_UMDF_MD_NODISCARD
        bool mDEntryPx(PriceOptional& value) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return decimal(value, offset, NullPriceOptional());
        }

        /// Displayed quantity or volume represented by the Market
        /// Data Entry.
        ONIXS_B3_UMDF_MD_NODISCARD
        Quantity mDEntrySize() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 8;

            return ordinary<Quantity>(offset);
        }

        /// Identifies the broker firm.
        ONIXS_B3_UMDF_MD_NODISCARD
        bool enteringFirm(FirmOptional& value) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 20;

            return ordinary(value, offset, NullFirmOptional());
        }

        /// The date and time when the order was inserted or re-
        /// inserted into the order book or manually altered by
        /// MktOps.
        ONIXS_B3_UMDF_MD_NODISCARD
        bool mDInsertTimestamp(UTCTimestampNanos& value) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 24;

            return ordinary(value, offset, NullUTCTimestampNanos());
        }

        /// Exchange-generated identifier of the order that updates
        /// with each order modification event involving a loss of
        /// priority, price change, or quantity replenishment in
        /// disclosed orders. This identifier reflects the order's
        /// priority relative to other orders at the same price level
        /// in an ascending manner, where smaller values indicate
        /// higher priority.
        ONIXS_B3_UMDF_MD_NODISCARD
        OrderID secondaryOrderId() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 32;

            return ordinary<OrderID>(offset);
        }

        /// Entry Type (BID or OFFER).
        ONIXS_B3_UMDF_MD_NODISCARD
        EntryType::Enum mDEntryType() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 40;

            return enumeration<EntryType>(offset);
        }

        /// Set of indicators that identify some market data events.
        /// Bits applied to this message: 4-Implied.
        ONIXS_B3_UMDF_MD_NODISCARD
        MatchEventIndicator matchEventIndicator() const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 41;

            return ordinary<MatchEventIndicator>(offset);
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static
        BlockLength
        blockLength(
            ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                42;
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static
        BlockLength 
        minimalBlockLength(
            ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return
                ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
                42;
        }

        /// Entity class name.
        ONIXS_B3_UMDF_MD_LTWT_EXPORTED
        ONIXS_B3_UMDF_MD_NODISCARD
        ONIXS_B3_UMDF_MD_CONSTEXPR
        static const Char* className()
        {
            return "SnapshotFullRefresh_Orders_MBO_71.Entry";
        }
    };

    /// Repeating group containing Entry entries.
    typedef
    SbeGroup<Entry, GroupSizeEncoding, MessageSize>
    Entries;

    /// Initializes a blank instance.
    SnapshotFullRefresh_Orders_MBO_71() ONIXS_B3_UMDF_MD_DEFAULT;

    /// Creates an instance over the given memory block.
    SnapshotFullRefresh_Orders_MBO_71(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SnapshotFullRefresh_Orders_MBO_71(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SnapshotFullRefresh_Orders_MBO_71(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_UMDF_MD_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// FIX Message Type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return MessageType::MarketDataSnapshotFullRefresh;
    }

    /// Specifies the service pack release being applied at
    /// message level.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static ApplVerID::Enum applVerId()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return ApplVerID::FIX50SP2;
    }

    /// Security ID as defined by B3. For the SecurityID list, see
    /// the Security Definition message in Market Data feed.
    ONIXS_B3_UMDF_MD_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SecurityID>(offset);
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return SecurityIDSource::EXCHANGE_SYMBOL;
    }

    /// Market to which the symbol belongs.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// \return instance of Entries repeating group.
    ONIXS_B3_UMDF_MD_NODISCARD
    Entries entries() const
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return getGroup<Entries>(EntriesAccess(), *this);
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            8;
    }

    /// Size of message body in bytes.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_UMDF_MD_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_UMDF_MD_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(Entries::EmptySize);
    }

    /// \return class name.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static const Char* className()
    {
        return "SnapshotFullRefresh_Orders_MBO_71";
    }

    /// FIX message type.
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED
    ONIXS_B3_UMDF_MD_NODISCARD
    ONIXS_B3_UMDF_MD_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_UMDF_MD_NOTHROW
    {
        return constructStrRef(
            "SnapshotFullRefresh_Orders_MBO_71");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_UMDF_MD_NODISCARD
    std::string toString() const;

private:
    void checkLength(
        EncodedLength length, SchemaVersion version) const
    {
       const EncodedLength minimalRequiredLength =
           minimalBlockLength(version) +
           MessageHeader::Size +
           getMinimalVariableFieldsSize(version);

       checkBinaryLength(
           *this, length, minimalRequiredLength);
    }

    /// Checks variable fields consistency.
    void checkVarLenFields() const
    {
        groups().
            checkTail<Entries>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct EntriesAccess
    {
        Entries
        operator()(
            const SnapshotFullRefresh_Orders_MBO_71& obj) const
            ONIXS_B3_UMDF_MD_NOTHROW
        {
            return obj.
                groups().
                    head<Entries>();
        }
    };
};


ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
