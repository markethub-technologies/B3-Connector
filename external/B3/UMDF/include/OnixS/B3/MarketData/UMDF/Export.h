
#ifndef ONIXS_B3_UMDF_MD_API_H
#define ONIXS_B3_UMDF_MD_API_H

#ifdef ONIXS_B3_UMDF_MD_AS_STATIC_LIB
#  define ONIXS_B3_UMDF_MD_API
#  define ONIXS_B3UMDFH_NO_EXPORT
#else
#  ifndef ONIXS_B3_UMDF_MD_API
#    ifdef b3umdfh_EXPORTS
        /* We are building this library */
#      define ONIXS_B3_UMDF_MD_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ONIXS_B3_UMDF_MD_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ONIXS_B3UMDFH_NO_EXPORT
#    define ONIXS_B3UMDFH_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ONIXS_B3UMDFH_DEPRECATED
#  define ONIXS_B3UMDFH_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ONIXS_B3UMDFH_DEPRECATED_EXPORT
#  define ONIXS_B3UMDFH_DEPRECATED_EXPORT ONIXS_B3_UMDF_MD_API ONIXS_B3UMDFH_DEPRECATED
#endif

#ifndef ONIXS_B3UMDFH_DEPRECATED_NO_EXPORT
#  define ONIXS_B3UMDFH_DEPRECATED_NO_EXPORT ONIXS_B3UMDFH_NO_EXPORT ONIXS_B3UMDFH_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONIXS_B3UMDFH_NO_DEPRECATED
#    define ONIXS_B3UMDFH_NO_DEPRECATED
#  endif
#endif

#endif /* ONIXS_B3_UMDF_MD_API_H */
