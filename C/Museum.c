#include<stdio.h>

// Ripped off geekforgeeks
typedef struct { 
    double x; 
    double y; 
} Point;

Point point(double x, double y){
    Point output;
    output.x = x;
    output.y = y;
    return output;
}

int orientation(Point p, Point q, Point r) 
{ 
    double val = (q.y - p.y) * (r.x - q.x) - 
                 (q.x - p.x) * (r.y - q.y); 
  
    return val > 0;
} 
  
int intersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) return 1; 
    return 0;
} 

Point pedastal[4];
Point walls[405];
int numWalls = 0;

int impossible[405][405];

void solve(){
    // Scan in input
    int L, W;
    scanf ("%d %d", &W, &L);

    double topX, topY, width;
    scanf("%lf %lf %lf", & topX, &topY, &width);

    // Make the pedastal points
    pedastal[0] = point(topX, topY);
    pedastal[1] = point(topX, topY + width);
    pedastal[2] = point(topX + width, topY + width);
    pedastal[3] = point(topX + width, topY);

    // Reset the number of walls
    numWalls = 0;

    // Make the points array:
    for (int i = 0; i <= L; ++i){
        walls[numWalls] = point(0, i);
        numWalls++;
        walls[numWalls] = point(W, i);
        numWalls++;
    }

    // Note that we do not include the 0 point
    for (int i = 1; i < W; ++i){
        walls[numWalls] = point(i, L);
        numWalls++;
        walls[numWalls] = point(i, 0);
        numWalls++;
    }

    // Time to see if the points intersect
    // We just loop through all (2L + 2W) walls ba...
    // Note that this is symmetric about the diagonal, so lets reflect it when
    // saving the values too
    for (int i = 0; i < numWalls-1; ++i){
        for (int j = i+1; j < numWalls; ++j){
            if (intersect(walls[i], walls[j], pedastal[0], pedastal[1]) ||
                intersect(walls[i], walls[j], pedastal[1], pedastal[2]) ||
                intersect(walls[i], walls[j], pedastal[2], pedastal[3]) ||
                intersect(walls[i], walls[j], pedastal[3], pedastal[0])){
                impossible[i][j] = 1;
                impossible[j][i] = 1;
            }
            else {
                impossible[i][j] = 0;
                impossible[j][i] = 0;
            }
        }
    }

    // Cool, now do an O(n3) algorithm
    // Wow, never thought I'll be doing an O(n3) algorithm on n=400 and 31 testcases
    // 400**3 * 31 = 2B
    int output = 0;
    for (int i = 0; i < numWalls-2; ++i){
        for (int j = i+1; j < numWalls-1; ++j){
            for (int k = j+1; k < numWalls; ++k){
                // Check if they are on the same side as the wall
                if (walls[i].x == walls[j].x && walls[j].x == walls[k].x) continue;
                if (walls[i].y == walls[j].y && walls[j].y == walls[k].y) continue;

                // If any of the three intersects the pedastal, continue
                if (impossible[i][j] || impossible[j][k] || impossible[k][i]) continue;

                // This triangle is possible. Add one to output
                output++;
            }
        }
    }

    // Print the output
    printf("%d\n", output);
}

int main(){
    int testcases;
    scanf("%d", &testcases);

    for (int i = 0; i < testcases; ++i){
        solve();
    }

    return 0;
}
