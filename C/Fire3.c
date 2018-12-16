#include<stdio.h>

char grid[1005][1005];
int visitedyou[1005][1005];
int visitedfire[1005][1005];
int flag = 1;

typedef struct {
	int x;
	int y;
} Pair;

// Ghetto Queues
Pair youQueue[1000005];
Pair fireQueue[1000005];
int fireQueueHead = 0;

int dr[5] = {0, 1, 0, -1, 0};
int R, C;

// Make pair method for pushing into the queue
Pair makePair(int x, int y){
	Pair new;
	new.x = x;
	new.y = y;
	return new;
}

// Do BFS on a given queue and grid
void BFS(Pair* queue, int queueHead, int queueTail, int playergrid[1005][1005]){
	while (queueHead - queueTail > 0){
		Pair curr = queue[queueTail++];
		for (int k = 0; k < 4; ++k){
			int newx = curr.x + dr[k];
			int newy = curr.y + dr[k+1];
			if (newx < 1 || newy < 1 || newx > R || newy > C) continue;
			if (grid[newx][newy] == '#') continue;
			if (playergrid[newx][newy] < (1<<20)) continue;
			playergrid[newx][newy] = playergrid[curr.x][curr.y] + 1;
			queue[queueHead++] = makePair(newx, newy);
		}
	}
}

int main(){
	// Scan in dimensions
	scanf("%d %d ", &R, &C);

	// Initialise the visited arrays to infinity
	for (int i = 0; i <= R+1 ; ++i){
		for (int j = 0; j <= C+1; ++j){
			visitedyou[i][j] = 1<<23;
			visitedfire[i][j] = 1<<22;
		}
	}

	// Scan in grid
	for (int i = 1; i <= R; ++i){
		for (int j = 1; j <= C; ++j){
			char ph;
			scanf(" %c", &ph);
			if (ph == 'F'){
				fireQueue[fireQueueHead++] = makePair(i, j);
				visitedfire[i][j] = 0;
			}
			else if (ph == 'J'){
				youQueue[0] = makePair(i, j);
				visitedyou[i][j] = 0;
			}
			grid[i][j] = ph;
		}
	}

	// Do BFS.
	BFS(fireQueue, fireQueueHead, 0, visitedfire);
	BFS(youQueue, 1, 0, visitedyou);

	// Check the boundaries. See if we managed to escape in time.
	// Notice if we are on the edge and the fire has not gotten to us
	// we just need one more step to win and escape alive!
	int best = 1<<24;
	for (int i = 1; i <= R; ++i){
		if (visitedfire[i][1] > visitedyou[i][1] && visitedyou[i][1] < best){
			best = visitedyou[i][1];
		}
		if (visitedfire[i][C] > visitedyou[i][C] && visitedyou[i][C] < best){
			best = visitedyou[i][C];
		}
	}
	for (int i = 1; i <= C; ++i){
		if (visitedfire[1][i] > visitedyou[1][i] && visitedyou[1][i] < best){
			best = visitedyou[1][i];
		}
		if (visitedfire[R][i] > visitedyou[R][i] && visitedyou[R][i] < best){
			best = visitedyou[R][i];
		}
	}

	// Do the printing
	if (best > 1<<20) printf("IMPOSSIBLE\n");
	else printf("%d\n", best+1);
	return 0;
}