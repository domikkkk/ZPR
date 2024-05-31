#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

cmake ..
cmake --build .

mv files_compare ..
mv tests ..

exit 0
