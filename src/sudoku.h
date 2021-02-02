//
// Created by rigoberto on 27/01/21.
//
#include <stdio.h>
#ifndef SUDOKU_C_SUDOKU_H
#define SUDOKU_C_SUDOKU_H

#define SIZE_SUDOKU 9
#define SIZE_SQRT 3

static inline void free_a3d(int*** a3d) {
    int i = 0;
    if(a3d != NULL) {
        int j = 0;
        while(a3d[i] != NULL) {
            while (a3d[i][j] != NULL)
                free(a3d[i][j++]);
            free(a3d[i++]);
        }
        free(a3d);
    }
}

static inline void free_a2d(int** a2d) {
    int i = 0;
    if(a2d != NULL)
        while (a2d[i] != NULL)
            free(a2d[i++]);
    free(a2d);
}

static inline void print(int* a) {
    int i = 0;
    if(a != NULL)
        while (a[i] != EOF)
            printf("%d ", a[i++]);
    printf("\n");
}

static inline int size(const int* a) {
    if (a == NULL) return 0;
    int i = 0;
    for(; a[i] != EOF; i++);
    return i;
}

static inline int search(const int* a, int v) {
    int i = 0;
    if (a != NULL)
        while (a[i] != EOF)
            if (a[i++] == v)
                return 1;
    return 0;
}

static inline int* get_row(int** a2d, int r) {
    int* a = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; a[i] = a2d[r][i], i++);
    a[SIZE_SUDOKU] = EOF;
    return a;
}

static inline int* get_col(int** a2d, int c) {
    int* a = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; a[i] = a2d[i][c], i++);
    a[SIZE_SUDOKU] = EOF;
    return a;
}

static inline int* get_grid(int** a2d, int r, int c) {
    int *l = calloc(SIZE_SUDOKU + 1, sizeof (int)), e = 0;
    for (int i = (r / SIZE_SQRT) * SIZE_SQRT; i <= (r / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; i++)
        for (int j = (c / SIZE_SQRT) * SIZE_SQRT; j <= (c / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; j++)
            l[e++] = a2d[i][j];
    l[SIZE_SUDOKU] = EOF;
    return l;
}

static inline int** get_row_2d(int*** a3d, int r) {
    int** a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        int s = size(a3d[r][i]), *a = calloc(s + 1, sizeof (int));
        for(int j = 0; j < s; a[j] = a3d[r][i][j], j++);
        a[s] = EOF, a2d[i] = a;
    }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

static inline int** get_col_2d(int*** a3d, int c) {
    int** a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        int s = size(a3d[i][c]), *a = calloc(s + 1, sizeof (int));
        for(int j = 0; j < s;  a[j] = a3d[i][c][j], j++);
        a[s] = EOF, a2d[i] = a;
    }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

static inline int** get_grid_2d(int*** a3d, int r, int c) {
    int **a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*)), e = 0;
    for (int i = (r / SIZE_SQRT) * SIZE_SQRT; i <= (r / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; i++)
        for (int j = (c / SIZE_SQRT) * SIZE_SQRT; j <= (c / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; j++) {
            int s = size(a3d[i][j]), *a = calloc(s + 1, sizeof (int));
            for(int k = 0; k < s;  a[k] = a3d[i][j][k], k++);
            a[s] = EOF, a2d[e++] = a;
        }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

int** open_sudoku(char* file);

int** get_map_2d(int** a2d, int r, int c);
int*** get_map_3d(int*** a3d, int r, int c);

int* get_elements(int** a2d, int r, int c);
int size_options(const int* a);

int* get_options(int** s, int r, int c);
int*** get_all_options(int** s);

int* unique(int** a2d);


#endif //SUDOKU_C_SUDOKU_H
