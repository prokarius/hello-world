#include<stdio.h>
#include<stdlib.h>

#define MAX_REPS 3

typedef struct {
    long long values[1005];
    int size;
} Row;

typedef struct {
    Row rows[1005];
    int size;
} Matrix;

int isSame (Row a, Row b) {
    for (int i = 0; i < a.size; ++i){
        if (a.values[i] != b.values[i]) return 0;
    }
    return 1;
}

// Do matrix multiplication
Row multiply(Row row, Matrix matrix){
    Row output;
    output.size = row.size;
    for (int i = 0; i < row.size; ++i){
        output.values[i] = 0;
        for (int j = 0; j < row.size; ++j){
            output.values[i] += row.values[j] * matrix.rows[j].values[i];
        }
    }

    return output;
}

// We will use a randomized algorithm for this
// Note that if A**2 == B, then for all vectors x, A**2x == Bx
// Although there maybe possibility of when A**2x == Bx even though A**2 != B
// So we just need to randomize it enough time. I say we do MAX_REPS times.
void solve(int n){
    Matrix A;
    Matrix B;
    A.size = n;
    B.size = n;

    // Scan in input
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%lld", &A.rows[i].values[j]);
        }
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%lld", &B.rows[i].values[j]);
        }
    }

    // Generate a random row. Do matrix multiplication with both new**2 and output
    for (int i = 0; i < MAX_REPS; ++i){
        Row testRow;
        testRow.size = n;
        for (int j = 0; j < n; ++j){
            testRow.values[j] = rand() % (1<<16);
        }

        Row fromA2 = multiply(multiply(testRow, A), A);
        Row fromB = multiply(testRow, B);

        if (!isSame(fromA2, fromB)){
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    while (n){
        solve(n);
        scanf("%d", &n);
    }
    return 0;
}

