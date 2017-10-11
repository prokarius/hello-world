#include<stdio.h>

int main(){
    long long n, k, i, b[95];
    b[1] = b[2] = 1;
    for (i = 3; i < 93; i++){
        b[i] = b[i-1] + b[i-2];
    }

    scanf("%lld %lld", &n, &k);
    if (n > 93) n = 93;
    while (n > 2){
        if (k <= b[n-2]) n-=2;
        else {
            k -= b[n-2];
            n -= 1;
        }
    }
    if (n == 1) printf ("N\n");
    else if (n == 2) printf ("A\n");
    else if (k == 1) printf ("N\n");
    else printf ("A\n");
    return 0;
}
