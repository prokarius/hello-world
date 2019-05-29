#include<stdio.h>

double enemies[105][3];

// Returns squared distance
double distance(double x1, double y1, double x2, double y2){
    double dx = x1 - x2;
    double dy = y1 - y2;

    return dx*dx + dy*dy;
}

int main(){
    double cx, cy;
    int n;

    scanf("%lf %lf %d", &cx, &cy, &n);

    // Scan in input
    for (int i = 0; i < n; ++i){
        scanf("%lf %lf %lf", &enemies[i][0], &enemies[i][1], &enemies[i][2]);
    }

    // Brute force the solution lol
    int out = 0;
    for (int i = 0; i < 2500; ++i){

        // Count keeps track of the number of enemies that I touch
        int count = 0;
        for (int j = 0; j < n; ++j){
            if (distance(cx, cy, enemies[j][0], enemies[j][1]) < (i + enemies[j][2])*(i + enemies[j][2])){
                count++;
            }
        }

        // If we touch too many enemies, then we break
        if (count > 2) break;

        // If not, update out
        out = i;
    }

    printf("%d\n", out);
    return 0;
}
