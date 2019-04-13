#include<stdio.h>

#define MIN(x, y) (x<y)?(x):(y)
#define MAX(x, y) (x>y)?(x):(y)

typedef struct {
    int campus;
    int start;
    int end;
} Lecture;

// Each of my data structres will take the test case number as 1st param
// Future David: This was a very bad idea. SO MUCH BLOAT!

// This gives the shortest path from each campus to another
int APSP[24][256][256];

// This is the list of lectures
Lecture lects [24][1024];

// This will store the adj matrix of which lectures can reach which other
int adjMat[24][1024][1024];

int toposort[24][1024];
int toposortHead[24];

int visited[24][1024];
int dp[24][1024];

void dfs(int T, int L, int node){
    if (visited[T][node]) return;
    visited[T][node] = 1;
    for (int i = 0; i < L; ++i){
        if (adjMat[T][node][i]){
            if (visited[T][i]) continue;
            dfs(T, L, i);
        }
    }
    toposort[T][toposortHead[T]] = node;
    toposortHead[T]++;
}

void ntnu(int T){
    int C, L;
    scanf("%d %d", &C, &L);

    // Populate the APSP matrix
    for (int i = 0; i < (C*(C-1))/2; ++i){
        int start, end, weight;
        scanf("%d %d %d", &start, &end, &weight);
        APSP[T][start][end] = weight;
        APSP[T][end][start] = weight;
    }

    // Do APSP
    for (int k = 0; k < C; ++k){
        for (int i = 0; i < C; ++i){
            for (int j = 0; j < C; ++j){
                APSP[T][i][j] = MIN(APSP[T][i][j], APSP[T][i][k] + APSP[T][k][j]);
            }
        }
    }

    // Scan in my lectures
    for (int i = 0; i < L; ++i){
        int campus, start, end;
        scanf("%d %d %d", &campus, &start, &end);
        lects[T][i].campus = campus;
        lects[T][i].start = start;
        lects[T][i].end = end;
    }

    // For each pair of lectures see if we can connect them
    for (int i = 0; i < L; ++i){
        for (int j = 0; j < L; ++j){
            if(i == j) continue;
            if(lects[T][j].start - lects[T][i].end >=
                    APSP[T][lects[T][i].campus][lects[T][j].campus]){
                adjMat[T][i][j] = 1;
            }
        }
    }

    // Final bit: Find the longest path in this DAG!
    // It starts off by doing toposort
    for (int i = 0; i < L; ++i){
        dfs(T, L, i);
    }

    // That's easy, ok last one. We are going to do dp.
    for (int i = L-1; i >= 0; --i){
        int curr = toposort[T][i];

        // Loop through all other lectures. See which other lecture we can reach.
        for (int j = 0; j < L; ++j){
            if (adjMat[T][curr][j]){
                dp[T][j] = MAX(dp[T][j], dp[T][curr] + 1);
            }
        }
    }

    // Wew we are done. Print the maximum of all of the DP array
    int maax = -1;
    for (int i = 0; i < L; ++i){
        maax = MAX(maax, dp[T][i]);
    }

    // Print that shit
    printf("%d\n", maax + 1);
}

int main(){
    // Scan in number of testcases
    int testcases;
    scanf("%d", &testcases);

    // For each testcase, run the main body of the code
    while (testcases){
        ntnu(testcases);
        --testcases;
    }
    return 0;
}
