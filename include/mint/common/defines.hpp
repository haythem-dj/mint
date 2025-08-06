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

#ifdef _MSC_VER
#define MINT_DEBUGBREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#define MINT_DEBUGBREAK() __builtin_trap()
#else
#warning "MINT_DEBUGBREAK is not defined for this compiler/platform."
#define MINT_DEBUGBREAK() ((void)0) // Placeholder for unsupported platforms
#endif
