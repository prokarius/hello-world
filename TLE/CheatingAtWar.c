#include<stdio.h>

#define MIN(x,y) (x<y)?(x):(y)

int n = 26;

int mapping[256];
int matrix[26][26], original[26][26];

int forward[26], backward[26];
int visited[26];

int dfs(int node){
    if (visited[node]) return 0;
    visited[node] = 1;

    for (int j = 0; j < n; ++j){
        // Do we even have an edge?
        if (matrix[node][j] != 0) continue;

        // Trivial matching?
        if (backward[j] == -1){
            backward[j] = node;
            forward[node] = j;
            return 1;
        }

        // Did we find a path backwards?
        if (!dfs(backward[j])) continue;

        backward[j] = node;
        forward[node] = j;
        return 1;
    }

    return 0;
}

void mcbm(){
    for (int i = 0; i < n; ++i){
        forward[i] = -1;
        backward[i] = -1;
    }

    // Trivial matching
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            // Connect if there is an edge to a node not yet used
            if (matrix[i][j] == 0 && backward[j] == -1){
                forward[i] = j;
                backward[j] = i;
                break;
            }
        }
    }

    // Do DFS for each unmatched node to find aug paths
    for (int i = 0; i < n; ++i){
        if (forward[i] != -1) continue;
        for (int j = 0; j < n; ++j) visited[j] = 0;
        dfs(forward[i]);
    }
}

int hungarian(){
    // Subtract smallest number from rows and col
    printf("BBBBBBBBBBBBB\n");
    for (int i = 0; i < n; ++i){
        int best = 1<<30;
        for (int j = 0; j < n; ++j) best = MIN(best, matrix[i][j]);
        for (int j = 0; j < n; ++j) matrix[i][j] -= best;
    }

    for (int j = 0; j < n; ++j){
        int best = 1<<30;
        for (int i = 0; i < n; ++i) best = MIN(best, matrix[i][j]);
        for (int i = 0; i < n; ++i) matrix[i][j] -= best;
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            printf("%d ", matrix[i][j]);
        }printf("\n"); 
    }

    // Find the minimum number of rows and columns to be covered by 0s
    // This is done using greedy
    printf("CCCCCC\n");
    while (1){
        int rowzeros[n], colzeros[n];
        int chosenrows[n], chosencols[n];
 
        // Reset all the arrays
        for (int i = 0; i < n; ++i){
            rowzeros[i] = 0;
            colzeros[i] = 0;
            chosenrows[i] = 0;
            chosencols[i] = 0;
        }

        // Calculate the number of rows
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (matrix[i][j] == 0){
                    rowzeros[i]++;
                    colzeros[j]++;
                }
            }
        }

        // Find for each zero where we should draw the line
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (matrix[i][j] != 0) continue;

                int direction = rowzeros[i] - colzeros[j];
                if (direction > 0 && !chosenrows[i]) chosenrows[i]++;
                else if (direction <= 0 && !chosencols[j]) chosencols[j]++;
            }
        }

        // Lastly count the number of lines, break if lines == n
        int numLines = 0;
        for (int i = 0; i < n; ++i){
            numLines += (chosenrows[i] > 0) + (chosencols[i] > 0);
        }
        printf("%d\n", numLines);
        if (numLines == n) break;

        // Oh no, we need more zeros
        int minRemain = 1<<30;
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (matrix[i][j] == 0) continue;
                minRemain = MIN(minRemain, matrix[i][j]);
            }
        }

        // Delete from all cells not covered, add to all cells covered twice
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                if (!chosenrows[i] && !chosencols[j]) matrix[i][j] -= minRemain;
                else if (chosenrows[i] && chosencols[j]) matrix[i][j] += minRemain;
            }
        }
    }

    printf("DDDDDDDDDDD\n");

    // Cool, we have all the zeros we need. Do MCBM and choose the cells
    mcbm();
    
    printf("EEEEEEEEEE\n");

    int out = 0;
    for (int i = 0; i < n; ++i){
        int j = forward[i];
        out += original[i][j];
    }

    return out;
}

void solve(){
    // Scan in input
    int yraglac[32], opponent[32];
    
    for (int i = 0; i < n; ++i){
        char chr;
        scanf(" %c", &chr);
        yraglac[i] = mapping[chr];
    }

    for (int i = 0; i < n; ++i){
        char chr;
        scanf(" %c", &chr);
        opponent[i] = mapping[chr];
    }

    // Construct the matrix
    // matrix[i][j] is 2 if yraglac[i] > opponent[j]
    // matrix[i][j] is 1 if yraglac[i] == opponent[j]
    // matrix[i][j] is 0 if yraglac[i] < opponent[j]

    for (int i = 0; i < n; ++i){ 
        for (int j = 0; j < n; ++j){
            if (yraglac[i] > opponent[j]) matrix[i][j] = 0;
            else if (yraglac[i] == opponent[j]) matrix[i][j] = 1;
            else matrix[i][j] = 2;
        }
    }

    // Keep a copy of the matrix
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            original[i][j] = matrix[i][j];
        }
    }

    printf("AAAAAAAAA\n");

    // Then do Hungarian Algo on it
    printf("%d\n", -hungarian());
}

int main(){
    // Set up the mapping
    for (char i = '2'; i <= '9'; ++i) mapping[i] = i - '0';
    mapping['T'] = 10;
    mapping['J'] = 11;
    mapping['Q'] = 12;
    mapping['K'] = 13;
    mapping['A'] = 14;

    int testcases;
    scanf("%d", &testcases);

    while(testcases--) solve();
    return 0;
}

