#include <stdio.h>
#include <math.h>

int main(){
    double x, q;
    int C, n=0, f=1;
    scanf ("%lf", &x);
    if (x > 10){
        printf("No solution");
        return 0;
    }
    if (x == 1){
        for (C = 1; C<10; C++){
            printf ("%d\n", C);
        }
    }
    for (n=1; n<8; n++){
        for (C = 1; C<10; C++){
            q = C*(x*pow(10, n)-1)/(10-x) +1e-9;
            printf ("%d, %d, %d\n", C, n, (int)floor(q)+C*(int)pow(10,n));
            if (fabs(q-floor(q)) < 1e-8 && q < pow(10, n) && q >= pow(10, n-1)){
                printf ("%d\n", (int)floor(q)+C*(int)pow(10,n));
                f = 0;
            }
        }
    }
    if (f){
        printf("No solution");
    }
    return 0;
}
