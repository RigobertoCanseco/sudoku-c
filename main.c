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


    return EXIT_SUCCESS;
}
