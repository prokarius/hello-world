#include<stdio.h>
#include<stdlib.h>

#define MIN(x,y) ((x < y)?(x):(y))

typedef struct {
    int x, t;
} Event;

// Make a list of events
Event eventList[100005];
int n, m;

// So that we can sort our eventlist
int cmpfunc (const void * a, const void * b) {
    Event first = *(Event*)a;
    Event second = *(Event*)b;
    if (first.x == second.x){
        return first.t - second.t;
    }
    return first.x - second.x;
}

// Returns 1 if the guessed t value (curr) is too low. Else, return 0.
int check(int curr){
    // Initialise the start values: We are using 1 bomb
    // Left and Right most points are the possible bounds of the current bomb
    int numBombs = 1;
    int leftMostPoint = curr - eventList[0].t + eventList[0].x;
    int rightMostPoint = eventList[0].t - curr + eventList[0].x;

    // For each point, we gon see if we need more bombs to blow everything up
    for (int i = 1; i < n; ++i){
        int currLeftMostPoint = curr - eventList[i].t + eventList[i].x;
        int currRightMostPoint = eventList[i].t - curr + eventList[i].x;

        // First, lets see if the current left most point has overshot the right
        // most possible point the previous bomb could have been:
        // That means we need to have one more bomb, and reset the bounds
        if (currLeftMostPoint > rightMostPoint){
            numBombs++;
            leftMostPoint = currLeftMostPoint;
            rightMostPoint = currRightMostPoint;
        }

        // Else, lets see if we have overlaps on the bounds.
        // Note that we will never need to shrink the right bound since the ranges
        // will only keep increasing towards the right.
        // Simply update the left most bound.
        else if (leftMostPoint <= currLeftMostPoint &&
                 rightMostPoint >= currLeftMostPoint &&
                 rightMostPoint <= currRightMostPoint){
            leftMostPoint = currLeftMostPoint;
        }

        // Last case, if our new interval is enclosed
        // Then we need to update both bounds!
        else if (leftMostPoint <= currLeftMostPoint &&
                 rightMostPoint >= currRightMostPoint){
            leftMostPoint = currLeftMostPoint;
            rightMostPoint = currRightMostPoint;
        }

        // If we used more bombs than we needed to, return 0.
        if (numBombs > m) return 0;
    }

    // If we reached here, we have survived! Return 1
    return 1;
}


int main(){
    int testcases;
    scanf("%d", &testcases);

    // Solve for each test case
    for (int cases = 1; cases <= testcases; ++cases){
        scanf ("%d %d", &n, &m);

        // Initialise the variables for the binary search and the answer.
        int hi = 5000000, lo = -2000005;
        int out;

        // Scan in the events
        // Don't be tricked by the flipped
        int x, t;
        for (int i = 0; i < n; ++i){
            scanf ("%d %d", &t, &x);
            Event newEvent;
            newEvent.x = x;
            newEvent.t = t;
            eventList[i] = newEvent;
            hi = MIN(hi, t);
        }

        // First, we sort the list of events
        qsort(eventList, n, sizeof(Event), cmpfunc);


        // This is EMP missiles style. Binary search for the answer!
        while (hi >= lo){
            int mid = (hi+lo)/2;
            if (check(mid)){
                out = mid;
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }

        // Print that shit
        printf ("Case %d: %d\n", cases, out);
    }
    return 0;
}
