#include<stdio.h>

#define MOD 1000000007

int main(){
    int n, x;
    int ones = 0;
    long long twos = 0;
    long long ans = 0;

    // Scan in input
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d", &x); 

        // If 1, add to the number of starting positions
        if (x == 1) ones++;

        // If 2, double the running count because for each existing track in running
        // count, we can choose to include or not include this song
        // Also add the number of starting positions, to say exclude all
        // this is the second ever song in the playlist
        else if (x == 2) twos = (2*twos + ones) % MOD;

        // If 3, bank the running count
        else ans = (ans + twos) % MOD;
    }

    // Print the answer
    printf("%lld\n", ans % MOD);

    return 0;
}
