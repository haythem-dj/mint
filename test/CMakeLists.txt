project(mint_test VERSION 1.0 LANGUAGES CXX)

add_executable(mint_test main.cpp)
target_link_libraries(mint_test PRIVATE mint)

target_compile_options(mint PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
target_compile_definitions(mint_test PRIVATE
    $<$<CONFIG:debug>:MINT_CONFIG_DEBUG>
    $<$<CONFIG:release>:MINT_CONFIG_RELEASE>
)

add_custom_command(TARGET mint_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:mint>"
        "$<TARGET_FILE_DIR:mint_test>"
    COMMENT "Copying the mint shared library to mint_test executable directory."
)
