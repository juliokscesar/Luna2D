#!/usr/bin/env bash

# build GLFW
cd Luna/ext/glfw
mkdir -p build
cd build
cmake ..
cmake --build . --config Release -j 4

cd ../../../..

# build project
mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=.
make && make install
