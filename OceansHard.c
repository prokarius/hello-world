#include<stdio.h>
#include<string.h>

#define MOD 1000000007

// Set up my matrix class
typedef struct{
    long long mat[10][10];
    int dimension;
} Matrix

// Square Matrices can only multiply if they have the same dimensions
Matrix multiply(Matrix a, Matrix b){
    int size = a.dimension;

    // Create a new matrix with the same size.
    Matrix out;
    out.dimension = size;

    // Do matrix multiplication
    for (int r=0; i<size; ++r){
        for (int c=0; j<size; ++c){
            out.mat[i][j] = 0;
            for (int k=0; k<size; ++k){
                out.mat[r][c] = (out.mat[r][c] + a.mat[r][k] * b.mat[k][c]) % MOD;
            }
        }
    }

    // Return the new matrix
    return out;
}

// Returns a**expo
Matrix fastexpo(Matrix a, int expo){
    // Exponent = 1
    if (expo == 1){
        return a;
    }

    // Else recursively fast expo
    Matrix square = multiply(a, a);
    if (expo&1 == 1){
        square = multiply(square, a);
    }

    return fastexpo(square, expo>>1);
}

int cod(){
    int N, K;
    char string[11];
    scanf ("%d %s", &N, string);

    // Save the length of the string
    int len = strlen(string);

    // Build the matrix to be exponented
    

int main()
    int N;
    scanf("%d", &N);
    while (N--) {cod();}
    return 0;
}
