#include<stdio.h>

char grid[256][256];

// Return 1 if game was won by hansel (x)
int solve(){
    // Scan in input
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);

    for (int i = 0; i < n; ++i){
        scanf("%s", grid[i]);
    }

    // Brute force the top left
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            int fail = 1;
            if (grid[i][j] == '.') continue;
            char curr = grid[i][j];

            // Search down
            // But only if there are space left
            if (i + k <= n){
                fail = 0;
                for (int c = 1; c < k; ++c){
                    if (grid[i+c][j] != curr){
                        fail = 1;
                        break;
                    }
                }
            }

            if (fail == 0) return (curr == 'x')?(1):(-1);

            // Search right
            // But only if there are space left
            if (j + k <= m){
                fail = 0;
                for (int c = 1; c < k; ++c){
                    if (grid[i][j+c] != curr){
                        fail = 1;
                        break;
                    }
                }
            }

            if (fail == 0) return (curr == 'x')?(1):(-1);

            // Search diagonally right
            // But only if there are space left <-- This seems to be a common theme
            if (j + k <= m && i + k <= n){
                fail = 0;
                for (int c = 1; c < k; ++c){
                    if (grid[i+c][j+c] != curr){
                        fail = 1;
                        break;
                    }
                }
            }

            if (fail == 0) return (curr == 'x')?(1):(-1);

            // Last case: Search diagonially left
            // Can you guess the theme?
            if (j - k > -2 && i + k <= n){
                fail = 0;
                for (int c = 1; c < k; ++c){
                    if (grid[i+c][j-c] != curr){
                        fail = 1;
                        break;
                    }
                }
            }

            if (fail == 0) return (curr == 'x')?(1):(-1);
        }
    }

    // If not, just return 0 to mean a draw!
    return 0;
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    int hansel = 0;
    int gretel = 0;

    for (int i = 0; i < testcases; ++i){
        switch (solve()){
            case 1:
                ++hansel;
                break;
            case -1:
                ++gretel;
                break;
        }
    }

    printf("%d:%d\n", hansel, gretel);

    return 0;
}
