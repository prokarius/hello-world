#include<stdio.h>

long long dp[10005][102];

int main(){
    int n, w, h;

    scanf("%d %d %d", &n, &w, &h);

    // Initialise the dp table
    // DP state: [length of ribbon used][current row number]
    // Stores the number of ways this can happen ^
    dp[0][0] = 1;

    // For each row number
    for (int r = 1; r <= w; ++r){
        // For the largest possible amount of ribbon used
        for (int j = 0; j <= w*h; ++j){
            // If we used too much ribbon, break
            if (n < j){
                break;
            }

            // Sum up the number of ways to use [x][y] x amount of ribbon
            // to make y rows
            for (int k = 0; k <= h; ++k){
                // If we use negative ribbon from previous row, break
                if (j-k < 0){
                    break;
                }
                dp[j][r] = (dp[j-k][r-1] + dp[j][r]) % 1000000007;
            }
        }
    }

    // Sum up the total number of ways and subtract away the plains:
    long long total = (n/w)>h?~h:~(n/w);
    for (int i = 0; i <= n; ++i){
        total = (total + dp[i][w]) % 1000000007;
    }

    printf("%lld\n", total);

}
