#include<stdio.h>
#include<string.h>

char grid[10][10];
char instructions[64];

int dr[5] = {1, 0, -1, 0, 1};

int main(){
    int turtleX, turtleY, dir;
    int goalX, goalY;
    int laserX, laserY;

    // Scan in input
    for (int j = 1; j <= 8; ++j){
        for (int i = 1; i <= 8; ++i){
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'T'){
                turtleX = i;
                turtleY = j;
                dir = 0;
                grid[i][j] = '.';
            }
            if (grid[i][j] == 'D'){
                goalX = i;
                goalY = j;
                grid[i][j] = '.';
            }
        }
    }

    scanf(" %s", instructions);

    // Process instructions
    for (int i = 0; i < strlen(instructions); ++i){
        switch (instructions[i]){
            // Move forward, only if it is permissible
            case('F'):
                turtleX += dr[dir];
                turtleY += dr[dir+1];

                if (grid[turtleX][turtleY] != '.'){
                    printf("Bug!\n");
                    return 0;
                }
                break;

            case ('R'):
                dir = (dir + 3) % 4;
                break;

            case ('L'):
                dir = (dir + 1) % 4;
                break;

            case ('X'):
                laserX = turtleX + dr[dir];
                laserY = turtleY + dr[dir+1];

                if (grid[laserX][laserY] != 'I'){
                    printf("Bug!\n");
                    return 0;
                }
                else {
                    grid[laserX][laserY] = '.';
                }
                break;
        }
    }

    // Did we reach the end?
    if (turtleX == goalX && turtleY == goalY) printf("Diamond!\n");
    else printf("Bug!\n");
    return 0;
}

