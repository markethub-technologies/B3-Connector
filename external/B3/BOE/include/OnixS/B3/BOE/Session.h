/*
 * Copyright Onix Solutions Limited [OnixS]. All rights reserved.
 *
 * This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
 * and international copyright treaties.
 *
 * Access to and use of the software is governed by the terms of the applicable OnixS Software
 * Services Agreement (the Agreement) and Customer end user license agreements granting
 * a non-assignable, non-transferable and non-exclusive license to use the software
 * for it's own data processing purposes under the terms defined in the Agreement.
 *
 * Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
 * of this source code or associated reference material to any other location for further reproduction
 * or redistribution, and any amendments to this copyright notice, are expressly prohibited.
 *
 * Any reproduction or redistribution for sale or hiring of the Software not in accordance with
 * the terms of the Agreement is a violation of copyright law.
 */

#pragma once

#include <limits.h>

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/Defines.h>
#include <OnixS/B3/BOE/SessionListener.h>
#include <OnixS/B3/BOE/SessionSettings.h>
#include <OnixS/B3/BOE/SessionStorage.h>
#include <OnixS/B3/BOE/SessionReactor.h>
#include <OnixS/B3/BOE/TcpInfo.h>
#include <OnixS/B3/BOE/messaging/SbeMessage.h>
#include <OnixS/B3/BOE/threading/Future.h>

namespace OnixS
{
namespace B3
{
namespace BOE
{
// Forward declarations
class TcpDirectStack;
namespace AdHoc { struct SessionHelper; };

/**
* A FIXP Session.
*/
class ONIXS_B3_BOE_EXPORTED Session
{
public:
    static const UInt64 UndefinedSessionVerID = 0;

    /**
     * Constructor.
     *
     * \param settings Session settings.
     * \param listener Session listener.
     * \param storageType Session storage type.
     * \param storage Session storage.
     * \param sessionVerId Session Version Identification (sessionVerId).
     * \param customKey Custom key that could be used to distinguish sessions with the same sessionVerId, Session ID, FirmId, and Market Segment ID values.
     */
    Session(const SessionSettings &settings, SessionListener *listener, SessionStorageType::Enum storageType = SessionStorageType::FileBased,
        SessionStorage *storage = ONIXS_B3_BOE_NULLPTR, UInt64 sessionVerId = UndefinedSessionVerID, const std::string &customKey = "");

    Session(SessionReactor & stack, const SessionSettings & settings, SessionListener * listener, SessionStorageType::Enum storageType = SessionStorageType::FileBased,
        SessionStorage * storage = ONIXS_B3_BOE_NULLPTR, UInt64 sessionVerId = UndefinedSessionVerID, const std::string &customKey = "");

    ~Session();

    /// \return the Session Version Identification (sessionVerId).
    UInt64 sessionVerId() const ONIXS_B3_BOE_NOTHROW;

    /// \return string presentation for Session ID (assigned by the exchange).
    std::string id() const;

    /// \return Session ID (assigned by the exchange).
    Messaging::SessionID sessionId() const ONIXS_B3_BOE_NOTHROW;

    /// \return Custom key that could be used to distinguish sessions with the same sessionVerId, Session ID, FirmId, and Market Segment ID values.
    std::string customKey() const;

    /// \return `true` if the session is negotiated (the Negotiation Response message has been received in reply to the Negotiation message); otherwise - `false`.
    bool negotiated() const;

    /// Sets the "negotiated" status.
    ///
    /// The session is negotiated when the Negotiation Response message has been received in reply to the Negotiation message.
    Session& negotiated(bool negotiated);

    /**
     * Establishes the connection.
     *
     * \param host Market Segment Gateway host.
     * \param port Market Segment Gateway port.
     *
     * \return This session.
     */
    Session& connect(const std::string &host, Port port);

    /**
     * Establishes the connection asynchronously.
     *
     * \param host Market Segment Gateway host.
     * \param port Market Segment Gateway port.
     */
    Threading::SharedFuture<void> connectAsync(const std::string & host, Port port);

    /**
    * Terminates the connection.
    *
    * \note Method blocks until the Terminate message is received in reply, or the timeout is elapsed.
    *
    * \return This session.
    */
    Session& disconnect();

    /**
    * Terminates the connection asynchronously.
    */
    Threading::SharedFuture<void> disconnectAsync();

