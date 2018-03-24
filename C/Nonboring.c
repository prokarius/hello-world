#include<stdio.h>

#define MOD 2800001

int input[200005];
int next[200005], prev[200005];
int hashtable[2800002][2]; // Prime to use is 2800001
long long ghettoHash[200005]; // Stores the hashed positions
int ghettoHashHead = 1;

// This is the reset function
void setting(int n){
    int i;
    // Reset the next and prev arrays
    for (i=0; i<=n; ++i){
        prev[i] = -1;
        next[i] = 262144;
    }

    // Reset the ghettoHash and hashtable
    while (ghettoHashHead != -1){
        hashtable[ghettoHash[ghettoHashHead]][0] = 0;
        hashtable[ghettoHash[ghettoHashHead]][1] = 0;
        ghettoHash[ghettoHashHead] = 0;
        ghettoHashHead--;
    }
    ghettoHashHead++;
}

long long getHash(int num){
    // Makes or updates a hash and returns the value
    // calculate (num**31)%MOD
    int i;
    long long n = num, k = 1;
    for (i=0; i<5; ++i){
        k = (k*n)%MOD;
        n = (n*n)%MOD;
    }

    // Try to insert num at the hash table in position n.
    // Check to see if another number has been hashed there already
    while ((hashtable[k][0] != 0) && (hashtable[k][0] != num)){
        // Oh no, someone is there!
        k = (k+1)%MOD;
    }

    // Finally, we have an open space!
    // Plop.
    hashtable[k][0] = num;

    // Add the entry to the ghettoHash
    ghettoHash[ghettoHashHead++] = k;
    return k;
}

int binsearch (int left, int right){
    if (left >= right) return 0;
    int i;
    for (i=0; i<=(right-left+1)/2; ++i){
        // Search from both ends.
        // If the previous occurance of the element being considered is before
        // the left margin, and the next occurance of the element is after the
        // right margin, we can conclude the element is unique in the range.
        // So divide and conquer!
        if (prev[left+i] < left && next[left+i] > right){
            return binsearch(left, left+i-1) | binsearch(left+i+1, right);
        }

        if (prev[right-i] < left && next[right-i] > right){
            return binsearch(left, right-i-1) | binsearch(right-i+1, right);
        }
    }
    // Note that if any subsequence has no unique elements = immediately boring.
    // Hence we return a 1 and use logical or to find the solutions
    return 1;
}

int main(){
    int d = 0;
    int T, n=0, ph, i;
    scanf ("%d", &T);
    while (T--){
        // Scan in the input, note that we use 1 based indexing
        // This is so that we can take advantage of the initialised 0 arrays.
        scanf("%d", &n);
        setting(n);
        for (int i=1; i<=n; ++i){
            scanf("%d", &ph);
            input[i] = ph+1;
        }

        // Set the next and prev respectively
        for (i=1; i<=n; ++i){
            long long hashed = getHash(input[i]);
            if (hashtable[hashed][1]){
                // We have seen this item before:
                // Set the previous guy to what was hashed
                // Set the next of the previous guy to curr
                prev[i] = hashtable[hashed][1];

                next[prev[i]] = i;
            }

            // Set the hashtable element to the new one no matter
            hashtable[hashed][1] = i;
        }

        // Now, we just do binary search
        // Note that if there is a unique element in the range, any subrange
        // that spans the element would be non-boring.
        // So we can use divide and conquer strategy. O(nlogn)
        if (binsearch(1, n) == 0) printf ("non-");
        printf ("boring\n");
    }

    return 0;
}
