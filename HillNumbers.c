#include<stdio.h>

// dp[x][y][a][b] stores the number of hill numbers that have the following:
// x = number of digits in the current number
// y = current digit
// a = whether the number is rising
// b = whether the number may be potentially higher than N
long long dp[18][10][2][2];

int main(){
    // Scan in input
    int n;
    scanf("%lld", &n);

    if (!isHillNumber(n)){
        printf("-1\n");
        return 0;
    }

    // Run the DP that has
    rundp(n);
    

    return 0;
}
