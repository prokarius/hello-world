#include<stdio.h>

int row, col;
char grid[64][16];
int dr[5] = {0, 1, 0, -1, 0};

int adjList[256][4];
int size[256];
int visited[256];

int forwards[256];
int backwards[256];

void reset(){
    for (int i = 0; i < 256; ++i){
        forwards[i] = -1;
        backwards[i] = -1;
        size[i] = 0;
    }
}

// Returns 1 if we found a new matching
int dfs(int x){
    if (visited[x]) return 0;
    visited[x] = 1;

    for (int i = 0; i < size[x]; ++i){
        int neighbor = adjList[x][i];

        // Is this guy taken?
        if (backwards[neighbor] == -1){
            backwards[neighbor] = x;
            forwards[x] = neighbor;
            return 1;
        }

        // DFS into the neighbor
        if (!dfs(backwards[neighbor])) continue;

        // Oh we actually found a success
        backwards[neighbor] = x;
        forwards[x] = neighbor;
        return 1;
    }

    // Tough luck
    return 0;
}

void solve(){
    // Scan in input
    int count = 0;
    scanf(" %d %d", &row, &col);
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == '*') ++count;
        }
    }

    // Define value as i*col + j.
    // Loop through all odd value in the grid.
    // If the character is a *, there is a antenna.
    // Look through dr to find if there are any adjacencies...
    for (int i = 0; i < row; ++i){
        for (int j = i%2; j < col; j += 2){
            if (grid[i][j] == '*'){
                int value = (i*col + j) / 2;
                for (int k = 0; k < 4; ++k){
                    int newI = i + dr[k];
                    int newJ = j + dr[k+1];

                    // Boundary checks
                    if (newI < 0 || newJ < 0 || newI >= row || newJ >= col) continue;
                    if (grid[newI][newJ] == '*'){
                        int newValue = (newI*col + newJ) / 2;
                        adjList[value][size[value]] = newValue;
                        ++size[value];
                    }
                }
            }
        }
    }

    // Ready to do MCBM, pre assign
    int matches = 0;
    for (int i = 0; i < (row * col) / 2; ++i){
        for (int j = 0; j < size[i]; ++j){
            if (backwards[adjList[i][j]] == -1){
                forwards[i] = adjList[i][j];
                backwards[adjList[i][j]] = i;
                matches++;
                break;
            }
        }
    }

    for (int i = 0; i < (row * col) / 2; ++i){
        if (forwards[i] != -1) continue;
        for (int j = 0; j < (row * col) / 2; ++j){
            visited[j] = 0;
        }

        matches += dfs(i);
    }

    // The answer is the number of antennas, minus the number of matches!
    printf("%d\n", count - matches);
}

int main(){
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        reset();
        solve();
    }

    return 0;
}

