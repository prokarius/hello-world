#include<stdio.h>

typedef struct {
    int x;
    int y;
} Coordinate;

Coordinate coordinate(int x, int y){
    Coordinate output;
    output.x = x;
    output.y = y;
    return output;
}

// BFS methods
Coordinate bfs[1<<16];
int bfsHead = 0;
int bfsTail = 0;

int size(){
    return bfsHead - bfsTail;
}

void push(Coordinate new){
    bfs[bfsHead] = new;
    bfsHead++;
}

Coordinate pop(){
    Coordinate output = bfs[bfsTail];
    bfsTail++;
    return output;
}

char grid[128][128];
int dp[128][128]; // Stores the number of moves it takes
int dr[10] = {1, 2, -1, -2, 1, -2, -1, 2, 1};
int n;

int main(){
    // Scan in input
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%s", grid[i]);
    }

    // Find the starting position
    int startX, startY;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (grid[i][j] == 'K'){
                startX = i;
                startY = j;
            }
        }
    }

    // Now we will do BFS
    push(coordinate(startX, startY));
    dp[startX][startY] = 1;

    while (size() > 0){
        Coordinate curr = pop();
        int currx = curr.x;
        int curry = curr.y;

        // Have we reached the end?
        if (currx == 0 && curry == 0){
            printf("%d\n", dp[0][0]-1);
            return 0;
        }

        // Else try to move
        for (int i = 0; i < 8; ++i){
            int newX = currx + dr[i];
            int newY = curry + dr[i+1];

            // Out of bounds check
            if (newX < 0 || newY < 0 || newX >= n || newY >= n) continue;

            // Have we been here before?
            if (dp[newX][newY] != 0) continue;

            // Is the square disallowed?
            if (grid[newX][newY] == '#') continue;

            // Push it into the bfs array!
            dp[newX][newY] = dp[currx][curry] + 1;
            push(coordinate(newX, newY));
        }
    }

    // If we have exhausted all the possible moves, then impossible
    printf("-1\n");
    return 0;
}
