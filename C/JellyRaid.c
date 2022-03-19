#include<stdio.h>

typedef struct {
    int x;
    int y;
    int dist;
} Coord;

Coord coord(int x, int y, int dist){
    Coord out;
    out.x = x;
    out.y = y;
    out.dist = dist;
    return out;
}

// BFS methods...
Coord ghettoQueue[1<<19];
int ghettoQueueHead = 0;
int ghettoQueueTail = 0;

void push(Coord x){
    ghettoQueue[ghettoQueueHead] = x;
    ghettoQueueHead++;
}

Coord pop(){
    Coord out = ghettoQueue[ghettoQueueTail];
    ghettoQueueTail++;
    return out;
}

int empty(){ return ghettoQueueHead == ghettoQueueTail;}


int dr[6] = {0, 1, 0, -1, 0, 0};  // 0, 0 = wait
char grid[64][64];
int visible[144][64][64];  // visible[period][gridx][gridy];
int visited[144][64][64];

int main(){
    // Scan in input
    int R, C;
    int bedx, bedy, jellyx, jellyy;
    scanf("%d %d", &R, &C);
    scanf(" (%d %d) (%d %d)", &bedx, &bedy, &jellyx, &jellyy);

    // Guard: is the bed the jelly?
    if (bedx == jellyx && bedy == jellyy){
        printf("0\n");
        return 0;
    }

    for (int i = 1; i <= R; ++i){
        for (int j = 1; j <= C; ++j){
            scanf(" %c", &grid[i][j]);
        }
    }

    int p; 
    scanf("%d", &p);
    for (int i = 0; i < p; ++i){
        int pp, x, y;
        scanf("%d", &pp);

        // For a stationary guard
        if (pp == 1){
            scanf(" (%d %d)", &x, &y);

            for(int d = 0; d < 4; ++d){
                int dx = x;
                int dy = y;

                while (dx >= 1 && dy >= 1 && dx <= R && dy <= C){
                    if (grid[dx][dy] == '#') break;
                    int t = 0;

                    while(t <= 120){
                        visible[t][dx][dy] = 1;
                        t++;
                    }

                    dx += dr[d];
                    dy += dr[d+1];
                }
            }
        }

        // For 2 or more path
        else{
            for (int j = 0; j < pp; ++j){
                scanf(" (%d %d)", &x, &y);

                // Precalculate where the patrolling masters can see
                // Since their period is at most 120, we can use that.
                // Note that this is essentially bfs on a changing grid
                for(int d = 0; d < 4; ++d){
                    int dx = x;
                    int dy = y;

                    while (dx >= 1 && dy >= 1 && dx <= R && dy <= C){
                        if (grid[dx][dy] == '#') break;
                        int post = j;
                        int negt = 2*pp-2 - j;

                        while(post <= 120){
                            visible[post][dx][dy] = 1;
                            visible[negt][dx][dy] = 1;
                            post += 2*pp-2;
                            negt += 2*pp-2;
                        }

                        dx += dr[d];
                        dy += dr[d+1];
                    }
                }
            }
        }
    }

    // One more cheese: Since the grid technically doesn't allow movements, just
    // say that outside of the board and walls are visible
    for (int t = 0; t < 120; ++t){
        for (int i = 0; i <= R+1; ++i){
            visible[t][i][0] = 8;
            visible[t][i][C+1] = 8;
        }
        for (int i = 0; i <= C+1; ++i){
            visible[t][0][i] = 8;
            visible[t][R+1][i] = 8;
        }
        for (int i = 1; i <= R; ++i){
            for (int j = 1; j <= C; ++j){
                if (grid[i][j] == '#'){
                    visible[t][i][j] = 8;
                }
            }
        }
    }

    // Now it's just a simple bfs:
    visited[0][bedx][bedy] = 1;
    push(coord(bedx, bedy, 1));
    while(!empty()){
        Coord curr = pop();
        int x = curr.x;
        int y = curr.y;
        int t = curr.dist - 1;

        for (int i = 0; i < 5; ++i){
            int newx = x + dr[i];
            int newy = y + dr[i+1];

            // If we reach jelly, yay!
            if (newx == jellyx && newy == jellyy){
                printf("%d\n", t+1);
                return 0;
            }

            if (visited[(t+1) % 120][newx][newy] != 0) continue;
            if (visible[(t+1) % 120][newx][newy]) continue;
            visited[(t+1) % 120][newx][newy] = curr.dist + 1;
            push(coord(newx, newy, curr.dist + 1));
        }
    }
    
    // Did not make it. Sad
    printf("IMPOSSIBLE\n");
    return 0;
}

