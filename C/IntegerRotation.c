#include<stdio.h>
#include<stdlib.h>

void solve(){
    // Scan in input
    int lo, hi;
    scanf("%d %d", &lo, &hi);

    int out = 0;

    // We will just simulate it I guess...
    // 100 * 1M = 100M... It might be fast enough... I think...?
    for (int curr = lo; curr <= hi; ++curr){
        int new = curr;

        // Find the position of the last digit
        curr /= 10;
        int lastDigit = 1;

        while (curr){
            lastDigit *= 10;
            curr /= 10;
        }

        // Regenerate curr
        curr = new;

        // Rotate the integer
        for (int i = 0; i < 7; ++i){
            new = (new % 10) * lastDigit + (new / 10);

            // Are we back to where we started?
            if (new == curr) break;

            // Is the new integer within bounds?
            if (new < curr || new > hi) continue;

            out++;
        }
    }

    // Print that shit
    printf("%d\n", out);
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    
    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}

