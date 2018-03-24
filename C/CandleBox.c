#include <stdio.h>

int bdlr [53], bdlt [53];

int main(){
    int d, t, r, i, sr = 0, st = 0;
    scanf ("%d %d %d", &d, &r, &t);
    for(i = 4; i < 46; i++){
        sr += i;
        bdlr [i] = sr;
    }
    for(i = 3; i < 46; i++){
        st += i;
        bdlt [i] = st;
    }
    for(i = 3+d; i<50; i++){
        int x = r - bdlr[i];
        if (bdlt[i-d] == t+x){
            printf ("%d", x);
            return 0;
        }
    }
    return 0;
}
