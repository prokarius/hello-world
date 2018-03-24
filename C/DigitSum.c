#include <stdio.h>

int slut[11] = {0,0,1,3,6,10,15,21,28,36,45};

long long ds(long long N){
    N += 1;
    long long output=0, mult = 1, t = N;
    while (t!= 0){
        output += mult * 45 * (t/10) + mult * slut[t%10] + (N%mult)*(t%10);
        mult *= 10;
        t /= 10;
    }
    return output;
}

int main(){
    long long num;
    scanf ("%lld", &num);
    while (num > 0){
        long long a, r, outp;
        scanf ("%lld %lld", &a, &r);
        if (a>0){
            outp = ds(r) - ds (a-1);
        }
        else {
            outp = ds(r);
        }
        printf ("%lld\n", outp);
        num -= 1;
    }
    return 0;
}
