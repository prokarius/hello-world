#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

char string[205];
int length=0, array[205][205]={0};

int dp (int start, int end){
    // If the answer has been memoized, return it.
    if (start == end) return 1;    
    if (array [start][end] != 0) return array[start][end];
    int ans=999, i, j;

    // The answer can be a concat of two strings
    for (i=start; i<end; ++i) ans = MIN(ans, dp(start, i) + dp(i+1, end));

    // Or the answer could be factored
    int len = end - start + 1;
    for (i=1; i<=len/2; ++i){
        if (len%i == 0){
            for (j = 0; j<len; ++j){
                if (string[start+j] != string[start+(j%i)]) break;
            }
            if (j == len) ans = MIN(ans, dp(start, start+i-1));
        }
    }
    array[start][end] = ans;
    return ans;
}

int main (){
    int ans, i;
    scanf ("%s", string);
    while (string[length] != '\0') ++length;
    printf ("%d\n", dp(0, length-1));
    return 0;
}

/*

// Failed Iterative DP solution

#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

char string[205];

int main(){
    int ans, i, j, k, l, length=0, dp[204][204] = {999};
    scanf("%s", string);
    while (string[length] != '\0') ++length;
    for (i=0; i<length; ++i){
        for (j=0; j<length; ++j){
            dp[i][j] = 9;
        }
    }
    // DP[i][j] stores the smallest factoring of the string from index i to j
    for (i=0; i<length; ++i) dp[i][i] = 1;
    for (i=1; i<length; ++i){
        for (j=i-1; j>=0; --j){
            // The smallest factoring could just be a concat of two things:
            ans = 999;
            for (k=j; k<i; ++k){
                printf("$ (%d, %d, %d) , (%d,%d, %d) $ \n", j,k,dp[j][k], k+1,i,dp[k+1][i]);
                ans = MIN (ans, dp[j][k]+dp[k+1][i]);
            }
            int strle = j-i+1;

            // Or it could itself be factored into something smaller:
            for (k=1; k<=strle/2; ++k){
                if (strle % k == 0){
                    for (l=0; l<strle; ++l){
                        if (string[i+l%k] != string[i+l]) break;
                    if (l == strle) ans = MIN(ans, dp[i][i+strle/k]);
                    }
                }
            }

            // Memoize this
            dp[i][j] = ans;
            printf("%d %d %d\n", i, j, ans);
        }
    }

    for (i=0; i< length; ++i){
        for (j=0; j<length; ++j){
            printf ("%d ", dp[i][j]);
        }
        printf("\n");
    }


    printf ("%d", dp[0][length-1]);
    return 0;

}

*/
