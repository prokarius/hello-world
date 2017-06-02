#include <stdio.h>

int main(){
    int numcases, i=1;

    scanf ("%d", &numcases);
    while (i<(numcases+1)){
        long long n, k;
        scanf ("%d %d", &n, &k);
        if (k % (1 << n) == (1 << n)-1){
            printf ("Case #%d: ON\n", i);
        }
        else {
            printf ("Case #%d: OFF\n", i);
        }
        i += 1;
    }
    return 0;
}
