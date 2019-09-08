#include<stdio.h>

int pos[16][2];
int visited[16];
int n;
int startx, starty;

int ABS(int x){
    return (x > 0)?(x):(-x);
}

int MIN(int x, int y){
    return (x < y)?(x):(y);
}

int recurse(int curr, int currx, int curry, int dist){
    if (curr == n){
        return dist + ABS(currx - startx) + ABS(curry - starty);
    }

    int best = 1<<30;

    for (int i = 0; i < n; ++i){
        if (visited[i]) continue;
        visited[i] = 1;
        best = MIN(best, recurse(curr+1, pos[i][0], pos[i][1], dist + ABS(currx - pos[i][0]) + ABS(curry - pos[i][1])));
        visited[i] = 0;
    }

    return best;
}

void solve(){
    // Scan in input
    scanf("%d %d", &n, &n); // Noone cares about the size of the world lol
    scanf("%d %d", &startx, &starty);

    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d %d", &pos[i][0], &pos[i][1]);
    }

    // TSP? What's that? Why not just brute force?
    printf("%d\n", recurse(0, startx, starty, 0));
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}

