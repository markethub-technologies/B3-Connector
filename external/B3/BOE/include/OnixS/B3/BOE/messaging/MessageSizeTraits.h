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

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/Compiler.h>

#include <OnixS/B3/BOE/messaging/Composites.h>
#include <OnixS/B3/BOE/messaging/Forwards.h>


ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

#if defined(ONIXS_B3_BOE_CXX11)

/// Assume the credentials filed of the message is empty.
template <typename Message>
struct HasEmptyCredentials
{
    static constexpr bool UseCustomValue = true;

    static constexpr
    UInt16 calculateMaxMessageSize()
    {
        return
            Message::blockLength(Message::Schema::Version)
            + MessageHeader::Size
            + Message::getMinimalVariableFieldsSize(Message::Schema::Version);
    }
};

/// Assume the message has a constant size.
template <typename Message>
struct HasNoVariableFieldsOrGroups
{
    static constexpr bool UseCustomValue = true;

    static constexpr
        UInt16 calculateMaxMessageSize()
    {
        return
            Message::blockLength(Message::Schema::Version)
            + MessageHeader::Size;
    }
};

/// Traits for calculating the buffer size of a message.
template <typename Message> struct MaxMessageSizeTraits;

/*
/// \private
template <>
struct MaxMessageSizeTraits<Negotiate1> : HasEmptyCredentials<Negotiate1> {};

/// \private
template <>
struct MaxMessageSizeTraits<Establish4> : HasEmptyCredentials<Establish4> {};

/// \private
template <>
struct MaxMessageSizeTraits<Sequence9> : HasNoVariableFieldsOrGroups<Sequence9> {};

/// \private
template <>
struct MaxMessageSizeTraits<Terminate7> : HasNoVariableFieldsOrGroups<Terminate7> {};

/// \private
template <>
struct MaxMessageSizeTraits<Retransmission13> : HasNoVariableFieldsOrGroups<Retransmission13> {};
*/

#endif

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
