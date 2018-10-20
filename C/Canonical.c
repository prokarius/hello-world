#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

int numCoins;
int coins[105];
int dp[2000005];

int greedy(int value, int nCoins){
    int out = 0;
    while (nCoins > 0){
        nCoins--;
        int curr = value / coins[nCoins];
        out += curr;
        value -= curr * coins[nCoins];
    }
    return out;
}

int main(){
    int n;
    scanf("%d", &n);

    if (n == 1){
        printf("canonical\n");
        return 0;
    }

    for (int i = 0; i < n; ++i){
        scanf("%d", &coins[i]);
    }

    int coinmax = coins[n-1] + coins[n-2];
    dp[0] = 0;

    for (int i = 1; i <= coinmax; ++i){
        int currmin = 1<<30;
        for (int j = 0; j < n; ++j){
            if (i < coins[j]) break;
            currmin = MIN(currmin, dp[i-coins[j]]);
        }
        dp[i] = currmin + 1;
    }

    for (int i = 0; i <= coinmax; ++i){
        if (greedy(i, n) > dp[i]){
            printf("non-canonical\n");
            return 0;
        }
    }

    printf("canonical\n");
    return 0;
}

