#include<stdio.h>
#include<math.h>

#define EPSILON 1e-10

typedef struct {
    double dx;
    double dy;
    double slope;
    double distance;
} Segment;

Segment segment(double dx, double dy){
    Segment output;
    output.dx = dx;
    output.dy = dy;
    output.slope = (dy/dx);
    output.distance = sqrt(dy*dy + dx*dx) / 1000; // m -> km zzz...
    return output;
}

Segment roads[10005];

// Math helper functions
double min(double x, double y){
    return (x < y)?(x):(y);
}

double max(double x, double y){
    return (x > y)?(x):(y);
}

void solve(){
    // Scan in input
    double a, b, vmax, f;
    scanf("%lf %lf %lf %lf", &a, &b, &vmax, &f);

    int numSegments;
    scanf ("%d", &numSegments);

    for (int i = 0; i < numSegments; ++i){
        double dx, dy;
        scanf("%lf %lf", &dx, &dy);
        roads[i] = segment(dx, dy);
    }

    // Why should we drive at a constant speed?
    // Suppose we have 2 road segments, and we drive at different speeds
    // Then fuel consumption = a(v1*d1 + v2*d2) + b(s1*d1 + s2*d2)
    // Since we want to maximize fuel use (use all the fuel), we get v1*d1 + v2*d2 = k
    // The time taken is d1/v1 + d2/v2.

    double lo = 0;
    double hi = vmax;

    // v1 = (k - v2d2)/d1 => dv1/dv2 = d2/d1
    // Differentiate time wrt v2 and set dtime/dv2 = 0 for min point:
    // d1/(v1**2) * dv1/dv2 = d2/(v2**2)
    // Substitute dv1/dv2: d1(v1**2) * d2/d1 = d2/(v1**2) = d2/(v2**2)
    // => v1**2 == v2**2
    // FOR ANY 2 SECTIONS, WE SHOULD DRIVE AT THE SAME SPEED!

    // Now do Binary search.
    // If we have fuel left over => We are going too slow
    // => we can afford to use more fuel => FASTER
    while (hi - lo > EPSILON){
        double mid = (hi+lo) / 2;
        double fuelUsed = 0;
        for (int i = 0; i < numSegments; ++i){
            fuelUsed += max(0, roads[i].distance * (a*mid + b*roads[i].slope));
        }

        // If we used too much fuel, slow down the car
        if (fuelUsed > f) hi = mid;
        else lo = mid;
    }

    // If we crawl and still have no fuel, give up
    if (lo < EPSILON){
        printf("IMPOSSIBLE\n");
        return;
    }

    // If not, find the amount of time needed
    // Rememebr that if we are going downhill, we 
    double timeNeeded = 0;
    for (int i = 0; i < numSegments; ++i){
        double speed = max(lo, min(vmax, -b*roads[i].slope/a));
        timeNeeded += roads[i].distance / speed;
    }

    printf("%.9lf\n", timeNeeded);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}
