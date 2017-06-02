#include <stdio.h>

int main() {
    int numtest;
    scanf("%d", &numtest);
    while (numtest --){
        int n, a, b;
        scanf("%d %d%*c%d", &n,&a,&b);
        if (b == 1){
            printf ("%d 1/%d\n", n, a+1);
            continue;
        }
        int k = a/b, t = a-k*b, p = b-t, h = t+p, d = p+k*h;
        printf ("%d %d/%d\n", n, h, d);
    }
    return 0;
}
