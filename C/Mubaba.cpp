#include <stdio.h>


int n;
int A[5], D[5][5], E[5][5];
long long S[5];

int main()
{
    scanf("%d", &n);
    for (int i=1;i<=n;i++) scanf("%d", A+i), S[i] = S[i-1] + A[i];
    for (int i=1;i<=n;i++){
        D[1][i] = 1;
        for (int j=i,k=i-1;j>1;j--){
            if (k >= j) k = j-1;
            while (k > 0 && S[j-1] - S[k-1] <= S[i] - S[j-1]){
                k--;
            }
            if (E[k+1][j-1]) D[j][i] = E[k+1][j-1] + 1;
        }
        for (int j=i;j;j--){
            if (D[j][i] > E[j+1][i]){
                E[j][i] = D[j][i];
            }
            else{
                E[j][i] = E[j+1][i];
            }
        }

    }
    int ans = 0;
    for (int i=1;i<=n;i++){
        if (D[i][n] > ans){
            ans = D[i][n];
        }
    }
    printf("%d\n", ans);
}
