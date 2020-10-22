#include<stdio.h>
#include<stdlib.h>

#define MIN(x, y) (x<y)?(x):(y)

int adjList[24][24];
int numEdges[24];

int check(int bitmask, int n){
    int curr = 0;

    int* arr = (int*) calloc(sizeof(int), n);

    while (bitmask){
        if (bitmask & 1){
            arr[curr]++;
            for (int i = 0; i < numEdges[curr]; ++i){
                arr[adjList[curr][i]]++;
            }
        }

        bitmask >>= 1;
        curr++;
    }

    // See if everyone is hit
    for (int i = 0; i < n; ++i){
        if (arr[i] == 0) return 0;
    }

    return 1;
}

void solve(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int d;
        scanf("%d", &d);
        numEdges[i] = d;

        for (int j = 0; j < d; ++j){
            int k;
            scanf("%d", &k);
            adjList[i][j] = k-1; // 1 indexing is disgusting
        }
    }

    // Just brute force this shit!
    int best = 1<<30;
    for (int i = 0; i < (1<<n); ++i){
        if (check(i, n)){
            best = MIN(__builtin_popcount(i), best);
        }
    }

    // Print
    printf("%d\n", best);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}
