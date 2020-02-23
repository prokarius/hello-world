#include<stdio.h>
#include<string.h>

char input[1<<20];

// Its really just counting in the number of digits right...?
int process(char* number){
    if (strcmp(number, "1") == 0) return 1;
    int length = strlen(number);
    if (length == 1) return 2;
    if (length < 10) return 3;
    return 4;
}

int main(){
    // Scan in input
    scanf("%s", input);
    while (strcmp(input, "END") != 0){
        printf("%d\n", process(input));
        scanf("%s", input);
    }
    return 0;
}

