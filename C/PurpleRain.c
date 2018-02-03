#include<stdio.h>
#define MAX(x,y) (x>y)?(x):(y)

int start[2], o[2];

int main(){
    char ph;
    int i, array[100005], ans = 0, end=-1, sum1=0, sum2=0;
    while (scanf ("%c ", &ph) != EOF) array[++end] = (ph=='R')?1:-1;
    for (i = 0; i<=end; ++i){
        sum1 += array[i];
        sum2 -= array[i];
        if (sum1 < 0){
            sum1 = 0;
            start[0] = i+1;
        }
        if (sum2 < 0){
            sum2 = 0;
            start[1] = i+1;
        }
        if (ans < sum1){
            ans = sum1;
            o[0] = start[0];
            o[1] = i;
        }
        else if (ans < sum2){
            ans = sum2;
            o[0] = start[1];
            o[1] = i;
        }
    }
    printf ("%d %d\n", ++o[0], ++o[1]);
    return 0;
}
