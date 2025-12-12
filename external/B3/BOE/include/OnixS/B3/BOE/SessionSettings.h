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

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/Messaging.h>
#include <OnixS/B3/BOE/ThreadingModel.h>

#include <climits>
#include <set>
#include <string>
#include <vector>

namespace OnixS {
namespace B3 {
namespace BOE {

/**
 * Session settings.
 */
class SessionSettings
{
public:
    ONIXS_B3_BOE_EXPORTED
    SessionSettings();

    /// \return the session id that was assigned by the exchange.
    ///
    /// The default value is empty.
    ONIXS_B3_BOE_NODISCARD
    Messaging::SessionID sessionId() const ONIXS_B3_BOE_NOTHROW {
        return sessionId_;
    }

    /// Sets the session id that was assigned by the exchange.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& sessionId(Messaging::SessionID value);

    /// \return the broker firm id that will enter orders.
    ///
    /// The default value is zero.
    ONIXS_B3_BOE_NODISCARD
    Messaging::UInt32 enteringFirm() const ONIXS_B3_BOE_NOTHROW {
        return enteringFirm_;
    }

    /// Sets the broker firm id that will enter orders.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& enteringFirm(Messaging::UInt32 value);

    /// \return The token provided by B3 for the FIXP session.
    ///
    /// The default value is empty.
    ONIXS_B3_BOE_NODISCARD
    const std::string & accessKey() const ONIXS_B3_BOE_NOTHROW {
        return accessKey_;
    }

    /// Sets the token provided by B3 for the FIXP session.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& accessKey(const std::string & value);

    /// \return The criteria used to initiate cancel on disconnect mechanism by the gateway.
    ///
    /// The default value is DoNotCancelOnDisconnectOrTerminate.
    ONIXS_B3_BOE_NODISCARD
    Messaging::CancelOnDisconnectType::Enum cancelOnDisconnectType() const ONIXS_B3_BOE_NOTHROW {
        return cancelOnDisconnectType_;
    }

    /// Sets the criteria used to initiate cancel on disconnect mechanism by the gateway.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& cancelOnDisconnectType(Messaging::CancelOnDisconnectType::Enum value);

    /// \return the trading system name.
    ///
    /// The default value is empty.
    ONIXS_B3_BOE_NODISCARD
    const std::string & tradingSystemName() const ONIXS_B3_BOE_NOTHROW {
        return tradingSystemName_;
    }

    /// Sets the trading system name.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& tradingSystemName(const std::string & value);

    /// \return the trading system version.
    ///
    /// The default value is empty.
    ONIXS_B3_BOE_NODISCARD
    const std::string & tradingSystemVersion() const ONIXS_B3_BOE_NOTHROW {
        return tradingSystemVersion_;
    }

    /// Sets the trading system version.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& tradingSystemVersion(const std::string & value);

    /// \return the threading model.
    ///
    /// The default value is Default::ThreadingModelValue.
    ONIXS_B3_BOE_NODISCARD
    ThreadingModel::Enum threadingModel() const ONIXS_B3_BOE_NOTHROW {
        return threadingModel_;
    }

    /// Sets the threading model.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& threadingModel(ThreadingModel::Enum value);

    /// \return the receive spinning timeout (microseconds).
    ///
    /// The default value is Default::ReceiveSpinningTimeout.
    ONIXS_B3_BOE_NODISCARD
    unsigned receiveSpinningTimeout() const ONIXS_B3_BOE_NOTHROW {
        return receiveSpinningTimeout_;
    }

    /// Sets the receive spinning timeout (microseconds).
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& receiveSpinningTimeout(unsigned usecTimeout);

    /// \return the send spinning timeout (microseconds).
    ///
    /// The default value is Default::SendSpinningTimeout.
    ONIXS_B3_BOE_NODISCARD
    unsigned sendSpinningTimeout() const ONIXS_B3_BOE_NOTHROW {
        return sendSpinningTimeout_;
    }

    /// Sets the send spinning timeout (microseconds).
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& sendSpinningTimeout(unsigned usecTimeout);

    /// \return the message grouping mode.
    ///
    /// - `0` means default grouping  - the messages are sent immediately, and pending messages (if any) are grouped till reaching of the TCP buffer size.
    /// - `1` means the messages are sent immediately and never grouped.
    /// - `2` (or higher) means the messages are sent immediately, and pending messages are grouped by 2 (or higher).
    ///
    /// The default value is Default::MessageGrouping.
    ONIXS_B3_BOE_NODISCARD
    unsigned messageGrouping() const ONIXS_B3_BOE_NOTHROW{
        return messageGrouping_;
    }

