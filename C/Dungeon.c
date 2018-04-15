#include<stdio.h>

typedef struct{
    int x;
    int y;
    int z;
    int t;
} Vertex;

int dr[8] = {0,0,1,0,0,-1,0,0};

// Set up ghettoQueue methods
Vertex ghettoQueue[300000];
int ghettoQueueHead;
int ghettoQueueTail;

void push(Vertex x){
    ghettoQueue[ghettoQueueHead++] = x;
}

Vertex pop(){
    return ghettoQueue[ghettoQueueTail++];
}

int size(){
    return ghettoQueueHead - ghettoQueueTail;
}

void init(){
    ghettoQueueHead = 0;
    ghettoQueueTail = 0;
}

// run method
void run(int L, int R, int C){
    char buffer[32];
    int grid[32][32][32];
    int visited[32][32][32];
    Vertex start, end;

    // Get my ghettoQueue up and running
    init();

    // Scan in input
    for (int i=0; i<L; ++i){
        for (int j=0; j<R; ++j){
            scanf("%s", buffer);
            for (int k=0; k<C; ++k){
                if (buffer[k] == '#'){
                    grid[i][j][k] = -1;
                }
                else if (buffer[k] == '.'){
                    grid[i][j][k] = 0;
                }
                else if (buffer[k] == 'S'){
                    start = (Vertex) {i, j, k, 0};
                }
                else if (buffer[k] == 'E'){
                    end = (Vertex) {i, j, k, 0};
                }

                // While we are at it, reset the visited array
                visited[i][j][k] = 0;
            }
        }
    }

    // Do a BFS from start.
    push(start);

    while (size()){
        Vertex pos = pop();

        // If we have reached the end, break.
        if (pos.x == end.x && pos.y == end.y && pos.z == end.z){
            printf("Escaped in %d minute(s).\n", pos.t);
            return;
        }

        // For the 6 new directions, if we can go there, go there.
        for (int i=0; i<6; ++i){
            int newrow = pos.x + dr[i];
            int newcol = pos.y + dr[i+1];
            int newhei = pos.z + dr[i+2];

            // Check out of bounds
            if (newrow < 0 || newrow >= L ||
                newcol < 0 || newcol >= R ||
                newhei < 0 || newhei >= C){
                continue;
            }

            // If we've been here before, or we cannot go there
            if (visited[newrow][newcol][newhei] || grid[newrow][newcol][newhei] == -1){
                continue;
            }
            visited[newrow][newcol][newhei] = 1;
            push((Vertex) {newrow, newcol, newhei, pos.t+1});
        }
    }

    printf ("Trapped!\n");
}

int main(){
    int L, R, C;
    scanf ("%d %d %d ", &L, &R, &C);

    while (L != 0 && R != 0 && C != 0){
        run (L, R, C);
        scanf ("%d %d %d", &L, &R, &C);
    }

    return 0;
}
