#pragma once

#include <stdlib.h>

// Cross platform inlining compiler directive
#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCE_INLINE static inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

double *ppg_util_generate_random_data(size_t size);