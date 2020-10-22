#include<stdio.h>
#include<stdlib.h>

int c, a;
char grid[110000];
int dr[5] = {0, 0, -1, 0, 1};
int visited[110000];

int queue[1600000];
int queueTail = 0;
int queueHead = 0;

void push(int x){
    queue[queueHead] = x;
    queueHead++;
}

int pop(){
    int out = queue[queueTail];
    queueTail++;
    return out;
}

int empty(){
    return queueTail == queueHead;
}

int bfs(int x, int y){
    // If the motorcycles are moving clockwise => gon is movine counter clockwise!
    push(0);

    while (!empty()){
        int curr = pop();
        int x = curr % a;
        int y = curr / a;

        // Visit the neighbors
        for (int i = 0; i < 4; ++i){
            int newx2 = x + dr[i];
            int newx = newx2 - 1; // Since gon is moving ccw
            int newy = y + dr[i+1];

            if (newy < 0) continue;

            if (newx < 0) newx += a;
            if (newx2 < 0) newx2 += a;
            newx %= a;
            newx2 %= a;

            // Are we at the end?
            if (newy == c){
                return visited[curr];
            }

            // If we have not been there before, and it is not a motorcycle, visit.
            int encode = newy * a + newx;

            if (grid[encode] == 'M') continue;
            if (i && grid[newy * a + newx2] == 'M') continue;
            if (visited[encode]) continue;
            visited[encode] = visited[curr]+1;

            push(encode);
        }
    }

    // If we are here, there is no way to get to the hall
    return -1;
}

int main(){
    // Scan in input
    scanf("%d %d", &c, &a);

    for (int i = 0; i < c; ++i){
        for (int j = 0; j < a; ++j){
            scanf(" %c", &grid[i*a + j]);
        }
    }

    // Do BFS
    visited[0] = 1;
    printf("%d\n", bfs(0, 0));

    return 0;
}

