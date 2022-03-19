#include<stdio.h>
#include<math.h>

long long dp[10][40];

// Initialize the dp array
void init(){
    for (int i = 1; i < 10; ++i){ 
        dp[i][0] = 1;
        dp[i][1] = i;
        for (int j = 2; j < 40; ++j){
            dp[i][j] = dp[i][j-1] * i;
            if (dp[i][j] > (1LL << 40)) break;
        }
    }   
}

// The trick is to take mod 10!
int recurse(long long a, long long b, int numDigit){
    // Base case: We reached 0 and 0;
    if (a == 0 && b == 0) return 1;
    int digit = a % 10;
    for (int i = 0; i < 40; ++i){
        // If we reached too big a number, break
        if (b < dp[digit][i]) break;

        if ((b - dp[digit][i]) % 10 == 0){
            if (recurse(a/10, (b-dp[digit][i])/10, numDigit + 1)){
                printf("%d ", i);
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    // Scan in input
    long long a, b;
    scanf("%lld %lld", &a, &b);
    init();
    recurse(a, b, 0);
    printf("\n");

    return 0;
}

