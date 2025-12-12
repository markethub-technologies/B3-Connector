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

#include <OnixS/B3/MarketData/UMDF/ABI.h>

#include <string>

namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {

                /// Known (selected) error codes.
                struct ONIXS_B3_UMDF_MD_API ErrorCode
                {
                    /// @copydoc ErrorCode
                    enum Enum
                    {
                        General = 1, ///< Identifiers errors of generic nature.
                        NotLicensed ///< Indicates License-related issues like there's no license available or license has been expired.
                    };
                };

                /// Returns string representation of ErrorCode value.
                ONIXS_B3_UMDF_MD_API std::string enumToString (ErrorCode::Enum);

                /// Defines an interface through which the Handler notifies subscribers
                /// about errors occurred while processing messages.
                class ErrorListener
                {
                    public:
                        /// Implement this member to get notified about errors.
                        /// @param code identifies error occurred while processing messages.
                        /// @param description supplies notes on occurred error.
                        /// @note Errors mean that the Handler is not capable to recover from errors by itself 
                        /// and have to be restarted manually.
                        virtual void onError (ErrorCode::Enum code, const std::string& description) = 0;

                    protected:
                        /// Class provides an interface for handling errors in subscriptions.
                        /// It doesn't provide an interface for instance deletion. However,
                        /// since C++ doesn't have a pure interface concept, the destructor will be
                        /// generated anyway. We can only control proper use of it. For this
                        /// reason we hide from public use and make it available for descendants.
                        virtual ~ErrorListener() {}
                };

            }
        }
    }
}
