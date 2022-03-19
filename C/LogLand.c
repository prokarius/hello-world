#include<stdio.h>

long long MOD = 1000000007;

int main(){
    int n, num;
    long long out = 0;
    long long denom = 1;
    long long leftover = 0;

    // Scan in input
    scanf("%d", &n);

    // Each smaller coin can be paired and then contribute to a denomination up, or thrown
    for (int i = 0; i < n; ++i){
        scanf("%d", &num);
        num += leftover; // Pair the smaller coins here

        // If we have an odd number, and don't have any smaller denominations to pair
        // it up with, throw away the coin since it is useless.
        if ((num & 1) && (leftover == 0)){
            out = (denom + out) % MOD;
        }

        // Divide the number of coins by 2.
        // If this was an odd number, it means we either have pairs of smaller
        // denomination coins, or a single coin of that denomination.
        // If we have pairs of something smaller (leftover != 0) we split them.
        leftover = num >> 1;
        denom = (denom * 2) % MOD;
    }

    printf("%lld\n", out);
    return 0;
}

