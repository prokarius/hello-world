#include<stdio.h>
#include<string.h>

int position[2<<24];
int LPS[2<<24]; // For KMP

int dp[256][256][256];
char grid[256][256];
char string[256];

int main(){
    int n;
    // Scan in input
    scanf("%d", &n);
    scanf(" %s", string);
    
    int x;
    int y;
    int moveIndex = 0;

    // grid[y][x]. x goes >>, y goes vv
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){ 
            scanf(" %c", &(grid[i][j]));
            if (grid[i][j] == 'R'){
                x = j;
                y = i;
            }
        }
    }

    // Simulate the robot's moveset.
    int len = strlen(string);

    int numPos = 1;

    while(1){
        // Have we been at this tile during this current move before?
        if (dp[x][y][moveIndex]) break;

        // If not fill in this move
        dp[x][y][moveIndex] = numPos;

        // Simulate the next move
        int newY, newX;
        switch(string[moveIndex++]){
            case '^':
                newY = y - 1;
                newX = x;
                break;
            case 'v':
                newY = y + 1;
                newX = x;
                break;
            case '>':
                newY = y;
                newX = x + 1;
                break;
            case '<':
                newY = y;
                newX = x - 1;
                break;
        }

        // Did we hit a wall?
        if (grid[newY][newX] != '#'){
            x = newX;
            y = newY;
            position[numPos++] = (x << 8) + y;
        }

        // Don't forget wraparound
        moveIndex %= len;
    }

    // The path length is given by
    int pathLen = numPos - dp[x][y][moveIndex];

    // Short circuit: If the pathlength is 0, then it's 1:
    if (pathLen == 0){
        printf("1\n");
        return 0;
    }

    // Populate this last position
    //position[numPos++] = (x << 8) + y;

    // OK we have reached a place we were at before
    // Last step: Do KMP style preprocessing
    // Make the LIS array the same way we do before
    int zero = dp[x][y][moveIndex]; // This is our current position
    LPS[zero] = zero;
    int i = zero+1;
    int prefixLen = zero;

    // Technically we can use a while loop I guess...
    while (i < numPos){
        // If the current letter is the same as in the prefix, add one and move on.
        if (position[i] == position[prefixLen]){
            prefixLen++;
            LPS[i] = prefixLen;
            ++i;
        }

        // If the current letter doesn't match, 2 cases:
        else {
            // Case 1: We still haven't reached the start of the word yet
            // In this case, find the next shortest prefix that we have seen before
            if (prefixLen != zero){ 
                prefixLen = LPS[prefixLen - 1];
            }

            // Case 2: We reached the start of the word:
            // Then there is no shorter prefix. Sorry.
            else {
                LPS[i] = zero;
                i++;
            }
        }
    }


    // Final check: The shortest substring we found is some multiple of the pathlength
    int ans = numPos - LPS[numPos - 1];

    if (pathLen % ans == 0){
        printf("%d\n", ans);
    }
    else {
        printf("%d\n", pathLen);
    }

    return 0;
}

