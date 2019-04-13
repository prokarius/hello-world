#include<stdio.h>

char grid[1005][1005];
long long dp[1005][1005];
int dfs[1000002][2];
int dfshead = 0;
int dr[5] ={0, 1, 0, -1, 0};

int main(){
    int n;
    char ph;
    scanf("%d ", &n);
    for (int i=1; i<=n; ++i){
        for (int j=1; j<=n; ++j){
            scanf(" %c", &ph);
            grid[i][j] = ph;
            dp[i][j] = -1;
        }
    }

    // Do dp on the first row
    dp[1][1] = 1;
    for (int j=2; j<=n; ++j){
        if (grid[1][j] == '.'){
            dp[1][j] = 1;
        }
        else {
            break;
        }
    }

    // And the first column
    for (int j=2; j<=n; ++j){
        if (grid[j][1] == '.'){
            dp[j][1] = 1;
        }
        else {
            break;
        }
    }

    // Then do dp on the rest
    for (int i=2; i<=n; ++i){
        for (int j=2; j<=n; ++j){
            if (grid[i][j] == '.'){
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % 2147483647;
                if (dp[i-1][j] == -1 || dp[i][j-1] == -1){
                    dp[i][j]++;
                }
            }
            else{
                dp[i][j] = -1;
            }
        }
    }

    // check if the final answer is -1
    if (dp[n][n] != -1){
        printf("%lld\n", dp[n][n]);
        return 0;
    }

    // Else we just gotta dfs
    dfs[dfshead][0] = 1;
    dfs[dfshead][1] = 1;
    dfshead++;
    while (dfshead != 0){
        dfshead--;
        int x = dfs[dfshead][0];
        int y = dfs[dfshead][1];
        for (int i=0; i<4; ++i){
            int newx = x+dr[i];
            int newy = y+dr[i+1];
            if (grid[newx][newy] == '.'){
                grid[newx][newy] = '#';
                dfs[dfshead][0] = newx;
                dfs[dfshead][1] = newy;
                dfshead++;
            }
        }
    }

    //  Check if we have visited the end
    printf(grid[n][n] == '#' ? "THE GAME IS A LIE\n" : "INCONCEIVABLE\n");

    return 0;
}
