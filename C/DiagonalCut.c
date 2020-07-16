#include<stdio.h>

long long gcd(long long a, long long b){
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main(){
    long long X, Y;
    scanf("%lld %lld", &X, &Y);

    // The only way we cut a square in half is if the cut goes through the middle.
    // But in order to go through the middle, we have that (x+0.5, y+0.5) is
    // a solution to y = mx + c. Since the line is diagonal, m = Y/X, c = 0

    // Do algebra X(2y+1) = Y(2x+1)
    // We want to find solutions to the above equation.
    // At the simplest, gcd(X, Y) = 1.
    // For integer solutions, the parity of LHS and RHS has to be odd

    // If it is, then there will be 1 solution: X = 2x+1, Y = 2y+1
    // i.e. There will be an intersection at (X-1/2, Y-1/2)

    // Suppose gcd(X, Y) = k. Then this is similar to scaling up the situation by k.
    // Then we will have k points that gets sliced through the middle.

    // TLDR:
    long long g = gcd(X, Y);
    printf("%lld\n", ((X/g)%2 * (Y/g)%2)?g:0);
    return 0;
}
