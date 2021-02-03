//
// Created by rigoberto on 27/01/21.
//
#include <stdio.h>
#ifndef SUDOKU_C_SUDOKU_H
#define SUDOKU_C_SUDOKU_H

#define SIZE_SUDOKU 9
#define SIZE_SQRT 3

static inline void replace_value(int** a2d, int *a) {
    if (a != NULL) {
        a2d[a[1]][a[2]] = a[0];
        free(a);
    }
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

static inline void free_a2d(int** a2d) {
    int i = 0;
    if(a2d != NULL)
        while (a2d[i] != NULL)
            free(a2d[i++]);
    free(a2d);
}

static inline void print(int* a) {
    int i = 0;
    if(a != NULL)
        while (a[i] != EOF)
            printf("%d ", a[i++]);
    printf("\n");
}

static inline int size(const int* a) {
    if (a == NULL) return 0;
    int i = 0;
    for(; a[i] != EOF; i++);
    return i;
}

static inline int search(const int* a, int v) {
    int i = 0;
    if (a != NULL)
        while (a[i] != EOF)
            if (a[i++] == v)
                return 1;
    return 0;
}

static inline int* get_row(int** a2d, int r) {
    int *a = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; a[i] = a2d[r][i], i++);
    a[SIZE_SUDOKU] = EOF;
    return a;
}

static inline int* get_col(int** a2d, int c) {
    int* a = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; a[i] = a2d[i][c], i++);
    a[SIZE_SUDOKU] = EOF;
    return a;
}

static inline int* get_grid(int** a2d, int r, int c) {
    int *l = calloc(SIZE_SUDOKU + 1, sizeof (int)), e = 0;
    for (int i = (r / SIZE_SQRT) * SIZE_SQRT; i <= (r / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; i++)
        for (int j = (c / SIZE_SQRT) * SIZE_SQRT; j <= (c / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; j++)
            l[e++] = a2d[i][j];
    l[SIZE_SUDOKU] = EOF;
    return l;
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

static inline int* get_options(int** a2d, int r, int c) {
    if(a2d[r][c] != 0) return NULL;
    int *column = get_col(a2d, c), *row = get_row(a2d, r), *grid = get_grid(a2d, r, c), size = 0,
            *cells = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        if (column[i] != 0) cells[column[i] - 1] = 1;
        if (row[i] != 0) cells[row[i] - 1] = 1;
        if (grid[i] != 0) cells[grid[i] - 1] = 1;
    }
    cells[SIZE_SUDOKU] = EOF;
    free(row), free(column), free(grid);

    for (int i = 0; i < SIZE_SUDOKU; i++) if (cells[i] != 1) size++;
    int *a = calloc(size + 1, sizeof (int));
    for (int n = 0, i = 0; n < SIZE_SUDOKU; n++) if (cells[n] != 1) a[i++] = n + 1;
    a[size] = EOF;
    free(cells);
    return a;
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

static inline int* is_unique(int** a2d) {
    if (a2d == NULL) return NULL;
    int **pos = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; pos[i] = calloc(SIZE_SUDOKU + 1, sizeof(int)), pos[i][0] = EOF, i++);
    pos[SIZE_SUDOKU] = NULL;

    for (int i = 1; i <= SIZE_SUDOKU; i++)
        for (int j = 0, c = 0; a2d[j] != NULL; j++)
            if (search(a2d[j], i) == 1)
                pos[i - 1][c++] = j, pos[i - 1][c] = EOF;

    int u = 0, p;
    for (int i = 0; i < SIZE_SUDOKU; i++)
        if (size(pos[i]) == 1) {
            if (u == 0)
                u = i + 1, p = pos[i][0];
            else {
                u = 0;
                break;
            }
        }

    free_a2d(pos);

    if (u != 0) {
        int *a = calloc(3, sizeof (int));
        a[0] = u,
        a[1] = p,
        a[2] = EOF;

        return a;
    }
    return NULL;
}

static inline int get_unique_in_row(int **a2d, int r) {
    int **rows = calloc(SIZE_SUDOKU, sizeof (int*));
    for(int i = 0; i < SIZE_SUDOKU; rows[i] = get_options(a2d, r, i), i++);
    int *u = is_unique(rows);
    free_a2d(rows);
    if (u != NULL) {
        a2d[r][u[1]] = u[0];
        free(u);
        return 1;
    }
    return 0;
}

static inline int get_unique_in_col(int **a2d, int c) {
    int **cols = calloc(SIZE_SUDOKU, sizeof (int*));
    for(int i = 0; i < SIZE_SUDOKU; cols[i] = get_options(a2d, i, c), i++);
    int *u = is_unique(cols);
    free_a2d(cols);
    if (u != NULL) {
        a2d[u[1]][c] = u[0];
        free(u);
        return 1;
    }
    return 0;
}

static inline int get_unique_in_grid(int **a2d, int g) {
    int **grids = calloc(SIZE_SUDOKU, sizeof (int*)), e = 0;
    for (int i = (g / SIZE_SQRT) * SIZE_SQRT; i <= (g / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; i++)
        for (int j = (g % SIZE_SQRT) * SIZE_SQRT; j <= (g % SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; j++)
            grids[e++] = get_options(a2d, i, j);
    int *u = is_unique(grids);
    free_a2d(grids);
    if (u != NULL) {
        a2d[SIZE_SQRT * (g / SIZE_SQRT) + SIZE_SQRT % SIZE_SQRT]
        [SIZE_SQRT * (u[1] % SIZE_SQRT) + SIZE_SQRT / SIZE_SQRT] = u[0];
        free(u);
        return 1;
    }
    return 0;
}

static inline void insert_in_map_2d(int** map, int r, int c, int v) {
    int i = 0;
    while (map[i] != NULL)
        if (map[i][0] == r && map[i][1] == c) return;
        else i++;
    map[i] = calloc(4, sizeof(int)), map[i][0] = r, map[i][1] = c, map[i][2] = v, map[i][3] = EOF;
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

int** open_sudoku(char* file);

int reduce(int** a2d);

#endif //SUDOKU_C_SUDOKU_H
