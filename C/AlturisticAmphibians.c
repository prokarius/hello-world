#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) (x > y)?(x):(y)

// Fake OOP kek
typedef struct {
    int leap;
    int weight;
    int height;
} Frog;

Frog frog(int leap, int weight, int height){
    Frog output;
    output.leap = leap;
    output.weight = weight;
    output.height = height;
    return output;
}

// For sorting the frog by weight
int cmpfunc(const void* a, const void* b){
    Frog first = *(Frog*) a;
    Frog second = *(Frog*) b;
    return -(first.weight - second.weight);
}

Frog frogs[100005];
int maxHeight[100000005];

int main(){
    // Scan in input
    int n, d;
    scanf("%d %d", &n, &d);

    for (int i = 0; i < n; ++i){
        int l, w, h;
        scanf("%d %d %d", &l, &w, &h);
        frogs[i] = frog(l, w, h);
    }

    // Sort the frog by weight because the lightest one will hop out first.
    qsort(frogs, n, sizeof(Frog), cmpfunc);
    int ans = 0;

    // For each frog from the heaviest, find the highest frog tower that can support
    // that weight. Store that in the maxHeight variable
    // Do this using DP.
    for (int i = 0; i < n; ++i){
        Frog curr = frogs[i];
        int currWeight = curr.weight;

        // Cam the current frog escape?
        if (curr.leap + maxHeight[curr.weight] > d) ++ans;

        // Update the height of the tallest frog tower.
        // If the tower can accomodate at least k < w in weight, then as long as we put
        // the frog at the bottom, he would be able to bear everyone on top!
        for (int j = 0; j < currWeight; ++j){
            if (j + currWeight >= 100000005) break; // Possible to go out of bounds
            int newHeight = curr.height + maxHeight[j + currWeight];
            maxHeight[j] = MAX(maxHeight[j], newHeight);
        }
    }

    // Print that shit!
    printf("%d\n", ans);
    return 0;
}

