#include<stdio.h>

int MAX(int x, int y){return x > y ? x : y;}
int MIN(int x, int y){return x < y ? x : y;}

// Stores the minimum amount of water to add to dam i to overflow the camp
int dp[200005];

int main(){
    // Scan in input
    int n, best;
    scanf("%d %d", &n, &best);
    dp[0] = best;  // It takes best amount of water to flood the camp

    for (int i = 1; i <= n; ++i){
        int d, c, u;
        scanf("%d %d %d", &d, &c, &u);

        // The amount of water to overrun this dam and flood the camp is
        // Water to overflow the dam + how much access to flood the next dam in line
        dp[i] = (c - u) + MAX(0, dp[d] - c);
        best = MIN(best, dp[i]);
    }

    // Print the answer
    printf("%d\n", best);

    return 0;
}

