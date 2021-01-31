//
// Created by rigoberto on 27/01/21.
//
#include <stdio.h>
#ifndef SUDOKU_C_SUDOKU_H
#define SUDOKU_C_SUDOKU_H

#define SIZE_SUDOKU 9

int** open_sudoku(char *file);
void close_sudoku(int** ptr);

void* f_row(void *s, int p, int i);
void* f_col(void *s, int p, int i);
void* f_grid(void *s, int i, int j);

void* get_list(void *s, int p, void* (*f)(void* s, int p, int i));
void* get_grid(int** s, int r, int c, void* (*f)(void *s, int i, int j));

int* get_elements(void* s, int r, int c);
int size_options(const int* a);

int* get_options(void* s, int r, int c);
int*** get_all_options(int** s);

void free_list(int* l);
void free_plist(int** l);
void free_pplist(int*** l);
#endif //SUDOKU_C_SUDOKU_H
