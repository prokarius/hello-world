#include<stdio.h>
#define MAX(x, y) ((x) > (y))?(x):(y)
#define MIN(x, y) ((x) < (y))?(x):(y)

int visited[10005][10005];
int goblins[100005][2];

// Not sure if cheese is the correct solution

int main(){
    // Scan in input
    int numgoblins;
    scanf("%d", &numgoblins);
    for (int i=0; i<numgoblins; ++i){
        scanf("%d %d", &goblins[i][0], &goblins[i][1]);
    }

    int numsprinkler;
    scanf("%d", &numsprinkler);

    // For each sprinkler
    // Find out where it can reach
    for (int i=0; i<numsprinkler; ++i){
        int x, y, r;
        scanf("%d %d %d", &x, &y, &r);
        int r2 = r*r;
        int maxr = MAX(0, x-r);
        int maxc = MAX(0, y-r);
        int minr = MIN(x+r, 10000);
        int minc = MIN(y+r, 10000);
        for (int R = maxr; R <= minr; ++R){
            for (int C = maxc; C <= minc; ++C){

                // If some sprinkler reached there before, continue
                if (visited[R][C]){
                    continue;
                }
                // If we cannot reach it, continue
                int dr = x-R;
                int dc = y-C;
                if (dr*dr + dc*dc > r2){
                    continue;
                }
                // Else, mark that we have visited it
                visited[R][C] = 1;
            }
        }
    }

    // For each goblin see if we have visited his spot before
    int ans = numgoblins;
    for (int i=0; i<numgoblins; ++i){
        // If we have, mark that he is gone.
        if (visited[goblins[i][0]][goblins[i][1]]){
            --ans;
        }
    }

    printf ("%d\n", ans);
    return 0;
}
