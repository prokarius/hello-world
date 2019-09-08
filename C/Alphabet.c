#include<stdio.h>
#include<string.h>

int LISLength = 1;
int LIS[64];
char alphabet[64];

int main(){
    // Scan in input
    scanf("%s", alphabet);

    // Get the length of string to do LIS
    int length = strlen(alphabet);

    for (int i = 0; i < 64; ++i){
        LIS[i] = 256;
    }

    // Do LIS
    LIS[0] = alphabet[0];
    for (int i = 1; i < length; ++i){
        for (int j = 0; j <= LISLength; ++j){
            if (LIS[j] < alphabet[i]) continue;
            LIS[j] = alphabet[i];
            if (j == LISLength) LISLength++;
            break;
        }
    }

    printf("%d\n", 26 - LISLength);

    return 0;
}
