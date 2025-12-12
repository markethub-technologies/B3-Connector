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

#if !(defined(ONIXS_B3_BOE_DOXYGEN) && ONIXS_B3_BOE_DOXYGEN)

#include <OnixS/B3/BOE/CompilerDetection.h>

#if defined(ONIXS_B3_BOE_COMPILER_IS_Clang)
#define ONIXS_B3_BOE_PADDING(size) __attribute__((__unused__)) char padding[size]
#else
#define ONIXS_B3_BOE_PADDING(size) char padding[size]
#endif

#if defined(_MSC_VER) && defined(_MSVC_LANG)
#  define ONIXS_CURRENT_CXX_STD _MSVC_LANG
#else
#  define ONIXS_CURRENT_CXX_STD __cplusplus
#endif

# if defined(ONIXS_B3_BOE_CXX11)
#  if (ONIXS_CURRENT_CXX_STD < 201103L)
#   error C++11 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_B3_BOE_CXX14)
#  if (ONIXS_CURRENT_CXX_STD < 201402L)
#   error C++14 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_B3_BOE_CXX17)
#  if (ONIXS_CURRENT_CXX_STD < 201703L)
#   error C++17 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_B3_BOE_CXX20)
#  if !(ONIXS_CURRENT_CXX_STD > 201703L)
#   error C++20 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_TERMINATE_COMPILATION)
#  include <termnate_compilation>
#endif

# if defined(ONIXS_B3_BOE_COMPILER_IS_GNU) | defined(ONIXS_B3_BOE_COMPILER_IS_Clang)
#  define ONIXS_B3_BOE_COMPILER_IS_GNU_or_Clang
# endif

# if defined(ONIXS_B3_BOE_COMPILER_IS_GNU_or_Clang)

#  define ONIXS_B3_BOE_LIKELY(cond) (__builtin_expect((static_cast<bool>((cond))), true))
#  define ONIXS_B3_BOE_UNLIKELY(cond) (__builtin_expect((static_cast<bool>((cond))), false))
#  define ONIXS_B3_BOE_UNUSED __attribute__((__unused__))
#  define ONIXS_B3_BOE_MAY_ALIAS __attribute__((__may_alias__))
#  define ONIXS_B3_BOE_HOTPATH __attribute__((hot))
#  define ONIXS_B3_BOE_COLDPATH __attribute__((noinline,cold))
#  define ONIXS_B3_BOE_NORETURN __attribute__ ((__noreturn__))
#  define ONIXS_B3_BOE_NODISCARD __attribute__((warn_unused_result))
#  define ONIXS_B3_BOE_PURE

#elif defined(ONIXS_B3_BOE_COMPILER_IS_MSVC)

#  define ONIXS_B3_BOE_LIKELY(cond) ((cond))
#  define ONIXS_B3_BOE_UNLIKELY(cond) ((cond))
#  define ONIXS_B3_BOE_PURE
#  define ONIXS_B3_BOE_UNUSED
#  define ONIXS_B3_BOE_MAY_ALIAS
#  define ONIXS_B3_BOE_HOTPATH
#  define ONIXS_B3_BOE_COLDPATH
#  define ONIXS_B3_BOE_NORETURN __declspec(noreturn)
#  define ONIXS_B3_BOE_NODISCARD _Check_return_

#else
#  error Unsupported compiler
#endif

# if defined(ONIXS_B3_BOE_COMPILER_IS_GNU) & !defined(ONIXS_B3_BOE_CXX11)
#  define ONIXS_B3_BOE_GCC44_SPURIOUS_WARNING_TURNAROUND ONIXS_B3_BOE_MAY_ALIAS
# else
#  define ONIXS_B3_BOE_GCC44_SPURIOUS_WARNING_TURNAROUND
# endif


#if defined(ONIXS_B3_BOE_CXX11)

# define ONIXS_B3_BOE_NOTHROW noexcept
# define ONIXS_B3_BOE_CHECK_NOTHROW(equation) ONIXS_B3_BOE_STATIC_ASSERT(noexcept((equation)))
# define ONIXS_B3_BOE_EXPLICIT explicit
# define ONIXS_B3_BOE_CONST_OR_CONSTEXPR constexpr
# define ONIXS_B3_BOE_FINAL final
# define ONIXS_B3_BOE_OVERRIDE override
# define ONIXS_B3_BOE_CONSTEXPR constexpr
# define ONIXS_B3_BOE_NULLPTR nullptr
# define ONIXS_B3_BOE_DELETED_FUNCTION = delete
# define ONIXS_B3_BOE_STATIC_ASSERT(X) static_assert(X, #X)
# define ONIXS_B3_BOE_STATIC_ASSERT_MSG(X, MSG) static_assert(X, MSG)
# define ONIXS_B3_BOE_ALIGNAS(X) alignas(X)
# define ONIXS_B3_BOE_DEFAULT =default

