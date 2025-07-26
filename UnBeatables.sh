#!/bin/bash
# shellcheck disable=SC2164
cd "$(dirname "$0")"

mkdir -p build
# shellcheck disable=SC2164
cd build
cmake ..
make
./exe