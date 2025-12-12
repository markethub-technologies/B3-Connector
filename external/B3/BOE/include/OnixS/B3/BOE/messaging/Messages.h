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

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/messaging/Composites.h>
#include <OnixS/B3/BOE/messaging/SbeMessage.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// The client sends the Negotiate message to B3 to initiate a connection. Negotiate is the first message that the client must sent to start the communication between client and gateway through a TCP socket connection.
ONIXS_B3_BOE_LTWT_STRUCT
Negotiate1
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef Negotiate1 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 1 };

    /// Initializes a blank instance.
    Negotiate1() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    Negotiate1(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    Negotiate1(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    Negotiate1(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Negotiate1(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Negotiate1(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = Negotiate.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::Negotiate;
    }

    /// Message type = Negotiate.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SessionVerID sessionVerId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<SessionVerID>(offset);
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ThisType& setSessionVerId(SessionVerID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of request. Sent in number of nanoseconds since Unix
    /// epoch.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos timestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of request. Sent in number of nanoseconds since Unix
    /// epoch.
    ThisType& setTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Type of flow from client to server. It is a constant value
    /// = idempotent.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static FlowType::Enum clientFlow()
        ONIXS_B3_BOE_NOTHROW
    {
        return FlowType::Idempotent;
    }

    /// Type of flow from client to server. It is a constant value
    /// = idempotent.

    /// Identifies the broker firm that will enter orders.
    ONIXS_B3_BOE_NODISCARD
    Firm enteringFirm() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Firm>(offset);
    }

    /// Identifies the broker firm that will enter orders.
    ThisType& setEnteringFirm(Firm value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the broker firm who executes their orders on
    /// behalf.
    ONIXS_B3_BOE_NODISCARD
    bool onbehalfFirm(FirmOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// Identifies the broker firm who executes their orders on
    /// behalf.
    ThisType& setOnbehalfFirm(FirmOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOnbehalfFirmToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        setOrdinary(offset, NullFirmOptional());
        return *this;
    }

    /// Credentials to identify/authenticate the client. The format is a JSON with the following data: { "auth_type": "basic", "username": "session_id", "access_key": "somepassword" }.
    ONIXS_B3_BOE_NODISCARD
    StrRef credentials() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(
            credentialsAccess(),
            *this);
    }

    /// Source IP from client system.
    ONIXS_B3_BOE_NODISCARD
    StrRef clientIP() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(clientIPAccess(), *this);
    }

    /// Application name as informed during certification process.
    ONIXS_B3_BOE_NODISCARD
    StrRef clientAppName() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(
            clientAppNameAccess(),
            *this);
    }

    /// Application version as informed during certification process.
    ONIXS_B3_BOE_NODISCARD
    StrRef clientAppVersion() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(
            clientAppVersionAccess(),
            *this);
    }

    /// Credentials to identify/authenticate the client. The format is a JSON with the following data: { "auth_type": "basic", "username": "session_id", "access_key": "somepassword" }.
    ThisType& setCredentials(StrRef value)
    {
        setVariableLengthField(
            credentialsAccess(),
            value,
            *this);

        return *this;
    }

    /// Source IP from client system.
    ThisType& setClientIP(StrRef value)
    {
        setVariableLengthField(
            clientIPAccess(),
            value,
            *this);

        return *this;
    }

    /// Application name as informed during certification process.
    ThisType& setClientAppName(StrRef value)
    {
        setVariableLengthField(
            clientAppNameAccess(),
            value,
            *this);

        return *this;
    }

    /// Application version as informed during certification process.
    ThisType& setClientAppVersion(StrRef value)
    {
        setVariableLengthField(
            clientAppVersionAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            28;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(CredentialsEncoding::Size) + static_cast<MessageSize>(ClientAppEncoding::Size) + static_cast<MessageSize>(ClientAppEncoding::Size) + static_cast<MessageSize>(ClientAppEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setCredentialsToNull();
        setClientIPToNull();
        setClientAppNameToNull();
        setClientAppVersionToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setOnbehalfFirmToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "Negotiate1";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("Negotiate1");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (clientAppVersion().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<CredentialsEncoding>().
            checkTail<ClientAppEncoding>().
            checkTail<ClientAppEncoding>().
            checkTail<ClientAppEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct credentialsAccess
    {
        CredentialsEncoding& operator()(const Negotiate1& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<CredentialsEncoding>();
        }
    };

    /// Access helper.
    struct clientIPAccess
    {
        ClientAppEncoding& operator()(const Negotiate1& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<CredentialsEncoding>().
                    head<ClientAppEncoding>();
        }
    };

    /// Access helper.
    struct clientAppNameAccess
    {
        ClientAppEncoding& operator()(const Negotiate1& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<CredentialsEncoding>().
                    tail<ClientAppEncoding>().
                    head<ClientAppEncoding>();
        }
    };

    /// Access helper.
    struct clientAppVersionAccess
    {
        ClientAppEncoding& operator()(const Negotiate1& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<CredentialsEncoding>().
                    tail<ClientAppEncoding>().
                    tail<ClientAppEncoding>().
                    head<ClientAppEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setCredentialsToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(
            credentialsAccess(),
            *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setClientIPToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(clientIPAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setClientAppNameToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(
            clientAppNameAccess(),
            *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setClientAppVersionToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(
            clientAppVersionAccess(),
            *this);

        return *this;
    }
};

/// The NegotiationResponse message is sent when a Negotiate message from the client is accepted by B3.
ONIXS_B3_BOE_LTWT_STRUCT
NegotiateResponse2
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef NegotiateResponse2 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 2 };

    /// Initializes a blank instance.
    NegotiateResponse2() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    NegotiateResponse2(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    NegotiateResponse2(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    NegotiateResponse2(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    NegotiateResponse2(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    NegotiateResponse2(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = NegotiateResponse.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::NegotiateResponse;
    }

    /// Message type = NegotiateResponse.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SessionVerID sessionVerId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<SessionVerID>(offset);
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ThisType& setSessionVerId(SessionVerID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Matches Negotiate timestamp.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos requestTimestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Matches Negotiate timestamp.
    ThisType& setRequestTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Type of flow from client to server. It is a constant value
    /// = recoverable.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static FlowType::Enum serverFlow()
        ONIXS_B3_BOE_NOTHROW
    {
        return FlowType::Recoverable;
    }

    /// Type of flow from client to server. It is a constant value
    /// = recoverable.

    /// Type of flow from client to server. It is a constant value
    /// = idempotent.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static FlowType::Enum clientFlow()
        ONIXS_B3_BOE_NOTHROW
    {
        return FlowType::Idempotent;
    }

    /// Type of flow from client to server. It is a constant value
    /// = idempotent.

    /// Identifies the broker firm that will enter orders.
    ONIXS_B3_BOE_NODISCARD
    Firm enteringFirm() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<Firm>(offset);
    }

    /// Identifies the broker firm that will enter orders.
    ThisType& setEnteringFirm(Firm value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the semantic version of the schema used in this
    /// session.
    ONIXS_B3_BOE_NODISCARD
    bool semanticVersion(Version& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 4;

        return ordinary(value, offset, NullVersion(), since);
    }

    /// Identifies the semantic version of the schema used in this
    /// session.
    ThisType& setSemanticVersion(Version value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 4;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setSemanticVersionToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 4;

        setOrdinary(offset, NullVersion(), since);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 4)
                ? 28
                : 24;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        if (version() >= 4)
        {
            setSemanticVersionToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "NegotiateResponse2";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("NegotiateResponse2");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// NegotiateReject message is sent when B3 rejects a Negotiate message sent by the client.
ONIXS_B3_BOE_LTWT_STRUCT
NegotiateReject3
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef NegotiateReject3 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 3 };

    /// Initializes a blank instance.
    NegotiateReject3() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    NegotiateReject3(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    NegotiateReject3(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    NegotiateReject3(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    NegotiateReject3(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    NegotiateReject3(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = NegotiateReject.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::NegotiateReject;
    }

    /// Message type = NegotiateReject.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SessionVerID sessionVerId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<SessionVerID>(offset);
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ThisType& setSessionVerId(SessionVerID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Matches Negotiate timestamp.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos requestTimestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Matches Negotiate timestamp.
    ThisType& setRequestTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Type of flow from client to server. It is a constant value
    /// = idempotent.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static FlowType::Enum clientFlow()
        ONIXS_B3_BOE_NOTHROW
    {
        return FlowType::Idempotent;
    }

    /// Type of flow from client to server. It is a constant value
    /// = idempotent.

    /// Identifies the broker firm that will enter orders.
    ONIXS_B3_BOE_NODISCARD
    bool enteringFirm(FirmOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullFirmOptional());
    }

    /// Identifies the broker firm that will enter orders.
    ThisType& setEnteringFirm(FirmOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setEnteringFirmToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, NullFirmOptional());
        return *this;
    }

    /// Identifies the code of reject negotiation.
    ONIXS_B3_BOE_NODISCARD
    NegotiationRejectCode::Enum
    negotiationRejectCode() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return enumeration<NegotiationRejectCode>(offset);
    }

    /// Identifies the code of reject negotiation.
    ThisType&
    setNegotiationRejectCode(
        NegotiationRejectCode::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        setEnumeration<NegotiationRejectCode>(offset, value);
        return *this;
    }

    /// The current sessionVerID informed at the first Negotiate
    /// message for that specific session.
    ONIXS_B3_BOE_NODISCARD
    bool
    currentSessionVerId(
        SessionVerIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullSessionVerIDOptional());
    }

    /// The current sessionVerID informed at the first Negotiate
    /// message for that specific session.
    ThisType&
    setCurrentSessionVerId(
        SessionVerIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setCurrentSessionVerIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullSessionVerIDOptional());
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setEnteringFirmToNull();
        setCurrentSessionVerIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "NegotiateReject3";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("NegotiateReject3");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// After negotiation level is complete, the client must send an Establish message to start assigning sequence numbers and also to keep the connection active. Once the connection is established, client can submit orders and quotes.
ONIXS_B3_BOE_LTWT_STRUCT
Establish4
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef Establish4 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 4 };

    /// Initializes a blank instance.
    Establish4() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    Establish4(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    Establish4(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    Establish4(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Establish4(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Establish4(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = Establish.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::Establish;
    }

    /// Message type = Establish.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SessionVerID sessionVerId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<SessionVerID>(offset);
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ThisType& setSessionVerId(SessionVerID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of request. Sent in number of nanoseconds since Unix
    /// epoch.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos timestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of request. Sent in number of nanoseconds since Unix
    /// epoch.
    ThisType& setTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Longest time in milliseconds the initiator should remain
    /// silent before sending Sequence message. It should be in
    /// the range of 1000 to 60000 (inclusive).
    ONIXS_B3_BOE_NODISCARD
    DeltaInMillis keepAliveInterval() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<DeltaInMillis>(offset);
    }

    /// Longest time in milliseconds the initiator should remain
    /// silent before sending Sequence message. It should be in
    /// the range of 1000 to 60000 (inclusive).
    ThisType& setKeepAliveInterval(DeltaInMillis value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// The next application sequence number to be produced by the
    /// client.
    ONIXS_B3_BOE_NODISCARD
    SeqNum nextSeqNo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<SeqNum>(offset);
    }

    /// The next application sequence number to be produced by the
    /// client.
    ThisType& setNextSeqNo(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Criteria used to initiate cancel on disconnect mechanism
    /// by the gateway.
    ONIXS_B3_BOE_NODISCARD
    CancelOnDisconnectType::Enum
    cancelOnDisconnectType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return enumeration<CancelOnDisconnectType>(offset);
    }

    /// Criteria used to initiate cancel on disconnect mechanism
    /// by the gateway.
    ThisType&
    setCancelOnDisconnectType(
        CancelOnDisconnectType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        setEnumeration<CancelOnDisconnectType>(offset, value);
        return *this;
    }

    /// Gateway will not trigger CoD if the customer reconnects
    /// within the timeout window (milliseconds) which starts when
    /// the triggering event is detected. Range is 0 (as soon as
    /// possible) to 60000.
    ONIXS_B3_BOE_NODISCARD
    DeltaInMillis codTimeoutWindow() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        return ordinary<DeltaInMillis>(offset);
    }

    /// Gateway will not trigger CoD if the customer reconnects
    /// within the timeout window (milliseconds) which starts when
    /// the triggering event is detected. Range is 0 (as soon as
    /// possible) to 60000.
    ThisType& setCodTimeoutWindow(DeltaInMillis value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setOrdinary(offset, value);
        return *this;
    }

    /// Credentials to identify/authenticate the client. The format is a JSON with the following data: { "auth_type": "basic", "username": "session_id", "access_key": "somepassword" }.
    ONIXS_B3_BOE_NODISCARD
    StrRef credentials() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(
            credentialsAccess(),
            *this);
    }

    /// Credentials to identify/authenticate the client. The format is a JSON with the following data: { "auth_type": "basic", "username": "session_id", "access_key": "somepassword" }.
    ThisType& setCredentials(StrRef value)
    {
        setVariableLengthField(
            credentialsAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            42;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(CredentialsEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setCredentialsToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "Establish4";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("Establish4");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (credentials().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<CredentialsEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct credentialsAccess
    {
        CredentialsEncoding& operator()(const Establish4& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<CredentialsEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setCredentialsToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(
            credentialsAccess(),
            *this);

        return *this;
    }
};

/// The EstablishmentAck message is sent when an Establish message is accepted by B3. EstablishmentAck message contains next sequence number. At the start of a session, default value is 1 (one).
ONIXS_B3_BOE_LTWT_STRUCT
EstablishAck5
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef EstablishAck5 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 5 };

    /// Initializes a blank instance.
    EstablishAck5() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    EstablishAck5(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    EstablishAck5(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    EstablishAck5(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    EstablishAck5(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    EstablishAck5(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = EstablishAck.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::EstablishAck;
    }

    /// Message type = EstablishAck.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SessionVerID sessionVerId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<SessionVerID>(offset);
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ThisType& setSessionVerId(SessionVerID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Matches Negotiate timestamp.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos requestTimestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Matches Negotiate timestamp.
    ThisType& setRequestTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Longest time in milliseconds the initiator should remain
    /// silent before sending Sequence message.
    ONIXS_B3_BOE_NODISCARD
    DeltaInMillis keepAliveInterval() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<DeltaInMillis>(offset);
    }

    /// Longest time in milliseconds the initiator should remain
    /// silent before sending Sequence message.
    ThisType& setKeepAliveInterval(DeltaInMillis value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// The next application sequence number to be produced by the
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SeqNum nextSeqNo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<SeqNum>(offset);
    }

    /// The next application sequence number to be produced by the
    /// gateway.
    ThisType& setNextSeqNo(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Indicates the application sequence number of the last
    /// application message received by the server from the
    /// client. At the start of a session, default value is 0
    /// (zero).
    ONIXS_B3_BOE_NODISCARD
    SeqNum lastIncomingSeqNo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary<SeqNum>(offset);
    }

    /// Indicates the application sequence number of the last
    /// application message received by the server from the
    /// client. At the start of a session, default value is 0
    /// (zero).
    ThisType& setLastIncomingSeqNo(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        setOrdinary(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "EstablishAck5";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("EstablishAck5");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// EstablishmentReject message is sent when an Establish message is rejected by B3 informing the reason of rejection.
ONIXS_B3_BOE_LTWT_STRUCT
EstablishReject6
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef EstablishReject6 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 6 };

    /// Initializes a blank instance.
    EstablishReject6() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    EstablishReject6(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    EstablishReject6(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    EstablishReject6(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    EstablishReject6(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    EstablishReject6(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = EstablishReject.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::EstablishReject;
    }

    /// Message type = EstablishReject.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SessionVerID sessionVerId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<SessionVerID>(offset);
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ThisType& setSessionVerId(SessionVerID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Matches Negotiate timestamp.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos requestTimestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Matches Negotiate timestamp.
    ThisType& setRequestTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the code of reject establishment.
    ONIXS_B3_BOE_NODISCARD
    EstablishRejectCode::Enum
    establishmentRejectCode() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return enumeration<EstablishRejectCode>(offset);
    }

    /// Identifies the code of reject establishment.
    ThisType&
    setEstablishmentRejectCode(
        EstablishRejectCode::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setEnumeration<EstablishRejectCode>(offset, value);
        return *this;
    }

    /// If establishmentRejectCode =
    /// EstablishRejectCode.INVALID_NEXTSEQNO, indicates the
    /// application sequence number of the last application
    /// message received by the server from the client. At the
    /// start of a session, default value is 0 (zero).
    ONIXS_B3_BOE_NODISCARD
    bool lastIncomingSeqNo(SeqNumOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 22;

        return ordinary(value, offset, NullSeqNumOptional());
    }

    /// If establishmentRejectCode =
    /// EstablishRejectCode.INVALID_NEXTSEQNO, indicates the
    /// application sequence number of the last application
    /// message received by the server from the client. At the
    /// start of a session, default value is 0 (zero).
    ThisType& setLastIncomingSeqNo(SeqNumOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 22;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setLastIncomingSeqNoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 22;

        setOrdinary(offset, NullSeqNumOptional());
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            26;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setLastIncomingSeqNoToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "EstablishReject6";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("EstablishReject6");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// Terminate message is sent to indicate that the sender is going to disconnect the TCP socket connection.
ONIXS_B3_BOE_LTWT_STRUCT
Terminate7
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef Terminate7 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 7 };

    /// Initializes a blank instance.
    Terminate7() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    Terminate7(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    Terminate7(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    Terminate7(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Terminate7(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Terminate7(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = Terminate.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::Terminate;
    }

    /// Message type = Terminate.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ONIXS_B3_BOE_NODISCARD
    SessionVerID sessionVerId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<SessionVerID>(offset);
    }

    /// Session version identification: unique identification of a
    /// sequence of messages to be transmitted to/from B3´s
    /// gateways associated with given SessionId. Need to be
    /// incremented each time Negotiate message is sent to
    /// gateway.
    ThisType& setSessionVerId(SessionVerID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the code of termination.
    ONIXS_B3_BOE_NODISCARD
    TerminationCode::Enum terminationCode() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return enumeration<TerminationCode>(offset);
    }

    /// Identifies the code of termination.
    ThisType&
    setTerminationCode(
        TerminationCode::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setEnumeration<TerminationCode>(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            13;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "Terminate7";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("Terminate7");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// NotApplied message is sent when B3 detects messages that already been sent (concept of idempotence) or an invalid message format from the client.
ONIXS_B3_BOE_LTWT_STRUCT
NotApplied8
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef NotApplied8 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 8 };

    /// Initializes a blank instance.
    NotApplied8() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    NotApplied8(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    NotApplied8(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    NotApplied8(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    NotApplied8(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    NotApplied8(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = NotApplied.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::NotApplied;
    }

    /// Message type = NotApplied.

    /// The first applied sequence number.
    ONIXS_B3_BOE_NODISCARD
    SeqNum fromSeqNo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SeqNum>(offset);
    }

    /// The first applied sequence number.
    ThisType& setFromSeqNo(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// How many messages haven´t been applied?.
    ONIXS_B3_BOE_NODISCARD
    MessageCounter count() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<MessageCounter>(offset);
    }

    /// How many messages haven´t been applied?.
    ThisType& setCount(MessageCounter value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            8;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "NotApplied8";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("NotApplied8");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// Sequence message specifies the sequence number of the next business message both: Recoverable (B3 to client) and Idempotent (client to B3) flows. It is also used as heartbeat.
ONIXS_B3_BOE_LTWT_STRUCT
Sequence9
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef Sequence9 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 9 };

    /// Initializes a blank instance.
    Sequence9() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    Sequence9(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    Sequence9(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    Sequence9(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Sequence9(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Sequence9(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = Sequence.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::Sequence;
    }

    /// Message type = Sequence.

    /// The next application sequence number to be produced by the
    /// client.
    ONIXS_B3_BOE_NODISCARD
    SeqNum nextSeqNo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SeqNum>(offset);
    }

    /// The next application sequence number to be produced by the
    /// client.
    ThisType& setNextSeqNo(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            4;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "Sequence9";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("Sequence9");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// RetransmitRequest message is used for client to recover missed messages.
ONIXS_B3_BOE_LTWT_STRUCT
RetransmitRequest12
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef RetransmitRequest12 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 12 };

    /// Initializes a blank instance.
    RetransmitRequest12() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    RetransmitRequest12(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    RetransmitRequest12(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    RetransmitRequest12(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    RetransmitRequest12(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    RetransmitRequest12(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = RetransmitRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::RetransmitRequest;
    }

    /// Message type = RetransmitRequest.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of request. Sent in number of nanoseconds since Unix
    /// epoch.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos timestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of request. Sent in number of nanoseconds since Unix
    /// epoch.
    ThisType& setTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// The first applied sequence number.
    ONIXS_B3_BOE_NODISCARD
    SeqNum fromSeqNo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<SeqNum>(offset);
    }

    /// The first applied sequence number.
    ThisType& setFromSeqNo(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Maximum number of messages to be retransmitted. Range is 1
    /// to 1000 (inclusive).
    ONIXS_B3_BOE_NODISCARD
    MessageCounter count() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary<MessageCounter>(offset);
    }

    /// Maximum number of messages to be retransmitted. Range is 1
    /// to 1000 (inclusive).
    ThisType& setCount(MessageCounter value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 16;

        setOrdinary(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            20;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "RetransmitRequest12";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("RetransmitRequest12");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// Retransmission message is sent when a RetransmitRequest message from the client is accepted by B3.
ONIXS_B3_BOE_LTWT_STRUCT
Retransmission13
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef Retransmission13 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 13 };

    /// Initializes a blank instance.
    Retransmission13() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    Retransmission13(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    Retransmission13(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    Retransmission13(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Retransmission13(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Retransmission13(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = Retransmission.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::Retransmission;
    }

    /// Message type = Retransmission.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Matches Negotiate timestamp.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos requestTimestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Matches Negotiate timestamp.
    ThisType& setRequestTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// The sequence number of the first retransmitted message.
    ONIXS_B3_BOE_NODISCARD
    SeqNum nextSeqNo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return ordinary<SeqNum>(offset);
    }

    /// The sequence number of the first retransmitted message.
    ThisType& setNextSeqNo(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setOrdinary(offset, value);
        return *this;
    }

    /// Number of messages to be retransmitted.
    ONIXS_B3_BOE_NODISCARD
    MessageCounter count() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 16;

        return ordinary<MessageCounter>(offset);
    }

    /// Number of messages to be retransmitted.
    ThisType& setCount(MessageCounter value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 16;

        setOrdinary(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            20;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "Retransmission13";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("Retransmission13");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// RetransmitReject message is sent when a RetransmitRequest message is rejected by B3. More details are described in the Message Specification Guidelines document.
ONIXS_B3_BOE_LTWT_STRUCT
RetransmitReject14
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef RetransmitReject14 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 14 };

    /// Initializes a blank instance.
    RetransmitReject14() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    RetransmitReject14(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    RetransmitReject14(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    RetransmitReject14(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    RetransmitReject14(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    RetransmitReject14(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = RetransmitReject.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::RetransmitReject;
    }

    /// Message type = RetransmitReject.

    /// Client connection identification on the gateway assigned
    /// by B3.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return ordinary<SessionID>(offset);
    }

    /// Client connection identification on the gateway assigned
    /// by B3.
    ThisType& setSessionId(SessionID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        setOrdinary(offset, value);
        return *this;
    }

    /// Matches Negotiate timestamp.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos requestTimestamp() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Matches Negotiate timestamp.
    ThisType& setRequestTimestamp(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 4;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the code of reject retransmission.
    ONIXS_B3_BOE_NODISCARD
    RetransmitRejectCode::Enum
    retransmitRejectCode() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        return enumeration<RetransmitRejectCode>(offset);
    }

    /// Identifies the code of reject retransmission.
    ThisType&
    setRetransmitRejectCode(
        RetransmitRejectCode::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 12;

        setEnumeration<RetransmitRejectCode>(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            13;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "RetransmitReject14";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("RetransmitReject14");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// SimpleNewOrder message submits a simple new order focused on sent only main parameters with low complexity. Used by client to enter a simple order in the system.
ONIXS_B3_BOE_LTWT_STRUCT
SimpleNewOrder100
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef SimpleNewOrder100 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 100 };

    /// Initializes a blank instance.
    SimpleNewOrder100() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    SimpleNewOrder100(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    SimpleNewOrder100(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    SimpleNewOrder100(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SimpleNewOrder100(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SimpleNewOrder100(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = SimpleNewOrder.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::SimpleNewOrder;
    }

    /// Message type = SimpleNewOrder.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum mmProtectionReset() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<Boolean>(offset);
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ThisType& setMmProtectionReset(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ONIXS_B3_BOE_NODISCARD
    SelfTradePreventionInstruction::Enum
    selfTradePreventionInstruction() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        return enumeration<SelfTradePreventionInstruction>(offset);
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ThisType&
    setSelfTradePreventionInstruction(
        SelfTradePreventionInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        setEnumeration<SelfTradePreventionInstruction>(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    SimpleOrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        return enumeration<SimpleOrdType>(offset);
    }

    /// Order type.
    ThisType&
    setOrdType(
        SimpleOrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setEnumeration<SimpleOrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    SimpleTimeInForce::Enum timeInForce() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        return enumeration<SimpleTimeInForce>(offset);
    }

    /// Specifies how long the order remains in effect.
    ThisType&
    setTimeInForce(
        SimpleTimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setEnumeration<SimpleTimeInForce>(offset, value);
        return *this;
    }

    /// Indicates additional order instruction.
    ONIXS_B3_BOE_NODISCARD
    bool
    routingInstruction(
        RoutingInstruction::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        return enumeration<RoutingInstruction>(value, offset, NullUint8EnumEncoding());
    }

    /// Indicates additional order instruction.
    ThisType&
    setRoutingInstruction(
        RoutingInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setEnumeration<RoutingInstruction>(offset, value);
        return *this;
    }

    ThisType& setRoutingInstructionToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            84;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setOrdTagIdToNull();
        setAccountToNull();
        setRoutingInstructionToNull();
        setPriceToNull();
        setInvestorIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "SimpleNewOrder100";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("SimpleNewOrder100");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const SimpleNewOrder100& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// The SimpleModifyOrder submits a simple modify request for basic parameters like price and quantity. The client sends the SimpleModifyOrder message to B3 to modify some order values only.
ONIXS_B3_BOE_LTWT_STRUCT
SimpleModifyOrder101
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef SimpleModifyOrder101 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 101 };

    /// Initializes a blank instance.
    SimpleModifyOrder101() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    SimpleModifyOrder101(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    SimpleModifyOrder101(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    SimpleModifyOrder101(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SimpleModifyOrder101(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SimpleModifyOrder101(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = SimpleModifyOrder.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::SimpleModifyOrder;
    }

    /// Message type = SimpleModifyOrder.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum mmProtectionReset() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<Boolean>(offset);
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ThisType& setMmProtectionReset(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ONIXS_B3_BOE_NODISCARD
    SelfTradePreventionInstruction::Enum
    selfTradePreventionInstruction() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        return enumeration<SelfTradePreventionInstruction>(offset);
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ThisType&
    setSelfTradePreventionInstruction(
        SelfTradePreventionInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        setEnumeration<SelfTradePreventionInstruction>(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    SimpleOrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        return enumeration<SimpleOrdType>(offset);
    }

    /// Order type.
    ThisType&
    setOrdType(
        SimpleOrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setEnumeration<SimpleOrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    SimpleTimeInForce::Enum timeInForce() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        return enumeration<SimpleTimeInForce>(offset);
    }

    /// Specifies how long the order remains in effect.
    ThisType&
    setTimeInForce(
        SimpleTimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setEnumeration<SimpleTimeInForce>(offset, value);
        return *this;
    }

    /// Indicates additional order instruction.
    ONIXS_B3_BOE_NODISCARD
    bool
    routingInstruction(
        RoutingInstruction::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        return enumeration<RoutingInstruction>(value, offset, NullUint8EnumEncoding());
    }

    /// Indicates additional order instruction.
    ThisType&
    setRoutingInstruction(
        RoutingInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setEnumeration<RoutingInstruction>(offset, value);
        return *this;
    }

    ThisType& setRoutingInstructionToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    bool orderId(OrderIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        return ordinary(value, offset, NullOrderIDOptional());
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrderIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, NullOrderIDOptional());
        return *this;
    }

    /// ClOrdID which should be replaced.
    ONIXS_B3_BOE_NODISCARD
    bool origClOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// ClOrdID which should be replaced.
    ThisType& setOrigClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Type of account associated with an order.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static AccountType::Enum accountType()
        ONIXS_B3_BOE_NOTHROW
    {
        return AccountType::RegularAccount;
    }

    /// Type of account associated with an order.

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            100;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setOrdTagIdToNull();
        setAccountToNull();
        setRoutingInstructionToNull();
        setPriceToNull();
        setOrderIdToNull();
        setOrigClOrdIdToNull();
        setInvestorIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "SimpleModifyOrder101";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("SimpleModifyOrder101");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const SimpleModifyOrder101& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// NewOrderSingle message is used to enter an order in the system; the behavior of an order can be affected by many parameters such as order type and order type qualifier.
ONIXS_B3_BOE_LTWT_STRUCT
NewOrderSingle102
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef NewOrderSingle102 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 102 };

    /// Initializes a blank instance.
    NewOrderSingle102() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    NewOrderSingle102(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    NewOrderSingle102(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    NewOrderSingle102(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    NewOrderSingle102(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    NewOrderSingle102(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = NewOrderSingle.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::NewOrderSingle;
    }

    /// Message type = NewOrderSingle.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum mmProtectionReset() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<Boolean>(offset);
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ThisType& setMmProtectionReset(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ONIXS_B3_BOE_NODISCARD
    SelfTradePreventionInstruction::Enum
    selfTradePreventionInstruction() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        return enumeration<SelfTradePreventionInstruction>(offset);
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ThisType&
    setSelfTradePreventionInstruction(
        SelfTradePreventionInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        setEnumeration<SelfTradePreventionInstruction>(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    OrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        return enumeration<OrdType>(offset);
    }

    /// Order type.
    ThisType& setOrdType(OrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setEnumeration<OrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    TimeInForce::Enum timeInForce() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        return enumeration<TimeInForce>(offset);
    }

    /// Specifies how long the order remains in effect.
    ThisType& setTimeInForce(TimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setEnumeration<TimeInForce>(offset, value);
        return *this;
    }

    /// Indicates additional order instruction.
    ONIXS_B3_BOE_NODISCARD
    bool
    routingInstruction(
        RoutingInstruction::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        return enumeration<RoutingInstruction>(value, offset, NullUint8EnumEncoding());
    }

    /// Indicates additional order instruction.
    ThisType&
    setRoutingInstruction(
        RoutingInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setEnumeration<RoutingInstruction>(offset, value);
        return *this;
    }

    ThisType& setRoutingInstructionToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ONIXS_B3_BOE_NODISCARD
    bool stopPx(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        return decimal(value, offset, NullPriceOptional());
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ThisType& setStopPx(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStopPxToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Minimum quantity of an order to be executed.
    ONIXS_B3_BOE_NODISCARD
    bool minQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Minimum quantity of an order to be executed.
    ThisType& setMinQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMinQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ONIXS_B3_BOE_NODISCARD
    bool maxFloor(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ThisType& setMaxFloor(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMaxFloorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    bool executingTrader(StrRef& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(value, offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    ThisType& setExecutingTraderToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, StrRef());
        return *this;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ONIXS_B3_BOE_NODISCARD
    bool expireDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 105;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ThisType& setExpireDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 105;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setExpireDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 105;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Identifies the custodian.
    ONIXS_B3_BOE_NODISCARD
    bool custodianInfo(CustodianInfo& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 107;

        return ordinary(value, offset, NullCustodianInfo());
    }

    /// Identifies the custodian.
    ThisType& setCustodianInfo(CustodianInfo value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 107;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setCustodianInfoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 107;

        setOrdinary(offset, NullCustodianInfo());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 119;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 119;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 119;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Client-assigned identification of a strategy.
    ONIXS_B3_BOE_NODISCARD
    bool
    strategyId(
        StrategyIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 127;

        return ordinary(value, offset, NullStrategyIDOptional());
    }

    /// Client-assigned identification of a strategy.
    ThisType& setStrategyId(StrategyIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 127;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStrategyIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 127;

        setOrdinary(offset, NullStrategyIDOptional());
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 131;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 131;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 131;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 135
                : 131;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setOrdTagIdToNull();
        setAccountToNull();
        setRoutingInstructionToNull();
        setPriceToNull();
        setStopPxToNull();
        setMinQtyToNull();
        setMaxFloorToNull();
        setExecutingTraderToNull();
        setExpireDateToNull();
        setCustodianInfoToNull();
        setInvestorIdToNull();
        setStrategyIdToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "NewOrderSingle102";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("NewOrderSingle102");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const NewOrderSingle102& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const NewOrderSingle102& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// Sent by client system to replace an existing order.
ONIXS_B3_BOE_LTWT_STRUCT
OrderCancelReplaceRequest104
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef OrderCancelReplaceRequest104 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 104 };

    /// Initializes a blank instance.
    OrderCancelReplaceRequest104() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    OrderCancelReplaceRequest104(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    OrderCancelReplaceRequest104(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    OrderCancelReplaceRequest104(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    OrderCancelReplaceRequest104(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    OrderCancelReplaceRequest104(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = OrderCancelReplaceRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::OrderCancelReplaceRequest;
    }

    /// Message type = OrderCancelReplaceRequest.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum mmProtectionReset() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<Boolean>(offset);
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ThisType& setMmProtectionReset(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ONIXS_B3_BOE_NODISCARD
    SelfTradePreventionInstruction::Enum
    selfTradePreventionInstruction() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        return enumeration<SelfTradePreventionInstruction>(offset);
    }

    /// Indicates which order should be cancelled due to Self-
    /// Trade Prevention.
    ThisType&
    setSelfTradePreventionInstruction(
        SelfTradePreventionInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        setEnumeration<SelfTradePreventionInstruction>(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    OrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        return enumeration<OrdType>(offset);
    }

    /// Order type.
    ThisType& setOrdType(OrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setEnumeration<OrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    bool timeInForce(TimeInForce::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        return enumeration<TimeInForce>(value, offset, NullChar());
    }

    /// Specifies how long the order remains in effect.
    ThisType& setTimeInForce(TimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setEnumeration<TimeInForce>(offset, value);
        return *this;
    }

    ThisType& setTimeInForceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Indicates additional order instruction.
    ONIXS_B3_BOE_NODISCARD
    bool
    routingInstruction(
        RoutingInstruction::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        return enumeration<RoutingInstruction>(value, offset, NullUint8EnumEncoding());
    }

    /// Indicates additional order instruction.
    ThisType&
    setRoutingInstruction(
        RoutingInstruction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setEnumeration<RoutingInstruction>(offset, value);
        return *this;
    }

    ThisType& setRoutingInstructionToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    bool orderId(OrderIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        return ordinary(value, offset, NullOrderIDOptional());
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrderIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, NullOrderIDOptional());
        return *this;
    }

    /// ClOrdID which should be replaced.
    ONIXS_B3_BOE_NODISCARD
    bool origClOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// ClOrdID which should be replaced.
    ThisType& setOrigClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ONIXS_B3_BOE_NODISCARD
    bool stopPx(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        return decimal(value, offset, NullPriceOptional());
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ThisType& setStopPx(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStopPxToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Minimum quantity of an order to be executed.
    ONIXS_B3_BOE_NODISCARD
    bool minQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Minimum quantity of an order to be executed.
    ThisType& setMinQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMinQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ONIXS_B3_BOE_NODISCARD
    bool maxFloor(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ThisType& setMaxFloor(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMaxFloorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    bool executingTrader(StrRef& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(value, offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    ThisType& setExecutingTraderToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, StrRef());
        return *this;
    }

    /// Type of account associated with an order.
    ONIXS_B3_BOE_NODISCARD
    bool accountType(AccountType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 121;

        return enumeration<AccountType>(value, offset, NullUint8EnumEncoding());
    }

    /// Type of account associated with an order.
    ThisType& setAccountType(AccountType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 121;

        setEnumeration<AccountType>(offset, value);
        return *this;
    }

    ThisType& setAccountTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 121;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ONIXS_B3_BOE_NODISCARD
    bool expireDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 122;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ThisType& setExpireDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 122;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setExpireDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 122;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Identifies the custodian.
    ONIXS_B3_BOE_NODISCARD
    bool custodianInfo(CustodianInfo& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 124;

        return ordinary(value, offset, NullCustodianInfo());
    }

    /// Identifies the custodian.
    ThisType& setCustodianInfo(CustodianInfo value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 124;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setCustodianInfoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 124;

        setOrdinary(offset, NullCustodianInfo());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Client-assigned identification of a strategy.
    ONIXS_B3_BOE_NODISCARD
    bool
    strategyId(
        StrategyIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        return ordinary(value, offset, NullStrategyIDOptional());
    }

    /// Client-assigned identification of a strategy.
    ThisType& setStrategyId(StrategyIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStrategyIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, NullStrategyIDOptional());
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 148;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 148;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 148;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 152
                : 148;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setOrdTagIdToNull();
        setAccountToNull();
        setTimeInForceToNull();
        setRoutingInstructionToNull();
        setPriceToNull();
        setOrderIdToNull();
        setOrigClOrdIdToNull();
        setStopPxToNull();
        setMinQtyToNull();
        setMaxFloorToNull();
        setExecutingTraderToNull();
        setAccountTypeToNull();
        setExpireDateToNull();
        setCustodianInfoToNull();
        setInvestorIdToNull();
        setStrategyIdToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "OrderCancelReplaceRequest104";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "OrderCancelReplaceRequest104");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const OrderCancelReplaceRequest104& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const OrderCancelReplaceRequest104& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// OrderCancelRequest message submits a deletion of an existing order by referencing the original client order id.
ONIXS_B3_BOE_LTWT_STRUCT
OrderCancelRequest105
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef OrderCancelRequest105 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 105 };

    /// Initializes a blank instance.
    OrderCancelRequest105() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    OrderCancelRequest105(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    OrderCancelRequest105(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    OrderCancelRequest105(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    OrderCancelRequest105(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    OrderCancelRequest105(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = OrderCancelRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::OrderCancelRequest;
    }

    /// Message type = OrderCancelRequest.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    bool orderId(OrderIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullOrderIDOptional());
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrderIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, NullOrderIDOptional());
        return *this;
    }

    /// ClOrdID which should be cancelled.
    ONIXS_B3_BOE_NODISCARD
    bool origClOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// ClOrdID which should be cancelled.
    ThisType& setOrigClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Used to communicate a reason for a solicited cancel.
    ONIXS_B3_BOE_NODISCARD
    bool
    execRestatementReason(
        ExecRestatementReasonValidForSingleCancel::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 53;

        return enumeration<ExecRestatementReasonValidForSingleCancel>(value, offset, NullUint8EnumEncoding());
    }

    /// Used to communicate a reason for a solicited cancel.
    ThisType&
    setExecRestatementReason(
        ExecRestatementReasonValidForSingleCancel::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 53;

        setEnumeration<ExecRestatementReasonValidForSingleCancel>(offset, value);
        return *this;
    }

    ThisType& setExecRestatementReasonToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 53;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 66;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 66;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    bool executingTrader(StrRef& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 71;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(value, offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 71;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    ThisType& setExecutingTraderToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 71;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, StrRef());
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            76;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setOrderIdToNull();
        setOrigClOrdIdToNull();
        setExecRestatementReasonToNull();
        setExecutingTraderToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "OrderCancelRequest105";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("OrderCancelRequest105");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const OrderCancelRequest105& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const OrderCancelRequest105& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// The NewOrderCross message submits a Cross on Order Entry gateway, a two-sided order submitted by a single party/broker at the same price and quantity.
ONIXS_B3_BOE_LTWT_STRUCT
NewOrderCross106
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef NewOrderCross106 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 106 };

    /// Repeating group dimensions.
    /// Entry of SidesEntry repeating group.
    ONIXS_B3_BOE_LTWT_STRUCT
    SidesEntry : SbeGroupEntry
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

        /// This type alias.
        typedef SidesEntry ThisType;

        /// Initializes instance of given
        /// version over given memory block.
        SidesEntry(
            void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Reset all variable-length fields if any.
        ThisType& resetVariableFields()
            ONIXS_B3_BOE_NOTHROW
        {
            return *this;
        }

        /// Reset all variable-length and optional fields if any.
        ThisType& reset()
            ONIXS_B3_BOE_NOTHROW
        {
            setAccountToNull();
            setEnteringFirmToNull();

            if (version() >= 5)
            {
                setTradingSubAccountToNull();
            }

            resetVariableFields();
            return *this;
        }

        /// Side of order.
        ONIXS_B3_BOE_NODISCARD
        Side::Enum side() const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return enumeration<Side>(offset);
        }

        /// Side of order.
        ThisType& setSide(Side::Enum value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            setEnumeration<Side>(offset, value);
            return *this;
        }

        /// Account mnemonic of the order.
        ONIXS_B3_BOE_NODISCARD
        bool account(AccountOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 2;

            return ordinary(value, offset, NullAccountOptional());
        }

        /// Account mnemonic of the order.
        ThisType& setAccount(AccountOptional value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 2;

            setOrdinary(offset, value);
            return *this;
        }

        ThisType& setAccountToNull()
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 2;

            setOrdinary(offset, NullAccountOptional());
            return *this;
        }

        /// Identifies the broker firm that will enter orders.
        ONIXS_B3_BOE_NODISCARD
        bool enteringFirm(FirmOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 6;

            return ordinary(value, offset, NullFirmOptional());
        }

        /// Identifies the broker firm that will enter orders.
        ThisType& setEnteringFirm(FirmOptional value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 6;

            setOrdinary(offset, value);
            return *this;
        }

        ThisType& setEnteringFirmToNull()
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 6;

            setOrdinary(offset, NullFirmOptional());
            return *this;
        }

        /// Unique identifier of the order as assigned by the market
        /// participant.
        ONIXS_B3_BOE_NODISCARD
        ClOrdID clOrdId() const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 10;

            return ordinary<ClOrdID>(offset);
        }

        /// Unique identifier of the order as assigned by the market
        /// participant.
        ThisType& setClOrdId(ClOrdID value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 10;

            setOrdinary(offset, value);
            return *this;
        }

        /// Account used for associating risk limits (when defined).
        ONIXS_B3_BOE_NODISCARD
        bool tradingSubAccount(AccountOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            return ordinary(value, offset, NullAccountOptional(), since);
        }

        /// Account used for associating risk limits (when defined).
        ThisType& setTradingSubAccount(AccountOptional value)
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            setOrdinary(offset, value, since);
            return *this;
        }

        ThisType& setTradingSubAccountToNull()
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            setOrdinary(offset, NullAccountOptional(), since);
            return *this;
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static
        BlockLength
        blockLength(
            ONIXS_B3_BOE_UNUSED SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                minimalBlockLength(version);
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static BlockLength minimalBlockLength(SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                (version >= 5)
                    ? 22
                    : 18;
        }

        /// Entity class name.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_NODISCARD
        ONIXS_B3_BOE_CONSTEXPR
        static const Char* className()
        {
            return "NewOrderCross106.SidesEntry";
        }
    };

    /// Repeating group containing SidesEntry entries.
    typedef
    SbeGroup<SidesEntry, GroupSizeEncoding, MessageSize>
    Sides;

    /// Initializes a blank instance.
    NewOrderCross106() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    NewOrderCross106(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    NewOrderCross106(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    NewOrderCross106(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    NewOrderCross106(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    NewOrderCross106(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = NewOrderCross.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::NewOrderCross;
    }

    /// Message type = NewOrderCross.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ONIXS_B3_BOE_NODISCARD
    CrossID crossId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<CrossID>(offset);
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ThisType& setCrossId(CrossID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 38;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 38;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    bool executingTrader(StrRef& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 43;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(value, offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 43;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    ThisType& setExecutingTraderToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 43;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, StrRef());
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    Price price() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return decimal<Price>(offset);
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(Price value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    /// Indicates cross order purpose.
    ONIXS_B3_BOE_NODISCARD
    bool
    crossedIndicator(
        CrossedIndicator::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return enumeration<CrossedIndicator>(value, offset, NullUint16EnumEncoding());
    }

    /// Indicates cross order purpose.
    ThisType&
    setCrossedIndicator(
        CrossedIndicator::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setEnumeration<CrossedIndicator>(offset, value);
        return *this;
    }

    ThisType& setCrossedIndicatorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, NullUint16EnumEncoding());
        return *this;
    }

    /// Type of cross being submitted to a market. Null value
    /// indicates all or none cross.
    ONIXS_B3_BOE_NODISCARD
    bool crossType(CrossType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 74;

        return enumeration<CrossType>(value, offset, NullUint8EnumEncoding());
    }

    /// Type of cross being submitted to a market. Null value
    /// indicates all or none cross.
    ThisType& setCrossType(CrossType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 74;

        setEnumeration<CrossType>(offset, value);
        return *this;
    }

    ThisType& setCrossTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 74;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Indicates if one side or the other of a cross order should
    /// be prioritized. Null value indicates none is prioritized.
    ONIXS_B3_BOE_NODISCARD
    bool
    crossPrioritization(
        CrossPrioritization::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 75;

        return enumeration<CrossPrioritization>(value, offset, NullUInt8());
    }

    /// Indicates if one side or the other of a cross order should
    /// be prioritized. Null value indicates none is prioritized.
    ThisType&
    setCrossPrioritization(
        CrossPrioritization::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 75;

        setEnumeration<CrossPrioritization>(offset, value);
        return *this;
    }

    ThisType& setCrossPrioritizationToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 75;

        setOrdinary(offset, NullUInt8());
        return *this;
    }

    /// Maximum sweep quantity.
    ONIXS_B3_BOE_NODISCARD
    bool maxSweepQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum sweep quantity.
    ThisType& setMaxSweepQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMaxSweepQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// \return instance of Sides repeating group.
    ONIXS_B3_BOE_NODISCARD
    Sides sides() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Sides>(SidesAccess(), *this);
    }

    /// \return instance of Sides repeating group.
    ONIXS_B3_BOE_NODISCARD
    Sides sides()
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Sides>(SidesAccess(), *this);
    }

    /// Setup repeating group with the given number of entries.
    /// Sets all optional fields of the group entries to null.
    /// \return noSides(552) repeating group.
    Sides sides(Sides::Size length)
    {
        return constructGroup<Sides>(
            SidesAccess(),
            length,
            *this);
    }

    /// Setup repeating group with the given number of entries.
    /// \return noSides(552) repeating group.
    Sides
    sides(
        Sides::Size length,
        NoFieldsInit)
    {
        return setupGroup<Sides>(
            SidesAccess(),
            length,
            *this);
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            84;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size) + static_cast<MessageSize>(Sides::EmptySize);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setSidesToNull();
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setExecutingTraderToNull();
        setCrossedIndicatorToNull();
        setCrossTypeToNull();
        setCrossPrioritizationToNull();
        setMaxSweepQtyToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "NewOrderCross106";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("NewOrderCross106");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkVariableLengthFields<Sides>().
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct SidesAccess
    {
        Sides
        operator()(
            const NewOrderCross106& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    head<Sides>();
        }
    };

    /// Reset an instance of the repeating group.
    /// All the following data will be invalidated.
    void setSidesToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        resetGroup<Sides>(SidesAccess(), *this);
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const NewOrderCross106& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Sides>().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const NewOrderCross106& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Sides>().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// Execution Report - New message is sent in response to a NewOrderSingle or SimpleNewOrder messages, or also from a restated iceberg order.
ONIXS_B3_BOE_LTWT_STRUCT
ExecutionReportNew200
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef ExecutionReportNew200 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 200 };

    /// Initializes a blank instance.
    ExecutionReportNew200() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    ExecutionReportNew200(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    ExecutionReportNew200(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    ExecutionReportNew200(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionReportNew200(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionReportNew200(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// MessageType.ExecutionReport_New.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::ExecutionReportNew;
    }

    /// MessageType.ExecutionReport_New.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Identifies current status of order.
    ONIXS_B3_BOE_NODISCARD
    OrdStatus::Enum ordStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<OrdStatus>(offset);
    }

    /// Identifies current status of order.
    ThisType& setOrdStatus(OrdStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<OrdStatus>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ONIXS_B3_BOE_NODISCARD
    OrderID secondaryOrderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<OrderID>(offset);
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ThisType& setSecondaryOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    OrderID orderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary<OrderID>(offset);
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ONIXS_B3_BOE_NODISCARD
    ExecID execId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary<ExecID>(offset);
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ThisType& setExecId(ExecID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of receipt of related inbound message in the market
    /// segment path. For aggressor STOP orders, it indicates the
    /// moment when the order is triggered.
    ONIXS_B3_BOE_NODISCARD
    bool
    marketSegmentReceivedTime(
        UTCTimestampNanosOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return ordinary(value, offset, NullUTCTimestampNanosOptional());
    }

    /// Time of receipt of related inbound message in the market
    /// segment path. For aggressor STOP orders, it indicates the
    /// moment when the order is triggered.
    ThisType&
    setMarketSegmentReceivedTime(
        UTCTimestampNanosOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMarketSegmentReceivedTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, NullUTCTimestampNanosOptional());
        return *this;
    }

    /// Conditionally returned on execution reports for Market and
    /// Stop Protect orders. This contains the final protection
    /// price limit at which any unmatched quantity will rest on
    /// the book.
    ONIXS_B3_BOE_NODISCARD
    bool protectionPrice(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Conditionally returned on execution reports for Market and
    /// Stop Protect orders. This contains the final protection
    /// price limit at which any unmatched quantity will rest on
    /// the book.
    ThisType& setProtectionPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setProtectionPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ONIXS_B3_BOE_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ThisType& setTradeDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    /// Indicates if an order has been triggered and is available
    /// for trading. Used with Stop (Limit, with protection)
    /// orders and the At the Close validity.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum workingIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 90;

        return enumeration<Boolean>(offset);
    }

    /// Indicates if an order has been triggered and is available
    /// for trading. Used with Stop (Limit, with protection)
    /// orders and the At the Close validity.
    ThisType& setWorkingIndicator(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 90;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Used to indicate what an Execution Report represents.
    /// Default value is 1 (Single Security).
    ONIXS_B3_BOE_NODISCARD
    bool
    multiLegReportingType(
        MultiLegReportingType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 91;

        return enumeration<MultiLegReportingType>(value, offset, NullChar());
    }

    /// Used to indicate what an Execution Report represents.
    /// Default value is 1 (Single Security).
    ThisType&
    setMultiLegReportingType(
        MultiLegReportingType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 91;

        setEnumeration<MultiLegReportingType>(offset, value);
        return *this;
    }

    ThisType& setMultiLegReportingTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 91;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    OrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        return enumeration<OrdType>(offset);
    }

    /// Order type.
    ThisType& setOrdType(OrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 92;

        setEnumeration<OrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    TimeInForce::Enum timeInForce() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 93;

        return enumeration<TimeInForce>(offset);
    }

    /// Specifies how long the order remains in effect.
    ThisType& setTimeInForce(TimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 93;

        setEnumeration<TimeInForce>(offset, value);
        return *this;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ONIXS_B3_BOE_NODISCARD
    bool expireDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 94;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ThisType& setExpireDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 94;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setExpireDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 94;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ONIXS_B3_BOE_NODISCARD
    bool stopPx(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        return decimal(value, offset, NullPriceOptional());
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ThisType& setStopPx(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStopPxToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Minimum quantity of an order to be executed.
    ONIXS_B3_BOE_NODISCARD
    bool minQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Minimum quantity of an order to be executed.
    ThisType& setMinQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMinQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ONIXS_B3_BOE_NODISCARD
    bool maxFloor(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ThisType& setMaxFloor(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMaxFloorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ONIXS_B3_BOE_NODISCARD
    bool crossId(CrossIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        return ordinary(value, offset, NullCrossIDOptional());
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ThisType& setCrossId(CrossIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setCrossIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, NullCrossIDOptional());
        return *this;
    }

    /// Time of receipt of related inbound message in the gateway.
    ONIXS_B3_BOE_NODISCARD
    bool
    receivedTime(
        UTCTimestampNanosOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        return ordinary(value, offset, NullUTCTimestampNanosOptional());
    }

    /// Time of receipt of related inbound message in the gateway.
    ThisType&
    setReceivedTime(
        UTCTimestampNanosOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setReceivedTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, NullUTCTimestampNanosOptional());
        return *this;
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Type of cross being submitted to a market. Null value
    /// indicates report is not related to cross.
    ONIXS_B3_BOE_NODISCARD
    bool crossType(CrossType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 164;

        return enumeration<CrossType>(value, offset, NullUint8EnumEncoding());
    }

    /// Type of cross being submitted to a market. Null value
    /// indicates report is not related to cross.
    ThisType& setCrossType(CrossType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 164;

        setEnumeration<CrossType>(offset, value);
        return *this;
    }

    ThisType& setCrossTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 164;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Indicates if one side or the other of a cross order should
    /// be prioritized.  Null value indicates report is not
    /// related to cross.
    ONIXS_B3_BOE_NODISCARD
    bool
    crossPrioritization(
        CrossPrioritization::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 165;

        return enumeration<CrossPrioritization>(value, offset, NullUInt8());
    }

    /// Indicates if one side or the other of a cross order should
    /// be prioritized.  Null value indicates report is not
    /// related to cross.
    ThisType&
    setCrossPrioritization(
        CrossPrioritization::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 165;

        setEnumeration<CrossPrioritization>(offset, value);
        return *this;
    }

    ThisType& setCrossPrioritizationToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 165;

        setOrdinary(offset, NullUInt8());
        return *this;
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ONIXS_B3_BOE_NODISCARD
    bool mmProtectionReset(Boolean::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 166;

        return enumeration<Boolean>(value, offset, NullUInt8());
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ThisType& setMmProtectionReset(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 166;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    ThisType& setMmProtectionResetToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 166;

        setOrdinary(offset, NullUInt8());
        return *this;
    }

    /// Client-assigned identification of a strategy.
    ONIXS_B3_BOE_NODISCARD
    bool
    strategyId(
        StrategyIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 168;

        return ordinary(value, offset, NullStrategyIDOptional());
    }

    /// Client-assigned identification of a strategy.
    ThisType& setStrategyId(StrategyIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 168;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStrategyIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 168;

        setOrdinary(offset, NullStrategyIDOptional());
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 172;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 172;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 172;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 176
                : (version >= 3)
                    ? 172
                    : 152;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setAccountToNull();
        setMarketSegmentReceivedTimeToNull();
        setProtectionPriceToNull();
        setMultiLegReportingTypeToNull();
        setExpireDateToNull();
        setPriceToNull();
        setStopPxToNull();
        setMinQtyToNull();
        setMaxFloorToNull();
        setCrossIdToNull();
        setReceivedTimeToNull();
        setOrdTagIdToNull();
        setInvestorIdToNull();
        setCrossTypeToNull();
        setCrossPrioritizationToNull();
        setMmProtectionResetToNull();
        setStrategyIdToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionReportNew200";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("ExecutionReportNew200");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const ExecutionReportNew200& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const ExecutionReportNew200& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// Execution Report - Modify message is sent in response to OrderCancelReplaceRequest or SimpleModifyOrder messages.
ONIXS_B3_BOE_LTWT_STRUCT
ExecutionReportModify201
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef ExecutionReportModify201 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 201 };

    /// Initializes a blank instance.
    ExecutionReportModify201() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    ExecutionReportModify201(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    ExecutionReportModify201(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    ExecutionReportModify201(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionReportModify201(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionReportModify201(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// MessageType.ExecutionReport_Modify.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::ExecutionReportModify;
    }

    /// MessageType.ExecutionReport_Modify.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Identifies current status of order.
    ONIXS_B3_BOE_NODISCARD
    OrdStatus::Enum ordStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<OrdStatus>(offset);
    }

    /// Identifies current status of order.
    ThisType& setOrdStatus(OrdStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<OrdStatus>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ONIXS_B3_BOE_NODISCARD
    OrderID secondaryOrderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<OrderID>(offset);
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ThisType& setSecondaryOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Amount of shares open for further execution, or
    /// unexecuted.
    ONIXS_B3_BOE_NODISCARD
    Quantity leavesQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary<Quantity>(offset);
    }

    /// Amount of shares open for further execution, or
    /// unexecuted.
    ThisType& setLeavesQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ONIXS_B3_BOE_NODISCARD
    ExecID execId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary<ExecID>(offset);
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ThisType& setExecId(ExecID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    /// Total number of shares or contracts filled.
    ONIXS_B3_BOE_NODISCARD
    Quantity cumQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return ordinary<Quantity>(offset);
    }

    /// Total number of shares or contracts filled.
    ThisType& setCumQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of receipt of related inbound message in the market
    /// segment path. For aggressor STOP orders, it indicates the
    /// moment when the order is triggered.
    ONIXS_B3_BOE_NODISCARD
    bool
    marketSegmentReceivedTime(
        UTCTimestampNanosOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        return ordinary(value, offset, NullUTCTimestampNanosOptional());
    }

    /// Time of receipt of related inbound message in the market
    /// segment path. For aggressor STOP orders, it indicates the
    /// moment when the order is triggered.
    ThisType&
    setMarketSegmentReceivedTime(
        UTCTimestampNanosOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMarketSegmentReceivedTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, NullUTCTimestampNanosOptional());
        return *this;
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    OrderID orderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        return ordinary<OrderID>(offset);
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, value);
        return *this;
    }

    /// Value of origClOrdID field informed from the related
    /// request message.
    ONIXS_B3_BOE_NODISCARD
    bool origClOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// Value of origClOrdID field informed from the related
    /// request message.
    ThisType& setOrigClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// Conditionally returned on execution reports for Market and
    /// Stop Protect orders. This contains the final protection
    /// price limit at which any unmatched quantity will rest on
    /// the book.
    ONIXS_B3_BOE_NODISCARD
    bool protectionPrice(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Conditionally returned on execution reports for Market and
    /// Stop Protect orders. This contains the final protection
    /// price limit at which any unmatched quantity will rest on
    /// the book.
    ThisType& setProtectionPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setProtectionPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ONIXS_B3_BOE_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ThisType& setTradeDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    /// Indicates if an order has been triggered and is available
    /// for trading. Used with Stop (Limit, with protection)
    /// orders and the At the Close validity.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum workingIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 114;

        return enumeration<Boolean>(offset);
    }

    /// Indicates if an order has been triggered and is available
    /// for trading. Used with Stop (Limit, with protection)
    /// orders and the At the Close validity.
    ThisType& setWorkingIndicator(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 114;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Used to indicate what an Execution Report represents.
    /// Default value is 1 (Single Security).
    ONIXS_B3_BOE_NODISCARD
    bool
    multiLegReportingType(
        MultiLegReportingType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 115;

        return enumeration<MultiLegReportingType>(value, offset, NullChar());
    }

    /// Used to indicate what an Execution Report represents.
    /// Default value is 1 (Single Security).
    ThisType&
    setMultiLegReportingType(
        MultiLegReportingType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 115;

        setEnumeration<MultiLegReportingType>(offset, value);
        return *this;
    }

    ThisType& setMultiLegReportingTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 115;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    OrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        return enumeration<OrdType>(offset);
    }

    /// Order type.
    ThisType& setOrdType(OrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        setEnumeration<OrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    TimeInForce::Enum timeInForce() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 117;

        return enumeration<TimeInForce>(offset);
    }

    /// Specifies how long the order remains in effect.
    ThisType& setTimeInForce(TimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 117;

        setEnumeration<TimeInForce>(offset, value);
        return *this;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ONIXS_B3_BOE_NODISCARD
    bool expireDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 118;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ThisType& setExpireDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 118;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setExpireDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 118;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ONIXS_B3_BOE_NODISCARD
    bool stopPx(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        return decimal(value, offset, NullPriceOptional());
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ThisType& setStopPx(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStopPxToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Minimum quantity of an order to be executed.
    ONIXS_B3_BOE_NODISCARD
    bool minQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Minimum quantity of an order to be executed.
    ThisType& setMinQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMinQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ONIXS_B3_BOE_NODISCARD
    bool maxFloor(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 152;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ThisType& setMaxFloor(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 152;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMaxFloorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 152;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Time of receipt of related inbound message in the gateway.
    ONIXS_B3_BOE_NODISCARD
    bool
    receivedTime(
        UTCTimestampNanosOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 160;

        return ordinary(value, offset, NullUTCTimestampNanosOptional());
    }

    /// Time of receipt of related inbound message in the gateway.
    ThisType&
    setReceivedTime(
        UTCTimestampNanosOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 160;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setReceivedTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 160;

        setOrdinary(offset, NullUTCTimestampNanosOptional());
        return *this;
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 171;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 171;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 171;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 172;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 172;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 172;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ONIXS_B3_BOE_NODISCARD
    bool mmProtectionReset(Boolean::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 180;

        return enumeration<Boolean>(value, offset, NullUInt8());
    }

    /// Resets Market Protections. When Market Protections are
    /// triggered, the Exchange will not accept new orders for
    /// that product group without tag MMProtectionReset: True =
    /// Reset Market Maker Protection; False = Do nothing related
    /// to Market Maker Protection.
    ThisType& setMmProtectionReset(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 180;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    ThisType& setMmProtectionResetToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 180;

        setOrdinary(offset, NullUInt8());
        return *this;
    }

    /// Client-assigned identification of a strategy.
    ONIXS_B3_BOE_NODISCARD
    bool
    strategyId(
        StrategyIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 182;

        return ordinary(value, offset, NullStrategyIDOptional());
    }

    /// Client-assigned identification of a strategy.
    ThisType& setStrategyId(StrategyIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 182;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStrategyIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 182;

        setOrdinary(offset, NullStrategyIDOptional());
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 186;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 186;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 186;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 190
                : (version >= 3)
                    ? 186
                    : 168;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setAccountToNull();
        setMarketSegmentReceivedTimeToNull();
        setOrigClOrdIdToNull();
        setProtectionPriceToNull();
        setMultiLegReportingTypeToNull();
        setExpireDateToNull();
        setPriceToNull();
        setStopPxToNull();
        setMinQtyToNull();
        setMaxFloorToNull();
        setReceivedTimeToNull();
        setOrdTagIdToNull();
        setInvestorIdToNull();
        setMmProtectionResetToNull();
        setStrategyIdToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionReportModify201";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "ExecutionReportModify201");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const ExecutionReportModify201& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const ExecutionReportModify201& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// ExecutionReport - Cancel message is sent in response to Order Cancel Request as well as to report unsolicited cancellation of orders due to: Market Operations or Cancel On Disconnect mechanism.
ONIXS_B3_BOE_LTWT_STRUCT
ExecutionReportCancel202
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef ExecutionReportCancel202 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 202 };

    /// Initializes a blank instance.
    ExecutionReportCancel202() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    ExecutionReportCancel202(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    ExecutionReportCancel202(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    ExecutionReportCancel202(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionReportCancel202(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionReportCancel202(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// MessageType.ExecutionReport_Cancel.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::ExecutionReportCancel;
    }

    /// MessageType.ExecutionReport_Cancel.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Identifies current status of order.
    ONIXS_B3_BOE_NODISCARD
    OrdStatus::Enum ordStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<OrdStatus>(offset);
    }

    /// Identifies current status of order.
    ThisType& setOrdStatus(OrdStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<OrdStatus>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ONIXS_B3_BOE_NODISCARD
    OrderID secondaryOrderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<OrderID>(offset);
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ThisType& setSecondaryOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Total number of shares or contracts filled.
    ONIXS_B3_BOE_NODISCARD
    Quantity cumQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary<Quantity>(offset);
    }

    /// Total number of shares or contracts filled.
    ThisType& setCumQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ONIXS_B3_BOE_NODISCARD
    ExecID execId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary<ExecID>(offset);
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ThisType& setExecId(ExecID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of receipt of related inbound message in the market
    /// segment path. For aggressor STOP orders, it indicates the
    /// moment when the order is triggered.
    ONIXS_B3_BOE_NODISCARD
    bool
    marketSegmentReceivedTime(
        UTCTimestampNanosOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return ordinary(value, offset, NullUTCTimestampNanosOptional());
    }

    /// Time of receipt of related inbound message in the market
    /// segment path. For aggressor STOP orders, it indicates the
    /// moment when the order is triggered.
    ThisType&
    setMarketSegmentReceivedTime(
        UTCTimestampNanosOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMarketSegmentReceivedTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, NullUTCTimestampNanosOptional());
        return *this;
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    OrderID orderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        return ordinary<OrderID>(offset);
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, value);
        return *this;
    }

    /// Value of origClOrdID field informed from the related
    /// request message.
    ONIXS_B3_BOE_NODISCARD
    bool origClOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// Value of origClOrdID field informed from the related
    /// request message.
    ThisType& setOrigClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ONIXS_B3_BOE_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ThisType& setTradeDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    /// Indicates if an order has been triggered and is available
    /// for trading. Used with Stop (Limit, with protection)
    /// orders and the At the Close validity.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum workingIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;

        return enumeration<Boolean>(offset);
    }

    /// Indicates if an order has been triggered and is available
    /// for trading. Used with Stop (Limit, with protection)
    /// orders and the At the Close validity.
    ThisType& setWorkingIndicator(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Indicates reason of cancelation, if available.
    ONIXS_B3_BOE_NODISCARD
    bool
    execRestatementReason(
        ExecRestatementReason::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 99;

        return enumeration<ExecRestatementReason>(value, offset, NullUint8EnumEncoding());
    }

    /// Indicates reason of cancelation, if available.
    ThisType&
    setExecRestatementReason(
        ExecRestatementReason::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 99;

        setEnumeration<ExecRestatementReason>(offset, value);
        return *this;
    }

    ThisType& setExecRestatementReasonToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 99;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Unique ID of Order Mass Action Report as assigned by the
    /// matching engine.
    ONIXS_B3_BOE_NODISCARD
    bool
    massActionReportId(
        MassActionReportIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        return ordinary(value, offset, NullMassActionReportIDOptional());
    }

    /// Unique ID of Order Mass Action Report as assigned by the
    /// matching engine.
    ThisType&
    setMassActionReportId(
        MassActionReportIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMassActionReportIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, NullMassActionReportIDOptional());
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    OrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        return enumeration<OrdType>(offset);
    }

    /// Order type.
    ThisType& setOrdType(OrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        setEnumeration<OrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    TimeInForce::Enum timeInForce() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 113;

        return enumeration<TimeInForce>(offset);
    }

    /// Specifies how long the order remains in effect.
    ThisType& setTimeInForce(TimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 113;

        setEnumeration<TimeInForce>(offset, value);
        return *this;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ONIXS_B3_BOE_NODISCARD
    bool expireDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 114;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ThisType& setExpireDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 114;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setExpireDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 114;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 124;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 124;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 124;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ONIXS_B3_BOE_NODISCARD
    bool stopPx(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 132;

        return decimal(value, offset, NullPriceOptional());
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ThisType& setStopPx(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 132;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStopPxToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 132;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Minimum quantity of an order to be executed.
    ONIXS_B3_BOE_NODISCARD
    bool minQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 140;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Minimum quantity of an order to be executed.
    ThisType& setMinQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 140;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMinQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 140;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ONIXS_B3_BOE_NODISCARD
    bool maxFloor(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 148;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ThisType& setMaxFloor(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 148;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMaxFloorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 148;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Time of receipt of related inbound message in the gateway.
    ONIXS_B3_BOE_NODISCARD
    bool
    receivedTime(
        UTCTimestampNanosOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        return ordinary(value, offset, NullUTCTimestampNanosOptional());
    }

    /// Time of receipt of related inbound message in the gateway.
    ThisType&
    setReceivedTime(
        UTCTimestampNanosOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setReceivedTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        setOrdinary(offset, NullUTCTimestampNanosOptional());
        return *this;
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 167;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 167;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 167;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 168;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 168;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 168;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Client-assigned identification of a strategy.
    ONIXS_B3_BOE_NODISCARD
    bool
    strategyId(
        StrategyIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 176;

        return ordinary(value, offset, NullStrategyIDOptional());
    }

    /// Client-assigned identification of a strategy.
    ThisType& setStrategyId(StrategyIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 176;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStrategyIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 176;

        setOrdinary(offset, NullStrategyIDOptional());
        return *this;
    }

    /// Indicates the SessionID that requested the Cancel on
    /// behalf.
    ONIXS_B3_BOE_NODISCARD
    bool actionRequestedFromSessionId(SessionIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 180;

        return ordinary(value, offset, NullSessionIDOptional());
    }

    /// Indicates the SessionID that requested the Cancel on
    /// behalf.
    ThisType& setActionRequestedFromSessionId(SessionIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 180;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setActionRequestedFromSessionIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 180;

        setOrdinary(offset, NullSessionIDOptional());
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 3)
                ? 184
                : 164;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setAccountToNull();
        setMarketSegmentReceivedTimeToNull();
        setOrigClOrdIdToNull();
        setExecRestatementReasonToNull();
        setMassActionReportIdToNull();
        setExpireDateToNull();
        setPriceToNull();
        setStopPxToNull();
        setMinQtyToNull();
        setMaxFloorToNull();
        setReceivedTimeToNull();
        setOrdTagIdToNull();
        setInvestorIdToNull();
        setStrategyIdToNull();
        setActionRequestedFromSessionIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionReportCancel202";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "ExecutionReportCancel202");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const ExecutionReportCancel202& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const ExecutionReportCancel202& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// Execution Report – Trade/Trade Bust message is sent with order fills that were traded and processed on Matching Engine. Also, trade bust included on behalf of B3’s desk.
ONIXS_B3_BOE_LTWT_STRUCT
ExecutionReportTrade203
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef ExecutionReportTrade203 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 203 };

    /// Initializes a blank instance.
    ExecutionReportTrade203() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    ExecutionReportTrade203(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    ExecutionReportTrade203(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    ExecutionReportTrade203(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionReportTrade203(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionReportTrade203(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// MessageType.ExecutionReport_Trade.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::ExecutionReportTrade;
    }

    /// MessageType.ExecutionReport_Trade.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Identifies current status of order.
    ONIXS_B3_BOE_NODISCARD
    OrdStatus::Enum ordStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<OrdStatus>(offset);
    }

    /// Identifies current status of order.
    ThisType& setOrdStatus(OrdStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<OrdStatus>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    bool clOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ONIXS_B3_BOE_NODISCARD
    OrderID secondaryOrderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<OrderID>(offset);
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ThisType& setSecondaryOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Quantity of shares bought/sold on the last fill.
    ONIXS_B3_BOE_NODISCARD
    Quantity lastQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<Quantity>(offset);
    }

    /// Quantity of shares bought/sold on the last fill.
    ThisType& setLastQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price of last fill.
    ONIXS_B3_BOE_NODISCARD
    Price lastPx() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return decimal<Price>(offset);
    }

    /// Price of last fill.
    ThisType& setLastPx(Price value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ONIXS_B3_BOE_NODISCARD
    ExecID execId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return ordinary<ExecID>(offset);
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ThisType& setExecId(ExecID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, value);
        return *this;
    }

    /// Amount of shares open for further execution, or
    /// unexecuted.
    ONIXS_B3_BOE_NODISCARD
    Quantity leavesQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        return ordinary<Quantity>(offset);
    }

    /// Amount of shares open for further execution, or
    /// unexecuted.
    ThisType& setLeavesQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, value);
        return *this;
    }

    /// Total number of shares or contracts filled.
    ONIXS_B3_BOE_NODISCARD
    Quantity cumQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        return ordinary<Quantity>(offset);
    }

    /// Total number of shares or contracts filled.
    ThisType& setCumQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identify whether the order initiator is an aggressor or
    /// not in the trade.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum aggressorIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        return enumeration<Boolean>(offset);
    }

    /// Identify whether the order initiator is an aggressor or
    /// not in the trade.
    ThisType& setAggressorIndicator(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Describes the action that triggered this specific
    /// Execution Report - see the OrdStatus (39) tag for the
    /// current order status (e.g, Partially Filled).
    ONIXS_B3_BOE_NODISCARD
    ExecType::Enum execType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 97;

        return enumeration<ExecType>(offset);
    }

    /// Describes the action that triggered this specific
    /// Execution Report - see the OrdStatus (39) tag for the
    /// current order status (e.g, Partially Filled).
    ThisType& setExecType(ExecType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 97;

        setEnumeration<ExecType>(offset, value);
        return *this;
    }

    /// Reason why a trade occurred.
    ONIXS_B3_BOE_NODISCARD
    bool
    orderCategory(
        OrderCategory::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;

        return enumeration<OrderCategory>(value, offset, NullChar());
    }

    /// Reason why a trade occurred.
    ThisType&
    setOrderCategory(
        OrderCategory::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;

        setEnumeration<OrderCategory>(offset, value);
        return *this;
    }

    ThisType& setOrderCategoryToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Used to indicate what an Execution Report represents.
    /// Default value is 1 (Single Security).
    ONIXS_B3_BOE_NODISCARD
    bool
    multiLegReportingType(
        MultiLegReportingType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 99;

        return enumeration<MultiLegReportingType>(value, offset, NullChar());
    }

    /// Used to indicate what an Execution Report represents.
    /// Default value is 1 (Single Security).
    ThisType&
    setMultiLegReportingType(
        MultiLegReportingType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 99;

        setEnumeration<MultiLegReportingType>(offset, value);
        return *this;
    }

    ThisType& setMultiLegReportingTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 99;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    TradeID tradeId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;

        return ordinary<TradeID>(offset);
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ThisType& setTradeId(TradeID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the contra broker firm.
    ONIXS_B3_BOE_NODISCARD
    Firm contraBroker() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        return ordinary<Firm>(offset);
    }

    /// Identifies the contra broker firm.
    ThisType& setContraBroker(Firm value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    OrderID orderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        return ordinary<OrderID>(offset);
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        setOrdinary(offset, value);
        return *this;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ONIXS_B3_BOE_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ThisType& setTradeDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    /// Number of leg fill notice messages sent with spread
    /// summary.
    ONIXS_B3_BOE_NODISCARD
    bool totNoRelatedSym(TotNoRelatedSym& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 118;

        return ordinary(value, offset, NullTotNoRelatedSym());
    }

    /// Number of leg fill notice messages sent with spread
    /// summary.
    ThisType& setTotNoRelatedSym(TotNoRelatedSym value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 118;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setTotNoRelatedSymToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 118;

        setOrdinary(offset, NullTotNoRelatedSym());
        return *this;
    }

    /// Unique identifier present in all messages associated with
    /// a spread transaction. This value allows linking spread
    /// summary fill notice, leg fill notices, and leg trade
    /// cancellation execution report messages generated from a
    /// spread transaction.
    ONIXS_B3_BOE_NODISCARD
    bool secondaryExecId(ExecIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        return ordinary(value, offset, NullExecIDOptional());
    }

    /// Unique identifier present in all messages associated with
    /// a spread transaction. This value allows linking spread
    /// summary fill notice, leg fill notices, and leg trade
    /// cancellation execution report messages generated from a
    /// spread transaction.
    ThisType& setSecondaryExecId(ExecIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setSecondaryExecIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, NullExecIDOptional());
        return *this;
    }

    /// Optionally sent when reporting a trade bust. Contains the
    /// identifier of the busted trade.
    ONIXS_B3_BOE_NODISCARD
    bool execRefId(ExecIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        return ordinary(value, offset, NullExecIDOptional());
    }

    /// Optionally sent when reporting a trade bust. Contains the
    /// identifier of the busted trade.
    ThisType& setExecRefId(ExecIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setExecRefIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, NullExecIDOptional());
        return *this;
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ONIXS_B3_BOE_NODISCARD
    bool crossId(CrossIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        return ordinary(value, offset, NullCrossIDOptional());
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ThisType& setCrossId(CrossIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setCrossIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, NullCrossIDOptional());
        return *this;
    }

    /// Indicates cross order purpose.
    ONIXS_B3_BOE_NODISCARD
    bool
    crossedIndicator(
        CrossedIndicator::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        return enumeration<CrossedIndicator>(value, offset, NullUint16EnumEncoding());
    }

    /// Indicates cross order purpose.
    ThisType&
    setCrossedIndicator(
        CrossedIndicator::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setEnumeration<CrossedIndicator>(offset, value);
        return *this;
    }

    ThisType& setCrossedIndicatorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, NullUint16EnumEncoding());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 146;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 146;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifier for Trading Session.
    ONIXS_B3_BOE_NODISCARD
    bool
    tradingSessionId(
        TradingSessionID::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 154;

        return enumeration<TradingSessionID>(value, offset, NullUint8EnumEncoding());
    }

    /// Identifier for Trading Session.
    ThisType&
    setTradingSessionId(
        TradingSessionID::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 154;

        setEnumeration<TradingSessionID>(offset, value);
        return *this;
    }

    ThisType& setTradingSessionIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 154;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Identifier for the instrument group phase.
    ONIXS_B3_BOE_NODISCARD
    bool
    tradingSessionSubId(
        TradingSessionSubID::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;

        return enumeration<TradingSessionSubID>(value, offset, NullUint8EnumEncoding());
    }

    /// Identifier for the instrument group phase.
    ThisType&
    setTradingSessionSubId(
        TradingSessionSubID::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;

        setEnumeration<TradingSessionSubID>(offset, value);
        return *this;
    }

    ThisType& setTradingSessionSubIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Identifier for the instrument status.
    ONIXS_B3_BOE_NODISCARD
    bool
    securityTradingStatus(
        SecurityTradingStatus::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        return enumeration<SecurityTradingStatus>(value, offset, NullUint8EnumEncoding());
    }

    /// Identifier for the instrument status.
    ThisType&
    setSecurityTradingStatus(
        SecurityTradingStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        setEnumeration<SecurityTradingStatus>(offset, value);
        return *this;
    }

    ThisType& setSecurityTradingStatusToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 156;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Type of cross being submitted to a market. Null value
    /// indicates report is not related to cross.
    ONIXS_B3_BOE_NODISCARD
    bool crossType(CrossType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 157;

        return enumeration<CrossType>(value, offset, NullUint8EnumEncoding());
    }

    /// Type of cross being submitted to a market. Null value
    /// indicates report is not related to cross.
    ThisType& setCrossType(CrossType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 157;

        setEnumeration<CrossType>(offset, value);
        return *this;
    }

    ThisType& setCrossTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 157;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Indicates if one side or the other of a cross order should
    /// be prioritized.  Null value indicates report is not
    /// related to cross.
    ONIXS_B3_BOE_NODISCARD
    bool
    crossPrioritization(
        CrossPrioritization::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 158;

        return enumeration<CrossPrioritization>(value, offset, NullUInt8());
    }

    /// Indicates if one side or the other of a cross order should
    /// be prioritized.  Null value indicates report is not
    /// related to cross.
    ThisType&
    setCrossPrioritization(
        CrossPrioritization::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 158;

        setEnumeration<CrossPrioritization>(offset, value);
        return *this;
    }

    ThisType& setCrossPrioritizationToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 158;

        setOrdinary(offset, NullUInt8());
        return *this;
    }

    /// Client-assigned identification of a strategy.
    ONIXS_B3_BOE_NODISCARD
    bool
    strategyId(
        StrategyIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 160;

        return ordinary(value, offset, NullStrategyIDOptional());
    }

    /// Client-assigned identification of a strategy.
    ThisType& setStrategyId(StrategyIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 160;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStrategyIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 160;

        setOrdinary(offset, NullStrategyIDOptional());
        return *this;
    }

    /// Unique ID for all matches that occur as a result of a
    /// implied event.
    ONIXS_B3_BOE_NODISCARD
    bool impliedEventId(ImpliedEventID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 164;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 4;

        return ordinary(value, offset, NullImpliedEventID(), since);
    }

    /// Unique ID for all matches that occur as a result of a
    /// implied event.
    ThisType& setImpliedEventId(ImpliedEventID value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 164;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 4;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setImpliedEventIdToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 164;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 4;

        setOrdinary(offset, NullImpliedEventID(), since);
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 170;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 170;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 170;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 174
                : (version >= 4)
                    ? 170
                    : (version >= 3)
                        ? 164
                        : 159;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setClOrdIdToNull();
        setAccountToNull();
        setOrderCategoryToNull();
        setMultiLegReportingTypeToNull();
        setTotNoRelatedSymToNull();
        setSecondaryExecIdToNull();
        setExecRefIdToNull();
        setCrossIdToNull();
        setCrossedIndicatorToNull();
        setTradingSessionIdToNull();
        setTradingSessionSubIdToNull();
        setSecurityTradingStatusToNull();
        setCrossTypeToNull();
        setCrossPrioritizationToNull();
        setStrategyIdToNull();

        if (version() >= 4)
        {
            setImpliedEventIdToNull();
        }

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionReportTrade203";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "ExecutionReportTrade203");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const ExecutionReportTrade203& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const ExecutionReportTrade203& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// Execution Report - Reject message notifies the reason a client request was not accepted by Matching Engine.
ONIXS_B3_BOE_LTWT_STRUCT
ExecutionReportReject204
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef ExecutionReportReject204 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 204 };

    /// Initializes a blank instance.
    ExecutionReportReject204() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    ExecutionReportReject204(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    ExecutionReportReject204(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    ExecutionReportReject204(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionReportReject204(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionReportReject204(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// MessageType.ExecutionReport_Reject.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::ExecutionReportReject;
    }

    /// MessageType.ExecutionReport_Reject.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Identifies current status of order.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static OrdStatus::Enum ordStatus()
        ONIXS_B3_BOE_NOTHROW
    {
        return OrdStatus::Rejected;
    }

    /// Identifies current status of order.

    /// Identifies the type of request that this Cancel Reject is
    /// in response to.
    ONIXS_B3_BOE_NODISCARD
    CxlRejResponseTo::Enum cxlRejResponseTo() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<CxlRejResponseTo>(offset);
    }

    /// Identifies the type of request that this Cancel Reject is
    /// in response to.
    ThisType&
    setCxlRejResponseTo(
        CxlRejResponseTo::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<CxlRejResponseTo>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ONIXS_B3_BOE_NODISCARD
    bool secondaryOrderId(OrderIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullOrderIDOptional());
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ThisType& setSecondaryOrderId(OrderIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setSecondaryOrderIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullOrderIDOptional());
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Code to identify reason for order rejection. Please refer
    /// to the error codes document for domain information.
    ONIXS_B3_BOE_NODISCARD
    RejReason ordRejReason() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary<RejReason>(offset);
    }

    /// Code to identify reason for order rejection. Please refer
    /// to the error codes document for domain information.
    ThisType& setOrdRejReason(RejReason value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ONIXS_B3_BOE_NODISCARD
    ExecID execId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary<ExecID>(offset);
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ThisType& setExecId(ExecID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    bool orderId(OrderIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return ordinary(value, offset, NullOrderIDOptional());
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrderIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, NullOrderIDOptional());
        return *this;
    }

    /// Value of origClOrdID field informed from the related
    /// request message.
    ONIXS_B3_BOE_NODISCARD
    bool origClOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// Value of origClOrdID field informed from the related
    /// request message.
    ThisType& setOrigClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Order type.
    ONIXS_B3_BOE_NODISCARD
    OrdType::Enum ordType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        return enumeration<OrdType>(offset);
    }

    /// Order type.
    ThisType& setOrdType(OrdType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;

        setEnumeration<OrdType>(offset, value);
        return *this;
    }

    /// Specifies how long the order remains in effect.
    ONIXS_B3_BOE_NODISCARD
    TimeInForce::Enum timeInForce() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 85;

        return enumeration<TimeInForce>(offset);
    }

    /// Specifies how long the order remains in effect.
    ThisType& setTimeInForce(TimeInForce::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 85;

        setEnumeration<TimeInForce>(offset, value);
        return *this;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ONIXS_B3_BOE_NODISCARD
    bool expireDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 86;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Date of order expiration (last day the order can trade),
    /// always expressed in terms of the local market date.
    ThisType& setExpireDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 86;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setExpireDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 86;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Quantity ordered. Not presented if the order to be
    /// cancelled is not found.
    ONIXS_B3_BOE_NODISCARD
    bool orderQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Quantity ordered. Not presented if the order to be
    /// cancelled is not found.
    ThisType& setOrderQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrderQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        return decimal(value, offset, NullPriceOptional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ONIXS_B3_BOE_NODISCARD
    bool stopPx(PriceOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        return decimal(value, offset, NullPriceOptional());
    }

    /// The stop price of a stop limit order (Conditionally
    /// required if OrdType = 4).
    ThisType& setStopPx(PriceOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStopPxToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, NullPriceOptional());
        return *this;
    }

    /// Minimum quantity of an order to be executed.
    ONIXS_B3_BOE_NODISCARD
    bool minQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Minimum quantity of an order to be executed.
    ThisType& setMinQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMinQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ONIXS_B3_BOE_NODISCARD
    bool maxFloor(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Maximum number of shares or contracts within an order to
    /// be shown on the match engine at any given time.
    ThisType& setMaxFloor(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setMaxFloorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ONIXS_B3_BOE_NODISCARD
    bool crossId(CrossIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        return ordinary(value, offset, NullCrossIDOptional());
    }

    /// ID of electronically submitted cross order by the
    /// institution (if in response to a cross order).
    ThisType& setCrossId(CrossIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setCrossIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, NullCrossIDOptional());
        return *this;
    }

    /// Indicates cross order purpose.
    ONIXS_B3_BOE_NODISCARD
    bool
    crossedIndicator(
        CrossedIndicator::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        return enumeration<CrossedIndicator>(value, offset, NullUint16EnumEncoding());
    }

    /// Indicates cross order purpose.
    ThisType&
    setCrossedIndicator(
        CrossedIndicator::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setEnumeration<CrossedIndicator>(offset, value);
        return *this;
    }

    ThisType& setCrossedIndicatorToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, NullUint16EnumEncoding());
        return *this;
    }

    /// Time of receipt of related inbound message in the gateway.
    ONIXS_B3_BOE_NODISCARD
    bool
    receivedTime(
        UTCTimestampNanosOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 138;

        return ordinary(value, offset, NullUTCTimestampNanosOptional());
    }

    /// Time of receipt of related inbound message in the gateway.
    ThisType&
    setReceivedTime(
        UTCTimestampNanosOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 138;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setReceivedTimeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 138;

        setOrdinary(offset, NullUTCTimestampNanosOptional());
        return *this;
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 149;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 149;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 149;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 150;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for self trade
    /// prevention/mass cancel on behalf purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 150;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 150;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Client-assigned identification of a strategy.
    ONIXS_B3_BOE_NODISCARD
    bool
    strategyId(
        StrategyIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 158;

        return ordinary(value, offset, NullStrategyIDOptional());
    }

    /// Client-assigned identification of a strategy.
    ThisType& setStrategyId(StrategyIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 158;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setStrategyIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 158;

        setOrdinary(offset, NullStrategyIDOptional());
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 162;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 162;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 162;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Free ASCII format text string.
    ONIXS_B3_BOE_NODISCARD
    StrRef text() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(textAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text string.
    ThisType& setText(StrRef value)
    {
        setVariableLengthField(
            textAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 166
                : (version >= 3)
                    ? 162
                    : 146;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size) + static_cast<MessageSize>(TextEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        setTextToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setSecondaryOrderIdToNull();
        setOrderIdToNull();
        setOrigClOrdIdToNull();
        setAccountToNull();
        setExpireDateToNull();
        setOrderQtyToNull();
        setPriceToNull();
        setStopPxToNull();
        setMinQtyToNull();
        setMaxFloorToNull();
        setCrossIdToNull();
        setCrossedIndicatorToNull();
        setReceivedTimeToNull();
        setOrdTagIdToNull();
        setInvestorIdToNull();
        setStrategyIdToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionReportReject204";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "ExecutionReportReject204");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (text().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>().
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
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const ExecutionReportReject204& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const ExecutionReportReject204& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Access helper.
    struct textAccess
    {
        TextEncoding&
        operator()(
            const ExecutionReportReject204& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    tail<MemoEncoding>().
                    head<TextEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setTextToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(textAccess(), *this);

        return *this;
    }
};

/// Execution Report – Forward message is sent with order fills were traded and processed on Matching Engine for Forward exclusively (Termo).
ONIXS_B3_BOE_LTWT_STRUCT
ExecutionReportForward205
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef ExecutionReportForward205 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 205 };

    /// Initializes a blank instance.
    ExecutionReportForward205() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    ExecutionReportForward205(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    ExecutionReportForward205(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    ExecutionReportForward205(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    ExecutionReportForward205(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    ExecutionReportForward205(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// MessageType.ExecutionReport_Forward.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::ExecutionReportForward;
    }

    /// MessageType.ExecutionReport_Forward.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Identifies current status of order.
    ONIXS_B3_BOE_NODISCARD
    OrdStatus::Enum ordStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<OrdStatus>(offset);
    }

    /// Identifies current status of order.
    ThisType& setOrdStatus(OrdStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<OrdStatus>(offset, value);
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    bool clOrdId(ClOrdIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullClOrdIDOptional());
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setClOrdIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, NullClOrdIDOptional());
        return *this;
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ONIXS_B3_BOE_NODISCARD
    OrderID secondaryOrderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<OrderID>(offset);
    }

    /// Exchange-generated order identifier that changes for each
    /// order modification event, or quantity replenishment in
    /// disclosed orders.
    ThisType& setSecondaryOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Quantity of shares bought/sold on the last fill.
    ONIXS_B3_BOE_NODISCARD
    Quantity lastQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<Quantity>(offset);
    }

    /// Quantity of shares bought/sold on the last fill.
    ThisType& setLastQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price of last fill.
    ONIXS_B3_BOE_NODISCARD
    Price lastPx() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return decimal<Price>(offset);
    }

    /// Price of last fill.
    ThisType& setLastPx(Price value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ONIXS_B3_BOE_NODISCARD
    ExecID execId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return ordinary<ExecID>(offset);
    }

    /// Unique identifier of execution message as assigned by the
    /// exchange – unique per instrument.
    ThisType& setExecId(ExecID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, value);
        return *this;
    }

    /// Amount of shares open for further execution, or
    /// unexecuted.
    ONIXS_B3_BOE_NODISCARD
    Quantity leavesQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        return ordinary<Quantity>(offset);
    }

    /// Amount of shares open for further execution, or
    /// unexecuted.
    ThisType& setLeavesQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, value);
        return *this;
    }

    /// Total number of shares or contracts filled.
    ONIXS_B3_BOE_NODISCARD
    Quantity cumQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        return ordinary<Quantity>(offset);
    }

    /// Total number of shares or contracts filled.
    ThisType& setCumQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;

        setOrdinary(offset, value);
        return *this;
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    TradeID tradeId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        return ordinary<TradeID>(offset);
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ThisType& setTradeId(TradeID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the contra broker firm.
    ONIXS_B3_BOE_NODISCARD
    Firm contraBroker() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;

        return ordinary<Firm>(offset);
    }

    /// Identifies the contra broker firm.
    ThisType& setContraBroker(Firm value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 100;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier for order as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    OrderID orderId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        return ordinary<OrderID>(offset);
    }

    /// Unique identifier for order as assigned by the exchange.
    ThisType& setOrderId(OrderID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 104;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identify whether the order initiator is an aggressor or
    /// not in the trade.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum aggressorIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        return enumeration<Boolean>(offset);
    }

    /// Identify whether the order initiator is an aggressor or
    /// not in the trade.
    ThisType& setAggressorIndicator(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 112;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ONIXS_B3_BOE_NODISCARD
    bool settlType(SettlType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 113;

        return enumeration<SettlType>(value, offset, NullChar());
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ThisType& setSettlType(SettlType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 113;

        setEnumeration<SettlType>(offset, value);
        return *this;
    }

    ThisType& setSettlTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 113;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ONIXS_B3_BOE_NODISCARD
    Timestamp tradeDate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 114;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ThisType& setTradeDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 114;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ONIXS_B3_BOE_NODISCARD
    bool
    daysToSettlement(
        DaysToSettlementOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        return ordinary(value, offset, NullDaysToSettlementOptional());
    }

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ThisType&
    setDaysToSettlement(
        DaysToSettlementOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setDaysToSettlementToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        setOrdinary(offset, NullDaysToSettlementOptional());
        return *this;
    }

    /// Unique identifier present in all messages associated with
    /// a spread transaction. This value allows linking spread
    /// summary fill notice, leg fill notices, and leg trade
    /// cancellation execution report messages generated from a
    /// spread transaction.
    ONIXS_B3_BOE_NODISCARD
    bool secondaryExecId(ExecIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        return ordinary(value, offset, NullExecIDOptional());
    }

    /// Unique identifier present in all messages associated with
    /// a spread transaction. This value allows linking spread
    /// summary fill notice, leg fill notices, and leg trade
    /// cancellation execution report messages generated from a
    /// spread transaction.
    ThisType& setSecondaryExecId(ExecIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setSecondaryExecIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 120;

        setOrdinary(offset, NullExecIDOptional());
        return *this;
    }

    /// Optionally sent when reporting a trade bust. Contains the
    /// identifier of the busted trade.
    ONIXS_B3_BOE_NODISCARD
    bool execRefId(ExecIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        return ordinary(value, offset, NullExecIDOptional());
    }

    /// Optionally sent when reporting a trade bust. Contains the
    /// identifier of the busted trade.
    ThisType& setExecRefId(ExecIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setExecRefIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 128;

        setOrdinary(offset, NullExecIDOptional());
        return *this;
    }

    /// Describes the interest to be paid by the forward buyer and
    /// received by the forward seller, in proportion to the
    /// agreed days to settlement. Expressed in decimal form. For
    /// example, 1% is expressed and sent as 0.01. One basis point
    /// is represented as 0.0001.
    ONIXS_B3_BOE_NODISCARD
    bool
    fixedRate(
        Percentage8Optional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        return decimal(value, offset, NullPercentage8Optional());
    }

    /// Describes the interest to be paid by the forward buyer and
    /// received by the forward seller, in proportion to the
    /// agreed days to settlement. Expressed in decimal form. For
    /// example, 1% is expressed and sent as 0.01. One basis point
    /// is represented as 0.0001.
    ThisType&
    setFixedRate(
        Percentage8Optional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setFixedRateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 136;

        setOrdinary(offset, NullPercentage8Optional());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 144;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifier for Trading Session.
    ONIXS_B3_BOE_NODISCARD
    bool
    tradingSessionId(
        TradingSessionID::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 152;

        return enumeration<TradingSessionID>(value, offset, NullUint8EnumEncoding());
    }

    /// Identifier for Trading Session.
    ThisType&
    setTradingSessionId(
        TradingSessionID::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 152;

        setEnumeration<TradingSessionID>(offset, value);
        return *this;
    }

    ThisType& setTradingSessionIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 152;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Identifier for the instrument group phase.
    ONIXS_B3_BOE_NODISCARD
    bool
    tradingSessionSubId(
        TradingSessionSubID::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 153;

        return enumeration<TradingSessionSubID>(value, offset, NullUint8EnumEncoding());
    }

    /// Identifier for the instrument group phase.
    ThisType&
    setTradingSessionSubId(
        TradingSessionSubID::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 153;

        setEnumeration<TradingSessionSubID>(offset, value);
        return *this;
    }

    ThisType& setTradingSessionSubIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 153;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Identifier for the instrument status.
    ONIXS_B3_BOE_NODISCARD
    bool
    securityTradingStatus(
        SecurityTradingStatus::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 154;

        return enumeration<SecurityTradingStatus>(value, offset, NullUint8EnumEncoding());
    }

    /// Identifier for the instrument status.
    ThisType&
    setSecurityTradingStatus(
        SecurityTradingStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 154;

        setEnumeration<SecurityTradingStatus>(offset, value);
        return *this;
    }

    ThisType& setSecurityTradingStatusToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 154;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 155;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 159
                : 155;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setClOrdIdToNull();
        setAccountToNull();
        setSettlTypeToNull();
        setDaysToSettlementToNull();
        setSecondaryExecIdToNull();
        setExecRefIdToNull();
        setFixedRateToNull();
        setTradingSessionIdToNull();
        setTradingSessionSubIdToNull();
        setSecurityTradingStatusToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "ExecutionReportForward205";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "ExecutionReportForward205");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const ExecutionReportForward205& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const ExecutionReportForward205& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// BusinessMessageReject message can reject an application-level message which fulfills session level rules but fails the business rules.
ONIXS_B3_BOE_LTWT_STRUCT
BusinessMessageReject206
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef BusinessMessageReject206 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 206 };

    /// Initializes a blank instance.
    BusinessMessageReject206() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    BusinessMessageReject206(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    BusinessMessageReject206(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    BusinessMessageReject206(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    BusinessMessageReject206(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    BusinessMessageReject206(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = BusinessMessageReject.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::BusinessMessageReject;
    }

    /// Message type = BusinessMessageReject.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// MsgType of the FIX message being referenced.
    ONIXS_B3_BOE_NODISCARD
    MessageType::Enum refMsgType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<MessageType>(offset);
    }

    /// MsgType of the FIX message being referenced.
    ThisType& setRefMsgType(MessageType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<MessageType>(offset, value);
        return *this;
    }

    /// Message sequence number of rejected message.
    ONIXS_B3_BOE_NODISCARD
    SeqNum refSeqNum() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<SeqNum>(offset);
    }

    /// Message sequence number of rejected message.
    ThisType& setRefSeqNum(SeqNum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// The value of the business-level “ID” field on the message
    /// being referenced. Required unless the corresponding ID
    /// field was not specified.
    ONIXS_B3_BOE_NODISCARD
    bool
    businessRejectRefId(
        BusinessRejectRefID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary(value, offset, NullBusinessRejectRefID());
    }

    /// The value of the business-level “ID” field on the message
    /// being referenced. Required unless the corresponding ID
    /// field was not specified.
    ThisType&
    setBusinessRejectRefId(
        BusinessRejectRefID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setBusinessRejectRefIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        setOrdinary(offset, NullBusinessRejectRefID());
        return *this;
    }

    /// Code to identify the reason of the rejection.
    ONIXS_B3_BOE_NODISCARD
    RejReason businessRejectReason() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary<RejReason>(offset);
    }

    /// Code to identify the reason of the rejection.
    ThisType& setBusinessRejectReason(RejReason value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        setOrdinary(offset, value);
        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Free ASCII format text string.
    ONIXS_B3_BOE_NODISCARD
    StrRef text() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(textAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text string.
    ThisType& setText(StrRef value)
    {
        setVariableLengthField(
            textAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            36;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(MemoEncoding::Size) + static_cast<MessageSize>(TextEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setMemoToNull();
        setTextToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setBusinessRejectRefIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "BusinessMessageReject206";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "BusinessMessageReject206");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (text().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<MemoEncoding>().
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
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const BusinessMessageReject206& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<MemoEncoding>();
        }
    };

    /// Access helper.
    struct textAccess
    {
        TextEncoding&
        operator()(
            const BusinessMessageReject206& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<MemoEncoding>().
                    head<TextEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setTextToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(textAccess(), *this);

        return *this;
    }
};

/// The SecurityDefinitionRequest message creates a User Defined Spread (UDS) instrument. User-Defined Spreads provide users of the electronic trading platform the ability to create strategies composed by their choice of leg instruments, leg ratio and leg side.
ONIXS_B3_BOE_LTWT_STRUCT
SecurityDefinitionRequest300
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef SecurityDefinitionRequest300 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 300 };

    /// Repeating group dimensions.
    /// Entry of LegsEntry repeating group.
    ONIXS_B3_BOE_LTWT_STRUCT
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

        /// This type alias.
        typedef LegsEntry ThisType;

        /// Initializes instance of given
        /// version over given memory block.
        LegsEntry(
            void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Reset all variable-length fields if any.
        ThisType& resetVariableFields()
            ONIXS_B3_BOE_NOTHROW
        {
            return *this;
        }

        /// Reset all variable-length and optional fields if any.
        ThisType& reset()
            ONIXS_B3_BOE_NOTHROW
        {
            setLegSideToNull();

            resetVariableFields();
            return *this;
        }

        /// Multileg instrument's individual security’s Symbol. See
        /// Symbol (55) field for description.
        ONIXS_B3_BOE_NODISCARD
        StrRef legSymbol() const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 20;

            return fixedStr<length>(offset);
        }

        /// Multileg instrument's individual security’s Symbol. See
        /// Symbol (55) field for description.
        ThisType& setLegSymbol(StrRef value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 20;

            setFixedStr<length>(offset, value);
            return *this;
        }

        /// Exchange code the leg security belongs to.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_NODISCARD
        ONIXS_B3_BOE_CONSTEXPR
        static StrRef legSecurityExchange()
            ONIXS_B3_BOE_NOTHROW
        {
            return constructStrRef("BVMF");
        }

        /// The ratio of quantity for this individual leg relative to
        /// the entire multileg security.
        ONIXS_B3_BOE_NODISCARD
        RatioQty legRatioQty() const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

            return decimal<RatioQty>(offset);
        }

        /// The ratio of quantity for this individual leg relative to
        /// the entire multileg security.
        ThisType& setLegRatioQty(RatioQty value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

            setOrdinary(offset, value);
            return *this;
        }

        /// The side of this individual leg (multileg security). See
        /// Side (54) field for description and values.
        ONIXS_B3_BOE_NODISCARD
        bool legSide(Side::Enum& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

            return enumeration<Side>(value, offset, NullChar());
        }

        /// The side of this individual leg (multileg security). See
        /// Side (54) field for description and values.
        ThisType& setLegSide(Side::Enum value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

            setEnumeration<Side>(offset, value);
            return *this;
        }

        ThisType& setLegSideToNull()
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

            setOrdinary(offset, NullChar());
            return *this;
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static
        BlockLength
        blockLength(
            ONIXS_B3_BOE_UNUSED SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                30;
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static
        BlockLength
        minimalBlockLength(
            ONIXS_B3_BOE_UNUSED SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                29;
        }

        /// Entity class name.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_NODISCARD
        ONIXS_B3_BOE_CONSTEXPR
        static const Char* className()
        {
            return "SecurityDefinitionRequest300.LegsEntry";
        }
    };

    /// Repeating group containing LegsEntry entries.
    typedef
    SbeGroup<LegsEntry, GroupSizeEncoding, MessageSize>
    Legs;

    /// Initializes a blank instance.
    SecurityDefinitionRequest300() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    SecurityDefinitionRequest300(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    SecurityDefinitionRequest300(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    SecurityDefinitionRequest300(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SecurityDefinitionRequest300(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SecurityDefinitionRequest300(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = SecurityDefinitionRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::SecurityDefinitionRequest;
    }

    /// Message type = SecurityDefinitionRequest.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Unique ID of a Security Definition Request.
    ONIXS_B3_BOE_NODISCARD
    SecurityReqRespID securityReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary<SecurityReqRespID>(offset);
    }

    /// Unique ID of a Security Definition Request.
    ThisType& setSecurityReqId(SecurityReqRespID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// \return instance of Legs repeating group.
    ONIXS_B3_BOE_NODISCARD
    Legs legs() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Legs>(LegsAccess(), *this);
    }

    /// \return instance of Legs repeating group.
    ONIXS_B3_BOE_NODISCARD
    Legs legs()
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Legs>(LegsAccess(), *this);
    }

    /// Setup repeating group with the given number of entries.
    /// Sets all optional fields of the group entries to null.
    /// \return noLegs(555) repeating group.
    Legs legs(Legs::Size length)
    {
        return constructGroup<Legs>(
            LegsAccess(),
            length,
            *this);
    }

    /// Setup repeating group with the given number of entries.
    /// \return noLegs(555) repeating group.
    Legs
    legs(
        Legs::Size length,
        NoFieldsInit)
    {
        return setupGroup<Legs>(
            LegsAccess(),
            length,
            *this);
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            41;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(Legs::EmptySize);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    UInt64
    getMaxMessageSize(
        UInt8 maxGroupItems = 255)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version) +
            (GroupSizeEncoding::Size + LegsEntry::blockLength(Schema::Version) * static_cast<UInt64>(maxGroupItems));
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setLegsToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "SecurityDefinitionRequest300";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "SecurityDefinitionRequest300");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            legs().tail();
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<Legs>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct LegsAccess
    {
        Legs
        operator()(
            const SecurityDefinitionRequest300& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    head<Legs>();
        }
    };

    /// Reset an instance of the repeating group.
    /// All the following data will be invalidated.
    void setLegsToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        resetGroup<Legs>(LegsAccess(), *this);
    }
};

/// The SecurityDefinitioresponse message is sent in response to an attempt to create a new security definition.
ONIXS_B3_BOE_LTWT_STRUCT
SecurityDefinitionResponse301
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef SecurityDefinitionResponse301 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 301 };

    /// Initializes a blank instance.
    SecurityDefinitionResponse301() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    SecurityDefinitionResponse301(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    SecurityDefinitionResponse301(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    SecurityDefinitionResponse301(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    SecurityDefinitionResponse301(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    SecurityDefinitionResponse301(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = SecurityDefinitionResponse.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::SecurityDefinitionResponse;
    }

    /// Message type = SecurityDefinitionResponse.

    /// Common header to all outbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all outbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Unique ID of a Security Definition Request.
    ONIXS_B3_BOE_NODISCARD
    SecurityReqRespID securityReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<SecurityReqRespID>(offset);
    }

    /// Unique ID of a Security Definition Request.
    ThisType& setSecurityReqId(SecurityReqRespID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    bool
    securityId(
        SecurityIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullSecurityIDOptional());
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setSecurityIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullSecurityIDOptional());
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Type of Security Definition message response.
    ONIXS_B3_BOE_NODISCARD
    SecurityResponseType::Enum
    securityResponseType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return enumeration<SecurityResponseType>(offset);
    }

    /// Type of Security Definition message response.
    ThisType&
    setSecurityResponseType(
        SecurityResponseType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setEnumeration<SecurityResponseType>(offset, value);
        return *this;
    }

    /// Indicates the type of Strategy created. This field is not
    /// sent on rejects.
    ONIXS_B3_BOE_NODISCARD
    bool securityStrategyType(StrRef& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 37;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 3;

        return fixedStr<length>(value, offset);
    }

    /// Indicates the type of Strategy created. This field is not
    /// sent on rejects.
    ThisType& setSecurityStrategyType(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 37;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 3;

        setFixedStr<length>(offset, value);
        return *this;
    }

    ThisType& setSecurityStrategyTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 37;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 3;

        setFixedStr<length>(offset, StrRef());
        return *this;
    }

    /// B3 requires that this field is properly set. It contains
    /// the human readable form of the SecurityID tag, available
    /// in the Security List message in Market Data feed.
    ONIXS_B3_BOE_NODISCARD
    StrRef symbol() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 40;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 20;

        return fixedStr<length>(offset);
    }

    /// B3 requires that this field is properly set. It contains
    /// the human readable form of the SecurityID tag, available
    /// in the Security List message in Market Data feed.
    ThisType& setSymbol(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 40;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 20;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Unique ID of a Security Definition message.
    ONIXS_B3_BOE_NODISCARD
    SecurityReqRespID securityResponseId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<SecurityReqRespID>(offset);
    }

    /// Unique ID of a Security Definition message.
    ThisType& setSecurityResponseId(SecurityReqRespID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            83;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setSecurityIdToNull();
        setSecurityStrategyTypeToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "SecurityDefinitionResponse301";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "SecurityDefinitionResponse301");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// The Quote Request message is used within the context of this Forward transaction in which two parties have completed a deal outside the Exchange and are initiating the negotiation process to formalize and execute this operation on the Exchange.
ONIXS_B3_BOE_LTWT_STRUCT
QuoteRequest401
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef QuoteRequest401 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 401 };

    /// Repeating group dimensions.
    /// Entry of SidesEntry repeating group.
    ONIXS_B3_BOE_LTWT_STRUCT
    SidesEntry : SbeGroupEntry
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

        /// This type alias.
        typedef SidesEntry ThisType;

        /// Initializes instance of given
        /// version over given memory block.
        SidesEntry(
            void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Reset all variable-length fields if any.
        ThisType& resetVariableFields()
            ONIXS_B3_BOE_NOTHROW
        {
            return *this;
        }

        /// Reset all variable-length and optional fields if any.
        ThisType& reset()
            ONIXS_B3_BOE_NOTHROW
        {
            setAccountToNull();

            if (version() >= 5)
            {
                setTradingSubAccountToNull();
            }

            resetVariableFields();
            return *this;
        }

        /// Side of order.
        ONIXS_B3_BOE_NODISCARD
        Side::Enum side() const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return enumeration<Side>(offset);
        }

        /// Side of order.
        ThisType& setSide(Side::Enum value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            setEnumeration<Side>(offset, value);
            return *this;
        }

        /// Account mnemonic of the order.
        ONIXS_B3_BOE_NODISCARD
        bool account(AccountOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            return ordinary(value, offset, NullAccountOptional());
        }

        /// Account mnemonic of the order.
        ThisType& setAccount(AccountOptional value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            setOrdinary(offset, value);
            return *this;
        }

        ThisType& setAccountToNull()
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            setOrdinary(offset, NullAccountOptional());
            return *this;
        }

        /// Account used for associating risk limits (when defined).
        ONIXS_B3_BOE_NODISCARD
        bool tradingSubAccount(AccountOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 5;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            return ordinary(value, offset, NullAccountOptional(), since);
        }

        /// Account used for associating risk limits (when defined).
        ThisType& setTradingSubAccount(AccountOptional value)
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 5;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            setOrdinary(offset, value, since);
            return *this;
        }

        ThisType& setTradingSubAccountToNull()
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 5;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            setOrdinary(offset, NullAccountOptional(), since);
            return *this;
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static BlockLength blockLength(SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                minimalBlockLength(version);
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static BlockLength minimalBlockLength(SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                (version >= 5)
                    ? 9
                    : 5;
        }

        /// Entity class name.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_NODISCARD
        ONIXS_B3_BOE_CONSTEXPR
        static const Char* className()
        {
            return "QuoteRequest401.SidesEntry";
        }
    };

    /// Repeating group containing SidesEntry entries.
    typedef
    SbeGroup<SidesEntry, GroupSizeEncoding, MessageSize>
    Sides;

    /// Initializes a blank instance.
    QuoteRequest401() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    QuoteRequest401(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    QuoteRequest401(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    QuoteRequest401(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    QuoteRequest401(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    QuoteRequest401(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = QuoteRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::QuoteRequest;
    }

    /// Message type = QuoteRequest.

    /// Common header to all bidirectional business messages.
    ONIXS_B3_BOE_NODISCARD
    const BidirectionalBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Common header to all bidirectional business messages.
    BidirectionalBusinessHeader&
    businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for quote request.
    ONIXS_B3_BOE_NODISCARD
    QuoteReqID quoteReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<QuoteReqID>(offset);
    }

    /// Unique identifier for quote request.
    ThisType& setQuoteReqId(QuoteReqID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier for quote.
    ONIXS_B3_BOE_NODISCARD
    bool quoteId(QuoteIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullQuoteIDOptional());
    }

    /// Unique identifier for quote.
    ThisType& setQuoteId(QuoteIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setQuoteIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, NullQuoteIDOptional());
        return *this;
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    bool tradeId(TradeIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullTradeIDOptional());
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ThisType& setTradeId(TradeIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setTradeIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, NullTradeIDOptional());
        return *this;
    }

    /// Broker identifier as assigned by B3 used to indicate the
    /// counterparty brokerage firm in a Forward deal.
    ONIXS_B3_BOE_NODISCARD
    Firm contraBroker() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary<Firm>(offset);
    }

    /// Broker identifier as assigned by B3 used to indicate the
    /// counterparty brokerage firm in a Forward deal.
    ThisType& setContraBroker(Firm value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    Price8 price() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return decimal<Price8>(offset);
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(Price8 value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ONIXS_B3_BOE_NODISCARD
    SettlType::Enum settlType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return enumeration<SettlType>(offset);
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ThisType& setSettlType(SettlType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setEnumeration<SettlType>(offset, value);
        return *this;
    }

    /// Specifies if a simultaneous trade of the underlying is to
    /// be performed.Required to indicate Termo Vista and Termo
    /// Vista Registered.
    ONIXS_B3_BOE_NODISCARD
    bool
    executeUnderlyingTrade(
        ExecuteUnderlyingTrade::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        return enumeration<ExecuteUnderlyingTrade>(value, offset, NullChar());
    }

    /// Specifies if a simultaneous trade of the underlying is to
    /// be performed.Required to indicate Termo Vista and Termo
    /// Vista Registered.
    ThisType&
    setExecuteUnderlyingTrade(
        ExecuteUnderlyingTrade::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        setEnumeration<ExecuteUnderlyingTrade>(offset, value);
        return *this;
    }

    ThisType& setExecuteUnderlyingTradeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef executingTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 93;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 93;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Describes the interest to be paid by the forward buyer and
    /// received by the forward seller, in proportion to the
    /// agreed days to settlement. Expressed in decimal form. For
    /// example, 1% is expressed and sent as 0.01. One basis point
    /// is represented as 0.0001.
    ONIXS_B3_BOE_NODISCARD
    Percentage8 fixedRate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;

        return decimal<Percentage8>(offset);
    }

    /// Describes the interest to be paid by the forward buyer and
    /// received by the forward seller, in proportion to the
    /// agreed days to settlement. Expressed in decimal form. For
    /// example, 1% is expressed and sent as 0.01. One basis point
    /// is represented as 0.0001.
    ThisType& setFixedRate(Percentage8 value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;

        setOrdinary(offset, value);
        return *this;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static Boolean::Enum privateQuote()
        ONIXS_B3_BOE_NOTHROW
    {
        return Boolean::TrueValue;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ONIXS_B3_BOE_NODISCARD
    DaysToSettlement daysToSettlement() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 106;

        return ordinary<DaysToSettlement>(offset);
    }

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ThisType& setDaysToSettlement(DaysToSettlement value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 106;

        setOrdinary(offset, value);
        return *this;
    }

    /// \return instance of Sides repeating group.
    ONIXS_B3_BOE_NODISCARD
    Sides sides() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Sides>(SidesAccess(), *this);
    }

    /// \return instance of Sides repeating group.
    ONIXS_B3_BOE_NODISCARD
    Sides sides()
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Sides>(SidesAccess(), *this);
    }

    /// Setup repeating group with the given number of entries.
    /// Sets all optional fields of the group entries to null.
    /// \return noSides(35511) repeating group.
    Sides sides(Sides::Size length)
    {
        return constructGroup<Sides>(
            SidesAccess(),
            length,
            *this);
    }

    /// Setup repeating group with the given number of entries.
    /// \return noSides(35511) repeating group.
    Sides
    sides(
        Sides::Size length,
        NoFieldsInit)
    {
        return setupGroup<Sides>(
            SidesAccess(),
            length,
            *this);
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            108;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size) + static_cast<MessageSize>(Sides::EmptySize);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setSidesToNull();
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setQuoteIdToNull();
        setTradeIdToNull();
        setExecuteUnderlyingTradeToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "QuoteRequest401";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("QuoteRequest401");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkVariableLengthFields<Sides>().
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct SidesAccess
    {
        Sides
        operator()(
            const QuoteRequest401& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    head<Sides>();
        }
    };

    /// Reset an instance of the repeating group.
    /// All the following data will be invalidated.
    void setSidesToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        resetGroup<Sides>(SidesAccess(), *this);
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const QuoteRequest401& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Sides>().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const QuoteRequest401& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Sides>().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// The QuoteStatusReport message is to inform the current status of forward acceptance.
ONIXS_B3_BOE_LTWT_STRUCT
QuoteStatusReport402
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef QuoteStatusReport402 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 402 };

    /// Initializes a blank instance.
    QuoteStatusReport402() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    QuoteStatusReport402(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    QuoteStatusReport402(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    QuoteStatusReport402(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    QuoteStatusReport402(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    QuoteStatusReport402(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = QuoteStatusReport.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::QuoteStatusReport;
    }

    /// Message type = QuoteStatusReport.

    /// Common header to all bidirectional business messages.
    ONIXS_B3_BOE_NODISCARD
    const BidirectionalBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Common header to all bidirectional business messages.
    BidirectionalBusinessHeader&
    businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Reason Quote was rejected.
    ONIXS_B3_BOE_NODISCARD
    bool quoteRejectReason(RejReasonOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullRejReasonOptional());
    }

    /// Reason Quote was rejected.
    ThisType& setQuoteRejectReason(RejReasonOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setQuoteRejectReasonToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, NullRejReasonOptional());
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for quote request.
    ONIXS_B3_BOE_NODISCARD
    QuoteReqID quoteReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary<QuoteReqID>(offset);
    }

    /// Unique identifier for quote request.
    ThisType& setQuoteReqId(QuoteReqID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier for quote.
    ONIXS_B3_BOE_NODISCARD
    QuoteID quoteId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return ordinary<QuoteID>(offset);
    }

    /// Unique identifier for quote.
    ThisType& setQuoteId(QuoteID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 40;

        setOrdinary(offset, value);
        return *this;
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    bool tradeId(TradeIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary(value, offset, NullTradeIDOptional());
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ThisType& setTradeId(TradeIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setTradeIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, NullTradeIDOptional());
        return *this;
    }

    /// Broker identifier as assigned by B3 used to indicate the
    /// counterparty brokerage firm in a Forward deal.
    ONIXS_B3_BOE_NODISCARD
    Firm contraBroker() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary<Firm>(offset);
    }

    /// Broker identifier as assigned by B3 used to indicate the
    /// counterparty brokerage firm in a Forward deal.
    ThisType& setContraBroker(Firm value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the status of the quote acknowledgement.
    ONIXS_B3_BOE_NODISCARD
    QuoteStatus::Enum quoteStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return enumeration<QuoteStatus>(offset);
    }

    /// Identifies the status of the quote acknowledgement.
    ThisType& setQuoteStatus(QuoteStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setEnumeration<QuoteStatus>(offset, value);
        return *this;
    }

    /// Identifies the type of request that a Quote Status Report
    /// is in response to.
    ONIXS_B3_BOE_NODISCARD
    bool
    quoteStatusResponseTo(
        QuoteStatusResponseTo::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 65;

        return enumeration<QuoteStatusResponseTo>(value, offset, NullChar());
    }

    /// Identifies the type of request that a Quote Status Report
    /// is in response to.
    ThisType&
    setQuoteStatusResponseTo(
        QuoteStatusResponseTo::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 65;

        setEnumeration<QuoteStatusResponseTo>(offset, value);
        return *this;
    }

    ThisType& setQuoteStatusResponseToToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 65;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 66;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 66;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 66;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    bool side(Side::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        return enumeration<Side>(value, offset, NullChar());
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    ThisType& setSideToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ONIXS_B3_BOE_NODISCARD
    bool settlType(SettlType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 71;

        return enumeration<SettlType>(value, offset, NullChar());
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ThisType& setSettlType(SettlType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 71;

        setEnumeration<SettlType>(offset, value);
        return *this;
    }

    ThisType& setSettlTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 71;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(Price8Optional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        return decimal(value, offset, NullPrice8Optional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(Price8Optional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 72;

        setOrdinary(offset, NullPrice8Optional());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 88;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 98;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef executingTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 103;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 103;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Interest rate of the forward trade.
    ONIXS_B3_BOE_NODISCARD
    bool
    fixedRate(
        Percentage8Optional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        return decimal(value, offset, NullPercentage8Optional());
    }

    /// Interest rate of the forward trade.
    ThisType&
    setFixedRate(
        Percentage8Optional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setFixedRateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 108;

        setOrdinary(offset, NullPercentage8Optional());
        return *this;
    }

    /// Specifies if a simultaneous trade of the underlying is to
    /// be performed.Required to indicate Termo Vista and Termo
    /// Vista Registered.
    ONIXS_B3_BOE_NODISCARD
    bool
    executeUnderlyingTrade(
        ExecuteUnderlyingTrade::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        return enumeration<ExecuteUnderlyingTrade>(value, offset, NullChar());
    }

    /// Specifies if a simultaneous trade of the underlying is to
    /// be performed.Required to indicate Termo Vista and Termo
    /// Vista Registered.
    ThisType&
    setExecuteUnderlyingTrade(
        ExecuteUnderlyingTrade::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        setEnumeration<ExecuteUnderlyingTrade>(offset, value);
        return *this;
    }

    ThisType& setExecuteUnderlyingTradeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 116;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static Boolean::Enum privateQuote()
        ONIXS_B3_BOE_NOTHROW
    {
        return Boolean::TrueValue;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ONIXS_B3_BOE_NODISCARD
    bool
    daysToSettlement(
        DaysToSettlementOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 117;

        return ordinary(value, offset, NullDaysToSettlementOptional());
    }

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ThisType&
    setDaysToSettlement(
        DaysToSettlementOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 117;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setDaysToSettlementToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 117;

        setOrdinary(offset, NullDaysToSettlementOptional());
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 119;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 119;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 119;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Free ASCII format text string.
    ONIXS_B3_BOE_NODISCARD
    StrRef text() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(textAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text string.
    ThisType& setText(StrRef value)
    {
        setVariableLengthField(
            textAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 123
                : 119;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size) + static_cast<MessageSize>(TextEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        setTextToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setQuoteRejectReasonToNull();
        setTradeIdToNull();
        setQuoteStatusResponseToToNull();
        setAccountToNull();
        setSideToNull();
        setSettlTypeToNull();
        setPriceToNull();
        setFixedRateToNull();
        setExecuteUnderlyingTradeToNull();
        setDaysToSettlementToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "QuoteStatusReport402";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("QuoteStatusReport402");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (text().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>().
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
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const QuoteStatusReport402& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const QuoteStatusReport402& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Access helper.
    struct textAccess
    {
        TextEncoding&
        operator()(
            const QuoteStatusReport402& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    tail<MemoEncoding>().
                    head<TextEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setTextToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(textAccess(), *this);

        return *this;
    }
};

/// Quote message is used as the response to a QuoteRequest message, tradeable, and restricted tradeable quoting markets.
ONIXS_B3_BOE_LTWT_STRUCT
Quote403
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef Quote403 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 403 };

    /// Initializes a blank instance.
    Quote403() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    Quote403(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    Quote403(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    Quote403(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    Quote403(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    Quote403(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = TermoQuote.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::Quote;
    }

    /// Message type = TermoQuote.

    /// Common header to all bidirectional business messages.
    ONIXS_B3_BOE_NODISCARD
    const BidirectionalBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Common header to all bidirectional business messages.
    BidirectionalBusinessHeader&
    businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for quote request.
    ONIXS_B3_BOE_NODISCARD
    QuoteReqID quoteReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<QuoteReqID>(offset);
    }

    /// Unique identifier for quote request.
    ThisType& setQuoteReqId(QuoteReqID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier for quote.
    ONIXS_B3_BOE_NODISCARD
    QuoteID quoteId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<QuoteID>(offset);
    }

    /// Unique identifier for quote.
    ThisType& setQuoteId(QuoteID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(Price8Optional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return decimal(value, offset, NullPrice8Optional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(Price8Optional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, NullPrice8Optional());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    Quantity orderQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<Quantity>(offset);
    }

    /// Quantity ordered.
    ThisType& setOrderQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ONIXS_B3_BOE_NODISCARD
    SettlType::Enum settlType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        return enumeration<SettlType>(offset);
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ThisType& setSettlType(SettlType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        setEnumeration<SettlType>(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 74;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 74;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 84;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef executingTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 89;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 89;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Interest rate of the forward trade.
    ONIXS_B3_BOE_NODISCARD
    Percentage8 fixedRate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 94;

        return decimal<Percentage8>(offset);
    }

    /// Interest rate of the forward trade.
    ThisType& setFixedRate(Percentage8 value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 94;

        setOrdinary(offset, value);
        return *this;
    }

    /// Specifies if a simultaneous trade of the underlying is to
    /// be performed.Required to indicate Termo Vista and Termo
    /// Vista Registered.
    ONIXS_B3_BOE_NODISCARD
    bool
    executeUnderlyingTrade(
        ExecuteUnderlyingTrade::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 102;

        return enumeration<ExecuteUnderlyingTrade>(value, offset, NullChar());
    }

    /// Specifies if a simultaneous trade of the underlying is to
    /// be performed.Required to indicate Termo Vista and Termo
    /// Vista Registered.
    ThisType&
    setExecuteUnderlyingTrade(
        ExecuteUnderlyingTrade::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 102;

        setEnumeration<ExecuteUnderlyingTrade>(offset, value);
        return *this;
    }

    ThisType& setExecuteUnderlyingTradeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 102;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static Boolean::Enum privateQuote()
        ONIXS_B3_BOE_NOTHROW
    {
        return Boolean::TrueValue;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ONIXS_B3_BOE_NODISCARD
    DaysToSettlement daysToSettlement() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 103;

        return ordinary<DaysToSettlement>(offset);
    }

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ThisType& setDaysToSettlement(DaysToSettlement value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 103;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account used for associating risk limits (when defined).
    ONIXS_B3_BOE_NODISCARD
    bool tradingSubAccount(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 105;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        return ordinary(value, offset, NullAccountOptional(), since);
    }

    /// Account used for associating risk limits (when defined).
    ThisType& setTradingSubAccount(AccountOptional value)
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 105;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, value, since);
        return *this;
    }

    ThisType& setTradingSubAccountToNull()
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 105;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

        setOrdinary(offset, NullAccountOptional(), since);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength minimalBlockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            (version >= 5)
                ? 109
                : 105;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setPriceToNull();
        setAccountToNull();
        setExecuteUnderlyingTradeToNull();

        if (version() >= 5)
        {
            setTradingSubAccountToNull();
        }

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "Quote403";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("Quote403");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding& operator()(const Quote403& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding& operator()(const Quote403& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// The QuoteCancel message is used to cancel a previous QuoteRequest message.
ONIXS_B3_BOE_LTWT_STRUCT
QuoteCancel404
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef QuoteCancel404 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 404 };

    /// Initializes a blank instance.
    QuoteCancel404() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    QuoteCancel404(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    QuoteCancel404(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    QuoteCancel404(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    QuoteCancel404(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    QuoteCancel404(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = QuoteCancel.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::QuoteCancel;
    }

    /// Message type = QuoteCancel.

    /// Common header to all bidirectional business messages.
    ONIXS_B3_BOE_NODISCARD
    const BidirectionalBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Common header to all bidirectional business messages.
    BidirectionalBusinessHeader&
    businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for quote request.
    ONIXS_B3_BOE_NODISCARD
    bool
    quoteReqId(
        QuoteReqIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary(value, offset, NullQuoteReqIDOptional());
    }

    /// Unique identifier for quote request.
    ThisType& setQuoteReqId(QuoteReqIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setQuoteReqIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullQuoteReqIDOptional());
        return *this;
    }

    /// Unique identifier for quote.
    ONIXS_B3_BOE_NODISCARD
    bool quoteId(QuoteIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary(value, offset, NullQuoteIDOptional());
    }

    /// Unique identifier for quote.
    ThisType& setQuoteId(QuoteIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setQuoteIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, NullQuoteIDOptional());
        return *this;
    }

    /// Identifies the type of quote cancel.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static QuoteCancelType::Enum quoteCancelType()
        ONIXS_B3_BOE_NOTHROW
    {
        return QuoteCancelType::CancelForQuoteId;
    }

    /// Identifies the type of quote cancel.

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef executingTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 63;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 63;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static Boolean::Enum privateQuote()
        ONIXS_B3_BOE_NOTHROW
    {
        return Boolean::TrueValue;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            68;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setQuoteReqIdToNull();
        setQuoteIdToNull();
        setAccountToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "QuoteCancel404";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("QuoteCancel404");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const QuoteCancel404& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const QuoteCancel404& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// The QuoteRequestReject message is used when a QuoteRequest is not accept by B3 due to missing or incorrect details to reject QuoteRequest messages for all quoting models.
ONIXS_B3_BOE_LTWT_STRUCT
QuoteRequestReject405
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef QuoteRequestReject405 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 405 };

    /// Repeating group dimensions.
    /// Entry of SidesEntry repeating group.
    ONIXS_B3_BOE_LTWT_STRUCT
    SidesEntry : SbeGroupEntry
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

        /// This type alias.
        typedef SidesEntry ThisType;

        /// Initializes instance of given
        /// version over given memory block.
        SidesEntry(
            void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Reset all variable-length fields if any.
        ThisType& resetVariableFields()
            ONIXS_B3_BOE_NOTHROW
        {
            return *this;
        }

        /// Reset all variable-length and optional fields if any.
        ThisType& reset()
            ONIXS_B3_BOE_NOTHROW
        {
            setAccountToNull();

            if (version() >= 5)
            {
                setTradingSubAccountToNull();
            }

            resetVariableFields();
            return *this;
        }

        /// Side of order.
        ONIXS_B3_BOE_NODISCARD
        Side::Enum side() const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return enumeration<Side>(offset);
        }

        /// Side of order.
        ThisType& setSide(Side::Enum value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            setEnumeration<Side>(offset, value);
            return *this;
        }

        /// Account mnemonic of the order.
        ONIXS_B3_BOE_NODISCARD
        bool account(AccountOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            return ordinary(value, offset, NullAccountOptional());
        }

        /// Account mnemonic of the order.
        ThisType& setAccount(AccountOptional value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            setOrdinary(offset, value);
            return *this;
        }

        ThisType& setAccountToNull()
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            setOrdinary(offset, NullAccountOptional());
            return *this;
        }

        /// Account used for associating risk limits (when defined).
        ONIXS_B3_BOE_NODISCARD
        bool tradingSubAccount(AccountOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 5;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            return ordinary(value, offset, NullAccountOptional(), since);
        }

        /// Account used for associating risk limits (when defined).
        ThisType& setTradingSubAccount(AccountOptional value)
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 5;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            setOrdinary(offset, value, since);
            return *this;
        }

        ThisType& setTradingSubAccountToNull()
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 5;
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR SchemaVersion since = 5;

            setOrdinary(offset, NullAccountOptional(), since);
            return *this;
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static BlockLength blockLength(SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                minimalBlockLength(version);
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static BlockLength minimalBlockLength(SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                (version >= 5)
                    ? 9
                    : 5;
        }

        /// Entity class name.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_NODISCARD
        ONIXS_B3_BOE_CONSTEXPR
        static const Char* className()
        {
            return "QuoteRequestReject405.SidesEntry";
        }
    };

    /// Repeating group containing SidesEntry entries.
    typedef
    SbeGroup<SidesEntry, GroupSizeEncoding, MessageSize>
    Sides;

    /// Initializes a blank instance.
    QuoteRequestReject405() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    QuoteRequestReject405(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    QuoteRequestReject405(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    QuoteRequestReject405(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    QuoteRequestReject405(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    QuoteRequestReject405(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = QuoteRequestReject.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::QuoteRequestReject;
    }

    /// Message type = QuoteRequestReject.

    /// Common header to all bidirectional business messages.
    ONIXS_B3_BOE_NODISCARD
    const BidirectionalBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Common header to all bidirectional business messages.
    BidirectionalBusinessHeader&
    businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<BidirectionalBusinessHeader>(offset);
    }

    /// Reason Quote was rejected.
    ONIXS_B3_BOE_NODISCARD
    bool quoteRequestRejectReason(RejReasonOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary(value, offset, NullRejReasonOptional());
    }

    /// Reason Quote was rejected.
    ThisType& setQuoteRequestRejectReason(RejReasonOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setQuoteRequestRejectReasonToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, NullRejReasonOptional());
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 24;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for quote request.
    ONIXS_B3_BOE_NODISCARD
    QuoteReqID quoteReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        return ordinary<QuoteReqID>(offset);
    }

    /// Unique identifier for quote request.
    ThisType& setQuoteReqId(QuoteReqID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique identifier for quote.
    ONIXS_B3_BOE_NODISCARD
    bool quoteId(QuoteIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 40;

        return ordinary(value, offset, NullQuoteIDOptional());
    }

    /// Unique identifier for quote.
    ThisType& setQuoteId(QuoteIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 40;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setQuoteIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 40;

        setOrdinary(offset, NullQuoteIDOptional());
        return *this;
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ONIXS_B3_BOE_NODISCARD
    bool tradeId(TradeIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return ordinary(value, offset, NullTradeIDOptional());
    }

    /// Contains the unique identifier for this trade, per
    /// instrument + trading date, as assigned by the exchange.
    ThisType& setTradeId(TradeIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setTradeIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, NullTradeIDOptional());
        return *this;
    }

    /// Broker identifier as assigned by B3 used to indicate the
    /// counterparty brokerage firm in a Forward deal.
    ONIXS_B3_BOE_NODISCARD
    Firm contraBroker() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        return ordinary<Firm>(offset);
    }

    /// Broker identifier as assigned by B3 used to indicate the
    /// counterparty brokerage firm in a Forward deal.
    ThisType& setContraBroker(Firm value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 52;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ONIXS_B3_BOE_NODISCARD
    bool settlType(SettlType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        return enumeration<SettlType>(value, offset, NullChar());
    }

    /// Indicates who in the contract has control over evoking
    /// settlement.
    ThisType& setSettlType(SettlType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        setEnumeration<SettlType>(offset, value);
        return *this;
    }

    ThisType& setSettlTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ONIXS_B3_BOE_NODISCARD
    bool price(Price8Optional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        return decimal(value, offset, NullPrice8Optional());
    }

    /// Price per share or contract. Conditionally required if the
    /// order type requires a price (not market orders and RLP).
    ThisType& setPrice(Price8Optional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPriceToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 70;

        setOrdinary(offset, NullPrice8Optional());
        return *this;
    }

    /// Quantity ordered.
    ONIXS_B3_BOE_NODISCARD
    bool orderQty(QuantityOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;

        return ordinary(value, offset, NullQuantityOptional());
    }

    /// Quantity ordered.
    ThisType& setOrderQty(QuantityOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrderQtyToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;

        setOrdinary(offset, NullQuantityOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 86;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 86;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is executing an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef executingTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is executing an order.
    ThisType& setExecutingTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 96;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Interest rate of the forward trade.
    ONIXS_B3_BOE_NODISCARD
    bool
    fixedRate(
        Percentage8Optional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 101;

        return decimal(value, offset, NullPercentage8Optional());
    }

    /// Interest rate of the forward trade.
    ThisType&
    setFixedRate(
        Percentage8Optional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 101;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setFixedRateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 101;

        setOrdinary(offset, NullPercentage8Optional());
        return *this;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static Boolean::Enum privateQuote()
        ONIXS_B3_BOE_NOTHROW
    {
        return Boolean::TrueValue;
    }

    /// Specifies whether a quote is public, i.e. available to the
    /// market, or private, i.e. available to a specified
    /// counterparty only.

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ONIXS_B3_BOE_NODISCARD
    bool
    daysToSettlement(
        DaysToSettlementOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 109;

        return ordinary(value, offset, NullDaysToSettlementOptional());
    }

    /// Deadline for completing the forward deal. For Common,
    /// Dollar and Index contracts must be between 16 and 999. And
    /// maximum of 90 days for Flexible.
    ThisType&
    setDaysToSettlement(
        DaysToSettlementOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 109;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setDaysToSettlementToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 109;

        setOrdinary(offset, NullDaysToSettlementOptional());
        return *this;
    }

    /// \return instance of Sides repeating group.
    ONIXS_B3_BOE_NODISCARD
    Sides sides() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Sides>(SidesAccess(), *this);
    }

    /// \return instance of Sides repeating group.
    ONIXS_B3_BOE_NODISCARD
    Sides sides()
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Sides>(SidesAccess(), *this);
    }

    /// Setup repeating group with the given number of entries.
    /// Sets all optional fields of the group entries to null.
    /// \return noSides(35511) repeating group.
    Sides sides(Sides::Size length)
    {
        return constructGroup<Sides>(
            SidesAccess(),
            length,
            *this);
    }

    /// Setup repeating group with the given number of entries.
    /// \return noSides(35511) repeating group.
    Sides
    sides(
        Sides::Size length,
        NoFieldsInit)
    {
        return setupGroup<Sides>(
            SidesAccess(),
            length,
            *this);
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Free ASCII format text string.
    ONIXS_B3_BOE_NODISCARD
    StrRef text() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(textAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text string.
    ThisType& setText(StrRef value)
    {
        setVariableLengthField(
            textAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            111;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size) + static_cast<MessageSize>(TextEncoding::Size) + static_cast<MessageSize>(Sides::EmptySize);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setSidesToNull();
        setDeskIdToNull();
        setMemoToNull();
        setTextToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setQuoteRequestRejectReasonToNull();
        setQuoteIdToNull();
        setTradeIdToNull();
        setSettlTypeToNull();
        setPriceToNull();
        setOrderQtyToNull();
        setFixedRateToNull();
        setDaysToSettlementToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "QuoteRequestReject405";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("QuoteRequestReject405");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (text().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkVariableLengthFields<Sides>().
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>().
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
    struct SidesAccess
    {
        Sides
        operator()(
            const QuoteRequestReject405& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    head<Sides>();
        }
    };

    /// Reset an instance of the repeating group.
    /// All the following data will be invalidated.
    void setSidesToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        resetGroup<Sides>(SidesAccess(), *this);
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const QuoteRequestReject405& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Sides>().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const QuoteRequestReject405& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Sides>().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Access helper.
    struct textAccess
    {
        TextEncoding&
        operator()(
            const QuoteRequestReject405& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Sides>().
                    tail<DeskIDEncoding>().
                    tail<MemoEncoding>().
                    head<TextEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setTextToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(textAccess(), *this);

        return *this;
    }
};

/// PositionMaintenanceCancelRequest is a solicited cancel of PositionMaintenance message sent by client.
ONIXS_B3_BOE_LTWT_STRUCT
PositionMaintenanceCancelRequest501
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef PositionMaintenanceCancelRequest501 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 501 };

    /// Initializes a blank instance.
    PositionMaintenanceCancelRequest501() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    PositionMaintenanceCancelRequest501(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    PositionMaintenanceCancelRequest501(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    PositionMaintenanceCancelRequest501(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    PositionMaintenanceCancelRequest501(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    PositionMaintenanceCancelRequest501(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = PositionMaintenanceCancelRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::PositionMaintenanceCancelRequest;
    }

    /// Message type = PositionMaintenanceCancelRequest.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Unique identifier for the position maintenance request.
    ONIXS_B3_BOE_NODISCARD
    PosReqID posReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary<PosReqID>(offset);
    }

    /// Unique identifier for the position maintenance request.
    ThisType& setPosReqId(PosReqID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Reference to the PosReqID (710) of a previous maintenance
    /// request that is being cancelled.
    ONIXS_B3_BOE_NODISCARD
    bool origPosReqRefId(PosReqIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        return ordinary(value, offset, NullPosReqIDOptional());
    }

    /// Reference to the PosReqID (710) of a previous maintenance
    /// request that is being cancelled.
    ThisType& setOrigPosReqRefId(PosReqIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigPosReqRefIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setOrdinary(offset, NullPosReqIDOptional());
        return *this;
    }

    /// Reference to a PosMaintRptID (721) from a previous
    /// Position Maintenance Report that is being cancelled.
    ONIXS_B3_BOE_NODISCARD
    bool
    posMaintRptRefId(
        PosMaintRptIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        return ordinary(value, offset, NullPosMaintRptIDOptional());
    }

    /// Reference to a PosMaintRptID (721) from a previous
    /// Position Maintenance Report that is being cancelled.
    ThisType&
    setPosMaintRptRefId(
        PosMaintRptIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPosMaintRptRefIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        setOrdinary(offset, NullPosMaintRptIDOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 50;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 50;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            65;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setOrigPosReqRefIdToNull();
        setPosMaintRptRefIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "PositionMaintenanceCancelRequest501";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "PositionMaintenanceCancelRequest501");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// PositionMaintenanceRequest message allows the position owner (holder) to submit requests which will affect the position. Generally, the holder of the position or clearing organization is a central party but can also be a party providing investment services.
ONIXS_B3_BOE_LTWT_STRUCT
PositionMaintenanceRequest502
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef PositionMaintenanceRequest502 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 502 };

    /// Initializes a blank instance.
    PositionMaintenanceRequest502() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    PositionMaintenanceRequest502(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    PositionMaintenanceRequest502(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    PositionMaintenanceRequest502(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    PositionMaintenanceRequest502(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    PositionMaintenanceRequest502(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = PositionMaintenanceRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::PositionMaintenanceRequest;
    }

    /// Message type = PositionMaintenanceRequest.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Unique identifier for the position maintenance request.
    ONIXS_B3_BOE_NODISCARD
    PosReqID posReqId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary<PosReqID>(offset);
    }

    /// Unique identifier for the position maintenance request.
    ThisType& setPosReqId(PosReqID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Used to indicate the minimum acceptable offset between the
    /// Strike Price and the Market Price.
    ONIXS_B3_BOE_NODISCARD
    bool
    thresholdAmount(
        PriceOffsetOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        return decimal(value, offset, NullPriceOffsetOptional());
    }

    /// Used to indicate the minimum acceptable offset between the
    /// Strike Price and the Market Price.
    ThisType&
    setThresholdAmount(
        PriceOffsetOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setThresholdAmountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setOrdinary(offset, NullPriceOffsetOptional());
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the type of position transaction.
    ONIXS_B3_BOE_NODISCARD
    PosTransType::Enum posTransType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return enumeration<PosTransType>(offset);
    }

    /// Identifies the type of position transaction.
    ThisType& setPosTransType(PosTransType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setEnumeration<PosTransType>(offset, value);
        return *this;
    }

    /// The 'Clearing Business Date' referred to by this request.
    /// It must be set with the current date.
    ONIXS_B3_BOE_NODISCARD
    Timestamp clearingBusinessDate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// The 'Clearing Business Date' referred to by this request.
    /// It must be set with the current date.
    ThisType& setClearingBusinessDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    /// Used to indicate when a contrary instruction for exercise
    /// or abandonment is being submitted: The exercise should not
    /// happen to an ITM position or it should happen to an ATM or
    /// OTM position, always using the values of tags
    /// 709-PosTransType and 712-PosMaintAction to determine which
    /// operation will take place. Should not be submitted when
    /// false.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum contraryInstructionIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        return enumeration<Boolean>(offset);
    }

    /// Used to indicate when a contrary instruction for exercise
    /// or abandonment is being submitted: The exercise should not
    /// happen to an ITM position or it should happen to an ATM or
    /// OTM position, always using the values of tags
    /// 709-PosTransType and 712-PosMaintAction to determine which
    /// operation will take place. Should not be submitted when
    /// false.
    ThisType& setContraryInstructionIndicator(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 59;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Used to identify the type of quantity.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static PosType::Enum posType()
        ONIXS_B3_BOE_NOTHROW
    {
        return PosType::OptionExerciseQty;
    }

    /// Used to identify the type of quantity.

    /// Long quantity.
    ONIXS_B3_BOE_NODISCARD
    Quantity longQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 65;

        return ordinary<Quantity>(offset);
    }

    /// Long quantity.
    ThisType& setLongQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 65;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            73;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setThresholdAmountToNull();
        setAccountToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "PositionMaintenanceRequest502";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "PositionMaintenanceRequest502");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const PositionMaintenanceRequest502& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const PositionMaintenanceRequest502& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// PositionMaintenanceReport message is sent owner of a position (holder) in response to a PositionMaintenanceRequest message and is used to confirm that a request has been successfully processed or rejected.
ONIXS_B3_BOE_LTWT_STRUCT
PositionMaintenanceReport503
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef PositionMaintenanceReport503 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 503 };

    /// Repeating group dimensions.
    /// Entry of PositionsEntry repeating group.
    ONIXS_B3_BOE_LTWT_STRUCT
    PositionsEntry : SbeGroupEntry
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

        /// This type alias.
        typedef PositionsEntry ThisType;

        /// Initializes instance of given
        /// version over given memory block.
        PositionsEntry(
            void* data,
            EncodedLength length,
            SchemaVersion version)
          : Base(data, numericCast<Base::BlockLength>(length), version)
        {
            assert(version >= Schema::MinimalVersion);
            assert(length >= minimalBlockLength(version));
        }

        /// Reset all variable-length fields if any.
        ThisType& resetVariableFields()
            ONIXS_B3_BOE_NOTHROW
        {
            return *this;
        }

        /// Reset all variable-length and optional fields if any.
        ThisType& reset()
            ONIXS_B3_BOE_NOTHROW
        {
            setLongQtyToNull();
            setShortQtyToNull();

            resetVariableFields();
            return *this;
        }

        /// Used to identify the type of quantity.
        ONIXS_B3_BOE_NODISCARD
        PosType::Enum posType() const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            return enumeration<PosType>(offset);
        }

        /// Used to identify the type of quantity.
        ThisType& setPosType(PosType::Enum value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

            setEnumeration<PosType>(offset, value);
            return *this;
        }

        /// Long Quantity.
        ONIXS_B3_BOE_NODISCARD
        bool longQty(QuantityOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            return ordinary(value, offset, NullQuantityOptional());
        }

        /// Long Quantity.
        ThisType& setLongQty(QuantityOptional value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            setOrdinary(offset, value);
            return *this;
        }

        ThisType& setLongQtyToNull()
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 1;

            setOrdinary(offset, NullQuantityOptional());
            return *this;
        }

        /// Short Quantity.
        ONIXS_B3_BOE_NODISCARD
        bool shortQty(QuantityOptional& value) const
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 9;

            return ordinary(value, offset, NullQuantityOptional());
        }

        /// Short Quantity.
        ThisType& setShortQty(QuantityOptional value)
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 9;

            setOrdinary(offset, value);
            return *this;
        }

        ThisType& setShortQtyToNull()
            ONIXS_B3_BOE_NOTHROW
        {
            ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 9;

            setOrdinary(offset, NullQuantityOptional());
            return *this;
        }

        /// \return size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static BlockLength blockLength(SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                minimalBlockLength(version);
        }

        /// \return minimal size of entry body in bytes
        /// for given version of message template.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_CONSTEXPR
        static
        BlockLength
        minimalBlockLength(
            ONIXS_B3_BOE_UNUSED SchemaVersion version)
            ONIXS_B3_BOE_NOTHROW
        {
            return
                ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
                17;
        }

        /// Entity class name.
        ONIXS_B3_BOE_LTWT_EXPORTED
        ONIXS_B3_BOE_NODISCARD
        ONIXS_B3_BOE_CONSTEXPR
        static const Char* className()
        {
            return "PositionMaintenanceReport503.PositionsEntry";
        }
    };

    /// Repeating group containing PositionsEntry entries.
    typedef
    SbeGroup<PositionsEntry, GroupSizeEncoding, MessageSize>
    Positions;

    /// Initializes a blank instance.
    PositionMaintenanceReport503() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    PositionMaintenanceReport503(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    PositionMaintenanceReport503(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    PositionMaintenanceReport503(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    PositionMaintenanceReport503(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    PositionMaintenanceReport503(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = PositionMaintenanceReport.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::PositionMaintenanceReport;
    }

    /// Message type = PositionMaintenanceReport.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Unique identifier for the position maintenance request.
    ONIXS_B3_BOE_NODISCARD
    bool posReqId(PosReqIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary(value, offset, NullPosReqIDOptional());
    }

    /// Unique identifier for the position maintenance request.
    ThisType& setPosReqId(PosReqIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPosReqIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, NullPosReqIDOptional());
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for this position report.
    ONIXS_B3_BOE_NODISCARD
    PosMaintRptID posMaintRptId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        return ordinary<PosMaintRptID>(offset);
    }

    /// Unique identifier for this position report.
    ThisType& setPosMaintRptId(PosMaintRptID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the type of position transaction.
    ONIXS_B3_BOE_NODISCARD
    PosTransType::Enum posTransType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        return enumeration<PosTransType>(offset);
    }

    /// Identifies the type of position transaction.
    ThisType& setPosTransType(PosTransType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        setEnumeration<PosTransType>(offset, value);
        return *this;
    }

    /// Maintenance Action to be performed.
    ONIXS_B3_BOE_NODISCARD
    PosMaintAction::Enum posMaintAction() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 43;

        return enumeration<PosMaintAction>(offset);
    }

    /// Maintenance Action to be performed.
    ThisType&
    setPosMaintAction(
        PosMaintAction::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 43;

        setEnumeration<PosMaintAction>(offset, value);
        return *this;
    }

    /// Status of Position Maintenance Request.
    ONIXS_B3_BOE_NODISCARD
    PosMaintStatus::Enum posMaintStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return enumeration<PosMaintStatus>(offset);
    }

    /// Status of Position Maintenance Request.
    ThisType&
    setPosMaintStatus(
        PosMaintStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setEnumeration<PosMaintStatus>(offset, value);
        return *this;
    }

    /// The unique ID assigned to the trade entity once it is
    /// received or matched by the exchange or central
    /// counterparty.
    ONIXS_B3_BOE_NODISCARD
    bool tradeId(TradeIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        return ordinary(value, offset, NullTradeIDOptional());
    }

    /// The unique ID assigned to the trade entity once it is
    /// received or matched by the exchange or central
    /// counterparty.
    ThisType& setTradeId(TradeIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setTradeIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        setOrdinary(offset, NullTradeIDOptional());
        return *this;
    }

    /// Reference to the PosReqID (710) of a previous maintenance
    /// request that is being cancelled.
    ONIXS_B3_BOE_NODISCARD
    bool origPosReqRefId(PosReqIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 49;

        return ordinary(value, offset, NullPosReqIDOptional());
    }

    /// Reference to the PosReqID (710) of a previous maintenance
    /// request that is being cancelled.
    ThisType& setOrigPosReqRefId(PosReqIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 49;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrigPosReqRefIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 49;

        setOrdinary(offset, NullPosReqIDOptional());
        return *this;
    }

    /// Type of account associated with an order.
    ONIXS_B3_BOE_NODISCARD
    bool accountType(AccountType::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        return enumeration<AccountType>(value, offset, NullUint8EnumEncoding());
    }

    /// Type of account associated with an order.
    ThisType& setAccountType(AccountType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setEnumeration<AccountType>(offset, value);
        return *this;
    }

    ThisType& setAccountTypeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// The 'Clearing Business Date' referred to by this request.
    /// It must be set with the current date.
    ONIXS_B3_BOE_NODISCARD
    Timestamp clearingBusinessDate() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        return localMktDateToTimestamp(ordinary<LocalMktDate>(offset));
    }

    /// The 'Clearing Business Date' referred to by this request.
    /// It must be set with the current date.
    ThisType& setClearingBusinessDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    /// Used to indicate the minimum acceptable offset between the
    /// Strike Price and the Market Price.
    ONIXS_B3_BOE_NODISCARD
    bool
    thresholdAmount(
        PriceOffsetOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return decimal(value, offset, NullPriceOffsetOptional());
    }

    /// Used to indicate the minimum acceptable offset between the
    /// Strike Price and the Market Price.
    ThisType&
    setThresholdAmount(
        PriceOffsetOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setThresholdAmountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, NullPriceOffsetOptional());
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setOrdinary(offset, value);
        return *this;
    }

    /// Account mnemonic of the order.
    ONIXS_B3_BOE_NODISCARD
    bool account(AccountOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        return ordinary(value, offset, NullAccountOptional());
    }

    /// Account mnemonic of the order.
    ThisType& setAccount(AccountOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAccountToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 76;

        setOrdinary(offset, NullAccountOptional());
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 80;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies reason for rejection. Required when
    /// PosMaintStatus = 2.
    ONIXS_B3_BOE_NODISCARD
    bool posMaintResult(RejReasonOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 90;

        return ordinary(value, offset, NullRejReasonOptional());
    }

    /// Identifies reason for rejection. Required when
    /// PosMaintStatus = 2.
    ThisType& setPosMaintResult(RejReasonOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 90;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setPosMaintResultToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 90;

        setOrdinary(offset, NullRejReasonOptional());
        return *this;
    }

    /// Used to indicate when a contrary instruction for exercise
    /// or abandonment is being submitted :The exercise should not
    /// happen to an ITM position or it should happen to an ATM or
    /// OTM position, always using the values of tags
    /// 709-PosTransType and 712-PosMaintAction to determine which
    /// operation will take place. Should not be submitted when
    /// false.
    ONIXS_B3_BOE_NODISCARD
    Boolean::Enum contraryInstructionIndicator() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 94;

        return enumeration<Boolean>(offset);
    }

    /// Used to indicate when a contrary instruction for exercise
    /// or abandonment is being submitted :The exercise should not
    /// happen to an ITM position or it should happen to an ATM or
    /// OTM position, always using the values of tags
    /// 709-PosTransType and 712-PosMaintAction to determine which
    /// operation will take place. Should not be submitted when
    /// false.
    ThisType& setContraryInstructionIndicator(Boolean::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 94;

        setEnumeration<Boolean>(offset, value);
        return *this;
    }

    /// \return instance of Positions repeating group.
    ONIXS_B3_BOE_NODISCARD
    Positions positions() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Positions>(PositionsAccess(), *this);
    }

    /// \return instance of Positions repeating group.
    ONIXS_B3_BOE_NODISCARD
    Positions positions()
        ONIXS_B3_BOE_NOTHROW
    {
        return getGroup<Positions>(PositionsAccess(), *this);
    }

    /// Setup repeating group with the given number of entries.
    /// Sets all optional fields of the group entries to null.
    /// \return noPositions(702) repeating group.
    Positions positions(Positions::Size length)
    {
        return constructGroup<Positions>(
            PositionsAccess(),
            length,
            *this);
    }

    /// Setup repeating group with the given number of entries.
    /// \return noPositions(702) repeating group.
    Positions
    positions(
        Positions::Size length,
        NoFieldsInit)
    {
        return setupGroup<Positions>(
            PositionsAccess(),
            length,
            *this);
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Free ASCII format text string.
    ONIXS_B3_BOE_NODISCARD
    StrRef text() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(textAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text string.
    ThisType& setText(StrRef value)
    {
        setVariableLengthField(
            textAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            95;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size) + static_cast<MessageSize>(TextEncoding::Size) + static_cast<MessageSize>(Positions::EmptySize);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setPositionsToNull();
        setDeskIdToNull();
        setMemoToNull();
        setTextToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setPosReqIdToNull();
        setTradeIdToNull();
        setOrigPosReqRefIdToNull();
        setAccountTypeToNull();
        setThresholdAmountToNull();
        setAccountToNull();
        setPosMaintResultToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "PositionMaintenanceReport503";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "PositionMaintenanceReport503");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (text().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkVariableLengthFields<Positions>().
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>().
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
    struct PositionsAccess
    {
        Positions
        operator()(
            const PositionMaintenanceReport503& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    head<Positions>();
        }
    };

    /// Reset an instance of the repeating group.
    /// All the following data will be invalidated.
    void setPositionsToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        resetGroup<Positions>(PositionsAccess(), *this);
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const PositionMaintenanceReport503& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Positions>().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const PositionMaintenanceReport503& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Positions>().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Access helper.
    struct textAccess
    {
        TextEncoding&
        operator()(
            const PositionMaintenanceReport503& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                groups().
                    variableLengthFields<Positions>().
                    tail<DeskIDEncoding>().
                    tail<MemoEncoding>().
                    head<TextEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setTextToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(textAccess(), *this);

        return *this;
    }
};

/// AllocationInstruction message submits a request to allocate (fully or partially) a non-allocated trade to block an issuer position, preventing it to be assigned to an exercise executed by a holder during current session.
ONIXS_B3_BOE_LTWT_STRUCT
AllocationInstruction601
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef AllocationInstruction601 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 601 };

    /// Initializes a blank instance.
    AllocationInstruction601() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    AllocationInstruction601(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    AllocationInstruction601(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    AllocationInstruction601(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    AllocationInstruction601(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    AllocationInstruction601(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = AllocationInstruction.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::AllocationInstruction;
    }

    /// Message type = AllocationInstruction.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Unique identifier for this allocation instruction message.
    ONIXS_B3_BOE_NODISCARD
    AllocID allocId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary<AllocID>(offset);
    }

    /// Unique identifier for this allocation instruction message.
    ThisType& setAllocId(AllocID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Identifies allocation transaction type.
    ONIXS_B3_BOE_NODISCARD
    AllocTransType::Enum allocTransType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        return enumeration<AllocTransType>(offset);
    }

    /// Identifies allocation transaction type.
    ThisType&
    setAllocTransType(
        AllocTransType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setEnumeration<AllocTransType>(offset, value);
        return *this;
    }

    /// Describes the specific type or purpose of an Allocation
    /// message.
    ONIXS_B3_BOE_NODISCARD
    AllocType::Enum allocType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 35;

        return enumeration<AllocType>(offset);
    }

    /// Describes the specific type or purpose of an Allocation
    /// message.
    ThisType& setAllocType(AllocType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 35;

        setEnumeration<AllocType>(offset, value);
        return *this;
    }

    /// Indicates how the orders being booked and allocated by an
    /// Allocation Instruction.
    ONIXS_B3_BOE_NODISCARD
    AllocNoOrdersType::Enum allocNoOrdersType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return enumeration<AllocNoOrdersType>(offset);
    }

    /// Indicates how the orders being booked and allocated by an
    /// Allocation Instruction.
    ThisType&
    setAllocNoOrdersType(
        AllocNoOrdersType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setEnumeration<AllocNoOrdersType>(offset, value);
        return *this;
    }

    /// Overall/total quantity (e.g. number of shares).
    ONIXS_B3_BOE_NODISCARD
    Quantity quantity() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 37;

        return ordinary<Quantity>(offset);
    }

    /// Overall/total quantity (e.g. number of shares).
    ThisType& setQuantity(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 37;

        setOrdinary(offset, value);
        return *this;
    }

    /// Side of order.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static Side::Enum side()
        ONIXS_B3_BOE_NOTHROW
    {
        return Side::Buy;
    }

    /// Side of order.

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 55;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 55;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// The unique ID assigned to the trade entity once it is
    /// received or matched by the exchange or central
    /// counterparty.
    ONIXS_B3_BOE_NODISCARD
    TradeID tradeId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<TradeID>(offset);
    }

    /// The unique ID assigned to the trade entity once it is
    /// received or matched by the exchange or central
    /// counterparty.
    ThisType& setTradeId(TradeID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ONIXS_B3_BOE_NODISCARD
    bool tradeDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ThisType& setTradeDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setTradeDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Unique identifier for a specific NoAllocs (78) repeating
    /// group instance (e.g. for an AllocAccount).
    ONIXS_B3_BOE_NODISCARD
    AllocID individualAllocId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 66;

        return ordinary<AllocID>(offset);
    }

    /// Unique identifier for a specific NoAllocs (78) repeating
    /// group instance (e.g. for an AllocAccount).
    ThisType& setIndividualAllocId(AllocID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 66;

        setOrdinary(offset, value);
        return *this;
    }

    /// Sub-account mnemonic.
    ONIXS_B3_BOE_NODISCARD
    Account allocAccount() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 74;

        return ordinary<Account>(offset);
    }

    /// Sub-account mnemonic.
    ThisType& setAllocAccount(Account value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 74;

        setOrdinary(offset, value);
        return *this;
    }

    /// Quantity allocated to specific sub-account.
    ONIXS_B3_BOE_NODISCARD
    Quantity allocQty() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;

        return ordinary<Quantity>(offset);
    }

    /// Quantity allocated to specific sub-account.
    ThisType& setAllocQty(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 78;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the trading desk.
    ONIXS_B3_BOE_NODISCARD
    StrRef deskId() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(deskIDAccess(), *this);
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ONIXS_B3_BOE_NODISCARD
    StrRef memo() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(memoAccess(), *this);
    }

    /// Identifies the trading desk.
    ThisType& setDeskId(StrRef value)
    {
        setVariableLengthField(
            deskIDAccess(),
            value,
            *this);

        return *this;
    }

    /// Free ASCII format text field. This field may be used to convey client's relevant info. It's always echoed in the reports.
    ThisType& setMemo(StrRef value)
    {
        setVariableLengthField(
            memoAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            86;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(DeskIDEncoding::Size) + static_cast<MessageSize>(MemoEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setDeskIdToNull();
        setMemoToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setTradeDateToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "AllocationInstruction601";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "AllocationInstruction601");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (memo().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
            checkTail<DeskIDEncoding>().
            checkTail<MemoEncoding>();
    }

    void checkCompatibility() const
    {
        assert(TemplateId == templateId());

        checkSchema<Schema>(schemaId(), version());
        checkLength(bufferSize(), version());
        checkVarLenFields();
    }

    /// Access helper.
    struct deskIDAccess
    {
        DeskIDEncoding&
        operator()(
            const AllocationInstruction601& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<DeskIDEncoding>();
        }
    };

    /// Access helper.
    struct memoAccess
    {
        MemoEncoding&
        operator()(
            const AllocationInstruction601& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    tail<DeskIDEncoding>().
                    head<MemoEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setDeskIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(deskIDAccess(), *this);

        return *this;
    }

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setMemoToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(memoAccess(), *this);

        return *this;
    }
};

/// AllocationReport message is as response of AllocationInstruction message.
ONIXS_B3_BOE_LTWT_STRUCT
AllocationReport602
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef AllocationReport602 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 602 };

    /// Initializes a blank instance.
    AllocationReport602() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    AllocationReport602(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    AllocationReport602(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    AllocationReport602(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    AllocationReport602(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    AllocationReport602(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = AllocationReport.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::AllocationReport;
    }

    /// Message type = AllocationReport.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Unique identifier for this allocation instruction message.
    ONIXS_B3_BOE_NODISCARD
    AllocID allocId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return ordinary<AllocID>(offset);
    }

    /// Unique identifier for this allocation instruction message.
    ThisType& setAllocId(AllocID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setOrdinary(offset, value);
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    SecurityID securityId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        return ordinary<SecurityID>(offset);
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 26;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier for this message.
    ONIXS_B3_BOE_NODISCARD
    AllocReportID allocReportId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        return ordinary<AllocReportID>(offset);
    }

    /// Unique identifier for this message.
    ThisType& setAllocReportId(AllocReportID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 34;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies allocation transaction type.
    ONIXS_B3_BOE_NODISCARD
    AllocTransType::Enum allocTransType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        return enumeration<AllocTransType>(offset);
    }

    /// Identifies allocation transaction type.
    ThisType&
    setAllocTransType(
        AllocTransType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 42;

        setEnumeration<AllocTransType>(offset, value);
        return *this;
    }

    /// Describes the specific type or purpose of an Allocation
    /// Report message.
    ONIXS_B3_BOE_NODISCARD
    AllocReportType::Enum allocReportType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 43;

        return enumeration<AllocReportType>(offset);
    }

    /// Describes the specific type or purpose of an Allocation
    /// Report message.
    ThisType&
    setAllocReportType(
        AllocReportType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 43;

        setEnumeration<AllocReportType>(offset, value);
        return *this;
    }

    /// Indicates how the orders being booked and allocated by an
    /// Allocation Instruction.
    ONIXS_B3_BOE_NODISCARD
    AllocNoOrdersType::Enum allocNoOrdersType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return enumeration<AllocNoOrdersType>(offset);
    }

    /// Indicates how the orders being booked and allocated by an
    /// Allocation Instruction.
    ThisType&
    setAllocNoOrdersType(
        AllocNoOrdersType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setEnumeration<AllocNoOrdersType>(offset, value);
        return *this;
    }

    /// Identifies reason for rejection.
    ONIXS_B3_BOE_NODISCARD
    bool allocRejCode(RejReasonOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        return ordinary(value, offset, NullRejReasonOptional());
    }

    /// Identifies reason for rejection.
    ThisType& setAllocRejCode(RejReasonOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setAllocRejCodeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        setOrdinary(offset, NullRejReasonOptional());
        return *this;
    }

    /// Overall/total quantity (e.g. number of shares).
    ONIXS_B3_BOE_NODISCARD
    Quantity quantity() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 49;

        return ordinary<Quantity>(offset);
    }

    /// Overall/total quantity (e.g. number of shares).
    ThisType& setQuantity(Quantity value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 49;

        setOrdinary(offset, value);
        return *this;
    }

    /// Identifies status of allocation.
    ONIXS_B3_BOE_NODISCARD
    AllocStatus::Enum allocStatus() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        return enumeration<AllocStatus>(offset);
    }

    /// Identifies status of allocation.
    ThisType& setAllocStatus(AllocStatus::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 57;

        setEnumeration<AllocStatus>(offset, value);
        return *this;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ONIXS_B3_BOE_NODISCARD
    bool tradeDate(Timestamp& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        typedef LocalMktDateOptional FieldValue;

        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        FieldValue fieldValue;

        if (ordinary(fieldValue, offset, NullLocalMktDateOptional()))
        {
            value = localMktDateToTimestamp(fieldValue);
            return true;
        }
        return false;
    }

    /// Indicates date of trading day (expressed in local time at
    /// place of trade). Sent in number of days since Unix epoch.
    ThisType& setTradeDate(Timestamp value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setOrdinary(offset, timestampToLocalMktDate(value));
        return *this;
    }

    ThisType& setTradeDateToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 58;

        setOrdinary(offset, NullLocalMktDateOptional());
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 60;

        setOrdinary(offset, value);
        return *this;
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    Side::Enum side() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        return enumeration<Side>(offset);
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 68;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    /// Identifies the original location for routing orders.
    ONIXS_B3_BOE_NODISCARD
    StrRef senderLocation() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        return fixedStr<length>(offset);
    }

    /// Identifies the original location for routing orders.
    ThisType& setSenderLocation(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 69;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 10;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Identifies the trader who is inserting an order.
    ONIXS_B3_BOE_NODISCARD
    StrRef enteringTrader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 79;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        return fixedStr<length>(offset);
    }

    /// Identifies the trader who is inserting an order.
    ThisType& setEnteringTrader(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 79;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 5;

        setFixedStr<length>(offset, value);
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            84;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static BlockLength blockLength(SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setAllocRejCodeToNull();
        setTradeDateToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "AllocationReport602";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("AllocationReport602");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// OrderMassActionRequest is sent by the client system to cancel working orders that belongs to a defined criteria as per client definition.
ONIXS_B3_BOE_LTWT_STRUCT
OrderMassActionRequest701
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef OrderMassActionRequest701 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 701 };

    /// Initializes a blank instance.
    OrderMassActionRequest701() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    OrderMassActionRequest701(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    OrderMassActionRequest701(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    OrderMassActionRequest701(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    OrderMassActionRequest701(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    OrderMassActionRequest701(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = OrderMassActionRequest.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::OrderMassActionRequest;
    }

    /// Message type = OrderMassActionRequest.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const InboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    InboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<InboundBusinessHeader>(offset);
    }

    /// Specifies the type of action requested.
    ONIXS_B3_BOE_NODISCARD
    MassActionType::Enum massActionType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<MassActionType>(offset);
    }

    /// Specifies the type of action requested.
    ThisType&
    setMassActionType(
        MassActionType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<MassActionType>(offset, value);
        return *this;
    }

    /// Specifies the scope of the action.
    ONIXS_B3_BOE_NODISCARD
    bool
    massActionScope(
        MassActionScope::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<MassActionScope>(value, offset, NullUint8EnumEncoding());
    }

    /// Specifies the scope of the action.
    ThisType&
    setMassActionScope(
        MassActionScope::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<MassActionScope>(offset, value);
        return *this;
    }

    ThisType& setMassActionScopeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Used to communicate event type which triggers the Order
    /// Mass Action Request.
    ONIXS_B3_BOE_NODISCARD
    bool
    execRestatementReason(
        ExecRestatementReasonValidForMassCancel::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return enumeration<ExecRestatementReasonValidForMassCancel>(value, offset, NullUint8EnumEncoding());
    }

    /// Used to communicate event type which triggers the Order
    /// Mass Action Request.
    ThisType&
    setExecRestatementReason(
        ExecRestatementReasonValidForMassCancel::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setEnumeration<ExecRestatementReasonValidForMassCancel>(offset, value);
        return *this;
    }

    ThisType& setExecRestatementReasonToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 29;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 29;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 29;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    bool side(Side::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 30;

        return enumeration<Side>(value, offset, NullChar());
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 30;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    ThisType& setSideToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 30;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Asset associated with the security, such as DOL, BGI, OZ1,
    /// WDL, CNI, etc.
    ONIXS_B3_BOE_NODISCARD
    bool asset(StrRef& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 6;

        return fixedStr<length>(value, offset);
    }

    /// Asset associated with the security, such as DOL, BGI, OZ1,
    /// WDL, CNI, etc.
    ThisType& setAsset(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 6;

        setFixedStr<length>(offset, value);
        return *this;
    }

    ThisType& setAssetToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 32;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 6;

        setFixedStr<length>(offset, StrRef());
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    bool
    securityId(
        SecurityIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 38;

        return ordinary(value, offset, NullSecurityIDOptional());
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 38;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setSecurityIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 38;

        setOrdinary(offset, NullSecurityIDOptional());
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier of investor for mass cancel on behalf
    /// purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for mass cancel on behalf
    /// purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            54;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            0;
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            static_cast<UInt64>(MessageHeaderBuilder::Size) +
            blockLength(Schema::Version);
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setMassActionScopeToNull();
        setExecRestatementReasonToNull();
        setOrdTagIdToNull();
        setSideToNull();
        setAssetToNull();
        setSecurityIdToNull();
        setInvestorIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "OrderMassActionRequest701";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "OrderMassActionRequest701");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                advanceByBytes(
                    binary(),
                    static_cast<ptrdiff_t>(SbeMessage::blockLength()) +
                        MessageHeader::Size));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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

/// OrderMassActionReport message is used to acknowledge an OrderMassActionRequest message.
ONIXS_B3_BOE_LTWT_STRUCT
OrderMassActionReport702
: SbeMessage
{
    /// Used template schema.
    typedef SchemaTraits Schema;

    /// This type alias.
    typedef OrderMassActionReport702 ThisType;

    /// Message template ID from SBE schema.
    enum { TemplateId = 702 };

    /// Initializes a blank instance.
    OrderMassActionReport702() ONIXS_B3_BOE_DEFAULT;

    /// Initializes an instance over the given memory block.
    OrderMassActionReport702(
        void* data,
        EncodedLength length,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        reset();
    }

    /// Initializes an instance over the given memory block
    /// With no variable-length fields initialization
    /// It is assumed that the user does such an initialization manually.
    OrderMassActionReport702(
        void* data,
        EncodedLength length,
        NoFieldsInit,
        SchemaVersion version = Schema::Version)
      : SbeMessage(data, length, version)
    {
        checkVersion<Schema>(version);
        checkLength(length, version);
        init(TemplateId, minimalBlockLength(version), blockLength(version), Schema::Id);
        resetVariableFields();
    }

    /// Creates an instance over the given memory block.
    OrderMassActionReport702(
        void* data,
        EncodedLength length,
        NoInit)
      : SbeMessage(data, length)
    {
        checkCompatibility();
    }

    /// Creates an instance over the given SBE message.
    explicit
    OrderMassActionReport702(
        const SbeMessage& message)
      : SbeMessage(message)
    {
        assert(message.valid());

        checkCompatibility();
    }

    /// Creates an instance over the given memory block.
    /// Performs no checks.
    OrderMassActionReport702(
        void* data,
        EncodedLength length,
        NoInit,
        NoCheck)
        ONIXS_B3_BOE_NOTHROW
      : SbeMessage(data, length, NoCheck())
    {
        assert(schemaId() == Schema::Id);
        assert(version() >= Schema::MinimalVersion);
        assert(TemplateId == templateId());
    }

    /// Message type = OrderMassActionReport.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static MessageType::Enum messageType()
        ONIXS_B3_BOE_NOTHROW
    {
        return MessageType::OrderMassActionReport;
    }

    /// Message type = OrderMassActionReport.

    /// Common header to all inbound business messages.
    ONIXS_B3_BOE_NODISCARD
    const OutboundBusinessHeader&
    businessHeader() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;

        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Common header to all inbound business messages.
    OutboundBusinessHeader& businessHeader()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 0;
        return accessOrdinary<OutboundBusinessHeader>(offset);
    }

    /// Specifies the type of action requested.
    ONIXS_B3_BOE_NODISCARD
    MassActionType::Enum massActionType() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        return enumeration<MassActionType>(offset);
    }

    /// Specifies the type of action requested.
    ThisType&
    setMassActionType(
        MassActionType::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 18;

        setEnumeration<MassActionType>(offset, value);
        return *this;
    }

    /// Specifies the scope of the action.
    ONIXS_B3_BOE_NODISCARD
    bool
    massActionScope(
        MassActionScope::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        return enumeration<MassActionScope>(value, offset, NullUint8EnumEncoding());
    }

    /// Specifies the scope of the action.
    ThisType&
    setMassActionScope(
        MassActionScope::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setEnumeration<MassActionScope>(offset, value);
        return *this;
    }

    ThisType& setMassActionScopeToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 19;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ONIXS_B3_BOE_NODISCARD
    ClOrdID clOrdId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        return ordinary<ClOrdID>(offset);
    }

    /// Unique identifier of the order as assigned by the market
    /// participant.
    ThisType& setClOrdId(ClOrdID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 20;

        setOrdinary(offset, value);
        return *this;
    }

    /// Unique ID of Order Mass Action Report as assigned by the
    /// matching engine.
    ONIXS_B3_BOE_NODISCARD
    MassActionReportID massActionReportId() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        return ordinary<MassActionReportID>(offset);
    }

    /// Unique ID of Order Mass Action Report as assigned by the
    /// matching engine.
    ThisType& setMassActionReportId(MassActionReportID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 28;

        setOrdinary(offset, value);
        return *this;
    }

    /// Time of execution/order creation.
    ONIXS_B3_BOE_NODISCARD
    UTCTimestampNanos transactTime() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        return ordinary<UTCTimestampNanos>(offset);
    }

    /// Time of execution/order creation.
    ThisType& setTransactTime(UTCTimestampNanos value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 36;

        setOrdinary(offset, value);
        return *this;
    }

    /// Specifies the action taken by matching engine when it
    /// receives the Order Mass Action Request.
    ONIXS_B3_BOE_NODISCARD
    MassActionResponse::Enum massActionResponse() const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        return enumeration<MassActionResponse>(offset);
    }

    /// Specifies the action taken by matching engine when it
    /// receives the Order Mass Action Request.
    ThisType&
    setMassActionResponse(
        MassActionResponse::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 44;

        setEnumeration<MassActionResponse>(offset, value);
        return *this;
    }

    /// Reason Order Mass Action Request was rejected.
    ONIXS_B3_BOE_NODISCARD
    bool
    massActionRejectReason(
        MassActionRejectReason::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        return enumeration<MassActionRejectReason>(value, offset, NullUInt8());
    }

    /// Reason Order Mass Action Request was rejected.
    ThisType&
    setMassActionRejectReason(
        MassActionRejectReason::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        setEnumeration<MassActionRejectReason>(offset, value);
        return *this;
    }

    ThisType& setMassActionRejectReasonToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 45;

        setOrdinary(offset, NullUInt8());
        return *this;
    }

    /// Used to communicate event type which triggers the Order
    /// Mass Action Request.
    ONIXS_B3_BOE_NODISCARD
    bool
    execRestatementReason(
        ExecRestatementReasonValidForMassCancel::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;

        return enumeration<ExecRestatementReasonValidForMassCancel>(value, offset, NullUint8EnumEncoding());
    }

    /// Used to communicate event type which triggers the Order
    /// Mass Action Request.
    ThisType&
    setExecRestatementReason(
        ExecRestatementReasonValidForMassCancel::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;

        setEnumeration<ExecRestatementReasonValidForMassCancel>(offset, value);
        return *this;
    }

    ThisType& setExecRestatementReasonToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 46;

        setOrdinary(offset, NullUint8EnumEncoding());
        return *this;
    }

    /// Identifies the order tag identification.
    ONIXS_B3_BOE_NODISCARD
    bool ordTagId(OrdTagID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        return ordinary(value, offset, NullOrdTagID());
    }

    /// Identifies the order tag identification.
    ThisType& setOrdTagId(OrdTagID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setOrdTagIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 47;

        setOrdinary(offset, NullOrdTagID());
        return *this;
    }

    /// Side of order.
    ONIXS_B3_BOE_NODISCARD
    bool side(Side::Enum& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        return enumeration<Side>(value, offset, NullChar());
    }

    /// Side of order.
    ThisType& setSide(Side::Enum value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setEnumeration<Side>(offset, value);
        return *this;
    }

    ThisType& setSideToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 48;

        setOrdinary(offset, NullChar());
        return *this;
    }

    /// Asset associated with the security, such as DOL, BGI, OZ1,
    /// WDL, CNI, etc.
    ONIXS_B3_BOE_NODISCARD
    bool asset(StrRef& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 50;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 6;

        return fixedStr<length>(value, offset);
    }

    /// Asset associated with the security, such as DOL, BGI, OZ1,
    /// WDL, CNI, etc.
    ThisType& setAsset(StrRef value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 50;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 6;

        setFixedStr<length>(offset, value);
        return *this;
    }

    ThisType& setAssetToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 50;
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength length = 6;

        setFixedStr<length>(offset, StrRef());
        return *this;
    }

    /// Security identification as defined by exchange.
    ONIXS_B3_BOE_NODISCARD
    bool
    securityId(
        SecurityIDOptional& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        return ordinary(value, offset, NullSecurityIDOptional());
    }

    /// Security identification as defined by exchange.
    ThisType& setSecurityId(SecurityIDOptional value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setSecurityIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 56;

        setOrdinary(offset, NullSecurityIDOptional());
        return *this;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static SecurityIDSource::Enum securityIdSource()
        ONIXS_B3_BOE_NOTHROW
    {
        return SecurityIDSource::ExchangeSymbol;
    }

    /// Identifies the class of the SecurityID (Exchange Symbol).

    /// Market to which the symbol belongs.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef securityExchange()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef("BVMF");
    }

    /// Unique identifier of investor for mass cancel on behalf
    /// purposes.
    ONIXS_B3_BOE_NODISCARD
    bool investorId(InvestorID& value) const
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        return ordinary(value, offset, NullInvestorID());
    }

    /// Unique identifier of investor for mass cancel on behalf
    /// purposes.
    ThisType& setInvestorId(InvestorID value)
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, value);
        return *this;
    }

    ThisType& setInvestorIdToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        ONIXS_B3_BOE_CONST_OR_CONSTEXPR BlockLength offset = 64;

        setOrdinary(offset, NullInvestorID());
        return *this;
    }

    /// Free ASCII format text string.
    ONIXS_B3_BOE_NODISCARD
    StrRef text() const
        ONIXS_B3_BOE_NOTHROW
    {
        return getVariableLengthField(textAccess(), *this);
    }

    /// Free ASCII format text string.
    ThisType& setText(StrRef value)
    {
        setVariableLengthField(
            textAccess(),
            value,
            *this);

        return *this;
    }

    /// Minimal size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    minimalBlockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            72;
    }

    /// Size of message body in bytes.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_CONSTEXPR
    static
    BlockLength
    blockLength(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            minimalBlockLength(version);
    }

    /// Minimal variable fields size (when variable-length fields are empty).
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static
    MessageSize
    getMinimalVariableFieldsSize(
        ONIXS_B3_BOE_UNUSED SchemaVersion version)
    {
        return
            ONIXS_B3_BOE_ASSERT(version >= Schema::MinimalVersion),
            static_cast<MessageSize>(TextEncoding::Size);
    }

    /// Maximal message size.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static UInt64 getMaxMessageSize(UInt8)
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::getMaxMessageSize();
    }

    /// Reset all variable-length fields if any.
    ThisType& resetVariableFields()
        ONIXS_B3_BOE_NOTHROW
    {
        setTextToNull();
        return *this;
    }

    /// Reset all variable-length and optional fields if any.
    ThisType& reset()
        ONIXS_B3_BOE_NOTHROW
    {
        setMassActionScopeToNull();
        setMassActionRejectReasonToNull();
        setExecRestatementReasonToNull();
        setOrdTagIdToNull();
        setSideToNull();
        setAssetToNull();
        setSecurityIdToNull();
        setInvestorIdToNull();

        resetVariableFields();
        return *this;
    }

    /// \return class name.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static const Char* className()
    {
        return "OrderMassActionReport702";
    }

    /// FIX message type.
    ONIXS_B3_BOE_LTWT_EXPORTED
    ONIXS_B3_BOE_NODISCARD
    ONIXS_B3_BOE_CONSTEXPR
    static StrRef fixType()
        ONIXS_B3_BOE_NOTHROW
    {
        return constructStrRef(
            "OrderMassActionReport702");
    }

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// \return the end of the message.
    ONIXS_B3_BOE_NODISCARD
    const void* tail() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            toOpaquePtr(
                (text().end()));
    }

    /// \return the size occupied by the message.
    ONIXS_B3_BOE_NODISCARD
    EncodedLength calculateBinarySize() const
        ONIXS_B3_BOE_NOTHROW
    {
        return
            SbeMessage::calculateBinarySize(tail());
    }

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
    struct textAccess
    {
        TextEncoding&
        operator()(
            const OrderMassActionReport702& obj) const
            ONIXS_B3_BOE_NOTHROW
        {
            return obj.
                variableLengthFields().
                    head<TextEncoding>();
        }
    };

    /// Reset the field.
    /// All the following data will be invalidated.
    ThisType& setTextToNull()
        ONIXS_B3_BOE_NOTHROW
    {
        setVariableLengthFieldToNull(textAccess(), *this);

        return *this;
    }
};


ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
