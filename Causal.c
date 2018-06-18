#include<stdio.h>
#include<stdlib.h>

#define MAX(x,y) ((x > y)?(x):(y))


int xcoords[100005], ycoords[100005];
int left[100005], right[100005];

int check(int curr){



}


int main(){
    int testcases;
    scanf("%d", &testcases);

    // Solve for each test case
    for (int cases = 1; cases <= testcases; ++cases){
        int n, m;
        scanf ("%d %d", &n, &m);

        // Initialise the variables for the binary search
        int high = 5000000, low = -2000005;

        // Scan in the points
        int x, y;
        for (int i = 0; i < n; ++i){
            scanf ("%d %d", &x, &y);
            xcoords[i] = x, ycoords[i] = y;
            high = MAX(high, y);

            // Populate the left and right array
            left[i] = 



        }

        // Print that shit
        printf ("case %d: %d", cases, out);
    }
    return 0;
}
