#include<stdio.h>

char grid[256][256];
int visited[256][256];

int main(){
    // Scan in input
    int r, c;
    scanf("%d %d", &r, &c);

    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            scanf(" %c", &grid[i][j]);
        }
    }

    int out = 0;
    int currR = 0;
    int currC = 0;

    // Simulate that shit
    while (grid[currR][currC] != 'T'){
        visited[currR][currC] = 1;

        switch (grid[currR][currC]){
            case 'N':
                currR--;
                break;
            case 'S':
                currR++;
                break;
            case 'E':
                currC++;
                break;
            case 'W':
                currC--;
                break;
        }

        // Check if we are out of bounds
        if (currC < 0 || currC >= c || currR < 0 || currR >= r){
            out = -2;
            break;
        }

        // Are we going in a circle?
        if (visited[currR][currC]){
            out = -1;
            break;
        }

        // If not, take a step
        out++;
    }

    if (out == -1) printf("Lost\n");
    else if (out == -2) printf("Out\n");
    else printf("%d\n", out);

    return 0;
}
