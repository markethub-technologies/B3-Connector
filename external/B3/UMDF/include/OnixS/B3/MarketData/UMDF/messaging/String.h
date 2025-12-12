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

#include <string>

#include <OnixS/B3/MarketData/UMDF/ABI.h>

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN

/// Character type alias.
typedef char Char;

/// Appends the character to the given std::string instance.
inline
void toStr(std::string& str, Char character)
{
    str.append(1, character);
}

/// Appends strings.
inline
void toStr(std::string& str, const std::string& value)
{
    str.append(value);
}

/// Constructs a std::string from the given character.
ONIXS_B3_UMDF_MD_NODISCARD
inline std::string toStr(Char character)
{
    return std::string(1, character);
}

ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END
