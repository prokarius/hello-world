#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) (x > y)?(x):(y)

typedef struct {
    int x;
    int y;
} Point;

// For use in qsort
int cmpfunc(const void* a, const void* b){
    Point first = *(Point*) a;
    Point second = *(Point*) b;

    if (first.x == second.x){
        return first.y - second.y;
    }
    return first.x - second.x;
}

// Returns positive if abc forms a counter clockwise turn
int ccw (Point a, Point b, Point c){
    return ((b.x - a.x) * (c.y - a.y)) -
           ((b.y - a.y) * (c.x - a.x));
}

// points array stores my input, hull stores the convex hull
Point points[1005];
Point hull[2005];

// Gets the area of the triangle given by abc.
int getTriangleArea(Point a, Point b, Point c){
    return ((a.x*b.y) + (b.x*c.y) + (c.x*a.y)) -
           ((a.x*c.y) + (b.x*a.y) + (c.x*b.y));
}

// Gets the area of the quadrilateral given by abcd.
// Do this by splitting into 2 triangles
int getArea(Point a, Point b, Point c, Point d){
    return getTriangleArea(a, b, c) + getTriangleArea(a, c, d);
}

int process(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    // Sort the points and prepare for monotone chain
    qsort(points, n, sizeof(Point), cmpfunc);
    int hullsize = 0;

    // Lower hull
    for (int i = 0; i < n; ++i){
        while (hullsize > 1 &&
               ccw(hull[hullsize-2], hull[hullsize-1], points[i]) < 0){
            --hullsize;
        }

        hull[hullsize++] = points[i];
    }

    // Upper hull
    int anchor = hullsize + 1;
    for (int i = n-2; i >= 0; --i){
        while (hullsize >= anchor &&
               ccw(hull[hullsize-2], hull[hullsize-1], points[i]) < 0){
            --hullsize;
        }
        hull[hullsize++] = points[i];
    }

    // Get rid of the repeated point
    hullsize--;

    // If we don't even have 4 points, give up
    if (hullsize < 4){

        // Oh unless we have 3 points, then we can make a triangle. Probably
        if (hullsize != 3) return 0;
        return getTriangleArea(hull[0], hull[1], hull[2]);
    }

    // Simulate looping around the convex hull
    for (int i = 0; i < hullsize; ++i){
        hull[hullsize + i] = hull[i];
    }

    int best = 0;

    // For all possible values of a, we find the largest triangle
    for (int a = 0; a < hullsize-2; ++a){
        int innerLoopBest = 0;
        int b = a+1;
        int d = a+3;

        // We allow c to rotate through all possible hullsizes
        for (int c = a+2; c < a + hullsize -1; ++c){
            int oldArea = getArea(hull[a], hull[b], hull[c], hull[d]);
            int newArea;

            // Save the current best
            innerLoopBest = oldArea;

            // If we can scoot b, we try to scoot b.
            while (b + 1 < c){
                newArea = getArea(hull[a], hull[b+1], hull[c], hull[d]);
                if (newArea < oldArea) break;

                // Oh we can scoot b! So we scoot it over
                ++b;
                innerLoopBest = newArea;
                oldArea = newArea;
                newArea = getArea(hull[a], hull[b+1], hull[c], hull[d]);
            }

            // If we can scoot d, we try to scoot d.
            while (d + 1 < a + hullsize){
                newArea = getArea(hull[a], hull[b], hull[c], hull[d+1]);
                if (newArea < oldArea) break;

                // Oh we can scoot d! So we scoot it over
                ++d;
                innerLoopBest = newArea;
                oldArea = newArea;
                newArea = getArea(hull[a], hull[b], hull[c], hull[d+1]);
            }

            // Save the best area we have seen so far
            best = MAX(best, innerLoopBest);
        }
    }

    return best;
}

int main(){
    int testcases;
    scanf ("%d", &testcases);
    while (testcases--){
        int area = process();
        printf("%d%s\n", area/2, area%2?".5":"");
    }
    return 0;
}
