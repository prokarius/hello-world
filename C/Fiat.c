#include<stdio.h>

#define MOD 1000000007

// Ripped off Geek for geeks
long long modInverse(long long a, long long m)
{
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
      return 0;

    while (a > 1)
    {
        // q is quotient
        int q = a / m;
        int t = m;

        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
       x += m0;

    return x;
}

long long factorial2(int start, int end){
    long long out = 1;
    for (int i = start; i <= end; ++i){
        out = (out * i) % MOD;
    }
    return out;
}

long long factorial(int end){
    return factorial2(1, end);
}

// Literally finding the nth catalan number mod MOD
int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    printf("%lld\n", factorial2(n+2, 2*n) * modInverse(factorial(n), MOD) % MOD);

    return 0;
}
