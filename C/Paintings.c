#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n;
char* colors[16];
int bad[16][16];

int out = 0;
int visited[16];
int sequence[16];
int first[16];

void dp(int curr, int prev){
    // Have we reached the end?
    if (curr == n){
        // Is this our first time reaching the end?
        if (out == 0){
            for (int i = 0; i < n; ++i){
                first[i] = sequence[i];
            }
        }
        out += 1;
    }

    // Recurse
    for (int i = 0; i < n; ++i){
        // If we have been here before, give up
        if (visited[i]) continue;

        // If the two colours don't go well together, give up
        if (bad[prev][i]) continue;

        visited[i] = 1;
        sequence[curr] = i;
        dp(curr + 1, i);
        visited[i] = 0;
    }
}

int getColor(char* color){
    for (int i = 0; i < n; ++i){
        if (strcmp(color, colors[i]) == 0){
            return i;
        }
    }
}

void solve(){
    // Scan in input
    scanf("%d ", &n);

    // Scan in the colors
    for (int i = 0; i < n; ++i){
        char* color = (char*) malloc(sizeof(char) * 24);
        scanf("%s ", color);
        colors[i] = color;
    }

    // Reset the bad array
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            bad[i][j] = 0;
        }
    }

    // Now get all the bad colors
    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i){
        char* color1 = malloc(sizeof(char) * 24);
        char* color2 = malloc(sizeof(char) * 24);
        scanf(" %s %s", color1, color2);

        int start = getColor(color1);
        int end = getColor(color2);

        bad[start][end] = 1;
        bad[end][start] = 1;
    }

    // Do complete search
    out = 0;    
    dp(0, 15);

    // Print the number, and the colours
    printf("%d\n", out);
    for (int i = 0; i < n; ++i){
        printf("%s ", colors[first[i]]);
    }
    printf("\n");
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}

