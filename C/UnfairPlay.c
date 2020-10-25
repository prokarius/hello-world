#include<stdio.h>

#define MIN(x, y) (x < y)?(x):(y)

int n, m;

int initScore[128];
int matches[1024];
int skip[1024];
int adjMat[1536][1536];
int matchOutcome[1024];

int visited[1536];
int parent[1536];

int queue[1<<16];
int queueHead = 0;
int queueTail = 0;

void push(int x){ queue[queueHead++] = x; }
int pop(){ return queue[queueTail++]; }
int notEmpty(){ return queueHead > queueTail; }
void clear(){ queueHead = 0; queueTail = 0; }

// Returns 1 if we can BFS from source to sink
int bfs(int source, int sink){
    clear();

    // Reset visited array
    for (int i = 1; i < sink; ++i){
        visited[i] = 0;
        parent[i] = 0;
    }

    for (int i = 1; i <= m; ++i){
        if (adjMat[0][i] == 0) continue;
        visited[i] = 1;
        parent[i] = 0;
        push(i);
    }

    while(notEmpty()){
        int curr = pop();

        // If this is a match node:
        if (curr <= m){
            for (int i = m+1; i <= n+m+1 ; ++i){
                if (visited[i] || adjMat[curr][i] == 0) continue;
                push(i);
                parent[i] = curr;
                visited[i] = 1;
            }
        }

        // Else this is a team node
        else {
            // Short circuit if we can go to sink
            if (adjMat[curr][sink] != 0){
                parent[sink] = curr;
                return 1;
            }

            // If not, see if there are back edges
            for (int i = 1; i <= m; ++i){
                if (visited[i] || adjMat[curr][i] == 0) continue;
                push(i);
                parent[i] = curr;
                visited[i] = 1;
            }
        }
    }

    return 0;
}

void solve(){
    // Scan in input
    scanf("%d", &m);

    int SOURCE = 0;
    int SINK = m+n+1;

    for (int i = 1; i <= n; ++i){
        scanf("%d", &initScore[i]);
    }
    initScore[n]--;

    for (int i = 0; i <= n + m + 1; ++i){
        for (int j = 0; j <= n + m + 1; ++j){
            adjMat[i][j] = 0;
        }
    }

    // Read each match. If it involves my team, make him win.
    int matchesRemaining = 0;
    for (int i = 1; i <= m; ++i){
        int x, y;
        scanf("%d %d", &x, &y);

        matches[i] = x;

        if (x == n){
            matchOutcome[i] = 0;
            initScore[n] += 2;
            skip[i] = 1;
            continue;
        }

        if (y == n){
            matchOutcome[i] = 2;
            initScore[n] += 2;
            skip[i] = 1;
            continue;
        }

        // Add the edges to the adjmatrix
        // Adjmatrix[x][y] means there is a flow edge from x to y
        // x = 0 is the source
        // 1 <= x <= m are the matches
        // m+1 <= x <= m+n are the teams
        // m+n+1 is the sink;

        // Each match has 2 points to give out
        adjMat[i][m+x] = 2;
        adjMat[i][m+y] = 2;

        // Also, give source to this node flow of 2.
        adjMat[SOURCE][i] = 2;

        skip[i] = 0;
        ++matchesRemaining;
    }

    // The outflow capacities are limited by how many points each team can win
    for (int i = 1; i < n; ++i){
        int score = initScore[n] - initScore[i];

        // Short circuit if we cannot win from the get go
        if (score < 0){
            printf("NO\n");
            return;
        }

        adjMat[m+i][SINK] = score;
    }

    int maxFlow = 0;

    // Now we do maxFlow (Today is EK)
    while (bfs(SOURCE, SINK)){
        int best = 1024;
        // Saturate the edges
        int curr = SINK;
        while (curr != SOURCE){
            int prev = parent[curr];
            best = MIN(best, adjMat[prev][curr]);
            curr = prev;
        }

        curr = SINK;
        while (curr != SOURCE){
            int prev = parent[curr];
            adjMat[prev][curr] -= best;
            adjMat[curr][prev] += best;
            curr = prev;
        }

        maxFlow += best;
    }

    // If the maxFlow is the same as the number of edges, we failed!
    if (maxFlow != 2 * matchesRemaining){
        printf("NO\n");
        return;
    }

    // Else find out who won in which match
    for (int i = 1; i <= m; ++i){
        if (skip[i]) continue;
        int first = matches[i];
        matchOutcome[i] = adjMat[i][m + first];
    }

    // Print
    for (int i = 1; i <= m; ++i){
        printf("%d ", matchOutcome[i]);
    }
    printf("\n"); 
}

int main(){
    scanf("%d", &n);
    while (n != -1){
        solve();
        scanf("%d", &n);
    }

    return 0;
}
