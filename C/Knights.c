#include<stdio.h>
#define MOD 1000000009

// Defines a matrix structure
typedef struct{
    int dimension;
    long long mat[81][81];
} Matrix;

// Returns if a number i is a valid combination in n.
// Why 33 and 12? Because:
// This is 33 and this is 12
//     100           001
//     001           100
// If any of these patterns turn up, it's an invalid config
// The same logic can be used for n == 4
int isValid (int i, int n){
    if (n < 3) return 1;
    if (n == 3) return !((33 == (i & 33)) || (12 == (i & 12)));
    if (n == 4) return !((20 == (i & 20)) || (40 == (i & 40)) ||
                         (65 == (i & 65)) || (130 == (i & 130)));
}

// This checks if 2 rows away the states are still valid
int isValid2Rows (int i, int n){
    if (n < 2) return 1;
    if (n == 2) return !((6 == (i & 6)) || (9 == (i & 9)));

    if (n == 3) return !((10 == (i & 10)) || (17 == (i & 17)) ||
                         (20 == (i & 20)) || (34 == (i & 34)));

    if (n == 4) return !((18 == (i & 18)) || (33 == (i & 33)) ||
                         (36 == (i & 36)) || (66 == (i & 66)) ||
                         (72 == (i & 72)) || (132 == (i & 132)));
}

// Initialises a matrix which is n wide.
Matrix init (int n){
    Matrix out;
    int bitmask = (1 << (2*n)) - 1;
    int shortbitmask = (1 << n) - 1;

    // This is a mapping from a bitmask to configuration number
    // Valid is the reverse mapping.
    int valid[256];
    int configuration[256];
    int configHead = 0;

    for (int i = 0; i < bitmask + 1; ++i){
        if (isValid(i, n)){
            configuration[i] = configHead;
            valid[configHead++] = i;
        }
    }

    // Anyways, the dimension of the output matrix is just the number of valid
    // configurations there are, that is just the value of configHead
    out.dimension = configHead;

    // Initialise the matrix to all 0s
    for (int r = 0; r < configHead; ++r){
        for (int c = 0; c < configHead; ++c){
            out.mat[r][c] = 0;
        }
    }

    // OK so now that we know which combis are valid, we will figure out which ones
    // can lead to the other.
    for (int i = 0; i < configHead; ++i){
        int number = valid[i];

        // Note that for each of the states, we consider 2 rows at a time, but we
        // only advance by 1 row. In other words, the second row becomes the first.
        int next = number >> n;

        // Then there is only (1 << n) - 1 other combis,
        // Initalise it outside the loop to help it save time
        for (int j = 0; j < shortbitmask + 1; ++j){
            int nextnumber = next + (j << n);
            int row2number = (number & shortbitmask) + (j << n);
            // Then we check if the resulting number is valid
            // And if it is, we push 1 into the matrix.
            if (isValid(nextnumber, n) && isValid2Rows(row2number, n)){
                int location = configuration[nextnumber];
                out.mat[i][location] = 1;
            }
        }
    }

    // Finally, we return the matrix we hacked together
    return out;
}

// Multiplies matrix a and b together
Matrix matmul(Matrix a, Matrix b){
    // Initialise our output matrix
    int size = a.dimension;
    Matrix out;
    out.dimension = size;

    // Do the actual multiplication
    for (int r = 0; r < size; ++r){
        for (int c = 0; c < size; ++c){
            out.mat[r][c] = 0;
            for (int k = 0; k < size; ++k){
                out.mat[r][c] = (out.mat[r][c] + a.mat[r][k] * b.mat[k][c]) % MOD;
            }
        }
    }

    return out;
}

// Does matrix fast expo
Matrix fastexpo (Matrix a, int expo){
    // Return the matrix if the exponent is just 1
    if (expo == 1) return a;

    // If not, do fast expo
    Matrix squared = matmul(a, a);
    if ((expo & 1) == 1) return matmul(a, fastexpo(squared, expo >> 1));
    return fastexpo(squared, expo >> 1);
}

// Returns the sum of all the elements of a given matrix a
long long summatrix (Matrix a){
    long long out = 0;
    for (int i = 0; i < a.dimension; ++i){
        for (int j = 0; j < a.dimension; ++j){
            out = (out + a.mat[i][j]) % MOD;
        }
    }
    return out;
}

int main(){
    int n, H;
    scanf("%d %d", &n, &H);

    // If the height is 1, well it'll just be a binary string...
    if (H == 1){
        printf("%d\n", 1<<n);
        return 0;
    }

    // Initialise the matrix for n knights
    Matrix initial = init(n);

    // If H == 2, then the number of valid configs is the dimension of the matrix.
    if (H == 2){
        printf("%d\n", initial.dimension);
        return 0;
    }

    // Then do fast expo for H columns
    Matrix final = fastexpo(initial, H-2);

    // Lastly, sum up the number for each matrix
    printf("%lld\n", summatrix(final));

    return 0;
}
