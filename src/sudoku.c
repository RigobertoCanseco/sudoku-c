//
// Created by rigoberto on 27/01/21.
//
#include <malloc.h>
#include <math.h>
#include "sudoku.h"

/**
 * Open file with sudoku
 * @param file File location
 * @return sudoku data type
 */
int** open_sudoku(char *file) {
    printf("Opening file:%s ...\n", file);
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Can not open file\n");
        return NULL;
    }

    int** s = calloc(SIZE_SUDOKU, sizeof (int*));
    int c, i = 0, j = 0;

    s[0] = calloc(SIZE_SUDOKU, sizeof (int));
    while ((c = getc(fp)) != EOF) {
        if (c != '\n')
            s[i][j++] = c - '0';
        else {
            j = 0;
            s[++i] = calloc(SIZE_SUDOKU, sizeof (int));
        }
    }
    fclose(fp);
    return s;
}

void close_sudoku(int** ptr) {
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        free(ptr[i]);
    }
    free(ptr);
}

void* f_row(void *s, int p, int i) {
    return &((int**)s)[p][i];
}

void* f_col(void* s, int p, int i) {
    return &((int**)s)[i][p];
}

void* f_grid(void* s, int i, int j) {
    return &((int**)s)[i][j];
}

void* get_list(void* s, int p, void* (*f)(void *s, int p, int i)) {
    int* l = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU;  i++)
        l[i] = *(int*) f(s, p, i);
    l[SIZE_SUDOKU] = EOF;
    return l;
}

void* get_grid(int** s, int r, int c, void* (*f)(void *s, int i, int j)) {
    int* l = calloc(SIZE_SUDOKU + 1, sizeof (int));
    int e = 0;
    for (int i = (r / (int) sqrt(SIZE_SUDOKU)) * 3; i <= (r / (int) sqrt(SIZE_SUDOKU)) * 3 + 2; i++)
        for (int j = (c / (int) sqrt(SIZE_SUDOKU)) * 3; j <= (c / (int) sqrt(SIZE_SUDOKU)) * 3 + 2; j++)
            l[e++] = *(int*)f(s, i, j);
    l[SIZE_SUDOKU] = EOF;
    return l;
}

int* get_elements(void* s, int r, int c) {
    int* column = (int*) get_list(s, c, f_col);
    int* row = (int*) get_list(s, r, f_row);
    int* grid = (int*) get_grid(s, r, c, f_grid);
    int* cells = calloc(SIZE_SUDOKU, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        if (column[i] != 0)
            cells[column[i] - 1] = 1;
        else if (row[i] != 0)
            cells[row[i] - 1] = 1;
        else if (grid[i] != 0)
            cells[grid[i] - 1] = 1;
    }
    free_list(row);
    free_list(column);
    free_list(grid);
    return cells;
}

int size_options(const int* a) {
    int size = 0;
    for (int i = 0; i < SIZE_SUDOKU; i++)
        if (a[i] != 1)
            size++;
    return size;
}

int* options(void* s, int r, int c) {
    int* o = get_elements(s, r, c);
    int size = size_options(o);
    int* l = calloc(size + 1, sizeof (int));
    for (int n = 0, i = 0; n < SIZE_SUDOKU; n++)
        if(o[n] != 1)
            l[i++] = n + 1;
    l[size] = EOF;
    free(o);
    return l;
}

int* get_options(void* s, int r, int c) {
    if(  ((int***)s)[r][c] != 0 )
        return NULL;
    return options(s, r, c);
}

int*** get_all_options(int** s) {
    int*** options = calloc(SIZE_SUDOKU, sizeof (int**));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        options[i] = calloc(SIZE_SUDOKU, sizeof (int*));
        for (int j = 0; j < SIZE_SUDOKU; j++) {
            options[i][j] = get_options(s, i, j);
        }
    }
    return options;
}

void free_list(int* l) {
    free(l);
}

void free_pplist(int*** l) {
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        for (int j = 0; j < SIZE_SUDOKU; j++)
            free(l[i][j]);
        free(l[i]);
    }
    free(l);
}

void free_plist(int** l) {
    for (int i = 0; i < SIZE_SUDOKU; i++)
        free(l[i]);
    free(l);
}