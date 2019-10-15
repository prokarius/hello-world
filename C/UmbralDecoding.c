#include<stdio.h>

typedef struct{
    int x;
    int y;
} Point;

Point point(int x, int y){
    Point output;
    output.x = x;
    output.y = y;
    return output;
}

typedef struct{
    Point p;
    int b;
} Umbra;

Umbra umbra (int x, int y, int b){
    Umbra output;
    output.p = point(x, y);
    output.b = b;
    return output;
}

Umbra umbras[128];
int k;

__int128_t ABS(__int128_t x){
    return (x > 0)?(x):(-x);
}

// Returns 1 if point a in in umbra u
int checkOverlap(Point a, Umbra u){
    int dx = a.x - u.p.x;
    int dy = a.y - u.p.y;

    __int128_t dx3 = 1LL * dx * dx * dx;
    __int128_t dy3 = 1LL * dy * dy * dy;

    return (ABS(dx3) + ABS(dy3) <= u.b)?(1):(0);
}

// Returns the number of points inside the area (left, top) -> (right, bottom)
// We have the rule that b will always be the bottom right point
long long binSearch2D(Point a, Point b){
    // 3 cases.

    // Case 1: The entire square is covered (by one umbra)
    // If so, then return the size of the square
    // You can do this by checking if the 4 corners of the square belong in any umbra
    for (int i = 0; i < k; ++i){
        if (checkOverlap(a, umbras[i]) && checkOverlap(b, umbras[i]) &&
            checkOverlap(point(a.x, b.y), umbras[i]) && checkOverlap(point(b.x, a.y), umbras[i])){
            int dx = b.x - a.x;
            int dy = b.y - a.y;
            return 1LL * (dx+1) * (dy+1);
        }
    }

    // Case 2: The entire square is NOT covered, AT ALL
    // We can check this by finding the point with the highest probability of being
    // in each Umbra, and then checking if it is in the umbra
    int overlap = 0;
    for (int i = 0; i < k; ++i){
        // Look at one dimension, if the umbra's coordinate is within the square
        // then the point closest will share in the umbra's coordinate
        int closestX, closestY;
        if (umbras[i].p.x < a.x){
            closestX = a.x;
        }
        else if (umbras[i].p.x > b.x){
            closestX = b.x;
        }
        else {
            closestX = umbras[i].p.x;
        }
        if (umbras[i].p.y < a.y){
            closestY = a.y;
        }
        else if (umbras[i].p.y > b.y){
            closestY = b.y;
        }
        else {
            closestY = umbras[i].p.y;
        }

        // Does this mofo even belong in the umbra?
        if (checkOverlap(point(closestX, closestY), umbras[i])){
            overlap = 1;
            break;
        }
    }

    if (overlap == 0) return 0;

    // Case 3: We need to go deeper. RECURSE. The points created will be as follows:
    int x1 = a.x;
    int y1 = a.y;
    int x3 = b.x;
    int y3 = b.y;

    int x2 = x1 + (x3 - x1)/2;
    int y2 = y1 + (y3 - y1)/2;

    return (binSearch2D(point(x1, y1), point(x2, y2)) +
            binSearch2D(point(x1, y2+1), point(x2, y3)) +
            binSearch2D(point(x2+1, y1), point(x3, y2)) +
            binSearch2D(point(x2+1, y2+1), point(x3, y3)));
}

int main(){
    // Scan in input
    int n;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; ++i){
        int x, y, b;
        scanf("%d %d %d", &x, &y, &b);
        umbras[i] = umbra(x, y, b);
    }

    // Print n**2 minus the number of points that is not within x, y or b.
    printf("%lld\n", 1LL*(n+1)*(n+1) - binSearch2D(point(0, 0), point(n, n)));
    return 0;
}

