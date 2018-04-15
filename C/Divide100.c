#include<stdio.h>
#include<string.h>

int main(){
    char n[1000005];
    char m[1000005];

    scanf("%s %s", n, m);
    int divisor = strlen(n);
    // number of decimal places to scoot over by
    int digits = strlen(m) - 1;
    int pre = divisor - digits;

    // Figure out where the trailing 0s end.
    --divisor;
    while (n[divisor] == '0'){
        --divisor;
    }

    // This bit to to take care of the stuff before the decimal point
    // If pre is below 0, it means we scooted over too many points.
    int end = digits;
    if (pre <= 0){
        printf("0.");
        // Print the correct number of 0s
        for (int j = -pre; j>0; j--){
            printf("0");
        }
        for (int j = 0; j<=divisor; ++j){
            printf("%c", n[j]);
        }
        printf("\n");
    }

    //Else, account for the decimal point
    else {
        int i = 0;
        for (; i<pre; i++){
            printf("%c", n[i]);
        }
        if (i <= divisor){
            printf(".");
            while (i <= divisor){
                printf("%c", n[i]);
                i++;
            }
        }
        printf("\n");
    }
    return 0;
}
