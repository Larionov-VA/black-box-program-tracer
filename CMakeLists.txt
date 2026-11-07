cmake_minimum_required(VERSION 3.20)

project(bbtracer VERSION 0.1.0 LANGUAGES CXX)

add_library(bbtrace_core INTERFACE)

target_include_directories(bbtrace_core
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(bbtrace_core
    INTERFACE
        cxx_std_20
)

target_compile_options(bbtrace_core
    INTERFACE
        -Wall
        -Wextra
        -Werror
        -pedantic
)

add_executable(bbtrace
    src/black_box_tracer.cpp
)

target_link_libraries(bbtrace
    PRIVATE
        bbtrace_core
)

find_package(GTest REQUIRED)
enable_testing()
include(GoogleTest)

add_executable(bbtrace_tests
    tests/bbtrace_tests.cpp
)

target_link_libraries(bbtrace_tests
    PRIVATE
        bbtrace_core
        GTest::gtest_main
)

gtest_discover_tests(bbtrace_tests)
