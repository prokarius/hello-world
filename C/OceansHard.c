#include<stdio.h>
#include<string.h>

#define MOD 1000000007

// Set up my matrix class
typedef struct{
    long long mat[11][11];
    int dimension;
} Matrix;

// Builds the matrix to be multiplied.
// F(i,k) number of substrings of length i which ends with the first k bits.
// 1 at row i col j represents a contribution from F(t,j) to F(t+1,i).
Matrix init(char string[]){
    int len = strlen(string);

    // Copy the old string over so that we can compare with it later
    char saved[11];
    for (int i=0; i<len; ++i){
        saved[i] = string[i];
    }

    // Initialise my matrix properly.
    Matrix out;
    out.dimension = len;
    for (int i=0; i<len; ++i){
        for (int j=0; j<len; ++j){
            out.mat[i][j] = 0;
        }
    }

    // For each possible end point.
    for (int i=len-1; i>=0; --i){

        // Check when you add a 0 or 1 to the end of the string. Then do a check
        // to see where the contribution goes.
        for (int b=0; b<2; ++b){
            string[i] = '0'+b;
            for (int j=i+1; j>=0; --j){

                // If the last j digits of the original string is equal to
                // the first j digits of the modified string
                if (strncmp(string+i+1-j, saved, j) == 0){
                    out.mat[j][i] = 1;
                    break;
                }
            }
        }
    }

    // Return that shit
    return out;
}

// Square Matrices can only multiply if they have the same dimensions
Matrix multiply(Matrix a, Matrix b){
    int size = a.dimension;

    // Create a new matrix with the same size.
    Matrix out;
    out.dimension = size;

    // Do matrix multiplication
    for (int r=0; r<size; ++r){
        for (int c=0; c<size; ++c){
            out.mat[r][c] = 0;
            for (int k=0; k<size; ++k){
                out.mat[r][c] = (out.mat[r][c] + a.mat[r][k] * b.mat[k][c]) % MOD;
            }
        }
    }

    // Return the new matrix
    return out;
}

// Returns the sum of the first column.
long long suum (Matrix a){
    long long out = 0;
    for (int i=0; i<a.dimension; ++i){
        out = (out + a.mat[i][0]) % MOD;
    }
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
    if ((expo&1) == 1){
        return multiply(a, fastexpo(square, expo>>1));
    }
    return fastexpo(square, expo>>1);
}

int cod(){
    int N;
    char string[11];
    scanf("%d %s", &N, string);

    // Build the matrix to be exponented
    Matrix multiple = init(string);

    // Multiply
    Matrix end = fastexpo(multiple, N);

    // Sum.
    printf("%lld\n", suum(end));
}

int main(){
    int N;
    scanf("%d", &N);
    while (N--) {cod();}
    return 0;
}
