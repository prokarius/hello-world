#include<stdio.h>
#include<stdlib.h>

int adjlist[128][128];
int guess[128];

int n;

void printColors(){
    for (int i = 1; i <= n; ++i){
        printf("%d %d\n", i, guess[i]);
    }
}

int dp(int pos){
    // Have we reached the end?
    if (pos == n+1){
        printColors();
        exit(0);  // OK well Im got a bit lazy, sorry
    }

    // Try each color
    for (int i = 1; i <= 4; ++i){
        guess[pos] = i;

        // Does this color work 
        int possible = 1;
        for (int j = 1; j < pos; ++j){ 

            // Same color as something it was connected to
            if (adjlist[pos][j] && guess[j] == i){
                possible = 0;
                break;
            }
        }    

        // This color would cause problems down the line
        if (possible == 1){
            if (dp(pos+1) == 0) continue;
        }
    }
    
    // We have tried all colors, and no coloring works
    return 0;
}

int main(){
    // Scan in input
    scanf("%d", &n);

    // Keep scanning until EOF
    int x, y;
    while (scanf("%d-%d", &x, &y) != EOF){
        adjlist[x][y]++;
        adjlist[y][x]++;
    }

    // Imma see if backtracking works?
    guess[1] = 1;
    dp(2);

    return 0;
}

