#include<cstdio>
#include<stack>

#define MOD 1000000009

int vis[100005];
std::stack<int> adjl[100005];

void dfs(int v){
    ++vis[v];
    while (!adjl[v].empty()){
        int p = adjl[v].top();
        adjl[v].pop();
        if (!vis[p]) dfs(p);
    }
}

int main(){
    // Initialise all our shit and scan the stuff in
    int i=0, N, M, a, b;
    scanf ("%d %d", &N, &M);
    while (i++ < M){
        scanf ("%d %d", &a, &b);
        adjl[a].push(b);
        adjl[b].push(a);
    }

    // Total number of redundant edges = total number of distinct cycles
    // = number of edges - number of edges in a forest of K trees
    // Number of edges in a forest of K trees = N - K
    // Hence total number of useless edges => M - N + K

    // We want to find the total number of trees. So BFS.
    // The number of new calls to BFS will give us the number of trees.
    int C = 0;
    for (i=1; i<=N; ++i){ // Fucking one based indexing
        if (!vis[i]){
            ++C;
            dfs(i);
        }
    }
    int ans = 1;
    for (i=0; i<(M-N+C); ++i) ans = (2*ans)%MOD;
    printf ("%d\n", ans);
    return 0;
}
