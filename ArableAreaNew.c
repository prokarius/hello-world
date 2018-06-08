#include<stdio.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct{
    Point start;
    Point end;
    double gradient;
} Line;

// Takes two Points and calculates the gradient between them.
// Returns 10007 if the line is vertical.
double gradient(Point a, Point b){
    if (a.x == b.x){
        return 10007;
    }
    return ((double)(a.y-b.y))/(a.x - b.x);
}

// Line constructor. Ensures that output.start is higher than output.end;
Line makeLine(Point a, Point b){
    Line output;
    output.gradient = gradient(a,b);
    if (a.y < b.y){
        output.start = b;
        output.end = a;
    }
    else {
        output.start = a;
        output.end = b;
    }
    return output;
}

// Given a y value and a line, find x such that the line intersects (x,y).
// Precondition is the line is not horizontal, and the y value is valid
double xintercept(Line line, int y){
    // If the line is vertical, then the intersect is just the x value
    if (line.gradient == 10007){
        return line.start.x;
    }
    return ((y - line.start.y) / line.gradient) + line.start.x;
}

long long invalidRange(Line line, int y){




}

void code(int n){
    Point pointlist[102];
    Line linelist[102];
    int validsquares[205][205];
    int invalid[205][205];

    // Scan in input
    int x, y;
    int miny = 1000, maxy = -1000;
    for (int i = 1; i <= n; ++i){
        scanf("%d %d", &x, &y);
        Point newPoint = {x + 102, y + 102};
        pointlist[i] = newPoint;

        // So that we don't waste time looking at rows we don't need to.
        if (miny > y) miny = y;
        if (maxy < y) maxy = y;
    }

    // To make the construction of the linelist easier
    pointlist[0] = pointlist[n];

    for (int i = 0; i < n; ++i){
        Line newline = makeLine(pointlist[i], pointlist[i+1]);
        linelist[i] = newline;
    }

    // For each row from miny to maxy, count the number of squares
    // Whenever a line intersects the squares, the next square are now invalid
    while (miny <= maxy){
        for (int i = 0; i < n; ++i){
            long long invalidrange = invalidRange(linelist[i], miny);
            :wq


        }
        miny++;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    while (n){
        code(n);
        scanf("%d", &n);
    }
    return 0;
}
