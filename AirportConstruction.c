#include<stdio.h>

#define MAX(x, y) (x > y)?(x):(y)
#define MIN(x, y) (x < y)?(x):(y)

typedef struct {
    double x;
    double y;
} Point;

Point points[205];
int n;

/* This entire section is ripped off Geek for Geeks */

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
int onSegment(Point p, Point q, Point r){
    if (q.x <= MAX(p.x, r.x) && q.x >= MIN(p.x, r.x) &&
        q.y <= MAX(p.y, r.y) && q.y >= MIN(p.y, r.y))
       return 1;

    return 0;
}

// Function that takes 2 line segments and returns if they intersect each other
int intersect(Point p1, Point q1, Point p2, Point q2){
    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4){
        return 1;
    }

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return 1;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return 1;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return 1;

     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return 1;

    return 0; // Doesn't fall in any of the above cases
}

// Given 2 line segments, returns if they intersect
// This method gets the longest line that can be formed using points at index a and b
// If the line intersects an already existing line, we return 1e200.
// Precondition: a and b are not the same point.
double longestLine(int a, int b){
    double best = 1e200;

    // For each line that we have, on the island, check where it intersects all
    // the other edges of the island.
    for (int i = 0; i < n; ++i){

        // If it intersects another line, we don't just to conclusions first
        if (intersect(points[a], points[b], points[i], points[i+1])){

            // See if the line in consideration intersects at the end points
            if (a == i || a == i+1 || b == i || b== i+1){


            }

            // Else, we just return 1e200
            else {
                return 1e200;
            }
        }

    }

    return best;
}

int main(){
    // Scan in input
    scanf ("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    // So that it's easier to compare the line segments
    points[n] = points[0];
    points[n+1] = points[1];

    double best = 1e200;

    // For each pair of points see what's the longest line that can be formed
    // 2 for loops here takes O(n2)
    // Each call to longest line takes O(n) since we are looping through all
    // possible line segments to check the intersection.
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            double out = longestLine(i, j);
            best = MAX(best, out);
        }
    }

}
