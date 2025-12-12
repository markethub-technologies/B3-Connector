
#ifndef ONIXS_B3_BOE_EXPORTED_H
#define ONIXS_B3_BOE_EXPORTED_H

#ifdef ONIXS_B3_BOE_AS_STATIC_LIB
#  define ONIXS_B3_BOE_EXPORTED
#  define ONIXS_B3_BOE_INTERNAL
#else
#  ifndef ONIXS_B3_BOE_EXPORTED
#    ifdef b3_boe_EXPORTS
        /* We are building this library */
#      define ONIXS_B3_BOE_EXPORTED __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define ONIXS_B3_BOE_EXPORTED __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef ONIXS_B3_BOE_INTERNAL
#    define ONIXS_B3_BOE_INTERNAL __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef ONIXS_B3_BOE_DEPRECATED
#  define ONIXS_B3_BOE_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef ONIXS_B3_BOE_DEPRECATED_EXPORT
#  define ONIXS_B3_BOE_DEPRECATED_EXPORT ONIXS_B3_BOE_EXPORTED ONIXS_B3_BOE_DEPRECATED
#endif

#ifndef ONIXS_B3_BOE_DEPRECATED_NO_EXPORT
#  define ONIXS_B3_BOE_DEPRECATED_NO_EXPORT ONIXS_B3_BOE_INTERNAL ONIXS_B3_BOE_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ONIXS_B3_BOE_NO_DEPRECATED
#    define ONIXS_B3_BOE_NO_DEPRECATED
#  endif
#endif

#endif /* ONIXS_B3_BOE_EXPORTED_H */
