/**
 * A mystery hello world in C
 */
#include <stdlib.h>
#include "src/sudoku.h"



int main(int argc, char** argv) {
    int** s = open_sudoku("../resources/sudoku-01.txt");
    printf("Sudoku ok\n");

    printf("Sudoku reduce\n");
    reduce(s);
    printf("Sudoku\n");

    for (int i = 0; i < SIZE_SUDOKU; i++) {
        print(s[i]);
    }
    reduce(s);
    printf("Sudoku\n");

    for (int i = 0; i < SIZE_SUDOKU; i++) {
        print(s[i]);
    }
    reduce(s);
    printf("Sudoku\n");

    for (int i = 0; i < SIZE_SUDOKU; i++) {
        print(s[i]);
    }
    return EXIT_SUCCESS;
}
