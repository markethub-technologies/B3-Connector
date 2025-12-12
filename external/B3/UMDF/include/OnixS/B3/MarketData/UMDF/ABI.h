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

#include <OnixS/B3/MarketData/UMDF/Export.h>
#include <OnixS/B3/MarketData/UMDF/Compiler.h>

#if defined (_MSC_VER)
#define ONIXS_B3_UMDF_MD_API_DECL(typeKind, typeName) \
typeKind ONIXS_B3_UMDF_MD_API typeName

#define ONIXS_B3_UMDF_MD_THROWABLE
#else
#define ONIXS_B3_UMDF_MD_API_DECL(typeKind, typeName) \
typeKind typeName

#define ONIXS_B3_UMDF_MD_THROWABLE ONIXS_B3_UMDF_MD_API
#endif

#define ONIXS_B3_UMDF_MD_EXPORTED ONIXS_B3_UMDF_MD_API

// Common part of export-related decorations.

#define \
    ONIXS_B3_UMDF_MD_EXPORTED_CLASS_DECL(typeName) \
    ONIXS_B3_UMDF_MD_EXPORTED_DECL(class, typeName)

#define \
    ONIXS_B3_UMDF_MD_EXPORTED_STRUCT_DECL(typeName) \
    ONIXS_B3_UMDF_MD_EXPORTED_DECL(struct, typeName)

#define \
    ONIXS_B3_UMDF_MD_EXPORTED_CLASS \
    class ONIXS_B3_UMDF_MD_EXPORTED

#define \
    ONIXS_B3_UMDF_MD_EXPORTED_STRUCT \
    struct ONIXS_B3_UMDF_MD_EXPORTED

#define \
    ONIXS_B3_UMDF_MD_INTERNAL_CLASS_DECL(typeName) \
    class typeName

#define \
    ONIXS_B3_UMDF_MD_INTERNAL_STRUCT_DECL(typeName) \
    struct typeName

#if defined (ONIXS_B3_UMDF_MD_LTWT_AS_EXPORTED)

#define \
    ONIXS_B3_UMDF_MD_LTWT_CLASS \
    ONIXS_B3_UMDF_MD_EXPORTED_CLASS

#define \
    ONIXS_B3_UMDF_MD_LTWT_STRUCT \
    ONIXS_B3_UMDF_MD_EXPORTED_STRUCT

#define \
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED \
    /* Nothing */

#define \
    ONIXS_B3_UMDF_MD_LTWT_CLASS_DECL(name) \
    ONIXS_B3_UMDF_MD_EXPORTED_CLASS_DECL(name)

#define \
    ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(name) \
    ONIXS_B3_UMDF_MD_EXPORTED_STRUCT_DECL(name)

#else

#define \
    ONIXS_B3_UMDF_MD_LTWT_CLASS \
    class ONIXS_B3_UMDF_MD_GCC44_SPURIOUS_WARNING_TURNAROUND

#define \
    ONIXS_B3_UMDF_MD_LTWT_STRUCT \
    struct ONIXS_B3_UMDF_MD_GCC44_SPURIOUS_WARNING_TURNAROUND

#define \
    ONIXS_B3_UMDF_MD_LTWT_EXPORTED \
    ONIXS_B3_UMDF_MD_EXPORTED

#define \
    ONIXS_B3_UMDF_MD_LTWT_CLASS_DECL(name) \
    class ONIXS_B3_UMDF_MD_GCC44_SPURIOUS_WARNING_TURNAROUND name

#define \
    ONIXS_B3_UMDF_MD_LTWT_STRUCT_DECL(name) \
    struct ONIXS_B3_UMDF_MD_GCC44_SPURIOUS_WARNING_TURNAROUND name

#endif // ONIXS_B3_UMDF_MD_LTWT_AS_EXPORTED

// Structure packing.

#define \
    ONIXS_B3_UMDF_MD_TO_STR(entity) \
    #entity

#if defined (_MSC_VER)

#define \
    ONIXS_B3_UMDF_MD_DATA_PACKING_BEGIN(alignment) \
        __pragma(pack(push, alignment))

#define \
    ONIXS_B3_UMDF_MD_DATA_PACKING_END \
    __pragma(pack(pop))

#elif defined (__GNUC__) && (__GNUC__ >= 3)

#define \
    ONIXS_B3_UMDF_MD_DATA_PACKING_BEGIN(alignment) \
    _Pragma(ONIXS_B3_UMDF_MD_TO_STR(pack(push, alignment)))

#define \
    ONIXS_B3_UMDF_MD_DATA_PACKING_END \
    _Pragma("pack(pop)")

#else

#error \
    Compiler toolset is not (yet) supported. \
    Please contact support@onixs.biz for further assistance.

#endif

#define \
    ONIXS_B3_UMDF_MD_TESTING_NAMESPACE_BEGIN \
    namespace OnixS { namespace B3 { namespace MarketData { namespace UMDF { namespace Testing {


#define \
    ONIXS_B3_UMDF_MD_TESTING_NAMESPACE_END \
    }}}}}

#define \
    ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_BEGIN \
    namespace OnixS { namespace B3 { namespace MarketData { namespace UMDF { namespace Messaging {


#define \
    ONIXS_B3_UMDF_MD_MESSAGING_NAMESPACE_END \
    }}}}}


#define \
    ONIXS_B3_UMDF_MD_NAMESPACE_BEGIN \
    namespace OnixS { namespace B3 { namespace MarketData { namespace UMDF {


#define \
    ONIXS_B3_UMDF_MD_NAMESPACE_END \
    }}}}

#define ONIXS_B3_UMDF_MD_MESSAGING OnixS::B3::MarketData::UMDF::Messaging
