#include<stdio.h>

int bfs[1<<22];
int bfsHead = 0;
int bfsTail = 0;

void push(x) { bfs[bfsHead++] = x; }
int pop() { return bfs[bfsTail++]; }
int notEmpty() { return bfsHead != bfsTail; }

int visited[1<<20];

int a[16];
int b[16];

int main(){
    // Scan in input
    int m, n, s;
    scanf("%d %d %d", &m, &n, &s);

    for (int i = 0; i < n; ++i){
        scanf("%d %d", &a[i], &b[i]);
        a[i] %= m;
        b[i] %= m;
    }

    // Now do BFS
    visited[s] = 1;
    push(s);

    while (notEmpty()){
        long long curr = pop();

        // Have we found 0?
        if (curr == 0){
            printf("%d\n", visited[0]-1);
            return 0;
        }

        // Simulate all moves
        for (int i = 0; i < n; ++i){
            long long new = curr * a[i] + b[i];
            int next = new % m;

            if (visited[next]) continue;
            visited[next] = visited[curr] + 1;
            push(next);
        }
    }

    // We did not find 0 :(
    printf("-1\n");
    return 0;
}

