#include<stdio.h>

long long sum[3005]; // Sum of all the bananas from 0 to the number
long long dp[3005]; // output
long long diff[3005]; // The bananas to beat

int main(){
    int n, i, j, ph;
    scanf("%d", &n);
    for (i=1; i<=n; ++i){
        scanf ("%d", &ph);
        sum[i] = sum[i-1] + ph;
    }
    // For each starting point
    for (i=1; i<=n ; ++i){
        for (j=i-1; j>=0; --j){
            // If ever the difference is possible to reduce the difference
            // Then do so. It will most definitely help the output
            if (sum[i] - sum[j] >= diff[j]){
                diff[i] = sum[i] - sum[j];
                dp[i] = dp[j]+1;
                break; //You don't want to continue
            }
        }
    }
    printf("%lld\n", dp[n]);
}
