#pragma once
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

#include <OnixS/B3/BOE/ABI.h>
#include <OnixS/B3/BOE/messaging/StrRef.h>

#include <string>
#include <vector>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Encoding {

/// Byte sequence.
typedef std::vector<unsigned char> ByteArray;

/// BASE64 encoding service.
class ONIXS_B3_BOE_EXPORTED Base64Encoding
{
public:
    /// Reconstructs the binary data from a BASE64-encoded string.
    ///
    /// @throw Exception if the string is corrupted or not BASE64-encoded.
    static void decode(ByteArray & decoded, const std::string & encoded);

    /// Reconstructs the binary data from a BASE64-encoded string.
    ///
    /// @throw Exception if the string is corrupted or not BASE64-encoded.
    static void decode(ByteArray & decoded, Messaging::StrRef encoded);
};
}
}
}
}
