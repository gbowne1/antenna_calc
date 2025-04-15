cmake_minimum_required(VERSION 3.10)

project(antenna_calc VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the executable
add_executable(antenna_calc
    main.cpp
    src/Antenna.cpp
    src/Band.cpp
    src/Spectrum.cpp
    src/Frequency.cpp
    src/Wavelength.cpp
    src/Utility.cpp
)

# Target properties
target_include_directories(antenna_calc PRIVATE include)

# Install target (optional)
install(TARGETS antenna_calc DESTINATION bin)
