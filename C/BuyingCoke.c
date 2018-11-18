#include<stdio.h>

#define MIN(x,y) (x<y)?(x):(y)

// There are 5 ways to by a coke:
// A) 1 x 10 -> getting 2 pennies back
// B) 2 x 5 -> getting 2 pennies back
// C) 1 x 10 + 3 x 1 -> get a 5 back
// D) 1 x 5 + 3 x 1
// E) 8 x 1
// We know that we need to expand all the 10s to be optimal
void run(int numCokes, int n1, int n5, int n10){
    // First check if numCokes <= n10s. Then just use A all the way
    if (numCokes <= n10){
        printf("%d\n", numCokes);
        return;
    }

    int out = 99999;
    // i will be the number of 10s that goes into A
    for (int i = 0; i <= n10; ++i){
        int newn10 = n10 - i;

        // new10 is therefore the number of C equations that will happen.
        int newn1 = n1 + 2*i - 3*newn10;
        int newn5 = n5 + newn10;

        // Update the number of coins we used
        // ix10s and newn10 (1x10 + 3x1)s
        int currCount = i + (newn10 * 4);

        // Brute force the number of B equations
        for (int j = 0; j <= numCokes - n10 ; ++j){
            // See if the number of pennies is positive;
            int newern1 = newn1 + 2*j;
            if (newern1 < 0) continue;

            // See if we have enough 5s, if not, we never will.
            int newern5 = newn5 - 2*j;
            if (newern5 < 0) break;

            // Use the remaining n5s to pay for the coke
            // But if we run out of pennies, we know we need to use more doubles
            int numCokesLeft = numCokes - (n10 + j);
            int newCount = currCount + 2*j;
            if (newern5 >= numCokesLeft){
                int newestn1 = newern1 - 3*numCokesLeft;
                if (newestn1 >= 0){
                    int newestCount = newCount + 4 * numCokesLeft;
                    out = MIN(out, newestCount);
                }
                continue;
            }

            // Pay using all the 5s and 1s, then dump all the 1s
            int newestCount = newCount + 4 * newern5;
            int newestn1 = newern1 - 3*newern5;
            int lastCokeLeft = numCokesLeft - newern5;
            if (newestn1 >= lastCokeLeft * 8){
                newestCount += 8*lastCokeLeft;
                out = MIN(out, newestCount);
            }
        }
    }

    // Print that shit
    printf("%d\n", out);
}

int main(){
    int n, C, n10, n5, n1;
    scanf("%d", &n);
    while (n--){
        scanf("%d %d %d %d", &C, &n1, &n5, &n10);
        run(C, n1, n5, n10);
    }
    return 0;
}
