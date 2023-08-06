#!/usr/bin/env bash

set -x

rm -f cmake/SourceLists.cmake
cp cmake/SourceLists{.official,}.cmake

mkdir -p build/ && cd build && cmake .. && cmake --build . && ./tests/tests