cmake_minimum_required(VERSION 3.10)

project (HarmonyEngine)

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -I/usr/local/include -I/opt/X11/include -I/opt/X11/lib")
set(GCC_COVERAGE_LINK_FLAGS    "-lglfw -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -L/usr/local/lib")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

set(CMAKE_LIBRARY_PATH includes)

file(GLOB_RECURSE SRC_FILES
    "src/*.h"
    "src/*.cpp"
    "src/*/*.h"
    "src/*/*.cpp"
)

add_library(
    STB_IMAGE_LIB
    includes/stb_image/stb_image.cpp
    includes/stb_image/stb_image.h
)

add_executable(HarmonyEngine ${SRC_FILES})
target_link_libraries(HarmonyEngine PRIVATE STB_IMAGE_LIB)