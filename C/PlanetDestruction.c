#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define PI 3.14159265358979
#define PI2 6.28318530718
#define EPSILON 1e-8

typedef struct{
    double left;
    double right;
} Virus;

typedef struct{
    double reachTime; // When the ship hits the planet
    double angle; // Angle where the rocket strikes
    double speed; // Speed of the virus
} Ship;

// Takes two virus pointers and returns their sorted ordering
int cmpfunc(const void *a, const void *b){
    Virus first = *(Virus*) a;
    Virus second = *(Virus*) b;
    double value = first.left - second.left;
    if (value == 0){
        return (first.right - second.right) > (second.right - first.right);
    }
    return (value) > (-value);
}

// Given an input time, and an array of ships, calculates
// whether the virus takes over the planet
int check(double currtime, Ship ships[], int numships){
    Virus segments[20005];
    int numsegments = 0;

    // Simulate the virus from each ship
    for (int i=0; i<numships; i++){

        // If the ship don't reach the planet yet, just skip it.
        if (ships[i].reachTime > currtime){
            continue;
        }
        double range = ships[i].speed * (currtime - ships[i].reachTime);

        // Check if this strain of virus made it around the planet.
        if (range >= PI){
            return 1;
        }

        // Adding the virus to the list
        double left = ships[i].angle - range;
        double right = ships[i].angle + range;
        Virus curr;

        // Check if the stuff is outside [0, 2*PI].
        if (left < 0){
            curr.left = -EPSILON;
            curr.right = right;
            segments[numsegments++] = curr;
            curr.right = PI2 + EPSILON;
            curr.left = PI2 + left;
            segments[numsegments++] = curr;
        }
        else if (right > PI2){
            curr.right = PI2 + EPSILON;
            curr.left = left;
            segments[numsegments++] = curr;
            curr.left = -EPSILON;
            curr.right = right - PI2;
            segments[numsegments++] = curr;
        }
        else {
            curr.left = left;
            curr.right = right;
            segments[numsegments++] = curr;
        }
    }

    // This bit means none of the rockets has arrived yet.
    if (numsegments == 0){
        return 0;
    }

    // Sort the list of virusses
    qsort(segments, numsegments, sizeof(Virus), cmpfunc);

    // Check if it even touched 0 before
    if (segments[0].left > 0){
        return 0;
    }

    // Else set the right edge to be the end point of the first segment.
    double rightedge = segments[0].right;

    // Iterate through all the edges, if a segment manages to extend the
    // distance of the right edge, extend it.
    for (int i = 0; i<numsegments; i++){

        // First check if the rightedge is more right
        if (segments[i].right - rightedge > -EPSILON){
            // Then check if left edge is more left
            if (rightedge - segments[i].left > -EPSILON){
                // Update if it is
                rightedge = segments[i].right;
            }

            // If it's not more left, then we will never ever be more left
            // Return false.
            else{
                return 0;
            }
        }
    }

    // Now if we are here, we just need to see if the right edge is greater than PI2
    return (rightedge - PI2 > -EPSILON);
}

void run(){
    int rad, numship;
    scanf("%d %d", &rad, &numship);

    // Create an array to store the ships
    Ship ship[10002];

    for (int i=0; i<numship; i++){
        double x, y, rocketspeed, virusspeed;
        scanf("%lf %lf %lf %lf", &x, &y, &rocketspeed, &virusspeed);
        double distance = sqrt(x*x + y*y) - rad;
        Ship curr;
        curr.reachTime = distance / rocketspeed;
        curr.angle = atan2(y, x) + PI;
        curr.speed = virusspeed/rad;
        ship[i] = curr;
    }

    // We will do a binary search for the answer.
    double low = 0;
    double high = 20000000;
    while (high - low > EPSILON){
        double mid = (low + high)/2;
        if (check(mid, ship, numship)){
            high = mid;
        }
        else {
            low = mid;
        }
    }

    printf ("%lf\n", low);
}

int main(){
    int test;
    scanf ("%d", &test);
    while (test--){
        run();
    }
    return 0;
}
