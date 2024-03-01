cmake_minimum_required(VERSION 3.5)

# Project Name
project(generator)

# Include directories
include_directories(${PROJECT_NAME} PUBLIC include)  # Assuming headers are in the 'include' directory

file(GLOB SRC_FILES src/shapes/*.cpp src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})


