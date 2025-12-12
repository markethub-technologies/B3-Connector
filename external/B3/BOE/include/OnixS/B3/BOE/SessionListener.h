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
#include <OnixS/B3/BOE/SessionStateId.h>

#include <string>

namespace OnixS {
namespace B3 {
namespace BOE {

ONIXS_B3_BOE_API_DECL(class, Session);

/**
 * Session Warning Reason.
 */
struct SessionWarningReason
{
    enum Enum
    {
        /// General session-related warning.
        GeneralWarning,

        /// Incoming message sequence gap is detected.
        SequenceGapIsDetected,

        /// Unexpected SBE Schema version is received from B3.
        UnexpectedSbeSchemaVersion,

        /// Received an unexpected `NextSeqNo` value.
        UnexpectedNextSeqNo,

        /// Received an unsupported message type.
        UnsupportedMessageType,

        /// The incoming message has a sequence number is out of the expected  range and the <i>PossRetransFlag</i> is
        /// set, it indicates a warning. It is strongly recommended that the session be terminated and manual intervention
        /// be initiated.
        MsgSeqNumOutOfRange,

        /// Received a message with an unexpected sessionId
        UnexpectedSessionId,

        /// Raised when the `KeepAliveInterval` has expired and no keep alive message is received.
        ReceiveTimeoutIsDetected,

        /// Exception was thrown from user's event handler.
        ExceptionInEventHandler,

        /// An exception is thrown from the user-provided Session Storage
        PluggableSessionStorageException,

        /// Session state cannot be restored.
        RestoreSessionStateWarning,

        /// Raised when the AsyncFileBasedStorage queue exceeded `SessionSettings::asyncFileBasedStorageQueueMaxSize`
        AsyncFileBasedStorageQueueOverflow,

        /// Raised when the license will expire in less than `SessionSettings::licenseAlertingDaysBeforeExpiration`
        LicenseExpiration,

        /// The <i>Retransmit Reject</i> message is received in reply to the <i>Retransmit Request</i> message.
        RetransmitReject,

        /// Telecommunication link error is detected.
        LinkErrorIsDetected,

        /// After sending the initial Negotiate or Establish message the telecommunication link error is detected.
        LinkErrorIsDetectedDuringSessionEstablishment,

        /// Error setting socket option
        CannotSetSocketOption,

        /// Cannot backup the file.
        CannotBackup,

        /// Session state cannot be restored.
        CannotRestoreSessionState,
    };

    ONIXS_B3_BOE_EXPORTED static const char* toString(Enum type) ONIXS_B3_BOE_NOTHROW;
};

/**
 * Session Error Reason.
 */
struct SessionErrorReason
{
    enum Enum
    {
        /// Internal error
        InternalError,

        /// A general session-related error.
        GeneralError,

        /// First message received is not the <i>NegotiationResponse</i> or <i>EstablishmentAck</i> message.
        UnexpectedMessageType,

        /// The <i>Negotiation Reject</i> message is received in reply to the <i>Negotiation</i> message.
        NegotiationReject,

        /// The <i>Establishment Reject</i> message is received in reply to the <i>Establish</i> message.
        EstablishmentReject,

        /// The <i>Terminate</i> message is received in reply to the <i>Establish</i> message.
        TerminateInReplyOnEstablish,

        /// The incoming message has a sequence number less than expected and the <i>PossRetransFlag</i> is not
        /// set, it indicates a serious error.
        /// The incoming message has a sequence number less than expected and the <i>PossRetransFlag</i> is not set, it
        /// indicates a serious error. It is strongly recommended that the session be terminated and manual intervention
        /// be initiated.
        MsgSeqNumTooLow,

        /// Connection cannot be restored.
        CannotRestoreConnection,

        /// Connection cannot be established.
        CannotEstablishConnection,

        /// Exception during processing of an incoming message.
        ExceptionDuringProcessingOfIncomingMessage,

        /// Received an invalid incoming message.
        DecodingError,

        /// When two times the `KeepAliveInterval` has expired and no keep alive
        /// message is received then the session is terminated ungracefully and will need to be re-established.
        KeepAliveIntervalLapsed,

        /// Telecommunication link error is detected.
        LinkErrorIsDetected,

        /// After sending the initial Negotiate or Establish message the telecommunication link error is detected.
        LinkErrorIsDetectedDuringSessionEstablishment,

        /// The Exchange sent the initial Terminate message.
        ExchangeInitiatedTerminateMessage,

        /// The maximum size of the incoming message gap queue is exceeded.
        IncomingMessageGapQueueOverflow,

        /// An exception is thrown from the user-provided Session Storage
        PluggableSessionStorageException,

        /// A message with unexpected sessionVerId is received.
        UnexpectedSessionVerId,

        /// Session state cannot be restored.
        CannotRestoreSessionState,
    };

    ONIXS_B3_BOE_EXPORTED static const char* toString(Enum type) ONIXS_B3_BOE_NOTHROW;
};

/// Represents a timestamp of the received data.
/// If the source is `None`, no timestamp is available.
struct ReceivedDataTimestamp
{
    enum Source
    {
        /// No timestamp available.
        None,

        /// Timestamp provided by the OS kernel / user-level network stack.
        Software,

        /// Timestamp provided by the network card.
        Hardware
    };

    /// The timestamp.
    Messaging::Timestamp time_;
    Source source_;

