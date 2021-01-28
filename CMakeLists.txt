cmake_minimum_required(VERSION 3.17)
project(sudoku_c C)

set(CMAKE_C_STANDARD 99)

add_executable(sudoku_c main.c src/sudoku.c src/sudoku.h)