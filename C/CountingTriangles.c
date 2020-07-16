#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) (x > y)?(x):(y)
#define MIN(x, y) (x < y)?(x):(y)

typedef struct{
    double x;
    double y;
} Point;

Point point(double a, double b){
    Point p = {a, b};
    return p;
}

typedef struct {
    Point start;
    Point end;
} Line;

Line line(double x1, double y1, double x2, double y2){
    Line a;
    a.start = point(x1, y1);
    a.end = point(x2, y2);
    return a;
}

// Totally not copied from geekforgeeks

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
int onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= MAX(p.x, r.x) && q.x >= MIN(p.x, r.x) && 
        q.y <= MAX(p.y, r.y) && q.y >= MIN(p.y, r.y)) 
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
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
int doIntersect(Line* line1, Line* line2){
    Point p1 = (*line1).start;
    Point q1 = (*line1).end;
    Point p2 = (*line2).start;
    Point q2 = (*line2).end;

    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4) return 1;

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

int triangle(Line* a, Line* b, Line* c){
    // Check if they pairwise intersect
    return (doIntersect(a, b) +
            doIntersect(b, c) +
            doIntersect(c, a) == 3);
}

void solve(int n){
    // Scan in input
    Line* lines = (Line*) malloc(n * sizeof(Line));
    for (int i = 0; i < n; ++i){
        double a, b, c, d;
        scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
        lines[i] = line(a, b, c, d);
    }

    int out = 0;

    // 3 for loops!
    for (int i = 0; i < n-2; ++i){
        for (int j = i+1; j < n-1; ++j){
            for (int k = j+1; k < n; ++k){
                out += triangle(&lines[i], &lines[j], &lines[k]);
            }
        }
    }

    printf("%d\n", out);
}

int main(){
    int n;
    scanf("%d", &n);
    while (n != 0){
        solve(n);
        scanf("%d", &n);
    }
    return 0;
}
