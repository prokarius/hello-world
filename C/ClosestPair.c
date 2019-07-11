// SHAMEFULLY REFERENCED FROM GEEK FOR GEEKS :<
// But the geek for geeks version requires the x coords to be distinct. Worthless!

#include<stdio.h>
#include<stdlib.h>

double MIN(double x, double y){
    return (x < y)?(x):(y);
}

double ABS(double x){
    return (x > 0)?(x):(-x);
}

typedef struct{
    double x;
    double y;
} Point;

// Constructor
Point point(double x, double y){
    Point output;
    output.x = x;
    output.y = y;
    return output;
}

// I need to save the result somehow...
typedef struct {
    Point first;
    Point second;
    double distance;
} DoublePoint;

DoublePoint doublePoint(Point first, Point second, double distance){
    DoublePoint out;
    out.first = first;
    out.second = second;
    out.distance = distance;
    return out;
}

// Global Variables
int n;
Point allPointsX[131072];
Point allPointsY[131072];

// Distance function. Note that we delay the sqrt to the end to save computation.
double distance(Point a, Point b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}

// We need to sort points by x and y values. Create cmpfuncs
int cmpfuncX(const void* a, const void* b){
    Point first = *(Point*) a;
    Point second = *(Point*) b;
    return (first.x > second.x) - (second.x > first.x);
}

int cmpfuncY(const void* a, const void* b){
    Point first = *(Point*) a;
    Point second = *(Point*) b;
    return (first.y > second.y) - (second.y > first.y);
}

// When there is less than 3 points, we will use bruteforce. No point divide and conquering.
DoublePoint bruteForce(Point points[], int size){
    Point bestPointA, bestPointB;
    double best = 1LL << 62;
    for (int i = 0; i < size - 1; ++i){
        for (int j = i + 1; j < size; ++j){
            double dist = distance(points[i], points[j]);
            if (dist < best){
                best = dist;
                bestPointA = points[i];
                bestPointB = points[j];
            }
        }
    }
    return doublePoint(bestPointA, bestPointB, best);
}

DoublePoint closest(Point points[], int numPoints){
    // If there is 2 or 3 points, just brute that shit.
    if (numPoints <= 3){
        return bruteForce(points, numPoints);
    }

    // Find the midpoint point
    int mid = numPoints/2;
    Point midPoint = points[mid];
    double midX = midPoint.x;

    // Divide and conquer
    DoublePoint minLeft = closest(&points[0], mid);
    DoublePoint minRight = closest(&points[mid], numPoints - mid);
    DoublePoint best;
    double bestDist;

    if (minLeft.distance < minRight.distance){
        best = minLeft;
        bestDist = minLeft.distance;
    }
    else {
        best = minRight;
        bestDist = minRight.distance;
    }

    // Get a list of all the points in the strip that is at most y = bestSoFar away
    // from the current mid points
    Point* strip = (Point*) malloc(numPoints * sizeof(Point));
    int numPointsInStrip = 0;

    for (int i = 0; i < numPoints; ++i){
        if (ABS(points[i].x - midX) < bestDist){
            strip[numPointsInStrip] = points[i];
            numPointsInStrip++;
        }
    }

    // Sort them by y value, we will be doing a "sliding window"
    qsort(strip,numPointsInStrip, sizeof(Point), cmpfuncY);

    // So now for each point, we look ahead to see which points may potentially be
    // the best points. If the y distance is too far away, we just give up.
    for (int i = 0; i < numPointsInStrip; ++i){
        for (int j = i+1; j < numPointsInStrip && (strip[j].y - strip[i].y < bestDist); ++j){
            double dist = distance(strip[i], strip[j]);
            if (dist < bestDist){
                best.first = strip[i];
                best.second = strip[j];
                bestDist = dist;
            }
        }
    }
    best.distance = bestDist;
    free(strip);
    return best;
}

void solve(){
    // Scan in input
    for (int i = 0; i < n; ++i){
        double x, y;
        scanf("%lf %lf", &x, &y);
        allPointsX[i] = point(x, y);
        allPointsY[i] = allPointsX[i];
    }

    // Sort the points and then call the recursive solve function
    qsort(allPointsX, n, sizeof(Point), cmpfuncX);
    qsort(allPointsY, n, sizeof(Point), cmpfuncY);

    DoublePoint best = closest(allPointsX, n);

    printf("%lf %lf %lf %lf\n", best.first.x, best.first.y, best.second.x, best.second.y);
}

int main(){
    // Scan in input
    scanf("%d", &n);

    while (n){
        solve();
        scanf("%d", &n);
    }

    return 0;
}