    /**
     * Sends the message.
     *
     * \param sendingTime The time value to be used for a `sendingTimeEpoch` field of the message(s) being sent.
     * \param msg The message to be sent.
     *
     * \note This call is thread-safe, except for the TCPDirect mode.
     *
     * \return This session.
     */
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Session& send(
        Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &msg,
        Messaging::Timestamp sendingTime = UtcWatch::now());

#if defined (ONIXS_B3_BOE_CXX11)

    /**
     * Sends the message.
     * \param sendingTime The time value to be used for a `sendingTimeEpoch` field of the message(s) being sent.
     * \param msg The message to be sent.
     *
     * \note This call is thread-safe, except for the TCPDirect mode.
     *
     * \return This session.
     */
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Session& send(
        Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &&msg,
        Messaging::Timestamp sendingTime = UtcWatch::now());

#endif

    /// Packet size maximum behavior based on MTU (Maximum Transmission Unit) 1420 bytes.
    static const size_t B3BOEMaxPacketSize = 1420;

#if defined (ONIXS_B3_BOE_CXX11)

    /**
     * Sends messages.
     *
     * \note This call is thread-safe.
     *
     * \param msgs Message batch to send.
     * \param maxPacketSize The maximum number of bytes written to the socket's send buffer together.
     * This parameter could be used to reduce the probability that the operating system will fragment the message across multiple TCP packets.
     * \param sendingTime The time value to be used for a `sendingTimeEpoch` field of the message(s) being sent.
     *
     * \note The maxPacketSize parameter should not be less than any message size in the batch.
     * Otherwise, the method call can produce an error, and the session can close the connection.
     *
     * \return This session.
     */
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Session& send(
        MessageBatch<SbeMessageType, MaxMessageSize, MessageInitializer> & msgs,
        Messaging::Timestamp sendingTime = UtcWatch::now(),
        size_t maxPacketSize = B3BOEMaxPacketSize);

    /**
    * Sends messages.
    *
    * \note This call is thread-safe.
    *
    * \param msgs Message batch combiner to send.
    * \param maxPacketSize The maximum number of bytes written to the socket's send buffer together.
    * This parameter could be used to reduce the probability that the operating system will fragment the message across multiple TCP packets.
    * \param sendingTime The time value to be used for a `sendingTimeEpoch` field of the message(s) being sent.
    *
    * \note The maxPacketSize parameter should not be less than any message size in the batch.
    * Otherwise, the method call can produce an error, and the session can close the connection.
    *
    * \return This session.
    */
    Session& send(
        MessageBatchCombiner & msgs,
        Messaging::Timestamp sendingTime = UtcWatch::now(),
        size_t maxPacketSize = B3BOEMaxPacketSize);

#endif

    /**
     * Send the Sequence message.
     *
     * \note The session sends Sequence messages automatically per the B3 BOE protocol.
     * This method should be used only if an ad hoc Sequence message is required
     * and the connection is established.
     *
     * \return This session.
     */
    Session& sendSequenceMessage();

    /**
    * Warms up the sending path.
    *
    * \param msg SBE message to warm up the sending path.
    * \param warmupFlags Specific flags which can be used to turn on the warmup feature for a specific NIC.
    * \param sendingTime The time value to be used for a `sendingTimeEpoch` field of the message(s) being sent.
    *
    * \note This call is thread-safe, except for the TCPDirect mode.
    *
    * \return This session.
    */
    template <typename SbeMessageType, size_t MaxMessageSize>
    Session& warmUp(
        Messaging::MessageHolder<SbeMessageType, MaxMessageSize> &msg,
        Messaging::Timestamp sendingTime = UtcWatch::now(),
        int warmupFlags = 0);


#if defined (ONIXS_B3_BOE_CXX11)

    /**
     * Warms up the sending path.
     *
     * \note This call is thread-safe.
     *
     * \param msgs Message batch to send.
     * \param maxPacketSize The maximum number of bytes written to the socket's send buffer together during the subsequent `send` call.
     * \param sendingTime The time value to be used for a `sendingTimeEpoch` field of the message(s) being sent.
     * \param warmupFlags Specific flags which can be used to turn on the warmup feature for a specific NIC.
     *
     * \note The maxPacketSize parameter should not be less than any message size in the batch.
     * Otherwise, the method call can produce an error, and the session can close the connection.
     *
     * \return This session.
     */
    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    Session& warmUp(
        MessageBatch<SbeMessageType, MaxMessageSize, MessageInitializer> & msgs,
        Messaging::Timestamp sendingTime = UtcWatch::now(),
        size_t maxPacketSize = B3BOEMaxPacketSize,
        int warmupFlags = 0);

