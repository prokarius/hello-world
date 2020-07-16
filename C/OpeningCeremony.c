#include<stdio.h>
#include<stdlib.h>

#define MIN(x, y) ((x)<(y)?(x):(y))

// cmpfunc for qsort
int cmpfunc(const void *a, const void *b){
    return *(int*) a < *(int*) b;
}

int heights[100005];

int main(){
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &heights[i]);
    }

    // Sort the heights backwards
    qsort(heights, n, sizeof(int), cmpfunc);

    // Sentinel value
    heights[n] = 0;

    int min = 1<<30;

    // Shoot down the largest i buildings.
    for (int i = 0; i <= n; ++i){
        min = MIN(min, i + heights[i]);
    }

    printf("%d\n", min);

    return 0;
}

