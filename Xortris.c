#include<stdio.h>

int grid[105][105];

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
    // Case 1: If the grid is 2x2, then ensure it is all black
    if (n == 2 && m == 2){
        if (numBlack == 4){
            printf("possible\n");
        }
        else {
            printf("impossible\n");
        }
        return 0;
    }

    // Case 2: If the grid is one dimensional, use the I piece



    // Case 3: Note that




    return 0;
}
