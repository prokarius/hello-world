#include<stdio.h>

#define INF 1<<29

int grid[905];
int portals[905][5];
int distance[905];
int visited[905];
int neverEscape[905];

// adjList schema looks like this:
// adjList[squareId][0][0] = number of edges
// adjList[squareId][x][0] = end point of the edge
// adjList[squareId][x][1] = distance
int adjList[905][5][2];

int dr[5] = {0, 1, 0, -1, 0};

// We will need to dfs. Set up the dfs methods 
int dfsStack[905];
int dfsStackHead = 0;

void push(int e){
    dfsStack[dfsStackHead] = e;
    dfsStackHead++;
}

int pop(){
    dfsStackHead--;
    return dfsStack[dfsStackHead];
}

int queueNotEmpty(){
    return dfsStackHead != 0;
}

// This is the main run method
void run(int W, int H){
    // Scan in input
    int numGraves;
    scanf("%d", &numGraves);
    for (int i = 0; i < numGraves; ++i){
        int graveRow, graveCol;
        scanf("%d %d", &graveRow, &graveCol);
        grid[graveRow * 30 + graveCol] = 1;
    }

    int numStones;
    scanf("%d", &numStones);
    for (int i = 2; i < numStones+2; ++i){
        scanf ("%d %d %d %d %d", &portals[i][0], &portals[i][1], &portals[i][2], &portals[i][3], &portals[i][4]);
        grid[portals[i][0] * 30 + portals[i][1]] = i;
    }

    // Construct the adjMatrix
    // At this point, the grid will have 0 1 and 2+
    // 0 represents nothing. 1 represents gravestone.
    // 2 or more represents a portal. The details are in the portals array
    for (int currRow = 0; currRow < W; ++currRow){
        for (int currCol = 0; currCol < H; ++currCol){
            if (grid[currRow * 30 + currCol] == 1) continue;

            int currentSquare = currRow * 30 + currCol;
            if (grid[currRow * 30 + currCol] > 1){
                int neighbourSquare = portals[grid[currRow * 30 + currCol]][2] * 30 + portals[grid[currRow * 30 + currCol]][3];
                adjList[currentSquare][0][0] = 1;
                adjList[currentSquare][1][0] = neighbourSquare;
                adjList[currentSquare][1][1] = portals[grid[currRow * 30 + currCol]][4];
                continue;
            }

            for (int k = 0; k < 4; ++k){
                int newRow = currRow + dr[k];
                int newCol = currCol + dr[k+1];

                if (newRow < 0 || newRow >= W || newCol < 0 || newCol >= H) continue;
                int neighbourSquare = newRow*30 + newCol;
                adjList[currentSquare][0][0]++;
                adjList[currentSquare][adjList[currentSquare][0][0]][0] = neighbourSquare;
                adjList[currentSquare][adjList[currentSquare][0][0]][1] = 1;
            }
        }
    }

    /*
    for (int i = 0; i < W; ++i){
        for (int j = 0; j < H; ++j){
            if (i == 0 && j == 0) printf("S");
            else if (i == W-1 && j == H-1) printf("W");
            else printf("%d", grid[i*30 + j]);
        }
        printf("\n");
    }
    */

    // There are no paths leaving the exit
    adjList[(W-1)*30 + H-1][0][0] = 0;

    // Initialise the distance
    distance[0] = 0;

    // Do Bellman Ford's here
    for (int _ = 0; _ < W*H; _++){
        for (int curr = 0; curr < 900; ++curr){
            for (int edgenum = 1; edgenum <= adjList[curr][0][0]; edgenum++){
                if (distance[curr] == INF) continue;
                if (distance[curr] + adjList[curr][edgenum][1] >= distance[adjList[curr][edgenum][0]]) continue;
                distance[adjList[curr][edgenum][0]] = distance[curr] + adjList[curr][edgenum][1];
            }
        }
    }

    int negativeCycle = INF;
    // Check for negative cycles
    for (int curr = 0; curr < 900; ++curr){
        for (int edgenum = 1; edgenum <= adjList[curr][0][0]; edgenum++){
            if (distance[curr] + adjList[curr][edgenum][1] < distance[adjList[curr][edgenum][0]]){
                negativeCycle = curr;
                neverEscape[adjList[curr][edgenum][0]] = 1;
            }
        }
    }
    //printf("%d\n", negativeCycle);

    // If we have a negative cycle, check if we can reach it
    // negativeCycle variable stores the entry point to
    if (negativeCycle != INF){
        push(0);
        while (queueNotEmpty()){
            int curr = pop();
            if (neverEscape[curr]){
                printf("Never\n");
                return;
            }
            for (int edgenum = 1; edgenum <= adjList[curr][0][0]; edgenum++){
                if (visited[adjList[curr][edgenum][0]]) continue;
                visited[adjList[curr][edgenum][0]] = 1;
                push(adjList[curr][edgenum][0]);
            }
        }
    }

    // Ensure that we can even reach the end
    if (distance[(W-1)*30 + H-1] == INF){
        printf("Impossible\n");
        return;
    }

    // Else, just print the shortest time to reach the exit
    printf("%d\n", distance[(W-1)*30 + H-1]);
}

// Function to reset the solution
void resetGrid(){
    // Reset the grid
    for (int i = 0; i < 905; ++i){
        grid[i] = 0;
    }

    // Reset portals
    for (int i = 0; i < 905; ++i){
        portals[i][0] = 0;
        portals[i][1] = 0;
        portals[i][2] = 0;
        portals[i][3] = 0;
        portals[i][4] = 0;
    }

    // Reset nodes that are part of negative Cycles
    for (int i = 0; i < 905; ++i){
        neverEscape[i] = 0;
    }

    // Reset adjlist
    for (int i = 0; i < 905; ++i){
        for (int j = 0; j < 5; ++j){
            adjList[i][j][0] = 0;
            adjList[i][j][1] = 0;
        }
    }

    // Reset the distance array
    for (int i = 0; i < 905; ++i){
        distance[i] = INF;
    }

    // Reset visited array
    for (int i = 0; i < 905; ++i){
        visited[i] = 0;
    }

    // Reset the stack
    dfsStackHead = 0;
}

int main(){
    int W, H;
    scanf("%d %d", &W, &H);
    while (!(W == 0 && H == 0)){
        resetGrid();
        run(W, H);
        scanf("%d %d", &W, &H);
    }
    return 0;
}
