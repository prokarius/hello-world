#include<stdio.h>

int n;
long long m;
long long INF = 1LL<<60;

// memo[x][y] Gives the number of x-lengthed sequences that contains y open brackets
long long memo[1<<12][1<<11];

long long dp(int length, int left){
    // Base cases: If we have reached the end, return 1;
    if (length == n){
        if (left == n/2) return 1;
        return 0; // Not enough left brackets
    }

    // Do we have too many right brackets for the number of left brackets?
    int right = length - left;
    if (right > left) return 0;

    // Do we have too many left / right brackets?
    if (left > n/2 || right > n/2) return 0;

    // Have we been here before?
    if (memo[length][left] != 0) return memo[length][left];

    // If not, we can choose to put either a left or right bracket..
    memo[length][left] = dp(length+1, left+1) + dp(length+1, left);

    // Now, if we exceed INF for the value, just return INF
    if (memo[length][left] > INF) memo[length][left] = INF;

    return memo[length][left];
}

int main(){
    // Scan in the two numbers
    scanf("%d %lld", &n, &m);

    // Print while generating dp
    int numLeft = 1;
    for (int i = 1; i <= n; ++i){
        if (dp(i, numLeft) >= m){
            printf("(");
            numLeft++;
        }
        else {
            printf(")");
            m -= dp(i, numLeft);
        }
    }

    printf("\n");

    return 0;
}

