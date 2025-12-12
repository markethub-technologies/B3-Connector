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
#include <vector>

namespace OnixS {
namespace B3 {
namespace BOE {
namespace Scheduling {

/// Counterparty host name.
typedef std::string Host;

/// Counterparty port.
typedef unsigned short Port;

/// Parameters required to establish
/// the connection with the counterparty.
class ONIXS_B3_BOE_EXPORTED Counterparty
{
public:
    /// Initializes a blank instance.
    Counterparty();

    /// Fully identified counterparty.
    Counterparty(const Host& host, Port port);

    /// Initializes as clone of the given instance.
    Counterparty(const Counterparty& other);

    ~Counterparty();

    /// \return remote host.
    const Host& host() const ONIXS_B3_BOE_NOTHROW;

    /// \return port number.
    Port port() const ONIXS_B3_BOE_NOTHROW;

    Counterparty& operator=(const Counterparty& other);

private:
    Host* host_;
    Port port_;
};

/// Ordered series of counterparties.
typedef std::vector<Counterparty> Counterparties;

/// Connection-related settings.
class ONIXS_B3_BOE_EXPORTED SessionConnectionSettings
{
public:
    /// Constructor.
    ///
    /// \param host the remote host to which session must connect to.
    /// \param port the port number to which session must connect to.
    SessionConnectionSettings(const Host& host, Port port);

    SessionConnectionSettings(const SessionConnectionSettings& other);

    virtual ~SessionConnectionSettings();

    /// Adds the counterparty.
    SessionConnectionSettings& addCounterparty(const Host& host, Port port);

    /// \return Counterparties.
    const Counterparties& counterparties() const ONIXS_B3_BOE_NOTHROW;

    SessionConnectionSettings& operator=(const SessionConnectionSettings& other);

protected:
    SessionConnectionSettings();

private:
    Counterparties* counterparties_;
};


inline const Counterparties& SessionConnectionSettings::counterparties() const ONIXS_B3_BOE_NOTHROW
{
    return *counterparties_;
}

}
}
}
}
