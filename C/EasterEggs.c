#include<stdio.h>
#include<math.h>

#define EPSILON 1e-7

typedef struct {
    double x;
    double y;
} Point;

Point red[256];
Point blue[256];
double forwardDistances[256][256];

// Adjlist[i][0] stores the last element of the adjlist
int adjList[256][256];
int visited[256];
int forwardConnection[256];
int backwardConnection[256];
int n, b, r;

// Suppose we binary search for the answer. We try to find out if given a distance d
// whether it is possible to put N eggs so that all of them are at least d apart.

// Note that if we draw edges between nodes that are less than d apart, then we are
// trying to find a maximum independent set that has at least N elements.

// Also note that the size of a maximum independent set is the number of points in
// the graph, minus the number of points in the minimum vertex cover.
// This is because if we get rid of all the points in the MVC, we will be left with
// all the points that are not connected to anyone else with an edge

// Lastly, by Konig's theorem, the cardinality of MVC is the cardinality of MCBM.
// ... *smile*

// Edit: OK wait, don't smile yet, so what we need to do is this:
// 1. Binary search for the answer. Assume the answer is d, then
// 2. Draw a graph where the edges represent points where the distance is less than d.
// 3. Do an MCBM on that graph
// 4. Count the number of edges we drew in MCBM.
// 5. Do R + B - E, and check if it is >= N
// 6. If is it >= N, we can increase the distance d. If not, decrease. Go to 1.

int dfs(int node){
    if (visited[node]) return 0;
    visited[node] = 1;

    // For each potential red egg, see if it is already matched.
    for (int next = 1; next < adjList[node][0]; next++){

        // If it had not been matched before, yay, we win
        int nextNode = adjList[node][next];
        if (backwardConnection[nextNode] == -1){
            backwardConnection[nextNode] = node;
            forwardConnection[node] = nextNode;
            return 1;
        }

        // If not, dfs into the neighbour.
        // If it cannot be dfs'ed, move on to the next neighbour
        if (!dfs(backwardConnection[nextNode])) continue;

        // If we are here, we managed to find an augmenting path!
        backwardConnection[nextNode] = node;
        forwardConnection[node] = nextNode;
        return 1;
    }

    // Well if we failed to return anything, we don't find any augmenting paths :<
    return 0;
}

// Takes a distance d and returns an adjlist of edges that are lower than d.
void constructAdjList(double dist){
    for (int i = 0; i < b; ++i){
        adjList[i][0] = 1;
        for (int j = 0; j < r; ++j){
            if (forwardDistances[i][j] < dist){
                adjList[i][adjList[i][0]] = j;
                adjList[i][0]++;
            }
        }
    }
}

// Returns true if the distance is small enough to form a MCBM of size r+b-n
int check(double dist){

    // Step 2, create the adjList
    constructAdjList(dist);

    // Reset the matching arrays
    for (int i = 0; i < b; ++i){
        forwardConnection[i] = -1;
    }

    for (int i = 0; i < r; ++i){
        backwardConnection[i] = -1;
    }

    // Step 3: Do the MCBM. For each blue egg, try to preassign the blue eggs to
    // a red egg that hasn't already been assigned.
    for (int i = 0; i < b; ++i){
        for (int j = 1; j < adjList[i][0]; ++j){
            if (backwardConnection[adjList[i][j]] == -1){
                forwardConnection[i] = adjList[i][j];
                backwardConnection[adjList[i][j]] = i;
                break;
            }
        }
    }

    // Now run dfs for each of blue eggs, but only if it hasn't been matched before
    for (int i = 0; i < b; ++i){
        if (forwardConnection[i] != -1) continue;

        // Reset the visited array before doing the dfs
        for (int i = 0; i < b; ++i){
            visited[i] = 0;
        }

        // Then run the dfs
        dfs(i);
    }

    // Step 4: Count the number of edges
    int out = 0;
    for (int i = 0; i < b; ++i){
        if (forwardConnection[i] != -1){
            ++out;
        }
    }

    // Step 5: Do the check here
    if (r+b-n >= out) return 1;
    return 0;
}

int main(){

    // Scan in input
    scanf ("%d %d %d", &n, &b, &r);

    for (int i = 0; i < b; ++i){
        scanf("%lf %lf", &blue[i].x, &blue[i].y);
    }

    for (int i = 0; i < r; ++i){
        scanf("%lf %lf", &red[i].x, &red[i].y);
    }

    // Create the adjMatrix of distances:
    for (int i = 0; i < b; ++i){
        for (int j = 0; j < r; ++j){
            forwardDistances[i][j] = hypot(blue[i].x - red[j].x, blue[i].y - red[j].y);
        }
    }

    // Do binary search for the answer (Step 1)
    double lo = 0;
    double hi = 40000;
    double mid;

    while (hi - lo > EPSILON){
        mid = (hi + lo)/2;

        // Step 6, modify the values for the binary search
        if (check(mid)){
            lo = mid;
        }
        else {
            hi = mid;
        }
    }

    printf ("%lf\n", mid);
}

