#include<stdio.h>

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // Remember difference of 2 squares formula? Well use that
    // Do trial division to find factors of n
    for (int aMinusB = 1; aMinusB*aMinusB <= n; ++aMinusB){
        if (n % aMinusB) continue;
        int aPlusB = n/aMinusB;

        // Is a a whole number?
        if ((aPlusB + aMinusB) % 2) continue;
        int a = (aPlusB + aMinusB) / 2;
        int b = aPlusB - a;

        // Does this value of A cause B to be negative?
        if (b < 0) continue;

        // Yay we found a**2 - b**2 print print!
        printf("%d %d\n", b, a);
        return 0;
    }

    printf("impossible\n");
    return 0;
}

