#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main(){
    double r, h ,s;
    double output;
    scanf("%lf %lf %lf", &r ,&h, &s);
    while (r != 0 || h!=0 || s!= 0){
        output = ((PI-acos(r/h))*r)+sqrt(h*h - r*r);
        output *= ((100 + s)/50.0);
        printf ("%.2f\n", output);
        scanf("%lf %lf %lf", &r ,&h, &s);
    }
    return 0;
}
