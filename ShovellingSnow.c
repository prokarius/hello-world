#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

typedef struct pair{
    int r;
    int c;
    int w;
} Pair;

int dr[5] = {0, -1, 0, 1, 0}, house[6] = {1, 2, 3, 6, 7, 11};
int pos[4], grid[402], APSP[402][402], prev[402][402];
Pair ghettoDeque [5000];
int dequeH, dequeT, visited[402];

// GhettoDeque Methods
void push(Pair x){
    ghettoDeque[dequeT++] = x;
}

void pushfront (Pair x){
    ghettoDeque[--dequeH] = x;
}

Pair pop(){
    return ghettoDeque[dequeH++];
}

int main(){
    int i, j, k, R, C;
    char ph;
    scanf ("%d %d", &C, &R);
    while (R){
        int best = 9999;

        // Read the input. Pretend houses are worth 0.
        // Essentially, pos is the positions of the 4 houses, encoded.
        // grid tracks the grid. 1 for snow, 0 for path, -1 for obstacles

        for (i=0; i<R; ++i){
            for (j=0; j<C; ++j){
                scanf(" %c", &ph);
                if (ph >= 'A' && ph <= 'D') pos[ph - 'A'] = i*C + j;
                if (ph == '#') grid[i*C + j] = -1;
                else if (ph == 'o') grid[i*C + j] = 1;
                else grid[i*C + j] = 0;
            }
        }

        // Reset the APSP array
        for (i=0; i<R*C; ++i){
            for (j=0; j<R*C; ++j) APSP[i][j] = 999;
        }

        // The idea is to brute force the Steiner points. But how do we know
        // what is the cost of going from one edge to another?
        // We need to dijkstra from all points to all other points!
        // BUT WAIT, DO WE NEED DIJKSTRA? The cost of the points are only 0s or
        // 1s. For all points we can do a BFS (modified).
        for (i = 0; i<R*C; ++i){
            // Check if we are starting from a #. Set it to 999 if so.
            if (grid[i] == -1) continue;

            // Reset our dfs stuff
            dequeH = 2500;
            dequeT = 2500;
            for (j = 0; j<R*C; ++j) visited[j] = 0;

            // Create a node to stuff into our BFS queue. The staring point is
            // the point in question, and the weights of our nodes will be the
            // weights of all the snow, including the current square.
            Pair x = {i/C, i%C, grid[i]};
            push(x);

            // While we still have elements in our deque, BFS from there
            while (dequeH < dequeT){
                x = pop();
                int currr = x.r;
                int currc = x.c;

                // If we have visited this node before, the current distance
                // won't be any better than what we had before. Don't bother.
                if (visited[currr*C + currc]) continue;
                int w = x.w;
                ++visited[currr*C + currc];
                APSP[i][currr*C + currc] = w;

                // For our 4 directions, calculate the stuff.
                for (k = 0; k < 4; ++k){
                    int nextr = currr + dr[k];
                    int nextc = currc + dr[k+1];

                    // If we are out of bounds, don't add it
                    // If we have visited the node before, don't add it.
                    // If the node to go is an obstacle, don't add it.
                    // Push to the front if the gridweight is 0, and to the back
                    // if the grid weight is 1.
                    if (nextr >= R || nextr < 0 || nextc < 0 || nextc >= C) continue;
                    if (visited[nextr*C + nextc]) continue;
                    int gridweight = grid[nextr*C + nextc];
                    if (gridweight == -1) continue;
                    Pair y = {nextr, nextc, w+gridweight};
                    if (gridweight) push(y);
                    else pushfront(y);
                }
            }
        }

        // We will now brute force two Steiner points.
        // Calculate the distance and store it as the best.
        // For each of the positions, ignore it if it's an obstacle.
        int h1, h2, h3, h4, sp1, sp2;
        int bestsp1, bestsp2;
        for (sp1 = 0; sp1 < R*C; ++sp1){
            if (grid[sp1] == -1) continue;
            for (sp2 = 0 ; sp2 < R*C; ++sp2){
                if (grid[sp2] == -1) continue;
                for (k = 0; k<3; ++k){
                    h1 = pos[house[k]/4];
                    h2 = pos[house[k]%4];
                    h3 = pos[house[5-k]/4];
                    h4 = pos[house[5-k]%4];
                    int cost = APSP[sp1][sp2] + APSP[h1][sp1] + APSP[h2][sp1] +
                               APSP[h3][sp2] + APSP[h4][sp2] - 2*(grid[sp1] + grid[sp2]);
                    if (cost <= best){
                        best = MIN(best, cost);
                        bestsp1 = sp1;
                        bestsp2 = sp2;
                    }
                }
            }
        }

        // From here, we want to recover the path that we took
        

        printf ("%d\n", best);

        // Reset everything
        for (i = 0; i<4; ++i) pos[i] = 0;
        for (i = 0; i<R*C; ++i) grid[i] = 0;
        scanf ("%d %d", &C, &R);
    }
    return 0;
}

