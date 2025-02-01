# Makefile for antenna_calc project

# Compiler and flags
CXX = /usr/bin/g++
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic

# Directories
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/Debug
RELEASE_DIR = $(BUILD_DIR)/Release
SRC_DIR = src

# Source files
SRCS = $(SRC_DIR)/Antenna.cpp \
       $(SRC_DIR)/Band.cpp \
       $(SRC_DIR)/Frequency.cpp \
       $(SRC_DIR)/Spectrum.cpp \
       $(SRC_DIR)/Wavelength.cpp \
       main.cpp

# Output executable name
TARGET = antenna_calc

# Ensure the build directories exist
$(shell mkdir -p $(DEBUG_DIR) $(RELEASE_DIR))

# Default target (Debug build)
all: debug

# Debug build target
debug: CXXFLAGS += -g
debug: $(DEBUG_DIR)/$(TARGET)

# Release build target
release: CXXFLAGS += -O2
release: $(RELEASE_DIR)/$(TARGET)

# Linking rule for Debug build
$(DEBUG_DIR)/$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $@

# Linking rule for Release build
$(RELEASE_DIR)/$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) -o $@

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Testing rule (optional, can be customized for your testing framework)
test:
	# Place your testing commands here, e.g. running gtest or any test framework
	@echo "Testing not configured. Add test commands here."

.PHONY: all debug release clean test
