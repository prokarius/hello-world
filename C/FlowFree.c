#include<stdio.h>

char grid[16];
char copy[16];
int givens[4][2];

int yellow = 0;
char colors[4] = {'R', 'G', 'B', 'Y'};

int color(char currColor, int curr, int end){
    int ans = 0;
    grid[curr] = 'X';

    // Base case, if we reached the end, check to see if we colored everything in
    if (curr == end){
        for (int i = 0; i < 16; ++i){
            if (grid[i] == currColor){
                grid[curr] = currColor;
                return 0;
            }
        }
        return 1;
    }

    // If not, try moving around the grid
    // Horizontally first
    if (curr % 4 != 0 && grid[curr - 1] == currColor){
        if (color(currColor, curr - 1, end)){
            grid[curr] = currColor;
            return 1;
        }
    }

    if (curr % 4 != 3 && grid[curr + 1] == currColor){
        if (color(currColor, curr + 1, end)){
            grid[curr] = currColor;
            return 1;
        }
    }

    if (curr / 4 != 0 && grid[curr - 4] == currColor){
        if (color(currColor, curr - 4, end)){
            grid[curr] = currColor;
            return 1;
        }
    }

    if (curr / 4 != 3 && grid[curr + 4] == currColor){
        if (color(currColor, curr + 4, end)){
            grid[curr] = currColor;
            return 1;
        }
    }

    grid[curr] = currColor;
    return 0;
}

// Returns 1 if the grid is a solution
int check(){
    // Make a copy of the grid
    for (int i = 0; i < 16; ++i){
        copy[i] = grid[i];
    }

    int ans = 1;
    for (int i = 0; i < 3 + yellow; ++i){
        // Short circuit. only continue checking if we can touch all squares of a given color
        if (!color(colors[i], givens[i][0], givens[i][1])){
            ans = 0;
            break;
        }
    }

    // Reset the grid copy
    for (int i = 0; i < 16; ++i){
        grid[i] = copy[i];
    }

    return ans;
}

int dfs(int x){
    // If we reached the end, try solving
    if (x == 16) return check();

    // If this square is a given, move on!
    if (grid[x] != 'W') return dfs(x+1);
    
    // If not, put this square to use
    for (int i = 0; i < 3 + yellow; ++i){
        grid[x] = colors[i];
        if (dfs(x + 1)) return 1;
    }

    // Don't forget to restore state
    grid[x] = 'W';
    return 0;
}

int main(){
    // Scan in grid
    for (int i = 0; i < 16; ++i){
        char c;
        scanf(" %c", &c);

        // How many colors do we have?
        if (c == 'Y') yellow = 1;
        grid[i] = c;
    }

    // Find the given colors
    // There is probably a better way than cutting pasting
    for (int j = 0; j < 3 + yellow; ++j){
        int found = 0;
        for (int i = 0; i < 16; ++i){
            if (grid[i] == colors[j]){
                givens[j][found] = i;
                found++;
            }
        }
    }

    // Try all possible colorings
    int ans = dfs(0);
    printf(ans?"":"not ");

    printf("solvable\n");

    return 0;
}

