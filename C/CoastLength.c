#include<stdio.h>

int n, m;

char grid[1<<10][1<<10];
int visited[1<<10][1<<10];
int dr[5] = {0, 1, 0, -1, 0};

int out = 0;

void dfs(int x, int y){
    for (int i = 0; i < 4; ++i){
        int newx = x + dr[i];
        int newy = y + dr[i+1];

        // Are we in bounds?
        if (newx < 0 || newy < 0 || newx > n+1 || newy > m+1) continue;
        
        if (grid[newx][newy] == '1'){
            out++;
            continue;
        }
        
        // Have we visited before?
        if (visited[newx][newy]) continue;
        visited[newx][newy] = 1;

        dfs(newx, newy);
    }
}

int main(){
    // Scan in input
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            scanf(" %c", &grid[i][j]);
        }
    }

    // Do DFS;
    visited[0][0] = 1;
    dfs(0, 0);

    // Print the outcome
    printf("%d\n", out);
    return 0;
}
