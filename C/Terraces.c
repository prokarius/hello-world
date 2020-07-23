#include<stdio.h>

int grid[512][512];
int visited[512][512];
int pool[1<<18];

int dr[5] = {0, 1, 0, -1, 0};

// Identify all components. Label it as such in the visited array
void dfs(int x, int y, int numPool){
    int curr = grid[x][y];

    for (int i = 0; i < 4; ++i){
        int newX = x + dr[i];
        int newY = y + dr[i+1];

        // Is there an outflow?
        if (grid[newX][newY] < curr) pool[numPool] = 0;

        // Find all tiles of the same height as curr
        if (visited[newX][newY]) continue;
        if (grid[newX][newY] != curr)continue;
        visited[newX][newY] = numPool;

        dfs(newX, newY, numPool);
    }
}

int main(){
    // Scan in input
    int r, c;
    scanf("%d %d", &r, &c);

    for (int i = 1; i <= c; ++i){
        for (int j = 1; j <= r; ++j){
            scanf("%d", &grid[i][j]);
        }
    }

    // Set a boundary around the outside
    for (int i = 0; i <= c+1; ++i){
        grid[i][0] = 1<<30;
        grid[i][r+1] = 1<<30;
    }

    for (int i = 0; i <= r+1; ++i){
        grid[0][i] = 1<<30;
        grid[c+1][i] = 1<<30;
    }

    // Identify each pool
    int numPool = 1;

    // Do DFS on the grid.
    for (int i = 1; i <= c; ++i){
        for (int j = 1; j <= r; ++j){
            if(!visited[i][j]){
                visited[i][j] = numPool;
                pool[numPool] = 1;
                dfs(i, j, numPool);
                numPool++;
            }
        }
    }
    
    // Now have a bunch of tiles each labelled with the component number.
    // For each time, see whether the component is leaky.
    int out = 0;
    for (int i = 1; i <= c; ++i){
        for (int j = 1; j <= r; ++j){
            if (pool[visited[i][j]]) out++;
        }
    }

    // Print out the number of pools
    printf("%d\n", out);

    return 0;
}

