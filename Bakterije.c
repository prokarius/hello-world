#include<stdio.h>

int main(){
    char ph;
    int  i, j, k, array[51][51][5], pos[3][5], trap, r, c, b;
    // Scan in the data
    scanf("%d %d %d", &r, &c, &b);
    scanf("%d %d", &pos[0][0], &pos[1][0]);
    trap = pos[0][0]*c + pos[1][0];
    for (i=0; i<b; ++i){
        scanf("%d %d", &pos[0][i], &pos[1][i]);
        --pos[0][i];
        --pos[1][i];
        scanf(" %c", &ph);
        if (ph == 'R') pos[2][i] = 1;
        else if (ph == 'D') pos[2][i] = 2;
        else if (ph == 'L') pos[2][i] = 3;
        else if (ph == 'U') pos[2][i] = 0;
        for (j=0; j<r; ++j){
            for (k=0; k<c; ++k){
                scanf(" %c", &ph);
                array[j][k][i] = ph - '0';
            }
        }
    }

    // For each bacterium, simulate its movement
    int state[10005][5]={0}, cycle[10005][5]={0}, eqn[2][5]={-1}, t;
    for (i=0; i<b; ++i){
        t=0;
        while (1){
            pos[2][i] = (pos[2][i] + array[pos[0][i]][pos[1][i]][i]) % 4;
            if (pos[2][i] == 0){
                if (pos[0][i] == 0) {
                    ++pos[0][i];
                    pos[2][i] = 2;
                }
                else --pos[0][i];
            }
            else if (pos[2][i] == 1){
                if (pos[1][i] == c-1){
                    --pos[1][i];
                    pos[2][i] = 3;
                }
                else ++pos[1][i];
            }
            else if (pos[2][i] == 2){
                if (pos[0][i] == r-1){
                    --pos[0][i];
                    pos[2][i] = 0;
                }
                else ++pos[0][i];
            }
            else {
                if (pos[1][i] == 0){
                    ++pos[1][i];
                    pos[2][i] = 1;
                }
                else --pos[1][i];
            }

            // Check if it hit the trap
            int curpos = 4*(pos[0][i]*c + pos[1][i]) + pos[2][i];
            if (curpos/4 == trap) eqn[0][i] = t;

            // Check if it is in a cycle
            printf ("%d %d %d \n", pos[0][i], pos[1][i], pos[2][i]);
            if (state[curpos][i] == 0){
                state[curpos][i] = 1;
                cycle[curpos][i] = t;
            }
            else {
                eqn[1][i] = t-cycle[curpos][i];
                break;
            }
            ++t;
        }
    }

    // If the bacteria cycles without touching the trap, return -1
    for (i=0; i<b; ++i){
        if (eqn[0][i] == -1){
            printf("-1");
            return 0;
        }
    }

    // Else, solve the system of linear equations
    // TODO

    printf("%d %d", eqn[0][0], eqn[1][0]);

    return 0;
}
