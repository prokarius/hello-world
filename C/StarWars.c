#include<stdio.h>

#define MIN(x,y) (x<y)?(x):(y)
#define MAX(x,y) (x>y)?(x):(y)
#define EPSILON 1e-8

double pos;
double positions[1005][4];
double powers[1005];

// Global so that binsearch can access
int n;

// Resets all our arrays
void reset(){
    for (int i = 0; i < 1005; ++i){
        powers[i] = 0;
        for (int j = 0; j < 3; ++j){
            positions[i][j] = 0;
        }
    }
}

double binsearch(double lo, double hi){
    double mid = (hi - lo) / 2 + lo;

    // If we are at the end of bin search, return mid
    if (hi - lo < EPSILON) return mid;

    int flag = 0;
    double excess[8];

    // Initialise the excess array to INF
    for (int i = 0; i < 4; ++i){
        excess[i] = 1e200;
        excess[i+4] = -1e200;
    }

    // Rearrange the equation to get the following:
    // x + y + z <= xi + yi + zi + pi*ANS
    // x + y + z <= xi + yi + zi - pi*ANS
    // The same can be said for the other 3 quadrants

    // Then we can rearrange to get 1 equation for each pair of opposing quadrants:
    // xi + yi + zi - pi*ANS <= x + y + z <= xi + yi + zi + pi*ANS

    // Yes code repetition, I can't think of a better way..
    for (int i = 0; i < n; ++i){
        double Q1 = positions[i][0] + positions[i][1] + positions[i][2];
        double Q2 = positions[i][0] + positions[i][1] - positions[i][2];
        double Q3 = positions[i][0] - positions[i][1] + positions[i][2];
        double Q4 = - positions[i][0] + positions[i][1] + positions[i][2];

        double Q1A = Q1 + powers[i] * mid;
        double Q1B = Q1 - powers[i] * mid;

        double Q2A = Q2 + powers[i] * mid;
        double Q2B = Q2 - powers[i] * mid;

        double Q3A = Q3 + powers[i] * mid;
        double Q3B = Q3 - powers[i] * mid;

        double Q4A = Q4 + powers[i] * mid;
        double Q4B = Q4 - powers[i] * mid;

        // So here's the smart bit. We count how much excess we have for each direction
        // If the number is negative, it means we require more power in that direction

        // Note that we take MAX when subtracting the power, and MIN when adding
        // This is because in QxAs, we are looking for the MINIMUM excess in the
        // direction, and in QxBs, we are looking for MAXIMUM deficit
        excess[0] = MIN(excess[0], Q1A);
        excess[1] = MIN(excess[1], Q2A);
        excess[2] = MIN(excess[2], Q3A);
        excess[3] = MIN(excess[3], Q4A);
        excess[4] = MAX(excess[4], Q1B);
        excess[5] = MAX(excess[5], Q2B);
        excess[6] = MAX(excess[6], Q3B);
        excess[7] = MAX(excess[7], Q4B);
    }

    // If for each quadrant, the residue is more than the excess on the other,
    // that means we will not be able to scoot the transmitter in anyway so that
    // it would be able to compensate for this excess / deficit 
    for (int j = 0; j < 4; ++j){
        if (excess[j] < excess[j+4]){
            flag = 1;
        }
    }

    // So if the flag has been turned on
    if (flag){
        return binsearch(mid, hi);
    }
    return binsearch(lo, mid);
}

void solve(int casenum){
    // Scan in input
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%lf %lf %lf %lf", &positions[i][0], &positions[i][1], &positions[i][2], &powers[i]);
    }

    // Do binary search
    printf("Case #%d: %.8lf\n", casenum, binsearch(0, 1e9));
}

int main(){
    int testcases;
    int casenum = 0;
    scanf("%d", &testcases);

    while (++casenum <= testcases){
        solve(casenum);
    }

    return 0;
}
    
