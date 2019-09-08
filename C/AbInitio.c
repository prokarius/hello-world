#include<stdio.h>

int adjmat[4096][4096];

int main(){
    // Scan in input
    int v, e, q;
    scanf("%d %d %d", &v, &e, &q);

    // Also initialise our two flags
    int complement = 0;
    int transpose = 0;

    // Scan in the edges
    for (int i = 0; i < e; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        adjmat[start][end] = 1;
    }

    // Scan in the queries
    for (int i = 0; i < q; ++i){
        int type;
        int start, end;
        scanf("%d", &type);

        switch(type){
            case 1:;
                for (int i = 0; i <= v; ++i){
                    adjmat[i][v] = complement;
                    adjmat[v][i] = complement;
                }
                v++;
                break;
            case 2:;
                scanf("%d %d", &start, &end);
                if (transpose){
                    adjmat[end][start] ^= 1;
                }
                else{
                    adjmat[start][end] ^= 1;
                }
                break;
            case 4:;
                scanf("%d %d", &start, &end);
                if (transpose){
                    adjmat[end][start] ^= 1;
                }
                else{
                    adjmat[start][end] ^= 1;
                }
                break;
            case 3:;
                int node;
                scanf("%d", &node);
                for (int i = 0; i < v; ++i){
                    adjmat[node][i] = complement;
                    adjmat[i][node] = complement;
                }
                break;
            case 5:
                transpose ^= 1;
                break;
            case 6:
                complement ^= 1;
                break;
        }
    }

    printf("%d\n", v);

    // OK we now have a graph that has been modified, so decode the graph as we
    // process the edges
    for (int i = 0; i < v; ++i){
        int numout = 0;
        long long hash = 0;
        for (int j = v-1; j >= 0; --j){
            if (i == j) continue;
            if (transpose){
                if (adjmat[j][i] != complement){
                    numout++;
                    hash = (hash * 7 + j) % 1000000007;
                }
            }
            else {
                if (adjmat[i][j] != complement){
                    numout++;
                    hash = (hash * 7 + j) % 1000000007;
                }
            }
        }

        printf("%d %lld\n", numout, hash);
    }

    return 0;
}

