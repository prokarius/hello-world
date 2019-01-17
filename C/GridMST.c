#include<stdio.h>

typedef struct{
    int dist;
    short x;
    short y;
} Edge;

// This cmpfunc is only for comparisons though
// Not for qsort.
int cmpfunc(Edge a, Edge b){
    return (a.dist > b.dist) - (b.dist > a.dist);
}

// Yes, I finally decided to make my own ghettoHeap.
// I think this completes the basic data structures list...
Edge ghettoHeap[50000000];
int ghettoHeapHead = 1;

// Damnit, why am I cause trouble to myself!
void swap(int a, int b){
    Edge temp = ghettoHeap[a];
    ghettoHeap[a] = ghettoHeap[b];
    ghettoHeap[b] = temp;
}

// Swaps the element at index index with the smaller of its two children
void sink(int index){
    if (index*2 >= ghettoHeapHead) return;
    int left = 2*index;
    int right = left + 1;

    // Well if the thing only has one child then we can only can potentially swap with...
    if (right == ghettoHeapHead){
        if (cmpfunc(ghettoHeap[left], ghettoHeap[index]) < 0){
            swap(left, index);
        }
    }
    else {
        int smaller = cmpfunc(ghettoHeap[left], ghettoHeap[right]) < 0 ? left : right;
        if (cmpfunc(ghettoHeap[smaller], ghettoHeap[index]) < 0){
            swap(smaller, index);
            sink(smaller);
        }
    }
}

void swim(int index){
    if (index <= 1) return;
    if (cmpfunc(ghettoHeap[index], ghettoHeap[index/2]) < 0){
        swap(index, index/2);
        swim(index/2);
    }
}

void push(Edge e){
    // Push to the bottom and swim upwards
    ghettoHeap[ghettoHeapHead] = e;
    swim(ghettoHeapHead);
    ghettoHeapHead++;
}

Edge pop(){
    // Replace the smallest with the 0th element, then sink
    Edge e = ghettoHeap[1];
    ghettoHeapHead--;
    ghettoHeap[1] = ghettoHeap[ghettoHeapHead];
    sink(1);
    return e;
}

// We will encode the coordinates as x << 10 + y
// Incidentally, the points can be repeated! What a scam!
int distance[1<<10][1<<10];
int visited[1<<10][1<<10];
short points[100005][2];

int dr[5] = {0, 1, 0, -1, 0};
int *dc = dr + 1;

void pri(Edge e){
    printf("%d %d %d\n", e.dist, e.x, e.y);
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    int numpoints = n;

    for (int i = 0; i < n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        points[i][0] = x;
        points[i][1] = y;
        if (visited[x][y]){
            numpoints--;
            continue;
        }
        visited[x][y] = 1;
    }
    numpoints--;

    // Reset the distance array:
    for (int i = 0; i <= 1000; ++i){
        for (int j = 0; j <= 1000; ++j){
            distance[i][j] = 1<<30;
        }
    }

    // Incidentally, we choose a random point as our starting point.
    // So how about point number 25th quartile + 1?
    // Push this point into the HeapQueue
    int luckyPoint = (n>>2);
    Edge luckyEdge;
    luckyEdge.dist = 0;
    luckyEdge.x = points[luckyPoint][0];
    luckyEdge.y = points[luckyPoint][1];
    push(luckyEdge);

    // Do Best First Search using Breadth First Search
    int out = 0;

    // Set the initial distance to be 0.
    distance[luckyEdge.x][luckyEdge.y] = 0;
    visited[luckyEdge.x][luckyEdge.y] = 0;

    // We will keep popping edges until we meet everything
    while (numpoints){
        Edge curr = pop();
        short x = curr.x;
        short y = curr.y;
        int dist = curr.dist;
        if (dist > distance[x][y]) continue;

        // If we see a point, this is the first time we are meeting it.
        // We will add the distance to it into our final result
        // Note that the current distance to this point is then reset.
        if (visited[x][y]){
            visited[x][y] = 0;
            out += distance[x][y];
            distance[x][y] = 0;
            dist = 0;
            numpoints--;
        }

        // Visit all neighbours
        for (int i = 0; i < 4; ++i){
            short newx = x + dr[i];
            short newy = y + dc[i];
            if (newx < 0 || newy < 0 || newx >= 1000 || newy >= 1000) continue;
            if (distance[newx][newy] <= dist + 1) continue;
            distance[newx][newy] = dist + 1;
            Edge newEdge = {dist+1, newx, newy};
            push(newEdge);
        }
    }

    // Print that shit
    printf("%d\n", out);

    return 0;
}
