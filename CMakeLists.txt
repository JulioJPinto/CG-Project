cmake_minimum_required(VERSION 3.20)
project(Cg VERSION 1.0 LANGUAGES CXX)

# Options
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Set debug-specific flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-g")
endif()

# Dependencies
include(FetchContent)

# - Fmt
FetchContent_Declare(fmt GIT_REPOSITORY "https://github.com/fmtlib/fmt")
FetchContent_MakeAvailable(fmt)

# - FreeGLUT
FetchContent_Declare(freeglut GIT_REPOSITORY "https://github.com/freeglut/freeglut")
FetchContent_MakeAvailable(freeglut)

# - Glew
FetchContent_Declare(glew GIT_REPOSITORY "https://github.com/Perlmint/glew-cmake")
FetchContent_MakeAvailable(glew)

# - Glm
FetchContent_Declare(glm 
    GIT_REPOSITORY "https://github.com/g-truc/glm")
FetchContent_MakeAvailable(glm)

# - Imgui with docking
FetchContent_Declare(imgui
    GIT_REPOSITORY "https://github.com/ocornut/imgui"
    GIT_TAG "origin/docking")
FetchContent_MakeAvailable(imgui)
add_library(CustomImgui STATIC
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glut.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)
target_include_directories(CustomImgui PUBLIC ${imgui_SOURCE_DIR})
target_link_libraries(CustomImgui PRIVATE freeglut GL GLU)

# Common
file(GLOB_RECURSE CG_COMMON_SOURCES
    "common/src/*.cpp"
)

# Generator
file(GLOB_RECURSE CG_GENERATOR_SOURCES
    "generator/src/*.cpp"
)
add_executable(cg-generator ${CG_GENERATOR_SOURCES} ${CG_COMMON_SOURCES})
set_target_properties(cg-generator PROPERTIES OUTPUT_NAME "cg-generator")
target_include_directories(cg-generator PUBLIC
    "generator/include/"
    "common/include/"
)

# Engine
file(GLOB_RECURSE CG_ENGINE_SOURCES
    "engine/src/*.cpp"
)
add_executable(cg-engine ${CG_ENGINE_SOURCES} ${CG_COMMON_SOURCES})
set_target_properties(cg-engine PROPERTIES OUTPUT_NAME "cg-engine")
target_include_directories(cg-engine PUBLIC
    "engine/include/"
    "common/include/"
    "lib/"
)
target_link_libraries(cg-engine PUBLIC
    libglew_static
    freeglut
    GL
    GLU
    CustomImgui
    glm
    fmt
)
