#include<stdio.h> 
#include<stdlib.h> 

typedef struct {
    long long x;
    long long y;
    int num;
} Point;

int cmpfunc(const void* a, const void* b){
    Point first = *(Point*) a;
    Point second = *(Point*) b;

    if (first.x - second.x == 0) return (first.y - second.y);
    return first.x - second.x;
}


// Monotone chain
long long ccw(Point a, Point b, Point c){
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

void solve(){
    // Scan in input
    int n;
    scanf("%d", &n);

    Point* points = (Point*) malloc(n * sizeof(Point));
    for (int i = 0; i < n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        Point new = {x, y, i};
        points[i] = new;
    }

    // Sort the points by x, then y
    qsort(points, n, sizeof(Point), cmpfunc);

    Point* hull = (Point*) malloc(n*sizeof(Point));
    int k = 0;

    // Find the lower hull
    // Totally not copied from the wiki
    for (int i = 0; i < n; ++i){
        while (k >= 2 && ccw(hull[k-2], hull[k-1], points[i]) < 0) --k;
        hull[k++] = points[i];
    }

    // Find out which points we have used to build the lower hull
    int* used = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < k; ++i){
        used[hull[i].num] = 1;
    }

    // Then walk backwards through the list and just populate the points in order
    for (int i = n-1; i >= 0; --i){
        if (used[points[i].num]) continue;
        hull[k++] = points[i];
    }

    printf("%d\n", k);

    // Print that shit
    for (int i = 0; i < n; ++i){
        printf("%d ", hull[i].num);
    }
    printf("\n");

    // Free the dobbies!
    free (points);
    free (hull);
    free (used);
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    while(testcases--) solve();
    return 0;
}

