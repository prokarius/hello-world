#include<stdio.h>
#include<stdlib.h>

#define MIN(x, y) (x < y)?(x):(y)
#define MAX(x, y) (x > y)?(x):(y)

// Stores the input
// index = index, value = value of input at index
int input[100005];

// Store the hash value of a given number
// index = said given number, value = hashed value
long long hashed[100005];

// Stores the cumulative XOR of all hashed values.
// index = index, value = XOR(hashed[0], hashed[1], ... , hashed[index])
long long cumxor[100005];

// Stores the last occurance of a given number
// index = element, value[0] = last occurance, value[1] = 2nd last occurance
// If you want to refer to below, value[0] = i, value[1] = j
int lastOccurance[100005][2];

// Stores the upper bound of the range at a given index
// index = index in the input, value = upperbound of the range.
int upperBound[100005];

// This is a ghettoHash to store where the last seen value of this hash is
// The hash function is just modding 2**22.
// index = hashed value, value[0] = unhashed value, value[1] = index of lastSeen
long long ghettoHash[1 << 22][2];

// Stores the value of the next occurance of cumxor at the given index.
// If there is no such index, next stores -1;
// index = index, value = location of next occurance.
int next[100005];

// Stores if we have visited the cell when we are doing sliding window.
// index = index, value = true if we have processed this cell before.
int visited[100005];

// Returns the last seen index of the cumxor at the current index
// Returns -1 if the index is not anywhere.
int hash(int index){
    long long hashedValue = cumxor[index] % (1<<22);
    while (ghettoHash[hashedValue][0] != 0){
        // If we have seen the value before, then save the current value
        if (ghettoHash[hashedValue][0] == cumxor[index]){
            int out = (int)ghettoHash[hashedValue][1];
            ghettoHash[hashedValue][1] = index;
            return out;
        }
        // If not, linear probing is OK too.
        else {
            hashedValue++;
        }
    }

    // Push the new value into the hashTable
    ghettoHash[hashedValue][0] = cumxor[index];
    ghettoHash[hashedValue][1] = index;
    return -1;
}


// Lingod is some next level genius.
// This is his solution.
int main(){
    // Part A: exactly PAIRED. (Ensuring each element appears even number of times)
    // Step 0: Scan in input (as always)
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d", &input[i]);
    }

    // Step 1: Initialise the hash.
    // Lets just use rand() because we can.
    // The idea is that when we see 2 occurances of the same number,
    // the xors are supposed to cancel out.
    for (int i = 0; i <= 100000; ++i){
        hashed[i] = ((long long)rand() << 32) + rand();
    }

    // Step 2: We will calculate the cumulative xor of the hashes
    // If we see 2 of the same values in the cumxor array, we can be (almost very)
    // sure that every element that appears in the arrays appear an even
    // number of times.
    cumxor[0] = 1;
    for (int i = 0; i < n; ++i){
        cumxor[i+1] = cumxor[i] ^ hashed[input[i]];
    }

    // Part B: EXACTLY paired (Ensure each element appears twice exactly)
    // Step 3: This part, we want to find all possible (i, k) such that
    // a) A[i] == A[k]
    // b) if A[j] == A[i] and i < j < k => j is unique
    // Essentially, we need to find all i and k such that there exists only one copy
    // of j within the range.

    // Then a range (x, y) is not allowed if x <= i, and y >= k, for all ijk triples.
    // Note that this is enough to ensure that each element within the range does
    // not appear more than twice.

    // Proof forward direction:
    // It is obvious that if x <= i, and y >= k, then there is A[i] == A[j] == A[k]
    // that appears 3 times within the range (x, y)

    // There was supposed to be a Proof of backward direction, but I don't think
    // I can come up with it right now because of tired. Hence...
    // The proof is left as an exercise to the reader :D

    // To even begin, we need to reset the lastOccurance array:
    for (int i = 0; i <= 100000; ++i){
        lastOccurance[i][0] = n;
        lastOccurance[i][1] = n;
    }

    // And also reset the upperBound array
    // The upper limit of the upperbound can be as large as n. We initialize it as such
    for (int i = 0; i <= n; ++i){
        upperBound[i] = n+1;
    }

    // Then, as we loop through the input, we keep track of the upper bound.
    for (int i = 0; i < n; ++i){
        // Each time we find a value, we scoot i j and k to the left.
        // Also, we update the upperBound to which ever is smaller:
        // itself, or the current value
        upperBound[lastOccurance[input[i]][0]] =
            MIN(upperBound[lastOccurance[input[i]][0]], i);

        // Don't forget to update the lastOccurance values
        lastOccurance[input[i]][0] = lastOccurance[input[i]][1];
        lastOccurance[input[i]][1] = i;
    }

    // Step 4: Now that we have all these ranges, can we find for each lower bound,
    // what is the largest upper bound. This will give us a load of ranges which are
    // not allowed.

    // However, to actually formalize it, we need to do some DP to find out the
    // ACTUAL upperBound.
    // Imagine an n*n board, and drawing rectangles where you are not allowed to
    // have certain values (a la this problem)
    // Then to find the actual upperbound, you just need to do the following:
    for (int i = n-2; i >= 0 ; --i){
        upperBound[i] = MIN(upperBound[i], upperBound[i+1]);
    }

    // Step 5: Awesome, we have a list of all the bad ranges, and all the
    // We are gonna do some form of bucket sort in order to find which hashes are
    // possible to be processed.
    for (int i = n; i >= 0; --i){
        next[i] = hash(i);
    }

    // Step 6: Now that we have a list of possible cumxors, we will use sliding
    // window to make it work. This will give us the largest possible window.
    int best = 0;

    // For each of the possible indices, we are going to check if it is part of the
    // longest subsequence. This will be done by checking if we visited it before.
    for (int i = 0; i < n; ++i){
        if (visited[i]) continue;
        visited[i] = 1;
        if (next[i] == -1) continue;
        int curr = i;
        int nextptr = next[i];

        // This is the sliding window bit.
        // Scoot curr up by 1 whenever nextptr is greater than the allowed upperBound
        while (curr != -1 && nextptr != -1){
            while (nextptr <= upperBound[curr]){
                if (nextptr == -1) break;
                visited[nextptr] = 1;
                best = MAX(best, nextptr - curr);
                nextptr = next[nextptr];
            }
            curr = next[curr];
        }
    }

    // Finally print that shit.
    printf("%d\n", best);

    return 0;
}
