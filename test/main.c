//
// Created by rigoberto on 30/01/21.
//
#include<stdio.h>
#include <malloc.h>

typedef struct dynamic_cast dynamic_cast;

int** g_num();
void row(void* a);
int main() {
    int** ptr = g_num();

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