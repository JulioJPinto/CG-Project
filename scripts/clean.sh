#!/bin/bash
rm -rf CMakeFiles
rm -f CMakeCache.txt
rm -f Makefile
rm -rf cmake-build-debug 
rm -rf build
rm -rf cmake_install.cmake 

# Remove CMakeLists.txt.user if exists
rm -f CMakeLists.txt.user

rm -rf */CMakeFiles
rm -f */CMakeCache.txt
rm -f */Makefile
rm -rf */cmake-build-debug
rm -rf */cmake_install.cmake 
rm -rf */build

rm -rf */engine
rm -rf */generator
rm -rf */common



echo "Cleanup complete."
