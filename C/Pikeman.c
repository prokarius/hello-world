// Does not work for Pikeman Hard because of long long overflow

#include <stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

int main(){    
    long long N, T, A, B, C, i, j=0, k, q, reps, rem, ph, count=0, out=0, out2=0, curt=0, array[100005]={0}, array2 [100005]={0};
    scanf ("%lld %lld", &N, &T);
    scanf ("%lld %lld %lld %lld", &A, &B, &C, &q);
    while (array[q] == 0){
        array[q]++;
        array2[count] = q;
        q = ((A*q + B)%C)+1;
        count++;
    }

    while (array2[j] != q){ //j is index where it loops
        j++;
    }
    k = count-j; //k is the length of the loop

    reps = (N-j)/k;
    rem = (N-j)%k;
    for (i=j; i<count; i++){
        array[array2[i]] = reps;
        if (i-j < rem){
            array[array2[i]]++;
        }
    }

    i=1;
    while (T > i){
        if (out == N){
            break;
        }
        ph = MIN(array[i], T/i);
        out += ph;
        T -= ph*i;
        out2 = (out2 + curt*ph+((ph*(ph+1)*i)/2))%1000000007;
        curt += ph*i;
        i++;
    }
    printf("%lld %lld\n", out, out2);
    return 0;
}
