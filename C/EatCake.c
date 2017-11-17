#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

int eat(int N, int R){
    if (N == 0){
        return 0;
    }
    if (N < 0 || R>10){
        return 99999;
    }
    return MIN(eat(N - R*R, R) + 1, eat(N, R+1));
}

int eat2(int N){
    int array[100000], i, j;
    array[0] = 0;
    for (i=1; i<=N; ++i){
        array[i] = 99999;
        for (j=1; j*j <= i; ++j){
            array[i] = MIN(array[i], array[i - j*j] + 1);
        }
    }
    return array[N];
}

int main(){
    int i=0, T, N;
    scanf("%d", &T);
    while (i++ < T){
        scanf("%d", &N);
        printf ("Case #%d: %d\n", i, eat2(N));
    }
    return 0;
}
