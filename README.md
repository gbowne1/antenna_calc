# AntennaCalc

A C++ console application for calculating antenna lengths for HF/shortwave antennas (1.6-30 MHz).

## Features
- Supports Dipole, Yagi-Uda, Loop, Vertical, Inverted V, Folded Dipole.
- Balanced/Unbalanced, 50Ω, half/quarter wave, baluns.
- Shortwave and Amateur HF bands.
- Login/register, menus, config/logs, help.
- ANSI UI with colors, boxes, arrow/WASD navigation.

## Build
- CMake: `cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build`
- Makefile: `make release`
- `./build.sh release`
- Meson: `meson setup build && meson compile -C build`

## Usage
`./build/antennacalc --help`

MIT License.
