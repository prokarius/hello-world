#include<stdio.h>

char grid[1<<16][16];
char output[1<<16][16];

int main(){
    // Scan in input
    int r, c;
    scanf("%d %d", &r, &c);

    // Initialise the original grid to be dots while scanning in input
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            scanf(" %c", &grid[i][j]);
            output[i][j] = '.';
        }
    }

    // Loop through each column and find out how many apples are falling
    for (int i = 0; i < c; ++i){
        int appleCount = 0;
        for (int j = 0; j < r; ++j){
            if (grid[j][i] == 'a') appleCount++;

            // If we see a brick wall, populate it, and fill it up with apples.
            else if (grid[j][i] == '#'){
                output[j][i] = '#';
                for (int k = 1; k <= appleCount; ++k) output[j-k][i] = 'a';
                appleCount = 0;
            }
        }

        // At the end, if we still have apples, drop them to gravity!
        for (int k = 1; k <= appleCount; ++k) output[r-k][i] = 'a';
    }

    // Print this shit
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            printf("%c", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}

