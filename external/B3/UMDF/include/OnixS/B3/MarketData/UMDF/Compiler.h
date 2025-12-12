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

#if !(defined(ONIXS_B3_UMDF_MD_DOXYGEN) && ONIXS_B3_UMDF_MD_DOXYGEN)

#include <OnixS/B3/MarketData/UMDF/CompilerDetection.h>


#if defined(_MSC_VER) && defined(_MSVC_LANG)
#  define ONIXS_B3_UMDF_MD_CURRENT_CXX_STD _MSVC_LANG
#else
#  define ONIXS_B3_UMDF_MD_CURRENT_CXX_STD __cplusplus
#endif

# if defined(ONIXS_B3_UMDF_MD_CXX11)
#  if (ONIXS_B3_UMDF_MD_CURRENT_CXX_STD < 201103L)
#   error C++11 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_B3_UMDF_MD_CXX14)
#  if (ONIXS_B3_UMDF_MD_CURRENT_CXX_STD < 201402L)
#   error C++14 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_B3_UMDF_MD_CXX17)
#  if (ONIXS_B3_UMDF_MD_CURRENT_CXX_STD < 201703L)
#   error C++17 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_B3_UMDF_MD_CXX20)
#  if !(ONIXS_B3_UMDF_MD_CURRENT_CXX_STD > 201703L)
#   error C++20 was targeted during the OnixS SDK compilation but is not detected now
#   define ONIXS_TERMINATE_COMPILATION
#  endif
# endif

# if defined(ONIXS_TERMINATE_COMPILATION)
#  include <terminate_compilation>
#endif

#undef ONIXS_B3_UMDF_MD_CURRENT_CXX_STD

# if defined(ONIXS_B3_UMDF_MD_CXX14)
#  define ONIXS_B3_UMDF_MD_CXX14_CONSTEXPR constexpr
#else
#  define ONIXS_B3_UMDF_MD_CXX14_CONSTEXPR
# endif

# if defined(ONIXS_B3_UMDF_MD_COMPILER_IS_GNU) | defined(ONIXS_B3_UMDF_MD_COMPILER_IS_Clang)
#  define ONIXS_B3_UMDF_MD_COMPILER_IS_GNU_or_Clang
# endif

# if defined(ONIXS_B3_UMDF_MD_COMPILER_IS_GNU)
# if __GNUC__ >= 9 && defined ONIXS_B3_UMDF_MD_CXX14
#   define ONIXS_B3_UMDF_MD_LIKELY(cond)   (__builtin_expect_with_probability((static_cast<bool>((cond))), true, 0.99999f))
#   define ONIXS_B3_UMDF_MD_UNLIKELY(cond) (__builtin_expect_with_probability((static_cast<bool>((cond))), false, 0.99999f))
# else
#   define ONIXS_B3_UMDF_MD_LIKELY(cond)   (__builtin_expect((static_cast<bool>((cond))), true))
#   define ONIXS_B3_UMDF_MD_UNLIKELY(cond) (__builtin_expect((static_cast<bool>((cond))), false))
# endif
# endif

# if defined(ONIXS_B3_UMDF_MD_COMPILER_IS_Clang)
#  define ONIXS_B3_UMDF_MD_LIKELY(cond) (__builtin_expect((static_cast<bool>((cond))), true))
#  define ONIXS_B3_UMDF_MD_UNLIKELY(cond) (__builtin_expect((static_cast<bool>((cond))), false))
#endif

# if defined(ONIXS_B3_UMDF_MD_COMPILER_IS_GNU_or_Clang)
#  define ONIXS_B3_UMDF_MD_UNUSED __attribute__((__unused__))
#  define ONIXS_B3_UMDF_MD_MAY_ALIAS __attribute__((__may_alias__))
#  define ONIXS_B3_UMDF_MD_HOTPATH __attribute__((hot))
#  define ONIXS_B3_UMDF_MD_COLDPATH __attribute__((noinline,cold))
#  define ONIXS_B3_UMDF_MD_NORETURN __attribute__ ((__noreturn__))
#  define ONIXS_B3_UMDF_MD_NODISCARD __attribute__((warn_unused_result))
#  define ONIXS_B3_UMDF_MD_PURE

