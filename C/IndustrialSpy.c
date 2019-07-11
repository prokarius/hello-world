#include<stdio.h>

int dp[10000000];

int ghettoHashStore[10000000];
int ghettoHash[14000];
int ghettoHashHead;

int numDigits;
int digits[8];
int visited[8];

// Push the point into the ghettoHash
// But doesn't do so if it already exists.
void push(int x){
    if (ghettoHashStore[x]) return;
    ghettoHashStore[x] = 1;
    ghettoHash[ghettoHashHead] = x;
    ++ghettoHashHead;
}

// Deletes all the points from the ghettoHash
void reset(){
    for (int i = 0; i < ghettoHashHead; ++i){
        ghettoHashStore[ghettoHash[i]] = 0;
    }
    ghettoHashHead = 0;
}

// Trial Division maybe is fast enough...?
int testPrime(int prime){
    if (dp[prime] != -1){
        return dp[prime];
    }

    for (int i = 2; i*i <= prime; ++i){
        if (prime % i == 0){
            dp[prime] = 0;
            return 0;
        }
    }
    dp[prime] = 1;
    return 1;
} 

// Recursively gets all the permutations of the given number
void recurse(int curr, int out){
    if (curr == numDigits){
        push(out);
        return;
    }

    // Remember to push the current number in too.
    push(out);

    for (int i = 0; i < numDigits; ++i){
        if (visited[i]) continue;
        visited[i] = 1;
        recurse(curr + 1, out * 10 + digits[i]);
        visited[i] = 0;
    }
}

void solve(){
    reset();

    // Scan in input
    char input[8];
    scanf("%s", input);

    // Get the number of digits
    numDigits = 0;
    while (input[numDigits] != 0){
        digits[numDigits] = input[numDigits] - '0';
        numDigits++;
    }

    // Recursively get all the numbers that can be formed
    recurse(0, 0);

    // Then test all the numbers
    int out = 0;
    for (int i = 0; i < ghettoHashHead; ++i){
        out += testPrime(ghettoHash[i]);
    }

    // Print it
    printf("%d\n", out);
}

int main(){
    int n;
    scanf("%d", &n);

    // Reset the primes dp
    for (int i = 0; i < 10000000; ++i){
        dp[i] = -1;
    }

    dp[0] = 0;
    dp[1] = 0;
    dp[2] = 1;

    for (int i = 0; i < n; ++i){
        solve();
    }
}
