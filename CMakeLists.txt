cmake_minimum_required(VERSION 3.5)

# Project Name
project(visualizer)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the output directory for object files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} src/engine.cpp)
add_executable(generator src/generator.cpp)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(WIN32)
    message(STATUS "Toolkits_DIR set to: ${TOOLKITS_FOLDER}")
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")

    if(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(FATAL_ERROR "GLUT not found")
    endif(NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")

    include_directories(${TOOLKITS_FOLDER}/glut)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib)

    if(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
    endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
    if(NOT GLUT_FOUND)
        message(FATAL_ERROR "GLUT not found!")
    endif(NOT GLUT_FOUND)
endif()

# Adding clang-format target
find_program(CLANG_FORMAT_EXECUTABLE NAMES "clang-format")
if(NOT CLANG_FORMAT_EXECUTABLE)
    message(WARNING "clang-format not found. Formatting will not be available.")
else()
    file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp include/*.hpp)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=Google -i ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format"
    )
endif()
