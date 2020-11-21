#include<stdio.h>

int main(){
    // Scan in input
    long long n, k;
    scanf("%lld %lld", &n, &k);

    // This is like the egg dropping thing, the shortest monotonically increasing 
    // chain will be of length sqrt(n).
    if (k*k < n){
        printf("-1\n");
        return 0;
    }

    // Split the numbers into groups of k (10, 11, 20, 21, 22, 30, 31, 32)
    // Then sort the groups backwards (30, 31, 32, 20, 21, 22, 10, 11)
    for (int i = n; i >= k; i -= k){
        for (int j = i-k+1; j <= i; j++){
            printf("%d ", j);
        }
    }

    // Then figure out the last group
    for (int i = 1; i <= n % k; ++i){
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}

