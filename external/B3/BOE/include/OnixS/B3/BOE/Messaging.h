#pragma once
// Copyright Onix Solutions Limited [OnixS]. All rights reserved.
//
// This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
// and international copyright treaties.
//
// Access to and use of the software is governed by the terms of the applicable OnixS Software
// Services Agreement (the Agreement) and Customer end user license agreements granting
// a non-assignable, non-transferable and non-exclusive license to use the software
// for it's own data processing purposes under the terms defined in the Agreement.
//
// Except as otherwise granted within the terms of the Agreement, copying or reproduction of any part
// of this source code or associated reference material to any other location for further reproduction
// or redistribution, and any amendments to this copyright notice, are expressly prohibited.
//
// Any reproduction or redistribution for sale or hiring of the Software not in accordance with
// the terms of the Agreement is a violation of copyright law.
//

#include <OnixS/B3/BOE/Defines.h>

#include <OnixS/B3/BOE/messaging/Aliases.h>
#include <OnixS/B3/BOE/messaging/Decimal.h>
#include <OnixS/B3/BOE/messaging/Decimal.Operations.h>
#include <OnixS/B3/BOE/messaging/Integral.h>
#include <OnixS/B3/BOE/messaging/MessageBatch.h>
#include <OnixS/B3/BOE/messaging/MessageHolder.h>
#include <OnixS/B3/BOE/messaging/MessageSizeTraits.h>
#include <OnixS/B3/BOE/messaging/Serialization.h>
#include <OnixS/B3/BOE/messaging/StrRef.h>
#include <OnixS/B3/BOE/messaging/Watch.h>
#include <OnixS/B3/BOE/messaging/Composites.h>
#include <OnixS/B3/BOE/messaging/Fields.h>
#include <OnixS/B3/BOE/messaging/MaxMessageSize.h>
#include <OnixS/B3/BOE/messaging/MessageSerialization.h>
#include <OnixS/B3/BOE/messaging/SbeMessage.h>
#include <OnixS/B3/BOE/messaging/SimpleOpenFramingHeader.h>
#include <OnixS/B3/BOE/messaging/Time.h>
#include <OnixS/B3/BOE/messaging/Decimal.h>
#include <OnixS/B3/BOE/messaging/Memory.h>
#include <OnixS/B3/BOE/messaging/Messages.h>
#include <OnixS/B3/BOE/messaging/SchemaTraits.h>
#include <OnixS/B3/BOE/messaging/String.h>
#include <OnixS/B3/BOE/messaging/Typification.h>
#include <OnixS/B3/BOE/messaging/Validation.h>
#include <OnixS/B3/BOE/messaging/NetworkMessage.h>

namespace OnixS {
namespace B3 {
namespace BOE {

typedef Messaging::UInt32 SeqNumber;

struct SeqNumberTraits {
    static ONIXS_B3_BOE_CONST_OR_CONSTEXPR SeqNumber Zero = 0;
    static ONIXS_B3_BOE_CONST_OR_CONSTEXPR SeqNumber InvalidValue = SeqNumber(-1);

    ONIXS_B3_BOE_CONSTEXPR
    static bool isValid(SeqNumber seqNumber) ONIXS_B3_BOE_NOTHROW {
        return seqNumber != InvalidValue;
    }
};

}
}
}
