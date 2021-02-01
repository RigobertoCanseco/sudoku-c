//
// Created by rigoberto on 27/01/21.
//
#include <stdio.h>
#ifndef SUDOKU_C_SUDOKU_H
#define SUDOKU_C_SUDOKU_H

#define SIZE_SUDOKU 9
#define SIZE_SQRT (int) sqrt(SIZE_SUDOKU)

int** open_sudoku(char* file);
void print(int* l);
int* get_row(int** a2d, int r);
int** get_row_2d(int*** a3d, int r);
int* get_col(int** a2d, int c);
int** get_col_2d(int*** a3d, int c);
int* get_grid(int** a2d, int r, int c);
int** get_grid_2d(int*** a3d, int r, int c);
int** get_map_2d(int** a2d, int r, int c);
int*** get_map_3d(int*** a3d, int r, int c);

int* get_elements(int** a2d, int r, int c);
int size_options(const int* a);

int* get_options(int** s, int r, int c);
int*** get_all_options(int** s);

void* unique_value(void *s, int r, int c);

void free_a2d(int** l);
void free_a3d(int*** l);
#endif //SUDOKU_C_SUDOKU_H
