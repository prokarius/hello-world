#include<stdio.h>

int main(){
    int n, v1, v2;
    scanf("%d %d %d", &n, &v1, &v2);

    int numBottle1 = n/v1;
    int numBottle2;
    int fuelLeft = n - numBottle1 * v1;

    int impossible = 0;

    // Just brute force lol
    while(fuelLeft != 0){
        if (fuelLeft % v2 == 0){
            numBottle2 = fuelLeft / v2;
            break;
        }

        if (numBottle1 == 0){
            impossible++;
            break;
        }

        numBottle1--;
        fuelLeft += v1;
    }

    if (impossible){
        printf("Impossible\n");
    }
    else {
        printf("%d %d\n", numBottle1, numBottle2); 
    }

    return 0;
}
