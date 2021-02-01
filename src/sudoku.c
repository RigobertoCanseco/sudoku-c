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

int size(const int* a) {
    if (a == NULL)
        return 0;
    int i = 0;
    while(a[i] != EOF)
        i++;
    return i;
}

int* get_row(int** a2d, int r) {
    int* a = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; i++)
        a[i] = a2d[r][i];
    a[SIZE_SUDOKU] = EOF;
    return a;
}

int** get_row_2d(int*** a3d, int r) {
    int** a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        int s = size(a3d[r][i]);
        int* a = calloc(s + 1, sizeof (int));
        for(int j = 0; j < s; j++)
            a[j] = a3d[r][i][j];
        a[s] = EOF;
        a2d[i] = a;
    }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

int* get_col(int** a2d, int c) {
    int* a = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; i++)
        a[i] = a2d[i][c];
    a[SIZE_SUDOKU] = EOF;
    return a;
}

int** get_col_2d(int*** a3d, int c) {
    int** a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        int s = size(a3d[i][c]);
        int* a = calloc(s + 1, sizeof (int));
        for(int j = 0; j < s; j++)
            a[j] = a3d[i][c][j];
        a[s] = EOF;
        a2d[i] = a;
    }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

int* get_grid(int** a2d, int r, int c) {
    int* l = calloc(SIZE_SUDOKU + 1, sizeof (int));
    int e = 0;
    for (int i = (r / SIZE_SQRT) * SIZE_SQRT; i <= (r / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; i++)
        for (int j = (c / SIZE_SQRT) * SIZE_SQRT; j <= (c / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; j++)
            l[e++] = a2d[i][j];
    l[SIZE_SUDOKU] = EOF;
    return l;
}

int** get_grid_2d(int*** a3d, int r, int c) {
    int** a2d = calloc(SIZE_SUDOKU + 1, sizeof (int*));
    int e = 0;
    for (int i = (r / SIZE_SQRT) * SIZE_SQRT; i <= (r / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; i++)
        for (int j = (c / SIZE_SQRT) * SIZE_SQRT; j <= (c / SIZE_SQRT) * SIZE_SQRT + SIZE_SQRT - 1; j++) {
            int s = size(a3d[i][j]);
            int* a = calloc(s + 1, sizeof (int));
            for(int k = 0; k < s; k++)
                a[k] = a3d[i][j][k];
            a[s] = EOF;
            a2d[e++] = a;
        }
    a2d[SIZE_SUDOKU] = NULL;
    return a2d;
}

void insert_in_map_2d(int** map, int r, int c, int v) {
    int i = 0;
    while (map[i] != NULL)
        if (map[i][0] == r && map[i][1] == c)
            return ;
        else i++;

    map[i] = calloc(4, sizeof(int));
    map[i][0] = r;
    map[i][1] = c;
    map[i][2] = v;
    map[i][3] = EOF;
}

void insert_in_map_3d(int*** map, int r, int c, int* v) {
    int i = 0;
    while (map[i] != NULL)
        if (map[i][0][0] == r && map[i][0][1] == c)
            return ;
        else i++;

    int* p = calloc(3, sizeof (int));
    p[0] = r;
    p[1] = c;
    p[2] = EOF;

    int s = size(v);
    int* a = calloc(s + 1, sizeof (int));
    for(int j = 0; j < s; j++)
        a[j] = v[j];
    a[s] = EOF;
    map[i] = calloc(3, sizeof (int*));
    map[i][0] = p;
    map[i][1] = a;
    map[i][2] = NULL;
}

int** get_map_2d(int** a2d, int r, int c) {
    int* row = get_row(a2d, r);
    int* col = get_col(a2d, c);
    int* grid = get_grid(a2d, r, c);
    int** map = calloc(22, sizeof (int*));

    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_2d(map, r, i, row[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_2d(map, i, c, col[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_2d(map, (r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT,
                         (c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT, grid[i]);

    map[21] = NULL;
    free(row);
    free(grid);
    free(col);

    return map;
}

int*** get_map_3d(int*** a3d, int r, int c) {
    int** row = get_row_2d(a3d, r);
    int** col = get_col_2d(a3d, c);
    int** grid = get_grid_2d(a3d, r, c);
    int*** map = calloc(22, sizeof (int**));

    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_3d(map, r, i, row[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_3d(map, i, c, col[i]);
    for (int i = 0; i < SIZE_SUDOKU; i++)
        insert_in_map_3d(map, (r / SIZE_SQRT) * SIZE_SQRT + i / SIZE_SQRT,
                         (c / SIZE_SQRT) * SIZE_SQRT + i % SIZE_SQRT, grid[i]);

    map[21] = NULL;
    free_a2d(row);
    free_a2d(grid);
    free_a2d(col);

    return map;
}

int* get_elements(int** a2d, int r, int c) {
    int* column = get_col(a2d, c);
    int* row = get_row(a2d, r);
    int* grid = get_grid(a2d, r, c);
    int* cells = calloc(SIZE_SUDOKU + 1, sizeof (int));
    for (int i = 0; i < SIZE_SUDOKU; i++)
        if (column[i] != 0)
            cells[column[i] - 1] = 1;
        else if (row[i] != 0)
            cells[row[i] - 1] = 1;
        else if (grid[i] != 0)
            cells[grid[i] - 1] = 1;
    cells[SIZE_SUDOKU] = EOF;
    free(row);
    free(column);
    free(grid);
    return cells;
}

int size_options(const int* a) {
    int size = 0;
    for (int i = 0; i < SIZE_SUDOKU; i++)
        if (a[i] != 1)
            size++;
    return size;
}

int* get_options(int** a2d, int r, int c) {
    if(a2d[r][c] != 0)
        return NULL;
    int* o = get_elements(a2d, r, c);
    int size = size_options(o);
    int* a = calloc(size + 1, sizeof (int));
    for (int n = 0, i = 0; n < SIZE_SUDOKU; n++)
        if(o[n] != 1)
            a[i++] = n + 1;
    a[size] = EOF;
    free(o);
    return a;
}

int*** get_all_options(int** a2d) {
    int*** a3d = calloc(SIZE_SUDOKU + 1, sizeof (int**));
    for (int i = 0; i < SIZE_SUDOKU; i++) {
        a3d[i] = calloc(SIZE_SUDOKU + 1 , sizeof (int*));
        for (int j = 0; j < SIZE_SUDOKU; j++)
            if(a2d[i][j] == 0)
                a3d[i][j] = get_options(a2d, i, j);
            else
                a3d[i][j] = NULL;
        a3d[i][SIZE_SUDOKU] = NULL;
    }
    a3d[SIZE_SUDOKU] = NULL;
    return a3d;
}

int search(const int* a, int v) {
    int i = 0;
    if (a != NULL)
        while (a[i] != EOF)
            if (a[i++] == v)
                return 1;
    return 0;
}

int* get_unique_value(int** a2d) {
    int* pos = calloc(SIZE_SUDOKU + 1, sizeof (int));
    int count;
    for (int i = 0; i < SIZE_SUDOKU; ++i)
       pos[i] = -1;

    for (int n = 1; n <= SIZE_SUDOKU; n++) {
        count = 0;
        for (int i = 0; i < SIZE_SUDOKU; i++)
            if( search(a2d[i], n) == 1) {
                if(count != 0) {
                    pos[n - 1] = (int) -1;
                    break;
                } else {
                    pos[n - 1] = i;
                    count++;
                }
            }
    }
    pos[SIZE_SUDOKU] = EOF;
    return pos;
}

void* unique_value(void *s, int r, int c) {
    int** columns = get_col_2d(s, c);
    int** rows = get_row_2d(s, r);
    int** grids = get_grid_2d(s, r, c);

    int* c_u = get_unique_value(columns);
    int* r_u = get_unique_value(rows);
    int* g_u = get_unique_value(grids);

    free(rows);
    free(columns);
    free(grids);

    int** res = calloc(3, sizeof (int*));
    res[0] = c_u;
    res[1] = r_u;
    res[2] = g_u;


    return res;
    /*
    for (int n = 0; n < SIZE_SUDOKU; n++) {
        if(c_u[n] != 0 && r_u[n] == 0 && g_u[n] == 0)
            col = c_u[n];
    }

        for (int n = 1; n <= SIZE_SUDOKU; n++) {
        for (int i = 0; i < SIZE_SUDOKU; i++) {
            if( search(columns[i], n) == 1) {
                count[n-1]++;
                y = i; x = c;
            }
        }
        for (int i = 0; i < SIZE_SUDOKU; i++) {
            if( search(rows[i], n) == 1) {
                count[n-1]++;
                x = i; y = r;
            }
        }
        for (int i = 0; i < SIZE_SUDOKU; i++) {
            if(search(grids[i], n) == 1) {
                count[n-1]++;
                x = (r / SIZE_SQRT) * 3 + ( i % SIZE_SQRT);
                y = (c / SIZE_SQRT) * 3 + ( i / SIZE_SQRT);
            }
        }
    }
     */

}

void free_a3d(int*** a3d) {
    int i = 0;
    if(a3d != NULL) {
        int j = 0;
        while (a3d[i][j] != NULL)
            free(a3d[i][j++]);
        free(a3d[i++]);
    }
    free(a3d);
}

void free_a2d(int** a2d) {
    int i = 0;
    if(a2d != NULL)
        while (a2d[i] != NULL)
            free(a2d[i++]);
    free(a2d);
}

void print(int* a) {
    int i = 0;
    if(a != NULL)
        while (a[i] != EOF)
            printf("%d ", a[i++]);
    printf("\n");
}