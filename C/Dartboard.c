#include<stdio.h>
#include<math.h>
#define PI 3.14159265352879323846L
double s;
double q(double r){
    return (exp(-r*r/(2*s*s))/(2*PI*s*s));
}

int main(){
    double a, b, c, d, e, f, h, dh, o=0;
    scanf("%lf %lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f, &s);
    dh = (a+b+c+d+e+f)/30000000;
    for (h=dh/2; h<a; h+=dh) o += q(h)*100*PI*h*dh;
    for (; h<b; h+=dh) o+=q(h)*50*PI*h*dh;
    for (; h<c; h+=dh) o+=q(h)*21*PI*h*dh;
    for (; h<d; h+=dh) o+=q(h)*63*PI*h*dh;
    for (; h<e; h+=dh) o+=q(h)*21*PI*h*dh;
    for (; h<f; h+=dh) o+=q(h)*42*PI*h*dh;
    printf ("%lf\n", o);
    return 0;
}
