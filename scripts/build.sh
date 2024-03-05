#!/bin/bash

# Navigate to the engine directory
cd engine || exit 1

# Run CMake for the engine
cmake CMakeLists.txt || exit 1

# Build the engine
make || exit 1

# Return to the parent directory
cd ..

# Navigate to the generator directory
cd generator || exit 1

# Run CMake for the generator
cmake CMakeLists.txt || exit 1

# Build the generator
make || exit 1

# Return to the parent directory
cd ..

