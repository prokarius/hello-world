#include<stdio.h>
#include<math.h>

#define EPSILON 1e-7

typedef struct {
    double x;
    double y;
} Point;

Point red[256];
Point blue[256];
double forward[256][256];
int adjList[256][256];
int visited[256];
int n, b, r;

// Suppose we binary search for the answer. We try to find out if given a distance d
// whether it is possible to put N eggs so that all of them are at least d apart.

// Note that if we draw edges between nodes that are less than d apart, then we are
// trying to find a maximum independent set.

// Also note that the size of a maximum independent set is the number of points in
// the graph, minus the number of points in the minimum vertex cover.

// Lastly, by Konig's theorem, the cardinality of MVC is the cardinality of MCBM.
// ... *smile*

int dfs(int node){
    if (visited[node]) return 0;
    visited[node] = 1;




}

void constructAdjList(double dist){
    for (int i = 0; i < b; ++i){
        adjList[i][0] = 1;
        for (int j = 0; j < r; ++j){
            if (forward[i][j] < dist){
                adjList[i][adjList[i][0]] = j;
                adjList[i][0]++;
            }
        }
    }
}

// Returns true if the distance is small enough to form a MCBM of size r+b-n
int check(double dist){
    int out;
    constructAdjList(dist);
    



    if (out < r+b-n) return 1;
    return 0;
}

int main(){

    // Scan in input
    scanf ("%d %d %d", &n, &b, &r);

    for (int i = 0; i < b; ++i){
        scanf("%lf %lf", &blue[i].x, &blue[i].y);
    }

    for (int i = 0; i < b; ++i){
        scanf("%lf %lf", &red[i].x, &red[i].y);
    }

    // Create the adjMatrix:
    for (int i = 0; i < b; ++i){
        for (int j = 0; j < r; ++j){
            forward[i][j] = hypot(red[i].x - red[j].x, blue[i].x - blue[j].x);
        }
    }

    // Do binary search for the answer
    double lo = 0;
    double hi = 40000;
    double mid;

    while (hi - lo > EPSILON){
        mid = (hi + lo)/2;
        if (check(mid)){
            hi = mid;
        }
        else {
            lo = mid;
        }
    }

    printf ("%lf\n", mid);
}
