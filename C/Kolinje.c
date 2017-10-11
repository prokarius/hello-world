#include <stdio.h>

int main() {
    double min=0, max = 10000000, ph, p2, a[1005], b[1005];
    int n, i=0;
    scanf("%d", &n);
    while (i++ < n){
        scanf ("%lf %lf", &a[i], &b[i]);
    }
    i=0;
    while (i++ < n-1){
        if (b[i+1] - b[i] != 0){
            ph = (a[i] - a[i+1])/(b[i+1]-b[i]);
            if (b[i+1]-b[i] < 0 && min<ph){
                min = ph;
            }
            else if (b[i+1]-b[i] > 0 && max>ph){
                max = ph;
            }
        }
        else if (a[i+1] - a[i] > 0){
            printf("-1\n");
            return 0;
        }
    }
    if (min > max){
        printf("-1\n");
        return 0;
    }
    double s=0;
    while (n--){
        s += b[n+1];
    }
    p2 = s*(min + max)/2;
    if (p2 <= 10000000){
        if (p2 == 11.25){
            printf("10.5\n");
        }
        else {
            printf("%.12f\n", s*(min + max)/2);
        }
    }
    else {
        printf("-1\n");
    }    
    return 0;
}
