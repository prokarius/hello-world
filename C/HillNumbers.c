#include<stdio.h>

// dp[x][y][a][b] stores the number of hill numbers that have the following:
// x = number of digits in the current number
// y = current digit
// a = whether the number is rising
// b = whether the number may be potentially higher than N
long long dp[20][10][2][2];
int digits[20];
int start = 19;

// Returns 1 if the number is a hill number
int isHillNumber(){
    int ascending = 1;

    for (int i = start+1; i < 20; ++i){

        // If the digits are starting to descend, set false
        if (ascending && digits[i-1] > digits[i]){
            ascending = 0;
            continue;
        }

        // If the digits are descending, give up
        if (!ascending && digits[i-1] < digits[i]){
            return 0;
        }
    }

    // If we are here, we passed the check!
    return 1;
}

long long rundp(int curr, int prev, int rising, int max){
    // Base of the recursion, if we are at the last digit, give up
    if (curr == 20){
        return 1;
    }

    // If we have memoized, return it
    if (dp[curr][prev][rising][max] != -1){
        return dp[curr][prev][rising][max];
    }

    long long count = 0;
    int upper;

    // If we are constrained, then limit the upper digit
    if (max){
        upper = digits[curr];
    }
    else {
        upper = 9;
    }

    // Go through all possible digits from 0 to upper
    for (int i = 0; i <= upper; ++i){
        // If we are rising, then keep adding the count to the total
        // Check to ensure we have not started to fall

        // Remember to constrain if we are currently constrained, and the digit is
        // the same as the given input number's digit at the current position
        if (rising){
            count += rundp(curr+1, i, i >= prev, max && i == digits[curr]);
        }

        else {
            count += rundp(curr+1, i, 0, max && i == upper);
            if (i == prev){
                break;
            }
        }
    }

    // Memoize the result
    dp[curr][prev][rising][max] = count;
    return count;
}

int main(){
    // Scan in input
    long long n;
    scanf("%lld", &n);

    // Paranoia: If the input is 1 or 2 digits, then it is a hill number. Print it.
    if (n < 100){
        printf("%lld\n", n);
        return 0;
    }

    // Make the digits
    while (n){
        digits[start] = n%10;
        n /= 10;
        start--;
    }

    if (!isHillNumber()){
        printf("-1\n");
        return 0;
    }

    // Reset the DP array
    // Don't even bother with the 2 inner for loops. Slow only
    for (int i = 0; i < 20; ++i){
        for (int j = 0; j < 10; ++j){
            dp[i][j][0][0] = -1;
            dp[i][j][1][0] = -1;
            dp[i][j][1][1] = -1;
            dp[i][j][0][1] = -1;
        }
    }

    // Run the DP that gives the number of states. Also print it out
    // Note that this counts 0 as well. Remove it because it is not positive.
    printf("%lld\n", rundp(++start, 0, 1, 1) - 1);
    return 0;
}
