#include<stdio.h>

// Set up globals
long long numballs[500005];
int toposort[500005], visited[500005], tsHead = 0;
int adj[500005][2];

// Set up my push methods
void tsPush(int elem){
    toposort[tsHead++] = elem;
}

// Make a toposorting DFS function:
void dfs(int vertex){
    visited[vertex] = 1;
    if (visited[adj[vertex][0]] == 0){
        dfs(adj[vertex][0]);
    }
    if (visited[adj[vertex][1]] == 0){
        dfs(adj[vertex][1]);
    }
    tsPush(vertex);
}

int main(){
    visited[0] = 1;
    // Read in input
    int i=0, n, state[500005];
    char dir;
    scanf("%lld %d", &numballs[1], &n);

    while (++i <= n){
        scanf(" %c %d %d", &dir, &adj[i][0], &adj[i][1]);
        if (dir == 'L') state[i] = 0;
        else state[i] = 1;
    }
    // TOPOSORT the stuff:
    dfs(1);

    // Simulate the ball's movements using TOPOSORTED array;
    while (tsHead--){
        int k = toposort[tsHead];
        long long half = numballs[k]/2;
        long long otherhalf = numballs[k] - half;
        numballs[adj[k][1-state[k]]] += half;
        numballs[adj[k][state[k]]] += otherhalf;
        if (numballs[k] % 2){
            state[k] = 1-state[k];
        }
    }

    // printf
    i = 0;
    while (++i <= n) printf((state[i])?"R":"L");
    return 0;
}
