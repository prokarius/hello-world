#include<stdio.h>
#include<stdlib.h> 

#define MOD 1000000007

typedef struct {
    long long values[4][4];
} Matrix;

// This matrix is the cowless matrix
Matrix cowless = {
    {{1,1,0,0}, {1,1,1,0}, {0,1,1,1}, {0,0,1,1}}
};

// And we need an Identity matrix too
Matrix identity = {
    {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}}
};

Matrix makeCowMatrix(Matrix oldMatrix, int cowRow){
    for (int i = 0; i < 4; ++i){    
        oldMatrix.values[i][cowRow] = 0;
    }
    return oldMatrix;
}

// Multiplies 2 matrices together
Matrix multiply(Matrix a, Matrix b){
    Matrix out = {
        {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}
    };
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            for (int k = 0; k < 4; ++k){
                out.values[i][j] = (out.values[i][j] + a.values[i][k]*b.values[k][j]) % MOD;
            }
        }
    }
    return out;
}

// Does fastexpo of a given matrix
Matrix fastexpo (Matrix a, long long power){
    if (power == 0){
        return identity;
    }
    if (power == 1){
        return a;
    }
    if (power & 1L){
        return multiply(a, fastexpo(multiply(a, a), power>>1));
    }
    return fastexpo(multiply(a, a), power>>1);
}

// This will keep the list of cows.
typedef struct {
    long long x;
    long long y;
} Cow;

// We need to sort the cows. Use qsort
int cmpfunc(const void* a, const void* b){
    Cow first = *(Cow *)a;
    Cow second = *(Cow *)b;

    return first.x > second.x;
}

int main(){
    long long K, N;
    Cow cows[105];

    // Scan in input
    scanf("%lld %lld", &K, &N);
    for (int i = 0; i < N; ++i){
        Cow newCow;
        scanf("%lld %lld", &newCow.y, &newCow.x);
        newCow.y--;
        cows[i] = newCow;
    }

    // Sort the cows in order
    qsort(cows, N, sizeof(Cow), cmpfunc);

    // We will do Fast expo between cows.
    // Suppose there is a cow at x=5 and x=20.
    // I can do cowless**4 * cowmatrix * cowless**14 * cowmatrix
    Matrix base = identity;
    long long currIndex = 1;
    int cowIndex = 0;
    while (cowIndex < N){
        long long spacing = (cows[cowIndex].x - currIndex) - 1;
        currIndex = cows[cowIndex].x;
        base = multiply(base, fastexpo(cowless, spacing));

        // Make the cow matrix
        Matrix cowful = cowless;
        while (cowIndex < N){
            if (currIndex != cows[cowIndex].x){
                break;
            }
            cowful = makeCowMatrix(cowful, cows[cowIndex].y);
            cowIndex++;
        }

        // And multiply it
        base = multiply(base, cowful);
    }

    base = multiply(base, fastexpo(cowless, K-currIndex));

    printf("%lld\n", base.values[0][0]);
}
