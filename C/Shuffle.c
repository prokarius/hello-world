#include<stdio.h>

int seen[1000005];

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // For each number, as we are scanning them in, check if we have not seen the
    // number below it. Becasue if we have seen the number below it, then this is
    // part of one contiguous sequence of numbers.

    // In the end we just check for what K does 2**K >= N
    int out = -1;
    for (int i = 0; i < n; ++i){
        int curr;
        scanf("%d", &curr);

        if (!seen[curr-1]){
            ++out;
        }

        seen[curr] = 1;
    }

    int k = 0;
    while (out > 0){
        out >>= 1;
        ++k;
    }

    printf("%d\n", k);

    return 0;
}

