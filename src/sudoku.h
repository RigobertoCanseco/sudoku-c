//
// Created by rigoberto on 27/01/21.
//
#include <stdio.h>
#ifndef SUDOKU_C_SUDOKU_H
#define SUDOKU_C_SUDOKU_H
#define SIZE_SUDOKU 9
#define SIZE_SQRT 3

static inline void print(int* a) {
    if (a != NULL)
        for (int i = 0; a[i] != EOF; i++)
            printf("%d ", a[i]);
    printf("\n");
}

static inline int* get_options(int** a2d, int r, int c) {
    if (a2d[r][c] != 0)
        return NULL;

    int *cells = calloc(SIZE_SUDOKU + 1, sizeof (int));
    cells[SIZE_SUDOKU] = EOF;

    for (int i = 0; i < SIZE_SUDOKU; i++) {
        if (a2d[r][i] != 0)
            cells[a2d[r][i] - 1] = 1;
        if (a2d[i][c] != 0)
            cells[a2d[i][c] - 1] = 1;
        if (a2d[(r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT][(c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT] != 0)
            cells[a2d[(r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT][(c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT] - 1] = 1;
    }

    return cells;
}

int** open_sudoku(char* file);

int reduce(int** a2d);

#endif //SUDOKU_C_SUDOKU_H
