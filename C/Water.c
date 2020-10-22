#include<stdio.h>

#define MIN(x, y) (x < y)?(x):(y)

int pipes[128][128];
int visited[128];

int n;

int START = 1;
int END = 2;

int dfs(int curr, int flow){
    // If we have been here before, give up
    if (visited[curr]) return 0;

    // Have we reached the end?
    if (curr == END) return flow;

    // Ok then, we must visit here...
    visited[curr] = 1;

    // Visit all neighbors
    for (int i = 1; i <= n; ++i){
        int push = MIN(flow, pipes[curr][i]);

        // Don't bother if it doesn't have a pipe
        if (push == 0) continue;

        // DFS into it and run FF.
        int newFlow = dfs(i, push);

        // If we have flow, push it!
        if (newFlow > 0){
            pipes[curr][i] -= newFlow;
            pipes[i][curr] += newFlow; // Account for backflow
            return newFlow;
        }
    }

    // OK we visited all neighbors and none can give flow. Give up.
    return 0;
}

int ff(){
    // Reset the visited array
    for (int i = 1; i <= n; ++i) visited[i] = 0;
    return dfs(START, 1<<28);
}

int main(){
    int p, k;
    scanf("%d %d %d", &n, &p, &k);
    for (int i = 0; i < p; ++i){
        int start, end, cap;
        scanf("%d %d %d", &start, &end, &cap);

        // The pipes have cap flow in either direction
        pipes[start][end] = cap;
        pipes[end][start] = cap;
    }

    // Run FF until it terminates.
    // Time complexity = O(mF)
    int out = 0;
    int flow = ff();
    while (flow){
        out += flow;
        flow = ff();
    }

    printf("%d\n", out);

    for (int i = 0; i < k; ++i){
        int start, end, cap;
        scanf("%d %d %d", &start, &end, &cap);

        // The pipe can have *cap* more flow in either direction
        pipes[start][end] += cap;
        pipes[end][start] += cap;

        // Since each mod can give 1000 more flow, then TC here = O(kc)
        // Maybe it can pass... idk...
        flow = ff();
        while(flow){
            out += flow;
            flow = ff();
        }

        printf("%d\n", out);
    }

    return 0;
}