#else

# define ONIXS_B3_BOE_NOTHROW throw()
# define ONIXS_B3_BOE_CHECK_NOTHROW(equation) ONIXS_B3_BOE_STATIC_ASSERT((true))
# define ONIXS_B3_BOE_EXPLICIT
# define ONIXS_B3_BOE_CONST_OR_CONSTEXPR const
# define ONIXS_B3_BOE_FINAL
# define ONIXS_B3_BOE_OVERRIDE
# define ONIXS_B3_BOE_CONSTEXPR
# define ONIXS_B3_BOE_DELETED_FUNCTION
# define ONIXS_B3_BOE_DEFAULT {}


# if defined ONIXS_B3_BOE_COMPILER_IS_GNU_or_Clang
#  define ONIXS_B3_BOE_NULLPTR __null
# else
#  define ONIXS_B3_BOE_NULLPTR 0
# endif


# define ONIXS_B3_BOE_STATIC_ASSERT_JOIN(X, Y) ONIXS_B3_BOE_STATIC_ASSERT_JOIN_IMPL(X, Y)
# define ONIXS_B3_BOE_STATIC_ASSERT_JOIN_IMPL(X, Y) X##Y
template<bool> struct ONIXS_B3_BOEStaticAssert;
template<> struct ONIXS_B3_BOEStaticAssert<true>{};
# define ONIXS_B3_BOE_STATIC_ASSERT(X) enum { ONIXS_B3_BOE_STATIC_ASSERT_JOIN(ONIXS_B3_BOEStaticAssertEnum, __LINE__) = sizeof(ONIXS_B3_BOEStaticAssert<X>) }
# define ONIXS_B3_BOE_STATIC_ASSERT_MSG(X, MSG) enum { ONIXS_B3_BOE_STATIC_ASSERT_JOIN(ONIXS_B3_BOEStaticAssertEnum, __LINE__) = sizeof(ONIXS_B3_BOEStaticAssert<X>) }


# if defined ONIXS_B3_BOE_COMPILER_IS_GNU_or_Clang
#  define ONIXS_B3_BOE_ALIGNAS(X) __attribute__ ((__aligned__(X)))
# elif defined ONIXS_B3_BOE_COMPILER_IS_MSVC
#  define ONIXS_B3_BOE_ALIGNAS(X) __declspec(align(X))
# else
#  define ONIXS_B3_BOE_ALIGNAS(X)
# endif

#endif

#if defined NDEBUG
# define ONIXS_B3_BOE_ASSERT(CHECK) static_cast<void>((CHECK))
#else
#if defined (ONIXS_B3_BOE_CXX11)
#       define ONIXS_B3_BOE_ASSERT(CHECK) ((CHECK) ? void(0) : []() {assert(!#CHECK);}())
#   else
#       define ONIXS_B3_BOE_ASSERT(CHECK) (assert((CHECK)))
#   endif
#endif

#if defined (ONIXS_B3_BOE_CXX11)
#   define ONIXS_B3_BOE_HAS_TYPE_TRAITS
#endif

#define ONIXS_B3_BOE_HARDWARE_DESTRUCTIVE_INTERFACE_SIZE (64)

#else //#if !(defined(ONIXS_DOXYGEN) && ONIXS_DOXYGEN)

#define ONIXS_B3_BOE_EXPORTED
#define ONIXS_B3_BOE_NOTHROW noexcept
#define ONIXS_B3_BOE_EXPLICIT explicit
#define ONIXS_B3_BOE_CONST_OR_CONSTEXPR constexpr
#define ONIXS_B3_BOE_CONSTEXPR constexpr
#define ONIXS_B3_BOE_OVERRIDE override
#define ONIXS_B3_BOE_FINAL final
#define ONIXS_B3_BOE_NULLPTR nullptr

#define ONIXS_B3_BOE_NORETURN
#define ONIXS_B3_BOE_NODISCARD

#define ONIXS_B3_BOE_HOTPATH
#define ONIXS_B3_BOE_COLDPATH
#define ONIXS_B3_BOE_PURE

#define ONIXS_B3_BOE_HAS_TYPE_TRAITS

#define ONIXS_B3_BOE_HAS_GATEWAY_EMULATOR

#define ONIXS_B3_BOE_CXX11
#define ONIXS_B3_BOE_CXX14
#define ONIXS_B3_BOE_CXX17
#define ONIXS_B3_BOE_CXX20


#define ONIXS_B3_BOE_UNUSED
#define ONIXS_B3_BOE_DEFAULT =default

#define ONIXS_B3_BOE_GCC44_SPURIOUS_WARNING_TURNAROUND

#endif
