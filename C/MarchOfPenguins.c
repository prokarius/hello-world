#include<stdio.h>

#define MIN(x, y) (x<y)?(x):(y)
#define EPSILON 1e-6

typedef struct{
    int x;
    int y;
} Coord;

Coord coord(int x, int y){
    Coord out = {x, y};
    return out;
}

double distance(Coord a, Coord b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}

int n;
int adjmat[256][256];
int network[256][256];
Coord coords[128];
int flag = 1;
int visited[256];

int addEdge(int start, int end, int amount){
    adjmat[start][end] += amount;
}

int dfs(int curr, int end, int flow){
    if (visited[curr]) return 0;
    if (curr == end) return flow;
    visited[curr] = 1;

    for (int i = 0; i < 2*n; i++){
        if (visited[i]) continue;
        int push = MIN(flow, network[curr][i]);
        if (push == 0) continue;

        int newFlow = dfs(i, end, push);
        if (newFlow == 0) continue;

        network[curr][i] -= newFlow;
        network[i][curr] += newFlow;
        return newFlow;
    }

    // No more possible augmenting paths from this node
    return 0;
}

int FF(int start, int end){
    int out = 0;
    int flow;

    do {
        // Reset the visited array
        for (int i = 0; i < 2*n + 2; ++i){
            visited[i] = 0;
        }
        flow = dfs(start, end, 1<<28);
        out += flow;
    }
    while (flow > 0);

    return out;
}

int main(){
    // Scan in input
    double d;
    scanf("%d %lf", &n, &d);

    d = d*d;  // So we don't need to call sqrt all the time...

    int SOURCE = 2*n + 1;

    // Scan in ice floes.
    // Inflow = num penguins on it, Outflow = max jumps
    int totalPenguins = 0;
    for (int i = 0; i < n; ++i){
        int x, y, k, m;
        scanf("%d %d %d %d", &x, &y, &k, &m);

        int IN_VERTEX = 2*i;
        int OUT_VERTEX = 2*i+1;

        coords[i] = coord(x, y);
        addEdge(SOURCE, IN_VERTEX, k);
        addEdge(IN_VERTEX, OUT_VERTEX, m);

        totalPenguins += k;
    }

    // If a penguin can make the jump, add the edge:
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (i == j) continue;
            if (distance(coords[i], coords[j]) - d < EPSILON){
                addEdge(2*i + 1, 2*j, 1023);
            }
        }
    }

    // Loop through all icefloes and see if every penguin can reach the SINK floe
    for (int i = 0; i < n; ++i){
        int SINK = 2*i;

        // Reset the FF array
        for (int j = 0; j < 2*n+2; ++j){
            for (int k = 0; k < 2*n+2; ++k){
                network[j][k] = adjmat[j][k];
            }
        }

        if (FF(SOURCE, SINK) == totalPenguins){
            printf("%d ", SINK >> 1);
            flag = 0;
        }
    }

    // If we didn't have a winning floe, print -1
    if (flag) printf("-1");
    printf("\n");

    return 0;
}

