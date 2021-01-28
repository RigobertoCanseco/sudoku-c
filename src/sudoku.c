//
// Created by rigoberto on 27/01/21.
//
#include <malloc.h>
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
    s = calloc(SIZE_SUDOKU, sizeof (element *));
    s[0] = calloc(SIZE_SUDOKU, sizeof (element));
    while ((c = getc(fp)) != EOF) {
        if (c != '\n')
            s[i][j++] = c;
        else {
            j = 0;
            s[++i] = calloc(9, sizeof (element));
        }
    }
    fclose(fp);
    return s;
}

/**
 * Close punter of sudoku
 * @param ptr
 */
void close_sudoku(sudoku ptr) {
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        free(ptr[i]);
    }
    free(ptr);
}