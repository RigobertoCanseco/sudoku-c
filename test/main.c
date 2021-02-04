//
// Created by rigoberto on 30/01/21.
//
#include<stdio.h>
#include <malloc.h>
#include "../src/sudoku.h"
typedef struct dynamic_cast dynamic_cast;

int** g_num();
void row(void* a);
int main() {
    int** ptr = g_num();
    int x = 0, y = 2;
    int** s = open_sudoku("../resources/sudoku-01.txt");
    printf("Sudoku ok\n");

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
    printf("Unique:");
    int* u = is_unique(rows);
    print(u);
    free(u);
    free_a2d(rows);

    printf("Cols:\n");
    int** cols = get_col_2d(ls3, x);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        printf("Col[%d][%d]:", i, x);
        print(cols[i]);
    }
    printf("Unique:");
    u = is_unique(cols);
    print(u);
    free(u);
    free_a2d(cols);

    printf("Grids:\n");
    int** grids = get_grid_2d(ls3, y, x);
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        printf("Grid[%d]:", i);
        print(grids[i]);
    }
    printf("Unique:");
    u = is_unique(grids);
    print(u);
    free(u);
    free_a2d(grids);

    int*** ls4 = get_map_3d(ls3, y, x);
    printf("Map options:\n");
    for(int  i = 0; i < 21; i++) {
        printf("[%d,%d]: ", ls4[i][0][0], ls4[i][0][1]);
        print(ls4[i][1]);
    }
    free_a3d(ls4);
    free_a3d(ls3);

    row(ptr);
    return 0;
}

int** g_num() {
    int q[3][3] = {{5, 9, 7},{8,3,2}, {1,4,6}};
    int** s = calloc(3, sizeof (int*));
    for (int i = 0; i < 3; i++) {
        s[i] = (int*)calloc(3, sizeof (int));
        for (int j = 0; j < 3; j++) {
            s[i][j] = q[i][j];
        }
    }

    return s;
}

void row(void* a) {
    int i = 2, j = 1;
    typeof(int*)d = a;
    for (int k = 0; k < 3; k++) {
        int n = *(d + ((sizeof(d))*(i+ 1) + k));
        printf("%d", n);
    }
}


static inline int*** get_all_options(int **a2d) {
    int*** a3d = calloc(SIZE_SUDOKU + 1, sizeof (int**));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        a3d[i] = calloc(SIZE_SUDOKU + 1 , sizeof (int*));
        for (int j = 0; j < SIZE_SUDOKU; a3d[i][j] = a2d[i][j] == 0?get_options(a2d, i, j): NULL, j++);
        a3d[i][SIZE_SUDOKU] = NULL;
    }
    a3d[SIZE_SUDOKU] = NULL;
    return a3d;
}

static inline int*** get_map_3d(int*** a3d, int r, int c) {
    int** row = get_row_2d(a3d, r);
    int** col = get_col_2d(a3d, c);
    int** grid = get_grid_2d(a3d, r, c);
    int*** map = calloc(22, sizeof (int**));

    for (int i = 0; i < SIZE_SUDOKU; insert_in_map_3d(map, r, i, row[i]), i++);
    for (int i = 0; i < SIZE_SUDOKU; insert_in_map_3d(map, i, c, col[i]), i++);
    for (int i = 0; i < SIZE_SUDOKU; insert_in_map_3d(map, (r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT,
                                                      (c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT, grid[i]), i++);
    map[21] = NULL;
    free_a2d(row), free_a2d(grid), free_a2d(col);
    return map;
}


static inline void insert_in_map_3d(int*** map, int r, int c, int* v) {
    int i = 0;
    while (map[i] != NULL)
        if (map[i][0][0] == r && map[i][0][1] == c)
            return ;
        else i++;

    int *p = calloc(3, sizeof (int));
    p[0] = r, p[1] = c, p[2] = EOF;
    int s = size(v);
    int *a = calloc(s + 1, sizeof (int));
    for(int j = 0; j < s; a[j] = v[j], j++);
    a[s] = EOF;
    map[i] = calloc(3, sizeof (int*)), map[i][0] = p, map[i][1] = a, map[i][2] = NULL;
}


static inline int** get_map_2d(int** a2d, int r, int c) {
    int* row = get_row(a2d, r);
    int* col = get_col(a2d, c);
    int* grid = get_grid(a2d, r, c);
    int** map = calloc(22, sizeof (int*));

    for (int i = 0; i < SIZE_SUDOKU; insert_in_map_2d(map, r, i, row[i]), i++);
    for (int i = 0; i < SIZE_SUDOKU; insert_in_map_2d(map, i, c, col[i]), i++);
    for (int i = 0; i < SIZE_SUDOKU; insert_in_map_2d(map, (r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT,
                                                      (c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT, grid[i]), i++);

    map[21] = NULL;
    free(row), free(grid), free(col);

    return map;
}

static inline void insert_in_map_2d(int** map, int r, int c, int v) {
    int i = 0;
    while (map[i] != NULL)
        if (map[i][0] == r && map[i][1] == c) return;
        else i++;
    map[i] = calloc(4, sizeof(int)), map[i][0] = r, map[i][1] = c, map[i][2] = v, map[i][3] = EOF;
}


static inline int** get_row_2d(int*** a3d, int r) {
    int** a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        int s = size(a3d[r][i]), *a = calloc(s + 1, sizeof (int));
        for(int j = 0; j < s; a[j] = a3d[r][i][j], j++);
        a[s] = EOF, a2d[i] = a;
    }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

static inline int** get_col_2d(int*** a3d, int c) {
    int** a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        int s = size(a3d[i][c]), *a = calloc(s + 1, sizeof (int));
        for(int j = 0; j < s;  a[j] = a3d[i][c][j], j++);
        a[s] = EOF, a2d[i] = a;
    }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

static inline int** get_grid_2d(int*** a3d, int r, int c) {
    int **a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*)), e = 0;
    for (int i = (r / SIZE_SQRT) * SIZE_SQRT; i <= (r / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; i++)
        for (int j = (c / SIZE_SQRT) * SIZE_SQRT; j <= (c / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; j++) {
            int s = size(a3d[i][j]), *a = calloc(s + 1, sizeof (int));
            for(int k = 0; k < s;  a[k] = a3d[i][j][k], k++);
            a[s] = EOF, a2d[e++] = a;
        }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

static inline void free_a3d(int*** a3d) {
    int i = 0;
    if(a3d != NULL) {
        int j = 0;
        while(a3d[i] != NULL) {
            while (a3d[i][j] != NULL)
                free(a3d[i][j++]);
            free(a3d[i++]);
        }
        free(a3d);
    }
}

static inline void replace_value(int** a2d, int *a) {
    if (a != NULL) {
        a2d[a[1]][a[2]] = a[0];
        free(a);
    }
}
