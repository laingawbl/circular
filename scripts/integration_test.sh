#!/usr/bin/env bash

EXECUTABLE=$1

OUTPUT=$($EXECUTABLE foo bar)

if [ "$OUTPUT" = "baz" ]
then
    exit 0
else
    exit 1
fi
