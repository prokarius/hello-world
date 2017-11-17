#include<stdio.h>
#define MAX(x,y) ((x)>(y))?(x):(y)

int count[1000005];

int cmpfunc (const void * a, const void * b){
    return ( *(int*)a - *(int*)b);
}

int cod(int N){
    int maax=-1, i, j, array[10005];
    for (i=0; i<N; i++){
        int ph;
        scanf("%d", &ph);
        array[i] = ph;
        ++count[ph];
    }

    for (i=0; i<1000001; i++){
        maax = MAX(count[i], maax);
        count[i] = 0;
    }

    qsort(array, N, sizeof(int), cmpfunc);

    printf("%d\n", maax);
    for (i=0; i<maax; i++){
        for (j=0; i+j<N; j+=maax){
            if (i<j){printf(" ");};
            printf("%d", array[i+j]);
        }
        printf("\n");
    }
}

int main(){
    int N;
    scanf("%d", &N);
    while (N){
        cod(N);
        scanf("%d", &N);
    }
    return 0;
}
