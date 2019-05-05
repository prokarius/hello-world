#include<stdio.h>
#include<stdlib.h>

#define MIN(x, y) ((x < y)?(x):(y))

int numEstates;
long long prices[55];
long long suffixSum[55];
long long output;

int cmpfunc(const void *a, const void* b){
    return (*(long long*)a > *(long long*)b) ? -1 : 1;
}

long long ABS(long long x){
    if (x < 0){
        return -x;
    }
    return x;
}

// Function takes
void dp(int current, long long jackEstate, long long jillEstate, long long soldEstate){
    // If we have sold more than the current best, give up
    if (soldEstate >= output){
        return;
    }

    // Small optimization: If the difference between the two is more than whatever
    // estate is left, just give up
    if (ABS(jackEstate - jillEstate) > suffixSum[current]){
        return;
    }

    // If Jack and Jill's estate is the same value, see if selling everything is best.
    if (jackEstate == jillEstate){
        output = MIN(output, soldEstate + suffixSum[current]);
    }

    // If we have exceeded n, give up.
    // This should be done after checking if jack and jill's estates are the same.
    if (current >= numEstates){
        return;
    }

    // Give both jack or jill the estate
    dp(current + 1, jackEstate + prices[current], jillEstate, soldEstate);

    // Small optimization: always give jack the first estate between them.
    // In other words, we will give jill some estate if Jack already owns something.
    if (jackEstate) {
        dp(current + 1, jackEstate, jillEstate + prices[current], soldEstate);
    }

    // Then try to sell the estate
    dp (current + 1, jackEstate, jillEstate, soldEstate + prices[current]);
}

int main(){
    // Scan in input
    scanf("%d", &numEstates);

    while (numEstates){
        // Reset the output
        output = 1L<<62;

        // Scan in the estate prices
        for (int i = 0; i < numEstates; ++i){
            scanf("%lld", &prices[i]);
        }

        // Sort the estate prices
        qsort(prices, numEstates, sizeof(long long), cmpfunc);

        // We also need to do a suffix sum, assuming we managed to split the first
        // k houses between jack and jill. Then we can find out the prices we get
        // from selling the remaining houses quickly!
        suffixSum[numEstates] = 0;
        for (int i = numEstates-1; i >= 0; --i){
            suffixSum[i] = suffixSum[i+1] + prices[i];
        }

        // We want to run the dp. This function will modify output, which we print.
        dp(0, 0, 0, 0);

        // Finally, print the output
        printf("%lld\n", output);

        scanf("%d", &numEstates);
    }

    return 0;
}
