#include<stdio.h>

#define MAX(x, y) (x > y)?(x):(y)

double points[205][2];

// Given 2 line segments, returns if they intersect
// This method gets the longest line that can be formed using points at index a and b
double longestLine(int a, int b){
    


}

int main(){
    // Scan in input
    int n;
    scanf ("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%lf %lf", &points[i][0], &points[i][1]);
    }

    // So that it's easier to compare the line segments
    points[n][0] = points[0][0];
    points[n][1] = points[0][1];

    double best = -1;

    // For each pair of points see what's the longest line that can be formed
    // 2 for loops here takes O(n2)
    // Each call to longest line takes O(n) since we are looping through all
    // possible line segments
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            double out = longestLine(i, j);
            best = MAX(best, out);
        }
    }

}
