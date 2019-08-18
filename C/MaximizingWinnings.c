#include<stdio.h>

int maxdp[64][8192]; // dp[x][y][z] stores the max amount of money you have ending up in room x,y after z turns
int mindp[64][8192]; // same as above
int adjlist[64][64];

int MAX(int x, int y){
    return (x > y)?(x):(y);
}

int MIN(int x, int y){
    return (x < y)?(x):(y);
}

void solve(int n){
    // Scan in input
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            int max;
            scanf("%d", &max);
            adjlist[i][j] = max;
        }
    }

    int numSteps;
    scanf("%d", &numSteps);

    // Reset the dp array
    for (int i = 0; i < n; ++i){
        for (int k = 1; k <= numSteps; ++k){
            maxdp[i][k] = -1;
            mindp[i][k] = 1<<30;
        }
    }

    for (int i = 0; i < n; ++i){
        maxdp[i][0] = adjlist[0][i];
        mindp[i][0] = adjlist[0][i];
    }

    // Now we just need to do dp
    for (int k = 1; k < numSteps; ++k){
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                maxdp[i][k] = MAX(maxdp[i][k], maxdp[j][k - 1] + adjlist[j][i]);
                mindp[i][k] = MIN(mindp[i][k], mindp[j][k - 1] + adjlist[j][i]);
            }
        }
    }

    int maxbest = -1;
    int minbest = 1<<30;
    // Print the max
    for (int i = 0; i < n; ++i){
        maxbest = MAX(maxbest, maxdp[i][numSteps-1]);
        minbest = MIN(minbest, mindp[i][numSteps-1]);
    }

    printf("%d %d\n", maxbest, minbest);
}

// DP question.
int main(){

    // Scan in input
    int n;
    scanf("%d", &n);

    while (n != 0){
        solve(n);
        scanf("%d", &n);
    }

    return 0;
}
