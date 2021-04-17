#!/bin/bash

echo "CREATE linux directory"

rm -rf build_linux
mkdir build_linux
cd build_linux

cmake -D CMAKE_C_FLAGS=-m64 \
       ../

cmake --build . -- -j12

cd ../
