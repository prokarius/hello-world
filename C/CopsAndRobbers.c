/* WE USE DINIC'S ALGORITHM HERE */
/* FOR EXPLANATION, SEE Java/KingOfTheNorth.java */

#include<stdio.h>

#define MIN(x, y) (x < y)?(x):(y)

#define MAX_VERTICES 2048
#define INF 1<<28

// Yes, we are going to code a dinic solver in C.
typedef struct {
    int end;
    int flow;
    int capacity;
} FlowEdge;

// Flow Edge constructor
FlowEdge newFlowEdge(int end, int capacity){
    FlowEdge flowEdge = {end, 0, capacity};
    return flowEdge;
}

// See if the given Edge is saturated
int isSaturated(FlowEdge edge){
    return (edge.flow == edge.capacity);
}

// Get the amount of flow that can be pushed through this edge.
int getFlow(FlowEdge edge){
    return edge.capacity - edge.flow;
}

// BFS queue methods
int bfsQueue[64 * MAX_VERTICES];
int bfsQueueHead = 0;
int bfsQueueTail = 0;

void pushBFS(int elem){
    bfsQueue[bfsQueueHead++] = elem;
}

int popBFS(){
    int out = bfsQueue[bfsQueueTail];
    bfsQueueTail++;
    return out;
}

int sizeBFS(){
    return bfsQueueHead - bfsQueueTail;
}

// Have all the data structaures ready at your disposal
// The each vertex can only have at most 5 neighbours. Except sink.
int vertices = MAX_VERTICES;
int adjList[MAX_VERTICES][20];
int vertexIndex[MAX_VERTICES];
int distance[MAX_VERTICES];

FlowEdge edgelist[100005];
int edgelisthead = 0;

int grid[31][31];
int cost[27];

void resetBFS(){
    bfsQueueHead = 0;
    bfsQueueTail = 0;

    for (int i = 0; i < MAX_VERTICES; ++i){
        distance[i] = INF;
    }
}

int bfs(int source, int sink){
    resetBFS();

    pushBFS(source);
    distance[source] = 0;

    while (sizeBFS() > 0){
        int curr = popBFS();
        if (curr == sink) return 1;

        for (int neighbouringEdge = 1; neighbouringEdge < adjList[curr][0]; neighbouringEdge++){
            FlowEdge edge = edgelist[adjList[curr][neighbouringEdge]];

            if (isSaturated(edge)) continue;

            int neighbour = edge.end;
            if (distance[neighbour] != INF) continue;

            distance[neighbour] = distance[curr] + 1;
            pushBFS(neighbour);
        }
    }

    return 0;
}

int dfs(int curr, int sink, int flow){
    if (curr == sink || flow == 0) return flow;

    for (int i = vertexIndex[curr]; i < adjList[curr][0]; ++i){
        if (isSaturated(edgelist[adjList[curr][i]])){
            vertexIndex[curr]++;
            continue;
        }

        if (distance[curr] + 1 != distance[edgelist[adjList[curr][i]].end]){
            vertexIndex[curr]++;
            continue;
        }

        int currFlow = MIN(getFlow(edgelist[adjList[curr][i]]), flow);
        int amountToPush = dfs(edgelist[adjList[curr][i]].end, sink, currFlow);

        if (amountToPush){
            edgelist[adjList[curr][i]].flow += amountToPush;
            edgelist[adjList[curr][i] ^ 1].flow -= amountToPush;
            return amountToPush;
        }

        vertexIndex[curr]++;
    }

    return 0;
}

int dfs2(int source, int sink){
    return dfs(source, sink, INF);
}

// Do Dinic's algorithm
int getMaxFlow(int source, int sink){
    int maxFlow = 0;

    while (bfs(source, sink)){
        for (int i = 0; i < MAX_VERTICES; ++i){
            vertexIndex[i] = 1;
        }

        int flow = dfs2(source, sink);
        while (flow){
            maxFlow += flow;
            flow = dfs2(source, sink);
        }
    }

    return maxFlow;
}

// Adds the edge to the solver
void addEdge(int start, int end, int capacity){
    FlowEdge forward = newFlowEdge(end, capacity);
    FlowEdge backward = newFlowEdge(start, 0);

    // Add the edges to the edgelist
    edgelist[edgelisthead++] = forward;
    edgelist[edgelisthead++] = backward;

    // Then add the index of the edges to the adjList
    adjList[start][adjList[start][0]] = edgelisthead - 2;
    adjList[end][adjList[end][0]] = edgelisthead - 1;
    adjList[start][0]++;
    adjList[end][0]++;
}

// Initialise the dinic solver.
void initDinicSolver(){
    for (int i = 0; i < MAX_VERTICES; ++i){
        adjList[i][0] = 1;
    }
}

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

int main(){
    initDinicSolver();

    // Scan in input
    int r, c, n;
    scanf("%d %d %d ", &r, &c, &n);

    int sourcex, sourcey;

    // Scan in the grid
    for (int i = 0; i < c; ++i){
        for (int j = 0; j < r; ++j){
            char ph;
            scanf("%c ", &ph);

            // If we cannot put a barricade there, then just put 0
            if (ph == '.'){
                grid[i][j] = 0;
            }

            // If not, are we at the bank?
            else if (ph == 'B'){
                sourcex = i;
                sourcey = j;
                grid[i][j] = -1;
            }

            // If not, we'll just 1 - index the character
            else {
                ph -= '`';
                grid[i][j] = ph;
            }
        }
    }

    // Scan in the cost
    for (int i = 1; i <= n; ++i){
        scanf("%d", &cost[i]);
    }
    cost[0] = INF;

    int source = (sourcex * r + sourcey) * 2 + 1;
    int sink = (r * c * 2);

    // Create the edge list
    // For each block, create the 2 vertices
    for (int i = 0; i < c; ++i){
        for (int j = 0; j < r; ++j){
            if (grid[i][j] < 0) continue;
            int incoming = 2 * (i*r + j);
            addEdge(incoming, incoming + 1, cost[grid[i][j]]);
        }
    }

    // Link each block to its neighbour
    for (int i = 0; i < c; ++i){
        for (int j = 0; j < r; ++j){
            int currOutgoing = 2 * (i*r + j) + 1;
            for (int k = 0; k < 4; ++k){
                int newc = i + dc[k];
                int newr = j + dr[k];

                if (newc < 0 || newr < 0 || newc >= c || newr >= r){
                    addEdge(currOutgoing, sink, INF);
                    continue;
                }

                int newIncoming = (newc * r + newr) * 2;

                addEdge(currOutgoing, newIncoming, INF);
            }
        }
    }

    // Print that shit
    int flow = getMaxFlow(source, sink);
    printf("%d\n", flow > INF ? -1 : flow);
}
