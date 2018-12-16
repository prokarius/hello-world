#include<stdio.h>
#define INF 1000000000
#define MIN(x, y) (x < y)?(x):(y)

int dist[155][155];

// Do this when N is small
void floyd(int n, int m, int q){
    // Reset the distance array and the adjMatrix
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            dist[i][j] = INF;
        }
    }

    // But the distance from a node to itself is 0
    for (int i = 0; i < n; ++i){
        dist[i][i] = 0;
    }

    // Scan in adjlist
    // Could it be that they give repeated edges?
    int u, v, w;
    for (int i = 0; i < m; ++i){
        scanf("%d %d %d", &u, &v, &w);
        dist[u][v] = MIN(w, dist[u][v]);
    }

    // Do APSP (Floyd Warshall)
    for (int k = 0; k < n; ++k){
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){

                // "If there are negative edges, ensure that INF + w is still INF."
                // Wisest words spoken on 17th Dec 2018, 12:22:42 AM
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                if (dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // OK right, now we need to see if a node is part of a negative cycle.
    // We can do that by checking of the distance ot itself is negative.
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){

            // We want to see for each edge, if it passes through the given node.
            // This can be done by checking if the node is reachable from the front
            // and then to the end.
            for (int k = 0; k < n; ++k){

                // Is the node k part of a negative cycle?
                if (dist[k][k] == 0) continue;

                // If we can't go from start to k, or k to end.
                if (dist[i][k] == INF || dist[k][j] == INF) continue;

                // Yes we can go from the start to the end through node k.
                dist[i][j] = -INF;
                break;
            }
        }
    }

    // Wew, we are done with the graph processing. We can now in queries
    for (int i = 0; i < q; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        if (dist[start][end] == INF){
            printf("Impossible\n");
        }
        else if (dist[start][end] == -INF){
            printf("-Infinity\n");
        }
        else {
            printf("%d\n", dist[start][end]);
        }
    }
}

int main(){
    int n, m, q;
    scanf ("%d %d %d", &n, &m, &q);
    while (n != 0 && m != 0 && q != 0){
        floyd(n, m, q);
        printf("\n");
        scanf ("%d %d %d", &n, &m, &q);
    }
    return 0;
}
