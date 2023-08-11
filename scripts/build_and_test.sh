#!/usr/bin/env bash

set -x

rm -f cmake/SourceLists.cmake
cp cmake/SourceLists{.official,}.cmake

mkdir -p build/

cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .

mkdir -p tests/fixtures

cp ../tests/fixtures/* tests/fixtures

./tests/tests "$@"