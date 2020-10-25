#include<stdio.h>

#define MAX(x, y) (x>y)?(x):(y)

typedef struct{
    int size;
    long long mat[52][52];
} Matrix;

Matrix matrixInit(int size, long long value){
    Matrix out;
    out.size = size;
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            out.mat[i][j] = -value;
        }
    }
    return out;
}

// Fake matrix multiplication
// Use a modified Bellman-ford style scheme
// Since mat[i][j] = cost to go from i to j
// Then we want mat[i][k] to maximize mat[i][j] x mat[j][k]
Matrix multiply(Matrix a, Matrix b){
    Matrix out = matrixInit(a.size, 1LL<<60);

    for (int i = 0; i < a.size; ++i){
        for (int j = 0; j < a.size; ++j){
            for (int k = 0; k < a.size; ++k){
                long long best = a.mat[j][i] + b.mat[i][k];
                out.mat[j][k] = MAX(out.mat[j][k], best);
            }
        }
    }
    return out;
}

// Fake fast exponentiation
Matrix fastExpo(Matrix a, int n){
    // Out is a**0, so this should be a matrix with only diagonal = 0
    // And all the other elements of the matrix = -INF
    Matrix out = matrixInit(a.size, 1LL<<60);
    for (int i = 0; i < a.size; ++i){
        out.mat[i][i] = 0;
    }

    while (n){
        if (n & 1) out = multiply(out, a);
        a = multiply(a, a);
        n >>= 1;
    }
    return out;
}

typedef struct{
    int x;
    int y;
} Coord;

Coord coord(int x, int y){
    Coord out = {x, y};
    return out;
}

// Ghetto BFS
Coord bfs[1<<16];
int bfsHead;
int bfsTail;

void push(Coord x){ bfs[bfsHead++] = x; }
Coord pop(){ return bfs[bfsTail++]; }
int notEmpty(){ return bfsHead != bfsTail; }
void reset(){ bfsHead = 0; bfsTail = 0; }

char grid[64][64];
int seen[64][64];
int money[64];

void resetSeen(int r, int c){
    for (int i = 0; i <= r; ++i){
        for (int j = 0; j < c; ++j){
            seen[i][j] = 0;
        }
    }
}

int main(){
    // Scan in input
    int r, c, k;
    scanf("%d %d %d", &r, &c, &k);

    for (int i = 0; i < r; ++i){
        for (int j = 0; j < c; ++j){
            scanf(" %c", &grid[i][j]);
        }
    }

    // Boundary condition perhaps...?
    for (int i = 0; i < c; ++i){
        grid[r][i] = '.';
        scanf("%d", &money[i]);
    }

    Matrix matrix = matrixInit(c, 1LL<<60);

    // Simulate the ball dropping in each column
    for (int i = 0; i < c; ++i){
        if (grid[0][i] == 'X') continue;

        reset();
        push(coord(0, i));
        resetSeen(r, c);

        seen[0][i] = 1;

        // We can do this using BFS.
        while (notEmpty()){
            Coord curr = pop();
            int x = curr.x;
            int y = curr.y;

            // Have we reached the bottom yet?
            if (x == r) continue;

            if (grid[x][y] == 'R'){
                int newX = x;
                int newY = y + 1;

                // Out of bounds?
                if (newY >= c) continue;

                // Goes into a wall?
                if (grid[newX][newY] == 'X') continue;

                // Been here before?
                if (seen[newX][newY]) continue;

                seen[newX][newY] = 1;
                push(coord(newX, newY));
            }

            if (grid[x][y] == 'L'){
                int newX = x;
                int newY = y - 1;

                if (newY < 0) continue;
                if (grid[newX][newY] == 'X') continue;
                if (seen[newX][newY]) continue;

                seen[newX][newY] = 1;
                push(coord(newX, newY));
            }

            if (grid[x][y] == '?'){
                for (int k = -1; k < 2; k += 2){
                    int newX = x;
                    int newY = y + k;

                    if (newY < 0) continue;
                    if (grid[newX][newY] == 'X') continue;
                    if (seen[newX][newY]) continue;

                    seen[newX][newY] = 1;
                    push(coord(newX, newY));
                }

            }

            if (grid[x][y] == '.'){
                int newX = x+1;
                int newY = y;

                if (grid[newX][newY] == 'X') continue;
                if (seen[newX][newY]) continue;

                seen[newX][newY] = 1;
                push(coord(newX, newY));
            }
        }

        // Cool which column's scores have we touched?
        for (int j = 0; j < c; ++j){
            if (seen[r][j] != 0) matrix.mat[i][j] = money[j];
        }
    }

    // Ok now we just gotta do matrix multiplication
    // matrix[i][j] is the max score to get from col i to j
    Matrix final = fastExpo(matrix, k);
    long long best = 0;
    for (int i = 0; i < c; ++i){
        for (int j = 0; j < c; ++j){
            best = MAX(best, final.mat[i][j]);
        }
    }

    printf("%lld\n", best);

    return 0;
}

