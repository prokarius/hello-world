#include<stdio.h>
#define MOD 2800001
#define MIN(x ,y) (x<y)?(x):(y);

// We will need a hash table for this question. Set up the ghettoHash!

// Our hash stores these values
// [0] original value
// [1] mapped value
int ghettoHashMap[2800001][2];

// Puts the value into the table.
// Returns MOD if the value has not be pushed into the table before
// Else returns the distance to the previous memeber
int getHash(int value, int location){
    int hashed = value % MOD;
    // Check to see if hash table is filled in that slot
    while(ghettoHashMap[hashed][0] != 0){
        if (ghettoHashMap[hashed][0] != value){
            hashed = (hashed + 1) % MOD;
        }
        else {
            int old = ghettoHashMap[hashed][1];
            ghettoHashMap[hashed][1] = location;
            return location - old;
        }
    }
    ghettoHashMap[hashed][0] = value;
    ghettoHashMap[hashed][1] = location;
    return MOD;
}

int main(){
    // Scan in inout
    int n;
    scanf ("%d", &n);

    int best = MOD;

    // For each guy
    for (int currpos = 1; currpos <= n; ++currpos){
        int next;
        scanf("%d", &next);

        // Shit, if next is 0, the hash table will die!
        next++;

        // Find out how awkward this guy is (distance to the previous guy)
        int awkward = getHash(next, currpos);

        // Get the maximum!
        best = MIN(best, awkward);
    }

    // If the best is the huge number, then everyone doesnt speak the same language
    printf("%d\n", (best == MOD)?n:best);

    return 0;
}
