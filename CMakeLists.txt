cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mint VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(configurations
    debug
    release
)

set(CMAKE_CONFIGURATION_TYPES "${configurations}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif()

set(LIB_SRCS
    src/core/engine.cpp
    src/core/logger.cpp
    src/graphics/shader.cpp
    src/input/key_input.cpp
    src/input/mouse_input.cpp
    src/platform/windows/windows_logger.cpp
    src/platform/windows/windows_window.cpp
    src/render_backend/opengl/gl_shader.cpp
)

add_subdirectory(external/glad)

add_library(mint SHARED ${LIB_SRCS})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(mint PUBLIC MINT_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(mint PUBLIC MINT_PLATFORM_WINDOWS)
    target_link_libraries(mint PUBLIC opengl32)
endif()

target_include_directories(mint PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(mint PRIVATE glad)

target_compile_options(mint PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

target_compile_definitions(mint PRIVATE
    $<$<CONFIG:debug>:MINT_CONFIG_DEBUG>
    $<$<CONFIG:release>:MINT_CONFIG_RELEASE>
    MINT_EXPORT
)

if (MINT_BUILD_TEST)
    add_subdirectory(test)
endif()
