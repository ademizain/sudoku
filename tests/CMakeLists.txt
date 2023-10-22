cmake_minimum_required(VERSION 3.5)
project(SudokuTest)

set(CMAKE_CXX_STANDARD 14)

# Use find_package to locate Google Test
find_package(GTest REQUIRED)

add_executable(sudoku_test sudoku_test.cpp sudoku_solver.cpp)

# Link with Google Test libraries
target_link_libraries(sudoku_test GTest::GTest GTest::Main)

