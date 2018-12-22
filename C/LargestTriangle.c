#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) (x>y)?(x):(y)
#define MOD 2800001

typedef struct{
    int x;
    int y;
} Point;

Point points[5005];
int numhash;

// Sigh, let's just mod away the points.
Point hash[MOD];
int visited[MOD];

int hashLocations[5005];

// We might have repeats, so if we see a repeat, just return 1
int samePoint(Point a, Point b){
    return (a.x == b.x && a.y == b.y);
}

void push(Point inputPoint){
    // Calculate the hash. Let's just do x + y % MOD
    int hashed = (MOD + (inputPoint.x + inputPoint.y) % MOD) % MOD;

    // Find a spot to plop the point
    while (visited[hashed] != 0){

        // If we have seen this point before, it is useless!
        if (samePoint(hash[hashed], inputPoint)){
            return;
        }
        // Scoot the hash table one unit
        else {
            hashed = (hashed + 1) % MOD;
        }
    }

    // Plot the point if we can
    hash[hashed] = inputPoint;
    visited[hashed] = 1;
    points[numhash++] = inputPoint;

}

// We are gonna need to calculate the area of a triangle.
// Incidentally, this returns twice the area. Nyeeh. Divide by 2 later.
long long area(Point a, Point b, Point c){
    return (long long)a.x*b.y + (long long)b.x*c.y + (long long)c.x*a.y -
          ((long long)a.x*c.y + (long long)b.x*a.y + (long long)c.x*b.y);
}

// Define a cmpfunc for the sorting of the points
// This will sort the points by x, then by y.
int cmpfunc(const void* a, const void* b){
    Point first = *(Point*) a;
    Point second = *(Point*) b;

    if (first.x == second.x){
        return first.y - second.y;
    }
    return first.x - second.x;
}

// This is for generating the convex hull
// ccw returns +ve for counter-clockwise, -ve for clockwise, 0 for collinear
long long ccw(Point a, Point b, Point c){
    return ((long long)b.x - a.x)*((long long)c.y - a.y) -
           ((long long)b.y - a.y)*((long long)c.x - a.x);
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        Point newPoint;
        scanf("%d %d", &newPoint.x, &newPoint.y);
        push(newPoint);
    }

    // Check if we even have enough points:
    if (numhash < 3){
        printf("0\n");
        return 0;
    }

    // Sort the points and prepare to do monotone chain
    qsort(points, numhash, sizeof(Point), cmpfunc);
    n = numhash;

    // k stores the number of points in the hull
    // hull stores the actual hull
    int k = 0;
    Point hull[10005];

    // Make the lower hull:
    for (int i = 0; i < n; ++i){

        // If we don't have enough points in our hull
        // or we are adding the same point to the hull
        // or the next point we add will make the hull go backwards
        // Remove the previous point.
        while (k >= 2 &&
               ccw(hull[k-2], hull[k-1], points[i]) <= 0){
            --k;
        }

        // Add the point to our hull
        hull[k++] = points[i];
    }

    // Do the same thing for the upperhull
    // t is like our sentinel value. This marks the start of the upper hull.
    int t = k + 1;

    // Traverse from right to left this time.
    for (int i = n - 2; i >= 0 ; --i){
        while (k >= t &&
               ccw(hull[k-2], hull[k-1], points[i]) <= 0){
            --k;
        }
        hull[k++] = points[i];
    }

    // Yay~! We now have our convex hull stored in hull.
    // Incidentally the size of the convex hull = k-1
    // Why didn't I call it "size" from the start? I also don't know... lol
    int size = k-1;
    long long best = -1;

    // Check that the size of the hull is at least 3.
    if (size < 3){
        printf ("0\n");
        return 0;
    }

    for (int i = 0; i < size; ++i){
        hull[size + i] = hull[i];
    }

    // For each starting point A, do sliding window method:
    // Pseudo code adapted from stackoverflow

    // For each value of a, set b and c as a+1 and a+2.
    for (int a = 0; a < size - 2; ++a){
        long long innerLoopBest = -1;
        int c = a+2;

        // We keep scooting c and b as the area of the triangle increases.
        for (int b = a+1; b < size+a-1; ++b){

            // Also save the results. To save computation
            long long oldArea = area(hull[a], hull[b], hull[c]);
            long long newArea = area(hull[a], hull[b], hull[c+1]) ;
            innerLoopBest = oldArea;
            while (oldArea <= newArea){
                c = c+1;
                innerLoopBest = newArea;
                oldArea = newArea;
                newArea = area(hull[a], hull[b], hull[c+1]);
            }

            // Now check if by scooting b we can increase the size
            best = MAX(best, innerLoopBest);
        }
    }

    // Print the output
    printf("%lld.%s\n", best/2, best%2?"5":"0");

    return 0;
}
