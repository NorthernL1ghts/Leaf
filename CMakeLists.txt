cmake_minimum_required(VERSION 3.20)
project(LeafCompiler LANGUAGES C)

if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "This project requires GCC. Set CMAKE_C_COMPILER to gcc or use -DCMAKE_C_COMPILER=gcc.")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

set(LEAF_SOURCES
    src/main.c
)

add_executable(leaf ${LEAF_SOURCES})

target_include_directories(leaf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_options(leaf PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -Wpedantic>
)
