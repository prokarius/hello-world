#include<stdio.h>
#include<stdlib.h>

int grid[36][36];
int adjlist[36][36];
int numEdges[36];

int forwards[36];
int backwards[36];

int visited[36];

int dfs(int curr){
    if (visited[curr]) return 0;
    visited[curr] = 1;

    for (int i = 0; i < numEdges[curr]; ++i){
        int neighbor = adjlist[curr][i];

        if (backwards[neighbor] == -1){
            backwards[neighbor] = curr;
            forwards[curr] = neighbor;
            return 1;
        }

        if (!dfs(backwards[neighbor])) continue;

        backwards[neighbor] = curr;
        forwards[curr] = neighbor;
        return 1;
    }

    return 0;
}

// Returns 1 if there is an MCBM can be formed
int check(int x, int n){
    for (int i = 0; i < n; ++i){
        numEdges[i] = 0;
    }

    // Create the adjlist
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (grid[i][j] >= x){
                adjlist[i][numEdges[i]] = j;
                numEdges[i]++;
            }
        }
    }

    // Then do MCBM
    for (int i = 0; i < n; ++i){
        forwards[i] = -1;
        backwards[i] = -1;
    }

    // Start by greedy matching everyone
    for (int i = 0; i < n; ++i){
        if (numEdges[i] == 0){
            return 0;
        }

        for (int j = 0; j < numEdges[i]; ++j){
            int neighbor = adjlist[i][j];
            if (backwards[neighbor] == -1){
                forwards[i] = neighbor;
                backwards[neighbor] = i;
                break;
            }
        }
    }

    // Then DFS
    for (int i = 0; i < n; ++i){
        if (forwards[i] != -1) continue;

        for (int i = 0; i < n; ++i){
            visited[i] = 0;
        }

        if (!dfs(i)) return 0;
    }

    return 1;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%d", &grid[i][j]);
        }
    }

    // We will be doing MCBM, but binary searching for the correct value of x
    int lo = 0;
    int hi = 1<<20;
    int best = -1;
    while (lo <= hi){
        int mid = (lo + hi)/2;

        if (check(mid, n)){
            best = mid;
            lo = mid+1;
        }
        else {
            hi = mid-1;
        }
    }

    printf("%d\n", best);

    return 0;
}
