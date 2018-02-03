#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)
#define MAX(x,y) (x>y)?(x):(y)

int dp[1<<20][7];

int main(){
    int N, ph, i=-1, j, k, z, array[21], best, num=-1, carry=0;

    // Scan in the input. Now, we don't really care about test that last 1 day.
    // We can just throw it somewhere by itself. So we just put them aside.
    scanf("%d", &N);
    while (++i<N){
        scanf ("%d", &ph);
        if (ph == 1) ++carry;
        else array[++num] = ph;
    }
    ++num;

    // Reset our DP array.
    for (i=0; i<(1<<num); ++i){
        for (j=0; j<7; ++j){
            dp[i][j] = 999;
        }
    }
    dp[0][0] = 0;

    // The first dimension is the bitmask of which allergen have been tested.
    // The second dimension is the number of days the allergen is left with.
    // The stored value is the total number of days the scheme will last
    // Complexity of this solution: O(2**k*D) states, O(D) transition.
    // In fact, it makes no sense to do top down DP. Maybe. No idea...

    // For all possible states
    for (i=1; i<(1<<num); ++i){
        // k represents the allergen number we are to be adding.
        for (k=0; k<num; ++k){
            // The new state is the lower of itself and the old state.
            // But only if the old state has the current allergen
            // I.e. if the current state _has_ the bit turned on.
            if (1<<k & i){
                // If we can add the new allergy to this, then we see if by adding
                // the allergy, it'll make it faster.
                // We need to check for all of the days of left.
                for (j=0; j<7; ++j){
                    z = MAX(array[k]-j-1, 0);
                    dp[i][z] = MIN(dp[i-(1<<k)][j] + z + 1, dp[i][z]);
                }
            }
        }
    }
    // Just to summarise all the monocharacteristic variable names:
    // i = bitmask of which allergens have been added
    // j = iterator for the previous excess duration of allergens
    // k = new allergen to be added
    // z = excess duration of the new allergen to be added

    // Now, at the end, we need to find out which is the smallest of all the
    // allergen testing schemes. So we just have to choose the smallest of all
    // dp[i][j], i = (1<<num)-1, j = 0 to 7.
    best = 999;
    for (i=0; i<7; ++i) best = MIN(best, dp[(1<<num)-1][i]);

    // Don't forget to add back the num
    printf ("%d\n", best + carry);
    return 0;
}