    /// Sets the message grouping mode.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& messageGrouping(unsigned value);

    /// Resets the settings to the default values.
    SessionSettings& resetToDefaults();

    /// Adds the path to the folder that contains license file(s).
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& addLicenseStore(const std::string& value);

    /// Sets the path to the folder that contains license file(s).
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& licenseStore(const std::string & value);

    /// Folders that contain license file(s).
    typedef std::vector<std::string> LicenseStores;

    /// \return path(s) to the folder that contains license file(s).
    ///
    /// The default value is '.'.
    ONIXS_B3_BOE_NODISCARD
    const LicenseStores& licenseStores() const ONIXS_B3_BOE_NOTHROW {
        return licenseStores_;
    }

    /// \return the number of days to alert before the license expiration.
    ///
    /// The default value is Default::LicenseAlertingDaysBeforeExpiration.
    ONIXS_B3_BOE_NODISCARD
    unsigned licenseAlertingDaysBeforeExpiration() const ONIXS_B3_BOE_NOTHROW {
        return licenseAlertingDaysBeforeExpiration_;
    }

    /// Sets the number of days to alert before the license expiration.
    ///
    /// If the amount of remaining license days is less or equal to this number,
    /// then the warning is reported to the Handler's log.
    ///
    /// The verification is performed during the Session::connect call.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& licenseAlertingDaysBeforeExpiration(unsigned days) {
        licenseAlertingDaysBeforeExpiration_ = days;
        return *this;
    }

    /// \return The interface name or IP-address from which the Handler connects to the counterparty.
    ///
    /// The default value is empty.
    ONIXS_B3_BOE_EXPORTED ONIXS_B3_BOE_NODISCARD
    const std::string & localNetworkInterface() const ONIXS_B3_BOE_NOTHROW {
        return localNetworkInterface_;
    }

    /// Specifies the local interface from which the Handler connects to the counterparty.
    ///
    /// Each local interface specification could specify the local IP address and port.
    /// For instance, `localhost` and `192.168.0.1:4501` are valid values.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& localNetworkInterface(const std::string & value);

    /// \return the Handler log file name.
    ///
    /// The default value is `HandlerLog.txt`.
    ONIXS_B3_BOE_NODISCARD
    const std::string & logFileName() const ONIXS_B3_BOE_NOTHROW {
        return logFileName_;
    }

    /// Specifies the Handler log file name.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& logFileName(const std::string & value);

    /// \return the Session Storage directory.
    ///
    /// Inbound and outbound messages, session's state data and the Handler log file are stored in this directory.
    ///
    /// The default value is `MsgStorage`.
    ONIXS_B3_BOE_NODISCARD
    const std::string & storageDirectory() const ONIXS_B3_BOE_NOTHROW {
        return storageDirectory_;
    }

    /// Sets the Session Storage directory.
    ///
    /// Inbound and outbound messages, session's state data and the Handler log file are stored in this directory.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& storageDirectory(const std::string & value);

    /// \return the usage of the local time in Handler events and log files.
    ///
    /// The default value is Default::LocalTimeUsage.
    ONIXS_B3_BOE_NODISCARD
    bool localTimeUsage() const ONIXS_B3_BOE_NOTHROW {
        return localTimeUsage_;
    }

    /// Specifies the usage of the local time in Handler events and log files.
    ///
    /// If it is `true`, then the local time is used; otherwise - UTC.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& localTimeUsage(bool);

    /// \return the segment size for the file-based session storage.
    ///
    /// The default value is Default::FileBasedStorageSegmentSize.
    ONIXS_B3_BOE_NODISCARD
    Messaging::UInt64 fileBasedStorageSegmentSize() const ONIXS_B3_BOE_NOTHROW {
        return fileBasedStorageSegmentSize_;
    }

    /// Sets the segment size for file-based session storage.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& fileBasedStorageSegmentSize(Messaging::UInt64 value);

    /// \return the maximum size of the asynchronous session storage queue.
    ///
    /// By default, the size is unlimited.
    ONIXS_B3_BOE_NODISCARD
    unsigned asyncFileBasedStorageQueueMaxSize() const ONIXS_B3_BOE_NOTHROW {
        return asyncFileBasedStorageQueueMaxSize_;
    }

