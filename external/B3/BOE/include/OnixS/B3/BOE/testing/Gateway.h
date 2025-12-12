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

#pragma once

#include <OnixS/B3/BOE/testing/ABI.h>
#include <OnixS/B3/BOE/SessionSettings.h>

#if defined(ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR)

#include <OnixS/B3/BOE/Messaging.h>
#include <OnixS/B3/BOE/testing/MessagePtr.h>
#include <OnixS/B3/BOE/testing/ClientMessageListener.h>

#include <chrono>
#include <atomic>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Testing {

// Assume NegotiateResponse2::credentials is empty
constexpr
UInt16 calculateNegotiateResponse2MaxSize()
{
    using Message = NegotiateResponse2;

    return
        Message::blockLength(Message::Schema::Version)
        + MessageHeader::Size
        + Message::getMinimalVariableFieldsSize(Message::Schema::Version);
}

//  Type aliases
using NegotiateResponse2Container = MessageHolder<NegotiateResponse2, calculateNegotiateResponse2MaxSize()>;
using NegotiateReject3Container = MessageHolder<NegotiateReject3>;
using EstablishAck5Container = MessageHolder<EstablishAck5>;
using EstablishReject6Container = MessageHolder<EstablishReject6>;
using Terminate7Container = MessageHolder<Terminate7>;
using Sequence9Container = MessageHolder<Sequence9>;

using MessageBasePtr = MessagePtr<SbeMessage>;
using Negotiate1Ptr = MessagePtr<Negotiate1>;
using Establish4Ptr = MessagePtr<Establish4>;
using Terminate7Ptr = MessagePtr<Terminate7>;
using Sequence9Ptr = MessagePtr<Sequence9>;

/// B3 BOE Gateway Emulator.
class ONIXS_B3_BOE_EXPORTED Gateway
{
public:
    /// Timeout alias.
    using Timeout = std::chrono::milliseconds;

    Gateway(const SessionSettings::LicenseStores& licenseStores, int port, const char* host = "127.0.0.1",
            const Timeout& acceptTimeout = defaultTimeout(),
            const Timeout& sendReceiveTimeout = defaultTimeout());

    ///
    virtual ~Gateway();

    /// Deleted.
    Gateway(const Gateway&) = delete;
    Gateway& operator=(const Gateway&) = delete;

    /// Move semantic.
    Gateway(Gateway&&) noexcept;
    Gateway& operator=(Gateway&&) noexcept;

    /// Swap with other.
    void swap(Gateway&) noexcept;

    /// Accepts an incoming connection.
    /// If the `acceptTimeout` is zero, the `acceptTimeout` provided in the constructor is used.
    Gateway& acceptConnection(const Timeout& acceptTimeout = defaultTimeout());

    /// Accepts an incoming connection.
    /// If the operation is timed out, `false` is returned.
    bool tryAcceptConnection(const Timeout& acceptTimeout = defaultTimeout());

    /// Accepts an incoming FIXP session.
    Gateway& acceptSession(SeqNumber outgoingSequenceNumber = 1);

    /// Waits until the Terminate7 message is received.
    ///
    /// If the listener is provided, then receives and reports application-level messages via the corresponding callback.
    /// Responds to the Sequence9 message if received.
    /// \note actual `outSeqNum` must be provided before invocation
    Terminate7Ptr waitUntilTerminate(
        ClientMessageListener* listener = nullptr, ClientSessionMessageListener* sessionMessageListener = nullptr,
        std::atomic<bool>* stopRequested = nullptr);

    /// Sends the Sequence9 message.
    Gateway& sendSequence(UInt32 nextSeqNo);

    /// Closes the accepted connection.
    Gateway& disconnect();

    /// @return listen host.
    const char * host() const noexcept;

    /// \return the listen port.
    ONIXS_B3_BOE_NODISCARD
    int port() const noexcept;

    /// Enables logging.
    Gateway& enableLogger(const std::string& logFileName, unsigned int logLevel = 3);

