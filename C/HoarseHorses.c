#include<stdio.h>

typedef struct{
    long long x;
    long long y;
} Point;

Point point(long long x, long long y){
    Point output;
    output.x = x;
    output.y = y;
    return output;
}

typedef struct{
    Point start;
    Point end;
} Line;

Line line(int sx, int sy, int ex, int ey){
    Line output;
    output.start = point(sx, sy);
    output.end = point(ex, ey);
    return output;
}

// min and max functions
long long min(x, y){
    return (x < y)?(x):(y);
}

long long max(x, y){
    return (x > y)?(x):(y);
}

// Shamelessly ripped off geek for geeks
int onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return 1;

    return 0;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    long long val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
int intersect(Line line1, Line line2){
    Point p1 = line1.start;
    Point q1 = line1.end;
    Point p2 = line2.start;
    Point q2 = line2.end;

    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return 1;

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

// We also need an onion to count how many components there are
int Onion[1024];

int find(int x){
    if (Onion[x] != x){
        Onion[x] = find(Onion[x]);
    }
    return Onion[x];
}

void onion(int x, int y){
    int parentx = find(x);
    int parenty = find(y);

    if (parentx != parenty){
        Onion[parentx] = parenty;
    }
}

Line lines[1024];
int count[1024];

int main(){
    // Scan in input
    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int sx, sy, ex, ey;
        scanf("%d %d %d %d", &sx, &sy, &ex, &ey);

        lines[i] = line(sx, sy, ex, ey);
    }

    // Initial the Onion
    for (int i = 0; i < n; ++i){
        Onion[i] = i;
    }

    // Find the number of intersection points:
    int numIntersections = 0;
    for (int i = 0; i < n-1; ++i){
        for (int j = i+1; j < n; ++j){
            if (intersect(lines[i], lines[j])){
                ++numIntersections;
                onion(i, j);
            }
        }
    }

    // Count the number of components
    for (int i = 0; i < n; ++i){
        count[find(Onion[i])] = 1;
    }

    int numComponents = 0;
    for (int i = 0; i < n; ++i){
        numComponents += count[i];
    }

    // Use Euler's formula!
    printf("%d\n", numIntersections + numComponents - n);

    return 0;
}

