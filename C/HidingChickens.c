#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double MIN(double x, double y){
    return (x < y)?(x):(y);
}

double MAX(double x, double y){
    return (x > y)?(x):(y);
}

typedef struct{
    double x;
    double y;
} Coordinate;

Coordinate coordinate(double x, double y){
    Coordinate output;
    output.x = x;
    output.y = y;
    return output;
}

double distance(Coordinate first, Coordinate second){
    double dx = first.x - second.x;
    double dy = first.y - second.y;
    return sqrt(dx*dx + dy*dy);
}

Coordinate chickens[24];

int main(){
    // Scan in input
    int n;
    double x, y;

    scanf ("%lf %lf %d", &x, &y, &n);
    Coordinate start = coordinate(x, y);

    for (int i = 0; i < n; ++i){
        double x, y;
        scanf("%lf %lf", &x, &y);
        chickens[i] = coordinate(x, y);
    }

    // Initialize dp array
    double* dp = (double*) malloc((1<<n) * sizeof(double));

    dp[0] = 0;

    for (int mask = 1; mask < (1<<n); ++mask){
        // Reset the DP entry
        dp[mask] = 1e50;

        // Get your first chicken!
        for (int i = 0; i < n; ++i){

            // Continue if we have visited there before
            if (~mask & (1 << i)) continue;

            // Go to the chicken and back
            dp[mask] = MIN(dp[mask], dp[mask ^ (1<<i)] + 2*distance(chickens[i], start));

            // Get your second chicken!
            for (int j = 0; j < n; ++j){

                // Break if we are considering the same point, or if we have visited
                if (i == j || ~mask & (1 << j)) continue;

                // Go to the chicken, then again, then back
                dp[mask] = MIN (dp[mask], dp[mask ^ (1 << i) ^ (1 << j)] +
                        distance(chickens[i], chickens[j]) +
                        distance(chickens[i], start) +
                        distance(chickens[j], start));
            }
        }
    }

    // Oh wtf trick question, the fox doesn't need to return to the roost!
    double best = -1;
    for (int i = 0; i < n; ++i){
        best = MAX(best, distance(chickens[i], start));
    }

    printf("%lf\n", dp[(1<<n)-1] - best);

    return 0;
}

