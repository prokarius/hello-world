#include<stdio.h>

int array[2600], onion[2600], ans[2600];

int main(){
    int i, j, r, c;
    // Scan in the data
    scanf ("%d %d" , &r, &c);
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            scanf("%d", &array[i*r+c]);
        }
    }

    // Precompute


    // Printf the answer for each query.
    int n, int k;
    scanf("%d", &n);
    while (n--){
        scanf("%d", &k);
        printf("%d\n", ans[k]);
    }
    return 0;
}
