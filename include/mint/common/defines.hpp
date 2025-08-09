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

typedef size_t size;

typedef bool b8;

typedef float f32;
typedef double f64;

#if defined(_WIN32) || defined(_WIN64)
    #define MINT_PLATFORM_WINDOWS
#else
    #error "Unknown or unsupported operating system" 
#endif

#ifdef MINT_PLATFORM_WINDOWS
    #ifdef MINT_EXPORT
        #define MINT_API __declspec(dllexport)
    #else
        #define MINT_API __declspec(dllimport)
    #endif
#endif

#ifdef _MSC_VER
    #define MINT_DEBUGBREAK() __debugbreak()
    #ifdef _DEBUG
        #define MINT_CONFIG_DEBUG
    #else
        #define MINT_CONFIG_RELEASE
    #endif
#elif defined(__clang__) || defined(__GNUC__)
    #define MINT_DEBUGBREAK() __builtin_trap()
    #ifdef NDEBUG
        #define MINT_CONFIG_RELEASE
    #else
        #define MINT_CONFIG_DEBUG
    #endif
#else
    #warning "MINT_DEBUGBREAK is not defined for this compiler/platform."
    #define MINT_DEBUGBREAK() ((void)0)
#endif
