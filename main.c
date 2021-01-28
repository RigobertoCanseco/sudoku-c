/**
 * A mystery hello world in C
 */
#include "src/sudoku.h"

int main() {
    sudoku s = open_sudoku("../resources/sudoku-01.txt");
    printf("Sudoku ...\n");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c ", s[i][j]);
        }
        printf("\n");
    }
    close_sudoku(s);

    return 0;
}
