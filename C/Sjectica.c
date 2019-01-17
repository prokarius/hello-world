#include<stdio.h>

// Simply put, the number of intersections happens when you choose 4 points
// Therefore the number of ways that can happen is nC4
int main(){
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", (n-- * n-- * n-- * n--) / 24);
}
