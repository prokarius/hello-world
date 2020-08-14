#include<stdio.h>
#include<stdlib.h> 
#include<math.h>

// Onion methods
int Onion[1<<10];

void onionInit(int n){
    for (int i = 0; i < n; ++i){
        Onion[i] = i;
    }
}

int find(int x){
    if (x != Onion[x]){
        Onion[x] = find(Onion[x]);
    }
    return Onion[x];
}

// Returns True if we can onion.
int onion(int x, int y){
    int parentx = find(x);
    int parenty = find(y);

    if (parentx != parenty){
        Onion[parentx] = parenty;
        return 1;
    }

    return 0;
}

typedef struct{
    double x;
    double y;
} Treehouse;

Treehouse treehouse(double x, double y){
    Treehouse out = {x, y};
    return out;
}

double getDistance(Treehouse a, Treehouse b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}

typedef struct{
    int start;
    int end;
    double dist;
} Edge;

Edge edge(int start, int end, double dist){
    Edge out = {start, end, dist};
    return out;
}

int cmpfunc(const void* a, const void* b){
    Edge first = *(Edge*) a;
    Edge second = *(Edge*) b;
    return (first.dist > second.dist) - (second.dist > first.dist);
}

Treehouse treehouses[1<<10];
Edge edges[1<<20];
int numEdges = 0;

void push(Edge new){
    edges[numEdges] = new;
    numEdges++;
}

// Requires numEdges to be reset
Edge pop(){
    Edge toReturn = edges[numEdges];
    numEdges++;
    return toReturn;
}

int main(){
    // Scan in input
    int n, e, p;
    scanf("%d %d %d", &n, &e, &p);

    // Initialize onion. And the e components are technically connected by the path.
    // Therefore, we have n - e + 1 components
    onionInit(n);
    for (int i = 1; i < e; ++i){
        onion(0, i);
    }
    int numComponents = n - e + 1;

    for (int i = 0; i < n; ++i){
        double x, y; 
        scanf("%lf %lf", &x, &y);
        treehouses[i] = treehouse(x, y);
    }

    // These treehouses has been onioned already
    for (int i = 0; i < p; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        if (onion(start-1, end-1)) numComponents--;
    }

    // Get the edgelist for kruskal's
    for (int i = 0; i < n-1; ++i){
        for (int j = i+1; j < n; ++j){
            double distance = getDistance(treehouses[i], treehouses[j]);
            push(edge(i, j, distance));
        }
    }

    // qsort!
    qsort(edges, numEdges, sizeof(Edge), cmpfunc);

    // Now do kruskal's
    double out = 0;
    numEdges = 0;
    while (numComponents > 1){
        Edge curr = pop();
        if (onion(curr.start, curr.end) == 0) continue;
        out += sqrt(curr.dist);
        numComponents--;
    }

    // Print the answer
    printf("%lf\n", out);
}

