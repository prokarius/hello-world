#include<stdio.h>

char str[1<<20];
int LPS[1<<20];

// Do KMP
int main(){
    // Scan in input
    int len;
    scanf("%d %s", &len, str);

    // Find LPS Array
    int i = 1;
    int prefix = 0;
    LPS[0] = 0;

    while (i < len){
        if (str[i] == str[prefix]){
            prefix++;
            LPS[i++] = prefix;
        }
        else if (prefix != 0){
            prefix = LPS[prefix-1];
        }
        else {
            LPS[i] = 0;
            ++i;
        }
    }

    // Check output len
    printf("%d\n", len - LPS[len-1]);
    return 0;
}   

