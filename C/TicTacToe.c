#include<stdio.h>

int board[1000][1000];

// Doubles as my out of bounds checker
int getChar(int r, int c, int n){
    if (r<0 || c<0 || r>=n || c>=n) return 0;
    else return board[r][c];
}

// Counts the number of winning squares a player could have made
// OK I know Im copy and pasting code. I should have thought this out more properly.
// Not a solution Im very proud of tbh.
int wincount(int player, int n ,int m){
    // initialise winplaces, which are the places the winning move could be
    int winplaces[1000][1000];
    int winnumber = 0;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            winplaces[i][j] = 0;
        }
    }

    // Check vertically
    for (int r = 0; r < n; ++r){
        int streaklength = 0;

        // We will check if there is a streak
        for (int c = 0; c < n+1; ++c){
            if (getChar(r, c, n) == player){
                streaklength++;
            }

            // If the streak has ended, we see which places could have been the
            // winning moves.
            // The number of such places is m - (lengthofstreak - m) long.
            // It starts from currlocation - m.
            else {
                // Of course, check if streaklength is longer than 2m
                // If so, it's an error, return a negative number.
                if (streaklength >= 2*m){
                    return -1;
                }
                if (streaklength >= m){
                    for (int k = 0; k < 2*m - streaklength; ++k){
                        winplaces[r][c+k-m]++;
                    }
                    winnumber++;
                }
                streaklength = 0;
            }
        }
    }

    // Horizontally
    for (int c = 0; c < n; ++c){
        int streaklength = 0;
        for (int r = 0; r < n+1; ++r){
            if (getChar(r, c, n) == player){
                streaklength++;
            }
            else {
                if (streaklength >= 2*m){
                    return -1;
                }
                if (streaklength >= m){
                    for (int k = 0; k < 2*m - streaklength; ++k){
                        winplaces[r+k-m][c]++;
                    }
                    winnumber++;
                }
                streaklength = 0;
            }
        }
    }

    // And diagonally. (dr = [-1, 1]
    for (int r = 0; r < 2 * n; ++r){
        int streaklength = 0;
        for (int c = 0; c < n+1; ++c){
            if (getChar(r - c, c, n) == player){
                streaklength++;
            }
            else {
                if (streaklength >= 2*m){
                    return -1;
                }
                if (streaklength >= m){
                    for (int k = 0; k < 2*m - streaklength; ++k){
                        winplaces[r-(c+k-m)][c+k-m]++;
                    }
                    winnumber++;
                }
                streaklength = 0;
            }
        }
    }

    // And diagonally again. (dr = [1,1])
    for (int r = -n; r < n; ++r){
        int streaklength = 0;
        for (int c = 0; c < n+1; ++c){
            if (getChar(r + c, c, n) == player){
                streaklength++;
            }
            else {
                if (streaklength >= 2*m){
                    return -1;
                }
                if (streaklength >= m){
                    for (int k = 0; k < 2*m - streaklength; ++k){
                        winplaces[r+c+k-m][c+k-m]++;
                    }
                    winnumber++;
                }
                streaklength = 0;
            }
        }
    }

    // Now, if no one won, then we just return 0.
    if (winnumber == 0) return 0;

    // Last bit is to see if we had a tile with as many pushes as winnumber
    int wins = 0;
    for (int r = 0; r < n; ++r){
        for (int c = 0; c < n; ++c){
            if (winplaces[r][c] == winnumber){
                wins++;
            }
        }
    }

    if (wins) return wins;
    return -1;
}

int main(){
    int n;
    int m;
    scanf("%d %d ", &n, &m);

    // Scan in input
    char ph;
    int x = 0, o = 0;
    for (int i = 0; i < n; ++i){
        scanf(" ");
        for (int j = 0; j < n; ++j){
            scanf("%c", &ph);
            if (ph == '.'){
                board[i][j] = 0;
            }
            else if (ph == 'O'){
                board[i][j] = -1;
                o++;
            }
            else{ // ph == 'X'
                board[i][j] = 1;
                x++;
            }
        }
    }

    // Now check for invalid stuff
    // 1) If there are more os than xs
    if (o > x){
        printf("ERROR\n");
        return 0;
    }

    // 2) If the number of xs - os is more than 1.
    if ((x-o) > 1){
        printf("ERROR\n");
        return 0;
    }

    // 3) If there are more than 2 winning rows.
    // This one just do a manual check.
    int xwincount = wincount(1, n, m);

    // If some invalid state happened while parsing the game board:
    if (xwincount < 0){
        printf("ERROR\n");
        return 0;
    }

    // Same for O
    int owincount = wincount(-1, n, m);
    if (owincount < 0){
        printf("ERROR\n");
        return 0;
    }

    // 4) If they both win:
    if (owincount * xwincount){
        printf("ERROR\n");
        return 0;
    }

    // 5) Did someone win?
    // 5a) Stupid corner case where o wins, but x still has an extra move
    if (owincount){
        if (x != o){
            printf("ERROR\n");
            return 0;
        }
        else {
            printf("O WINS\n");
            return 0;
        }
    }

    // 5b) And the related case where x wins, but o still moves
    if (xwincount){
        if (x != o+1){
            printf("ERROR\n");
            return 0;
        }
        else {
            printf("X WINS\n");
            return 0;
        }
    }

    // 6) Has the game ended in a draw?
    if ((x + o) == n*n){
        printf("DRAW\n");
        return 0;
    }

    // Else, the game is still ongoing
    printf ("IN PROGRESS\n");
    return 0;
}
