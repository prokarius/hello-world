#include<stdio.h>

int arr[105];
int dp [102][46000];

int ABS(int x){
    if (x < 0) return -x;
    else return x;
}

int main(){
    int n;
    int i, j, k;

    // Scan in input
    scanf("%d", &n);
    for (i=0; i<n; ++i){
        scanf("%d", &arr[i]);
    }

    // Initialise my dp array
    dp[0][0] = 1;
    int total = 0;

    // Populate the dp array
    // Each element represents whether it's possible to be in that state
    for (i=0; i<n; ++i){
        for (j=i/2; j>=0; --j){
            for (k=45000-arr[i]; k>=0; --k){
                dp[j+1][k+arr[i]] += dp[j][k];
            }
        }
        total += arr[i];
    }

    // Find the best
    int currbest = 0;
    i = 0;
    while (i < total){
        if (dp[n/2][i]){
            if (ABS((total-2*i)) < ABS((total-2*currbest))){
                currbest = i;
            }
            else {
                break;
            }
        }
        ++i;
    }

    if (currbest < total - currbest){
        currbest = total - currbest;
    }

    printf ("%d %d\n", total-currbest, currbest);

    return 0;
}
