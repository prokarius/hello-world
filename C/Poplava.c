#include <stdio.h>
#include <math.h>

int main (){
    long long n, m;
    scanf("%lld %lld", &n, &m);
    if (((n-1)*(n-2)/2) < m){
        printf("-1");
        return 0;
    }
    long long i, k = (long long)((2*n-1)-sqrt((2*n-1)*(2*n-1)-8*(m+n-1)))/2;
    long long left = m - ((k-1)*(2*n-k-2))/2;
    printf ("%d ", n);
    if (left){
        printf ("%d ", n-left-1);
    }
    for (i = 1; i < k; i++){
        printf ("%d ", i);
    }
    printf ("%d ", n-1);
    if (left){
        for (i = n-2; i>n-left-1; i--){
            printf ("%d ", i);
        }
        for (i = n-left-2; i>k-1; i--){
            printf ("%d ", i);
        }
    }
    else {
        for (i = n-2; i>k-1; i--){
            printf ("%d ", i);
        }
    }
    return 0;
}
