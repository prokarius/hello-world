#include<stdio.h>
#include<math.h>

// Index 0 stores time, Index 1 stores x, Index 2 stores y
int runPoints[128][3];

// Index 0 stores x, Index 1 store y
double GPSPoints[1000005][2];

int main(){
    // Scan in input
    int numPoints, timeQuanta;
    scanf("%d %d", &numPoints, &timeQuanta);

    for (int i = 0; i < numPoints; ++i){
        int x, y, time;
        scanf ("%d %d %d", &x, &y, &time);
        runPoints[i][0] = time;
        runPoints[i][1] = x;
        runPoints[i][2] = y;
    }

    // Calculate the actual distance ran
    double actualDistance = 0;
    for (int i = 0; i < numPoints-1; ++i){
        double dx = runPoints[i][1] - runPoints[i+1][1];
        double dy = runPoints[i][2] - runPoints[i+1][2];
        actualDistance += hypot(dx, dy);
    }

    // Input the first point
    GPSPoints[0][0] = runPoints[0][1];
    GPSPoints[0][1] = runPoints[0][2];

    // Now calculate the points the GPS measures
    int currTime = timeQuanta;
    int currentLeg = 0;
    int numGPSPoints = 1;
    while (currTime < runPoints[numPoints-1][0]){
        while (runPoints[currentLeg+1][0] < currTime){
            currentLeg++;
        }

        int legStartTime = runPoints[currentLeg][0];
        int legEndTime = runPoints[currentLeg+1][0];
        double dt = legEndTime - legStartTime;
        double proportion = (currTime - legStartTime) / dt;

        double dx = runPoints[currentLeg+1][1] - runPoints[currentLeg][1]; 
        double dy = runPoints[currentLeg+1][2] - runPoints[currentLeg][2]; 

        double x = runPoints[currentLeg][1] + proportion * dx;
        double y = runPoints[currentLeg][2] + proportion * dy;
    
        GPSPoints[numGPSPoints][0] = x;
        GPSPoints[numGPSPoints][1] = y;

        currTime += timeQuanta;
        ++numGPSPoints;
    }

    // Append the last point to the end of the array
    GPSPoints[numGPSPoints][0] = runPoints[numPoints-1][1];
    GPSPoints[numGPSPoints][1] = runPoints[numPoints-1][2];

    // Do the same calculation for the GPS points
    double GPSDistance = 0;
    for (int i = 0; i < numGPSPoints; ++i){
        double dx = GPSPoints[i][0] - GPSPoints[i+1][0];
        double dy = GPSPoints[i][1] - GPSPoints[i+1][1];
        GPSDistance += hypot(dx, dy);
    }

    // Print out the percentage difference
    printf("%lf\n", 100 - (100 * GPSDistance / actualDistance));

    return 0;
}
