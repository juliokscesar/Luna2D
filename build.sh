#!/usr/bin/env bash
if [[ ! -d ./build ]]; then
    mkdir build
fi

cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.
make && make install
