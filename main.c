/**
 * A mystery hello world in C
 */
#include <stdlib.h>
#include "src/sudoku.h"



int main(int argc, char** argv) {
    int** s = open_sudoku("../resources/sudoku-01.txt");
    printf("Sudoku ok\n");
    int x = 2, y = 0;

    printf("Row:\n");
    int* row = get_row(s, y);
    print(row);
    free(row);

    printf("Col:\n");
    int* col = get_col(s, x);
    print(col);
    free(col);

    printf("Grid:\n");
    int* grid = get_grid(s, y, x);
    print(grid);
    free(grid);

    printf("Options:\n");
    int* ls = get_options(s, y, x);
    print(ls);
    free(ls);

    printf("Map:\n");
    int** ls2 = get_map_2d(s, y, x);
    for(int  i = 0; i < 21; i++) {
        printf("[%d,%d]: %d\n", ls2[i][0], ls2[i][1], ls2[i][2]);
    }
    free_a2d(ls2);

    printf("All Options:\n");
    int*** ls3 = get_all_options(s);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        for (int j = 0; j < SIZE_SUDOKU; j++) {
            printf("[%d,%d]:", i, j);
            print(ls3[i][j]);
        }
    }

    printf("Rows:\n");
    int** rows = get_row_2d(ls3, y);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        printf("Row[%d][%d]:", y, i);
        print(rows[i]);
    }
    free_a2d(rows);

    printf("Cols:\n");
    int** cols = get_col_2d(ls3, x);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        printf("Col[%d][%d]:", i, x);
        print(cols[i]);
    }
    free_a2d(cols);

    printf("Grids:\n");
    int** grids = get_grid_2d(ls3, y, x);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        printf("Grid[%d]:", i);
        print(grids[i]);
    }
    free_a2d(grids);

    int*** ls4 = get_map_3d(ls3, y, x);
    printf("Map options:\n");
    for(int  i = 0; i < 21; i++) {
        printf("[%d,%d]: ", ls4[i][0][0], ls4[i][0][1]);
        print(ls4[i][1]);
    }
    free_a3d(ls4);


    free_a3d(ls3);
    free_a2d(s);

    return EXIT_SUCCESS;
}