    /**
    * Warms up the sending path.
    *
    * \note This call is thread-safe.
    *
    * \param msgs Message batch combiner to send.
    * \param maxPacketSize The maximum number of bytes written to the socket's send buffer together during the subsequent `send` call.
    * \param sendingTime The time value to be used for a `sendingTimeEpoch` field of the message(s) being sent.
    * \param warmupFlags Specific flags which can be used to turn on the warmup feature for a specific NIC.
    *
    * \note The maxPacketSize parameter should not be less than any message size in the batch.
    * Otherwise, the method call can produce an error, and the session can close the connection.
    *
    * \return This session.
    */
    Session& warmUp(
        MessageBatchCombiner & msgs, Messaging::Timestamp sendingTime = UtcWatch::now(),
        size_t maxPacketSize = B3BOEMaxPacketSize, int warmupFlags = 0);
#endif

    /**
    * Performs the throttling of a session that must be called before each send function call.
    * If the count of messages per time unit exceeds the throttling limit, the function will be blocked until the given time interval is passed.
    *
    * \note This call is thread-safe.
    */
    Session& throttle();

    /**
    * Checks the throttling of a session that must be called before each send function call.
    * If the count of messages per time unit exceeds the throttling limit, the function returns the delay (in milliseconds) until the sending becomes possible. Otherwise, it returns 0.
    *
    * \note This call is thread-safe.
    */
    size_t tryThrottle();

    /**
    * Sets throttling limit parameters.
    *
    * \param messagesCount Message limit per time unit.
    * \param intervalInMs Time interval to limit messages.
    *
    * \note This call is thread-safe.
    */
    Session & throttlingLimit(size_t messagesCount, size_t intervalInMs = 1000);

    /// \return the host name the session is connected to.
    std::string remoteHost() const;

    /// \return the IP address the session is connected to.
    std::string remoteIpAddress() const;

    /// \return the port number the session is connected to.
    Port remotePort() const;

    /// \return the local port range
    std::pair<Port, Port> localPortRange() const ONIXS_B3_BOE_NOTHROW;

    /// Sets the local port range
    Session& localPortRange(std::pair<Port, Port> portRange);

    /// \return the IP Address or name of the local network interface.
    std::string localNetworkInterface() const;

    /// Sets the IP Address or name of the local network interface.
    Session& localNetworkInterface(const std::string &value);

    /// \return the local network port number.
    Port localPort() const;

    /// \return the value of the `TCP_NODELAY` option (improve latency at the expense of message throughput).
    bool tcpNoDelayOption() const;

    /// Sets the `TCP_NODELAY` option (improve latency at the expense of message throughput).
    Session& tcpNoDelayOption(bool value);

    /// \return Socket options.
    const SocketOptions &socketOptions() const;

    /// Sets socket options.
    Session& socketOptions(const SocketOptions &options);

    static const int UndefinedAffinity = -1;

    /// Sets the receiving thread CPU affinity.
    Session& receivingThreadAffinity(CpuIndex cpuIndex);

    /// \return the receiving thread CPU affinity.
    Session& receivingThreadAffinity(const CpuIndexes &cpuIndexes);

    /// Sets the receiving thread CPU affinity.
    const CpuIndexes &receivingThreadAffinity() const;

    /// Sets the sending thread CPU affinity.
    Session& sendingThreadAffinity(CpuIndex cpuIndex);

    /// Sets the sending thread CPU affinity.
    Session& sendingThreadAffinity(const CpuIndexes &cpuIndexes);

    /// \return the auxiliary sending thread CPU affinity.
    const CpuIndexes &sendingThreadAffinity() const;

    /// \return the scheduling priority of the receiving thread.
    int receivingThreadPriority() const;

    /// Sets the scheduling priority of the receiving thread.
    Session& receivingThreadPriority(int priority);

    /// \return the scheduling priority of the sending thread.
    int sendingThreadPriority() const;

    /// \return the scheduling priority of the sending thread.
    Session& sendingThreadPriority(int priority);

