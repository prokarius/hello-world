// Code translated from Java/Mravi.java

#include<stdio.h>

typedef struct{
    int end;
    long double flow;
    int power;
} Edge;

Edge edge(int end, int flow, int power){
    Edge output;
    output.end = end;
    output.flow = flow / 100.0;
    output.power = (power == 1);
    return output;
}

int size[1005];
Edge adjList[1005][105];
long double required[1005];

void push(int index, Edge edge){
    adjList[index][size[index]] = edge;
    size[index]++;
}

int check(int curr, long double drip, int parent){
    if (required[curr] > 0 && drip < required[curr]) return 0;

    for (int i = 0; i < size[curr]; ++i){
        Edge neighbour = adjList[curr][i];
        int next = neighbour.end;
        if (next == parent) continue;

        long double newDrip = drip * neighbour.flow;

        if (neighbour.power){
            if (newDrip > 1){
                newDrip = newDrip * newDrip;
            }
        }

        if (check(next, newDrip, curr) == 0) return 0;
    }
    return 1;
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 1; i < n; ++i){
        int start, end, flow, power;
        scanf("%d %d %d %d", &start, &end, &flow, &power);

        push(start, edge(end, flow, power));
        push(end, edge(start, flow, power));
    }

    for (int i = 1; i <= n; ++i){
        scanf("%Lf", &required[i]);
    }

    double hi = 1e10;
    double lo = 0;

    while (hi - lo > 1e-7){
        double mid = lo + (hi - lo)/2;
        if (check(1, mid, -1)) hi = mid;
        else lo = mid;
    }

    printf("%.9lf\n", (hi+lo)/2);

    return 0;
}

