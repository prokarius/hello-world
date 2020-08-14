#include<stdio.h>

#define MIN(x, y) (x < y)?(x):(y)

int grid[512][512];
int pass[512][512];
int memo[512][512][11];

int dr[3] = {-1, 0, 1};

int isPass(int x, int y){
    if (grid[x][y] == -1 ||
        grid[x+1][y] == -1 ||
        grid[x-1][y] == -1 ||
        grid[x][y+1] == -1 ||
        grid[x][y-1] == -1
    ) return 0;

    if (grid[x-1][y] <= grid[x][y] ||
        grid[x+1][y] <= grid[x][y] ||
        grid[x][y+1] >= grid[x][y] ||
        grid[x][y-1] >= grid[x][y]
    ) return 0;

    return 1;
}

// Global because dp function needs access to these...
int r, c, n;

int dp(int x, int y, int numPasses){
    // Have we visited too many passes?
    if (numPasses < 0) return 1<<29;
    
    // Have we reached the end?
    if (y == c+1) return (numPasses != 0)*(1<<29);

    // Have we been here before?
    if (memo[x][y][numPasses] != -99) return memo[x][y][numPasses];

    int currBest = 1<<29;
    // Try out all possible paths!
    for (int i = 0; i < 3; ++i){
        int nextx = x + dr[i];
        
        // Did we just drive into a swamp?!
        if (grid[nextx][y+1] == -1) continue;

        // OK phew we didn't. Try going there.
        int best = grid[nextx][y+1] + dp(nextx, y+1, numPasses-pass[nextx][y+1]);

        currBest = MIN(currBest, best);
    }

    // Memoize before returning
    memo[x][y][numPasses] = currBest;
    return currBest;
}


int main(){
    // Scan in input
    scanf("%d %d %d", &r, &c, &n);

    for (int i = 1; i <= r; ++i){
        for (int j = 1; j <= c; ++j){
            scanf("%d", &grid[i][j]);
        }
    }

    // Pad with -1s all around
    for (int i = 0; i <= r; ++i){
        grid[i][0] = -1;
    }

    for (int i = 0; i <= c; ++i){
        grid[r+1][i] = -1;
        grid[0][i] = -1;
    }

    // Find out whether each square is a pass
    // Note that we don't do it for the borders because the
    // first and last row always isn't a pass
    for (int i = 2; i < r; ++i){
        for (int j = 2; j < c; ++j){
            pass[i][j] = isPass(i, j);
        }
    }

    // Reset my memo array:
    for (int i = 1; i <= r; ++i){
        for (int j = 1; j <= c; ++j){
            for (int k = 0; k <= n; ++k){
                memo[i][j][k] = -99;
            }
        }
    }

    // Try out all possible starting rows:
    int best = 1<<29;
    for (int i = 1; i <= r; ++i){
        if (grid[i][1] == -1) continue;
        int curr = grid[i][1] + dp(i, 1, n);
        best = MIN(curr, best);
    }

    if (best == 1<<29) printf("impossible\n");
    else printf("%d\n", best);

    return 0;
}

