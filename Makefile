CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -pedantic-errors -Iinclude
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O3

SRCS = src/main.cpp src/utils.cpp
OBJS = $(SRCS:.cpp=.o)

all: release

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: build_dir antennacalc

release: CXXFLAGS += $(RELEASE_FLAGS)
release: build_dir antennacalc

build_dir:
	mkdir -p build

antennacalc: $(OBJS)
	$(CXX) $(CXXFLAGS) -o build/antennacalc $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build *.o src/*.o
