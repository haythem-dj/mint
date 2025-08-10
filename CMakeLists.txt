cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mint VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_SRCS
    src/core/engine.cpp
    src/core/logger.cpp
    src/graphics/renderer.cpp
    src/graphics/shader.cpp
    src/graphics/vbo.cpp
    src/graphics/ebo.cpp
    src/graphics/vao.cpp
    src/graphics/texture.cpp
    src/input/key_input.cpp
    src/input/mouse_input.cpp
    src/math/math.cpp
    src/math/vector.cpp
    src/platform/windows/windows_logger.cpp
    src/platform/windows/windows_window.cpp
    src/render_backend/opengl/gl_renderer.cpp
    src/render_backend/opengl/gl_shader.cpp
    src/render_backend/opengl/gl_vbo.cpp
    src/render_backend/opengl/gl_ebo.cpp
    src/render_backend/opengl/gl_vao.cpp
    src/render_backend/opengl/gl_texture.cpp
)

add_subdirectory(external/glad)
add_subdirectory(external/stb_image)

add_library(mint SHARED ${LIB_SRCS})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(mint PUBLIC opengl32)
endif()

target_include_directories(mint PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(mint PRIVATE glad)
target_link_libraries(mint PRIVATE stb_image)

target_compile_options(mint PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

target_compile_definitions(mint PRIVATE
    MINT_EXPORT
)

if (MINT_BUILD_TEST)
    add_subdirectory(test)
endif()
