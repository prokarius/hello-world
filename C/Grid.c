#include<stdio.h>

int grid[250005];
int adjlist[250005][5];
int visited[250005];
long long ghettoqueue[2000000];
int ghettoqueueHead = 0;
int ghettoqueueTail = 0;
int R, C;
int dr[5] = {0, 1, 0, -1, 0};

void push(long long v){
    ghettoqueue[ghettoqueueTail++] = v;
}

long long pop(){
    return ghettoqueue[ghettoqueueHead++];
}

int bfs(){
    // Check the grid size first
    if (R*C == 1){
        return 0;
    }

    // Push vertex 0 in it
    push(0LL);

    // While the queue is not empty, bfs from there
    while (ghettoqueueHead != ghettoqueueTail){
        long long v = pop();
        int steps = v%1000000;
        int vertex = v/1000000;

        // Check if we have reached the end:
        if (vertex == R*C-1){
            return steps;
        }

        // If not, set that we have visited him before.
        visited[vertex] = 1;

        // Then push his unvisited vertices into the queue.
        for (int i=1; i<adjlist[vertex][0]; ++i){
            if (visited[adjlist[vertex][i]] == 0){
                visited[adjlist[vertex][i]] = 1;
                long long topush = adjlist[vertex][i]*1000000 + steps+1;
                push(topush);
            }
        }
    }

    // Else we cannot go anywhere. It's impossible.
    return -1;
}

int main(){
    // Scan in input
    scanf("%d %d", &R, &C);
    for (int i=0; i<R; ++i){
        for (int j=0; j<C; ++j){
            char ph;
            scanf(" %c", &ph);
            grid[i*C+j] = ph - '0';
        }
    }

    // Set up the adjlist
    for (int i=0; i<R; ++i){
        for (int j=0; j<C; ++j){
            int oldspace = i*C + j;
            adjlist[oldspace][0]++;

            // Don't bother if we cannot go anywhere
            if (grid[oldspace] == 0){
                continue;
            }

            // For each of the 4 directions
            for (int k=0; k<4; ++k){
                int newrow = i + dr[k]*grid[oldspace];
                int newcol = j + dr[k+1]*grid[oldspace];

                // Check out of bounds
                if (newrow < 0 || newrow >= R || newcol < 0 || newcol >= C){
                    continue;
                }

                // Else push him into the adjmatrix
                int newspace = newrow*C + newcol;
                adjlist[oldspace][adjlist[oldspace][0]++] = newspace;
            }
        }
    }

    printf("%d\n", bfs(0));
    return 0;
}
