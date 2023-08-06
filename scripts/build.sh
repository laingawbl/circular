#!/usr/bin/env bash

# this does not do `make install`

set -x

[ ./get_source_files.sh ] || { echo "could not get source files"; exit 1; }

mkdir -p build/ && cd build && cmake .. && make