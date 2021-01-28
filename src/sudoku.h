//
// Created by rigoberto on 27/01/21.
//
#include <stdio.h>
#ifndef SUDOKU_C_SUDOKU_H
#define SUDOKU_C_SUDOKU_H

#define SIZE_SUDOKU 9
typedef unsigned char element;
typedef element** sudoku;
sudoku open_sudoku(char *file);
void close_sudoku(sudoku ptr);

#endif //SUDOKU_C_SUDOKU_H
