#include<stdio.h>

#define EPSILON 1e-8

// Hard coded Math module methods
// Returns abs of a value
double ABS(double x){
    if (x < 0){
        return -x;
    }
    return x;
}

// I really should have declared the point class from the start
typedef struct{
    double x;
    double y;
} Point;

// This is the !.equals() method for points
int notequals(Point a, Point b){
    if (ABS(a.x - b.x) > EPSILON || ABS(a.y - b.y) > EPSILON){
        return 1;
    }
    return 0;
}

typedef struct{
    Point head;
    Point tail;
    double gradient;
} Trench;

// Trench methods

// Return the gradient of the trenches.
// Returns 1000000007 if it's vertical
double gradient (int x1, int y1, int x2, int y2){
    if (x1 == x2){
        return 1000000007;
    }
    return ((double)(y2 - y1)) / (x2 - x1);
}

// Public constructor
// Note that x1 < x2.
// If not, then we'll swap the two things around during construction
// BUT IF THE TRENCH IS VERTICAL, then make it so that y1 < y2.
Trench trench(int x1, int y1, int x2, int y2){
    Trench new;
    if (x1 > x2 || (x1 == x2 && y1 > y2)){
        int temp = x2;
        x2 = x1;
        x1 = temp;
        temp = y2;
        y2 = y1;
        y1 = temp;
    }

    Point a, b;
    a.x = x1;
    a.y = y1;
    b.x = x2;
    b.y = y2;
    new.head = a;
    new.tail = b;
    new.gradient = gradient(x1, y1, x2, y2);
    return new;
}

// Determine if the trenches overlap.
int overlap(Trench first, Trench second){
    // Check if the gradients are not the same
    if (ABS(first.gradient - second.gradient) > EPSILON){
        return 0;
    }

    // If the gradients are the same, then we need to check if the y intersect
    // of each of the two trenches lies in the same place.
    // Line equation y1 = mx1 + yintersect
    // yintersect = y1 - mx1
    // But only in the case where it's not vertical.
    if (first.gradient != 1000000007){
        double yinter1 = first.head.y - first.gradient*first.head.x;
        double yinter2 = second.head.y - second.gradient*second.head.x;

        if (ABS(yinter1 - yinter2) > EPSILON){
            return 0;
        }

        // Last, check if the y coords intersect each other
        if ((second.head.x <= first.tail.x && first.head.x <= second.head.x) ||
            (first.head.x <= second.tail.x && second.head.x <= first.head.x)){
            return 1;
        }
        return 0;
    }

    // If it's vertical, then we gotta check if the x coordinates are the same
    // Lastly, check if they y coordinates intersect each other
    else {
        if (ABS(first.head.x - second.head.x) > EPSILON){
            return 0;
        }
        if ((second.tail.y >= first.head.y && second.head.y <= first.head.y) ||
             (first.tail.y >= second.head.y && first.head.y <= second.head.y)){
        return 1;
        }
    }

    // Sadly they don't intersect
    return 0;
}

// Returns a new Trench that is the conglomeration of the two.
// Essentially picks the furthest x1 and x2s.
Trench makeOverlap(Trench first, Trench second){
    Trench new;
    // By here we can confirm that the trenches have the same gradients
    new.gradient = first.gradient;

    // Check if the gradient is vertical
    // If so, check for the smallest y1 values, and largest y2 values.
    if (first.gradient == 1000000007){
        if (first.head.y < second.head.y){
            new.head = first.head;
        }
        else {
            new.head = second.head;
        }

        if (first.tail.y > second.tail.y){
            new.tail = first.tail;
        }
        else {
            new.tail = second.tail;
        }
    }

    // Else, we just choose the smallest x1 and the largest x2
    else{
        if (first.head.x < second.head.x){
            new.head = first.head;
        }
        else {
            new.head = second.head;
        }

        if (first.tail.x > second.tail.x){
            new.tail = first.tail;
        }
        else {
            new.tail = second.tail;
        }
    }

    // Finally, return the new trench
    return new;
}

