#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)
#define MAX(x,y) (x>y)?(x):(y)

int main(){
    long long i, N, o, k;
    scanf("%lld", &N);
    while (N){
        if (N == 3){
            printf ("4\n");
            scanf("%lld", &N);
            continue;
        }
        if (N < 7){
            printf ("No such base\n");
            scanf ("%lld", &N);
            continue;
        }
        N -= 3;
        k = N;
        i = 2;
        o = 1LL << 40;

        // Brute force check all the factors!

        while (i*i <= N){
            if (!(N%i)){
                if (i > 3) o = MIN(o, i);
                if (N/i > 3) o = MIN(o, N/i);
            }
            ++i;
        }

        if (o > 1LL << 35) printf ("%lld\n", N);
        else printf ("%lld\n", o);
        scanf("%lld", &N);
    }
    return 0;
}
