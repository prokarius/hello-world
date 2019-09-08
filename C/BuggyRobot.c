#include<stdio.h>
#include<string.h>

typedef struct{
    int x;
    int y;
    int wordPos;
    int cost;
} Dijkstra;

Dijkstra dijkstra(int x, int y, int wordPos, int cost){
    Dijkstra output;
    output.x = x;
    output.y = y;
    output.wordPos = wordPos;
    output.cost = cost;
    return output;
}

// BFS (0 - 1 Dijkstra) methods
Dijkstra bfs[1<<25];
int bfsHead = 1<<24;
int bfsTail = 1<<24;

void pushFront(Dijkstra new){
    bfsHead--;
    bfs[bfsHead] = new;
}

void pushBack(Dijkstra new){
    bfs[bfsTail] = new;
    bfsTail++;
}

Dijkstra pop(){
    Dijkstra output = bfs[bfsHead];
    bfsHead++;
    return output;
}

int dr[5] = {0, 1, 0, -1, 0};

// Input grid
char grid[64][64];
char instructions[64];

// dp[x][y][z] stores the cost at pos (x,y) and character z
int dp[64][64][64];

int main(){
    // Initialize the dp array
    for (int i = 0; i < 64; ++i){
        for (int j = 0; j < 64; ++j){
            for (int k = 0; k < 64; ++k){
                dp[i][j][k] = 1<<30;
            }
        }
    }

    // Scan in input
    int H, W;
    scanf("%d %d", &H, &W);

    int startx, starty, endx, endy;
    for (int i = 0; i < H; ++i){
        for (int j = 0; j < W; ++j){
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'S'){
                startx = i;
                starty = j;
            }
            else if (grid[i][j] == 'G'){
                endx = i;
                endy = j;
            }
        }
    }

    scanf("%s", instructions);
    int len = strlen(instructions);

    // Do BFS on the array
    pushBack(dijkstra(startx, starty, 0, 0));

    while (bfsHead <= bfsTail){
        Dijkstra curr = pop();
        int currx = curr.x;
        int curry = curr.y;
        int currWordPos = curr.wordPos;
        int currCost = curr.cost;

        // Since this is 0-1 Dijkstra, break if we reached the end
        if (currx == endx && curry == endy){
            printf("%d\n", currCost);
            break;
        }

        // Check if we have been to the tile before
        if (dp[currx][curry][currWordPos] < currCost) continue;

        // Option 1: Add a letter.
        // Effect: +1 to cost, +/- 1 to each direction
        for (int i = 0; i < 4; ++i){
            int newx = currx + dr[i];
            int newy = curry + dr[i+1];

            // Check for out of bounds
            if (newx < 0 || newy < 0 || newx >= H || newy >= W) continue;

            // Check for walls
            if (grid[newx][newy] == '#') continue;
            if (dp[newx][newy][currWordPos] > currCost+1){
                pushBack(dijkstra(newx, newy, currWordPos, currCost+1));
                dp[newx][newy][currWordPos] = currCost+1;
            }
        }

        // Option 2: Ignore the letter.
        // Effect: +1 to wordPos, +1 to cost

        // But you can only do this if we still have characters
        if (currWordPos >= len) continue;
        if (dp[currx][curry][currWordPos+1] > currCost +1){
            pushBack(dijkstra(currx, curry, currWordPos+1, currCost+1));
            dp[currx][curry][currWordPos+1] = currCost+1;
        }

        // Option 3: Follow the letter.
        // Effect: +/- 1 to each direction
        int newx = currx;
        int newy = curry;
        switch (instructions[currWordPos]){
            case 'R':
                newy = curry + 1;
                break;
            case 'L':
                newy = curry - 1;
                break;
            case 'U':
                newx = currx - 1;
                break;
            case 'D':
                newx = currx + 1;
                break;
        }
        // Check for out of bounds, or for walls
        if (newx < 0 || newy < 0 || newx >= H || newy >= W || grid[newx][newy] == '#'){
            if (dp[currx][curry][currWordPos+1] > currCost){
                pushFront(dijkstra(currx, curry, currWordPos+1, currCost));
                dp[currx][curry][currWordPos+1] = currCost;
            }
        }
        else {
            if (dp[newx][newy][currWordPos+1] > currCost){
                pushFront(dijkstra(newx, newy, currWordPos+1, currCost));
                dp[newx][newy][currWordPos+1] = currCost;
            }
        }
    }

    return 0;
}

