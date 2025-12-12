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

#include <OnixS/B3/BOE/Session.h>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace AdHoc {

#if !(defined(ONIXS_B3_BOE_DOXYGEN) && ONIXS_B3_BOE_DOXYGEN)

/**
* Session helper.
*/
struct SessionHelper
{
    /**
    * Sends the Retransmit Request message.
    *
    * \note The handler sends Retransmit Request messages automatically per the B3 BOE protocol.
    * This method should be used on an ad hoc basis only.
    */
    static void sendRetransmitRequest(Session& sn, UInt64 sessionVerId, SeqNumber from, SeqNumber to)
    {
         sn.sendRetransmitRequest(sessionVerId, from, to);
    }
};

#endif

}}}}