    /// Sets the maximum size of the asynchronous session storage queue.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& asyncFileBasedStorageQueueMaxSize(unsigned value);

    /// \return the CPU index(es) for affinity of the asynchronous session storage threads.
    ///
    /// By default, the affinity is not set.
    ONIXS_B3_BOE_NODISCARD
    const CpuIndexes & asyncFileBasedStorageThreadAffinity() const ONIXS_B3_BOE_NOTHROW {
        return asyncFileBasedStorageThreadAffinity_;
    }

    /// Specifies the CPU index(es) for affinity of the asynchronous session storage threads.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& asyncFileBasedStorageThreadAffinity(const CpuIndexes & cpuIndexes);

    /// \return The file-based storage integrity errors checking mode:
    ///
    /// - `true` - ignore errors and create a new storage
    /// - `false` - throw an exception
    ///
    /// The default value is Default::IgnoreFileBasedStorageIntegrityErrors.
    ONIXS_B3_BOE_NODISCARD
    bool ignoreFileBasedStorageIntegrityErrors() const ONIXS_B3_BOE_NOTHROW {
        return ignoreFileBasedStorageIntegrityErrors_;
    }

    /// Sets the file-based storage integrity errors checking mode.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& ignoreFileBasedStorageIntegrityErrors(bool);

    /// \return `true` if outbound messages are logged before sending, 'false' otherwise.
    ///
    /// The default value is Default::LogBeforeSending.
    ONIXS_B3_BOE_NODISCARD
    bool logBeforeSending() const ONIXS_B3_BOE_NOTHROW {
        return logBeforeSending_;
    }

    /// Controls the order of logging and sending outbound messages.
    ///
    /// \param before if 'true' then outbound messages are logged before sending.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& logBeforeSending(bool before);

    /// \return the maximum number of tries to restore the telecommunications link.
    ///
    /// The default value is Default::ReconnectAttempts.
    ONIXS_B3_BOE_NODISCARD
    unsigned reconnectAttempts() const ONIXS_B3_BOE_NOTHROW {
        return reconnectAttempts_;
    }

    /// Sets the maximum number of tries to restore the telecommunications link.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& reconnectAttempts(unsigned reconnectAttempts);

    /// \return the time interval between retries to restore the telecommunications link (seconds).
    ///
    /// The default value is Default::ReconnectInterval.
    ONIXS_B3_BOE_NODISCARD
    unsigned reconnectInterval() const ONIXS_B3_BOE_NOTHROW {
        return reconnectInterval_;
    }

    /// Sets the time interval between retries to restore the telecommunications link (seconds).
    /// Should not be zero.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& reconnectInterval(unsigned value);

    /// Specifies the usage of the operating system default socket buffer size.
    static const int UseOsDefaultSocketBufferSize = -1;

    /// \return the socket receive buffer size.
    ///
    /// The default value is Default::SocketReceiveBufferSize.
    ONIXS_B3_BOE_NODISCARD
    int socketReceiveBufferSize() const ONIXS_B3_BOE_NOTHROW {
        return socketReceiveBufferSize_;
    }

    /// Sets the socket receive buffer size.
    ///
    /// \param bufferSize the size of the socket receive buffer size.
    /// If SessionSettings::UseOsDefaultSocketBufferSize then the default operating system value is used.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& socketReceiveBufferSize(int bufferSize);

    /// \return the reasonable transmission time - as the percentage from the `KeepAliveInterval` value.
    ///
    /// The default value is Default::ReasonableTransmissionTime.
    ONIXS_B3_BOE_NODISCARD
    unsigned reasonableTransmissionTime() const ONIXS_B3_BOE_NOTHROW {
        return reasonableTransmissionTime_;
    }

    /// Sets the reasonable transmission time - as the percentage from the `KeepAliveInterval` value.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& reasonableTransmissionTime(unsigned percentage);

    /// \return the size of the socket send buffer size.
    ///
    /// The default value is Default::SocketSendBufferSize.
    ONIXS_B3_BOE_NODISCARD
    int socketSendBufferSize() const ONIXS_B3_BOE_NOTHROW {
        return socketSendBufferSize_;
    }

    /// Sets the size of the socket send buffer size.
    ///
    /// \param bufferSize the size of the socket send buffer size.
    /// If SessionSettings::UseOsDefaultSocketBufferSize then the default operating system value is used.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& socketSendBufferSize(int bufferSize);

