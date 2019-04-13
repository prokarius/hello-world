#include<stdio.h>

#define MOD 1000000007

long long experiment[100005];

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%lld", &experiment[i]);
    }

    // Current number of bacteria
    long long curr = 1L;

    // For each of the experiments, double the bacteria
    for (int i = 0; i < n; ++i){
        curr <<= 1;

        // Check if we have enough bacteria
        if (curr < experiment[i]){
            printf("error\n");
            return 0;
        }

        // Use the bacteria for experiment
        curr -= experiment[i];

        // If the number of bacteria is above 2**60, then mod it until it is just
        // less than 2**60
        // The largest multiple of MOD less than 2**60 is 1152921497*MOD.
        if (curr > (1L<<60)){
            curr = curr % MOD;
            curr += MOD * 1152921497L;
        }
    }

    // Print the number of bacteria left
    printf("%lld\n", curr % MOD);

    return 0;
}
