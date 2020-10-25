#include<stdio.h>

typedef struct{
    int x;
    int y;
} Coord;

Coord coord(int x, int y){
    Coord out = {x, y};
    return out;
}

int dist(Coord a, Coord b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Ghetto BFS
Coord bfs[1<<18];
int bfsHead;
int bfsTail;

void push(Coord x){ bfs[bfsHead++] = x; }
Coord pop(){ return bfs[bfsTail++]; }
int notEmpty(){ return bfsHead != bfsTail; }
void clearBFS(){ bfsHead = 0; bfsTail = 0; }

char grid[512][512];
int seen[512][512];
int dr[5] = {0, 1, 0, -1, 0};

int main(){
    int r, s;
    scanf("%d %d", &r, &s);

    for (int i = 0; i < r; ++i){
        for (int j = 0; j < s; ++j){
            scanf(" %c", &grid[i][j]);
        }
    }

    // But each run of BFS takes O(n**2) time. And you need to run at least O(n**2)
    // times BFS! In total this is O(n**4) = 62B. Won't this TLE?
    // BFS works because the more apple trees there are, you won't need to explore
    // the whole grid in order for BFS to work.

    // Each new tree kinda "splits the search space in half".
    // So this is kinda like sum of geometric series = O(n**2). Possible

    int g;
    scanf("%d", &g);
    for (int i = 1; i <= g; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;  // 1 based indexing is stupid
        if (grid[x][y] == 'x'){
            printf("0\n");
            continue;
        }

        // Do BFS
        int best = 1<<19;
        clearBFS();

        // Mark that we have been to this square in the current generation
        seen[x][y] = i;
        Coord original = coord(x, y);
        push(original);

        while (notEmpty()){
            Coord curr = pop();

            // Prune if we are worse than best
            if (best < dist(original, curr)) continue;

            for (int j = 0; j < 4; ++j){
                int newX = dr[j] + curr.x;
                int newY = dr[j + 1] + curr.y;
                
                // Out of bounds checks
                if (newX < 0 || newY < 0 || newX >= r || newY >= s) continue;

                // Have we been here this generation?
                if (seen[newX][newY] == i) continue;
                seen[newX][newY] = i;

                Coord newCoord = coord(newX, newY);
                int newDist = dist(newCoord, original);

                // No point going deeper if we can't improve
                if (newDist >= best) continue;

                // Are we at a tree?
                if (grid[newX][newY] == 'x') best = newDist;
                
                // Push the new coords
                push(newCoord);
            }
        }

        printf("%d\n", best);
        grid[x][y] = 'x';
    }

    return 0;
}