#elif defined(ONIXS_B3_UMDF_MD_COMPILER_IS_MSVC)

#  define ONIXS_B3_UMDF_MD_LIKELY(cond) ((cond))
#  define ONIXS_B3_UMDF_MD_UNLIKELY(cond) ((cond))
#  define ONIXS_B3_UMDF_MD_PURE
#  define ONIXS_B3_UMDF_MD_UNUSED
#  define ONIXS_B3_UMDF_MD_MAY_ALIAS
#  define ONIXS_B3_UMDF_MD_HOTPATH
#  define ONIXS_B3_UMDF_MD_COLDPATH
#  define ONIXS_B3_UMDF_MD_NORETURN __declspec(noreturn)
#  define ONIXS_B3_UMDF_MD_NODISCARD _Check_return_

#else
#  error Unsupported compiler
#endif

# if defined(ONIXS_B3_UMDF_MD_COMPILER_IS_GNU) & !defined(ONIXS_B3_UMDF_MD_CXX11)
#  define ONIXS_B3_UMDF_MD_GCC44_SPURIOUS_WARNING_TURNAROUND ONIXS_B3_UMDF_MD_MAY_ALIAS
# else
#  define ONIXS_B3_UMDF_MD_GCC44_SPURIOUS_WARNING_TURNAROUND
# endif


#if defined(ONIXS_B3_UMDF_MD_CXX11)

# define ONIXS_B3_UMDF_MD_NOTHROW noexcept
# define ONIXS_B3_UMDF_MD_CHECK_NOTHROW(equation) ONIXS_B3_UMDF_MD_STATIC_ASSERT(noexcept((equation)))
# define ONIXS_B3_UMDF_MD_EXPLICIT explicit
# define ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR constexpr
# define ONIXS_B3_UMDF_MD_FINAL final
# define ONIXS_B3_UMDF_MD_OVERRIDE override
# define ONIXS_B3_UMDF_MD_CONSTEXPR constexpr
# define ONIXS_B3_UMDF_MD_NULLPTR nullptr
# define ONIXS_B3_UMDF_MD_DELETED_FUNCTION = delete
# define ONIXS_B3_UMDF_MD_STATIC_ASSERT(X) static_assert(X, #X)
# define ONIXS_B3_UMDF_MD_STATIC_ASSERT_MSG(X, MSG) static_assert(X, MSG)
# define ONIXS_B3_UMDF_MD_ALIGNAS(X) alignas(X)
# define ONIXS_B3_UMDF_MD_DEFAULT =default

#else

# define ONIXS_B3_UMDF_MD_NOTHROW throw()
# define ONIXS_B3_UMDF_MD_CHECK_NOTHROW(equation) ONIXS_B3_UMDF_MD_STATIC_ASSERT((true))
# define ONIXS_B3_UMDF_MD_EXPLICIT
# define ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR const
# define ONIXS_B3_UMDF_MD_FINAL
# define ONIXS_B3_UMDF_MD_OVERRIDE
# define ONIXS_B3_UMDF_MD_CONSTEXPR
# define ONIXS_B3_UMDF_MD_DELETED_FUNCTION
# define ONIXS_B3_UMDF_MD_DEFAULT {}


# if defined ONIXS_B3_UMDF_MD_COMPILER_IS_GNU_or_Clang
#  define ONIXS_B3_UMDF_MD_NULLPTR __null
# else
#  define ONIXS_B3_UMDF_MD_NULLPTR 0
# endif


