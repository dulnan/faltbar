#!/bin/sh

rm -rf build
meson build
cd build
ninja
# ninja install
./app/faltbar http://localhost:8080
