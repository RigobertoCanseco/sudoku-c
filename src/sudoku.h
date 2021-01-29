//
// Created by rigoberto on 27/01/21.
//
#include <stdio.h>
#ifndef SUDOKU_C_SUDOKU_H
#define SUDOKU_C_SUDOKU_H

#define SIZE_SUDOKU 9
typedef unsigned char cell;
typedef unsigned char pos;
typedef cell** sudoku;
typedef cell* list;

sudoku open_sudoku(char *file);
void close_sudoku(sudoku ptr);
list get_col(sudoku s, pos p);
list get_row(sudoku s, pos p);
list get_grid(sudoku s, pos r, pos c);
list get_options(sudoku s, pos r, pos c);
list** get_all_options(sudoku s);
list** values(list** pList);
void free_list(list l);
void free_options(list** l);
#endif //SUDOKU_C_SUDOKU_H
