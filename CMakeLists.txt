cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mint VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(configurations
    debug
    release
)

set(CMAKE_CONFIGURATION_TYPES "${configurations}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif()

file(GLOB LIB_FILES "src/**/*.cpp")

add_library(mint SHARED ${LIB_FILES})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(mint PUBLIC MINT_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(mint PUBLIC MINT_PLATFORM_WINDOWS)
endif()

target_include_directories(mint PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_compile_options(mint PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

target_compile_definitions(mint PRIVATE
    $<$<CONFIG:Debug>:MINT_BUILD_DEBUG>
    $<$<CONFIG:Release>:MINT_BUILD_RELEASE>
    MINT_EXPORT
)

if (MINT_BUILD_TEST)
    add_subdirectory(test)
endif()
