#include<stdio.h>


void solve(){
    char board[32][32][2];
    int numShips[2] = {0, 0};

    int playerTurn = 1; // Player 0 attacks player 1's board

    // Scan in input
    int w, h, q;
    scanf ("%d %d %d", &w, &h, &q);

    for (int player = 0; player < 2; player++){
        for (int i = h-1; i >= 0; --i){
            for (int j = 0; j < w; ++j){
                char ph;
                scanf(" %c", &ph);
                if (ph == '#') numShips[player]++;
                board[i][j][player] = ph;
            }
        }
    }

    int ded = 0;

    // For each input, if we have not died, process it
    for (int i = 0; i < q; ++i){
        int r, c;
        scanf("%d %d", &c, &r); // Tricky

        if (!ded){

            // If we had hit a ship, replace it with water, and reduce the number of
            // ships the other player has
            if (board[r][c][playerTurn] == '#'){
                board[r][c][playerTurn] = '_';
                --numShips[playerTurn];

                // If the player is ded, only give up if the player is player 2
                if (numShips[playerTurn] == 0){
                    if (!playerTurn){
                        ded = 1;
                    }
                    else {
                        playerTurn = 1 - playerTurn;
                    }
                }
            }

            // If we miss, flip the turns
            else {
                playerTurn = 1 - playerTurn;
            }
        }
    }

    // OK we have read all the inputs, we decide the outcome of the battle
    // If both parties still has ships left, it's a draw
    if (numShips[0] && numShips[1]){
        printf("draw\n");
    }

    // If no one has any ships left, it's a draw just in case (???)
    else if (numShips[0] == 0 && numShips[1] == 0){
        printf("draw\n");
    }

    // If not see who is still alive
    else if (numShips[0] == 0){
        printf("player two wins\n");
    }
    else { // numShips[1] == 0
        printf("player one wins\n");
    }
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    while (testcases--){
        solve();
    }
    return 0;
}
