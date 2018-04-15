#include<stdio.h>
#include<string.h>

char convert (int intstring, int type){
    if (type == 0){ // number
        return '0' + intstring;
    }
    if (type == 1){
        return 'A' + intstring;
    }
    return 'a' + intstring;
}

int main(){
    int add;
    char string[103];
    int intstring[103];
    int type[103];
    char newstring[103];

    // Scan in input
    while (scanf("%s %d", string, &add) != EOF){
        int len = strlen(string);

        // Convert the letters into numbers.
        for (int i=0; i<len; ++i){
            if (string[i] - '9' <= 0){
                intstring[i] = string[i] - '0';
                type[i] = 0; // number
            }
            else if (string[i] - 'Z' <= 0){
                intstring[i] = string[i] - 'A';
                type[i] = 1; // CAPS LETTER
            }
            else{ // small letter
                intstring[i] = string[i] - 'a';
                type[i] = 2;
            }
        }

        // For each digit, check if we need to add
        for (int i=len-1; i>=0; --i){
            if (add == 0){
                break;
            }
            // Yes we need to add
            // Is it a number?
            if (type[i] == 0){
                intstring[i] += add % 10;
                add /= 10;
                // Check for overflows
                if (intstring[i] >= 10){
                    intstring[i] -= 10;
                    ++add;
                }
            }
            else {
                intstring[i] += add % 26;
                add /= 26;
                // Check for overflows
                if (intstring[i] >= 26){
                    intstring[i] -= 26;
                    ++add;
                }
            }
        }

        // OK we have done all the arithmetic.
        // If we have still have an add, print the carry
        int head = 0;
        int ghettostackhead = 0;
        char ghettostack[10];
        int flag = 0;
        if (type[0]){
            while (add){
                if (add % 26 == 0){
                    ghettostack[ghettostackhead++] = convert(25, type[0]);
                    add -= 26;
                }
                else {
                    ghettostack[ghettostackhead++] = convert((add % 26)-1, type[0]);
                }
                add /= 26;
                flag++;
            }
        }
        else {
            while (add){
                ghettostack[ghettostackhead++] = convert(add % 10, type[0]);
                add /= 10;
            }
        }

        while(ghettostackhead){
            newstring[head] = ghettostack[--ghettostackhead];
            head++;
        }

        for (int i=0; i<len; ++i){
            newstring[head++] = convert(intstring[i], type[i]);
        }
        newstring[head] = '\0';

        for (int i=0; i<head; ++i){
            printf("%c", newstring[i]);
        }
        printf("\n");
    }

    return 0;
}
