#include<stdio.h>

int angles[360];

// For each of the angles given, we just have to see where it ends up
// Note that we can just simulate 360 rounds of the "dp" thing.
// Hence our complexity is simply (360 * 360 * 10)
int main(){
    angles[0] = 1;
    int i, j, k, K, N, given[10];
    scanf("%d %d", &N, &K);
    for (i=0; i<N; ++i) scanf("%d", &given[i]);
    for (j=360; j>0; --j){
        for (i=0; i<360; ++i){
            if (angles[i]){
                for (k=0; k<N; ++k){
                    ++angles[(i + given[k])%360];
                    ++angles[(360 + i - given[k])%360];
                }
            }
        }
    }
    while (K--){
        int temp;
        scanf("%d", &temp);
        if (angles[temp]) printf ("YES\n");
        else printf("NO\n");
    }
    return 0;
}
