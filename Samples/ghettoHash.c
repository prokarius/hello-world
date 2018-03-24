#define MOD = 2800001

int hashtable[2800002][2];
int ghettoHash[200000];
int ghettoHashHead = 0;

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


