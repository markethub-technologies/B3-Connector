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

#include <OnixS/B3/BOE/CompilerDetection.h>
#include <OnixS/B3/BOE/Compiler.h>

#include <vector>
#include <string>
#include <set>
#include <memory>

#if defined(_WIN32) // Windows platform.

#if !defined(STRICT)
#define STRICT
#endif

#include <winsock2.h>

#endif

namespace OnixS {
namespace B3 {
namespace BOE {

typedef unsigned short Port;
/// Type alias for byte.
typedef unsigned char Byte;

/// Sequence of bytes.
typedef std::vector<Byte> Bytes;

#if defined (_WIN32)
/// Type alias for socket handle.
typedef SOCKET Handle;
#else
/// Type alias for socket handle.
typedef int Handle;
#endif

/// Socket option of the SOL_SOCKET level
struct SocketOption {
    SocketOption() ONIXS_B3_BOE_NOTHROW
        : optname(0), optval(ONIXS_B3_BOE_NULLPTR), optlen(0) {}

    SocketOption(int optionName, const void* optionValue, int optionLength) ONIXS_B3_BOE_NOTHROW
        : optname(optionName), optval(optionValue), optlen(optionLength) {}

    int optname;
    const void * optval;
    int optlen;
};

typedef size_t CpuIndex;
typedef std::set<CpuIndex> CpuIndexes;
typedef std::pair<Port, Port> PortRange;

/// Socket options.
typedef std::vector<SocketOption> SocketOptions;

struct ThreadParams {
    std::string name;
    CpuIndexes affinity;
    int priority;
    int policy;

    ThreadParams()
        : priority(0)
      , policy(0)
    {
    }
};

struct PriorityAndPolicyTraits {
    enum Enum {
        UndefinedPriorityAndPolicy = 255
    };
};

template <typename T>
struct PtrTraits
{
#if defined (ONIXS_B3_BOE_CXX11)
    typedef std::unique_ptr<T> UniquePtr;
#else
    typedef std::auto_ptr<T> UniquePtr;
#endif
};

}
}
}
