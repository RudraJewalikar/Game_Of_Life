cmake_minimum_required(VERSION 3.16)

project(game_of_life_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSYS OR MINGW)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

endif()

add_library(gol STATIC src/Grid.cpp src/Cell.cpp)

target_include_directories(gol PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(gol_cli src/main.cpp)

target_link_libraries(gol_cli PRIVATE gol)

add_executable(gol_tests tests/test_grid.cpp)

target_link_libraries(gol_tests PRIVATE gol)