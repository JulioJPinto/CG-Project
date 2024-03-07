#!/bin/bash
build_dir=build

cmake -S . -B $build_dir

cd engine
make
cd ..
cd generator
make
cd ..