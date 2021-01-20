cmake_minimum_required(VERSION 3.10)

project (HarmonyEngine)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -I/usr/local/include -I/opt/X11/include -L/usr/local/lib -I/opt/X11/lib")
SET(GCC_COVERAGE_LINK_FLAGS    "-lglfw  -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file(GLOB_RECURSE SRC_FILES
    "src/*.h"
    "src/*.cpp"
    "src/*/*.h"
    "src/*/*.cpp"
)

add_executable(HarmonyEngine ${SRC_FILES})