// Returns the orientation of the 3 given points
// 0 is collinear
// 1 is clockwise
// 2 is counterclockwise
int orientation(Point a, Point b, Point c){
    double cross = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);
    if (cross){
        return (cross > 0) ? 1 : 2;
    }
    return 0;
}

// Returns if the trenches intersect each other
int checkorientation(Trench a, Trench b){
    int o1 = orientation(a.head, a.tail, b.head);
    int o2 = orientation(a.head, a.tail, b.tail);
    int o3 = orientation(b.head, b.tail, a.head);
    int o4 = orientation(b.head, b.tail, a.tail);

    if (o1 != o2 && o3 != o4){
        return 1;
    }
    return 0;
}

// Given two line segments that are guaranteed to intersect, finds the
// intersection point of them and returns it as a double
// Ripped off Wikipedia
Point findPoint(Trench one, Trench two){
    Point output;
    double x1 = one.head.x;
    double y1 = one.head.y;
    double x2 = one.tail.x;
    double y2 = one.tail.y;
    double x3 = two.head.x;
    double y3 = two.head.y;
    double x4 = two.tail.x;
    double y4 = two.tail.y;

    double xtop = ((x1*y2) - (y1*x2))*(x3 - x4) - (x1 - x2)*((x3*y4) - (y3*x4));
    double ytop = ((x1*y2) - (y1*x2))*(y3 - y4) - (y1 - y2)*((x3*y4) - (y3*x4));
    double bottom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);

    output.x = xtop/bottom;
    output.y = ytop/bottom;

    return output;
}

// Determine if three trenches intersects three times
// We just need to determine that pairwise they intersect each other.
// Hence calculate the theoretical intersection point, and see if they
int intersect(Trench first, Trench second, Trench third){
    // First check if the gradients are the same.
    // If they are, they're overlapping or parallel.
    // But we merged all overlapping things. So they must be parallel.
    // Die.
    if (first.gradient == second.gradient || second.gradient == third.gradient){
        return 0;
    }

    // Then calculate the intersection point of all three pairwise
    // Ripped off geek for geeks
    if (checkorientation(first, second) &&
        checkorientation(second, third) &&
        checkorientation(first, third)){

        // BUT WAIT, they could intersect at the same point.
        // So we gotta find the intersection point and check that
        Point firstsecond = findPoint(first, second);
        Point firstthird = findPoint(first, third);
        if (notequals(firstsecond, firstthird)){
            return 1;
        }
    }
    return 0;
}

void print(Trench trench){
    Point a = trench.head;
    Point b = trench.tail;
    printf("%lf %lf %lf %lf %lf\n", a.x, a.y, b.x, b.y, trench.gradient);
}

int main(){
    Trench trenchlist[20];
    int deleted[20];
    int n;

    // Scan in input
    scanf("%d", &n);
    for (int i=0; i<n; ++i){
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        trenchlist[i] = trench(x1, y1, x2, y2);
        deleted[i] = 0;
    }

    // For each trench, if it intersects some trench we've seen before,
    // Calculate the new trench and replace the old one with it.
    // Mark the original one for deletion.
    for (int i=1; i<n; ++i){
        for (int j=0; j<i; ++j){
            if (deleted[j]) continue;
            if (overlap(trenchlist[i], trenchlist[j])){
                trenchlist[i] = makeOverlap(trenchlist[i], trenchlist[j]);
                deleted[j] = 1;
                break;
                }
        }
    }

    // Lastly for every set of 3 trenches, check for intersections.
    int ans = 0;
    for (int i=2; i<n; ++i){
        if (deleted[i]) continue;
        for (int j=1; j<i; ++j){
            if (deleted[j]) continue;
            for (int k=0; k<j; ++k){
                if (deleted[k]) continue;
                if (intersect(trenchlist[i], trenchlist[j], trenchlist[k])){
                    ans += 1;
                }
            }
        }
    }

    // Print that shit.
    printf("%d\n", ans);
    return 0;
}
