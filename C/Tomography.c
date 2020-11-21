#include<stdio.h>
#include<stdlib.h>

// Decreasing
int cmpfunc(const void* a, const void* b){
    return *(int*) b - *(int*) a;
}

int rows[1024];
int cols[1024];

int main(){
    // Scan in input
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; ++i) scanf("%d", &rows[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &cols[i]);

    qsort(rows, m, sizeof(int), cmpfunc);
    qsort(cols, n, sizeof(int), cmpfunc);

    // Greedy:
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < rows[i]; ++j){
            cols[j] -= 1;
        }
        qsort(cols, n, sizeof(int), cmpfunc);
    }

    // Then see if all the values are 0s
    for (int i = 0; i < n; ++i){
        if (cols[i] != 0){
            printf("No\n");
            return 0;
        }
    }

    // Yup it's possible
    printf("Yes\n");
    return 0;
}

