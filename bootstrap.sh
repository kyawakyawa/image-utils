#!/bin/bash

rm -rf build

CC=clang CXX=clang++ cmake -H. -Bbuild \
                           -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
                           -DCMAKE_BUILD_TYPE=Debug \
                           -DIMAGE_UTILS_USE_EXTERNAL_GHC_FILESYSTEM=OFF \
                           -DIMAGE_UTILS_BUILD_EXAMPLES=ON \

mv build/compile_commands.json .
