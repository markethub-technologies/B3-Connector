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

#include <OnixS/B3/BOE/ABI.h>

#include <string>
#include <stdint.h>

namespace OnixS {
namespace B3 {
namespace BOE {

// Forward declarations
class TcpDirectStack;

/**
* TCPDirect Attributes to pass configuration details (a wrapper around the `zf_attr` struct).
*
* The default values for attributes may be overridden by setting the
* environment variable `ZF_ATTR`.  For example:
*
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.sh}
* ZF_ATTR="interface=enp4s0f0;log_level=3;reactor_spin_count=1"
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
class ONIXS_B3_BOE_EXPORTED TcpDirectAttr
{
public:
    /** Allocates an attribute object.
    *
    * \throws std::bad_alloc if memory could not be allocated.
    * \throws std::runtime_error if the `ZF_ATTR` environment variable is malformed.
    */
    TcpDirectAttr();

    ~TcpDirectAttr();

    TcpDirectAttr(const TcpDirectAttr & other);

    TcpDirectAttr & operator=(const TcpDirectAttr & other);

    /** Gets a string attribute.
    *
    * \param name Name of the attribute.
    *
    * \throws std::logic_error If @p name is not a valid attribute name or if @p name does not have a string type.
    */
    std::string getString(const std::string & name);

    /** Sets the attribute to the given value.
    *
    * \param name Name of the attribute.
    * \param value New value for the attribute (may be NULL).
    *
    * \throws std::logic_error If @p name is not a valid attribute name or if the attribute is not a string attribute.
    */
    void set(const std::string & name, const std::string & value);

    /** Gets an integer attribute.
    *
    * \param name Name of the attribute.
    *
    * \throws std::logic_error If @p name is not a valid attribute name or if @p name does not have an integer type.
    */
    int64_t getInt(const std::string & name);

    /** Sets the attribute to the given value.
    *
    * \param name Name of the attribute.
    * \param value New value for the attribute.
    *
    * \throws std::logic_error If @p name is not a valid attribute name.
    * \throws std::domain_error If @p value is not within the range of values this attribute can take.
    */
    void set(const std::string & name, uint64_t value);

private:
    class Impl;
    Impl * const impl_;

    friend class TcpDirectStack;
};

}
}
}
