#include<stdio.h>

typedef struct {
    long long x;
    long long y;
    long long z;
} Row;

typedef struct {
    int size;
    Row rows[3];
} Matrix;

// Row a - Row b
Row subtract(Row a, Row b){
    Row output;
    output.x = a.x - b.x;
    output.y = a.y - b.y;
    output.z = a.z - b.z;
    return output;
}

// Get the distance between two Rows
long long distance(Row a, Row b){
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// To ensure the input row is not the zero row
int notZero (Row row){
    return !(row.x == 0 && row.y == 0 && row.z == 0);
}

// To ensure that the rows are the same
int sameRow (Row curr, Row other){
    return (curr.x == other.x && curr.y == other.y && curr.z == other.z);
}

// Given a 3x3 matrix, calculate determinant.
long long determinant (Matrix matrix){
    Row a = matrix.rows[0];
    Row b = matrix.rows[1];
    Row c = matrix.rows[2];

    long long output = 0;
    output += a.x * b.y * c.z;
    output += a.y * b.z * c.x;
    output += a.z * b.x * c.y;
    output -= a.z * b.y * c.x;
    output -= a.y * b.x * c.z;
    output -= a.x * b.z * c.y;
    return output;
}

long long getDotProduct(Row a, Row b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Check if point c is inbetween a and b, given that they are collinear
int isBetween(Row a, Row b, Row c){
    // First make sure that c is not a or b
    if (sameRow(a, c) || sameRow(b, c)) return 0;

    Row CMinusA = subtract(c, a);
    Row BMinusA = subtract(b, a);

    // Ensure that dot product is positive
    long long dotProduct = getDotProduct(CMinusA, BMinusA);
    if (dotProduct < 0) return 0;

    // Ensure that dotproduct is less than squaredLength
    long long squaredLength = distance(a, b);
    if (dotProduct > squaredLength) return 0;

    return 1;
}

// OK Clearly this is duct tape...
void solve2(Matrix matrix, Row output){
    // First we want to ensure that there even is a solution:
    // So substitute output into row 3 and see if we even have a solution:
    Matrix newMatrix = matrix;
    newMatrix.rows[2] = output;
    int collinear = determinant(newMatrix);
    if (collinear){
        printf("NO\n");
        return;
    }

    // If we are here, output can be formed by some linear combination of the input.

    // OK now the idea is that each Row can be represented as a point in 3D space.
    // The 3 points defines a line. If output lies on the line, we have a solution.
    // What we can do is to check if output ever lies on the line between every
    // pairwise of points. This is can done using dot product.
    if (isBetween(matrix.rows[0], matrix.rows[1], output) ||
        isBetween(matrix.rows[1], matrix.rows[2], output) ||
        isBetween(matrix.rows[2], matrix.rows[0], output)){
        printf("YES\n");
        return;
    }
    printf("NO\n");
}

void solve(Matrix matrix, Row output){
    // 3 cases that we have to solve based on the number of unique rows in Matrix:
    switch (matrix.size){
        // If there is only 1 unique, then we just check if output is the same as
        // that singular row
        case 1:
            {
                printf (sameRow(matrix.rows[0], output) ? "YES\n" : "NO\n");
                return;
            }

        // When there are 2 rows, we need to ensure that output can be reached via
        // a linear combination of the two rows. Hence, add it to the matrix and
        // ensure that the determinant is 0.
        case 2:
            {
                matrix.size++;
                matrix.rows[2] = output;
                int collinear = determinant(matrix);
                if (collinear){
                    printf("NO\n");
                    return;
                }

                // Also we need to ensure that the probability of each dice roll is
                // not 0. This means output cannot be the same as any matrix row.
                if (sameRow(matrix.rows[0], output) || sameRow(matrix.rows[1], output)){
                    printf("NO\n");
                    return;
                }

                printf("YES\n");
                return;
            }

        // Last case: All 3 dice is unique.
        case 3:
            {
                long long originalDet = determinant(matrix);
                
                // If the original determinant is 0... uh oh..
                if (originalDet == 0){
                    solve2(matrix, output);
                    return;
                }

                // Use Cramer's rule here to solve the equation
                // Modify copies of the original matrix
                Matrix newX = matrix;
                Matrix newY = matrix;
                Matrix newZ = matrix;

                newX.rows[0] = output;
                newY.rows[1] = output;
                newZ.rows[2] = output;

                long long detX = determinant(newX);
                long long detY = determinant(newY);
                long long detZ = determinant(newZ);

                // We need to make sure the probabilities sum to 1
                if (detX + detY + detZ != originalDet){
                    printf("NO\n");
                    return;
                }

                // Normalize the outputs so they are positive
                if (originalDet < 0){
                    originalDet *= -1;
                    detX *= -1;
                    detY *= -1;
                    detZ *= -1;
                }

                // Now if any of detX, detY or detZ is not between 0 and originalDet
                // We know we are in trouble
                if (detX <= 0 || detX >= originalDet ||
                    detY <= 0 || detY >= originalDet ||
                    detZ <= 0 || detZ >= originalDet){
                    
                    printf("NO\n");
                    return;
                }
                printf ("YES\n");
                return;
            }
    }
}

int main(){

    // Scan in input and construct the matrix
    Row first, second, third, output;
    scanf("%lld %lld %lld", &first.x, &first.y, &first.z);
    while (notZero(first)){
        Matrix new;
        new.rows[0] = first;
        new.size = 1;
        
        scanf("%lld %lld %lld", &second.x, &second.y, &second.z);
        if (!sameRow(new.rows[0], second)){
            new.rows[1] = second;
            new.size++;
        }

        scanf("%lld %lld %lld", &third.x, &third.y, &third.z);
        for (int i = 0; i <= new.size; ++i){ 
            if (i == new.size){
                new.rows[i] = third;
                new.size++;
            }
            if (sameRow((new.rows[i]), third)){
                break;
            }
        }

        scanf("%lld %lld %lld", &output.x, &output.y, &output.z);
        solve(new, output);

        // Rescan in the first row:
        scanf("%lld %lld %lld", &first.x, &first.y, &first.z);
    }
    return 0;
}
