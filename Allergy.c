#include<stdio.h>

int main(){
    int N, array[21],i=0;
    scanf("%d", &N);
    int o = N;

    while(N--){
        int ph;
        scanf("%d", &array[N]);
        --ph;
        if (ph){
            array[i] = ph;
            ++i;
        }
    }

    return 0;
}
