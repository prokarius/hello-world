#include<stdio.h>
#include<math.h>

// Coordinates of the points
double points[32][32][3];
double areas[32];

double ABS(double x){
    return (x > 0)?(x):(-x);
}

double dist(double dx, double dy, double dz){
    return sqrt(dx*dx + dy*dy + dz*dz);
}

// Returns the area of the triangle
double herons(double a, double b, double c){
    double p = (a + b + c) / 2;
    return (sqrt((p-a)*(p-b)*(p-c)*p));
}

double getVolume(){
    int numFaces;
    scanf("%d", &numFaces);

    int totalVertices = 0;
    double threeDCenterx = 0;
    double threeDCentery = 0;
    double threeDCenterz = 0;

    double totalVolume = 0;

    for (int i = 0; i < numFaces; ++i){
        int numPoints;
        scanf("%d", &numPoints);

        // Scan in input
        // Get the center of all the points while we are at it
        double centerx = 0, centery = 0, centerz = 0;
        for (int j = 0; j < numPoints; ++j){
            scanf("%lf %lf %lf", &points[i][j][0], &points[i][j][1], &points[i][j][2]);
            centerx += points[i][j][0];
            centery += points[i][j][1];
            centerz += points[i][j][2];
        }
        points[i][numPoints][0] = points[i][0][0];
        points[i][numPoints][1] = points[i][0][1];
        points[i][numPoints][2] = points[i][0][2];

        // Add to the center
        threeDCenterx += centerx;
        threeDCentery += centery;
        threeDCenterz += centerz;
        totalVertices += numPoints;

        centerx /= numPoints;
        centery /= numPoints;
        centerz /= numPoints;

        // Get the area of this polygon
        areas[i] = 0;
        for (int j = 0; j < numPoints; ++j){
            areas[i] += herons(
                            dist(points[i][j][0] - points[i][j+1][0],
                                 points[i][j][1] - points[i][j+1][1],
                                 points[i][j][2] - points[i][j+1][2]),
                            dist(centerx - points[i][j+1][0],
                                 centery - points[i][j+1][1],
                                 centerz - points[i][j+1][2]),
                            dist(points[i][j][0] - centerx,
                                 points[i][j][1] - centery,
                                 points[i][j][2] - centerz)
                    );
        }
    }

    threeDCenterx /= totalVertices;
    threeDCentery /= totalVertices;
    threeDCenterz /= totalVertices;

    // We need to get the distance from the center to each face
    for (int i = 0; i < numFaces; ++i){
        // First get the normal vector
        double ax = points[i][0][0] - points[i][1][0];
        double ay = points[i][0][1] - points[i][1][1];
        double az = points[i][0][2] - points[i][1][2];

        double bx = points[i][0][0] - points[i][2][0];
        double by = points[i][0][1] - points[i][2][1];
        double bz = points[i][0][2] - points[i][2][2];

        // Get the cross product
        double nx = ay*bz - az*by;
        double ny = az*bx - ax*bz;
        double nz = ax*by - ay*bx;
        double d = -(points[i][0][0]*nx + points[i][0][1]*ny + points[i][0][2]*nz);

        double height = (nx*threeDCenterx + ny*threeDCentery + nz*threeDCenterz + d)/dist(nx, ny, nz);
        height = ABS(height);

        totalVolume += areas[i] * height / 3;
    }
    return totalVolume;
}

int main(){
    int numPolyhedra;
    scanf("%d", &numPolyhedra);

    double totalVolume = 0;
    for (int i = 0; i < numPolyhedra; ++i){
        totalVolume += getVolume();
    }

    printf("%.2lf\n", totalVolume);
    return 0;
}

