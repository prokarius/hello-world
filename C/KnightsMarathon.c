#include<stdio.h>

int ABS(int x){
    return (x < 0)?(-x):(x);
}

int dr[9] = {1, 2, -1, -2, 1, -2, -1, 2, 1};
int dp[128][128];

typedef struct {
    int x;
    int y;
    int jumps;
} Coord;

Coord coord(int x, int y, int jump){
    Coord out;
    out.x = x;
    out.y = y;
    out.jumps = jump;
    return out;
}

Coord ghettoQueue[1<<15];
int bfsHead = 0;
int bfsTail = 0;

void push(Coord coord){
    ghettoQueue[bfsHead] = coord;
    bfsHead++;
}

Coord pop(){
    Coord out = ghettoQueue[bfsTail];
    bfsTail++;
    return out;
}

int empty(){
    return bfsHead == bfsTail;
}

void bfs(int x, int y){
    push(coord(x, y, 0));
    dp[x][y] = 0;

    // Jump the knights
    while(!empty()){
        Coord curr = pop();
        for (int i = 0; i < 8; ++i){
            int newX = curr.x + dr[i];
            int newY = curr.y + dr[i+1];
            if (newX < 0 || newY < 0 || newX >= 128 || newY >= 128) continue;
            if (dp[newX][newY] <= curr.jumps + 1) continue;
            dp[newX][newY] = curr.jumps + 1;
            push(coord(newX, newY, curr.jumps + 1));
        }
    }
}

int main(){
    // Scan in input
    int nx, ny, kx, ky, cx, cy;
    scanf("%d %d %d %d %d %d", &nx, &ny, &kx, &ky, &cx, &cy);
    
    // Initialize the dp array
    for (int i = 0; i < 128; ++i){
        for (int j = 0; j < 128; ++j){
            dp[i][j] = 1<<16;
        }
    }
    bfs(63, 63); // Origin is (63, 63)

    // Sneaky corner case (literally) it seems:
    // Im sorry, I just wanted to solve this and be done...
    // There is probably a better way...
    if ((cx == 0 && cy == 0 && kx == 1 && ky == 1) ||
        (cx == 1 && cy == 1 && kx == 0 && ky == 0) || 
        (cx == nx-1 && cy == 0 && kx == nx-2 && ky == 1) ||
        (cx == nx-2 && cy == 1 && kx == nx-1 && ky == 0) ||
        (cx == nx-1 && cy == ny-1 && kx == nx-2 && ky == ny-2) ||
        (cx == nx-2 && cy == ny-2 && kx == nx-1 && ky == ny-1) ||
        (cx == 1 && cy == ny-2 && kx == 0 && ky == ny-1) ||
        (cx == 0 && cy == ny-1 && kx == 1 && ky == ny-2)){
        printf("4\n");
        return 0;
    }

    // Find the delta distance
    int dx = ABS(kx - cx);
    int dy = ABS(ky - cy);

    if (dy > dx){
        int temp = dy;
        dy = dx;
        dx = temp;
    }

    // Case: if dx and dy <= 15, just use dp array
    if (dx <= 63 && dy <= 63){
        printf("%d\n", dp[dx+63][dy+63]);
        return 0;
    }

    // If not, the knight is too far away.
    // Case 1: cover as much diagonal distance with (2, 1) moves, then the remaining
    // horizontal distance with (2, 1) + (2, -1) moves.
    if (dx >= 2 * dy){
        int dd = (dx - 2 * dy);
        int diagonalJumps = dy - 12;
        int horizontalJumps = (dd / 4) - 4;

        dx -= (2 * diagonalJumps) + (4 * horizontalJumps);
        dy -= (1 * diagonalJumps);

        printf("%d\n", dp[dx+63][dy+63] + 2 * horizontalJumps + diagonalJumps);
        return 0;
    }

    // Case 2: cover as much diagonal distance with (2, 1) moves, then the remaining
    // diagonal distance with (2, 1) + (1, 2) moves.
    else { // dy <= dx < 2*dy
        int dd = (dx - dy);
    
        int longDiagonalJumps = dd - 12;
        int diagonalJumps = ((dy - dd) / 3) - 4;

        dx -= (longDiagonalJumps * 2) + (diagonalJumps * 3);
        dy -= (longDiagonalJumps * 1) + (diagonalJumps * 3);

        printf("%d\n", dp[dx+63][dy+63] + longDiagonalJumps + diagonalJumps * 2);
        return 0;
    }
}

