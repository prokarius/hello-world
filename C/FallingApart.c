#include<stdio.h>
#include<stdlib.h>

int numbers[128];

int cmpfunc(const void* a, const void* b){
    return *(int*)b - *(int*)a;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &numbers[i]);
    }

    qsort(numbers, n, sizeof(int), cmpfunc);

    int out[2] = {0,0};
    for (int i = 0; i < n; ++i){
        out[i%2] += numbers[i];
    }

    printf("%d %d\n", out[0], out[1]);

    return 0;
}
