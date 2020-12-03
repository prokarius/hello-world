#include<stdio.h>

int stack[256];
int stackHead = 0;

void push(int x){ stack[stackHead++] = x; }
int pop(){ return stack[--stackHead]; }
int empty(){ return stackHead == 0; }

int main(){
    // Scan in input
    int n;
    scanf("%d ", &n);

    // Process each character online
    for (int i = 0; i < n; ++i){
        char c;
        scanf("%c", &c);

        switch(c){
            // If it's open brackets, just add to the count
            case('('):
                push(1);
                break;
            case('['):
                push(2);
                break;
            case('{'):
                push(3);
                break;

            // But if it is closed bracets, make sure we have enough!
            case(')'):
                if (empty() || pop() != 1){
                    printf(") %d\n", i);
                    return 0;
                }
                break;
            case(']'):
                if (empty() || pop() != 2){
                    printf("] %d\n", i);
                    return 0;
                }
                break;
            case('}'):
                if (empty() || pop() != 3){
                    printf("} %d\n", i);
                    return 0;
                }
                break;
        }
    }

    // OK cool we are alive
    printf("ok so far\n");

    return 0;
}

