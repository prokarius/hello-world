#include<stdio.h>
#include<stdlib.h>

#define MOD 1000000007

long long factorial[100005];
long long inv[100005];

int cmpfunc(const void *a, const void *b){
    return ( *(int*)b - *(int*)a);
}

// Calculates the inverse of a number % MOD
// Ripped off Geek for Geeks
long long inverse(long long a){
    long long y = 0, x = 1;
    long long m = MOD;
    while (a > 1){
        long long q = a/m;
        long long t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    x = (x+MOD)%MOD;
    return x;
}

// Returns nCr
long long nCr(int n, int r){
    long long temp = (factorial[n] * inv[r]) % MOD;
    return (temp * inv[n-r]) % MOD;
}

// Does all the setting up
void setting(int n){
    // Set up the factorial function first
    factorial[0] = inv[0] = 1;
    for (int i=1; i<=n; ++i){
        factorial[i] = (factorial[i-1] * i) % MOD;
        inv[i] = inverse(factorial[i]);
    }
}

int main(){
    int n, k;
    int input[100005];

    // Scan in input
    scanf ("%d %d", &n, &k);
    setting(n);
    for (int i=0; i<n; ++i){
        scanf("%d", &input[i]);
    }

    // Sort the numbers in descending order
    qsort(input, n, sizeof(int), cmpfunc);

    // For number at index i, multiply it by (i-1 choose K-1)
    long long out = 0;
    for (int i=0; i<=n-k; ++i){
        long long add = (input[i] * nCr(n-i-1, k-1)) % MOD;
        out = (out + add) % MOD;
    }

    printf("%lld\n", out % MOD);
    return 0;
}
