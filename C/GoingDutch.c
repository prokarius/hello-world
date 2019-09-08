#include<stdio.h>
#define MIN(x, y) (x < y)?(x):(y)

// DP[x] stores the number of transactions it takes such that bit-mask(x) has
// settled balance
int dp[1<<20];
int amount[24];

int main(){
    int m, n;

    scanf ("%d %d", &m, &n);

    // Find how much someone is taking / putting in the pool
    for (int i = 0; i < n; ++i){
        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);
        amount[a] += p;
        amount[b] -= p;
    }

    // Do Bottom up DP
    dp[0] = 0;
    for (int i = 1; i < (1<<m); ++i){
        int balance = 0;
        int numTransactions = 9999999;

        // Get the minimum number of transactions to hit the bitmask
        for (int j = 0; j < m; ++j){
            if (i & (1<<j)){
                numTransactions = MIN(numTransactions, dp[i ^ (1<<j)]);
                balance += amount[j];
            }
        }

        // The number of transactions needed += 1 if the balance is not 0
        dp[i] = numTransactions + (balance != 0);
    }

    printf("%d\n", dp[(1<<m) - 1]);

    return 0;
}
