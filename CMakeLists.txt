cmake_minimum_required(VERSION 3.13)
project(antenna_calc
    VERSION 1.0
    HOMEPAGE_URL
    DESCRIPTION
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_EXE_LINKER_FLAGS "-fuse-ld=ld")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -pedantic")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(antenna_calc
    src/Antenna.cpp
    src/Band.cpp
    src/Frequency.cpp
    src/Spectrum.cpp
    src/Wavelength.cpp
    main.cpp)

enable_testing()
include(CTest)
