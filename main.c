/**
 * A mystery hello world in C
 */
#include "src/sudoku.h"

int main() {
    sudoku s = open_sudoku("../resources/sudoku-01.txt");
    printf("Sudoku ok\n");
    pos x = 8, y = 8;
    list r = get_row(s, y);
    list c = get_col(s, x);
    list g = get_grid(s, y, x);
    list l = get_options(s, y, x);
    printf("Row:%s\n", r);
    printf("Col:%s\n", c);
    printf("Grid:%s\n", g);
    printf("List:%s\n", l);
    free_list(r);
    free_list(c);
    free_list(g);
    free_list(l);


    list** pList = get_all_options(s);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        for (int j = 0; j < SIZE_SUDOKU; j++)
            printf("[%d][%d] = %s\n", i, j, pList[i][j]);
    }

    values(pList);

    free_options(pList);
    close_sudoku(s);

    return 0;
}