/*

// SHOVELLING SNOW COST //

#include<stdio.h>
#define MIN(x,y) (x<y)?(x):(y)

typedef struct pair{
    int r;
    int c;
    int w;
} Pair;

int dr[5] = {0, -1, 0, 1, 0}, house[6] = {1, 2, 3, 6, 7, 11};
int pos[4], grid[402], APSP[402][402];
Pair ghettoDeque [5000];
int dequeH, dequeT, visited[402];

// GhettoDeque Methods
void push(Pair x){
    ghettoDeque[dequeT++] = x;
}

void pushfront (Pair x){
    ghettoDeque[--dequeH] = x;
}

Pair pop(){
    return ghettoDeque[dequeH++];
}

int main(){
    int i, j, k, R, C;
    char ph;
    scanf ("%d %d", &C, &R);
    while (R){
        int best = 9999;

        // Read the input. Pretend houses are worth 0.
        // Essentially, pos is the positions of the 4 houses, encoded.
        // grid tracks the grid. 1 for snow, 0 for path, -1 for obstacles

        for (i=0; i<R; ++i){
            for (j=0; j<C; ++j){
                scanf(" %c", &ph);
                if (ph == 'A') pos[0] = i*C + j;
                else if (ph == 'B') pos[1] = i*C + j;
                else if (ph == 'C') pos[2] = i*C + j;
                else if (ph == 'D') pos[3] = i*C + j;
                if (ph == '#') grid[i*C + j] = -1;
                else if (ph == 'o') grid[i*C + j] = 1;
                else grid[i*C + j] = 0;
            }
        }

        // Reset the APSP array
        for (i=0; i<R*C; ++i){
            for (j=0; j<R*C; ++j) APSP[i][j] = 999;
        }

        // The idea is to brute force the Steiner points. But how do we know
        // what is the cost of going from one edge to another?
        // We need to dijkstra from all points to all other points!
        // BUT WAIT, DO WE NEED DIJKSTRA? The cost of the points are only 0s or
        // 1s. For all points we can do a BFS (modified).
        for (i = 0; i<R*C; ++i){
            // Check if we are starting from a #. Set it to 999 if so.
            if (grid[i] == -1) continue;

            // Reset our dfs stuff
            dequeH = 2500;
            dequeT = 2500;
            for (j = 0; j<R*C; ++j) visited[j] = 0;

            // Create a node to stuff into our BFS queue. The staring point is
            // the point in question, and the weights of our nodes will be the
            // weights of all the snow, including the current square.
            Pair x = {i/C, i%C, grid[i]};
            push(x);

            // While we still have elements in our deque, BFS from there
            while (dequeH < dequeT){
                x = pop();
                int currr = x.r;
                int currc = x.c;

                // If we have visited this node before, the current distance
                // won't be any better than what we had before. Don't bother.
                if (visited[currr*C + currc]) continue;
                int w = x.w;
                ++visited[currr*C + currc];
                APSP[i][currr*C + currc] = w;

                // For our 4 directions, calculate the stuff.
                for (k = 0; k < 4; ++k){
                    int nextr = currr + dr[k];
                    int nextc = currc + dr[k+1];

                    // If we are out of bounds, don't add it
                    // If we have visited the node before, don't add it.
                    // If the node to go is an obstacle, don't add it.
                    // Push to the front if the gridweight is 0, and to the back
                    // if the grid weight is 1.
                    if (nextr >= R || nextr < 0 || nextc < 0 || nextc >= C) continue;
                    if (visited[nextr*C + nextc]) continue;
                    int gridweight = grid[nextr*C + nextc];
                    if (gridweight == -1) continue;
                    Pair y = {nextr, nextc, w+gridweight};
                    if (gridweight) push(y);
                    else pushfront(y);
                }
            }
        }

        // We will now brute force two Steiner points.
        // Calculate the distance and store it as the best.
        // For each of the positions, ignore it if it's an obstacle.
        int h1, h2, h3, h4, sp1, sp2;
        for (sp1 = 0; sp1 < R*C; ++sp1){
            if (grid[sp1] == -1) continue;
            for (sp2 = 0 ; sp2 < R*C; ++sp2){
                if (grid[sp2] == -1) continue;
                for (k = 0; k<3; ++k){
                    h1 = pos[house[k]/4];
                    h2 = pos[house[k]%4];
                    h3 = pos[house[5-k]/4];
                    h4 = pos[house[5-k]%4];
                    int cost = APSP[sp1][sp2] + APSP[h1][sp1] + APSP[h2][sp1] +
                               APSP[h3][sp2] + APSP[h4][sp2] - 2*(grid[sp1] + grid[sp2]);
                    best = MIN(best, cost);
                }
            }
        }

        printf ("%d\n", best);

        // Reset everything
        for (i = 0; i<4; ++i) pos[i] = 0;
        for (i = 0; i<R*C; ++i) grid[i] = 0;
        scanf ("%d %d", &C, &R);
    }
    return 0;
}

*/
