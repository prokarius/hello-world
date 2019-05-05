#include<stdio.h>

int gallery[205][2];

// DP state is dp[roomsConsidered][numberSelected][left/right]
// The value is the minimum number as stored
int dp[205][205][2];
int n, k;

int MIN(int x, int y){
    return (x < y)?(x):(y);
}

int MIN3(int x, int y, int z){
    return MIN(MIN(x, y), z);
}

void reset(){
    for (int i = 0; i < 205; ++i){
        for (int j = 0; j < 205; ++j){
            dp[i][j][0] = -1;
            dp[i][j][1] = -1;
        }
    }
}

int run(int currRow, int numChosen, int leftRight){
    // Check if we have memoized
    if (dp[currRow][numChosen][leftRight] != -1){
        return dp[currRow][numChosen][leftRight];
    }

    // If we have exceeded the length of the gallery, then check if we fulfilled our
    // objective. If we have not, return INFINITY, else, return 0.
    if (currRow >= n){
        if (numChosen == k){
            return 0;
        }
        return 9999999;
    }

    // 3 ways. We want to find the minimum of:
    // Case 1) Take the current room
    int case1 = run(currRow+1, numChosen+1, leftRight) + gallery[currRow][leftRight];

    // Case 2) Flip sides and take the room from the other side
    int case2 = run(currRow+2, numChosen+1, 1 - leftRight) + gallery[currRow][leftRight];

    // Case 3) Consider if we don't take anything else from the next row
    int case3 = MIN(run(currRow+1, numChosen, leftRight),
                    run(currRow+1, numChosen, 1 - leftRight));

    dp[currRow][numChosen][leftRight] = MIN3(case1, case2, case3);
    return dp[currRow][numChosen][leftRight];
}

int main(){
    scanf("%d %d", &n, &k);

    while (n != 0 || k != 0){
        reset();
        int total = 0;

        // Scan in input
        for (int i = 0; i < n; ++i){
            scanf("%d %d", &gallery[i][0], &gallery[i][1]);
            total += gallery[i][0];
            total += gallery[i][1];
        }

        // Run DP
        int output = MIN(run(0,0,0), run(0,0,1));

        printf("%d\n", total - output);

        scanf("%d %d", &n, &k);
    }

    return 0;
}
