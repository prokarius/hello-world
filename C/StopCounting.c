#include<stdio.h> 

#define MAX(x, y) ((x)>(y))?(x):(y)

int cards[1<<20];

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d", &cards[i]);
    }

    // The average will be some prefix / suffix of the deck. Not both.
    // Suppose the average is both prefix AND suffix. Call it a and b.
    // We must have that a == b, because avg(a,b) <= max(a,b)

    double best = 0;
    double prefixSum = 0;
    for (int i = 0; i < n; ++i){
        prefixSum += cards[i];
        best = MAX(best, prefixSum/(i+1));
    }

    double suffixSum = 0;
    for (int i = 1; i <= n; ++i){
        suffixSum += cards[n-i];
        best = MAX(best, suffixSum/i);
    }

    printf("%lf\n", best);

    return 0;
}

