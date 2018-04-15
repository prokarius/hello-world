#include<stdio.h>
#include<string.h>

// Setting up my stacks methods
char ghettoStack[1000005];
int ghettoStackHead = 0;

void push(char ch){
    ghettoStack[ghettoStackHead++] = ch;
}

int size(){
    return ghettoStackHead;
}

// Simulates popping n elements off the stack
// Doesn't really return anything cuz nothing to return anyways...
void pop(int n){
    ghettoStackHead -= n;
}

int main(){
    char input[1000005], bomb[40];
    scanf ("%s %s", input, bomb);

    int lenin = strlen(input);
    int lenbomb = strlen(bomb);

    // For each character, push it in
    for (int i=0; i<lenin; ++i){
        push(input[i]);

        // If we have enough characters to check, and when we do strcmp on the
        // last K characters of the stack , it's equal
        if (size() >= lenbomb &&
                strncmp(ghettoStack + size() - lenbomb, bomb, lenbomb) == 0){

            // Then get rid of the previous stuff
            pop(lenbomb);
        }
    }

    push('\0');

    printf("%s\n", (size() == 1) ? "FRULA" : ghettoStack);
    return 0;
}
