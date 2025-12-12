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

#include <OnixS/B3/BOE/messaging/Composites.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

/// SBE-encoded data version type.
typedef
MessageHeader::Version
SchemaVersion;

typedef
MessageHeader::SchemaId
SchemaId;

/// Attributes of SBE message schema.
ONIXS_B3_BOE_LTWT_STRUCT
SchemaTraits
{
    /// Identifier of the messages schema.
    enum { Id = 1 };

    /// Version of the messages schema.
    enum { Version = 5 };

    /// The minimal SBE Schema version supported by the SDK.
    /// Messages of lower versions will not be processed
    /// as they may miss fields required for the correct data
    /// handling.
    enum { MinimalVersion = 3 };
};

#define ONIXS_B3_BOE_SCHEMA_DESCRIPTION  "B3 Binary Entrypoint FIXP messages"

#define ONIXS_B3_BOE_SCHEMA_SEMANTIC_VERSION  "8.3.2"


ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
