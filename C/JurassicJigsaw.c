#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Onion methods!
int Onion[1<<10];
int numComponents;

void onionInit(int n){
    for (int i = 0; i < n; ++i){
        Onion[i] = i;
    }
    numComponents = n;
}

int find(int x){
    if (Onion[x] != x){
        Onion[x] = find(Onion[x]);
    }
    return Onion[x];
}

int onion(int x, int y){
    int parentx = find(x);
    int parenty = find(y);

    if (parentx == parenty) return 0;
    Onion[parentx] = parenty;
    numComponents--;
    return 1;
}


// Edge class for Kruskal's
typedef struct{
    int start;
    int end;
    int distance;
} Edge;

Edge edge(int start, int end, int distance){
    Edge out = {start, end, distance};
    return out;
}

int cmpfunc(const void* a, const void* b){
    Edge first = *(Edge*) a;
    Edge second = *(Edge*) b;

    return first.distance - second.distance;
}

// For kruskals and output
Edge edges[1<<20];
int numEdges = 0;

Edge output[1<<10];
int numOutput = 0;

void pushEdge(Edge edge){
    edges[numEdges] = edge;
    numEdges++;
}

Edge popEdge(){
    Edge out = edges[numEdges];
    numEdges++;
    return out;
}

void pushOutput(Edge edge){
    output[numOutput] = edge;
    numOutput++;
}

char* strlst[1024];

// Global variable because I need them :<
int n, k;

int getDistance(int a, int b){
    int out = 0;
    for (int i = 0; i < k; ++i){
        if (strlst[a][i] != strlst[b][i]) out++;
    }
    return out;
}

int main(){
    // Scan in input
    scanf("%d %d", &n, &k);

    onionInit(n);

    for (int i = 0; i < n; ++i){
        strlst[i] = malloc(12 * sizeof(char));
        scanf(" %s", strlst[i]);
    }

    // Now create adjlist 
    for (int i = 0; i < n-1; ++i){
        for (int j = i+1; j < n; ++j){
            pushEdge(edge(i, j, getDistance(i, j)));
        }
    }

    // qsort the edgelist
    qsort(edges, numEdges, sizeof(Edge), cmpfunc);
    
    int cost = 0;
    numEdges = 0;
    while (numComponents > 1){
        Edge curr = popEdge();
        if (onion(curr.start, curr.end)){
            pushOutput(curr);
            cost += curr.distance;
        }
    }

    // Print out the cost, and the edges
    printf("%d\n", cost);

    for (int i = 0; i < numOutput; ++i){
        printf("%d %d\n", output[i].start, output[i].end);
    }

    return 0;
}