    /// Sends the given message.
    /// \note  does not update `outSeqNum`.
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Gateway& send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>& msg);

    /// Sends the given message.
    /// \note  does not update `outSeqNum`.
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Gateway& send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>&& msg);

    /// Sets the given sequence number and sends the message.
    /// \note  does not update `outSeqNum`.
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Gateway& send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>& msg, SeqNumber num);

    /// Sets the given sequence number and sends the message.
    /// \note  does not update `outSeqNum`.
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Gateway& send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>&& msg, SeqNumber num);

    /// Sets the given sequence numbers and sends the messages.
    /// \note  does not update `outSeqNum`.
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Gateway& send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>& msg, std::initializer_list<SeqNumber> numbers);

    /// Sets the given sequence numbers and sends the messages.
    /// \note  does not update `outSeqNum`.
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Gateway& send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>&& msg, std::initializer_list<SeqNumber> numbers);


    /// Receives the message of the particular type.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    template <typename TMsg>
    MessagePtr<TMsg> receiveTypedMessage();

    /// Accepts an incoming connection and establishes the session.
    ///
    /// - Receives and reports application-level messages via the corresponding callback.
    /// - Sends Sequence messages in response to the received ones.
    Gateway& run(ClientMessageListener& listener);

    /// Accepts an incoming connection and establishes the session.
    ///
    /// - Receives and reports application-level messages via the corresponding callback.
    /// - Receives and reports session-level messages via the corresponding callback.
    /// - Sends Sequence messages.
    Gateway& run(ClientMessageListener& appMsgListener, ClientSessionMessageListener& sessionMsgListener);

    /// \return the sequence number of the next outgoing message.
    ONIXS_B3_BOE_NODISCARD
    SeqNumber outSeqNum() const noexcept;

    /// Sets the sequence number of the next outgoing message.
    Gateway& outSeqNum(SeqNumber nextOutSeqNum) noexcept;

    /// \return sessionVerId.
    ONIXS_B3_BOE_NODISCARD
    UInt64 sessionVerId() const noexcept
    {
        return uId_;
    }

    /// \return session Id.
    ONIXS_B3_BOE_NODISCARD
    SessionID sessionId() const noexcept
    {
        return sessionId_;
    }

    /// Sets the value of the option to improve latency at the expense of message throughput (the `TCP_NODELAY` socket option).
    Gateway& tcpNoDelayOption(bool noDelay);

    /// \return the value of the option to improve latency at the expense of message throughput (the `TCP_NODELAY` socket option).
    ///
    /// The default value is SessionSettings::Default::TcpNoDelayOption.
    ONIXS_B3_BOE_NODISCARD
    bool tcpNoDelayOption() const noexcept ;

    /// \return the socket receive buffer size.
    ///
    /// The default value is SessionSettings::Default::SocketReceiveBufferSize.
    ONIXS_B3_BOE_NODISCARD
    int socketReceiveBufferSize() const;

    /// Sets the socket receive buffer size.
    ///
    /// \param bufferSize the size of the socket receive buffer size.
    /// If SessionSettings::UseOsDefaultSocketBufferSize then the default operating system value is used.
    Gateway& socketReceiveBufferSize(int bufferSize);

    /// \return the size of the socket send buffer size.
    ///
    /// The default value is SessionSettings::Default::SocketSedndBufferSize.
    ONIXS_B3_BOE_NODISCARD
    int socketSendBufferSize() const noexcept;

    /// Sets the size of the socket send buffer size.
    ///
    /// \param bufferSize the size of the socket send buffer size.
    /// If SessionSettings::UseOsDefaultSocketBufferSize then the default operating system value is used.
    Gateway& socketSendBufferSize(int bufferSize);

