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

#include <OnixS/B3/BOE/messaging/Fields.h>

ONIXS_B3_BOE_MESSAGING_NAMESPACE_BEGIN

// B3 SBE Version 1.0 Little-endian
ONIXS_B3_BOE_CONST_OR_CONSTEXPR UInt16 B3BOESbeEncodingType = 0xEB50;

ONIXS_B3_BOE_DATA_PACKING_BEGIN(1)

/// Simple Open Framing Header.
ONIXS_B3_BOE_LTWT_CLASS SimpleOpenFramingHeader
{
public:
    /// Initializes the header.
    void setup(UInt16 sz) ONIXS_B3_BOE_NOTHROW
    {
        size(sz);
        encodingType = B3BOESbeEncodingType;
    }

    /// Sets the size.
    void size(UInt16 val) ONIXS_B3_BOE_NOTHROW
    {
        msgSize = val;
    }

    /// \return the size
    UInt16 size() const ONIXS_B3_BOE_NOTHROW
    {
        return msgSize;
    }

    /// \return the encoding type.
    UInt16 encoding() const ONIXS_B3_BOE_NOTHROW
    {
        return encodingType;
    }

private:
    UInt16 msgSize;
    UInt16 encodingType;
};

ONIXS_B3_BOE_DATA_PACKING_END

/// Serializes SimpleOpenFramingHeader into a string.
ONIXS_B3_BOE_EXPORTED
void toStr(std::string&, const SimpleOpenFramingHeader&);

inline
std::string toStr(const SimpleOpenFramingHeader& header)
{
    std::string res;
    toStr(res, header);
    return res;
}

ONIXS_B3_BOE_MESSAGING_NAMESPACE_END
