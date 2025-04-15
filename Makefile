# Compiler
CXX = g++

# Project directories
INCLUDE_DIR = include
SRC_DIR = src

# Flags
CXXFLAGS = -std=c++17 -Wall -I$(INCLUDE_DIR)
LDFLAGS = 

# Sources & Objects
SOURCES = main.cpp $(SRC_DIR)/Antenna.cpp $(SRC_DIR)/Band.cpp \
          $(SRC_DIR)/Spectrum.cpp $(SRC_DIR)/Frequency.cpp $(SRC_DIR)/Wavelength.cpp \
          $(SRC_DIR)/Utility.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Target
TARGET = antenna_calc

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJECTS) $(TARGET)
