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

#include <OnixS/B3/BOE/Defines.h>
#include <OnixS/B3/BOE/SessionListener.h>
#include <OnixS/B3/BOE/messaging/Fields.h>

#include <string>

#if WIN32
#pragma warning(push)
#pragma warning(disable : 4275)
#pragma warning(disable : 4251)
#endif

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Exceptions{

/**
 * A Session-related exception.
 */
class ONIXS_B3_BOE_EXPORTED SessionException : public std::exception
{
public:
    SessionException(SessionErrorReason::Enum reason, const std::string& message);

    SessionException(SessionErrorReason::Enum reason, const std::string& message, const std::exception& cause);

    ~SessionException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    const char* what() const ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE;

    SessionErrorReason::Enum reason() const ONIXS_B3_BOE_NOTHROW
    {
        return reason_;
    }

    const std::string& toString() const ONIXS_B3_BOE_NOTHROW
    {
        return message_;
    }

private:
    std::string message_;
    SessionErrorReason::Enum reason_;
};


class ONIXS_B3_BOE_EXPORTED SbeMessageAttachedExceptionBase
    : public SessionException
{
public:
    SbeMessageAttachedExceptionBase(SessionErrorReason::Enum reason, const std::string& message, Messaging::SbeMessage sbeMessage);

    Messaging::SbeMessage receivedMessage() const;

    ~SbeMessageAttachedExceptionBase() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE = 0;

private:
    std::vector<unsigned char> buffer_;
};

template <typename MessageType>
class TypedSbeMessageAttachedExceptionBase : public SbeMessageAttachedExceptionBase
{
public:
    TypedSbeMessageAttachedExceptionBase(SessionErrorReason::Enum reason, const std::string& message, Messaging::SbeMessage sbeMessage)
        : SbeMessageAttachedExceptionBase(reason, message, sbeMessage)
    {}

    MessageType receivedMessage() const
    {
        return Messaging::typify<MessageType>(SbeMessageAttachedExceptionBase::receivedMessage());
    }
};

/**
 * An unexpected message type is received.
 */
class ONIXS_B3_BOE_EXPORTED UnexpectedMessageTypeException
  : public SbeMessageAttachedExceptionBase
{
public:
    explicit UnexpectedMessageTypeException(Messaging::SbeMessage message);

    Messaging::MessageTemplateId templateId() const;

    ~UnexpectedMessageTypeException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;
};

/**
 * A telecommunication link error is detected.
 */
class ONIXS_B3_BOE_EXPORTED LinkErrorException
  : public SessionException
{
public:
    explicit LinkErrorException(const std::string& rejectReason);

    ~LinkErrorException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;
};

/**
 * An unexpected message sequence number is detected.
 */
class ONIXS_B3_BOE_EXPORTED UnexpectedSequenceNumberException
  : public SbeMessageAttachedExceptionBase
{
public:
    UnexpectedSequenceNumberException(Messaging::SbeMessage receivedMessage, const std::string& rejectReason,
        SeqNumber actualSeqNum, SeqNumber expectedSeqNum, Messaging::UInt64 sessionVerId);

    ~UnexpectedSequenceNumberException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    SeqNumber actualSeqNum() const ONIXS_B3_BOE_NOTHROW
    {
        return actualSeqNum_;
    }

    SeqNumber expectedSeqNum() const ONIXS_B3_BOE_NOTHROW
    {
        return expectedSeqNum_;
    }

    Messaging::UInt64 sessionVerId() const ONIXS_B3_BOE_NOTHROW
    {
        return sessionVerId_;
    }

private:
    SeqNumber actualSeqNum_;
    SeqNumber expectedSeqNum_;
    Messaging::UInt64 sessionVerId_;
};

/**
 * A response has not been received during the specified timeout.
 */
class ONIXS_B3_BOE_EXPORTED ResponseTimeoutException
  : public SessionException
{
public:
    explicit ResponseTimeoutException(const std::string& rejectReason, int timeoutMilliseconds)
      : SessionException(SessionErrorReason::LinkErrorIsDetected, rejectReason)
      , timeout_(timeoutMilliseconds)
    {}

    ~ResponseTimeoutException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    /// @return timeout in milliseconds
    int timeout() const ONIXS_B3_BOE_NOTHROW
    {
        return timeout_;
    }

private:
    int timeout_; ///< timeout in milliseconds.
};


/**
 * The program is finishing its execution.
 */
class ONIXS_B3_BOE_EXPORTED ProgramIsFinishingException
  : public SessionException
{
public:
    ProgramIsFinishingException();

    ~ProgramIsFinishingException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;
};

/// The telecommunication link cannot be established.
class ONIXS_B3_BOE_EXPORTED CannotEstablishLinkException
  : public SessionException
{
public:
    /// Constructor.
    ///
    /// \param errCode system error code (if present).
    /// \param rejectReason the telecommunication link error description.
    CannotEstablishLinkException(int errCode, const std::string& rejectReason);

    ~CannotEstablishLinkException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    int errCode() const ONIXS_B3_BOE_NOTHROW;

private:
    int errCode_;
};


/**
 * The Negotiate message is rejected by the exchange.
 */
class ONIXS_B3_BOE_EXPORTED NegotiateRejectException
    : public TypedSbeMessageAttachedExceptionBase<Messaging::NegotiateReject3>
{
public:
    explicit NegotiateRejectException(Messaging::NegotiateReject3 reject);

    ~NegotiateRejectException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    Messaging::NegotiationRejectCode::Enum errorCodes() const;
};

/**
 * The Establish message is rejected by the exchange.
 */
class ONIXS_B3_BOE_EXPORTED EstablishRejectException
    : public TypedSbeMessageAttachedExceptionBase<Messaging::EstablishReject6>
{
public:
    explicit EstablishRejectException(Messaging::EstablishReject6 reject);

    ~EstablishRejectException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    Messaging::EstablishRejectCode::Enum errorCodes() const;
};

/// Received the Terminate message
/// in reply to the Establish or Negotiate messages.
class ONIXS_B3_BOE_EXPORTED TerminateInReplyOnEstablishException
  : public TypedSbeMessageAttachedExceptionBase<Messaging::Terminate7>
{
public:
    explicit TerminateInReplyOnEstablishException(Messaging::Terminate7 terminate);

    ~TerminateInReplyOnEstablishException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    Messaging::TerminationCode::Enum errorCodes() const;
};

/// Received the BusinessReject message
/// in reply to the Establish or Negotiate messages.
class ONIXS_B3_BOE_EXPORTED BusinessRejectInReplyOnEstablishException
    : public TypedSbeMessageAttachedExceptionBase<Messaging::BusinessMessageReject206>
{
public:
    explicit BusinessRejectInReplyOnEstablishException(Messaging::BusinessMessageReject206 reject);

    ~BusinessRejectInReplyOnEstablishException() ONIXS_B3_BOE_NOTHROW ONIXS_B3_BOE_OVERRIDE ONIXS_B3_BOE_DEFAULT;

    Messaging::RejReason errorCodes() const;

    std::string text() const;
};

}
}
}
}

#if WIN32
#pragma warning(pop)
#endif
