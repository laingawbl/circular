#!/usr/bin/env bash

# this does not do `make install`

set -x

./scripts/get_source_files.sh
test $? -eq 0 || { echo "could not get source files"; exit 1; }

mkdir -p build/ && cd build && cmake .. && make