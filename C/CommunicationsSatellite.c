#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct{
    int x;
    int y;
    int radius;
} Satellite;

Satellite satellite(int x, int y, int radius){
    Satellite output;
    output.x = x;
    output.y = y;
    output.radius = radius;
    return output;
}

Satellite satellites[2048];

// Takes two integers
double distance(int satellite1, int satellite2){
    Satellite first = satellites[satellite1];
    Satellite second = satellites[satellite2];
    double dx = first.x - second.x;
    double dy = first.y - second.y;
    return sqrt(dx*dx + dy*dy) - (first.radius + second.radius);
}

typedef struct{
    int start;
    int end;
    double dist;
} Kruskals;

Kruskals kruskals(int start, int end, double dist){
    Kruskals output;
    output.start = start;
    output.end = end;
    output.dist = dist;
    return output;
}

Kruskals distances[4000005];
int distanceHead = 0;

void push(Kruskals data){
    distances[distanceHead] = data;
    distanceHead++;
}

int cmpfunc(const void* a, const void* b){
    Kruskals first = *(Kruskals*) a;
    Kruskals second = *(Kruskals*) b;
    return (first.dist > second.dist) - (second.dist > first.dist);
}

int Onion[2048];

int find(int node){
    if (Onion[node] != node){
        Onion[node] = find(Onion[node]);
    }
    return Onion[node];
}

// Returns 1 if the two things have not been onion'ed
int onion(int x, int y){
    int parentx = find(x);
    int parenty = find(y);

    if (parentx == parenty){
        return 0;
    }

    Onion[parentx] = parenty;
    return 1;
}

int main(){
    // Reset my onion
    for (int i = 0; i < 2048; ++i){
        Onion[i] = i;
    }

    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int x, y, r;
        scanf ("%d %d %d", &x, &y, &r);
        satellites[i] = satellite(x, y, r);
    }

    // Loop through and generate the kruskal's list
    for (int i = 0; i < n-1; ++i){
        for (int j = i+1; j < n; ++j){
            push(kruskals(i, j, distance(i, j)));
        }
    }

    // Sort the list
    qsort(distances, distanceHead, sizeof(Kruskals), cmpfunc);

    // Loop through the qsorted array and onion everything
    int curr = 0;
    double total = 0;
    while (n != 1){
        Kruskals current = distances[curr];

        if (onion(current.start, current.end)){
            total += current.dist;
            n--;
        }

        curr++;
    }

    printf("%lf\n", total);

    return 0;
}
