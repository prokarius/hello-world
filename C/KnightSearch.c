#include<stdio.h>

char grid[128][128];
char string[1<<14];
char match[16] = "ICPCASIASG";

int dr[10] = {1, 2, -1, -2, 1, -2, -1, 2, 1};
int n;

int recurse(int x, int y, int numIndex){
    // Base case, we reached the end of the string
    if (numIndex == 10) return 1;

    // Else recurse
    for (int i = 0; i < 8; ++i){
        int newX = x + dr[i];
        int newY = y + dr[i+1];

        // Bounds check
        if (newX < 0 || newY < 0 || newX >= n || newY >= n) continue;

        // Entry check
        if (grid[newX][newY] != match[numIndex]) continue;

        // Recurse
        if (recurse(newX, newY, numIndex+1)) return 1;
    }

    // If we cannot find it, return 0;
    return 0;
}

int main(){
    // Scan in input
    scanf("%d", &n);
    scanf("%s", string);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            grid[i][j] = string[i*n+j];
        }
    }

    // Do recursive DFS
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (grid[i][j] == match[0]){
                if (recurse(i, j, 1)){
                    printf("YES\n");
                    return 0;
                }
            }
        }
    }

    printf("NO\n");
    return 0;
}