# define ONIXS_B3_UMDF_MD_STATIC_ASSERT_JOIN(X, Y) ONIXS_B3_UMDF_MD_STATIC_ASSERT_JOIN_IMPL(X, Y)
# define ONIXS_B3_UMDF_MD_STATIC_ASSERT_JOIN_IMPL(X, Y) X##Y
template<bool> struct ONIXS_ILINK3StaticAssert;
template<> struct ONIXS_ILINK3StaticAssert<true>{};
# define ONIXS_B3_UMDF_MD_STATIC_ASSERT(X) enum { ONIXS_B3_UMDF_MD_STATIC_ASSERT_JOIN(ONIXS_ILINK3StaticAssertEnum, __LINE__) = sizeof(ONIXS_ILINK3StaticAssert<X>) }
# define ONIXS_B3_UMDF_MD_STATIC_ASSERT_MSG(X, MSG) enum { ONIXS_B3_UMDF_MD_STATIC_ASSERT_JOIN(ONIXS_ILINK3StaticAssertEnum, __LINE__) = sizeof(ONIXS_ILINK3StaticAssert<X>) }


# if defined ONIXS_B3_UMDF_MD_COMPILER_IS_GNU_or_Clang
#  define ONIXS_B3_UMDF_MD_ALIGNAS(X) __attribute__ ((__aligned__(X)))
# elif defined ONIXS_B3_UMDF_MD_COMPILER_IS_MSVC
#  define ONIXS_B3_UMDF_MD_ALIGNAS(X) __declspec(align(X))
# else
#  define ONIXS_B3_UMDF_MD_ALIGNAS(X)
# endif

#endif

#if defined NDEBUG
# define ONIXS_B3_UMDF_MD_ASSERT(CHECK) static_cast<void>((CHECK))
#else
#if defined (ONIXS_B3_UMDF_MD_CXX11)
#       define ONIXS_B3_UMDF_MD_ASSERT(CHECK) ((CHECK) ? void(0) : []() {assert(!#CHECK);}())
#   else
#       define ONIXS_B3_UMDF_MD_ASSERT(CHECK) (assert((CHECK)))
#   endif
#endif

#if defined (ONIXS_B3_UMDF_MD_CXX11)
#   define ONIXS_B3_UMDF_MD_HAS_TYPE_TRAITS
#endif

#define ONIXS_B3_UMDF_MD_HARDWARE_DESTRUCTIVE_INTERFACE_SIZE (64)

#else //#if !(defined(ONIXS_DOXYGEN) && ONIXS_DOXYGEN)

#define ONIXS_B3_UMDF_MD_EXPORTED
#define ONIXS_B3_UMDF_MD_NOTHROW noexcept
#define ONIXS_B3_UMDF_MD_EXPLICIT explicit
#define ONIXS_B3_UMDF_MD_CONST_OR_CONSTEXPR constexpr
#define ONIXS_B3_UMDF_MD_CONSTEXPR constexpr
#define ONIXS_B3_UMDF_MD_OVERRIDE override
#define ONIXS_B3_UMDF_MD_FINAL final
#define ONIXS_B3_UMDF_MD_NULLPTR nullptr

#define ONIXS_B3_UMDF_MD_NORETURN
#define ONIXS_B3_UMDF_MD_NODISCARD

#define ONIXS_B3_UMDF_MD_HOTPATH
#define ONIXS_B3_UMDF_MD_COLDPATH
#define ONIXS_B3_UMDF_MD_PURE

#define ONIXS_B3_UMDF_MD_HAS_TYPE_TRAITS

#define ONIXS_B3_UMDF_MD_HAS_GATEWAY_EMULATOR

#define ONIXS_B3_UMDF_MD_CXX11
#define ONIXS_B3_UMDF_MD_CXX14
#define ONIXS_B3_UMDF_MD_CXX17
#define ONIXS_B3_UMDF_MD_CXX20


#define ONIXS_B3_UMDF_MD_UNUSED
#define ONIXS_B3_UMDF_MD_DEFAULT =default

#define ONIXS_B3_UMDF_MD_GCC44_SPURIOUS_WARNING_TURNAROUND

#endif
