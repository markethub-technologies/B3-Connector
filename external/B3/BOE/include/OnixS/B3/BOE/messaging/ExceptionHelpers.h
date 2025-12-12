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
#include <OnixS/B3/BOE/messaging/SchemaTraits.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// Message type (template) identification.
typedef MessageHeader::TemplateId MessageTemplateId;

/// \private
/// Throws an exception on a bad repeating group.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwBadBinaryBlock();

/// \private
/// Throws an exception on a bad repeating group entry.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwDisallowedField();

/// \private
/// Raises an exception when the given binary block is too small.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwBinaryBlockIsTooSmall(MessageSize actual, MessageSize required);

/// \private
/// Raises an exception when the given binary block is too small.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwBinaryBlockIsTooSmall(MessageSize actual, MessageSize required, const Char*);

/// \private
/// Raises an exception on a bad message version.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwBadMessageVersion(SchemaVersion messageVersion, SchemaVersion minimalVersion);

/// \private
/// Raises an exception on a bad message id.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwBadSchemaId(SchemaId expected, SchemaId provided);

/// \private
/// Throws an exception on a bad repeating group entry.
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwNotEnoughSpace();

/// \private
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_COLDPATH
ONIXS_B3_BOE_NORETURN
void throwBadConversion(const Char* typeName);


/// \private
/// \throw DecodingError
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NORETURN
ONIXS_B3_BOE_COLDPATH
void throwIncorrectEncoding(Messaging::UInt16 encoding, const void* data, MessageSize size);

/// \private
/// \throw UnsufficientDataError
ONIXS_B3_BOE_EXPORTED
ONIXS_B3_BOE_NORETURN
ONIXS_B3_BOE_COLDPATH
void throwNetPacketIsTooSmall(MessageSize actual, MessageSize required);

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
