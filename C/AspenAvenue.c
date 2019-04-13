#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MIN(x, y) (x<y)?(x):(y)

double trees[2005];
double dp[1005][1005];
double dist;
double length, width;

// cmp func for qsort
int cmpfunc(const void *a, const void *b){
    return *(double *) a > *(double *) b;
}

// Function for computing the distance given the tree number
double cost(int treenum, int location, int left){
    // height is given by the differnece in the current location of
    // the tree and where the tree is supposed to be at.
    double h = (location * dist) - trees[treenum];
    double w = left*width;
    return hypot(h, w);
}

int main(){
    int n;

    // Scan in input
    scanf("%d %lf %lf", &n, &length, &width);

    for (int i = 0; i < n; ++i){
        scanf("%lf", &trees[i]);
    }

    // The distance between the n trees contains n-1 chunks.
    dist = length / (n/2-1);

    // Sort the trees
    qsort(trees, n, sizeof(double), cmpfunc);

    // Initialise the dp state
    // dp[a][b] contains the minimum distance to plant a trees on the
    // left and b trees on the right.
    dp[0][0] = 0;

    // Calculate the cost of planting all the trees on the left or on the right only.
    for (int i = 0; i < n/2; ++i){
        dp[i+1][0] = dp[i][0] + cost(i, i, 0);
    }

    for (int i = 0; i < n/2; ++i){
        dp[0][i+1] = dp[0][i] + cost(i, i, 1);
    }

    // Run bottom up dp.
    // This will be the minimum of putting the current tree (number a + b)
    // in the left hole, or the right hole
    for (int i = 1; i <= n/2; ++i){
        for (int j = 1; j <= n/2; ++j){
            int curr = i+j-1;
            double left = 
            dp[i][j] = cost(curr, i-1, 0) + dp[i-1][j];
            double right = cost(curr, j-1, 1) + dp[i][j-1];
            dp[i][j] = MIN(left, right);
        }
    }

    // Print the final answer
    printf("%lf\n", dp[n/2][n/2]);

    return 0;
}