    /// \return a human-readable presentation.
    ONIXS_B3_BOE_EXPORTED std::string toString() const;
};


/// Session's Listener.
class ONIXS_B3_BOE_EXPORTED SessionListener
{
public:
    virtual void onNotApplied(const Messaging::NotApplied8 & /*msg*/, Session* /*sn*/) {}

    /// Invoked when NegotiateResponse2 message has received.
    virtual void onNegotiateResponse(const Messaging::NegotiateResponse2&, Session* /*sn*/){}

    /// Invoked when NegotiateReject3 message has received.
    virtual void onNegotiateReject(const Messaging::NegotiateReject3&, Session* /*sn*/){}

    /// Invoked when EstablishAck5 message has received.
    virtual void onEstablishAck(const Messaging::EstablishAck5&, Session* /*sn*/){}

    /// Invoked when EstablishReject6 message has received.
    virtual void onEstablishReject(const Messaging::EstablishReject6&, Session* /*sn*/){}

    /// Invoked when Terminate7 message has received.
    virtual void onTerminate(const Messaging::Terminate7&, Session* /*sn*/){}

    /// Invoked when Sequence9 message has received.
    virtual void onSequence(const Messaging::Sequence9&, Session* /*sn*/){}

    /// Invoked when Retransmission13 message has received.
    virtual void onRetransmission(const Messaging::Retransmission13&, Session* /*sn*/){}

    /// Invoked when RetransmitReject14 message has received.
    virtual void onRetransmitReject(const Messaging::RetransmitReject14&, Session* /*sn*/){}

    /// Invoked when ExecutionReportNew200 message has received.
    virtual void onExecutionReportNew(const Messaging::ExecutionReportNew200&, Session* /*sn*/){}

    /// Invoked when ExecutionReportModify201 message has received.
    virtual void onExecutionReportModify(const Messaging::ExecutionReportModify201&, Session* /*sn*/){}

    /// Invoked when ExecutionReportCancel202 message has received.
    virtual void onExecutionReportCancel(const Messaging::ExecutionReportCancel202&, Session* /*sn*/){}

    /// Invoked when ExecutionReportTrade203 message has received.
    virtual void onExecutionReportTrade(const Messaging::ExecutionReportTrade203&, Session* /*sn*/){}

    /// Invoked when ExecutionReportReject204 message has received.
    virtual void onExecutionReportReject(const Messaging::ExecutionReportReject204&, Session* /*sn*/){}

    /// Invoked when ExecutionReportForward205 message has received.
    virtual void onExecutionReportForward(const Messaging::ExecutionReportForward205&, Session* /*sn*/){}

    /// Invoked when BusinessMessageReject206 message has received.
    virtual void onBusinessMessageReject(const Messaging::BusinessMessageReject206&, Session* /*sn*/){}

    /// Invoked when SecurityDefinitionResponse301 message has received.
    virtual void onSecurityDefinitionResponse(const Messaging::SecurityDefinitionResponse301&, Session* /*sn*/){}

    /// Invoked when QuoteRequest401 message has received.
    virtual void onQuoteRequest(const Messaging::QuoteRequest401&, Session* /*sn*/){}

    /// Invoked when QuoteStatusReport402 message has received.
    virtual void onQuoteStatusReport(const Messaging::QuoteStatusReport402&, Session* /*sn*/){}

    /// Invoked when Quote403 message has received.
    virtual void onQuote(const Messaging::Quote403&, Session* /*sn*/){}

    /// Invoked when QuoteCancel404 message has received.
    virtual void onQuoteCancel(const Messaging::QuoteCancel404&, Session* /*sn*/){}

    /// Invoked when QuoteRequestReject405 message has received.
    virtual void onQuoteRequestReject(const Messaging::QuoteRequestReject405&, Session* /*sn*/){}

    /// Invoked when PositionMaintenanceReport503 message has received.
    virtual void onPositionMaintenanceReport(const Messaging::PositionMaintenanceReport503&, Session* /*sn*/){}

    /// Invoked when AllocationReport602 message has received.
    virtual void onAllocationReport(const Messaging::AllocationReport602&, Session* /*sn*/){}

    /// Invoked when OrderMassActionReport702 message has received.
    virtual void onOrderMassActionReport(const Messaging::OrderMassActionReport702&, Session* /*sn*/){}

    /// Called as soon as bytes are received from the wire.
    virtual void onReceivedBytes(const char * /*bytes*/, size_t /*size*/, const ReceivedDataTimestamp& /*timestamp*/, Session * /*sn*/) {}

    /// Called when the SBE message is about to be sent to the wire.
    virtual void onMessageSending(char * /*bytes*/, size_t /*size*/, Session * /*sn*/) {}

    /// Called when the session changes its state.
    virtual void onStateChange(SessionStateId::Enum /*newState*/, SessionStateId::Enum /*prevState*/, Session * /*sn*/) {}

    /// Called when an error condition is detected.
    /// \note the message argument provided is a message which caused the problem, must be checked to be valid before usage
    virtual void onError(SessionErrorReason::Enum /*reason*/, const std::string & /*description*/, Session * /*sn*/, Messaging::SbeMessage) {}

    /// Called when a warning condition is detected.
    /// \note the message argument provided is a message which caused the problem, must be checked to be valid before usage
    virtual void onWarning(SessionWarningReason::Enum /*reason*/, const std::string & /*description*/, Session * /*sn*/, Messaging::SbeMessage) {}

protected:
    virtual ~SessionListener() = 0;
};

}
}
}
