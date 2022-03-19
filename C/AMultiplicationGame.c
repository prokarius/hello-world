#include<stdio.h>

long long dp[64];

int main(){
    // Set up the DP array.
    // Stan will win if it's <= 9
    dp[0] = 9;

    // Ollie will win if it lands between 9 and 18
    dp[1] = dp[0] * 2;

    // But Stan will win again if its between 19 and 18*9 = 172
    // Because if it's < 172, he can multiply by 9.
    // Ollie cannot do anything.
    dp[2] = dp[1] * 9;

    // If it's 173 - 344 though, Ollie will win
    dp[3] = dp[2] * 2;

    // The pattern is therefore *9, *2 etc.
    for (int i = 0; i < 32; i += 2){
        dp[i+1] = dp[i] * 2;
        dp[i+2] = dp[i+1] * 9;
    }

    // Now scan in input
    long long n;
    while (scanf("%lld", &n) != EOF){
        int x = 0;
        while (dp[x] < n){
            x++;
        }

        if (x % 2 == 0){
            printf("Stan wins.\n");
        }
        else {
            printf("Ollie wins.\n");
        }
    }

    return 0;
}

