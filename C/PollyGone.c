#include<stdio.h>

#define MIN(x, y) ((x) < (y))?(x):(y)

int boxProb[1<<10];
int energies[1<<10];
int dp[1<<14];

int main(){
    // Scan in input
    // This will be tricky, because we will be doing DP with floats!
    int n;
    double f;
    scanf("%d %lf", &n, &f);
    int prob = (int)(f*10000 + 0.5);

    // Short circuit if we don't care about the stupid bird
    if (prob == 0){
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; ++i){
        int energy;
        double probs;
        scanf("%d %lf", &energy, &probs);

        boxProb[i] = (int)(probs*10000 + 0.5);
        energies[i] = energy;
    }

    // Do 0-1 knapsack
    for (int i = 0; i < prob; ++i){
        dp[i] = 1<<30;
    }

    dp[0] = 0;
    int best = 1<<30;
    for (int i = 0; i < n; ++i){
        for (int j = prob-1; j >= 0; --j){
            if (j + boxProb[i] >= prob){
                best = MIN(best, dp[j] + energies[i]);
            }
            else {
                dp[j + boxProb[i]] = MIN(dp[j + boxProb[i]], dp[j] + energies[i]);
            }
        }
    }

    printf("%d\n", best);

    return 0;
}
