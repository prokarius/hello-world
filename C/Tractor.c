#include<stdio.h>

void run(){
    // Scan in input
    int A, B;
    scanf("%d %d", &A, &B);

    // This question is essentially:
    // Find the number of x, y that fulfills the 4 conditions
    // x <= A; y <= B; x & y = 0; x | y = (1<<n)-1, for some n

    // Solution is to start from number 4:
    // Enumerate all n, and find the number of (x, y) that matches
    // This is simple, we just need to find the range of values of x such that
    // x <= A, and n - x <= B (re written n - B >= x).

    // If A > B, then we can always
    // Hence we swap them if A < B
    if (A < B){
        int temp = B;
        B = A;
        A = temp;
    }

    // Loop through all possible n
    long long ans = 0;
    for (int i = 0; i < 32; ++i){
        int n = (1<<i) - 1;

        // Case 1: If both A and B are more than 1<<i
        // Then no matter what x you pick, it will be valid
        if (A >= n && B >= n){
            ans += n + 1;
            continue;
        }

        // Case 2: If A >= 1<<i, but B < 1<<i.
        // Then we can only have B numbers that fit.
        if (A >= n && B < n){
            ans += B + 1;
            continue;
        }

        // Case 3: If A + B < 1<<i
        // Then we will never win. Give up
        if (A+B < n){
            break;
        }

        // Case 4: If both A and B < 1<<i
        // Then it can only work from x = A, y = 1<<i - A to x = 1<<i - B, y = B
        // Note that since A + B >= 1<<i, then newY < y
        int newY = n - A;
        ans += B - newY + 1;
    }

    // Print that shit
    printf("%lld\n", ans);
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    while(testcases--){
        run();
    }
    return 0;
}
