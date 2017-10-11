#include<cstdio>
#include<cmath>
#include<algorithm>
#define PI 3.14159265358979323846L

double f(double a, double b, double h){
    double g = (a*std::exp(-h*h) + b*std::sqrt(h));
    return g*g;
}

int main(){
    double output=9999999, V, S[7] = {0};
    int ans, i=0, N;
    scanf ("%lf %d", &V, &N);
    while (i < N){
        double a, b, dh, h, j, o=0;
        scanf ("%lf %lf %lf", &a, &b, &h);
        dh = h/4000000;
        for (j=0; j<h; j+=dh) o += dh*f(a, b, j);
        o += dh*f(a,b,h)/2;
        o *= PI;
        S[i] = std::abs (o-V);
        ++i;
    }
    i = 0;
    while (i < N){
        if (output > S[i]){
            output = S[i];
            ans = i;
        }
        ++i;
    }
    printf ("%d\n", ans);
    return 0;
}
