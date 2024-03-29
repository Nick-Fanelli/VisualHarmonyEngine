cmake_minimum_required(VERSION 3.10)

project (HarmonyEngine)

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++17 -Wall -I/usr/local/include -I/opt/X11/include -I/opt/X11/lib -I${CMAKE_CURRENT_SOURCE_DIR}/include")
set(GCC_COVERAGE_LINK_FLAGS    "-lglfw -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -L/usr/local/lib")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/imgui)

file(GLOB_RECURSE SRC_FILES
        "src/**.h"
        "src/**.cpp"
)

set(target ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(link ${CMAKE_BINARY_DIR}/HarmonyEditor/assets)

add_library(HarmonyEngine ${SRC_FILES})

#execute_process(
#        COMMAND bash -c "create_symlink ${target} ${link}"
#)

add_custom_target(link_target ALL
                    COMMAND ${CMAKE_COMMAND} -E create_symlink ${target} ${link})

target_include_directories(HarmonyEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(HarmonyEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(HarmonyEngine ImGUI)

target_precompile_headers(HarmonyEngine PUBLIC "src/harmonypch.h")
target_precompile_headers(HarmonyEngine PUBLIC "src/imguipch.h")