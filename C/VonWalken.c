#include <stdio.h>
#define MIN(x, y) (x<y)?(x):(y)
#define MAX(x, y) (x>y)?(x):(y)

int main(){
    double D, high = 1, low = 0, a, ph=0;
    int nstep, array[10005], i=0;
    scanf ("%lf %d", &D, &nstep);
    while (i++ < nstep){
        scanf("%d", &array[i]);
    }
    for (i=1; i<=nstep; i++){
        ph += array[i];
        a = D*i-ph;
        low = MAX(low, a);
        high = MIN(high, a+1);
    }
    if (low <= high) printf("possible\n");
    else printf("impossible\n");
    return 0;
}