    /// \return the receiving thread policy.
    int receivingThreadPolicy() const;

    /// Sets the receiving thread policy.
    Session& receivingThreadPolicy(int policy);

    /// Sets the sending thread policy.
    int sendingThreadPolicy() const;

    /// \return the sending thread policy.
    Session& sendingThreadPolicy(int policy);

    /// \return the receive spinning timeout value (in microseconds).
    unsigned receiveSpinningTimeout() const ONIXS_B3_BOE_NOTHROW;

    /// Sets the receive spinning timeout value (in microseconds).
    Session& receiveSpinningTimeout(unsigned timeoutInUs);

    /// \return the send spinning timeout value (in microseconds).
    unsigned sendSpinningTimeout() const ONIXS_B3_BOE_NOTHROW;

    /// Sets the send spinning timeout value (in microseconds).
    Session& sendSpinningTimeout(unsigned timeoutInUs);

    /// \return `true` if new messages are reported even when the message gap is detected,
    /// and the reply on the `Retransmit Request` message is expected; otherwise - `false`.
    bool reportNewMessagesWhileWaitingForMissedMessages() const;

    /// Sets the option to report new messages even when the message gap is detected,
    /// and the reply on the `Retransmit Request` message is expected.
    Session& reportNewMessagesWhileWaitingForMissedMessages(bool value);

    /// \return the number of messages to be sent together.
    unsigned messageGrouping() const ONIXS_B3_BOE_NOTHROW;

    /**
     * Sets the number of messages to be sent together.
     *
     * \param numberOfMessagesToGroup If the parameter is zero (by default) or one, the Handler tries to send
     * an outgoing application-level message in the context of the thread that calls the OnixS::B3::BOE::Session::send method.
     * If the message cannot be sent immediately, it is stored in the queue for the subsequent sending by the sending thread.
     * If this parameter is larger than one, the Handler stores outgoing SBE messages in the queue for the subsequent sending by the sending thread.
     *
     * \return This session.
     */
    Session& messageGrouping(unsigned numberOfMessagesToGroup);

    /// \return Session storage type.
    SessionStorageType::Enum storageType() const ONIXS_B3_BOE_NOTHROW;

    /// \return Session storage ID.
    const std::string &storageId() const ONIXS_B3_BOE_NOTHROW;

    /// \return the sequence number of the next outgoing message.
    SeqNumber outSeqNum() const ONIXS_B3_BOE_NOTHROW;

    /// Sets the sequence number of the next outgoing message.
    Session& outSeqNum(SeqNumber nextOutSeqNum);

    /// \return the expected sequence number of the next inbound message.
    SeqNumber inSeqNum() const;

    /// Sets the expected sequence number of the next inbound message.
    Session& inSeqNum(SeqNumber nextExpectedInSeqNum);

    /**
     * Backups the current log files, resets the sequence numbers to 1 and generates a new sessionVerId.
     *
     * \warning Can be called only when the session is disconnected.
     *
     * \return This session.
     */
    Session& reset();

    /// \return Session's current state.
    SessionStateId::Enum state() const;

    /// \return the time when the session was created or the last reset operation was performed.
    Messaging::Timestamp creationTime() const ONIXS_B3_BOE_NOTHROW;

    /// Flushes all internal buffers of the session storage.
    void flushSessionStorage();

    /// \return the maximum number of tries to restore the telecommunications link.
    unsigned reconnectAttempts() const;

    /// Sets the maximum number of tries to restore the telecommunications link.
    Session& reconnectAttempts(unsigned reconnectAttempts);

    /// \return the time interval between retries to restore the telecommunications link (seconds).
    unsigned reconnectInterval() const;

    /// Sets the time interval between retries to restore the telecommunications link (seconds).
    Session& reconnectInterval(unsigned seconds);

    /// \return the usage of local time in Handler events and logs files.
    bool localTimeUsage() const;

    /// Specifies the usage of local time in Handler events and logs files.
    Session& localTimeUsage(bool useLocalTime);

    /// \return The session storage directory.
    const std::string &storageDirectory() const;

    /// \return `true` if logging of an outgoing message to the session storage is performed before sending it to the wire; otherwise - `false`.
    bool logBeforeSending() const;

    /// Sets the option to log an outgoing message to the session storage before sending it to the wire.
    Session& logBeforeSending(bool value);

