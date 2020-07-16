#include<stdio.h>
#include<math.h>

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        double w, g, h, r;
        scanf("%lf %lf %lf %lf", &w, &g, &h, &r);

        // Remove r from g and h
        g -= r;
        h -= r;

        // If g > h, flip them
        if (g > h){
            double temp = h;
            h = g;
            g = temp;
        }

        // The shortest distance is directly from g to h
        double min = sqrt((h-g)*(h-g) + (w*w));

        // Max is when you reflect g around the ground
        double max = sqrt((h+g)*(h+g) + (w*w));

        printf("%lf %lf\n", min, max);
    }

    return 0;
}

