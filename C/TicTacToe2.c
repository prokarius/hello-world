#include<stdio.h>

int main(){
    int magic[8] = {12, 345, 678, 36, 147, 258, 48, 246};
    int board[9];
    int testcases;
    scanf("%d ", &testcases);
    while (testcases--){

        // Scan in input
        char ph;
        int x = 0, o = 0;
        for (int i=0; i<9; ++i){
            scanf("%c ", &ph);
            if (ph == '.'){
                board[i] = 0;
            }
            else if (ph == 'O'){
                board[i] = 1;
                o++;
            }
            else{ // ph == 'X'
                board[i] = 2;
                x++;
            }
        }

        // Now check for invalid stuff
        // 1) If there are more os than xs
        if (o > x){
            printf("no\n");
            continue;
        }

        // 2) If the number of xs - os is more than 1.
        if ((x-o) > 1){
            printf("no\n");
            continue;
        }

        // 3) If there are more than 2 winning rows.
        // This one just do a manual check.
        int xwincount = 0;
        int owincount = 0;
        for (int i=0; i<8; ++i){
            int a = magic[i] % 10;
            int b = (magic[i]/10) % 10;
            int c = magic[i] / 100;
            if (board[a] == board[b] && board[b] == board[c]){
                if (board[a] == 1){
                    owincount++;
                }
                else if (board[a] == 2){
                    xwincount++;
                }
            }
        }

        if (owincount * xwincount){
            printf("no\n");
            continue;
        }

        // 4a) Stupid corner case where o wins, but x still has an extra move
        if (owincount){
            if (x != o){
                printf("no\n");
                continue;
            }
        }

        // 4b) And the related case where x wins, but o still moves
        if (xwincount){
            if (x != o+1){
                printf("no\n");
                continue;
            }
        }

        printf ("yes\n");
    }
}
