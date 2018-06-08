#include<stdio.h>
#include<stdlib.h>

// Oh my lord, this solution has so much duct tape...
// Dear whoever is reading this solution, I am so sorry.

typedef struct{
    int x;
    int y;
} Point;

typedef struct{
    Point start;
    Point end;
    int swap;
    double gradient;
} Line;

// Given two points, returns their gradients
double gradientCalc(Point one, Point two){
    if (one.x == two.x){
        return 1000000007;
    }
    return ((double)(two.y - one.y)) / (two.x - one.x);
}

// Checks if two points are the same
int equal(Point a, Point b){
    return (a.x == b.x) && (a.y == b.y);
}

// Returns -1 if the sign is negative, or 1 if the sign is positive
int sign(double x){
    return (0 < x) - (x < 0);
}

// Public constructor for a line
// We want to make it so that start is always higher than endy
Line MakeLine(int startx, int starty, int endx, int endy){
    Line output;
    Point a, b;

    if (starty > endy){
        a.x = startx;
        a.y = starty;
        b.x = endx;
        b.y = endy;
        output.swap = 0;
    }
    else {
        b.x = startx;
        b.y = starty;
        a.x = endx;
        a.y = endy;
        output.swap = 1;
    }

    output.gradient = gradientCalc(a, b);
    output.start = a;
    output.end = b;
    return output;
}

// Given a line and a y value, find out which x value the line intersects
// The returned x value is rounded down to the nearest int.
double xintercept(Line prevline, Line line, Line nextline, int y){
    // First, we need to check the validity of the line.
    // If the y coordinate is not within y of the line's end points, return 10007.
    if (line.start.y < y || line.end.y > y){
        return 10007;
    }

    // If the line is horizontal, include a point only if the end connects to
    // another line that is not horizontal
    if (line.gradient == 0){
        if (nextline.gradient == 0){
            return 10007;
        }
        else {
            printf("HOrizontal line at %d\n", line.end.x);
            return line.end.x;
        }
    }

    // If the line is vertical, we just return the x value.
    if (line.gradient == 1000000007){
        printf("Vertical line at %d\n", line.start.x);
        if (y == line.start.y || y == line.end.y){
            return line.start.x + 100000;
        }
        return line.start.x;
    }

    // It we need to check if the current y is the line's starting point.
    // We will only return a valid point if the previous line has a gradient of same sign
    // I.e. the two lines does not form a ^ or a v.
    if (y == line.start.y){
        if ((line.swap == 0 && prevline.start.y == line.start.y) ||
            (line.swap == 1 && nextline.start.y == line.start.y)) {
            // It forms a v or a ^, or it leads to a horizontal line
            return 10007;
        }
        printf("Ending Line at %d\n", line.start.x);
        return line.start.x + 100000;
    }
    else if (y == line.end.y){
        return 10007;
    }

    // Else, we will need to find the x intercept.
    // Remember that it is impossible for the line to be horizontal.
    double toreturn = ((y - line.start.y) / line.gradient) + line.start.x;
    printf ("Returning %lf from line %d %d %d %d\n", toreturn, line.start.x, line.start.y, line.end.x, line.end.y);
    return toreturn;
}


// Global ghettoList methods
double ghettoList[105];
int ghettoListHead = 0;

void push(double value){
    ghettoList[ghettoListHead++] = value;
}

int cmpfunc(const void *a, const void *b){
    double first = *(double*) a;
    double second = *(double*) b;
    return (a<b) - (b<a);
}

// Stores the state of the previous
int memory[205][205];

// Im duct taping something here because in the list of intersects there should not
// be any repeats. This will act to catch repeated
int repeat[205][205];

// Main run function
void run(int n){
    int coords[101][2];
    Line linelist[105];
    int lineHead = 1;

    // Scan in input
    int maxy = -1000;
    int miny = 1000;
    for (int i = 0; i < n; ++i){
        scanf("%d %d", &coords[i][0], &coords[i][1]);
        if (maxy < coords[i][1]) maxy = coords[i][1];
        if (miny > coords[i][1]) miny = coords[i][1];
    }

    coords[n][0] = coords[0][0];
    coords[n][1] = coords[0][1];

    // Make my lines and populate the line list
    for (int i = 0; i < n; ++i){
        Line ph =  MakeLine(coords[i][0], coords[i][1], coords[i+1][0], coords[i+1][1]);

        // If the line is horizontal, add all its points to the memory
        if (ph.gradient == 0){
            for (int i = ph.end.x; i < ph.start.x; ++i){
                memory[ph.start.y + 101][i+101]++;
            }
            for (int i = ph.start.x; i < ph.end.x; ++i){
                memory[ph.start.y + 101][i+101]++;
            }
        }
        else {
            linelist[lineHead++] = ph;
        }
    }

    // Just to help with the xintercept function
    linelist[0] = linelist[lineHead-1];
    linelist[lineHead+1] = linelist[1];

    int output = 0;
    while (miny <= maxy){
        printf("looking at y = %d\n", miny);
        // For each row, check where each line intersects.
        for (int i = 1; i < lineHead; ++i){
            double intersect = xintercept(linelist[i-1], linelist[i], linelist[i+1], miny);

            // Only push if the x intercept point is valid and is not repeated.
            if (intersect != 10007){
                if (intersect > 90000){
                    intersect = intersect - 100000;
                    int memorise = (int)(intersect + 1e-6);
                    if (memory[miny][memorise] == 0){
                        push(intersect);
                        memory[miny][memorise]++;
                    }
                }
                else{
                    push(intersect);
                }
            }
        }

        // Sort the intersection points
        qsort(ghettoList, ghettoListHead, sizeof(double), cmpfunc);

        printf ("Number of intersects = %d\n", ghettoListHead);
        for (int j = 0; j < ghettoListHead; ++j){
            printf("%lf ", ghettoList[j]);
        }
        printf("\n");

        for (int i = 0; i < ghettoListHead/2; ++i){
            int start = (int)(ghettoList[2*i] - 1e-6) + 1; // Left inclusive
            int end = (int)(ghettoList[2*i + 1] + 1e-6); // Right inclusive
            printf("start = %d, end = %d\n", start, end);
            int numpoints = end - start;
            if (numpoints > 0){
                // If there is such a case, check if the previous line has the same
                // two points that have been activated.
                while (end >= start){
                    printf("Looking at x = %d\n", start);
                    memory[miny + 101][start + 101] = 1;
                    if (memory[miny + 100][start + 101]){
                        // Yes, it has been activated before. Add one to output.
                        printf("YES!\n");
                        output++;
                    }
                    start++;
                }
            }
        }
        printf("Currentout = %d\n", output);

        // Reset the ghettoList
        for (int i = 0; i < ghettoListHead; ++i){
            ghettoList[i] = 0;
        }
        ghettoListHead = 0;

        miny ++;
    }

    // Then print that shit
    printf ("%d\n", output);
}

int main(){
    int n;
    scanf ("%d", &n);
    while (n){
        run(n);
        scanf ("%d", &n);
    }
    return 0;
}
