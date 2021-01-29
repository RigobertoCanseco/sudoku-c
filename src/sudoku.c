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
sudoku open_sudoku(char *file) {
    printf("Opening file:%s ...\n", file);
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Can not open file\n");
        return NULL;
    }

    sudoku s = NULL;
    int c, i = 0, j = 0;
    s = calloc(SIZE_SUDOKU, sizeof (cell *));
    s[0] = calloc(SIZE_SUDOKU, sizeof (cell));
    while ((c = getc(fp)) != EOF) {
        if (c != '\n')
            s[i][j++] = c;
        else {
            j = 0;
            s[++i] = calloc(9, sizeof (cell));
        }
    }
    fclose(fp);
    return s;
}

void close_sudoku(sudoku ptr) {
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        free(ptr[i]);
    }
    free(ptr);
}

list get_col(sudoku s, pos p) {
    list c = calloc(SIZE_SUDOKU, sizeof (cell));
    for (int i = 0; i < SIZE_SUDOKU; i++)
        c[i] = s[i][p];

    return c;
}

list get_row(sudoku s, pos p) {
    list r = calloc(SIZE_SUDOKU, sizeof (cell));
    for (int i = 0; i < SIZE_SUDOKU; i++)
        r[i] = s[p][i];

    return r;
}

list get_grid(sudoku s, pos r, pos c) {
    list g = calloc(SIZE_SUDOKU, sizeof (cell));
    int e = 0;
    for (int i = (r / (int) sqrt(SIZE_SUDOKU)) * 3; i <= (r / (int) sqrt(SIZE_SUDOKU)) * 3 + 2; i++)
        for (int j = (c / (int) sqrt(SIZE_SUDOKU)) * 3; j <= (c / (int) sqrt(SIZE_SUDOKU)) * 3 + 2; j++)
            g[e++] = s[i][j];

    return g;
}

list get_options(sudoku s, pos r, pos c) {
    if(s[r][c] != '0') {
        return NULL;
    } else {
        list column = get_col(s, c), row = get_row(s, r), grid = get_grid(s, r, c);
        cell* cells = calloc(SIZE_SUDOKU, sizeof (cell));
        for (int i = 0; i < SIZE_SUDOKU; i++) {
            if (column[i] != '0')
                cells[column[i] - 1 - '0'] = '1';
            if (row[i] != '0')
                cells[row[i] - 1 - '0'] = '1';
            if (grid[i] != '0')
                cells[grid[i] - 1 - '0'] = '1';
        }
        free_list(row);
        free_list(column);
        free_list(grid);

        int count = 0;
        for (int i = 0; i < SIZE_SUDOKU; i++)
            if (cells[i] != '1')
                count++;
        list l = calloc(count, sizeof (cell));
        for (int n = 0, i = 0; n < SIZE_SUDOKU; n++)
            if(cells[n] != '1')
                l[i++] = (n + 1) + '0';

        free(cells);
        return l;
    }
}

list** get_all_options(sudoku s) {
    list** options = calloc(SIZE_SUDOKU, sizeof (list*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        options[i] = calloc(SIZE_SUDOKU, sizeof (list));
        for (int j = 0; j < SIZE_SUDOKU; j++) {
            options[i][j] = get_options(s, i, j);
        }
    }
    return options;
}

list** values(list** pList) {
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        for (int j = 0; j < SIZE_SUDOKU; j++) {
            if(pList[i][j] != NULL){

            }
        }
    }
}


void free_list(list l) {
    free(l);
}

void free_options(list** l) {
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        for (int j = 0; j < SIZE_SUDOKU; j++)
            free(l[i][j]);
        free(l[i]);
    }
    free(l);
}