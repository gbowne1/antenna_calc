#!/bin/bash

BUILD_TYPE=${1:-release}

if command -v cmake &> /dev/null; then
  mkdir -p build
  cd build
  cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE^}
  cmake --build .
else
  if [ "$BUILD_TYPE" = "debug" ]; then
    make debug
  else
    make release
  fi
fi
