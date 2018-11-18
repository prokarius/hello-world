#include<stdio.h>
#define INF 1000000000

int dist[150][150];

// Do this when N is small
void floyd(int n, int m, int q){
    // Reset the distance array
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            dist[i][j] = INF; //Infinity
        }
    }

    // Scan in adjlist
    int u, v, w;
    for (int i=0; i<m; ++i){
        scanf("%d %d %d", &u, &v, &w);
        dist[u][v] = w;
    }

    // Do APSP (Floyd Warshall)
    for (int i=0; i<n; ++i){
        int relaxed = 1;
        for (int j=0; j<n; ++j){
            for (int k=0; k<n; ++k){
                if (dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    relaxed = 0;
                }
            }
        }
        if (relaxed){
            break;
        }
    }

    // Scan in queries
    for (int i=0; i<q; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        printf("%d\n", dist[start][end]);
    }
}

int main(){
    int n, m, q;
    scanf ("%d %d %d", &n, &m, &q);
    while (n != 0 && m != 0 && q != 0){
        floyd(n, m, q);
        scanf ("%d %d %d", &n, &m, &q);
    }
    return 0;
}
