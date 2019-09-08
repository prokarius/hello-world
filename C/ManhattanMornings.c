#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

int cmpfunc(const void* a, const void* b){
    Coordinate first = *(Coordinate*) a;
    Coordinate second = *(Coordinate*) b;

    if (first.x == second.x){
        return first.y - second.y;
    }

    return first.x - second.x;
}

Coordinate coordinates[100005];
int coordinatesHead = 0;

int startx, starty, endx, endy;
int LIS[100005];
int length = 0;

void push(int x, int y){
    if (startx <= x && x <= endx){
        if (starty <= y && y <= endy){
            Coordinate new;
            new.x = x;
            new.y = y;
            coordinates[coordinatesHead] = new;
            coordinatesHead++;
        }
    }
}

// Given a number, finds the index number of the next higher number in the LIS array
int binarySearch(int value){
    int lo = 0;
    int hi = coordinatesHead;

    while (lo <= hi){
        int mid = (hi + lo)/2;

        if (LIS[mid] <= value){
            lo = mid+1;
        }
        else{
            hi = mid-1;
        }
    }
    return lo;
}

int main(){
    // Scan in input
    int n;
    scanf ("%d", &n);
    
    scanf ("%d %d %d %d", &startx, &starty, &endx, &endy);

    // Mirror the test cases so that startx < endx and starty < endy
    int multiplierx, multipliery;
    if (startx > endx){
        multiplierx = -1;
        startx *= -1;
        endx *= -1;
    }
    else {
        multiplierx = 1;
    }

    if (starty > endy){
        multipliery = -1;
        starty *= -1;
        endy *= -1;
    }
    else {
        multipliery = 1;
    }

    for (int i = 0; i < n; ++i){
        int x, y;
        scanf ("%d %d", &x, &y);
        push(x*multiplierx, y*multipliery);
    }

    // Sort the coordinates
    qsort(coordinates, coordinatesHead, sizeof(Coordinate), cmpfunc);

    // Do LIS
    // Start by filling all the array with INTMAX
    for (int i = 0; i < coordinatesHead; ++i){
        LIS[i] = 1<<30;
    }

    for (int i = 0; i < coordinatesHead; ++i){
        int y = coordinates[i].y;
        int index = binarySearch(y);
        LIS[index] = y;
        if (index == length){
            length++;
        }
    }

    printf("%d\n", length);

    return 0;
}
