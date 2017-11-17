#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define MAX(x, y) ((x)>(y))?(x):(y)
#define MIN(x, y) ((x)<(y))?(x):(y)
#define ABS(x) ((x)>0)?(x):(-x)

int main() {
    int n; 
    scanf("%i", &n);
    int m; 
    scanf("%i", &m);
    int vlist[302][303];
    for(int a0 = 0; a0 < m; a0++){
        int x; 
        int y; 
        int w; 
        scanf("%i %i %i", &x, &y, &w);
        vlist[a0][0] = x;
        vlist[a0][1] = y;
        vlist[a0][2] = w;
    }
    int maax = -1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int sa = 0;
            for (int k = 0; k < m; k++){
                int dy = MAX(0, vlist[k][2] - ABS(i - vlist[k][0]));
                int dx = MAX(0, vlist[k][2] - ABS(j - vlist[k][1]));
                sa += MAX(0, MIN(dy, dx));
            }
            
            if (sa > maax){
                maax = sa;
            }
        }
    }
    printf("%d", maax);
    return 0;
}
