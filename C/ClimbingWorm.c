#include<stdio.h>

int main(){
    // Scan in input
    int a, b, h;
    scanf("%d %d %d", &a, &b, &h);

    // I wonder if I can just simulate it...
    int times = 0;
    while (1){
        h -= a;
        times++;
        if (h <= 0) break;
        h += b;
    }

    printf("%d\n", times);

    return 0;
}

