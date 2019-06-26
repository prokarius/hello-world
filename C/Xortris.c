#include<stdio.h>

int grid[128][128];
int greedy[128];

void greedyI(){
    for (int i = 0; i < 100; ++i){
        if (greedy[i]){
            greedy[i] ^= 1;
            greedy[i+1] ^= 1;
            greedy[i+2] ^= 1;
            greedy[i+3] ^= 1;
        }
    }

    for (int i = 0; i < 105; ++i){
        if (greedy[i]){
            printf("im");
            break;
        }
    }

    printf("possible\n");
}

int main(){
    int n, m;
    int numBlack = 0;
    char ph;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            scanf(" %c", &ph);
            if (ph == 'X'){
                ++numBlack;
                grid[i][j] = 1;
            }
            else {
                grid[i][j] = 0;
            }
        }
    }

    // 3 cases:
    // Case 1: If the grid is 2x2, then ensure it is all black or all white
    if (n == 2 && m == 2){
        if (numBlack % 4 != 0){
            printf("im");
        }
        printf("possible\n");
        return 0;
    }

    // Case 2: If the grid is one dimensional, greedily use the I piece
    if (n == 1){
        for (int i = 0; i < m; ++i){
            greedy[i] = grid[0][i];
        }
    }
    else if (m == 1){
        for (int i = 0; i < n; ++i){
            greedy[i] = grid[i][0];
        }
    }

    // Call the greedyI function
    if (n == 1 || m == 1){
        greedyI();
        return 0;
    }

    // Case 3: Note that using the following combinations of pieces:
    // a) S & L
    // b) S & T
    // c) L & T
    
    // I can swap (including symmetries):
    // a) X--    b) X--    c) XX-
    //    -X-       X--       ---

    // This means I can bring scoot any piece around
    // Meaning that if there are an even number of pieces, I can win
    if (numBlack % 2 != 0){
        printf("im");
    }
    printf("possible\n");
    return 0;
}
