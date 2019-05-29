#include<stdio.h>

#define EPSILON 1e-6

int a, d;
double height = 0;
double ascent[8192][2];
double descent[8192][2];

double descend(double time){
    double distance = height;
    int i;
    for (i = 1; i <= d; ++i){
        
        // If going on the next section would take too much time, break out of the loop
        if (time < descent[i][1]){
            break;
        }
        distance -= descent[i][0];
        time -= descent[i][1];
    }

    // Now, calculate the distance up in the segment
    return distance - time * descent[i][0] / descent[i][1];
}

double ascend(double time){
    double distance = 0;
    int i;
    for (i = 1; i <= a; ++i){
        
        // If going on the next section would be too much, break out of the loop
        if (time < ascent[i][1]){
            break;
        }
        distance += ascent[i][0];
        time -= ascent[i][1];
    }

    // Now, calculate the distance up in the segment
    return distance + time * ascent[i][0] / ascent[i][1];
}

double binsearch(double lo, double hi){
    double mid = lo + (hi - lo) / 2;
    if (hi - lo < EPSILON){
        return mid;
    }

    // If we have not passed each other yet
    if ((descend(mid) - ascend(mid)) > 0){
        return binsearch(mid, hi);
    }
    return binsearch(lo, mid);
}

int main(){

    // Scan in input
    scanf("%d %d", &a, &d);

    for (int i = 1; i <= a; ++i){
        double h, t;
        scanf("%lf %lf", &h, &t);
        ascent[i][0] = h;
        ascent[i][1] = t;
    }

    for (int i = 1; i <= d; ++i){
        double h, t;
        scanf("%lf %lf", &h, &t);
        descent[i][0] = h;
        descent[i][1] = t;
    }

    // Find the total height
    double time = 0;
    for (int i = 1; i <= a; ++i){
        time += ascent[i][1];
        height += ascent[i][0];
    }

    // Do binary search and print
    printf("%lf\n", binsearch(0, time));

    return 0;
}
