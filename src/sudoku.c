
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

int reduce(int **a2d) {
    printf("Sudoku\n");
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        print(a2d[i]);
    }
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        for (int j = 0; j < SIZE_SUDOKU; j++) {
            //printf("[%d, %d] = ", i, j);
            int *option = get_options(a2d, i, j);
            //print(option);
            if (option != NULL) {
                int c = 0;
                for (int k = 0; k < SIZE_SUDOKU; k++) {
                    if (option[k] == 0) {
                        a2d[i][j] = k + 1;
                        reduce(a2d);
                    } else c++;
                }
                if (c == 9) {
                    printf("%d, %d\n", i, j);
                    return 0;
                }
            }
            free(option);
        }
    }
    return 1;
}

