#include<stdio.h>
#include<math.h>

#define MIN(x, y) (x < y)?(x):(y)

// Is it because of floating point precision errors?
#define EPSILON 1e-10
#define EPSILON2 1e-4
#define INF 1e16;

int n;
int xpos[16];
int ypos[16];
int time[16];

// We cache the speeds so we don't need to recalculate them each time
double speed[20];

// This will be my TSP dp array
// tsp[visitedBitMask][lastMiceVisited] = timeTaken to reach said mice
double tsp[1<<16][16];

// Function to calculate the time it takes to get from (x, y) to the next mice.
double timeCost(int x, int y, int nextMice, double currTime, double speed){
    double dx = x - xpos[nextMice];
    double dy = y - ypos[nextMice];
    double nextTime = currTime + hypot(dx, dy) / speed;

    // Check if the mouse has already ducked.
    if (nextTime <= time[nextMice] + EPSILON){
        return nextTime;
    }
    else {
        return INF;
    }
}

// We are going to do TSP for the given speed, see if we hit all the mice.
int TSP(double currSpeed){

    // Start by resetting the DP array
    for (int i = 0; i < (1<<n); ++i){
        for (int j = 0; j < n; ++j){
            tsp[i][j] = INF;
        }
    }

    // The cost of getting to the first mice is then easy
    for (int i = 0; i < n; ++i){
        tsp[1 << i][i] = timeCost(0, 0, i, 0, currSpeed);
    }

    // Now we do the TSP.
    // For each possible bitmask
    for (int mask = 1; mask < (1<<n); ++mask){

        // Count the number of bits that are on.
        int numbits = 0;
        int temp = mask;
        while (temp){
            if (temp & 1) numbits ++;
            temp /= 2;
        }

        double newSpeed = currSpeed * speed[numbits];

        // Now, for all possible start points (that we have visited)
        // (Note that if 1<<i is not in mask, this is an invalid state.
        for (int i = 0; i < n; ++i){
            if ((mask & (1 << i)) == 0) continue;

            // And for all possible end points (that we have not visited)
            for (int j = 0; j < n; ++j){
                if ((mask & (1 << j)) != 0) continue;

                // Try running i to j, and taking the tsp.
                int newMask = mask ^ (1 << j);
                double nextTime = timeCost(xpos[i], ypos[i], j, tsp[mask][i], newSpeed);
                tsp[newMask][j] = MIN(tsp[newMask][j], nextTime);
            }
        }
    }

    // Check if we can visit everyone (bitmask = 11...1)
    double out = INF;
    for (int i = 0; i < n; ++i){
        out = MIN(out, tsp[(1<<n)-1][i]);
    }

    return out + EPSILON < INF;
}

int main(){
    // Scan in input
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d %d %d", &xpos[i], &ypos[i], &time[i]);
    }

    double speedFactor;
    scanf("%lf", &speedFactor);

    // Cache the speed factors.
    speed[0] = 1;
    for (int i = 0; i <= n; ++i){
        speed[i+1] = speed[i] * speedFactor;
    }

    // Since we are supposed to find the speed, we will simply binsearch
    double lo = 0;
    double hi = 10000000;

    while (hi - lo > EPSILON2){
        double mid = (lo + hi) / 2;
        if (TSP(mid)){
            hi = mid;
        }
        else {
            lo = mid;
        }
    }

    // Print the average of the speeds
    printf("%lf\n", (lo + hi) / 2);

    return 0;
}
