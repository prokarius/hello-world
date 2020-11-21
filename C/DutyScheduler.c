#include<stdio.h>

int n, m;
char TAs[64][32];

// 0 to m = TA nodes. m to m+n = Day nodes
int original[128][128];
int adjMatrix[128][128];
int visited[128];

int dfs(int curr, int sink){
    if (visited[curr]) return 0;
    if (curr == sink) return 1;

    visited[curr] = 1;

    for (int i = 0; i < n + m + 2; ++i){
        if (adjMatrix[curr][i] == 0) continue;
        int newFlow = dfs(i, sink);

        if (newFlow){
            adjMatrix[curr][i] -= 1;
            adjMatrix[i][curr] += 1;
            return 1;
        }
    }

    return 0;
}

// The adjMatrix should be set before coming into this function
int ff(){
    int flow = -1;

    int SOURCE = m + n;
    int SINK = m + n + 1;

    do {
        for (int i = 0; i <= m + n + 2; ++i) visited[i] = 0;
        flow += 1;
    } while (dfs(SOURCE, SINK));

    return flow;
}

int main(){
    // Scan in input
    scanf("%d %d", &m, &n);

    int SOURCE = m + n;
    int SINK = m + n + 1;

    for (int i = 0; i < m; ++i){
        scanf(" %s", TAs[i]);
        int days;
        scanf("%d", &days);
        for (int j = 0; j < days; ++j){
            int day;
            scanf("%d", &day);
            day--;
            original[i][m+day] = 1;
        }
    }

    // Then connect each day to SINK with flow of 2
    for (int i = 0; i < n; ++i){
        original[m+i][SINK] = 2;
    }

    // Loop over all the differeces in days:
    int differences = 1;
    while (1){
        // Now we just need to copy this array
        for (int i = 0; i < m + n + 2; ++i){
            for (int j = 0; j < m + n + 2; ++j){
                adjMatrix[i][j] = original[i][j];
            }
        }

        // Connect each TA to the source with differences
        for (int i = 0; i < m; ++i){
            adjMatrix[SOURCE][i] = differences;
        }

        // Run fake FF
        int out = ff();
        if (out == n * 2) break;
        differences ++;
    }

    // Print the connections by looking at the back edges
    printf("%d\n", differences);

    for (int i = 0; i < n; ++i){
        printf("Day %d:", i+1);

        for (int j = 0; j < m; ++j){
            if (adjMatrix[m+i][j]){
                printf(" %s", TAs[j]);
            }
        }

        printf("\n");
    }

    return 0;
}

