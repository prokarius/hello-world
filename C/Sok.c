#include<stdio.h>
#define MIN(x,y) (x)<(y) ? (x):(y)

int main(){
    double a,b,c,i,j,k, o;
    scanf ("%lf %lf %lf %lf %lf %lf", &a, &b,&c, &i, &j, &k);
    double x = a/i, y = b/j, z = c/k;
    o = MIN(MIN(x, y) , z);
    printf ("%lf %lf %lf\n", a-i*o, b-j*o, c-k*o);
    return 0;
}
