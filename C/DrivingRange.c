#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int start;
    int end;
    int weight;
} Edge;

// Edgelist methods
Edge edgelist[1000005];
int edgelisthead = 0;

// Push into the edge
void push(Edge x){
    edgelist[edgelisthead++] = x;
}

// Pop from the front
Edge pop(){
    return edgelist[--edgelisthead];
}

// compareTo for edges.
// Make a and b Edge pointers, dereferece it, and subtract the weights
int cmpfunc(const void *a, const void *b){
    return ((*(Edge*)b).weight) - ((*(Edge*)a).weight);
}


// Onion methods
int ufds[1000005];
int numcomponents;

// Initialise the onion
void init(int n){
    for (int i=0; i<n; ++i){
        ufds[i] = i;
    }
    numcomponents = n;
}

// Find parent
int find(int n){
    if (ufds[n] != n){
        ufds[n] = find(ufds[n]);
    }
    return ufds[n];
}

// Onion the two elements
void onion(int n, int m){
    int x = find(n);
    int y = find(m);
    if (x != y){
        ufds[x] = y;
        numcomponents--;
    }
}

int main(){
    int n, m;

    // Scan in input
    scanf("%d %d", &n, &m);
    for (int i=0; i<m; ++i){
        int start, end, weight;
        scanf("%d %d %d", &start, &end, &weight);
        Edge new = {start, end, weight};
        push(new);
    }

    if (n < 2){
        printf ("0\n");
        return 0;
    }

    init(n);

    qsort(edgelist, edgelisthead, sizeof(Edge), cmpfunc);

    Edge curr;
    while (numcomponents-1){
        if (edgelisthead){
            curr = pop();
            onion (curr.start, curr.end);
        }
        else {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }

    printf ("%d\n", curr.weight);
    return 0;
}
