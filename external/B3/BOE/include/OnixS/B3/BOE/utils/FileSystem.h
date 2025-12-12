/*
* Copyright Onix Solutions Limited [OnixS]. All rights reserved.
*
* This software owned by Onix Solutions Limited [OnixS] and is protected by copyright law
* and international copyright treaties.
*
* Access to and use of the software is governed by the terms of the applicable ONIXS Software
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

#include <vector>
#include <string>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Filesystem {

/// Gathers files which are stored in a given folder.
ONIXS_B3_BOE_EXPORTED
void gatherFiles(std::vector<std::string>* gatheredFiles, const std::string& root, const std::string& extension);

/// \return true if provided path is a directory
ONIXS_B3_BOE_EXPORTED
bool isDirectory(const std::string& path);

/// \return true if provided entry exists
ONIXS_B3_BOE_EXPORTED
bool exist(const std::string& entry);


}}}}
