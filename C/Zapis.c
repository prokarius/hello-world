#include<stdio.h>

char openBrackets[] = {'(', '[', '{'};
char closeBrackets[] = {')', ']', '}'};

char inputstr[205];
int flag = 0;
long long dp[256][256];

// We will use divide and conquer for this question
// Note that the closing bracket for the first opening 
// bracket needs to be in an even index.
// This uses top down memoization.
long long divide(int low, int high){
    // Base case, when we have reached the end, low > high
    // In this case, we simply return 1, to signify that it is 1 possible result.
    if (low >= high) return 1;

    // Else we try to see if we have memoized the result before:
    if (dp[low][high] >= 0) return dp[low][high];

    long long out = 0;

    // Note that the closing brackets can only be in even slots along
    // the input string. (Because if it is odd, there will
    // definitely be an unpaired open bracket)
    // Loop through all possible even positions and all possible bracket types
    for (int i = low + 1; i <= high; i += 2){
        for (int j = 0; j < 3; ++j){
            // If the first character of the sequence is the same bracket
            // type or is a question mark
            // And the closing bracket is of the same type or the
            // question mark
            if ((inputstr[low] == openBrackets[j] || inputstr[low] == '?') &&
                (inputstr[i] == closeBrackets[j] || inputstr[i] == '?')){
                // Then we know this is a chance for recursion.
                out = out + divide(low + 1, i - 1) * divide(i + 1, high);

                // Set the overflow flag if the number overflows.
                if (out > 100000){
                    flag = 1;
                    out = out % 100000;
                }
            }
        }
    }

    // Memoize the result
    dp[low][high] = out;
    return out;
}

int main(){
    int n;

    // Scan in input
    scanf ("%d ", &n);
    for (int i = 0; i < n; ++i){
        scanf("%c", &inputstr[i]);
    }

    // Initialise the dp array!!
    // It can be the case that there is no way to match brackets,
    // hence we need to set the initial value if the dp array to be -1 first!
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            dp[i][j] = -1;
        }
    }

    // Then we just need to call the recusrive algo!
    long long out = divide(0, n-1);

    // Print the output, and format it if flag is on.
    if (flag) printf("%05lld\n", out);
    else printf("%lld\n", out);
}
