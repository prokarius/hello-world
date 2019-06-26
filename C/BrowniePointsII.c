#include<stdio.h>
#include<stdlib.h>

#define MIN(x, y) (x < y)?(x):(y)
#define MAX(x, y) (x > y)?(x):(y)

// Initialise Fenwick Tree methods
int fenwickBefore[1<<18];
int fenwickAfter[1<<18];

int LSOne(int x){
    return x&(-x);
}

void update(int* fenwickTree, int location, int value){
    for (int i = location; i < 1<<18; i+=LSOne(i)){
        fenwickTree[i] += value;
    }
}

int rsq(int* fenwickTree, int end){
    int sum = 0;
    for (int i = end; i > 0; i -= LSOne(i)){
        sum += fenwickTree[i];
    }
    return sum;
}

int rsq2(int* fenwickTree, int start, int end){
    return rsq(fenwickTree, end) - rsq(fenwickTree, start-1);
}

// Encapsulate a point
typedef struct {
    int x;
    int y;
} Point;

// Constructor
Point point(int x, int y){
    Point output;
    output.x = x;
    output.y = y;
    return output;
}

Point points[1<<18];

int cmpfuncx(const void* a, const void* b){
    Point first = *(Point*) a;
    Point second = *(Point*) b;

    return first.x - second.x;
}

int cmpfuncy(const void* a, const void* b){
    Point first = *(Point*) a;
    Point second = *(Point*) b;

    return first.y - second.y;
}

int cmpfunc(const void* a, const void* b){
    int first = *(int*) a;
    int second = *(int*) b;

    return first - second;
}

// List of scores Ollie can get
int scores[1<<18];
int numScores = 0;

int main(){
    // Scan in points
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        points[i] = point(x, y);
    }

    // Now we want to sort the points by y value then by x value.
    // Because we do not care about the ordering of the points, only ordering
    qsort(points, n, sizeof(Point), cmpfuncy);

    // Assign the ordering to the points, replace the y value as we go along
    int currY = -1000000007;
    int currIndex = 0;
    
    for (int i = 0; i < n; ++i){
        if (points[i].y > currY){
            ++currIndex;
            currY = points[i].y;
        }
        points[i].y = currIndex;
    }

    // Save the maxY value so we can use it in our RSQ later.
    int maxY = currIndex;

    // Do the same for x coordinates
    qsort(points, n, sizeof(Point), cmpfuncx);

    // Assign the ordering to the points, replace the x value as we go along
    int currX = -1000000007;
    currIndex = -1;
    
    for (int i = 0; i < n; ++i){
        if (points[i].x > currX){
            ++currIndex;
            currX = points[i].x;
        }
        points[i].x = currIndex;
    }

    // Cool, now our points are sorted by X, we push all the points into the
    // fenwick tree that represents the points after the X coord we consider.
    for (int i = 0; i < n; ++i){
        update(fenwickAfter, points[i].y, 1);
    }

    // We are trying to find the largest lowest possible score Stan can get.
    // Note the currIndex is the same as the number of distinct X coords.
    int bestLowest = -1;
    int index = 0;

    int yValuesToConsider[1<<18];
    int numYValues;

    // For each possible x value
    for (int currX = 0; currX <= currIndex; ++currX){
        int currLowest = 999999;
        int ollieBest = -1;
        numYValues = 0;

        // Find all the possible scores of Ollie and Stan.
        // First find all the points
        while (points[index].x == currX && index < n){
            yValuesToConsider[numYValues] = points[index].y;
            ++numYValues;
            ++index;
        }

        // OK remove each of these points from the fenwick tree
        for (int i = 0; i < numYValues; ++i){
            update(fenwickAfter, yValuesToConsider[i], -1);
        }

        // Find all possible scores Stan & Ollie can get
        for (int i = 0; i < numYValues; ++i){
            int currY = yValuesToConsider[i];
            int stanScore = rsq(fenwickBefore, currY-1) + rsq2(fenwickAfter, currY+1, maxY);
            currLowest = MIN(stanScore, currLowest);

            int ollieScore = rsq2(fenwickBefore, currY+1, maxY) + rsq(fenwickAfter, currY-1);
            ollieBest = MAX(ollieBest, ollieScore);
        }

        // Lastly, push back all the yValues into the before fenwick tree
        for (int i = 0; i < numYValues; ++i){
            update(fenwickBefore, yValuesToConsider[i], 1);
        }

        // Is the current lowest score better than the best lowest score?
        if (currLowest > bestLowest){
            scores[0] = ollieBest;
            numScores = 1;
            bestLowest = currLowest;
        }

        // Is the current lowest score the same as the best lowest score?
        else if (currLowest == bestLowest){
            scores[numScores] = ollieBest;
            ++numScores;
        }
    }

    // Sort the list of scores Ollie can get
    qsort(scores, numScores, sizeof(int), cmpfunc);

    // Print that shit
    printf("Stan: %d; Ollie:", bestLowest);
    
    // Note that we cannot have repeats in Ollie's scores
    int prevBest = scores[0];
    for (int i = 1; i < numScores; ++i){
        if (prevBest < scores[i]){
            printf(" %d", prevBest);
            prevBest = scores[i];
        }
    }
    printf(" %d", prevBest);
    printf(";\n");

    return 0;
}
