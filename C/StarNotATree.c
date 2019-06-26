#include<stdio.h>
#include<math.h>

#define EPSILON 1e-4

int dr[5] = {0, -1, 0, 1, 0};
int n;

typedef struct {
    double x;
    double y;
} Point;

Point point(double x, double y){
    Point output;
    output.x = x;
    output.y = y;
    return output;
}

Point inputPoints[128];

// Takes 2 points and returns the hypotenuse squared
double hypotenuse(Point a, Point b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

// Given a point P, find the sum of squared distances to P 
double sum(Point P){
    double output = 0;
    for (int i = 0; i < n; ++i){
        output += hypotenuse(P, inputPoints[i]);
    }
    return output;
}


int main(){
    // Scan in input
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        double x, y;
        scanf("%lf %lf", &x, &y);
        inputPoints[i] = point(x, y);
    }

    // We will be doing binary search
    double x = 5000;
    double y = 5000;
    double delta = 5000;    

    // For each of the 4 directions
    // if moving in that direction would improve the sum, move there
    double current = sum(point(x, y));
    while (delta > EPSILON){
        for (int i = 0; i < 4; ++i){
            if (sum(point(x + delta*dr[i], y + delta*dr[i+1])) < current){
                x += delta*dr[i];
                y += delta*dr[i+1];
                current = sum(point(x, y));
            }
        }

        delta /= 2;
    }

    printf("%lf\n", sum(point(x, y)));
}
