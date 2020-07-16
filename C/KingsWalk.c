#include<stdio.h>

#define ABS(x) ((x) < 0)?(-(x)):(x)

void king(int left, int right, int dist, int n){
    int ways[n], newWays[n];

    // Initialise it to be all 0s except for the start
    for (int i = 0; i < n; ++i) ways[i] = 0;
    ways[left] = 1;

    // Do a trinomial walk
    for (int i = 0; i < dist; ++i){
        for (int j = 0; j < n; ++j){
            newWays[j] = ways[j];
            
            // Add the diagonal directions if we are not out of bounds
            if (j > 0) newWays[j] += ways[j-1];
            if (j+1 < n) newWays[j] += ways[j+1];
        }

        // Copy the newWays array into the old ways array
        for (int j = 0; j < n; ++j){
            ways[j] = newWays[j] % 5318008; // boobies
        }
    }

    printf("%d\n", ways[right]);
}

void run(){
    // Scan in input
    int n;
    scanf("%d", &n);

    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    int dx = ABS(x1 - x2);
    int dy = ABS(y1 - y2);

    if (dx > dy) king(y1-1, y2-1, dx, n);
    else king(x1-1, x2-1, dy, n);
}

int main(){
    int numTestcases;
    scanf("%d", &numTestcases);
    while (numTestcases--) run();
    return 0;
}

