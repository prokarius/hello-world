#include <stdio.h>

void thedp(int C, int n){
    int i, j;
    int weightlist [2005], valuelist [2005];
    for (i = 0; i < n; i++){
        int Q, R;
        scanf("%d %d", &Q, &R);
        valuelist[i] = Q;
        weightlist[i] = R;
    }
    int dp[n+1][C+1];
    for (i=0; i<(n+1); i++){
        for (j=0; j<(C+1); j++){
            dp[i][j] = 0;
        }
    }
    for (i=1; i<(n+1); i++){
        for (j=1; j<(C+1); j++){
            if (weightlist[i-1]<=j){
                int value = dp[i-1][j-weightlist[i-1]] + valuelist[i-1];
                if (value > dp[i-1][j]){
                    dp[i][j] = value;
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    int used [n];
    for (i=0; i<n; i++){
        used[i] = 0;
    }
    int posobj = n, poscap = C, outputnum = 0;
    while (posobj >=0){
        if (dp[posobj][poscap] > dp [posobj-1][poscap]){
            used[posobj-1] = 1;
            poscap -= weightlist[posobj-1];
            outputnum += 1;
        }
        posobj -= 1;
    }
    printf("%d\n", outputnum);
    if (outputnum != 0){
        for (i=0; i<n; i++){
            if (used[i]== 1){
                printf ("%d ", i);
            }
        }
    }
    printf("\n");
}

int main(){
    int n, C;
    float p;
    while (scanf("%f %d", &p, &n) > 0){
        C = (int)p;
        thedp(C,n);
    }
    return 0;
}

