#include<stdio.h>
#include<math.h>

typedef struct{
    double x;
    double y;
} House;

// Constructor
House house(double x, double y){
    House output;
    output.x = x;
    output.y = y;
    return output;
}

House houses[50005];

// Distance function.
double distance(House first, House second){
    double dx = first.x - second.x;
    double dy = first.y - second.y;
    return sqrt(dx*dx + dy*dy);
}

void solve(int n){
    // Scan in input
    for (int i = 0; i < n; ++i){
        double x, y;
        scanf ("%lf %lf", &x, &y);
        houses[i] = house(x, y);
    }

    // Do a clever binary search
    double furthest;
    double furthestDist = -1;
    double delta = 200000;
    double currentX = 0;
    while (delta > 5e-7){
        House position = house(currentX, 0);
        furthestDist = -1;

        // For each house, find the distance to the current x point
        for (int i = 0; i < n; ++i){
            double dist = distance(position, houses[i]);

            if (dist > furthestDist){
                furthestDist = dist;
                furthest = houses[i].x;
            }
        }

        // Scoot the x position towards the house
        currentX = currentX + delta * ((furthest > currentX)?(1):(-1));

        // Then divide the distance by 2
        delta /= 2;
    }

    printf("%lf %lf\n", currentX, furthestDist);
}

int main(){
    int n;
    scanf("%d", &n);

    while(n){
        solve(n);
        scanf("%d", &n);
    }

    return 0;
}
