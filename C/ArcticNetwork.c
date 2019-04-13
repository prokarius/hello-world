#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
    short start;
    short end;
    double distance;
} Edge;

// This will be for the MST
// We will be doing Kruskal's
Edge edgelist[250005];
int edgelisthead = 0;

void pushEdge(Edge edge){
    edgelist[edgelisthead++] = edge;
}

// To compare and sort the list of edges during Kruskal's
int cmpfunc(const void* a, const void* b){
    Edge first = *(Edge*) a;
    Edge second = *(Edge*) b;
    return (first.distance > second.distance) - (second.distance > first.distance);
}

// We will need an onion for Kruskal's
// Set up onion methods
int onion[505];

int find(int x){
    if (onion[x] != x){
        onion[x] = find(onion[x]);
    }
    return onion[x];
}

// Returns true if we successfully onioned the two sets
int Onion(int x, int y){
    int parentx = find(x);
    int parenty = find(y);
    if (onion[parentx] == onion[parenty]){
        return 0;
    }
    else {
        onion[parentx] = parenty;
        return 1;
    }
}

double outpost[505][2];

// Not difficult.
// Find the largest edge of the MST given some already connected components
void run(){
    // Scan in input
    int s, p;
    scanf("%d %d", &s, &p);

    for (int i = 0; i < p; ++i){
        scanf("%lf %lf", &outpost[i][0] ,&outpost[i][1]);
    }

    // Initialise the onion.
    // Each outpost is friends with itself.
    for (int i = 0; i < p; ++i){
        onion[i] = i;
    }

    // Create the EdgeList
    // Reset the edgelist
    edgelisthead = 0;
     
    // Step 1: Settle all outposts to each other.
    for (short i = 0; i < p-1; ++i){
        for (short j = i+1; j < p; ++j){
            double distance = hypot(outpost[i][0] - outpost[j][0], outpost[i][1] - outpost[j][1]);
            Edge edge;
            edge.start = i;
            edge.end = j;
            edge.distance = distance;
            pushEdge(edge);
        }
    }

    // Step 2: Sort the edge list
    qsort(edgelist, edgelisthead, sizeof(Edge), cmpfunc);

    // Step 3: Do Kruskals
    double weight = 0;
    for (int i = 0; i < edgelisthead; ++i){
        weight = edgelist[i].distance;
        if (Onion(edgelist[i].start, edgelist[i].end)){
            p--;
            if (p == s){
                break;
            }
        }
    }
    printf("%.2lf\n", weight);
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    while(testcases--){
        run();
    }
    return 0;
}
