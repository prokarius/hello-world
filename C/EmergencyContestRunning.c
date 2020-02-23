#include<stdio.h>
#define MIN(x, y) (x<y)?(x):(y)

int main(){
    // Scan in input
    long long n, k;

    scanf("%lld %lld", &n, &k);

    // 2 ways Lokpass can go home.
    // Case 1. Walk up, step by step
    long long case1 = n-1;

    // Case 2. Walk up to k, and take a hop to get to n - (n%k).
    // Then n%k more steps to get home.
    long long case2 = k + 1 + ((n-1)%k);

    printf("%lld\n", MIN(case1, case2));

    return 0;
}

