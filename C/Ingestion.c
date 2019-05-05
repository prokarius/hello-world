#include<stdio.h>

#define MIN(x,y) ((x < y) ? (x) : (y))
#define MAX(x,y) ((x > y) ? (x) : (y))

int calories[105];
int maxIngestion[105];
int dpTable[105][105][2];
int n, maxCalories;

// DP state if given by the current food we eat, the current food penalty,
// and whether we ate or rested in the previous period.
int memo(int curr, int penalty, int noEat){
    // Have we reached the end of the list
    if (curr >= n) return 0;

    // Have we been here before?
    if (dpTable[curr][penalty][noEat] != -1) return dpTable[curr][penalty][noEat];

    // How much have we eaten, suppose we eat now
    int currentEat = MIN(calories[curr], maxIngestion[penalty]);
    currentEat += memo(curr + 1, penalty + 1, 0);

    // Calculate the new penalty suppose we stop eating now.
    int newPenalty;
    if (noEat) newPenalty = 0;
    else newPenalty = MAX(penalty - 1, 0);

    // Then find the best of the two
    int supposeStop = memo(curr + 1, newPenalty, 1);
    int best = MAX(currentEat, supposeStop);

    // Save the dp state and return
    dpTable[curr][penalty][noEat] = best;
    return best;
}

int main(){
    // Scan in input
    scanf("%d %d", &n, &maxCalories);
    for (int i = 0; i < n; ++i){
        scanf("%d", &calories[i]);
    }

    // Precompute the max number of calories after eating n times
    int currMaxCalories = maxCalories;
    for (int i = 0; i < n; ++i){
        maxIngestion[i] = currMaxCalories;
        currMaxCalories = currMaxCalories * 2 / 3;
    }

    // Initialise DP table
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            dpTable[i][j][0] = -1;
            dpTable[i][j][1] = -1;
        }
    }

    // Do the dp.
    printf("%d\n", memo(0, 0, 1));
    return 0;
}

