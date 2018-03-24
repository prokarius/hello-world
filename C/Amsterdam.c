#include<stdio.h>
#include<math.h>

#define MIN(x,y) ((x<y)?(x):(y))
#define PI 3.14159265358979

int main(){
    int M, N, ax, ay, bx, by;
    double R;
    scanf ("%d %d %lf %d %d %d %d", &M, &N, &R, &ax, &ay, &bx, &by);
    double seg = R/N;

    // Shortest is either by all the way in
    double best = (ay + by);

    // Or it's the outer most circular segment
    double calc = MIN(ay, by) * fabs(ax-bx)*PI/M;
    calc += fabs(ay - by);

    best = MIN (calc, best);
    printf ("%.8lf\n", best*seg);
    return 0;
}
