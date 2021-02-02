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

    int** s = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    int c, i = 0, j = 0;

    s[0] = calloc(SIZE_SUDOKU + 1, sizeof (int));
    while ((c = getc(fp)) != EOF) {
        if (c != '\n'){
            s[i][j++] = c - '0';
        }
        else {
            s[i][SIZE_SUDOKU] = EOF;
            j = 0;
            s[++i] = calloc(SIZE_SUDOKU + 1, sizeof (int));
        }
    }
    s[8][SIZE_SUDOKU] = EOF;
    s[SIZE_SUDOKU] = NULL;
    fclose(fp);
    return s;
}

void insert_in_map_2d(int** map, int r, int c, int v) {
    int i = 0;
    while (map[i] != NULL)
        if (map[i][0] == r && map[i][1] == c)
            return ;
        else i++;

    map[i] = calloc(4, sizeof(int));
    map[i][0] = r;
    map[i][1] = c;
    map[i][2] = v;
    map[i][3] = EOF;
}

void insert_in_map_3d(int*** map, int r, int c, int* v) {
    int i = 0;
    while (map[i] != NULL)
        if (map[i][0][0] == r && map[i][0][1] == c)
            return ;
        else i++;

    int* p = calloc(3, sizeof (int));
    p[0] = r;
    p[1] = c;
    p[2] = EOF;

    int s = size(v);
    int* a = calloc(s + 1, sizeof (int));
    for(int j = 0; j < s; j++)
        a[j] = v[j];
    a[s] = EOF;
    map[i] = calloc(3, sizeof (int*));
    map[i][0] = p;
    map[i][1] = a;
    map[i][2] = NULL;
}

int** get_map_2d(int** a2d, int r, int c) {
    int* row = get_row(a2d, r);
    int* col = get_col(a2d, c);
    int* grid = get_grid(a2d, r, c);
    int** map = calloc(22, sizeof (int*));

    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_2d(map, r, i, row[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_2d(map, i, c, col[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_2d(map, (r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT,
                         (c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT, grid[i]);

    map[21] = NULL;
    free(row);
    free(grid);
    free(col);

    return map;
}

int*** get_map_3d(int*** a3d, int r, int c) {
    int** row = get_row_2d(a3d, r);
    int** col = get_col_2d(a3d, c);
    int** grid = get_grid_2d(a3d, r, c);
    int*** map = calloc(22, sizeof (int**));

    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_3d(map, r, i, row[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_3d(map, i, c, col[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_3d(map, (r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT,
                         (c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT, grid[i]);

    map[21] = NULL;
    free_a2d(row);
    free_a2d(grid);
    free_a2d(col);

    return map;
}

int* get_options(int** a2d, int r, int c) {
    if(a2d[r][c] != 0)
        return NULL;
    int *column = get_col(a2d, c), *row = get_row(a2d, r), *grid = get_grid(a2d, r, c),
            *cells = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        if (column[i] != 0)
            cells[column[i] - 1] = 1;
        if (row[i] != 0)
            cells[row[i] - 1] = 1;
        if (grid[i] != 0)
            cells[grid[i] - 1] = 1;
    }
    cells[SIZE_SUDOKU] = EOF;

    int size = 0;
    for (int i = 0; i < SIZE_SUDOKU; i++) if (cells[i] != 1) size++;
    int *a = calloc(size + 1, sizeof (int));
    for (int n = 0, i = 0; n < SIZE_SUDOKU; n++)
        if(cells[n] != 1)
            a[i++] = n + 1;
    a[size] = EOF;

    free(cells);
    free(row);
    free(column);
    free(grid);
    return a;
}

int*** get_all_options(int** a2d) {
    int*** a3d = calloc(SIZE_SUDOKU + 1, sizeof (int**));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        a3d[i] = calloc(SIZE_SUDOKU + 1 , sizeof (int*));
        for (int j = 0; j < SIZE_SUDOKU; j++)
            if(a2d[i][j] == 0)
                a3d[i][j] = get_options(a2d, i, j);
            else
                a3d[i][j] = NULL;
        a3d[i][SIZE_SUDOKU] = NULL;
    }
    a3d[SIZE_SUDOKU] = NULL;
    return a3d;
}

int* unique(int** a2d) {
    if (a2d == NULL)
        return NULL;
    int** positions = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        positions[i] = calloc(SIZE_SUDOKU + 1, sizeof(int));
        positions[i][0] = EOF;
    }
    positions[SIZE_SUDOKU] = NULL;

    for (int i = 1; i <= SIZE_SUDOKU; i++) {
        int j = 0, c = 0;
        while (a2d[j] != NULL) {
            if (search(a2d[j], i) == 1) {
                positions[i - 1][c++] = j;
                positions[i - 1][c] = EOF;
            }
            j++;
        }
    }

    int u = 0, p;
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        if (size(positions[i]) == 1) {
            if (u == 0) {
                u = i + 1;
                p = positions[i][0];
            } else
                return NULL;
        }
    }
    if (u == 0)
        return NULL;
    int* a = calloc(3, sizeof (int));
    a[0] = u;
    a[1] = p;
    a[2] = EOF;
    free_a2d(positions);

    return a;
}

int** reduce(int** a2d) {
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        for (int j = 0; j < SIZE_SUDOKU; j++) {
        }
    }
}