    /// \return the thread pool affinity.
    ONIXS_B3_BOE_NODISCARD
    const CpuIndexes & threadPoolAffinity() const ONIXS_B3_BOE_NOTHROW {
        return threadPoolAffinity_;
    }

    /// Sets the thread pool affinity.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& threadPoolAffinity(const CpuIndexes & cpuIndexes);

    /// \return the thread pool priority.
    ONIXS_B3_BOE_NODISCARD
    int threadPoolPriority() const ONIXS_B3_BOE_NOTHROW {
        return threadPoolPriority_;
    }

    /// Sets the thread pool priority.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& threadPoolPriority(int priority);

    /// \return the thread pool policy.
    ONIXS_B3_BOE_NODISCARD
    int threadPoolPolicy() const ONIXS_B3_BOE_NOTHROW {
        return threadPoolPolicy_;
    }

    /// Sets the thread pool policy.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& threadPoolPolicy(int policy);

    /// \return the value of the option to improve latency at the expense of message throughput (the `TCP_NODELAY` socket option).
    ///
    /// The default value is Default::TcpNoDelayOption.
    ONIXS_B3_BOE_NODISCARD
    bool tcpNoDelayOption() const ONIXS_B3_BOE_NOTHROW {
        return tcpNoDelayOption_;
    }

    /// Sets the value of the option to improve latency at the expense of message throughput (the `TCP_NODELAY` socket option).
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& tcpNoDelayOption(bool value);

    /// \return the size of the shared thread pool.
    ///
    /// The default value is Default::ThreadPoolSize.
    ONIXS_B3_BOE_NODISCARD
    unsigned threadPoolSize() const ONIXS_B3_BOE_NOTHROW {
        return threadPoolSize_;
    }

    /// Sets the size of the shared thread pool.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& threadPoolSize(unsigned numberOfThreads);

    /// \return the longest time in milliseconds the client system can remain silent before sending a message.
    ///
    /// The default value is Default::KeepAliveInterval.
    ONIXS_B3_BOE_EXPORTED ONIXS_B3_BOE_NODISCARD
    unsigned keepAliveInterval() const ONIXS_B3_BOE_NOTHROW {
        return keepAliveInterval_;
    }

    /// Sets the longest time in milliseconds the client system can remain silent before sending
    /// a message.
    ///
    /// \note Allowed range is between `5000` - `60000`. Any value outside this range will be rejected.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& keepAliveInterval(unsigned milliseconds);

    /// \return The CoD timeout window in milliseconds.
    ///
    /// The default value is Default::CodTimeoutWindow.
    ONIXS_B3_BOE_EXPORTED ONIXS_B3_BOE_NODISCARD
        unsigned codTimeoutWindow() const ONIXS_B3_BOE_NOTHROW {
        return codTimeoutWindow_;
    }

    /// Sets the CoD timeout window in milliseconds.
    /// Gateway will not trigger CoD if the customer reconnects within the timeout window
    /// (milliseconds) which starts when the triggering event is detected.
    ///
    /// \note Range is 0 (as soon as possible) to 60000.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& codTimeoutWindow(unsigned milliseconds);

    /// \return `true` if new messages are reported even when the message gap is detected,
    /// and the reply on the `Retransmit Request` message is expected; otherwise - `false`.
    ///
    /// The default value is Default::ReportNewMessagesWhileWaitingForMissedMessages.
    ONIXS_B3_BOE_NODISCARD
    bool reportNewMessagesWhileWaitingForMissedMessages() const ONIXS_B3_BOE_NOTHROW {
        return reportNewMessagesWhileWaitingForMissedMessages_;
    }

    /// Sets the option to report new messages even when the message gap is detected,
    /// and the reply on the `Retransmit Request` message is expected.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& reportNewMessagesWhileWaitingForMissedMessages(bool report);

    /// Sets the range of the local ports to be used
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& localPortRange(PortRange range);

    /// \return the range of the local ports to be used
    ONIXS_B3_BOE_NODISCARD
    PortRange localPortRange() const ONIXS_B3_BOE_NOTHROW {
        return localPortRange_;
    }

    /// Specifies the version of the message schema.
    /// Allowed range is between Messaging::SchemaTraits::MinimalVersion - Messaging::SchemaTraits::Version.
    /// The default value is Messaging::SchemaTraits::Version.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& messagingSchemaVersion(Messaging::SchemaVersion schema);

