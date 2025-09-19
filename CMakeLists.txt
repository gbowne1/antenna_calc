cmake_minimum_required(VERSION 3.10)
project(antennacalc VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})

add_definitions(-D_XOPEN_SOURCE=800 -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE)
if(WIN32)
  add_definitions(-D_WIN32 -D_WIN64 -D_CRT_SECURE_NO_WARNINGS)
endif()
add_definitions(-DPI=3.141592653589793)

include_directories(include)

add_executable(antennacalc src/main.cpp src/utils.cpp)

# Optional glog
find_package(glog QUIET)
if(glog_FOUND)
  target_link_libraries(antennacalc glog::glog)
  add_definitions(-DHAS_GLOG)
endif()

# Tests
enable_testing()
find_package(GTest QUIET)
if(GTest_FOUND)
  add_executable(antennacalc_tests tests/main_test.cpp src/utils.cpp)
  target_link_libraries(antennacalc_tests GTest::GTest GTest::Main)
  add_test(NAME antennacalc_tests COMMAND antennacalc_tests)
endif()

# Flags
target_compile_options(antennacalc PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -std=c++17)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(antennacalc PRIVATE -g -O0)
else()
  target_compile_options(antennacalc PRIVATE -O3)
endif()

install(TARGETS antennacalc DESTINATION bin)
