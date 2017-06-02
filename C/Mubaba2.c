long long dp[3006][3006], maxlist[3006][3006];
long long S[3006];

int main(){
    int i, j;
    long n, summ = 0;
    scanf("%d", &n);
    S[0] = 0;
    for (i = 0; i<n; i++){
        long long p;
        scanf("%d", &p);
        summ += p;
        S[i+1] = summ;
    }

    for (i = 0; i < n; i++){
        dp [i][n-1] = 1;
    }
    maxlist[n-1][n-1] = 1;

    for (i=n-2;i>=0; i--){
        for (j=n-2; j>= i; j--){
            int k = j+1;
            while ((k<n) && ((S[j+1] - S[i]) > (S[k+1] - S[j+1]))){
                k += 1;
            }
            if (k>=n) {
                dp[i][j] = 1;
            }
            else {
                if (maxlist [j+1][k] > dp [i][j]){
                    dp[i][j] = maxlist [j+1][k]+1;
                }
            }
        }
        for (j=n-1; j>=i; j--){
            if (maxlist[i][j+1]>dp[i][j]){
                maxlist[i][j] = maxlist[i][j+1];
            }
            else {
                maxlist [i][j] = dp[i][j];
            }
        }
    }

    int ans = -1;
    for (i = 0; i<n; i++){
        if (maxlist[0][i] > ans){
            ans = maxlist[0][i];
        }
    }
    printf ("%d", ans);
    return 0;
}