    /// \return the version of the message schema.
    ONIXS_B3_BOE_NODISCARD
    Messaging::SchemaVersion messagingSchemaVersion() const ONIXS_B3_BOE_NOTHROW {
        return messagingSchemaVersion_;
    }

    /// \return the value of the option to use spin lock.
    ///
    /// The default value is `false`.
    ONIXS_B3_BOE_NODISCARD
    bool useSpinLock() const ONIXS_B3_BOE_NOTHROW {
        return useSpinLock_;
    }

    /// Sets the value of the option to the option to use spin lock.
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& useSpinLock(bool value);

    /// \return the value of the option to enable received data timestamp.
    ///
    /// The default value is `false`.
    ONIXS_B3_BOE_NODISCARD
    bool enableRxTimestamp() const ONIXS_B3_BOE_NOTHROW {
        return enableRxTimestamp_;
    }

    /// Sets the value of the option to enable received data timestamp.
    /// \note available on Linux only
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& enableRxTimestamp(bool value);

    /// Loads the settings from the given configuration file.
    ///
    /// \see Key
    ONIXS_B3_BOE_EXPORTED
    SessionSettings& load(const std::string& configFile);

    /// \return the human-friendly description.
    ONIXS_B3_BOE_EXPORTED ONIXS_B3_BOE_NODISCARD
    std::string toString() const;

    /// Default session settings.
    struct ONIXS_B3_BOE_EXPORTED Default {
        static const Messaging::CancelOnDisconnectType::Enum CancelOnDisconnectType = Messaging::CancelOnDisconnectType::DoNotCancelOnDisconnectOrTerminate;
        static const ThreadingModel::Enum ThreadingModelValue = ThreadingModel::Dedicated;
        static const bool CreateLogFile = true;
        static const int KeepAliveInterval = 30000;
        static const int CodTimeoutWindow = 30000;
        static const bool LogBeforeSending = true;
        static const int SocketSendBufferSize = UseOsDefaultSocketBufferSize;
        static const int SocketReceiveBufferSize = UseOsDefaultSocketBufferSize;
        static const bool TcpNoDelayOption = true;
        static const int ReceiveSpinningTimeout = 0;
        static const int SendSpinningTimeout = 0;
        static const char LicenseStore[] ;
        static const unsigned LicenseAlertingDaysBeforeExpiration = 0;
        static const char LogDir[];
        static const char LogFileName[];
        static const bool LocalTimeUsage = false;
        static const unsigned MessageGrouping = 0;
        static const int ReasonableTransmissionTime = 20;
        static const int ReconnectAttempts = 3;
        static const int ReconnectInterval = 180;
        static const unsigned long long FileBasedStorageSegmentSize = 0;
        static const bool IgnoreFileBasedStorageIntegrityErrors = false;
        static const int ThreadPoolSize = 0;
        static const bool ReportNewMessagesWhileWaitingForMissedMessages = false;
        static const unsigned AsyncFileBasedStorageQueueMaxSize = UINT_MAX;
        static const bool UseSpinLock = false;
        static const bool EnableRxTimestamp = false;
    };

    /// The keys that are used to load settings from the configuration file.
    struct ONIXS_B3_BOE_EXPORTED Key {
        static const char * SessionId;                                      ///< = "SessionId"
        static const char * EnteringFirm;                                   ///< = "EnteringFirm"
        static const char * AccessKey;                                      ///< = "AccessKey"
        static const char * CancelOnDisconnectType;                         ///< = "CancelOnDisconnectType"
        static const char * TradingSystemName;                              ///< = "TradingSystem.Name"
        static const char * TradingSystemVersion;                           ///< = "TradingSystem.Version"

