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

#include <exception>

#include <OnixS/B3/MarketData/UMDF/ABI.h>
#include <OnixS/B3/MarketData/UMDF/Compiler.h>


namespace OnixS
{
    namespace B3
    {
        namespace MarketData
        {
            namespace UMDF
            {
                /// Basic exception class for this namespace
                class ONIXS_B3_UMDF_MD_THROWABLE Exception: public std::exception
                {
                    public:
                        /// Constructor
                        Exception (const char* method_name, const char* message);

                        /// Copy constructor
                        Exception (const Exception&);

                        /// Destructor
                        ~Exception () ONIXS_B3_UMDF_MD_NOTHROW ONIXS_B3_UMDF_MD_OVERRIDE;

                        /// Assignment
                        Exception& operator = (const Exception&);

                        /// Returns information about error
                        const char* what () const ONIXS_B3_UMDF_MD_NOTHROW ONIXS_B3_UMDF_MD_OVERRIDE;

                        /// Add information about context of exception
                        void touch (const char* method_name);

                    private:
                        struct Implementation;

                        Implementation* impl_;
                };

                /// Argument value error
                class ONIXS_B3_UMDF_MD_THROWABLE ArgumentException: public Exception
                {
                    public:
                        /// Constructor
                        ArgumentException (const char* source, const char* message);

                        /// Constructor
                        ArgumentException (const char* source, const char* argument_name, const char* value, const char* comment = "");

                        /// Constructor
                        ArgumentException (const char* source, const char* argument_name, int value, const char* comment = "");

                        /// Constructor
                        ArgumentException (const char* source, const char* argument_name, unsigned int value, const char* comment = "");

                        /// Constructor
                        ArgumentException (const char* source, const char* argument_name, double value, const char* comment = "");
                };

                /// Operation exception
                class ONIXS_B3_UMDF_MD_THROWABLE OperationException: public Exception
                {
                    public:
                        /// Constructor
                        OperationException (const char* source, const char* message);
                };
            }
        }
    }
}
