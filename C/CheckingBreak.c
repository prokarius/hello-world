#include<stdio.h>

#define MIN(x, y) (x<y)?(x):(y)
#define MAX(x, y) (x>y)?(x):(y)
#define ABS(x) ((x > 0)?(x):(-x))

typedef struct {
    int x;
    int y;
    int z;
} Coord;

Coord coord(int x, int y, int z){
    Coord out = {x, y, z};
    return out;
}

int checkCorners(Coord top, Coord bot, Coord max){
    if (bot.x > top.x || top.x > max.x) return 0;
    if (bot.y > top.y || top.y > max.y) return 0;
    if (bot.z > top.z || top.z > max.z) return 0;
    return 1;
}

int inside(Coord top, Coord bot, Coord chip){
    if (chip.x > top.x || chip.x < bot.x) return 0;
    if (chip.y > top.y || chip.y < bot.y) return 0;
    if (chip.z > top.z || chip.z < bot.z) return 0;
    return 1;
}

int overlap(Coord top1, Coord bot1, Coord top2, Coord bot2){
    int minX = MIN(top1.x, top2.x);
    int maxX = MAX(bot1.x, bot2.x);
    int minY = MIN(top1.y, top2.y);
    int maxY = MAX(bot1.y, bot2.y);
    int minZ = MIN(top1.z, top2.z);
    int maxZ = MAX(bot1.z, bot2.z);

    if (maxX > minX || maxY > minY || maxZ > minZ) return 0;
    return 1;
}

long long getVolume(Coord top, Coord bot){
    int dx = top.x - bot.x;
    int dy = top.y - bot.y;
    int dz = top.z - bot.z;

    return 1LL * (dx+1) * (dy+1) * (dz+1);
}

Coord chips[1<<10];
Coord slices[1<<10][2];

int solve(int a){
    // Scan in input
    int b, c, m;
    scanf("%d %d %d", &b, &c, &m);

    Coord max = coord(a, b, c);

    for (int i = 0; i < m; ++i){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        chips[i] = coord(x, y, z);
    }

    for (int i = 0; i < m; ++i){
        int x1, y1, z1, x2, y2, z2;
        scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
        slices[i][0] = coord(x1, y1, z1);
        slices[i][1] = coord(x2, y2, z2);
    }

    int out = 1;
    long long volume = 0;

    // For each slice
    for (int i = 0; i < m; ++i){
        // Check the correct corners
        if (checkCorners(slices[i][1], slices[i][0], max) == 0){
            out = 0;
            break;
        }

        // Check if the cake contains the i'th chip:
        if (inside(slices[i][1], slices[i][0], chips[i]) == 0){
            out = 0;
            break;
        }

        // Make sure there are no overlaps
        for (int j = i+1; j < m; ++j){
            if (overlap(slices[i][1], slices[i][0], slices[j][1], slices[j][0])){
                out = 0;
                break;
            }
        }

        // What is the volume of the slice?
        volume += 1LL * getVolume(slices[i][1], slices[i][0]);
    }

    // Is the volume correct?
    if (volume != 1LL * a * b * c) out = 0;

    printf(out?"YES\n":"NO\n");
}

int main(){
    int a;
    scanf("%d", &a);
    while (a != -1){
        solve(a);
        scanf("%d", &a);
    }

    return 0;
}

