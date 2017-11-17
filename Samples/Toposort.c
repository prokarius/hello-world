int toposort[500005], visited[500005], tsHead = 0;

// Set up my push methods
void tsPush(int elem){
    toposort[tsHead++] = elem;
}

// Make a toposorting DFS function:
void dfs(int vertex){
    visited[vertex] = 1;

    // Change this bit
    if (visited[adj[vertex][0]] == 0){
        dfs(adj[vertex][0]);
    }
    if (visited[adj[vertex][1]] == 0){
        dfs(adj[vertex][1]);
    }
    tsPush(vertex);
}
