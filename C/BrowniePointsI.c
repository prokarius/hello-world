#include<stdio.h>

typedef struct {
    int x;
    int y;
} Point;

Point point(int x, int y){
    Point output;
    output.x = x;
    output.y = y;
    return output;
}

Point points[20005];

void solve(int numPoints){
    // Scan in input
    for (int i = 0; i < numPoints; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        points[i] = point(x, y);
    }

    // Find the middle brownie
    int mid = (numPoints - 1) / 2;
    Point midPoint = points[mid];

    // Loop through all the points, and assign to stan or ollie
    int stan = 0;
    int ollie = 0;

    for (int i = 0; i < numPoints; ++i){
        if (points[i].x == midPoint.x || points[i].y == midPoint.y) continue;
        if ((points[i].x < midPoint.x) ^ (points[i].y > midPoint.y)) ++stan;
        else ++ollie;
    }

    printf("%d %d\n", stan, ollie);
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    while (n != 0){
        solve(n);
        scanf("%d", &n);
    }
    return 0;
}
