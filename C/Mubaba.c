#include <stdio.h>

long dp[3003][3003], maxlist[3003][3003];

int main(){
    int i, j;
    long n, summ = 0;
    scanf("%d", &n);
    long S[n+1];
    S[0] = 0;
    for (i = 0; i<n; i++){
        long p;
        scanf("%d", &p);
        summ += p;
        S[i+1] = summ;
    }
    for (i = 0; i<n; i++){
        dp[n-1][i] = 1;
    }

    for (i = n-1; i>=0; i--){
            printf("[[[%d]]]\n", i);
        for (j=i;j>=0; j--){
            int k = j-1;
                printf ("(%d, %d), (%d, %d)\n", S[j] - S[k] , S[i]-S[j], j, k);
            while (S[j] - S[k] < S[i]-S[j]){
            printf ("(%d, %d), (%d, %d)\n", S[j] - S[k] , S[i]-S[j], j, k);
                if (k<0){
                    break;
                    }
                k--;
                }

//                            printf ("%d  (%d.%d.%d)\n", maxlist[j][k+1],i ,j,k);

            if (maxlist [j][k+1] > 0){
                dp[i][j] = maxlist[j][k+1] + 1;

            }
//        printf ("%d\n",k);
        }

        for (j = i; j >= 0; j--){
            if (maxlist[i][j+1] >= dp[i][j]){
                maxlist[i][j] = maxlist[i][j+1];
            }
            else{
                maxlist[i][j] = dp[i][j];
            }
        }

    }

    int q, a;
        for (q = 0; q<n; q++){
            for (a=0; a<n; a++){
                printf ("%d ", dp[a][q]);
            }
        printf("\n");
        }

    int ans = -1;
    for (i = 0; i<n; i++){
        if (ans < dp[0][i]){
            ans = dp[0][i];
        }
    }

    printf ("%d", ans);
    return 0;
}
