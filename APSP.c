#include<stdio.h>

int dist[1002][1002];

// Do this when N is small
void floyd(int n, int m, int q, int s){
    // Reset the distance array
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            dist[i][j] = 1000000000; //Infinity
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
        printf("%d\n", 

int main(){
    int n, m, q, s;
    scanf ("%d %d %d %d", &n, &m, &q, &s);
    while (n != 0 && m != 0 && q != 0 && s != 0){
        APSP(n, m, q, s);
        scanf ("%d %d %d %d", &n, &m, &q, &s);
    }
    return 0;
}
