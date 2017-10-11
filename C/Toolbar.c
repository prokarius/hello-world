#include<stdio.h>
#define min(x,y) x<y ? x:y

int main(){
    long long i, o=2e18, n, ph, ans, ph2=0, array[100005], sum[50002], alt[50002];
    scanf ("%lld", &n);
    for (i=0; i<2*n; ++i){
        scanf (" %lld", &ph);
        array[i] = ph;
    }
    ph = 0;
    for (i=0; i<n; ++i){
        ph2 += array[i];
        sum[i] = ph2;
        ph += array[2*(n-i-1)];
        alt[n-i-2] = ph;
    }
    alt[n] = 0;
    for (i=0; i<n; ++i){
        ans = (sum[i]+alt[i])*(array[0]+array[i+1]);
        o = min (o, ans);
    }
    printf("%lld\n", o);
    return 0;
}
