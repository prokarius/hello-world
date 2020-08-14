#include<stdio.h>
#include<stdlib.h>

// Global because idk why my fenwick tree is global...
int n;

// Fenwick tree methods
int fenwickTree[1<<20];

int LSOne(int x){
    return x&(-x);
}

void update(int location, int value){
    for (int i = location; i < n+2; i += LSOne(i)){
        fenwickTree[i] += value;
    }
}

long long rsq(int end){
    long long sum = 0;
    for (int i = end; i > 0; i -= LSOne(i)){
        sum += fenwickTree[i];
    }
    return sum;
}

long long input[1<<20];
long long prefixsum[1<<20];
long long sorted[1<<20];

int cmpfunc(const void* a, const void* b){
    long long first = *(long long*)a;
    long long second = *(long long*)b;
    return (first > second) - (second > first);
}

// Get the "hashed" position of the current value.
// This will be used for our fenwick tree
int getHash(long long x){
    int lo = 0;
    int hi = n;

    while (lo < hi){
        int mid = (hi + lo) / 2;

        if (sorted[mid] < x){
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }

    return hi + 1;
}

int main(){
    // Scan in input
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%lld", &input[i]);
    }

    long long p;
    scanf("%lld", &p);

    // Build my prefix sum!
    // Subtract p from the sum because we only care about the average.
    for (int i = 0; i < n; ++i){
        prefixsum[i+1] = prefixsum[i] + input[i] - p;
        sorted[i+1] = prefixsum[i+1];
    }

    // Sort all the prefix sums so we know the relative orders of each prefix sum
    // This will allow them to be queried in the Fenwick tree.
    qsort(sorted, n+1, sizeof(long long), cmpfunc);

    // Since we have subtracted P from each value, we just want to find out how many
    // prefixsum[curr] - prefixsum[prev] > 0.

    long long out = 0;
    update(getHash(0), 1);

    // For each position, get the "hash" value, and see how many is below
    // Do this by querying the fenwick tree
    for (int i = 1; i <= n; ++i){
        int hash = getHash(prefixsum[i]);
        out += rsq(hash);
        update(hash, 1);
    }

    // Finally, print the number!
    printf("%lld\n", out);
    return 0;
}

