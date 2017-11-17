#include<stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    while (n){
        int o = 0, i = -1, j, k, p[50][4];
        while (++i < n) scanf("%d %d %d %d", &p[i][0], &p[i][1], &p[i][2], &p[i][3]);
        for (i = 0; i<500; ++i){
            for (j = 0; j<500; ++j){
                for (k = 0; k < n; ++k){
                    if (i >= p[k][0] && i < p[k][2] && j >= p[k][1] && j < p[k][3]){
                        ++o;
                        break;
                    }
                }
            }
        }
        printf ("%d\n", o);
        scanf ("%d", &n);
    }
    return 0;
}
