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


void reduce(int** a2d) {
    int ***a3d = get_all_options(a2d);
    int **r = NULL, **c = NULL, *u = NULL, **g = NULL;
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        r = get_row_2d(a3d, i);
        u = is_unique(r);
        if (u != NULL) {
            a2d[i][u[1]] = u[0];
        }
        free_a2d(r);
        free(u);
    }

    for (int i = 0; i < SIZE_SUDOKU; i++) {
        c = get_col_2d(a3d, i);
        u = is_unique(c);
        if (u != NULL) {
            a2d[u[1]][i] = u[0];
        }
        free_a2d(c);
        free(u);
    }

    for(int i = 0; i < SIZE_SQRT; i+=SIZE_SQRT) {
        for(int j = 0; j < SIZE_SQRT; j+=SIZE_SQRT) {
            g = get_grid_2d(a3d, i, j);
            u = is_unique(g);
            if (u != NULL) {
                a2d[(i / SIZE_SQRT) * SIZE_SQRT + u[1] / SIZE_SQRT]
                [(j / SIZE_SQRT) * SIZE_SQRT + u[1] % SIZE_SQRT] = u[0];
            }
            free_a2d(g);
            free(u);
        }
    }

    free_a3d(a3d);
}

