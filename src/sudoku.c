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

