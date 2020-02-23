#include<stdio.h>

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // I don't get it, why can't we just print powers of 2?
    // Like it fits right...?
    int count = 0;
    for(; n; count++) n >>= 1;

    // Print the highest power of 2
    printf ("%d\n", count);

    // Then print the powers of 2
    for (int i = 0; i < count; ++i) printf("%d ", 1<<i);
    printf("\n");
    return 0;
}

