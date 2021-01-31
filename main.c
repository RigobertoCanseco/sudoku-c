/**
 * A mystery hello world in C
 */
#include <stdlib.h>
#include "src/sudoku.h"

void print(int* l) {
    if(l != NULL) {
        int i = 0;
        while (l[i] != EOF) {
            printf("%d ", l[i++]);
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    int** s = open_sudoku("../resources/sudoku-01.txt");
    printf("Sudoku ok\n");
    int x = 4, y = 2;
    int* row = get_list(s, y, f_row);
    int* col = get_list(s, x, f_col);
    int* grid = get_grid(s, y, x, f_grid);
    int* ls = get_options(s, y, x);
    printf("Row:\n");
    print(row);
    printf("Col:\n");
    print(col);
    printf("Grid:\n");
    print(grid);
    printf("Options:\n");
    print(ls);

    free_list(row);
    free_list(col);
    free_list(grid);
    free_list(ls);



    int*** pList = (int ***) get_all_options(s);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        for (int j = 0; j < SIZE_SUDOKU; j++) {
            printf("[%d,%d]:", i, j);
            print(pList[i][j]);
        }

    printf("Row to Array 3D\n");
    //int** row1 = get_list(pList, y, f_row);
    for (int j = 0; j < SIZE_SUDOKU; j++) {
        printf("[%d,%d]:", y, j);
        print(pList[y][j]);
    }

    free_pplist(pList);


    /*
    printf("List \n");
    list* pList1 = get_row_of_list(pList, y);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        printf("[%d][%d] = %s\n", y, i, pList1[i]);
    }
    free_plist(pList1);
    */

    close_sudoku(s);

    return EXIT_SUCCESS;
}
