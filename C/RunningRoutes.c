#include<stdio.h>

#define MAX(x, y) (x>y)?(x):(y)

int routes[512][512];
int memo[512][512]; // Stores max number of runners using routes in [left][right] inclusive

int dp(int left, int right){
    // Base case: left is further right than right
    if (left >= right) return 0;

    // Base case: If we have seen this state before, return
    if (memo[left][right] != -1) return memo[left][right];

    // Choose left as the arbitrary vertex.
    // Case 1: We could choose not to use it:
    int best = dp(left+1, right);

    // Case 2: Or use any of the paths connected to it
    for (int i = left+1; i <= right; ++i){
        if (routes[left][i] != 1) continue;

        // numRoutes will be that runner + the max of each of the 2 partitions
        int numRoutes = 1 + dp(left+1, i-1) + dp(i+1, right);
        best = MAX(best, numRoutes);
    }

    // Memoize before returning
    memo[left][right] = best;
    return best;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%d", &routes[i][j]);

            // Initialize dp table while we are at it
            memo[i][j] = -1;
        }
    }

    // Do dp
    printf("%d\n", dp(0, n-1));

    return 0;
}