    /// \return the maximum size of the message queue used during message gap recovery.
    size_t incomingMessageGapQueueMaximumSize() const;

    /// Sets the maximum size of the message queue used during message gap recovery.
    Session& incomingMessageGapQueueMaximumSize(size_t value);

    /// Write the given user's message to the Handler's log file using the session formatted Id.
    const Session& log(const std::string &message) const;

    /// \return the human-friendly description.
    std::string toString() const;

    /// \return the license expiration date.
    Messaging::Timestamp licenseExpirationDate() const;

    /// \return the version of the message schema.
    Messaging::SchemaVersion messagingVersion() const ONIXS_B3_BOE_NOTHROW;

    /// Represents invalid value of socket handle.
    static const Handle InvalidSocketHandle;

    /// Returns the socket handle which the session uses to transmit data.
    ///
    /// \note The TCPDirect mode does not support this method, so it always returns the `InvalidSocketHandle` value.
    Handle socketHandle();

    /// Returns the total number of bytes in the outbound queue.
    size_t outboundQueueBytes();

    /// Gets information about the underlying TCP connection.
    ///
    /// \return `true` when success; otherwise - `false`.
    /// \note Available on Linux only.
    /// \note Not available for the TcpDirect mode.
    bool getTcpInfo(TcpInfo&);

    /// \return the version of the library.
    static const std::string& version() ONIXS_B3_BOE_NOTHROW;

private:
    Session(const Session& );
    Session& operator=(const Session& );

    void send(NetworkMessage msg, Messaging::Timestamp ts);
    void send(NetMessages& msgs, size_t maxPacketSize, Messaging::Timestamp ts);
    void warmUp(NetworkMessage msg, int warmupFlags, Messaging::Timestamp ts);
    void warmUp(NetMessages& msgs, size_t maxPacketSize, int warmupFlags, Messaging::Timestamp ts);

    template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
    void validate(const Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &msg) const;

    void validateVersion(Messaging::SchemaVersion version) const;

    Session& sendRetransmitRequest(UInt64 sessionVerId, SeqNumber from, SeqNumber to);

    struct Impl;
    Impl *const impl_;

friend struct AdHoc::SessionHelper;
};

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
ONIXS_B3_BOE_HOTPATH
Session& Session::send(Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &msg, Messaging::Timestamp ts)
{
    assert(ts != Messaging::Timestamp());

#ifndef NDEBUG
    validate(msg);
#endif

    send(msg.toNetworkMessage(), ts);

    return *this;
}

template <typename SbeMessageType, size_t MaxMessageSize>
ONIXS_B3_BOE_HOTPATH
Session& Session::warmUp(
    Messaging::MessageHolder<SbeMessageType, MaxMessageSize> &msg,
    Messaging::Timestamp sendingTime,
    int warmupFlags)
{
    warmUp(msg.toNetworkMessage(), warmupFlags, sendingTime);

    return *this;
}

#if defined (ONIXS_B3_BOE_CXX11)

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
ONIXS_B3_BOE_HOTPATH
Session& Session::send(Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &&msg, Messaging::Timestamp ts)
{
    assert(ts != Messaging::Timestamp());

    send(msg, ts);
    return *this;
}

#endif

#if defined (ONIXS_B3_BOE_CXX11)

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
ONIXS_B3_BOE_HOTPATH
Session& Session::send(
    Messaging::MessageBatch<SbeMessageType, MaxMessageSize, MessageInitializer> & msgs,
    Messaging::Timestamp ts,
    size_t maxPacketSize)
{
    assert(ts != Messaging::Timestamp());

    send(msgs.netMsgs_, maxPacketSize, ts);
    return *this;
}

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
ONIXS_B3_BOE_HOTPATH
Session& Session::warmUp(
    Messaging::MessageBatch<SbeMessageType, MaxMessageSize, MessageInitializer> & msgs,
    Messaging::Timestamp ts, size_t maxPacketSize, int flags)
{
    assert(ts != Messaging::Timestamp());

    warmUp(msgs.netMsgs_, maxPacketSize, flags, ts);
    return *this;
}

#endif

template <typename SbeMessageType, size_t MaxMessageSize, typename MessageInitializer>
void Session::validate(const Messaging::MessageHolder<SbeMessageType, MaxMessageSize, MessageInitializer> &holder) const
{
    validateVersion(holder->version());
}

}
}
}
