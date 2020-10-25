#include<stdio.h>
#include<stdlib.h>

#define MAX(x, y) ((x>(y))?(x):(y))

int* stack;
int stackHead = 0;
void push(int x){ stack[stackHead++] = x; }
int peek(){ return stack[stackHead-1]; } 
int pop(){ return stack[--stackHead]; } 
void reset(){ stackHead = 0; }

// Solution is similar to /stol
void solve(){
    // Scan in input
    int r, c;
    scanf("%d %d", &r, &c);

    int* count = (int*) calloc(r + c + 1, sizeof(int));
    int* currHeight = (int*) calloc(c+1, sizeof(int));
    int* ansAtCol = (int*) calloc(c+1, sizeof(int));
    stack = (int*) calloc(c+1, sizeof(int));

    // Process each row and char individually
    for (int i = 0; i < r; ++i){
        reset();
        push(0);

        for (int j = 1; j <= c; ++j){
            char curr;
            scanf(" %c", &curr);

            // If we meet a block, reset the height, clear the stack
            if (curr == '#'){
                currHeight[j] = 0;
                reset();
                push(j);
                ansAtCol[j] = 0;
            }
            else{
                int best = 0;
                currHeight[j] += 1;

                // Find the best perimeter a la stol
                while(currHeight[j] < currHeight[peek()]){
                    int length = j - pop() + 1;
                    int tall = currHeight[j];
                    best = MAX(best, length + tall);
                }

                // Last thing: the best is either
                // 1) the ans at the last col + distance to here
                // 2) the current height + distance to here
                int distToHere = j - peek();
                ansAtCol[j] = MAX(ansAtCol[peek()], currHeight[j]) + distToHere;

                // Populate the stack with the current height
                push(j);
                ++count[MAX(best, ansAtCol[j])];
            }
        }
    }

    // Print the answer
    for (int i = 2; i <= (r+c); ++i){
        if (!count[i]) continue;
        printf("%d x %d\n", count[i], i*2);
    }

    // Dobbies are free elves
    free(count);
    free(currHeight);
    free(ansAtCol);
    free(stack);
}

int main(){
    int testcases;
    scanf("%d", &testcases);
    while (testcases--){
        solve();
    }

    return 0;
}

