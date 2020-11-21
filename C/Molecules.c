#include<stdio.h>

#define ITERATIONS_MAX 100000
#define SCALE_FACTOR 0.75

typedef struct {
    double x;
    double y;
} Atom;

Atom atom(int x, int y){
    Atom out = {x, y};
    return out;
}

Atom atoms[128];
int immovable[128];
int numEdges[128];
int adjlist[128][128];

// Looks at the adjList and gets the average coordinate of the neighbours
Atom getAverage(int x){
    double dx = 0;
    double dy = 0;

    for (int i = 0; i < numEdges[x]; ++i){
        Atom neighbor = atoms[adjlist[x][i]];
        dx += neighbor.x;
        dy += neighbor.y;
    }
    
    Atom out = {dx / numEdges[x], dy / numEdges[x]};
    return out;
}


int main(){
    // Scan in input
    int n, m;
    scanf ("%d %d", &n, &m);

    for (int i = 0; i < n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);

        if (x == -1 && y == -1){
            immovable[i] = 0;
            atoms[i] = atom(i+12, i+12); // Just start it somewhere
        }
        else {
            immovable[i] = 1;
            atoms[i] = atom(x, y);
        }
    }

    // Scan in the adj list
    for (int i = 0; i < m; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        start--;
        end--;

        adjlist[start][numEdges[start]++] = end;
        adjlist[end][numEdges[end]++] = start;
    }

    // Do some simulation
    while(1){
        int flag = 1;
        for (int j = 0; j < n; ++j){
            if (immovable[j]) continue;
            Atom averageCoord = getAverage(j);

            double dx = atoms[j].x - averageCoord.x;
            double dy = atoms[j].y - averageCoord.y;

            if (dx*dx + dy*dy >= 1e-8) flag = 0;

            atoms[j].x -= dx * SCALE_FACTOR;
            atoms[j].y -= dy * SCALE_FACTOR;
        }

        // Terminate the decent
        if (flag) break;
    }

    // Print it out
    for (int i = 0; i < n; ++i){
        printf("%lf %lf\n", atoms[i].x, atoms[i].y);
    }

    return 0;
}

