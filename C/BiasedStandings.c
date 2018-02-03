#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int teams[100005];

int cmp(const void * a, const void * b){
    return ( *(int *)a - *(int *)b);
}

int main(){
    int n;
    scanf ("%d", &n);
    while (n--){
        int i, k, ph, o=0;
        scanf("%d", &k);
        for (i=0; i<k; ++i){
            scanf ("%*s %d", &ph);
            teams[i] = ph;
        }
        qsort (teams, k, sizeof(int), cmp);
        for (i=0; i<k; ++i) o += fabs(teams[i]-(i+1));
        printf ("%d\n", o);
    }
    return 0;
}
