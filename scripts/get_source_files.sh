#!/usr/bin/env bash

set -x

[ -e cmake/ ] || { echo "where is cmake/?"; exit 127; }
[ -e src/ ] || { echo "where is src/?"; exit 127; }

touch cmake/SourceLists.cmake
touch cmake/SourceLists.txt

find src/ -type f -name *.cpp -o -name *.hpp -o -name *.inl |
    awk '{print "$${PROJECT_SOURCE_DIR}/"$1}' > cmake/SourceLists.txt

rg --replace "$(cat cmake/SourceLists.txt)" --passthru --no-line-number \
--multiline --multiline-dotall '__the_sources__' \
cmake/SourceLists.cmake.template | tee > cmake/SourceLists.cmake