        static const char * AsyncFileBasedStorageQueueMaxSize;              ///< = "AsyncFileBasedStorage.QueueMaxSize"
        static const char * AsyncFileBasedStorageThreadAffinity;            ///< = "AsyncFileBasedStorage.ThreadAffinity"
        static const char * ThreadingModel;                                 ///< = "ThreadingModel"
        static const char * TcpNoDelayOption;                               ///< = "TcpNoDelayOption"
        static const char * MessageGrouping;                                ///< = "MessageGrouping"
        static const char * FileBasedStorageSegmentSize;                    ///< = "FileBasedStorageSegmentSize"
        static const char * IgnoreFileBasedStorageIntegrityErrors;          ///< = "IgnoreFileBasedStorageIntegrityErrors"
        static const char * KeepAliveInterval;                              ///< = "KeepAliveInterval"
        static const char * CodTimeoutWindow;                               ///< = "CodTimeoutWindow"
        static const char * LicenseFile;                                    ///< = "LicenseFile"
        static const char * LicenseStore;                                   ///< = "LicenseStore"
        static const char * LicenseAlertingDaysBeforeExpiration;            ///< = "LicenseAlertingDaysBeforeExpiration"
        static const char * LocalNetworkInterface;                          ///< = "LocalNetworkInterface"
        static const char * LogFileName;                                    ///< = "Log.FileName"
        static const char * LocalTimeUsage;                                 ///< = "LocalTimeUsage"
        static const char * LogBeforeSending;                               ///< = "Log.BeforeSending"
        static const char * ReasonableTransmissionTime;                     ///< = "ReasonableTransmissionTime"
        static const char * ReceiveSpinningTimeout;                         ///< = "ReceiveSpinningTimeout"
        static const char * ReconnectAttempts;                              ///< = "Reconnect.Attempts"
        static const char * ReconnectInterval;                              ///< = "Reconnect.Interval"
        static const char * SendSpinningTimeout;                            ///< = "SendSpinningTimeout"
        static const char * ThreadPoolAffinity;                             ///< = "ThreadPool.Affinity"
        static const char * ThreadPoolSize;                                 ///< = "ThreadPool.Size"
        static const char * ThreadPoolPriority;                             ///< = "ThreadPool.Priority"
        static const char * ThreadPoolPolicy;                               ///< = "ThreadPool.Policy"
        static const char * SocketReceiveBufferSize;                        ///< = "Socket.ReceiveBufferSize"
        static const char * SocketSendBufferSize;                           ///< = "Socket.SendBufferSize"
        static const char * StorageDirectory;                               ///< = "Log.Directory"
        static const char * ReportNewMessagesWhileWaitingForMissedMessages; ///< = "ReportNewMessagesWhileWaitingForMissedMessages"
        static const char * MessagingSchemaVersion;                         ///< = "MessagingSchemaVersion"
        static const char * LocalPortRange;                                 ///< = "LocalPortRange"
        static const char * UseSpinLock;                                    ///< = "UseSpinLock"
        static const char * EnableRxTimestamp;                              ///< = "EnableRxTimestamp"
    };

private:
    void processLicenseStores(const std::string& licenseStore);

    std::string accessKey_;

    unsigned asyncFileBasedStorageQueueMaxSize_;

    CpuIndexes asyncFileBasedStorageThreadAffinity_;

    bool createEngineLogFile_;

    Messaging::UInt64 fileBasedStorageSegmentSize_;

    Messaging::UInt32 enteringFirm_;

    Messaging::CancelOnDisconnectType::Enum cancelOnDisconnectType_;

    bool ignoreFileBasedStorageIntegrityErrors_;

    unsigned keepAliveInterval_;

    unsigned codTimeoutWindow_;

    unsigned licenseAlertingDaysBeforeExpiration_;

    std::string licenseFilePath_;

    LicenseStores licenseStores_;

    std::string localNetworkInterface_;

    bool localTimeUsage_;

    bool logBeforeSending_;

    std::string logFileName_;

    unsigned messageGrouping_;

    unsigned reasonableTransmissionTime_;

    int receiveSpinningTimeout_;

    unsigned reconnectAttempts_;

    unsigned reconnectInterval_;

    bool reportNewMessagesWhileWaitingForMissedMessages_;

    int sendSpinningTimeout_;

    Messaging::SessionID sessionId_;

    int socketReceiveBufferSize_;

    int socketSendBufferSize_;

    std::string storageDirectory_;

    bool tcpNoDelayOption_;

    ThreadingModel::Enum threadingModel_;

    CpuIndexes threadPoolAffinity_;

    int threadPoolPolicy_;

    int threadPoolPriority_;

    unsigned threadPoolSize_;

    std::string tradingSystemName_;

    std::string tradingSystemVersion_;

    std::pair<Port, Port> localPortRange_;

    Messaging::SchemaVersion messagingSchemaVersion_;

    bool useSpinLock_;

    bool enableRxTimestamp_;
};

}
}
}
