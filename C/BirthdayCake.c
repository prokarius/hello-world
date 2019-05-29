#include<stdio.h>

#define EPSILON 5e-6

typedef struct{
    double a;
    double b;
    double c;
} Line;

typedef struct{
    double x;
    double y;
} Point;

Line line(double a, double b, double c){
    Line out;
    out.a = a;
    out.b = b;
    out.c = c;
    return out;
}

Point point(double x, double y){
    Point out;
    out.x = x;
    out.y = y;
    return out;
}

Line lines[32];
Point points[64];
double r;

double ABS(double input){
    return (input < 0)?(-input):(input);
}

// Returns 1 if a and b intersect within the cake
// https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
int intersect(Line first, Line second){
    // Ensure that a and b are not parallel
    double determinant = first.a * second.b - first.b * second.a;
    if (ABS(determinant) < EPSILON) return 0;

    // Find x and y
    double x = (first.c * second.b - first.b * second.c) / determinant;
    double y = (first.a * second.c - first.c * second.a) / determinant;

    // Check if x and y is within the circle
    return (x*x + y*y < r*r);
}

// Returns 1 if the two points are seperated by the given line
// https://math.stackexchange.com/questions/162728/
int seperated(Point a, Point b, Line line){
    double first = line.a * a.x + line.b * a.y + line.c;
    double second = line.a * b.x + line.b * b.y + line.c;
    return (first * second < 0);
}

int main(){
    // Scan in input
    int n, m;

    scanf ("%d %d %lf", &n, &m, &r);

    for (int i = 0; i < n; ++i){
        double x, y;
        scanf("%lf %lf", &x, &y);
        points[i] = point(x, y);
    }

    for (int i = 0; i < m; ++i){
        double a, b, c;
        scanf("%lf %lf %lf", &a, &b, &c);
        lines[i] = line(a, b, c);
    }

    // 2 Conditions:
    // Condition 1: There are the same numebr of faces as points
    // This one is easy to check. Use Euler Characteristic!

    // We count the number of line-line intersections
    // Note that these intersections need to be within the cake!
    int lineline = 0;
    for (int i = 0; i < m-1; ++i){
        for (int j = i+1; j < m; ++j){
            lineline += intersect(lines[i], lines[j]);
        }
    }

    // Add that to the number of lines we have, and add 1.
    lineline += m;
    ++lineline;

    // Do we have more faces than candles?
    if (lineline != n){
        printf("no\n");
        return 0;
    }

    // Condition 2: Does every pair of candles have a line passing through?
    for (int i = 0; i < n-1; ++i){
        for (int j = i+1; j < n; ++j){
            int flag = 0;
            for (int k = 0; k < m; ++k){
                if (seperated(points[i], points[j], lines[k])){
                    flag = 1;
                    break;
                }
            }

            // If we did not find a line
            if (!flag){
                printf("no\n");
                return 0;
            }
        }
    }

    // We win
    printf("yes\n");
    return 0;
}
