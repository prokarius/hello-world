#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void solve(){
    char string[20005];
    scanf("%s", string);

    int len = strlen(string);

    // Maximum N is 10, since 10 * (2**10) = 10k and 11 * (2**11) = 22k > 20k
    for (int n = 10; n >= 0; --n){
        // Prune if we have too many characters
        int charsNeeded = n * (1 << n);
        if (charsNeeded > len) continue;

        // Find the smallest start
        int p = 0;
        while (p + charsNeeded <= len){
            // Reset the DP array
            int* dp = (int*) calloc((1<<n), sizeof(int));
            int passed = 1;

            // For each of the words, see if it fits in dp
            for (int num = 0; num < (1<<n); ++num){
                int startingChar = p + num*n;
                int mask = 0;

                // Generate the bitmask
                for (int i = 0; i < n; ++i){
                    if (string[startingChar + i] == 'H'){
                        mask ^= (1 << i);
                    }
                }

                // Have we seen this bitmask before?
                if (dp[mask]){
                    passed = 0;
                    break;
                }

                dp[mask] = 1;
            }

            // Oh yay we found it!
            if (passed){
                printf("%d %d\n", n, p);
                return;
            }

            // Bummer we failed to find the substring... Lets increase!
            ++p;
        }
    }
}

int main(){
    // Scan in input
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}