protected:
    /// Checks whether the connection is closed by the counterparty.
    ONIXS_B3_BOE_NODISCARD
    bool isConnectionClosed(const Timeout& timeout) const;

    /// Checks whether the connection is closed by the counterparty
    /// using the default timeout (provided in the constructor).
    ONIXS_B3_BOE_NODISCARD
    bool isConnectionClosed() const;

    /// Receives a message.
    MessageBasePtr receive() const;

    /// Receives a message using the provided timeout.
    /// If the operation is timed out, an empty message is returned.
    MessageBasePtr tryReceive(const Timeout& timeout = defaultTimeout()) const;

    /// Receives the Negotiate1 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Negotiate1Ptr receiveNegotiate();

    /// Receives the Negotiate1 and responds with the NegotiateResponse2 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Negotiate1Ptr acceptNegotiate();

    /// Receives the Negotiate1 message and responds with the NegotiateReject3 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Negotiate1Ptr rejectNegotiate(NegotiationRejectCode::Enum errorCodes = NegotiationRejectCode::Enum());

    /// Receives the Establish4 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Establish4Ptr receiveEstablish();

    /// Receive the Establish4 message and respond with the EstablishAck5 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Establish4Ptr acceptEstablish(UInt32 outgoingSequenceNumber = 1, unsigned gatewayKeepAliveInterval = 0);

    /// Receives the Establish4 message and responds with the EstablishReject6 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Establish4Ptr rejectEstablish(UInt32 outgoingSequenceNumber = 1, EstablishRejectCode::Enum errorCodes = EstablishRejectCode::Enum());

    /// Receive the Terminate7 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Terminate7Ptr receiveTerminate();

    /// Receive the Terminate7 message and responds with the Terminate7 message.
    ///
    /// \throw std::logic_error if an unexpected type is received.
    Terminate7Ptr acceptTerminate();

    /// Sends the Terminate7 message.
    Gateway& sendTerminate(TerminationCode::Enum errCode = TerminationCode::Finished);

    /// Sends the Terminate7 message and waits until the response is received.
    Terminate7Ptr terminate(TerminationCode::Enum errCode = TerminationCode::Finished);

    /// Creates a NegotiateResponse2 message
    NegotiateResponse2Container createNegotiationResponse(const Negotiate1Ptr& request);

    /// Creates a NegotiateReject3 message.
    NegotiateReject3Container createNegotiateReject(const Negotiate1Ptr& request, NegotiationRejectCode::Enum errorCodes);

    /// Creates a EstablishAck5 message.
    EstablishAck5Container createEstablishmentAck(const Establish4Ptr& request, UInt32 outgoingSequenceNumber, unsigned gatewayKeepAliveInterval = 0);

    /// Creates a EstablishReject6 message.
    EstablishReject6Container createEstablishReject(const Establish4Ptr& request, UInt32 outgoingSequenceNumber, EstablishRejectCode::Enum errorCodes);

    /// Creates a Terminate7 message.
    Terminate7Container createTerminate(const Terminate7Ptr& request);

    /// Creates a Terminate7 message.
    Terminate7Container createTerminate(TerminationCode::Enum errCode);

    /// Creates a Sequence9 message.
    Sequence9Container createSequence(UInt32 nextSeqNo);

    /// Sends the given message.
    Gateway& send(Messaging::SbeMessage, Messaging::SimpleOpenFramingHeader&);

    /// Sends the given data
    Gateway& sendData(const void* data, size_t size);

    /// Close the listening socket
    Gateway& close();

    /// Default timeout
    static Timeout defaultTimeout()
    {
        return Timeout(30000);
    }

    /// sessionVerId.
    UInt64 uId_{0};

    /// sessionId.
    SessionID sessionId_;

private:

    class Impl;
    Impl* impl_;
};


template <typename TMsg>
MessagePtr<TMsg> Gateway::receiveTypedMessage()
{
    return cast<TMsg>(receive());
}

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
Gateway& Gateway::send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>& msg)
{
    const auto messageSize = msg.setHeader();
    auto* const header = msg.header();
    assert(header);

    return send(Messaging::SbeMessage(header + 1, messageSize), *header);
}

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
Gateway& Gateway::send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>&& msg)
{
    return send(msg);
}

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
Gateway& Gateway::send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>& msg, SeqNumber num)
{
    auto & header = msg->businessHeader();
    header.setMsgSeqNum(num);
    return send(msg);
}

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
Gateway& Gateway::send(BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>&& msg, SeqNumber num)
{
    auto & header = msg->businessHeader();
    header.setMsgSeqNum(num);
    return send(msg);
}

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
Gateway& Gateway::send(
    BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>& msg, std::initializer_list<SeqNumber> numbers)
{
    for(auto seqNum : numbers)
    {
        send(msg, seqNum);
    }

    return *this;
}

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
Gateway& Gateway::send(
    BOE::Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer>&& msg, std::initializer_list<SeqNumber> numbers)
{
    for(auto seqNum : numbers)
    {
        send(msg, seqNum);
    }

    return *this;
}


}}}}


#endif
