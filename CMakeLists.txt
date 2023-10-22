cmake_minimum_required(VERSION 3.25)
project(sudoku_game)

set(CMAKE_CXX_STANDARD 20)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

add_executable(sudoku_game main.cpp)

target_link_libraries(sudoku_game ${X11_LIBRARIES})
