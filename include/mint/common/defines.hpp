#pragma once

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef bool b8;

typedef float f32;
typedef double f64;

#ifdef MINT_PLATFORM_WINDOWS
    #ifdef MINT_EXPORT
        #define MINT_API __declspec(dllexport)
    #else
        #define MINT_API __declspec(dllimport)
    #endif
#endif

#ifdef MINT_PLATFORM_LINUX
    #ifdef MINT_EXPORT
        #define MINT_API __attribute_((visibility("default")))
    #else
        #define MINT_API
    #endif
#endif
