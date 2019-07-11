#include<stdio.h>

int n;
int adjMat[1024][1024];
int visited[1024];
int topoSort[1024];
int topoSortHead = 0;

// Toposort methods
void push(int x){
    topoSort[topoSortHead++] = x;
}


// Generates the toposort
int toposort(int node){
    visited[node] = 1;

    for (int i = 0; i < n; ++i){
        if (adjMat[node][i] == 1 && !visited[i]){
            toposort(i);
        }
    }

    push(node);
}

int main(){
    // Scan in input
    scanf("%d", &n);

    // Scan in adjList
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            char ph;
            scanf(" %c", &ph);

            if (i == j) adjMat[i][j] = 0;
            else adjMat[i][j] = ph - '0';
        }
    }

    // DFS from Hank to see if he manages to reach everyone
    toposort(0);

    // If everyone can be reached, topoSortHead will be n;
    if (topoSortHead != n){
        printf("impossible\n");
        return 0;
    }

    // Else print the shit
    printf("%d", topoSort[0]);
    for (int i = 1; i < n; ++i){
        printf(" %d", topoSort[i]);
    }
    printf("\n");

    return 0;
}
