#include<stdio.h>
#define MAX(x,y) (x>y)?(x):(y)

int bitmask[100];

int main(){
    int counter=0, bitlen, i=0;
    long long N, ph, ans=0, k;
    scanf("%lld %lld",&N,&k);
    ++N;

    // First, write the bits of the number backwards.
    // bitmask[0] contains the LSB.
    // counter keeps the number of 1s already encountered
    for (bitlen = 0; N; ++bitlen){
        bitmask[bitlen] = N%2;
        if (bitmask[bitlen]) ++counter;
        N /= 2;
    }

    // While we have more than k 1s, remove 1s from the LSB
    // Do this by sweeping from LSB to MSB
    // If we see a 1, remove the entire chain of 1s.
    // Then add back a 1 after we reached the end of the 1s.
    while (counter > k){
        if (bitmask[i]){
            bitmask[i] = 0;
            --counter;
            while (bitmask[++i]){
                bitmask[i] = 0;
                --counter;
            }
            bitmask[i] = 1;
            ++counter;
        }
        else ++i;
    }

    // Now we are guarenteed to have a bunch of 0s as the LSB
    // Add back the 1s until we have k 1s again
    // If there are bits which are already 1s, just skip past them
    i = 0;
    while (counter < k){
        if (!bitmask[i]){
            bitmask[i] = 1;
            ++counter;
        }
        ++i;
    }

    // Generate the answers
    int end = 64;
    k = 1;
    i = -1;
    while (++i<end){
        if (bitmask[i]) ans += k;
        k *= 2;
    }
    printf ("%lld\n", ans);
    return 0;
}
