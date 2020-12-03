// OEIS A001169. I didn't know it was a thing...

#include<stdio.h>

#define MOD 10000

typedef struct {
    int matrix[3][3];
} Matrix;

Matrix init(){
    // Manually assign the stupid initial matrix
    // Wow C is really a small pain eh?
    Matrix a;
    a.matrix[0][0] = 5;
    a.matrix[0][1] = -7;
    a.matrix[0][2] = 4;
    a.matrix[1][0] = 1;
    a.matrix[1][1] = 0;
    a.matrix[1][2] = 0;
    a.matrix[2][0] = 0;
    a.matrix[2][1] = 1;
    a.matrix[2][2] = 0;
    return a;
}

Matrix matmul(Matrix a, Matrix b){
    Matrix out;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            out.matrix[i][j] = 0;
            for (int k = 0; k < 3; ++k){
                out.matrix[i][j] = (out.matrix[i][j] + ((a.matrix[i][k] * b.matrix[k][j]) % MOD) + MOD) % MOD;
            }
        }
    }
    return out;
}

// Matrix fast expo
Matrix fastExpo(Matrix a, int n){
    Matrix out = init();
    while (n){
        if (n&1){
            out = matmul(out,a);
        }
        a = matmul(a, a);
        n >>= 1;
    }

    return out;
}

int solve(){
    // Scan in input
    int n;
    scanf("%d", &n);

    // Guard clauses
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 6;
    if (n == 4) return 19;

    // If n > 5, do the matrix multiplication
    Matrix out = init();
    out = fastExpo(out, n-5);

    // Use n = 2, 3 and 4 values as "seed"
    int ans = (2 * out.matrix[0][2] + 6 * out.matrix[0][1] + 19 * out.matrix[0][0]);
    return ((ans % MOD) + MOD) % MOD;
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    
    for (int i = 1; i <= testcases; ++i){
        printf("Case %d: %d\n", i, solve());
    }

    return 0;
}

