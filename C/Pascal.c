#include <stdio.h>

int primelist[3800], somelist [32000];

int primesieve (){
    int i, j, l=0;
    for (i =2; i<32000; i++){
        if (somelist[i] == 0){
            primelist[l] = i;
            l++;
            for (j=i; j<32000/i; j++){
                somelist[j*i] = 1;
            }
        }
    }
    return l;
}

int main(){
    int l = primesieve();
    int n;
    scanf("%d", &n);
    if (n == 1){
        printf("0");
        return 0;
    }
    int v = 0;
    while (v < l){
        if (n%(primelist[v]) == 0){
            break;
        }
        v++;
    }
    if (v == l){
        printf("%d", n-1);
        return 0;
    }
    int k = n/primelist[v];
    printf("%d", n-k);
    return 0;
}

