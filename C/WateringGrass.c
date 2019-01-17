#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MIN(x, y) (x<y)?(x):(y)
#define MAX(x, y) (x>y)?(x):(y)

#define EPSILON 1e-9

typedef struct {
    double start;
    double end;
} Segment;

Segment points[10005];
int pointsHead = 0;

void reset(){
    pointsHead = 0;
}

void pushSegment(Segment sprinkler){
    points[pointsHead++] = sprinkler;
}

double ABS(double x){
    if (x < 0) return -x;
    return x;
}

// compares by first, then end
int cmpfunc(const void* a, const void* b){
    Segment first = *(Segment*) a;
    Segment second = *(Segment*) b;

    if (ABS(first.start - second.start) < EPSILON){
        return first.end > second.end;
    }
    return first.start > second.start;
}

int run(int numPoints, int length, int width){
    // Scan in input
    for (int i = 0; i < numPoints; ++i){
        double x, radius;
        scanf("%lf %lf", &x, &radius);

        // Ensure that the sprinkler can reach the furthest point on the grass strip
        if (radius <= width / 2.0) continue;

        // Save the effective horizontal distance and push the segments
        double effective = sqrt(radius*radius - width*width/4.0);

        Segment newSegment;
        newSegment.start = MAX(x - effective, 0);
        newSegment.end = MIN(x + effective, length + EPSILON);
        pushSegment(newSegment);
    }

    // Sort the ranges
    qsort(points, pointsHead, sizeof(Segment), cmpfunc);

    // Store the right most point
    double right = 0;
    int out = 0;
    double currBest = 0;

    // For each of the sprinker
    for (int curr = 0; curr < pointsHead; ++curr){
        // If we have reached past the right most point, just break
        if (right >= length) break;

        // Keep trying to find the furthest point which can be reached
        while (curr < pointsHead && right - points[curr].start > -EPSILON){
            currBest = MAX(currBest, points[curr].end);
            curr++;
        }

        // If our currentBest is unable to extend the length of watering
        if (currBest - right < EPSILON){
            out = -1;
            break;
        }

        // Else we just have to update
        right = currBest;
        out++;

        // When we are here, we have entered unwatered territory!
        // Take yourself back and reset the currentBest.
        curr--;
        currBest = 0;
    }

    // It could be the case we failed to even reach the end!
    if (right < length) out = -1;

    // Print that shit
    printf("%d\n", out);
}

int main(){
    int n, l, w;

    // Only run while we can scan in input
    while (scanf("%d %d %d", &n, &l, &w) != EOF){
        run(n, l, w);
        reset();
    }
    return 0;
}
