#include<stdio.h>

#define MAX 200000005

// Set up the visited array
int visited[MAX];
int sequence[10005];
int visitedHead = 1;

int main(){
    // Scan in input
    long long r, m;
    scanf("%lld %lld", &r, &m);

    // Start from 1, and walk upwards
    sequence[1] = r;
    visited[r] = 1;
    long long curr = r;
    int n = 1;
    while (!visited[m]){
        while (visited[visitedHead]) visitedHead++;

        // This is the smallest difference:
        n++;
        curr += visitedHead;
        sequence[n] = curr;

        // Might overflow
        if (curr < MAX) visited[curr] = 1;

        // Loop and find all difference, mark them as visited
        for (int i = 1; i < n; ++i){
            if (curr - sequence[i] > MAX) continue;
            visited[curr - sequence[i]] = 1;
        }
    }

    printf("%d\n", n);

    return 0;
}
