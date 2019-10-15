#include<stdio.h>

int adjList[1024][1024];
int size[1024];

int visited[1024];
int distances[1024][1024];

int possible1[1024];
int possible2[1024];

int n1, n2, m1, m2;
int n;
int graph;

int MAX(int x, int y){
    return (x > y)?(x):(y);
}

void dfs(int node){
    // Have we visited before?
    if (visited[node]) return;
    visited[node] = 1;

    // Visit all the neighbours
    for (int i = 0; i < size[node]; ++i){
        int neighbour = adjList[node][i];
        dfs(neighbour);

        // Then find out how many steps the previous one can take
        // Doing this post fix means that we are doing it in toposort order
        // Time complexity: O(n * m)... probably
        for (int d = 0; d <= n; ++d){
            if (distances[neighbour][d]){
                distances[node][d+1] = 1;
            }
        }
    }
}

int main(){
    // Scan in input
    scanf("%d %d %d %d", &n1, &n2, &m1, &m2);

    // Find the max
    n = MAX(n1, n2);

    for (int i = 0; i < m1; ++i){
        int start, end;
        scanf("%d %d", &start, &end);

        adjList[start][size[start]] = end;
        size[start]++;
    }

    // Do DFS preprocess from vertex 1
    visited[n1] = 1;
    distances[n1][0] = 1;
    dfs(1);

    // Copy the distances
    for (int i = 0; i <= n1; ++i){
        possible1[i] = distances[1][i];
    }

    // Copy and paste for second run
    // Reset the size array
    for (int i = 0; i <= n2; ++i){
        size[i] = 0;
        visited[i] = 0;

        for (int j = 0; j <= n2; ++j){
            distances[i][j] = 0;
        }
    }

    for (int i = 0; i < m2; ++i){
        int start, end;
        scanf("%d %d", &start, &end);

        adjList[start][size[start]] = end;
        size[start]++;
    }

    // Do DFS preprocess from vertex 1
    visited[n2] = 1;
    distances[n2][0] = 1;
    dfs(1);

    // Copy the distances
    for (int i = 0; i <= n2; ++i){
        possible2[i] = distances[1][i];
    }


    // Scan in the queries
    int numQueries;
    scanf("%d", &numQueries);
    for (int i = 0; i < numQueries; ++i){
        int query;
        scanf("%d", &query);

        int win = 0;
        for (int d = 0; (d <= n1) * (query-d >= 0); ++d){
            if (query-d > n2) continue;
            if (possible1[d] * possible2[query - d]){
                win = 1;
                break;
            }
        }

        printf(win?"Yes\n":"No\n");
    }

    return 0;
}

